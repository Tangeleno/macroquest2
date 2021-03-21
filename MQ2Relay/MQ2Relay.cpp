#include "MQ2Relay.h"
PreSetup("MQ2Relay");

EQRelay Relay;

void SetInterval(PSPAWNINFO pChar, PCHAR szLine) {
	CHAR szCmd[MAX_STRING] = { 0 };
	CHAR Arg1[MAX_STRING] = { 0 };
	CHAR Arg2[MAX_STRING] = { 0 };
	GetArg(Arg1, szLine, 1);
	GetArg(Arg2, szLine, 2);
	if (Arg1[0] == 0 || Arg2[0] == 0) {
		WriteChatColor("\aw\ay/setinterval\ax\a-u:\ax \a-r[stat|self|target|pet|group|spawn|xtarget|inventory] <#>", USERCOLOR_DEFAULT);
		return;
	}
	int newInterval = atoi(Arg2);
	Relay.SetInterval(Arg1, newInterval);;
}


void ForceStatUpdate(PSPAWNINFO pChar, PCHAR szLine)
{
	Relay.ForceUpdate(EQTopics::StatUpdate);
}
void ForceSelfUpdate(PSPAWNINFO pChar, PCHAR szLine)
{
	Relay.ForceUpdate(EQTopics::SelfUpdate);
}
void ForceTargetUpdate(PSPAWNINFO pChar, PCHAR szLine)
{
	Relay.ForceUpdate(EQTopics::TargetUpdate);
}
void ForceAnnounce(PSPAWNINFO pChar, PCHAR szLine)
{
	Relay.DoAnnounce();
}
void ForcePetUpdate(PSPAWNINFO pChar, PCHAR szLine)
{
	Relay.ForceUpdate(EQTopics::PetUpdate);
}
void ForceGroupUpdate(PSPAWNINFO pChar, PCHAR szLine)
{
	Relay.ForceUpdate(EQTopics::GroupUpdate);
}
void ForceSpawnUpdate(PSPAWNINFO pChar, PCHAR szLine)
{
	Relay.ForceUpdate(EQTopics::SpawnUpdate);
}
void ForceXTargetUpdate(PSPAWNINFO pChar, PCHAR szLine)
{
	Relay.ForceUpdate(EQTopics::XTargetUpdate);
}

PLUGIN_API VOID InitializePlugin(VOID)
{
	//WritePrivateProfileString("EQClasses", pEverQuest->GetClassDesc(i), s.c_str(), INIFileName);
	
	AddCommand("/setinterval", SetInterval, 0, 1);
	AddCommand("/statupdate", ForceStatUpdate, 0, 1);
	AddCommand("/selfupdate", ForceSelfUpdate, 0, 1);
	AddCommand("/targetUpdate", ForceTargetUpdate, 0, 1);
	AddCommand("/petUpdate", ForcePetUpdate, 0, 1);
	AddCommand("/groupUpdate", ForceGroupUpdate, 0, 1);
	AddCommand("/spawnupdate", ForceSpawnUpdate, 0, 1);
	AddCommand("/xtargetupdate", ForceXTargetUpdate, 0, 1);
	AddCommand("/forceannounce", ForceAnnounce, 0, 1);
	Relay.Initialize("tcp://localhost:8844", "tcp://localhost:8845");
}

// Called once, when the plugin is to shutdown
PLUGIN_API VOID ShutdownPlugin(VOID)
{
    DebugSpewAlways("Shutting down MQ2Relay");
	Relay.Shutdown();
	RemoveCommand("/setinterval");
	RemoveCommand("/statupdate");
	RemoveCommand("/selfupdate");
	RemoveCommand("/targetUpdate");
	RemoveCommand("/petUpdate");
	RemoveCommand("/groupUpdate");
	RemoveCommand("/buffupdate");
	RemoveCommand("/spawnupdate");
	RemoveCommand("/xtargetupdate");
	RemoveCommand("/forceannounce");
}

// Called after entering a new zone
PLUGIN_API VOID OnZoned()
{
	Relay.ZonedUpdate(false);
}

// Called once directly after initialization, and then every time the gamestate changes
PLUGIN_API VOID SetGameState(DWORD GameState)
{
	Relay.SetGameState(static_cast<EQGameState>(GameState));
}


// This is called every time MQ pulses
PLUGIN_API VOID OnPulse(VOID)
{
	Relay.Pulse();
}

// This is called every time EQ shows a line of chat with CEverQuest::dsp_chat,
// but after MQ filters and chat events are taken care of.
PLUGIN_API DWORD OnIncomingChat(PCHAR Line, DWORD Color)
{
	Relay.IncomingChat(Line, Color);
	return 0;
}

// This is called each time a spawn is added to a zone (inserted into EQ's list of spawns),
// or for each existing spawn when a plugin first initializes
// NOTE: When you zone, these will come BEFORE OnZoned
PLUGIN_API VOID OnAddSpawn(PSPAWNINFO pNewSpawn)
{
	if (pNewSpawn)
		Relay.AddSpawn(pNewSpawn);
}

// This is called each time a spawn is removed from a zone (removed from EQ's list of spawns).
// It is NOT called for each existing spawn when a plugin shuts down.
PLUGIN_API VOID OnRemoveSpawn(PSPAWNINFO pSpawn)
{
	if (pSpawn)
		Relay.RemoveSpawn(pSpawn);
}

// This is called each time a ground item is added to a zone
// or for each existing ground item when a plugin first initializes
// NOTE: When you zone, these will come BEFORE OnZoned
PLUGIN_API VOID OnAddGroundItem(PGROUNDITEM pNewGroundItem)
{
	Relay.AddSpawn(pNewGroundItem);
}

// This is called each time a ground item is removed from a zone
// It is NOT called for each existing ground item when a plugin shuts down.
PLUGIN_API VOID OnRemoveGroundItem(PGROUNDITEM pGroundItem)
{
	Relay.RemoveSpawn(pGroundItem);
}

// This is called when we receive the EQ_BEGIN_ZONE packet is received
PLUGIN_API VOID OnBeginZone(VOID)
{
	Relay.ZonedUpdate(true);
}

// This is called when we receive the EQ_END_ZONE packet is received
PLUGIN_API VOID OnEndZone(VOID)
{
	//relay.ZonedUpdate(false);
	//relay.ZonedUpdate(false);
}
