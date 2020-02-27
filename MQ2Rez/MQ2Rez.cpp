

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// Project: MQ2Rez.cpp
// Author: Complete rewrite by eqmule
// Based on the previous work and ideas of TheZ, dewey and s0rcier
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
// v3.0 - Eqmule 07-22-2016 - Added string safety.
// v3.1 - Eqmule 08-22-2017 - Added a delay to pulse for checking the dialog, it has improved performance.
// v3.2 - s0rCieR 01-28-2019 - Added missing command to be executed when you got rezzed! removed rezz sickness check
// v3.3 - EqMule May 16 2019 -Added /rez delay
//
#define    PLUGIN_NAME    "MQ2Rez"

#ifndef PLUGIN_API
	#include "../MQ2Plugin.h"
	PreSetup(PLUGIN_NAME);
	PLUGIN_VERSION(3.3);
#endif PLUGIN_API

int corpsecount = 0;
BOOL Initialized = 0;
BOOL bRezThreadStarted = 0;
BOOL bVoiceNotify = 1;
BOOL bNotified = 0;
BOOL bDoCommand = 0;
unsigned long bCommandPending = 0; // making it a timer so we could delay command
BOOL AutoRezAccept = 0;
DWORD AutoRezPct = 96;
BOOL AutoRezSafeMode = 0;
CHAR RezCommand[MAX_STRING] = {0};
int RezDelay = 100;
ULONGLONG RezDelayTimer = 0;

void DisplayHelp()
{
	WriteChatColor("Usage:");
	WriteChatColor("/rez -> displays settings");
	WriteChatColor("/rez accept on|off -> Toggle auto-accepting rezbox");
	WriteChatColor("/rez pct # -> Autoaccepts rezes only if they are higher than # percent");
	WriteChatColor("/rez delay #### -> sets time in milliseconds to wait before accepting rez.");
	WriteChatColor("/rez setcommand mycommand -> Set the command that you want to run after you are rezzed.");
	WriteChatColor("/rez voice on/off -> Turns on voice macro \"Help\" when in group");
	WriteChatColor("/rez help");
}

void AutoRezCommand(PSPAWNINFO pCHAR, PCHAR zLine) {
	char Parm1[MAX_STRING];
	char Parm2[MAX_STRING];
	GetArg(Parm1,zLine,1);
	GetArg(Parm2,zLine,2);

	if(!_stricmp("help",Parm1)) {
		DisplayHelp();
		return;
	}
	if(!_stricmp("accept",Parm1) && (!_stricmp("on",Parm2) || !_stricmp("1",Parm2))) {
		WritePrivateProfileString("MQ2Rez","accept","on",INIFileName);
		AutoRezAccept = 1;
		return;
	}
	if(!_stricmp("voice",Parm1) && (!_stricmp("on",Parm2) || !_stricmp("1",Parm2))) {
		WritePrivateProfileString("MQ2Rez","VoiceNotify","1",INIFileName);
		bVoiceNotify = 1;
		return;
	}
	if(!_stricmp("voice",Parm1) && (!_stricmp("off",Parm2) || !_stricmp("0",Parm2))) {
		WritePrivateProfileString("MQ2Rez","VoiceNotify","0",INIFileName);
		bVoiceNotify = 0;
		return;
	}
	if(!_stricmp("accept",Parm1) && (!_stricmp("off",Parm2) || !_stricmp("0",Parm2))) {
		WritePrivateProfileString("MQ2Rez","accept","off",INIFileName);
		AutoRezAccept = 0;
		return;
	}
	if(!_stricmp("pct",Parm1)) {
		WritePrivateProfileString("MQ2Rez","RezPct",Parm2,INIFileName);
		AutoRezPct=atoi(Parm2);
		return;
	}
	if(!_stricmp("delay",Parm1)) {
		WritePrivateProfileString("MQ2Rez","RezDelay",Parm2,INIFileName);
		RezDelay=atoi(Parm2);
		return;
	}
	if(!_stricmp("safemode",Parm1)) {
		WritePrivateProfileString("MQ2Rez","SafeMode",Parm2,INIFileName);
		AutoRezSafeMode=atoi(Parm2);
		return;
	}
	
	if(!_stricmp("setcommand",Parm1)) {
		WritePrivateProfileString("MQ2Rez","Command Line",Parm2,INIFileName);
		WriteChatf("Command set to: \ag%s\ax",Parm2);
		GetPrivateProfileString("MQ2Rez","Command Line",0,RezCommand,MAX_STRING,INIFileName);
		strcpy_s(RezCommand,Parm2);
		if(RezCommand[0]=='\0' || !_stricmp(RezCommand,"DISABLED")) {
			bDoCommand = 0;
		} else {
			bDoCommand = 1;
		}
		return;
	}
	
	WriteChatf("MQ2Rez Accept(\ag%s\ax).", (AutoRezAccept ? "on" : "off"));
	WriteChatf("MQ2Rez RezDelay(\ag%dms\ax).", RezDelay);
	WriteChatf("MQ2Rez VoiceNotify(\ag%s\ax).", (bVoiceNotify ? "on" : "off"));
	WriteChatf("MQ2Rez AcceptPct(\ag%d%%\ax).", AutoRezPct);
	WriteChatf("MQ2Rez SafeMode(\ag%s\ax).", (AutoRezSafeMode ? "on" : "off"));
	
	if(RezCommand[0]=='\0' || !_stricmp(RezCommand,"DISABLED")) {
		WriteChatf("Rez Command to run after rez: \agNot Set\ax.");
	} else {
		WriteChatf("Command line set to: \ag%s\ax",RezCommand);
	}
}


bool Rezzy(PSPAWNINFO pChar, PCHAR szLine) {
	if(CSidlScreenWnd *pWnd=(CSidlScreenWnd *)pRespawnWnd) {
		bRezThreadStarted = 0;
		pWnd->SetBGColor(0xFF000000);
		if (pWnd->IsVisible()) {
			if (CListWnd*clist = (CListWnd*)pWnd->GetChildItem("OptionsList")) {
				if (CButtonWnd*cButton = (CButtonWnd*)pWnd->GetChildItem("SelectButton")) {
					CXStr Str;
					CHAR szOut[MAX_STRING] = { 0 };
					for (int index = 0; index < clist->ItemsArray.Count; index++) {
						clist->GetItemText(&Str, index, 1);
						GetCXStr(Str.Ptr, szOut);
						if (_strnicmp(szOut, "Resurrect", 9) == 0) {
							clist->SetCurSel(index);
							break;
						}
					}
					if (cButton->IsEnabled()) {
						SendWndClick2(cButton, "leftmouseup");
						return true;
					}
				}
			}
		}
	}
	return false;
}

PLUGIN_API VOID InitializePlugin()
{
	AddCommand("/rez",AutoRezCommand);
}

PLUGIN_API VOID ShutdownPlugin()
{
	RemoveCommand("/rez");
}

BOOL IsRezSick()
{
	for (unsigned long nBuff=0 ; nBuff<NUM_LONG_BUFFS ; nBuff++)
    {
		if(PSPELL pSpell = GetSpellByID(GetCharInfo2()->Buff[nBuff].SpellID)) {
			if (strstr(pSpell->Name, "Resurrection Sickness")) {
				return TRUE;
			}
		}
    }
	return FALSE;
}
int PulseDelay = 0;
PLUGIN_API VOID OnPulse()
{
	if(GetGameState()==GAMESTATE_INGAME) {
		if (!Initialized) {
			Initialized = true;
			sprintf_s(INIFileName, "%s\\%s_%s.ini", gszINIPath, EQADDR_SERVERNAME, GetCharInfo()->Name);
			AutoRezAccept = GetPrivateProfileInt("MQ2Rez", "Accept", -1, INIFileName);
			if (AutoRezAccept == -1)
			{
				WritePrivateProfileString("MQ2Rez", "Accept", "0", INIFileName);
				AutoRezAccept = 0;
			}
			AutoRezPct = GetPrivateProfileInt("MQ2Rez", "RezPct", -1, INIFileName);
			if (AutoRezPct == -1)
			{
				WritePrivateProfileString("MQ2Rez", "RezPct", "96", INIFileName);
				AutoRezPct = 96;
			}
			RezDelay = GetPrivateProfileInt("MQ2Rez", "RezDelay", -1, INIFileName);
			if (RezDelay == -1)
			{
				WritePrivateProfileString("MQ2Rez", "RezDelay", "100", INIFileName);
				RezDelay = 100;
			}
			AutoRezSafeMode = GetPrivateProfileInt("MQ2Rez", "SafeMode", -1, INIFileName);
			if (AutoRezSafeMode == -1)
			{
				WritePrivateProfileString("MQ2Rez", "SafeMode", "0", INIFileName);
				AutoRezSafeMode = 0;
			}
			bVoiceNotify = GetPrivateProfileInt("MQ2Rez","VoiceNotify" ,-1,INIFileName);
			if (bVoiceNotify == -1)
			{
				WritePrivateProfileString("MQ2Rez", "VoiceNotify", "1", INIFileName);
				bVoiceNotify = 1;
			}
			GetPrivateProfileString("MQ2Rez","Command Line",0,RezCommand,MAX_STRING,INIFileName);
			if (RezCommand[0]=='\0')
			{
				WritePrivateProfileString("MQ2Rez", "Command Line", "DISABLED", INIFileName);
			}
			if(RezCommand[0]=='\0' || !_stricmp(RezCommand,"DISABLED"))
			{
				bDoCommand = 0;
			} 
			else
			{
				bDoCommand = 1;
			}
		}
		if (PCHARINFO pCharInfo = GetCharInfo()) {
			if(bDoCommand && bCommandPending && (unsigned long)clock() > bCommandPending) {
//				if (IsRezSick() && pCharInfo->pSpawn->StandState!=STANDSTATE_DEAD) {
				if (pCharInfo->pSpawn->StandState!=STANDSTATE_DEAD && gbInZone) {
					bCommandPending = 0;
					WriteChatf("Executing Command: \ag%s\ax",RezCommand);
					EzCommand(RezCommand);
				}
			}
			if (PCHARINFO2 pCharInfo2 = GetCharInfo2()) {
				if (pCharInfo->pSpawn && (pCharInfo->pSpawn->RespawnTimer || pCharInfo->pSpawn->StandState == STANDSTATE_DEAD || (pCharInfo2->BoundLocations[0].ZoneBoundID & 0x7FFF) == (pCharInfo->zoneId & 0x7FFF) || corpsecount > 0)) {
					//gLastRezCheck=MQGetTickCount64();
					if (bVoiceNotify && !bNotified) {
						if (pCharInfo->pSpawn->RespawnTimer || pCharInfo->pSpawn->StandState == STANDSTATE_DEAD) {
							bNotified = 1;
						}
						else {
							bNotified = 0;
						}
					}
				}
			}
			if (PulseDelay < 20) {//we just HAVE to slow down this check its choking the engine
				PulseDelay++;
			}
			else {
				PulseDelay = 0;
				if (CSidlScreenWnd *pWnd = (CSidlScreenWnd *)FindMQ2Window("ConfirmationDialogBox")) {
					if (pWnd->IsVisible()) {
						if (CStmlWnd *Child = (CStmlWnd*)pWnd->GetChildItem("cd_textoutput")) {
							CHAR InputCXStr[MAX_STRING] = { 0 };
							GetCXStr(Child->STMLText, InputCXStr, MAX_STRING);
							BOOL bReturn = FALSE;
							DWORD pct = 0;
							BOOL bOktoRez = FALSE;
							if (strstr(InputCXStr, " return you to your corpse")) {
								pct = 100;
								bReturn = TRUE;
							}
							//9047 %1 wants to cast %2 (%3 percent) upon you. Do you wish this?
							if (strstr(InputCXStr, " percent)") || bReturn) {
								bOktoRez = TRUE;
								//its a rez window lets check the pct
								if (PCHAR pTemp = strstr(InputCXStr, "(")) {
									pct = atoi(&pTemp[1]);
								}
								if (AutoRezSafeMode) {
									if (char*pDest = strchr(InputCXStr, ' ')) {
										pDest[0] = '\0';
										if (IsGroupMember(InputCXStr)) {
											bOktoRez = TRUE;
										}
										else if (IsFellowshipMember(InputCXStr)) {
											bOktoRez = TRUE;
										}
										else if (IsGuildMember(InputCXStr)) {
											bOktoRez = TRUE;
										}
										else if (IsRaidMember(InputCXStr)!=-1) {
											bOktoRez = TRUE;
										}
									}
								}
							}
							if (bOktoRez && pct >= AutoRezPct && bRezThreadStarted == 0) {
								bRezThreadStarted = 1;
								//its ok to take the rez.
								//DWORD nThreadID = 0;
								//CreateThread(NULL, 0, AcceptRez, pWnd, 0, &nThreadID);
								WriteChatColor("Accepting Rez now");
								DoCommand(GetCharInfo()->pSpawn,"/notify ConfirmationDialogBox Yes_Button leftmouseup");
								RezDelayTimer = MQGetTickCount64() + RezDelay;
								return;
							}
						}
					}
				}
				if (bRezThreadStarted)
				{
					if (RezDelayTimer < MQGetTickCount64())
					{
						RezDelayTimer = 0;
						if (CSidlScreenWnd *pWnd = (CSidlScreenWnd *)FindMQ2Window("ConfirmationDialogBox")) {
							if (pWnd->IsVisible() == 0) {
								WriteChatColor("Selecting Respawn now");
								Rezzy(NULL, NULL);
								if (bDoCommand) {
									bCommandPending = (unsigned long)clock() + 1000; // evaluating timer
								}
							}
						}
					}
				}
			}
		}
	}
}

PLUGIN_API VOID OnAddSpawn(PSPAWNINFO pNewSpawn)
{
	if (pNewSpawn && pNewSpawn->Type==SPAWN_CORPSE && strstr(pNewSpawn->Name,GetCharInfo()->Name)) {
        corpsecount++;
    }
}

PLUGIN_API VOID OnRemoveSpawn(PSPAWNINFO pSpawn) {
	if (pSpawn && pSpawn->Type==SPAWN_CORPSE && strstr(pSpawn->Name,GetCharInfo()->Name)) {
        if(corpsecount>0) {
			corpsecount--;
		}
    }
}
