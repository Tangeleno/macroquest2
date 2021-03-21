#pragma once
#include "ZMQHandler.h"
#include "../MQ2Plugin.h"


enum class EQGameState
{
	CharacterSelect = 1,
	CharacterCreate = 2,
	Unknown = 4,
	InGame = 5,
	PreCharacterSelect = -1,
	PostFrontLoad = 500,
	LoggingIn = 253,
	Unloading = 255
};

enum class EQCharacterState
{
	Stand = 0,
	Sit,
	Duck,
	Bind,
	Feign,
	Dead,
	Stun,
	Hover,
	Mount,
	Unknown
};

enum class EQCombatState
{
	Unknown = 0,
	Combat,
	Debuffed,
	CoolDown,
	Active,
	Resting
};

union byteConverter
{
	int Int;
	long long Int64;
	unsigned long ULong;
	float Float;
	unsigned long long UInt64;
	byte Byte;
	short Short;
	unsigned short UShort;
	unsigned int UInt;
	byte Raw[8];
	
};

class EQRelay
{
private:
	ZMQHandler _zmq;
	bool _zoning = false;
	bool _welcomed = false;

	EQGameState _previousGameState = EQGameState::Unknown;
	EQGameState _currentGameState = EQGameState::Unknown;
	std::string _serverName;
	std::string _characterName;
	std::string _id;
	std::vector<byte> _idBuffer;
	unsigned long long _joinAttemptDelay = 0;
	unsigned long long _nextTargetUpdate = 0;
	unsigned long long _nextSelfUpdate = 0;
	unsigned long long _nextPetUpdate = 0;
	unsigned long long _nextGroupUpdate = 0;
	unsigned long long _nextXTargetUpdate = 0;
	unsigned long long _nextStatUpdate = 0;
	unsigned long long _nextInventoryUpdate = 0;
	unsigned long long _nextSpawnUpdate = 0;
	int _xTargetUpdateInterval = 16;
	int _selfUpdateInterval = 16;
	int _petUpdateInterval = 16;
	int _groupUpdateInterval = 500;
	int _targetUpdateInterval = 16;
	int _inventoryUpdateInterval = 500;
	int _spawnUpdateInterval = 500;
	int _statUpdateInterval = 500;
	int _currentZoneId = 0;
	std::string _zoneName;
	static int GetInt(std::vector<byte>& buffer, int offset);
	static float GetFloat(std::vector<byte>& buffer, int offset);
	static unsigned int GetUInt(std::vector<byte>& buffer, int offset);
	static unsigned long GetULong(std::vector<byte>& buffer, int offset);
	static long long GetInt64(std::vector<byte>& buffer, int offset);
	static std::string GetString(std::vector<byte>& buffer, int offset);
	static void InsertIntoBuffer(std::vector<unsigned char>& buffer, const byteConverter& bytes, int length);
	static void GetBytes(std::vector<byte>& buffer, int value);
	static void GetBytes(std::vector<byte>& buffer, float value);
	static void GetBytes(std::vector<byte>& buffer, unsigned int value);
	static void GetBytes(std::vector<byte>& buffer, unsigned long value);
	static void GetBytes(std::vector<byte>& buffer, long long value);
	static void GetBytes(std::vector<byte>& buffer, const std::string& value);
	static void GetBytes(std::vector<byte>& buffer, char string[], int length);
	static int GetCharacterState(_SPAWNINFO* characterSpawn);
	static int GetCombatState(_CPLAYERWND* playerWindow);
	static int GetPctHPs(_SPAWNINFO* spawn);
	void SelfUpdate(std::vector<byte>& buffer) const;
	void InventoryUpdate(std::vector<byte>& buffer) const;
	void StatUpdate(std::vector<byte>& buffer) const;
	void PetUpdate(std::vector<byte>& buffer) const;
	void TargetUpdate(std::vector<byte>& buffer) const;
	void SpawnUpdate(std::vector<byte>& buffer) const;
	void GroupUpdate(std::vector<byte>& buffer) const;
	void XTargetUpdate(std::vector<byte>& buffer) const;
	void HandleReceive();

public:
	void ZonedUpdate(bool zoneStart);
	void SetInterval(const std::string& setting, int newInterval);
	void Shutdown() const;
	void Initialize(const std::string& publishEndpoint, const std::string& subscribeEndpoint);
	
	void Pulse();
	void FullSpawnUpdate(std::vector<byte>& buffer) const;
	void DoAnnounce();
	void DoDepart() const;
	void SetIdBuffer();
	void SetGameState(EQGameState gameState);
	void IncomingChat(const std::string& line, unsigned long color);
	void AddSpawn(PSPAWNINFO spawn);
	void AddSpawn(PGROUNDITEM spawn);
	void RemoveSpawn(PSPAWNINFO spawn);
	void RemoveSpawn(PGROUNDITEM spawn);
	void ForceUpdate(EQTopics topic);
};

