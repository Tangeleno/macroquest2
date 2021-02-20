#include "EQRelay.h"

int EQRelay::GetInt(std::vector<byte>& buffer, int offset)
{
	byteConverter converter{}; 
	memset(&converter, 0, sizeof(byteConverter));
	converter.Raw[0] = buffer[0 + offset];
	converter.Raw[1] = buffer[1 + offset];
	converter.Raw[2] = buffer[2 + offset];
	converter.Raw[3] = buffer[3 + offset];
	return converter.Int;
}

float EQRelay::GetFloat(std::vector<byte>& buffer, int offset)
{
	byteConverter converter{};
	memset(&converter, 0, sizeof(byteConverter));
	converter.Raw[0] = buffer[0 + offset];
	converter.Raw[1] = buffer[1 + offset];
	converter.Raw[2] = buffer[2 + offset];
	converter.Raw[3] = buffer[3 + offset];
	return converter.Float;
}

unsigned int EQRelay::GetUInt(std::vector<byte>& buffer, int offset)
{
	byteConverter converter{};
	memset(&converter, 0, sizeof(byteConverter));
	converter.Raw[0] = buffer[0 + offset];
	converter.Raw[1] = buffer[1 + offset];
	converter.Raw[2] = buffer[2 + offset];
	converter.Raw[3] = buffer[3 + offset];
	return converter.UInt;
}

unsigned long EQRelay::GetULong(std::vector<byte>& buffer, int offset)
{
	byteConverter converter{};
	memset(&converter, 0, sizeof(byteConverter));
	converter.Raw[0] = buffer[0 + offset];
	converter.Raw[1] = buffer[1 + offset];
	converter.Raw[2] = buffer[2 + offset];
	converter.Raw[3] = buffer[3 + offset];
	return converter.ULong;
}

__int64 EQRelay::GetInt64(std::vector<byte>& buffer, int offset)
{
	byteConverter converter{};
	memset(&converter, 0, sizeof(byteConverter));
	converter.Raw[0] = buffer[0 + offset];
	converter.Raw[1] = buffer[1 + offset];
	converter.Raw[2] = buffer[2 + offset];
	converter.Raw[3] = buffer[3 + offset];
	converter.Raw[4] = buffer[4 + offset];
	converter.Raw[5] = buffer[5 + offset];
	converter.Raw[6] = buffer[6 + offset];
	converter.Raw[7] = buffer[7 + offset];
	return converter.Int64;
}

std::string EQRelay::GetString(std::vector<byte>& buffer, int offset)
{
	const auto stringLength = GetInt(buffer, 0);
	offset += 4;
	return std::string(buffer[offset], stringLength);
}

void EQRelay::InsertIntoBuffer(std::vector<unsigned char>& buffer, const byteConverter& bytes, int length)
{
	for (int i = 0; i < length; ++i)
		buffer.push_back(bytes.Raw[i]);
	/*for (int i = length - 1; i >= 0; --i)
		buffer.push_back(bytes.Raw[i]);*/
}

void EQRelay::GetBytes(std::vector<byte>& buffer, const int value)
{
	byteConverter converter{};
	union
	{
		int Int;
		byte Raw[4];
	} test{};
	memset(&converter, 0, sizeof(byteConverter));
	converter.Int = value;
	test.Int = value;
	InsertIntoBuffer(buffer, converter, 4);
}

void EQRelay::GetBytes(std::vector<byte>& buffer, const unsigned int value)
{
	byteConverter converter{};
	memset(&converter, 0, sizeof(byteConverter));
	converter.UInt = value;
	InsertIntoBuffer(buffer, converter, 4);
}

void EQRelay::GetBytes(std::vector<byte>& buffer, const __int64 value)
{
	byteConverter converter{};
	memset(&converter, 0, sizeof(byteConverter));
	converter.Int64 = value;
	InsertIntoBuffer(buffer, converter, 8);
}

void EQRelay::GetBytes(std::vector<byte>& buffer, const std::string& value)
{
	const int length = value.size();
	GetBytes(buffer, length);
	for (int i = 0; i < length; ++i)
		buffer.push_back(value[i]);
}

void EQRelay::GetBytes(std::vector<byte>& buffer,char string[], int length)
{
	int i;
	//Find the real length of the string
	for (i = 0; i < length; ++i)
	{
		if (string[i] == '\0')
			break;
	}
	GetBytes(buffer, i);
	for (int j = 0; j < i; ++j)
		buffer.push_back(string[j]);
}

void EQRelay::GetBytes(std::vector<byte>& buffer, const unsigned long value)
{
	byteConverter converter{};
	memset(&converter, 0, sizeof(byteConverter));
	converter.ULong = value;
	InsertIntoBuffer(buffer, converter, 4);
}

void EQRelay::GetBytes(std::vector<byte>& buffer,const float value)
{
	byteConverter converter{};
	memset(&converter, 0, sizeof(byteConverter));
	converter.Float = value;
	InsertIntoBuffer(buffer, converter, 4);
}

int EQRelay::GetCharacterState(_SPAWNINFO* const characterSpawn)
{
	EQCharacterState state = EQCharacterState::Unknown;
	if (characterSpawn->PlayerState & 0x20)
		state = EQCharacterState::Stun;
	else if (characterSpawn->RespawnTimer)
		state = EQCharacterState::Hover;
	else if (characterSpawn->Mount)
		state = EQCharacterState::Mount;
	else
		switch (characterSpawn->StandState)
		{
		case STANDSTATE_STAND:
			state = EQCharacterState::Stand;
			break;
		case STANDSTATE_SIT:
			state = EQCharacterState::Sit;
			break;
		case STANDSTATE_DUCK:
			state = EQCharacterState::Duck;
			break;
		case STANDSTATE_BIND:
			state = EQCharacterState::Bind;
			break;
		case STANDSTATE_FEIGN:
			state = EQCharacterState::Feign;
			break;
		case STANDSTATE_DEAD:
			state = EQCharacterState::Dead;
			break;
		default: 
			state = EQCharacterState::Unknown;
		}
	return static_cast<int>(state);
}

int EQRelay::GetCombatState(_CPLAYERWND* const playerWindow)
{
	EQCombatState state = EQCombatState::Unknown;
	switch (playerWindow->CombatState)
	{
	case 0:
		if (reinterpret_cast<CXWnd*>(playerWindow)->GetChildItem("PW_CombatStateAnim"))
			state = EQCombatState::Combat;
		break;
	case 1:
		state = EQCombatState::Debuffed;
		break;
	case 2:
		state = EQCombatState::CoolDown;
		break;
	case 3:
		state = EQCombatState::Active;
		break;
	case 4:
		state = EQCombatState::Resting;
		break;
	default: 
		state= EQCombatState::Unknown;
	}
	return static_cast<int>(state);
}

int EQRelay::GetPctHPs(_SPAWNINFO* const spawn)
{
	const auto maxHP = spawn->HPMax;
	if (maxHP == 0)
		return 0;
	return static_cast<int>(spawn->HPCurrent * 100.0f / maxHP);
}

void EQRelay::SelfUpdate(std::vector<byte>& buffer) const
{
	const auto characterSpawn = reinterpret_cast<PSPAWNINFO>(pLocalPlayer);
	GetBytes(buffer, characterSpawn->SpawnID);
	GetBytes(buffer, *EQADDR_ATTACK);
	GetBytes(buffer, gAutoFire);
	GetBytes(buffer, characterSpawn->CastingData.SpellID);
	
	if(characterSpawn->CastingData.IsCasting())
	{
		GetBytes(buffer, characterSpawn->CastingData.TargetID);
		GetBytes(buffer, characterSpawn->CastingData.SpellETA);
	}
	GetBytes(buffer, characterSpawn->HPCurrent);
	GetBytes(buffer, characterSpawn->ManaCurrent);
	GetBytes(buffer, characterSpawn->EnduranceCurrent);
	GetBytes(buffer, GetCharacterState(characterSpawn));
	GetBytes(buffer, GetCombatState(reinterpret_cast<PCPLAYERWND>(pPlayerWnd)));
	GetBytes(buffer, FindSpeed(characterSpawn));
	GetBytes(buffer, characterSpawn->X);
	GetBytes(buffer, characterSpawn->Y);
	GetBytes(buffer, characterSpawn->Z);
	auto characterInfo2 = GetCharInfo2();
	int buffCount = 0;
	int maxBuffs = GetCharMaxBuffSlots();
	for (int i = 0; i < maxBuffs; ++i)
	{
		if (characterInfo2->Buff[i].SpellID > 0)
			buffCount++;
	}
	GetBytes(buffer, buffCount);
	if(buffCount)
	{
		for (int i = 0; i < maxBuffs; ++i)
		{
			if (characterInfo2->Buff[i].SpellID > 0)
			{
				GetBytes(buffer, characterInfo2->Buff[i].SpellID);
				GetBytes(buffer, GetSpellBuffTimer(characterInfo2->Buff[i].SpellID));
				GetBytes(buffer, i);
			}
		}
	}
}

void EQRelay::InventoryUpdate(std::vector<byte>&buffer) const
{
	//TODO
}

void EQRelay::StatUpdate(std::vector<byte>& buffer) const
{
	//std::vector<byte> buffer;
	auto* const characterSpawn = reinterpret_cast<PSPAWNINFO>(pLocalPlayer);
	auto* const characterInfo = GetCharInfo();
	auto* const characterInfo2 = GetCharInfo2();
	
	GetBytes(buffer, characterSpawn->SpawnID);
	GetBytes(buffer, characterSpawn->Level);
	GetBytes(buffer, characterSpawn->HPMax);
	GetBytes(buffer, characterSpawn->ManaMax);
	GetBytes(buffer, characterSpawn->EnduranceMax);
	GetBytes(buffer, characterInfo->AAExp / 1000.0f);
	GetBytes(buffer, characterInfo->Exp / 1000.0f);
	GetBytes(buffer, characterInfo2->AAPoints);
	
	DWORD totalAAPointsAssigned=0;
	
	for (auto assigned : characterInfo2->AAPointsAssigned)
	{
		totalAAPointsAssigned+=assigned;
	}
	GetBytes(buffer, totalAAPointsAssigned);
	GetBytes(buffer, characterInfo2->AAPointsSpent);

}

void EQRelay::PetUpdate(std::vector<byte>& buffer) const
{
	const auto characterSpawn = reinterpret_cast<PSPAWNINFO>(pLocalPlayer);
	if (characterSpawn->PetID<=0)
	{
		GetBytes(buffer, 0);
		return;
	}
	const auto petSpawn = reinterpret_cast<PSPAWNINFO>(GetSpawnByID(characterSpawn->PetID));
	GetBytes(buffer, petSpawn->SpawnID);
	GetBytes(buffer, petSpawn->Level);
	GetBytes(buffer, GetPctHPs(petSpawn));
	if(petSpawn->WhoFollowing)
		GetBytes(buffer, petSpawn->WhoFollowing->SpawnID);
	else
		GetBytes(buffer, 0);
	GetBytes(buffer, petSpawn->mActorClient.Class);
	GetBytes(buffer, petSpawn->Name);
	auto buffCount = 0;
	const auto petWindow = reinterpret_cast<PEQPETINFOWINDOW>(pPetInfoWnd);
	for (int i = 0; i < NUM_BUFF_SLOTS; ++i)
	{
		if (petWindow->Buff[i] == 0xFFFFFFFF || petWindow->Buff[i] == 0)
			continue;
		buffCount++;
	}
	GetBytes(buffer, buffCount);
	for (int i = 0; i < NUM_BUFF_SLOTS; ++i)
	{
		if (petWindow->Buff[i] == 0xFFFFFFFF || petWindow->Buff[i] == 0)
			continue;
		GetBytes(buffer, GetSpellByID(petWindow->Buff[i])->ID);
		GetBytes(buffer, petWindow->PetBuffTimer[i]);
		GetBytes(buffer, i);

	}
}

void EQRelay::TargetUpdate(std::vector<byte>& buffer) const
{
	if (pTarget)
	{
		const auto pSpawn = reinterpret_cast<PSPAWNINFO>(pTarget);
		GetBytes(buffer, pSpawn->SpawnID);
		GetBytes(buffer, pAggroInfo->aggroData[AD_Player].AggroPct);
		GetBytes(buffer, pAggroInfo->aggroData[AD_Secondary].AggroPct);
		GetBytes(buffer, pAggroInfo->AggroSecondaryID);
		if (gTargetbuffs)
		{
			int buffCount = 0;
			auto targetWnd = reinterpret_cast<PCTARGETWND>(pTargetWnd);
			for (int buff : targetWnd->BuffSpellID)
				if (buff)
					buffCount++;
			GetBytes(buffer, buffCount);
			for (int i = 0; i < NUM_BUFF_SLOTS; ++i)
			{
				const auto buffId = targetWnd->BuffSpellID[i];
				if (buffId)
				{
					GetBytes(buffer, buffId);
					GetBytes(buffer, targetWnd->BuffTimer[i]);
					GetBytes(buffer, i);
				}
			}
		}
		else
		{
			GetBytes(buffer, 0);
		}
	}
	else
	{
		GetBytes(buffer, 0);
	}
}

void EQRelay::SpawnUpdate(std::vector<byte>& buffer) const
{
	const auto characterInfo = GetCharInfo();
	GetBytes(buffer, characterInfo->zoneId & 0x7FFF);
	auto spawn = pSpawnList;
	while (spawn)
	{
		GetBytes(buffer, spawn->SpawnID);
		GetBytes(buffer, GetSpawnType(spawn));
		GetBytes(buffer, spawn->X);
		GetBytes(buffer, spawn->Y);
		GetBytes(buffer, spawn->Z);
		GetBytes(buffer, GetPctHPs(spawn));
		GetBytes(buffer, spawn->Heading*0.703125f);
		spawn = spawn->pNext;
	}
}

void EQRelay::GroupUpdate(std::vector<byte>& buffer) const
{
	const auto characterInfo = GetCharInfo();
	if(characterInfo->pGroupInfo)
	{
		int groupCount = 0;
		std::vector<std::string> groupMemberIds;
		CHAR Name[MAX_STRING] = { 0 };
		for (auto i = 1; i < 6; ++i)
		{
			if (characterInfo->pGroupInfo->pMember[i])
				groupCount++;
		}
		
		GetBytes(buffer,groupCount);
		
		for (auto i = 1; i < 6; ++i)
		{
			if (characterInfo->pGroupInfo->pMember[i])
			{
				GetCXStr(characterInfo->pGroupInfo->pMember[i]->pName, Name, MAX_STRING);
				CleanupName(Name, sizeof Name, FALSE, FALSE);
				GetBytes(buffer, _serverName + "." + Name);
			}
		}
				
	} else
	{
		GetBytes(buffer, 0);
	}
}

void EQRelay::XTargetUpdate(std::vector<byte>& buffer) const
{
	if(auto xManager = GetCharInfo()->pXTargetMgr)
	{
		if (xManager->XTargetSlots.Count)
		{
			int xCount = 0;
			for (auto i = 0; i < xManager->XTargetSlots.Count; i++)
			{
				const auto xSlot = xManager->XTargetSlots[xCount];
				if (xSlot.xTargetType && xSlot.XTargetSlotStatus)
				{
					xCount++;
				}
			}
			GetBytes(buffer, xCount);
			if (xCount > 0)
			{
				for (auto i = 0; i < xManager->XTargetSlots.Count; i++)
				{
					const auto xSlot = xManager->XTargetSlots[i];
					if (xSlot.SpawnID && xSlot.xTargetType == XTARGET_AUTO_HATER)
					{
						GetBytes(buffer, xSlot.SpawnID);
						GetBytes(buffer, pAggroInfo->aggroData[AD_xTarget1 + i].AggroPct);
						GetBytes(buffer,GetPctHPs(reinterpret_cast<PSPAWNINFO>(GetSpawnByID(xSlot.SpawnID))));
					}
				}
			}
		}
	}
	else
	{
		GetBytes(buffer, 0);
	}
}

void EQRelay::HandleReceive()
{
	std::vector<std::vector<byte>> msg;
	if(_zmq.Receive(msg))
	{

		for (size_t i = 0; i < msg.size(); i++)
		{
			const EQTopics topic = static_cast<EQTopics>(GetInt(msg[i], 0));
			switch (topic) {
			case EQTopics::None: break;
			case EQTopics::Join: break;
			case EQTopics::Welcome: 
				if (!_welcomed) {
					_welcomed = true;
					DoAnnounce();
				}
				break;
			case EQTopics::Announce: break;
			case EQTopics::Depart: break;
			case EQTopics::TargetUpdate: break;
			case EQTopics::SelfUpdate: break;
			case EQTopics::XTargetUpdate: break;
			case EQTopics::TellReceived: break;
			case EQTopics::Command: break;
			case EQTopics::UpdateRequest: break;
			case EQTopics::Acknowledged: break;
			case EQTopics::BeginZone: break;
			case EQTopics::EndZone: break;
			case EQTopics::PetUpdate: break;
			case EQTopics::GroupUpdate: break;
			case EQTopics::AnnounceRequest: break;
			case EQTopics::InventoryUpdate: break;
			case EQTopics::StatUpdate: break;
			case EQTopics::SpawnAdd: break;
			case EQTopics::SpawnRemove: break;
			case EQTopics::SpawnUpdate: break;
			case EQTopics::FullSpawnUpdate: break;
			case EQTopics::ZoneRequest:
				ZonedUpdate(false);
				break;
			default:;
			}
		}
	}
}

void EQRelay::ZonedUpdate(const bool zoneStart)
{
	_zoning = zoneStart;
	if (!_welcomed)
		return;
	std::vector<byte> buffer;
	if (_zoning) {
		_zmq.Unsubscribe(_zoneName);
		GetBytes(buffer, _currentZoneId);
		_zmq.AppendTopic(EQTopics::BeginZone, buffer, _idBuffer);
	}
	else
	{
		_currentZoneId = GetCharInfo()->zoneId & 0x7FFF;
		_zoneName = std::string(reinterpret_cast<PZONEINFO>(pZoneInfo)->ShortName);
		_zmq.Subscribe(_zoneName);
		SetIdBuffer();
		GetBytes(buffer, _currentZoneId);
		GetBytes(buffer, reinterpret_cast<PZONEINFO>(pZoneInfo)->ShortName);
		_zmq.AppendTopic(EQTopics::EndZone, buffer, _idBuffer);
		std::vector<byte> spawnBuffer;
		FullSpawnUpdate(spawnBuffer);
		_zmq.AppendTopic(EQTopics::FullSpawnUpdate, spawnBuffer, _idBuffer);
	}
	_zmq.Send();
}

void EQRelay::SetInterval(const std::string& setting, int newInterval)
{
	if (!_stricmp(setting.c_str(), "stat"))
	{
		_statUpdateInterval = newInterval;
	}
	else if (!_stricmp(setting.c_str(), "self"))
	{
		_selfUpdateInterval = newInterval;
	}
	else if (!_stricmp(setting.c_str(), "target"))
	{
		_targetUpdateInterval = newInterval;
	}
	else if (!_stricmp(setting.c_str(), "group"))
	{
		_groupUpdateInterval = newInterval;
	}
	else if (!_stricmp(setting.c_str(), "pet"))
	{
		_petUpdateInterval = newInterval;
	}
	else if (!_stricmp(setting.c_str(), "spawn"))
	{
		_spawnUpdateInterval= newInterval;
	}
	else if (!_stricmp(setting.c_str(), "inventory"))
	{
		_inventoryUpdateInterval = newInterval;
	}
	else if (!_stricmp(setting.c_str(), "xtarget"))
	{
		_xTargetUpdateInterval= newInterval;
	}
}

void EQRelay::Shutdown() const
{
	_zmq.Send(EQTopics::Depart, _idBuffer);
	_zmq.Shutdown();
}

void EQRelay::Initialize(const std::string& publishEndpoint, const std::string& subscribeEndpoint)
{
	_zmq.Initialize(publishEndpoint, subscribeEndpoint);
	_zmq.Subscribe("welcome");
}

void EQRelay::Pulse()
{
	auto tick = MQGetTickCount64();
	if (_currentGameState != EQGameState::InGame || _zoning)
		return;
	HandleReceive();
	if(!_welcomed && tick >=_joinAttemptDelay)
	{
		_zmq.Send(EQTopics::Join);
		_joinAttemptDelay = tick += 320;
		return;
	}
	bool any = false;
	if (tick >= _nextStatUpdate)
	{
		any = true;
		std::vector<byte> buffer;
		StatUpdate(buffer);
		_zmq.AppendTopic(EQTopics::StatUpdate, buffer, _idBuffer);
		_nextStatUpdate = tick + _statUpdateInterval;
	}
	if (tick >= _nextSelfUpdate)
	{
		any = true;
		std::vector<byte> buffer;
		SelfUpdate(buffer);
		_zmq.AppendTopic(EQTopics::SelfUpdate, buffer, _idBuffer);
		_nextSelfUpdate = tick + _selfUpdateInterval;
	}
	if (tick >= _nextTargetUpdate)
	{
		any = true;
		std::vector<byte> buffer;
		TargetUpdate(buffer);
		_zmq.AppendTopic(EQTopics::TargetUpdate, buffer, _idBuffer);
		_nextTargetUpdate = tick + _targetUpdateInterval;
	}
	if (tick >= _nextPetUpdate)
	{
		any = true;
		std::vector<byte> buffer;
		PetUpdate(buffer);
		_zmq.AppendTopic(EQTopics::PetUpdate, buffer, _idBuffer);
		_nextPetUpdate = tick + _petUpdateInterval;
	}
	if (tick >= _nextGroupUpdate)
	{
		any = true;
		std::vector<byte> buffer;
		GroupUpdate(buffer);
		_zmq.AppendTopic(EQTopics::GroupUpdate, buffer, _idBuffer);
		_nextGroupUpdate = tick + _groupUpdateInterval;
	}
	if (tick >= _nextSpawnUpdate)
	{
		any = true;
		std::vector<byte> buffer;
		SpawnUpdate(buffer);
		_zmq.AppendTopic(EQTopics::SpawnUpdate, buffer, _idBuffer);
		_nextSpawnUpdate = tick + _spawnUpdateInterval;
	}
	if (tick >= _nextXTargetUpdate)
	{
		any = true;
		std::vector<byte> buffer;
		XTargetUpdate(buffer);
		_zmq.AppendTopic(EQTopics::XTargetUpdate, buffer, _idBuffer);
		_nextXTargetUpdate = tick + _xTargetUpdateInterval;
	}
	if (tick >= _nextInventoryUpdate)
	{
		any = true;
		std::vector<byte> buffer;
		XTargetUpdate(buffer);
		_zmq.AppendTopic(EQTopics::XTargetUpdate, buffer, _idBuffer);
		_nextInventoryUpdate = tick + _inventoryUpdateInterval;
	}
	if (any && _welcomed)
		_zmq.Send();
}

void EQRelay::FullSpawnUpdate(std::vector<byte>& buffer) const
{
	const auto characterInfo = GetCharInfo();
	GetBytes(buffer, characterInfo->zoneId & 0x7FFF);
	auto spawn = pSpawnList;
	int spawnCount =0;
	while (spawn)
	{
		spawnCount++;
		spawn = spawn->pNext;
	}
	GetBytes(buffer,spawnCount);
	while (spawn)
	{
		GetBytes(buffer, spawn->SpawnID);
		GetBytes(buffer, GetSpawnType(spawn));
		GetBytes(buffer, spawn->X);
		GetBytes(buffer, spawn->Y);
		GetBytes(buffer, spawn->Z);
		GetBytes(buffer, GetPctHPs(spawn));
		GetBytes(buffer, spawn->Heading*0.703125f);
		GetBytes(buffer, spawn->Level);
		GetBytes(buffer, spawn->mActorClient.Class);
		GetBytes(buffer, spawn->MasterID);
		GetBytes(buffer, spawn->PetID);
		GetBytes(buffer, spawn->Name);
		spawn = spawn->pNext;
	}
}

void EQRelay::DoAnnounce()
{
	if (!_welcomed)
		return;

	const std::vector<byte> announceBuffer;
	std::vector<byte> statBuffer;
	std::vector<byte> selfBuffer;
	std::vector<byte> targetBuffer;
	std::vector<byte> petBuffer;
	std::vector<byte> groupBuffer;
	std::vector<byte> fullSpawnBuffer;
	std::vector<byte> zoneBuffer;
	
	StatUpdate(statBuffer);
	SelfUpdate(selfBuffer);
	TargetUpdate(targetBuffer);
	PetUpdate(petBuffer);
	GroupUpdate(groupBuffer);
	FullSpawnUpdate(fullSpawnBuffer);
	
	_currentZoneId = GetCharInfo()->zoneId & 0x7FFF;
	GetBytes(zoneBuffer, _currentZoneId);
	GetBytes(zoneBuffer, reinterpret_cast<PZONEINFO>(pZoneInfo)->ShortName);
	
	_zmq.AppendTopic(EQTopics::Announce, announceBuffer, _idBuffer);
	_zmq.AppendTopic(EQTopics::EndZone, zoneBuffer, _idBuffer);
	_zmq.AppendTopic(EQTopics::StatUpdate, statBuffer, _idBuffer);
	_zmq.AppendTopic(EQTopics::SelfUpdate, selfBuffer, _idBuffer);
	_zmq.AppendTopic(EQTopics::TargetUpdate, targetBuffer, _idBuffer);
	_zmq.AppendTopic(EQTopics::PetUpdate, petBuffer, _idBuffer);
	_zmq.AppendTopic(EQTopics::GroupUpdate, groupBuffer, _idBuffer);
	_zmq.AppendTopic(EQTopics::FullSpawnUpdate, fullSpawnBuffer, _idBuffer);
	_zmq.Send();
}

void EQRelay::DoDepart() const
{
	if (!_welcomed)
		return;
	_zmq.Send(EQTopics::Depart, _idBuffer);
}

void EQRelay::SetIdBuffer()
{
	if (!_id.empty() && _currentZoneId && GetCharInfo()->pSpawn->SpawnID)
	{
		_idBuffer.clear();
		_idBuffer.assign(_id.begin(),_id.end());
	}
}

void EQRelay::SetGameState(EQGameState gameState)
{

	if (gameState == EQGameState::CharacterSelect) {
		if(!_serverName.empty())
		{
			if(_serverName != EQADDR_SERVERNAME) {
				//We aren't on this server anymore
				_zmq.Unsubscribe(_serverName);
				_serverName = EQADDR_SERVERNAME;
				_zmq.Subscribe(_serverName);
			}
		}
		
	}
	if (gameState == EQGameState::InGame) {

		_characterName = GetCharInfo()->Name;
		_id = _serverName + "." + _characterName;
		_currentZoneId = GetCharInfo()->zoneId & 0x7FFF;
		_zmq.Subscribe(_id);
	}
	if (_currentGameState == EQGameState::InGame && gameState == EQGameState::CharacterSelect)
	{
		//We camped.
		DoDepart();
		_characterName.clear();
		if (!_id.empty())
			_zmq.Unsubscribe(_id);
		_id.clear();
		_currentZoneId = 0;
		if (_welcomed)
		{
			_zmq.AppendTopic(EQTopics::Depart);
			_zmq.Send();
		}
	}
	
	if(_previousGameState == EQGameState::Unknown && _currentGameState == EQGameState::Unknown && gameState == EQGameState::InGame || _previousGameState == EQGameState::CharacterSelect && _currentGameState == EQGameState::LoggingIn && gameState == EQGameState::InGame)
	{
		//Plugin loaded while in game
		//Or Character select to in game
		_serverName = EQADDR_SERVERNAME;
		_characterName = GetCharInfo()->Name;
		_id = _serverName + "." + _characterName;
		_currentZoneId = GetCharInfo()->zoneId & 0x7FFF;
		_zmq.Subscribe(_id);
		_zmq.Subscribe(_serverName);
		_zmq.Subscribe(std::string(reinterpret_cast<PZONEINFO>(pZoneInfo)->ShortName));
		if (_welcomed)
			DoAnnounce();
		
		
	}
	_previousGameState = _currentGameState;
	_currentGameState = gameState;
	SetIdBuffer();
}

void EQRelay::IncomingChat(const std::string& line, unsigned long color)
{	
	if (!_welcomed)
		return;
}

void EQRelay::AddSpawn(PSPAWNINFO spawn)
{

	if (_zoning || !_welcomed || _currentGameState != EQGameState::InGame)
		return;
	const auto character = static_cast<PCHARINFO>(GetCharInfo());
	if(spawn->SpawnID!=0 && character->pSpawn!=spawn)
	{
		std::vector<byte> buffer;
		GetBytes(buffer, character->zoneId & 0x7FFF);
		GetBytes(buffer, spawn->SpawnID);

		GetBytes(buffer, GetSpawnType(spawn));
		GetBytes(buffer, spawn->Level);
		GetBytes(buffer, spawn->mActorClient.Class);
		GetBytes(buffer, spawn->X);
		GetBytes(buffer, spawn->Y);
		GetBytes(buffer, spawn->Z);
		GetBytes(buffer, spawn->MasterID);
		GetBytes(buffer, spawn->PetID);
		GetBytes(buffer, spawn->Name);
		_zmq.AppendTopic(EQTopics::SpawnAdd, buffer, _idBuffer);
		_zmq.Send();
	}
}

void EQRelay::AddSpawn(PGROUNDITEM spawn)
{
	if (_zoning || !_welcomed || _currentGameState != EQGameState::InGame)
		return;
}

void EQRelay::RemoveSpawn(const PSPAWNINFO spawn)
{	
	if (_zoning || !_welcomed || _currentGameState != EQGameState::InGame)
		return;
	if(const auto character = GetCharInfo())
	{
		std::vector<byte> buffer;
		GetBytes(buffer, character->zoneId & 0x7FFF);
		GetBytes(buffer, spawn->SpawnID);
		_zmq.AppendTopic(EQTopics::SpawnRemove, buffer, _idBuffer);
		_zmq.Send();
	}
}

void EQRelay::RemoveSpawn(PGROUNDITEM spawn)
{
	if (_zoning|| !_welcomed || _currentGameState != EQGameState::InGame)
		return;
}

void EQRelay::ForceUpdate(const EQTopics topic)
{
	if (!_welcomed)
		return;
	std::vector<byte> buffer;
	switch (topic) {
	case EQTopics::TargetUpdate:
		TargetUpdate(buffer);
		_zmq.AppendTopic(topic, buffer, _idBuffer);
		_zmq.Send();
		break;
	case EQTopics::SelfUpdate:
		SelfUpdate(buffer);
		_zmq.AppendTopic(topic, buffer, _idBuffer);
		_zmq.Send();
		break;
	case EQTopics::XTargetUpdate:
		XTargetUpdate(buffer);
		_zmq.AppendTopic(topic, buffer, _idBuffer);
		_zmq.Send();
		break;
	case EQTopics::PetUpdate:
		PetUpdate(buffer);
		_zmq.AppendTopic(topic, buffer, _idBuffer);
		_zmq.Send();
		break;
	case EQTopics::GroupUpdate:
		GroupUpdate(buffer);
		_zmq.AppendTopic(topic, buffer, _idBuffer);
		_zmq.Send();
		break;
	case EQTopics::StatUpdate:
		StatUpdate(buffer);
		_zmq.AppendTopic(topic, buffer, _idBuffer);
		_zmq.Send();
		break;
	case EQTopics::SpawnUpdate:
		SpawnUpdate(buffer);
		_zmq.AppendTopic(topic, buffer, _idBuffer);
		_zmq.Send();
		break;
	default:;
	}
}
