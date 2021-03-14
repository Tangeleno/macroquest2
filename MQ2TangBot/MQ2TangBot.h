#pragma once
#include "../MQ2Plugin.h"
#define ISINDEX() (Index[0])
#define ISNUMBER() (IsNumber(Index))
#define GETNUMBER() (atoi(Index))
#define GETFIRST() Index
std::vector<std::string> SplitString(const std::string &s, char delim);
class MQ2TangBotType *pTangBotType = 0;
class MQ2SpellsType *pSpellsType = 0;
class MQ2QueueType *pQueueType=0;
class QueueCollectionType *pQueueCollectionType=0;
struct TargetTypes {
	enum {
		TargetAENoPlayersPets = 50,
		PetOwner = 47,
		TargetofTarget = 46,
		FreeTarget = 45,
		Beam = 44,
		SingleinGroup = 43,
		DirectionalAE = 42,
		Groupv2 = 41,
		AEPCv2 = 40,
		NoPets = 39,
		Pet2 = 38,
		CasterPBNPC = 37,
		CasterPBPC = 36,
		SpecialMuramites = 35,
		Chest = 34,
		Hatelist2 = 33,
		Hatelist = 32,
		AESummoned = 25,
		AEUndead = 24,
		TargetedAETap = 20,
		UberDragons = 18,
		UberGiants = 17,
		Plant = 16,
		Corpse = 15,
		Pet = 14,
		LifeTap = 13,
		Summoned = 11,
		Undead = 10,
		Animal = 9,
		TargetedAE = 8,
		Self = 6,
		Single = 5,
		PBAE = 4,
		Groupv1 = 3,
		AEPCv1 = 2,
		LineofSight = 1,
	};
};
struct EQCharacterClasses
{
	enum
	{
		Warrior = 1,
		Cleric,
		Paladin,
		Ranger,
		ShadowKnight,
		Druid,
		Monk,
		Bard,
		Rogue,
		Shaman,
		Necromancer,
		Wizard,
		Magician,
		Enchanter,
		Beastlord,
		Berserker
	};
};
struct SpellCategories
{
	enum {
		ArmorClass = 6,
		Attack = 7,
		Blind = 9,
		Charm = 13,
		Cold = 14,
		CombatAbilities = 15,
		CombatInnates = 16,
		CreateItem = 18,
		Cure = 19,
		DamageOverTime = 20,
		DamageShield = 21,
		Defensive = 22,
		Destroy = 23,
		DirectDamage = 25,
		Disciplines = 27,
		Disease = 29,
		Disempowering = 30,
		Dispel = 31,
		Enthrall = 35,
		Fear = 37,
		Fire = 38,
		FizzleRate = 39,
		Haste = 41,
		Heals = 42,
		Health = 43,
		HealthMana = 44,
		HPBuffs = 45,
		HPtypeone = 46,
		HPtypetwo = 47,
		IllusionOther = 48,
		Invulnerability = 52,
		Jolt = 53,
		LifeFlow = 56,
		Mana = 59,
		ManaDrain = 60,
		Misc = 64,
		Movement = 65,
		Objects = 66,
		Offensive = 68,
		Pet = 69,
		PetMiscBuffs = 71,
		Poison = 75,
		Reflection = 78,
		Regen = 79,
		ResistBuff = 80,
		ResistDebuffs = 81,
		Root = 83,
		Rune = 84,
		Shadowstep = 86,
		Shielding = 87,
		Slow = 88,
		Snare = 89,
		Special = 90,
		SpellFocus = 91,
		StatisticBuffs = 95,
		Stun = 97,
		Taelosia = 113,
		Taps = 114,
		Techniques = 115,
		Transport = 123,
		UtilityBeneficial = 125,
		UtilityDetrimental = 126,
		Traps = 131,
		Auras = 132,
	};
};
struct SpellSubCategories
{
	enum
	{
		Aegolism = 1,
		Agility = 2,
		Alliance = 3,
		Animal = 4,
		Antonica = 5,
		ArmorClass = 6,
		Attack = 7,
		Bane = 8,
		Blind = 9,
		Block = 10,
		Calm = 11,
		Charisma = 12,
		Charm = 13,
		Cold = 14,
		CombatAbilities = 15,
		CombatInnates = 16,
		Conversions = 17,
		CreateItem = 18,
		Cure = 19,
		DamageOverTime = 20,
		DamageShield = 21,
		Defensive = 22,
		Destroy = 23,
		Dexterity = 24,
		DirectDamage = 25,
		DisarmTraps = 26,
		Discord = 28,
		Disease = 29,
		Disempowering = 30,
		Dispel = 31,
		DurationHeals = 32,
		DurationTap = 33,
		EnchantMetal = 34,
		Enthrall = 35,
		Faydwer = 36,
		Fear = 37,
		Fire = 38,
		FizzleRate = 39,
		Fumble = 40,
		Haste = 41,
		Heals = 42,
		Health = 43,
		HealthMana = 44,
		HPBuffs = 45,
		HPtypeone = 46,
		HPtypetwo = 47,
		IllusionOther = 48,
		IllusionAdventurer = 49,
		ImbueGem = 50,
		Invisibility = 51,
		Invulnerability = 52,
		Jolt = 53,
		Kunark = 54,
		Levitate = 55,
		LifeFlow = 56,
		Luclin = 57,
		Magic = 58,
		Mana = 59,
		ManaDrain = 60,
		ManaFlow = 61,
		MeleeGuard = 62,
		MemoryBlur = 63,
		Misc = 64,
		Movement = 65,
		Odus = 67,
		Offensive = 68,
		PetHaste = 70,
		PetMiscBuffs = 71,
		Physical = 72,
		Picklock = 73,
		Plant = 74,
		Poison = 75,
		PowerTap = 76,
		QuickHeal = 77,
		Reflection = 78,
		Regen = 79,
		ResistBuff = 80,
		ResistDebuffs = 81,
		Resurrection = 82,
		Root = 83,
		Rune = 84,
		SenseTrap = 85,
		Shadowstep = 86,
		Shielding = 87,
		Slow = 88,
		Snare = 89,
		Special = 90,
		SpellFocus = 91,
		SpellGuard = 92,
		Spellshield = 93,
		Stamina = 94,
		StatisticBuffs = 95,
		Strength = 96,
		Stun = 97,
		SumAir = 98,
		SumAnimation = 99,
		SumEarth = 100,
		SumFamiliar = 101,
		SumFire = 102,
		SumUndead = 103,
		SumWarder = 104,
		SumWater = 105,
		SummonArmor = 106,
		SummonFocus = 107,
		SummonFoodWater = 108,
		SummonUtility = 109,
		SummonWeapon = 110,
		Summoned = 111,
		Symbol = 112,
		Taelosia = 113,
		Taps = 114,
		Techniques = 115,
		ThePlanes = 116,
		Timer1 = 117,
		Timer2 = 118,
		Timer3 = 119,
		Timer4 = 120,
		Timer5 = 121,
		Timer6 = 122,
		Undead = 124,
		UtilityBeneficial = 125,
		UtilityDetrimental = 126,
		Velious = 127,
		Visages = 128,
		Vision = 129,
		WisdomIntelligence = 130,
		Auras = 132,
		Endurance = 133,
		SerpentsSpine = 134,
		Corruption = 135,
		Learning = 136,
		Chromatic = 137,
		SumSwarm = 139,
		Delayed = 140,
		Temporary = 141,
		Twincast = 142,
		SumBodyguard = 143,
		HasteSpellFocus = 145,
		Timer9 = 148,
		Timer10 = 149,
		Timer11 = 150,
		Timer12 = 151,
		Hatred = 152,
		IllusionSpecial = 154,
		Timer13 = 155,
		Timer14 = 156,
		Timer15 = 157,
		Timer16 = 158,
		Timer17 = 159,
		Timer19 = 161,
		Timer20 = 162,
		Alaris = 163,
		Combination = 164,
		Independent = 165,
		SkillAttacks = 166,
		Incoming = 167,
		Curse = 168
	};
};
struct GroupMemberHPs {
public:
	int GroupNumber;
	int PctHPs;
	bool operator < (const GroupMemberHPs& other) const
	{
		return PctHPs < other.PctHPs;
	}
};
class MQ2TangBotType :public MQ2Type {
private:
	std::vector<GroupMemberHPs> _orderedGroupMembers;
	std::vector<GroupMemberHPs> _lastGroupMembers;
	
	float GetCampRadius(PSPAWNINFO spawn) const;
	static bool ValidGroupMember(PCHARINFO pChar, int groupIndex);
	float _campX{};
	float _campY{};
	float _campZ{};
	float _campRadius{};
	static float Distance(float x1, float y1, float z1, float x2, float y2, float z2);
	float Distance(float x1, float y1, float x2, float y2) const;
public:
	bool SetupCamp(int skipFindCenter);
	bool SetCampRadius(float radius);
	bool SetCampRadius();
	MQ2TangBotType();
	bool OrderGroupByHP();
	enum TangBotMembers {
		CampX,
		CampY,
		CampZ,
		MinDmgManaPct,
		SpawnInCamp,
		FindXTarget,
		SpawnInXTarget,
		CampRadius,
		CheckImmune,
		LastGroupMemberHP,
		GroupMemberByHP
	};
	enum TangBotMethods {
		SetCamp,
		OrderGroup,
	};
	bool GETMEMBER() override;
	bool ToString(MQ2VARPTR VarPtr, PCHAR Destination) override {
		strcpy_s(Destination, MAX_STRING, "TRUE");
		return true;
	}
	bool FromData(MQ2VARPTR &VarPtr, MQ2TYPEVAR &Source) override {
		return false;
	}
	bool FromString(MQ2VARPTR &VarPtr, PCHAR Source) override {
		return false;
	}
};
class MQ2SpellsType :public MQ2Type {
private:
	DWORD _poisonItemId{};
	PSPELL GetSpellByMember(PMQ2TYPEMEMBER member);
	static std::string FindResurrectionSpell(PSPELL spell);
	static std::string FindDurationHealSpell(PSPELL spell);
	static std::string FindCureSpell(PSPELL spell);
	static std::string FindQuickHealSpell(PSPELL spell);
	static std::string FindMiscHealSpell(PSPELL spell);
	static std::string FindHealSpell(PSPELL spell);
	static std::string GetResistBuffType(PSPELL spell);
	static bool IsPotion(_ITEMINFO* itemInfo);
	void ConfigurePoisonClicky(PSPAWNINFO pSpawn);
	void ConfigureCombatAbilities(PSPAWNINFO pSpawn, int characterClass);
	void SetAxes(PSPAWNINFO pSpawn,const std::string& spellType,std::unordered_map<int,PSPELL>& axeSpells);
	void SetSpell(std::string spellType, PSPELL spell, int characterClass);
	void SetMezSpell(const std::string& spellType, PSPELL spell, int characterClass);
	static long long GetCastTime(PSPELL spell);
public:
	std::unordered_map<std::string, PSPELL> Spells;
	MQ2SpellsType();
	bool ConfigureSpells();
	void EchoSpells();

	enum SpellsMembers {

	};
	enum SpellsMethods {
		FindSpells,
	};
	bool GETMEMBER() override;
	bool ToString(MQ2VARPTR VarPtr, PCHAR Destination) override
	{
		strcpy_s(Destination, MAX_STRING, "TRUE");
		return true;
	}
	bool FromData(MQ2VARPTR &VarPtr, MQ2TYPEVAR &Source) override {
		return false;
	}
	bool FromString(MQ2VARPTR &VarPtr, PCHAR Source) override {
		return false;
	}
};
class MQ2QueueType :public MQ2Type
{
public:
	enum QueueTypeMembers {
		Peek,
		Pop,
		Empty
	};
	enum QueueTypeMethods {
		Push, PushVar, Clear
	};
	MQ2QueueType();
	bool GETMEMBER() override;
	bool ToString(MQ2VARPTR VarPtr, PCHAR Destination) override
	{
		strcpy_s(Destination, MAX_STRING, "TRUE");
		return true;
	}
	bool FromData(MQ2VARPTR &VarPtr, MQ2TYPEVAR &Source) override {
		return false;
	}
	bool FromString(MQ2VARPTR &VarPtr, PCHAR Source) override {
		return false;
	}


};
class QueueCollectionType :public MQ2Type
{
private:
	std::unordered_map<std::string, std::queue<int>> _queues;
public:
	bool Lookup(PCHAR Index, MQ2TYPEVAR& Dest);
	enum QueueCollectionTypeMethods
	{
		Add, Remove, Clear
	};
	enum QueueCollectionTypeMembers
	{
		Size, Contains
	};
	QueueCollectionType();
	bool GETMEMBER() override;
	bool ToString(MQ2VARPTR VarPtr, PCHAR Destination) override
	{
		strcpy_s(Destination, MAX_STRING, "TRUE");
		return true;
	}
	bool FromData(MQ2VARPTR &VarPtr, MQ2TYPEVAR &Source) override {
		return false;
	}
	bool FromString(MQ2VARPTR &VarPtr, PCHAR Source) override {
		return false;
	}
};

VOID MQ2LoadSpellsCommand(PSPAWNINFO pChar, PCHAR szLine);
VOID MQ2SetCampCommand(PSPAWNINFO pChar, PCHAR szLine);
VOID MQ2SetCampRadiusCommand(PSPAWNINFO pChar, PCHAR szLine);
VOID MQ2GroupHPCommand(PSPAWNINFO pChar, PCHAR szLine);
VOID MQ2EchoSpellsCommand(PSPAWNINFO pChar, PCHAR szLine);
