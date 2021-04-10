#include "MQ2TangBot.h"
#include <iterator>
#include <sstream>
#include <chrono>

BOOL DataTangBot(PCHAR Index, MQ2TYPEVAR& dest) {
	dest.DWord = 1;
	dest.Type = pTangBotType;
	return true;
}

BOOL DataSpellsType(PCHAR Index, MQ2TYPEVAR& dest) {
	if (ISINDEX())
	{
		return pSpellsType->GetMember(MQ2VARPTR(), "", Index, dest);
	}
	else
	{
		dest.DWord = 1;
		dest.Type = pSpellsType;
		return true;
	}
}
PreSetup("MQ2TangBot");

PLUGIN_API VOID InitializePlugin(VOID)
{
	pTangBotType = new MQ2TangBotType;
	pSpellsType = new MQ2SpellsType;
	AddMQ2Data("TangBot", DataTangBot);
	AddMQ2Data("Spells", DataSpellsType);
	AddCommand("/loadspells", MQ2LoadSpellsCommand);
	AddCommand("/setcamp", MQ2SetCampCommand);
	AddCommand("/setcampradius", MQ2SetCampRadiusCommand);
	AddCommand("/grouphp", MQ2GroupHPCommand);
	AddCommand("/echospells", MQ2EchoSpellsCommand);
}

PLUGIN_API VOID ShutdownPlugin(VOID)
{
	delete pTangBotType;
	delete pSpellsType;
	RemoveMQ2Data("TangBot");
	RemoveMQ2Data("Spells");
	RemoveCommand("/loadspells");
	RemoveCommand("/setcamp");
	RemoveCommand("/setcampradius");
	RemoveCommand("/grouphp");
	RemoveCommand("/echospells");
}

VOID MQ2SetCampCommand(PSPAWNINFO pChar, PCHAR szLine)
{
	int skipFindCenter = 0;
	if (IsNumber(szLine)) {
		skipFindCenter = atoi(szLine);
	}
	pTangBotType->SetupCamp(skipFindCenter);
	WriteChatf("Camp Set");
}

VOID MQ2SetCampRadiusCommand(PSPAWNINFO pChar, PCHAR szLine)
{
	if (IsNumber(szLine)) {
		auto radius = atof(szLine);
		pTangBotType->SetCampRadius(radius);
		WriteChatf("Radius set to %d", radius);
	}
}
VOID MQ2GroupHPCommand(PSPAWNINFO pChar, PCHAR szLine)
{
	pTangBotType->OrderGroupByHP();
}
VOID MQ2LoadSpellsCommand(PSPAWNINFO pChar, PCHAR szLine)
{
	pSpellsType->ConfigureSpells();
	WriteChatf("Spells Loaded");
}
VOID MQ2EchoSpellsCommand(PSPAWNINFO pChar, PCHAR szLine)
{
	pSpellsType->EchoSpells();
}

MQ2TangBotType::MQ2TangBotType() :MQ2Type("TangBot") {
	TypeMember(LastGroupMemberHP);
	TypeMember(GroupMemberByHP);
	TypeMember(CampX);
	TypeMember(CampY);
	TypeMember(CampZ);
	TypeMember(MinDmgManaPct);
	TypeMember(SpawnInCamp);
	TypeMember(FindXTarget);
	TypeMember(SpawnInXTarget);
	TypeMember(CampRadius);
	TypeMember(TimeStamp);

	TypeMember(CheckImmune);
	TypeMethod(SetCamp);
	TypeMethod(OrderGroup);
}

float MQ2TangBotType::GetCampRadius(const PSPAWNINFO spawn) const {
	float maxRange = get_melee_range(reinterpret_cast<EQPlayer*>(spawn), reinterpret_cast<EQPlayer*>(spawn));
	float maxRangeTo = get_melee_range(pCharSpawn, reinterpret_cast<EQPlayer*>(spawn));
	return _campRadius + (maxRange > maxRangeTo ? maxRange : maxRangeTo);
}

bool MQ2TangBotType::OrderGroupByHP()
{
	_lastGroupMembers = _orderedGroupMembers;
	_lastGroupMembers.clear();
	for (auto orderedGroupMember : _orderedGroupMembers)
		_lastGroupMembers.push_back(orderedGroupMember);
	auto* const pChar = GetCharInfo();
	_orderedGroupMembers.clear();
	GroupMemberHPs me{};
	me.GroupNumber = 0;
	LONG maxhp = pChar->pSpawn->HPMax;
	if (maxhp != 0)
		me.PctHPs = pChar->pSpawn->HPCurrent * 100 / maxhp;
	_orderedGroupMembers.push_back(me);
	for (int i = 1; i < 6; ++i)
	{
		if (ValidGroupMember(pChar, i)) {
			GroupMemberHPs gMember{};
			gMember.GroupNumber = i;
			maxhp = pChar->pGroupInfo->pMember[i]->pSpawn->HPMax;
			if (maxhp != 0)
				gMember.PctHPs = pChar->pGroupInfo->pMember[i]->pSpawn->HPCurrent * 100 / maxhp;
			else
				gMember.PctHPs = 0;
			_orderedGroupMembers.push_back(gMember);
		}
	}
	std::sort(_orderedGroupMembers.begin(), _orderedGroupMembers.end());
	return true;
}

bool MQ2TangBotType::ValidGroupMember(PCHARINFO pChar, const int groupIndex) {
	return pChar->pGroupInfo && pChar->pGroupInfo->pMember[groupIndex] &&
		pChar->pGroupInfo->pMember[groupIndex]->pSpawn &&
		pChar->pGroupInfo->pMember[groupIndex]->pSpawn->Type != SPAWN_CORPSE &&
		pChar->pGroupInfo->pMember[groupIndex]->Offline == 0;
}

bool MQ2TangBotType::SetupCamp(const int skipFindCenter) {

	//There are faster ways (Welzl's Algorithm) but that's too much work, this is a small list of points so n^4 doesn't matter
	auto* const pChar = GetCharInfo();
	auto x = pChar->pSpawn->X, y = pChar->pSpawn->Y, z = pChar->pSpawn->Z;
	auto groupCount = 1;
	//Find the center of the camp
	if (skipFindCenter) {
		_campX = x;
		_campY = y;
		_campZ = z;
	}
	else
	{
		for (auto i = 1; i < 6; ++i)
		{
			if (ValidGroupMember(pChar, i) && !pChar->pGroupInfo->pMember[i]->Puller) {
				//Group Member is in the zone
				groupCount++;
				x += pChar->pGroupInfo->pMember[i]->pSpawn->X;
				y += pChar->pGroupInfo->pMember[i]->pSpawn->Y;
				z += pChar->pGroupInfo->pMember[i]->pSpawn->Z;
			}
		}
		_campX = x / groupCount;
		_campY = y / groupCount;
		_campZ = z / groupCount;
		SetCampRadius();
	}

	return true;
}

bool MQ2TangBotType::SetCampRadius(const float radius)
{
	_campRadius = radius;
	return true;
}

bool MQ2TangBotType::SetCampRadius()
{
	auto* const pChar = GetCharInfo();
	//Find the Radius of the camp
	auto maxDistance = Distance(_campX, _campY, pChar->pSpawn->X, pChar->pSpawn->Y);
	for (int i = 1; i < 6; ++i)
	{
		if (ValidGroupMember(pChar, i) && !pChar->pGroupInfo->pMember[i]->Puller) {
			const auto distance = Distance(_campX, _campY, pChar->pSpawn->X, pChar->pSpawn->Y);
			if (distance > maxDistance)
				maxDistance = distance;
		}
	}
	_campRadius = maxDistance * 1.1f;
	return true;
}


float MQ2TangBotType::Distance(const float x1, const float y1, const float z1, const float x2, const float y2, const float z2) {
	const auto x = x1 - x2;
	const auto y = y1 - y2;
	const auto z = z1 - z2;
	return sqrtf(x * x + y * y + z * z);
}

float MQ2TangBotType::Distance(const float x1, const float y1, const float x2, const float y2) const {
	return Distance(x1, y1, 0, x2, y2, 0);
}

int GetXTargetCount() {
	if (auto* xtm = GetCharInfo()->pXTargetMgr)
	{
		if (xtm->XTargetSlots.Count)
		{
			auto x = 0;
			for (auto n = 0; n < xtm->XTargetSlots.Count; n++)
			{
				const auto xts = xtm->XTargetSlots[n];
				if (xts.xTargetType && xts.XTargetSlotStatus)
				{
					x++;
				}
			}
			return x;
		}
	}
	return 0;
}

bool MQ2TangBotType::GETMEMBER() {
	auto returnValue = false;
	auto* pMethod = FindMethod(Member);
	if (pMethod) {
		switch (static_cast<TangBotMethods>(pMethod->ID))
		{
		case SetCamp:
			returnValue = SetupCamp(0);
			break;
		case OrderGroup:
			returnValue = OrderGroupByHP();
			break;
		}
	}
	else if (PMQ2TYPEMEMBER pMember = FindMember(Member))
	{
		returnValue = true;
		switch (static_cast<TangBotMembers>(pMember->ID))
		{
		case LastGroupMemberHP:
			//Set to return null
			Dest.DWord = 0;
			if (!ISINDEX() || !ISNUMBER()) {
				returnValue = false;
			}
			else {
				const auto index = GETNUMBER() - 1;
				for (unsigned int i = 0; i < _lastGroupMembers.size(); i++)
				{
					if (_lastGroupMembers[i].GroupNumber == index)
						Dest.DWord = _lastGroupMembers[i].PctHPs;
				}
			}
			Dest.Type = pIntType;
			break;
		case CampX:
			Dest.Float = _campX;
			Dest.Type = pFloatType;
			break;
		case CampY:
			Dest.Float = _campY;
			Dest.Type = pFloatType;
			break;
		case CampZ:
			Dest.Float = _campZ;
			Dest.Type = pFloatType;
			break;
		case MinDmgManaPct:
		{
			const auto charClass = GetCharInfo()->pSpawn->mActorClient.Class;
			if (charClass == EQCharacterClasses::Cleric || charClass == EQCharacterClasses::Shaman || charClass == EQCharacterClasses::Druid || charClass == EQCharacterClasses::Enchanter)
				Dest.Int = 30;
			else
				Dest.Int = 5;
			Dest.Type = pIntType;
			break;
		}
		case SpawnInCamp:
		{
			if (!ISINDEX() || !ISNUMBER()) {
				returnValue = false;
				break;
			}
			const auto spawnId = GETNUMBER();
			if (spawnId == 0)
			{
				returnValue = false;
				break;
			}
			auto* const spawn = reinterpret_cast<PSPAWNINFO>(GetSpawnByID(spawnId));
			if (!spawn)
			{
				returnValue = false;
				break;
			}
			Dest.DWord = (Distance(_campX, _campY, spawn->X, spawn->Y) <= GetCampRadius(spawn));
			Dest.Type = pBoolType;
			break;
		}
		case FindXTarget:
		{
			//Loop through XTargets and return an npc in the camp
			Dest.DWord = 0;
			Dest.Type = pSpawnType;
			auto* const charInfo = GetCharInfo();
			if (const auto* xtm = charInfo->pXTargetMgr)
			{
				if (xtm->XTargetSlots.Count)
				{
					for (auto i = 0; i < xtm->XTargetSlots.Count; i++)
					{
						const auto xTarget = xtm->XTargetSlots[i];
						if (xTarget.xTargetType && xTarget.XTargetSlotStatus) {
							if (auto* const ptr = GetXtargetType(xTarget.xTargetType)) {
								if (!strcmp(ptr, "Auto Hater")) {
									if (auto* const pSpawn = reinterpret_cast<PSPAWNINFO>(GetSpawnByID(xTarget.SpawnID))) {
										auto isGroupMark = false;
										for (auto g : charInfo->pSpawn->GroupMarkNPC)
										{
											if (g == pSpawn->GetId())
											{
												isGroupMark = true;
												break;
											}
										}

										if (isGroupMark)
										{
											continue;
										}

										if (Distance(_campX, _campY, pSpawn->X, pSpawn->Y) <= GetCampRadius(pSpawn) && LineOfSight(charInfo->pSpawn, pSpawn)) {
											Dest.Ptr = pSpawn;
											Dest.Type = pSpawnType;
											break;
										}
									}
								}
							}
						}
					}
				}
			}
			break;
		}
		case SpawnInXTarget:
		{
			if (!ISINDEX() || !ISNUMBER()) {
				returnValue = false;
				break;
			}
			const auto spawnId = GETNUMBER();
			Dest.DWord = 0;
			Dest.Type = pIntType;
			if (const auto* xtm = GetCharInfo()->pXTargetMgr)
			{
				if (xtm->XTargetSlots.Count)
				{
					for (int i = 0; i < xtm->XTargetSlots.Count; i++)
					{
						const auto xTarget = xtm->XTargetSlots[i];
						if (xTarget.SpawnID == spawnId) {
							Dest.DWord = 1;
							break;
						}
					}
				}
			}
			break;
		}
		case CampRadius:
			Dest.Float = _campRadius;
			Dest.Type = pFloatType;
			break;
		case CheckImmune:
			//TODO: Come back to this
			Dest.DWord = 0;
			Dest.Type = pBoolType;
			break;
		case GroupMemberByHP:
			Dest.Type = pGroupMemberType;
			if (!ISINDEX())
			{
				returnValue = true;
				Dest.DWord = _orderedGroupMembers[0].GroupNumber;
			}
			else
			{
				if (ISNUMBER())
				{
					returnValue = true;
					auto index = static_cast<unsigned int>(GETNUMBER());
					index = index - 1;

					if (index >= 0 && index < _orderedGroupMembers.size())
					{
						Dest.DWord = _orderedGroupMembers[index].GroupNumber;
					}
					else
					{
						returnValue = false;
					}
				}
			}
			break;
		case TimeStamp:
			Dest.Type = pInt64Type;
			Dest.Int64 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
			returnValue = true;
			break;
		default:;
		}
	}
	return returnValue;
}

MQ2SpellsType::MQ2SpellsType() :MQ2Type("Spells") {
	TypeMethod(FindSpells);
	_poisonItemId = 0;
}

void MQ2SpellsType::ConfigureCombatAbilities(PSPAWNINFO pSpawn, int characterClass) {
	int combatAbility = 0;
	std::unordered_map<int, PSPELL> berserkerAxes;
	while (combatAbility < NUM_COMBAT_ABILITIES && pCombatSkillsSelectWnd->ShouldDisplayThisSkill(combatAbility))
	{
		if (PSPELL spell = GetSpellByID(pPCData->GetCombatAbility(combatAbility))) {
			std::string spellType = "";
			switch (characterClass)
			{
			case EQCharacterClasses::Rogue:
				if (spell->spaindex == 51) {
					if (spell->NumEffects == 4) {
						spellType = "AssassinStrike";
					}
				}
				else if (!strcmp(spell->Name, "Theif's Eyes")) {
					spellType = "ThiefEyes";
				}
				else if (strstr(spell->Name, "Pinpoint")) {
					spellType = "PinPoint";
				}
				break;
			case EQCharacterClasses::Warrior:
				if (spell->Category == SpellCategories::CombatAbilities && spell->spaindex == 51 && spell->NumEffects == 2)
					spellType = "Provoke";
				else if (spell->Category == SpellCategories::Auras)
					spellType = "Aura";
				break;
			case EQCharacterClasses::Berserker:
				switch (spell->Category)
				{
				case SpellCategories::CreateItem:
				{
					const long itemId = GetSpellBase(spell, 0);
					berserkerAxes.insert_or_assign(itemId, spell);
					break;
				}
				case SpellCategories::UtilityDetrimental:
					if (spell->Subcategory == SpellSubCategories::Snare)
						spellType = "Snare";
					else if (spell->Subcategory == SpellSubCategories::Jolt)
						spellType = "Jolt";
					break;
				case SpellCategories::DirectDamage:
					if (spell->Subcategory == SpellSubCategories::Stun)
						spellType = "StunNuke";
					break;
				case SpellCategories::CombatAbilities:
					if (spell->Subcategory == SpellSubCategories::Physical)
						spellType = "Volley";
					break;
				case SpellCategories::Auras:
					if (spell->Subcategory == SpellSubCategories::Attack)
						spellType = "Aura";
					break;
				case SpellCategories::StatisticBuffs:
					if (spell->Subcategory == SpellSubCategories::Attack)
						spellType = "Cry";
					break;
				}
				break;
			}
			if (spellType[0]) {
				SetSpell(spellType, spell, characterClass);
			}
		}
		combatAbility++;
	}
	//if we're a berserker we have to assign spell axes as well.
	if (characterClass == EQCharacterClasses::Berserker)
	{
		SetAxes(pSpawn, "Jolt", berserkerAxes);
		SetAxes(pSpawn, "Snare", berserkerAxes);
		SetAxes(pSpawn, "StunNuke", berserkerAxes);

		//And of course Volley is different, they have a reagentId[0] of -1 even thought they do have a reagent. Luckily it's the name of the Volley Spell
		auto iterator = Spells.find("Volley");
		if (iterator != Spells.end())
		{
			PSPELL axeSpell = nullptr;
			//there's no pretty way to do this...
			if (_strcmpi(iterator->second->Name, "Rage Volley") == 0)
			{
				//Magic number, ID of Rage Axe
				const auto axeIterator = berserkerAxes.find(69020);
				if (axeIterator != berserkerAxes.end())
				{
					axeSpell = axeIterator->second;
				}
			}
			else
			{
				//Things seem to get better at this point. We can find the axe that is the closest lower level spell to our volley spell
				auto* const volleyLevel = iterator->second->ClassLevel;
				for (auto axe : berserkerAxes)
				{
					if (axe.second->ClassLevel > volleyLevel)
						continue;
					if (axeSpell)
					{
						if (volleyLevel - axeSpell->ClassLevel > volleyLevel - axe.second->ClassLevel)
						{
							axeSpell = axe.second;
						}
					}
					else
					{
						axeSpell = axe.second;
					}
				}
			}
			if (axeSpell)
			{
				SetSpell("VolleyAxe", axeSpell, EQCharacterClasses::Berserker);
			}
		}
	}
}

void MQ2SpellsType::SetAxes(PSPAWNINFO pSpawn, const std::string& spellType, std::unordered_map<int, PSPELL>& axeSpells)
{
	auto iterator = Spells.find(spellType);
	if (iterator != Spells.end())
	{
		if (iterator->second->ReagentCount[0])
		{
			//This is needed because otherwise the compiler seems decide  axeSpell!=axeSpells.end() is true for the 'Jolt' spell.. I've no idea what's going on here
			auto* spell = iterator->second;
			auto reagentId = spell->ReagentID[0];
			if (reagentId) {
				const auto axeSpell = axeSpells.find(reagentId);
				if (axeSpell != axeSpells.end())
				{
					SetSpell(spellType + "Axe", axeSpell->second, EQCharacterClasses::Berserker);
				}
			}
		}
	}
}

bool MQ2SpellsType::ConfigureSpells() {
	Spells.clear();
	auto* pSpawn = GetCharInfo()->pSpawn;
	auto characterClass = pSpawn->mActorClient.Class;
	if (!ClassInfo[characterClass].PureCaster) {
		ConfigureCombatAbilities(pSpawn, characterClass);
	}
	if (ClassInfo[characterClass].CanCast) {
		auto* spellBook = GetCharInfo2()->SpellBook;
		for (auto i = 0; i < NUM_BOOK_SLOTS; ++i)
		{
			if (spellBook[i] == -1)
				continue;
			auto* spell = GetSpellByID(spellBook[i]);
			std::string spellType;
			auto ignoreType = false;
			switch (spell->Category)
			{
			case SpellCategories::Heals:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::Heals:
					//
					if (strstr(spell->Name, "Remedy"))
					{
						FindQuickHealSpell(spell);
					}
					else
					{
						spellType = FindHealSpell(spell);
					}
					break;
				case SpellSubCategories::Cure:
					spellType = FindCureSpell(spell);
					break;
				case SpellSubCategories::ManaFlow:
					if (characterClass == EQCharacterClasses::Wizard) {
						spellType = "Harvest";
					}
					break;
				case SpellSubCategories::Resurrection:
					spellType = FindResurrectionSpell(spell);
					break;
				case SpellSubCategories::DurationHeals:
					spellType = FindDurationHealSpell(spell);
					break;
				case SpellSubCategories::QuickHeal:
					spellType = FindQuickHealSpell(spell);
					break;
				case SpellSubCategories::Delayed:
					spellType = "DelayHeal";
					break;
				case SpellSubCategories::Misc:
					spellType = FindMiscHealSpell(spell);
					break;
				}
				break;
			case SpellCategories::StatisticBuffs:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::ArmorClass:
					spellType = "ArmorClass";
					break;
				case SpellSubCategories::Strength:
					//Duration in ticks
					if (GetSpellDuration(spell, pSpawn) > 10)
						spellType = "StrBuff";
					break;
				case SpellSubCategories::WisdomIntelligence:
					spellType = "IntBuff";
					break;
				case SpellSubCategories::Dexterity:
					spellType = "DexBuff";
					break;
				case SpellSubCategories::Agility:
					spellType = "AgiBuff";
					break;
				case SpellSubCategories::Stamina:
					spellType = "StaBuff";
					break;
				case SpellSubCategories::Charisma:
					spellType = "ChaBuff";
					break;
				case SpellSubCategories::Mana:
					spellType = "ManaBuff";
					break;
				case SpellSubCategories::Attack:
					if (GetCharInfo2()->Class == EQCharacterClasses::Cleric)
						spellType = "Yaulp";
					else
						spellType = "AttackBuff";
					break;
				case SpellSubCategories::ResistBuff:
					spellType = GetResistBuffType(spell);
					break;
				}
				break;
			case SpellCategories::DirectDamage:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::Magic:
					spellType = "Magic";
					break;
				case SpellSubCategories::Cold:
					spellType = "Cold";
					break;
				case SpellSubCategories::Fire:
					spellType = "Fire";
					if (characterClass == EQCharacterClasses::Magician && strstr(spell->Name, "Fickle"))
					{
						spellType = "Fickle";
					}
					break;
				case SpellSubCategories::Summoned:
					spellType = "Summoned";
					break;
				case SpellSubCategories::Undead:
					spellType = "Undead";
					break;
				case SpellSubCategories::Stun:
					spellType = "Stun";
					if (spell->NumEffects == 1)
					{
						ignoreType = true;
					}
					break;
				case SpellSubCategories::Chromatic:
					spellType = "Chromatic";
					break;
				case SpellSubCategories::Poison:
					spellType = "Poison";
					break;
				case SpellSubCategories::Plant:
					spellType = "Plant";
					break;
				case SpellSubCategories::Physical:
					spellType = "Physical";
					break;
				case SpellSubCategories::Animal:
					spellType = "Animal";
					break;
				case SpellSubCategories::Disease:
					spellType = "Disease";
					break;
				case SpellSubCategories::Enthrall:
					spellType = "Mez";
					ignoreType = true;
					break;
				}
				//03=Group v1, 04=PB AE, 05=Single, 06=Self, 08=Targeted AE, 0e=Pet, 28=AE PC v2, 29=Group v2, 2a=Directional
				if (characterClass == EQCharacterClasses::Wizard && spell->TargetType == TargetTypes::Single)
				{
					switch (spell->Subcategory)
					{
					case SpellSubCategories::Cold:
					case SpellSubCategories::Fire:
					case SpellSubCategories::Magic:
						if (strstr(spell->Name, "Wildmagic"))
						{
							spellType = "Wildmagic";
							
						} else if (spell->CastTime < 1000)
						{
							spellType.insert(0, "Quick");
						}
						else if (strstr(spell->Name, "Lure") || strstr(spell->Name, "lure"))
						{
							spellType += "Lure";
						}
						else if (strstr(spell->Name, "Energy"))
						{
							spellType += "Fickle";
						}
						else if (strstr(spell->Name, "Mindfreeze"))
						{
							spellType = "Jolt";
						}
						break;
					default: break;
					}
				}
				
				if (!ignoreType && spellType[0]) {
					switch (spell->TargetType)
					{
					case TargetTypes::PBAE://PBAE
						spellType += "PBAE";
						break;
					case TargetTypes::Undead:
					case TargetTypes::Summoned:
					case TargetTypes::Single://Single
						spellType += "Nuke";
						break;
					case TargetTypes::LineofSight:
						spellType += "Bolt";
						break;
					case TargetTypes::AESummoned:
					case TargetTypes::AEUndead:
					case TargetTypes::TargetedAE://TargetedAE
						spellType += "Rain";
						break;
					case TargetTypes::DirectionalAE://Directional
						spellType += "Cone";
						break;
					case TargetTypes::Beam://Directional
						spellType += "Beam";
						break;
					case TargetTypes::FreeTarget://Directional
						spellType += "Splash";
						break;
					}
				}
				break;
			case SpellCategories::UtilityBeneficial:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::Invulnerability:
					spellType = "DA";
					break;
				case SpellSubCategories::Spellshield:
					if (spell->TargetType == TargetTypes::Self)
						spellType = "SelfSpellShield";
					else if (spell->TargetType == TargetTypes::Single)
						spellType = "SpellShield";
					break;
				case SpellSubCategories::Invisibility:
					break;
				case SpellSubCategories::Movement:
					if (spell->TargetType == TargetTypes::Single) {
						if (strstr(spell->Name, "Spirit of Wolf") || strstr(spell->Name, "Spirit of Eagle")) {
							spellType = "SoW";
						}
					}
					else if (strstr(spell->Name, "Pack Spirit") || strstr(spell->Name, "Flight of Eagles") || strstr(spell->Name, "Spirit of Bih`Li"))
						spellType = "GroupSoW";
					break;
				case SpellSubCategories::DamageShield:
					if (characterClass == EQCharacterClasses::Cleric) {
						spellType = "Mark";
					}
					else {
						if (spell->TargetType == TargetTypes::Self)
							spellType = "SelfDamageShield";
						else
						{
							if (characterClass == EQCharacterClasses::Magician && GetSpellDuration(spell, pSpawn) <= 10)
								spellType = "BurstDamageShield";
							else
								spellType = "DamageShield";
						}
					}
					break;
				case SpellSubCategories::SpellFocus:
					if (spell->TargetType == TargetTypes::Single)
						spellType = "SpellHaste";
					break;
				case SpellSubCategories::MeleeGuard:
					spellType = "Vie";
					break;
				case SpellSubCategories::Rune:
					if (spell->TargetType == TargetTypes::Self) {
						spellType = "SelfRune";
					}
					else if (spell->TargetType == TargetTypes::Single) {
						spellType = "Rune";
					}
					else {
						spellType = "GroupRune";
					}
					break;
				case SpellSubCategories::Twincast:
					spellType = "Twincast";
					break;
				case SpellSubCategories::Haste:
					if (spell->TargetType == TargetTypes::Single)
						spellType = "Haste";
					else
						spellType = "GroupHaste";
					break;
				case SpellSubCategories::Conversions:
					if (characterClass == EQCharacterClasses::Shaman)
						spellType = "Canni";
					else
						spellType = "Lich";
					break;
				case SpellSubCategories::CombatInnates:
					switch (characterClass)
					{
					case EQCharacterClasses::Cleric:
						spellType = "HealProc";
						break;
					case EQCharacterClasses::Paladin:
						if (spell->spaindex == 19)
						{
							if (spell->ReuseTimerIndex == 12)
							{
								spellType = "DefensiveProc";
							}
							else
							{
								spellType = "FuryProc";
							}
						}
						else if (strstr(spell->Name, "Remorse"))
						{
							spellType = "RemorseProc";
						}
						break;
					case EQCharacterClasses::Magician:
						spellType = "DefensiveProc";
						break;
					case EQCharacterClasses::Ranger:
						spellType = "MagicProc";
						break;
					case EQCharacterClasses::Shaman:
						if (spell->spaindex == 7)
						{
							if (spell->TargetType == TargetTypes::Self)
							{
								spellType = "SpellProc";
							}
							else
							{
								spellType = "Puma";
							}
						}
						break;
					case EQCharacterClasses::Enchanter:
						if (spell->TargetType == TargetTypes::Self) {
							if (strstr(spell->Name, "Ward"))
								spellType = "DefensiveProc";
						}
						else if (strstr(spell->Name, "Mana")) {
							spellType = "ManaFlare";
						}
						break;
					case EQCharacterClasses::ShadowKnight:
						//This will work as long as they stick with the naming scheme, I'm sure they'll add more later, but works up till lvl 95
						// after that you might get a mana tap proc as your LeechProc
						if (strstr(spell->Name, "Skin"))
						{
							spellType = "DefensiveProc";
						}
						else if (strstr(spell->Name, "Horror")) {
							spellType = "LeechProc";
						}
						else {
							spellType = "TapProc";
						}
					default:
						break;
					}
					break;
				case SpellSubCategories::Reflection:
					spellType = "Reflect";
					break;
				case SpellSubCategories::SpellGuard:
					if (spell->TargetType == TargetTypes::Single)
						spellType = "SpellGuard";
					else if (spell->TargetType == TargetTypes::Self)
						spellType = "SelfSpellGuard";
					else
						spellType = "GroupSpellGuard";
					break;
				case SpellSubCategories::Levitate:
					spellType = "Levitate";
					break;
				case SpellSubCategories::Visages:
					if (spell->TargetType == TargetTypes::Single && characterClass == EQCharacterClasses::ShadowKnight)
					{
						spellType = "AggroVisage";
					}
					break;
				case SpellSubCategories::Misc:
					switch (characterClass)
					{
					case EQCharacterClasses::Cleric:
						if (strstr(spell->Name, "Mark"))
							spellType = "Mark";
						else if (!strcmp(spell->Name, "Death Pact"))
							spellType = "DeathPact";
						break;
					case EQCharacterClasses::Wizard:
						if (strstr(spell->Name, "Iceflame of E`ci"))
							spellType = "ColdDmgBuff";
						break;
					case EQCharacterClasses::ShadowKnight:
					case EQCharacterClasses::Necromancer:
						if (spell->spaindex == 19)
							spellType = "FeignDeath";
					}
					break;
				}
				break;
			case SpellCategories::UtilityDetrimental:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::Calm:
					spellType = "Paci";
					break;
				case SpellSubCategories::Charm:
					spellType = "Charm";
					break;
				case SpellSubCategories::Dispel:
					spellType = "Dispel";
					break;
				case SpellSubCategories::Fear:
					spellType = "Fear";
					break;
				case SpellSubCategories::Root:
					if (spell->TargetType == TargetTypes::Single)
						spellType = "Root";
					else
						spellType = "AERoot";
					break;
				case SpellSubCategories::Snare:
					if (spell->TargetType == TargetTypes::Single)
						spellType = "Snare";
					else
						spellType = "AESnare";
					break;
				case SpellSubCategories::Blind:
					spellType = "Blind";
					break;
				case SpellSubCategories::MemoryBlur:
					spellType = "MemBlur";
					break;
				case SpellSubCategories::Disempowering:
					spellType = "Cripple";
					break;
				case SpellSubCategories::ManaDrain:
					spellType = "ManaDrain";
					break;
				case SpellSubCategories::Slow:
					if (spell->CastTime < 2000)
						spellType = "FastSlow";
					else
					{
						if (spell->Resist == 6)
							spellType = "DiseaseSlow";
						else
							spellType = "Slow";

					}
					break;
				case SpellSubCategories::Jolt:
					if (strstr(spell->Name, "for Power"))
					{
						spellType = "ChallengeJolt";
					}
					else if (spell->TargetType == TargetTypes::PBAE) {
						spellType = "PBAEJolt";
					}
					else
					{
						spellType = "Jolt";
					}
					break;
				case SpellSubCategories::ResistDebuffs:
					if (characterClass == EQCharacterClasses::Enchanter)
					{
						if (spell->TargetType == TargetTypes::Single)
						{
							spellType = "Tash";
						}
						else
						{
							spellType = "AETash";
						}
					}
					else if (characterClass == EQCharacterClasses::Necromancer)
					{
						spellType = "Scent";
					}
					else if (characterClass == EQCharacterClasses::Shaman || characterClass == EQCharacterClasses::Magician)
					{
						if (strstr(spell->Name, "Malo"))
							spellType = "Malo";
					}
					break;
				case SpellSubCategories::Enthrall:
					//03=Group v1, 04=PB AE, 05=Single, 06=Self, 08=Targeted AE, 0e=Pet, 28=AE PC v2, 29=Group v2, 2a=Directional, 45 = Free Target
					if (spell->TargetType == TargetTypes::TargetedAE || spell->TargetType == TargetTypes::FreeTarget)
						spellType = "AEMez";
					else if (spell->TargetType == TargetTypes::PBAE)
						spellType = "PBAEMez";
					else
						spellType = "Mez";
					break;
				}
				break;
			case SpellCategories::HPBuffs:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::HPtypeone:
					if (spell->TargetType == TargetTypes::Single/*single*/)
						spellType = "HPType1";
					else
						spellType = "GroupHPType1";
					break;
				case SpellSubCategories::Symbol:
					if (spell->TargetType == TargetTypes::Single/*single*/)
						spellType = "Symbol";
					else
						spellType = "GroupSymbol";
					break;
				case SpellSubCategories::Shielding:
					if (characterClass == EQCharacterClasses::Shaman || characterClass == EQCharacterClasses::Beastlord)
					{
						if (spell->TargetType == TargetTypes::Single)
							spellType = "Focus";
						else
							spellType = "GroupFocus";
					}
					else
						spellType = "Shielding";
					break;
				case SpellSubCategories::Aegolism:
					if (spell->TargetType == TargetTypes::Single/*single*/)
						spellType = "Aego";
					else
						spellType = "GroupAego";
					break;
				case SpellSubCategories::HPtypetwo:
					if (spell->TargetType == TargetTypes::Single/*single*/)
						spellType = "HPType2";
					else
						spellType = "GroupHPType2";
					break;
				}
				break;
			case SpellCategories::DamageOverTime:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::Undead:
					spellType = "Undead";
					break;
				case SpellSubCategories::Fire:
					spellType = "Fire";
					break;
				case SpellSubCategories::Magic:
					if (strstr(spell->Name, "Splurt") || strstr(spell->Name, "Splort") || strstr(spell->Name, "Splart") || strstr(spell->Name, "Splirt"))
					{
						spellType = "Splurt";
					}
					else
					{
						spellType = "Magic";
					}
					break;
				case SpellSubCategories::Cold:
					spellType = "Cold";
					break;
				case SpellSubCategories::Poison:
					spellType = "Poison";
					break;
				case SpellSubCategories::Disease:
					spellType = "Disease";
					break;
				case SpellSubCategories::Snare:
					spellType = "Snare";
					break;
				case SpellSubCategories::Misc:
					spellType = "Misc";
					break;
				case SpellSubCategories::Corruption:
					spellType = "Corruption";
					break;
				}
				if (spellType[0])
					spellType += "Dot";
				break;
			case SpellCategories::Pet:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::PetHaste:
					spellType = "PetHaste";
					break;
				case SpellSubCategories::SumWater:
					spellType = "WaterPet";
					break;
				case SpellSubCategories::SumFire:
					spellType = "FirePet";
					break;
				case SpellSubCategories::SumFamiliar:
					spellType = "Familiar";
					break;
				case SpellSubCategories::SumAir:
					spellType = "AirPet";
					break;
				case SpellSubCategories::SumUndead:
					spellType = "Pet";
					break;
				case SpellSubCategories::SumEarth:
					spellType = "EarthPet";
					break;
				case SpellSubCategories::SumWarder:
					spellType = "Pet";
					break;
				case SpellSubCategories::Heals:
					spellType = "PetHeal";
					break;
				case SpellSubCategories::Delayed:
					spellType = "PetDelayHeal";
					break;
				case SpellSubCategories::CombatInnates:
					spellType = "GuardPet";
					break;
				case SpellSubCategories::ManaFlow:
					spellType = "PetManaTap";
					break;
				case SpellSubCategories::Conversions:
					spellType = "PetManaBuff";
					break;
				case SpellSubCategories::SumSwarm:
					spellType = "SwarmPet";
					break;
				case SpellSubCategories::Block:
					spellType = "PetBlock";
					break;
				case SpellSubCategories::ResistBuff:
					spellType = "PetResist";
					break;
				case SpellSubCategories::PetMiscBuffs:
					if (characterClass == EQCharacterClasses::Beastlord)
					{
						if (strstr(spell->Name, "Spirit of"))
						{
							spellType = "PetProc";
						}
						else if (strstr(spell->Name, "Warder"))
						{
							spellType = "PetTwincastHealProc";
						}
						else if (strstr(spell->Name, "Growl of the"))
						{
							spellType = "PetGrowl";
						}
						else if (strstr(spell->Name, "Protection"))
						{
							spellType = "PetProtection";
						}
						else if (strstr(spell->Name, "Aggression"))
						{
							spellType = "PetAggression";
						}
						else if (strstr(spell->Name, "Jaws"))
						{
							spellType = "PetJaws";
						}
					}
					else if (strstr(spell->Name, "Iceflame") || strncmp("Spirit of ", spell->Name, 10) == 0)
					{
						spellType = "PetProc";
					}
					break;
				case SpellSubCategories::SumAnimation:
					spellType = "Pet";
					break;
				}
				break;
			case SpellCategories::Auras:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::MeleeGuard:
				case SpellSubCategories::HPBuffs:
				case SpellSubCategories::Heals:
					spellType = "Aura";
					break;
				case SpellSubCategories::Mana:
					spellType = "ManaAura";
					break;
				case SpellSubCategories::CombatInnates:
					spellType = "CombatAura";
					break;
				case SpellSubCategories::Learning:
					spellType = "ExpAura";
					break;
				case SpellSubCategories::Disempowering:
					spellType = "DebuffAura";
					break;
				case SpellSubCategories::Rune:
					spellType = "RuneAura";
					break;
				case SpellSubCategories::Twincast:
					spellType = "TwincastAura";
					break;
				case SpellSubCategories::Charm:
					spellType = "CharmAura";
					break;
				}
				break;
			case SpellCategories::Regen:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::Health:
					spellType = "Regen";
					break;
				case SpellSubCategories::Mana:
					spellType = "ManaRegen";
					break;
				case SpellSubCategories::HealthMana:
					spellType = "PhantomShield";
					break;
				}
				break;
			case SpellCategories::Taps:
				switch (spell->Subcategory)
				{
				case SpellSubCategories::DurationTap:
					spellType = "TapDot";
					break;
				case SpellSubCategories::Health:
					spellType = "TapNuke";
					break;
				case SpellSubCategories::HealthMana:
					spellType = "HealthManaTapNuke";
					break;
				case SpellSubCategories::PowerTap:
					if (characterClass == EQCharacterClasses::ShadowKnight)
					{
						if (strstr(spell->Name, "of Pain") || strstr(spell->Name, "of Agony"))
						{
							spellType = "ACTap";
						}
						else if (strstr(spell->Name, "of Hate")) {
							spellType = "ATKTap";
						}
					}
					break;
				}
				break;
			default:
				break;
			}
			if (spellType[0])
			{
				if (spellType == "Mez")
				{
					SetMezSpell(spell, characterClass);
				}
				else if (spellType == "Stun" && characterClass == EQCharacterClasses::Paladin)
				{
					SetStunSpell(spell, characterClass);
				}
				else if (spellType == "Jolt" && characterClass == EQCharacterClasses::ShadowKnight)
				{

					SetJoltSpell(spell, characterClass);
				}
				else if (spellType == "Charm")
				{
					SetCharmSpell(spell,characterClass);
				}
				else
				{
					SetSpell(spellType, spell, characterClass);
				}
			}
		}
	}
	if (characterClass == EQCharacterClasses::Rogue)
	{
		ConfigurePoisonClicky(pSpawn);
	}
	return true;
}

void MQ2SpellsType::EchoSpells()
{
	WriteChatf("Found the following spells");
	for (auto& Spell : Spells)
	{
		WriteChatf("\ao%s:\ax \a-g%s\ax", Spell.first.c_str(), Spell.second->Name);
	}
	if (_poisonItemId != 0)
	{
		auto* const poison = FindItemByID(_poisonItemId);
		WriteChatf("\aoPoisonClicky:\ax \a-g%s\ax", poison->Item1->Name);
	}
}

PSPELL MQ2SpellsType::GetSpellByMember(PMQ2TYPEMEMBER member) {
	std::string stringVal;
	auto spell = Spells.find(stringVal);
	if (spell != Spells.end())
		return spell->second;
	else
		return 0;
}

std::string MQ2SpellsType::FindResurrectionSpell(PSPELL spell)
{
	if (spell->TargetType == TargetTypes::PBAE /*PBAE*/)
		return "AERezSpell";
	return "RezSpell";
}

std::string MQ2SpellsType::FindDurationHealSpell(PSPELL spell)
{
	if (spell->TargetType == TargetTypes::Groupv1/*Group v1*/)
		return "GroupDurationHeal";
	return "DurationHeal";
}

std::string MQ2SpellsType::FindCureSpell(PSPELL spell)
{
	std::string spellType;
	if (!strcmp(spell->Name, "Puratus") || !strcmp(spell->Name, "Antidote") || strstr(spell->Name, "Poison"))
	{
		//Cure poison
		spellType = "CurePoison";
	}
	else if (strstr(spell->Name, "Corruption"))
	{
		//Cure Corruption
		spellType = "CureCorruption";
	}
	else if (strstr(spell->Name, "Disease"))
	{
		//Cure Disease
		spellType = "CureDisease";
	}
	else if (strstr(spell->Name, "Curse"))
	{
		//Cure Curse
		spellType = "CureCurse";
	}
	else if (strstr(spell->Name, "Blindness"))
	{
		//Cure Blindness
		spellType = "CureBlindness";
	}
	else if (!strcmp(spell->Name, "Pure Blood"))
	{
		//Cure Poison/Disease
		spellType = "CurePoisonDisease";
	}
	return spellType;
}

std::string MQ2SpellsType::FindQuickHealSpell(PSPELL spell)
{
	__int64 castTime = GetCastTime(spell);
	if (castTime < 1000)
		return "OhShitHeal";
	return "QuickHeal";
}

std::string MQ2SpellsType::FindMiscHealSpell(PSPELL spell)
{
	if (strstr(spell->Name, "Intervention"))
		return "Intervention";
	return "Contravention";
}

std::string MQ2SpellsType::FindHealSpell(PSPELL spell)
{
	if (!strcmp(spell->Name, "Complete Heal"))
		return "CompleteHeal";
	if (spell->TargetType == TargetTypes::Groupv1 || spell->TargetType == TargetTypes::Groupv2)
		return "GroupHeal";
	if (strstr(spell->Name, "Renewal"))
		return "HealCure";
	return "Heal";
}

std::string MQ2SpellsType::GetResistBuffType(PSPELL spell)
{
	if (strstr(spell->Name, "Poison"))
		return "PoisonResist";
	if (strstr(spell->Name, "Fire"))
		return "FireResist";
	if (strstr(spell->Name, "Disease"))
		return "DiseaseResist";
	if (strstr(spell->Name, "Cold"))
		return "ColdResist";
	if (strstr(spell->Name, "Corruption"))
		return "CorruptionResist";
	if (strstr(spell->Name, "Magic"))
		return "MagicResist";
	if (strstr(spell->Name, "Seasons"))
		return "SeasonsResist";
	return "Resist";
}

bool MQ2SpellsType::IsPotion(_ITEMINFO* itemInfo)
{
	return itemInfo->Type == 0 && itemInfo->ItemType == 21 && itemInfo->Clicky.SpellID != -1 && itemInfo->Clicky.EffectType == 5;
}

void MQ2SpellsType::ConfigurePoisonClicky(PSPAWNINFO pSpawn)
{
	PCONTENTS bestPoison = nullptr;
	PCHARINFO2 pChar2 = GetCharInfo2();
	if (pChar2 && pChar2->pInventoryArray && pChar2->pInventoryArray->InventoryArray) {
		for (auto* pItem : pChar2->pInventoryArray->InventoryArray) {
			if (pItem) {
				_ITEMINFO* itemInfo = GetItemFromContents(pItem);
				if (IsPotion(itemInfo) && (itemInfo->Clicky.RequiredLevel <= pSpawn->Level
					&& (bestPoison && GetItemFromContents(bestPoison)->Clicky.RequiredLevel < itemInfo->Clicky.RequiredLevel || !bestPoison)))
				{
					bestPoison = pItem;
				}
			}
		}
	}
	if (pChar2 && pChar2->pInventoryArray) {
		for (auto* pPack : pChar2->pInventoryArray->Inventory.Pack)
		{
			if (pPack)
			{
				if (GetItemFromContents(pPack)->Type == ITEMTYPE_PACK && pPack->Contents.ContainedItems.pItems)
				{
					for (unsigned long nItem = 0; nItem < GetItemFromContents(pPack)->Slots; nItem++)
					{
						if (const PCONTENTS pItem = pPack->GetContent(nItem))
						{
							_ITEMINFO* itemInfo = GetItemFromContents(pItem);
							if (IsPotion(itemInfo) && (itemInfo->Clicky.RequiredLevel <= pSpawn->Level
								&& (bestPoison && GetItemFromContents(bestPoison)->Clicky.RequiredLevel < itemInfo->Clicky.RequiredLevel || !bestPoison)))
							{
								bestPoison = pItem;
							}
						}
					}
				}
			}
		}
	}
	if (bestPoison)
	{
		_poisonItemId = GetItemFromContents(bestPoison)->ItemNumber;
	}
}

void MQ2SpellsType::SetSpell(std::string spellType, PSPELL spell, int characterClass) {
	auto iterator = Spells.find(spellType);
	if (iterator != Spells.end())
	{
		if (iterator->second->ClassLevel[characterClass] < spell->ClassLevel[characterClass])
		{
			Spells.insert_or_assign(spellType, spell);
		}
	}
	else
	{
		Spells.insert_or_assign(spellType, spell);
	}
};

void MQ2SpellsType::SetMezSpell(PSPELL spell, const int characterClass) {
	const auto mez1 = Spells.find("Mez1");
	const auto mez2 = Spells.find("Mez2");
	const auto mez3 = Spells.find("Mez3");
	if (GetCastTime(spell) < 2000) {
		auto quickMez = Spells.find("QuickMez");
		if (quickMez != Spells.end() && quickMez->second->ClassLevel[characterClass] < spell->ClassLevel[characterClass]) {
			Spells.insert_or_assign("QuickMez", spell);
		}
	}
	else if (mez1 == Spells.end()) {
		Spells.insert_or_assign("Mez1", spell);
	}
	else if (mez2 == Spells.end()) {
		Spells.insert_or_assign("Mez2", spell);
	}
	else if (mez3 == Spells.end()) {
		Spells.insert_or_assign("Mez3", spell);
	}
	else {
		auto* const pSpawn = GetCharInfo()->pSpawn;

		//All mez slots are filled, we have to replace the worse one
		std::unordered_map<std::string, PSPELL>::const_iterator mezSpells[3] = { mez1,mez2,mez3 };
		auto worst = 0;
		//Find the worse mez
		for (auto i = 1; i < 3; i++)
		{
			if (IsWorseMezSpell(mezSpells[worst]->second, mezSpells[i]->second, pSpawn))
			{
				worst = i;
			}
		}

		//Compare the worst mez to the current mez
		if (!IsWorseMezSpell(mezSpells[worst]->second, spell, pSpawn))
		{
			Spells.insert_or_assign(mezSpells[worst]->first, spell);
		}
	}
}

void MQ2SpellsType::SetJoltSpell(_SPELL* spell, const int characterClass)
{
	const auto jolt1 = Spells.find("Jolt1");
	const auto jolt2 = Spells.find("Jolt2");
	const auto jolt3 = Spells.find("Jolt3");
	if (jolt1 == Spells.end()) {
		Spells.insert_or_assign("Jolt1", spell);
	}
	else if (jolt2 == Spells.end()) {
		Spells.insert_or_assign("Jolt2", spell);
	}
	else if (jolt3 == Spells.end()) {
		Spells.insert_or_assign("Jolt3", spell);
	}
	else {
		auto* pSpawn = GetCharInfo()->pSpawn;

		//All jolt slots are filled, we have to replace the worse one
		std::unordered_map<std::string, PSPELL>::const_iterator joltSpells[3] = { jolt1,jolt2,jolt3 };
		auto worst = 0;
		//Find the worse stun
		for (auto i = 1; i < 3; i++)
		{
			if (IsWorseJoltSpell(joltSpells[worst]->second, joltSpells[i]->second, characterClass))
			{
				worst = i;
			}
		}
		if (!IsWorseMezSpell(joltSpells[worst]->second, spell, pSpawn))
		{
			Spells.insert_or_assign(joltSpells[worst]->first, spell);
		}
	}
}

void MQ2SpellsType::SetStunSpell(PSPELL spell, const int characterClass) {
	const auto stun1 = Spells.find("Stun1");
	const auto stun2 = Spells.find("Stun2");
	const auto stun3 = Spells.find("Stun3");
	if (stun1 == Spells.end()) {
		Spells.insert_or_assign("Stun1", spell);
	}
	else if (stun2 == Spells.end()) {
		Spells.insert_or_assign("Stun2", spell);
	}
	else if (stun3 == Spells.end()) {
		Spells.insert_or_assign("Stun3", spell);
	}
	else {
		auto* pSpawn = GetCharInfo()->pSpawn;

		//All stun slots are filled, we have to replace the worse one
		std::unordered_map<std::string, PSPELL>::const_iterator stunSpells[3] = { stun1,stun2,stun3 };
		auto worst = 0;
		//Find the worse stun
		for (auto i = 1; i < 3; i++)
		{
			if (IsWorseStunSpell(stunSpells[worst]->second, stunSpells[i]->second, characterClass))
			{
				worst = i;
			}
		}
		if (!IsWorseMezSpell(stunSpells[worst]->second, spell, pSpawn))
		{
			Spells.insert_or_assign(stunSpells[worst]->first, spell);
		}
	}
};

void MQ2SpellsType::SetCharmSpell(_SPELL* spell, int characterClass)
{
	const auto currentCharm = Spells.find("Charm");
	if(currentCharm == Spells.end())
	{
		Spells.insert_or_assign("Charm",spell);
	} else
	{
		auto* const pSpawn = GetCharInfo()->pSpawn;
		auto currentDuration = GetSpellDuration(currentCharm->second, pSpawn);
		auto maxCurrentLevel = GetSpellMax(currentCharm->second,0);
		auto maxCompareLevel =  GetSpellMax(spell,0);
		auto compareDuration = GetSpellDuration(spell,pSpawn);
		if(currentDuration <= 12000 && maxCurrentLevel - maxCompareLevel < 5 && currentDuration < compareDuration)
		{
			Spells.insert_or_assign("Charm",spell);
		}
		else if (maxCurrentLevel < maxCompareLevel)
		{
			Spells.insert_or_assign("Charm",spell);
		}
	}
}

bool MQ2SpellsType::IsWorseJoltSpell(_SPELL* const currentWorst, _SPELL* const compareTo, const int characterClass)
{
	auto isWorse = false;

	if (currentWorst->HateGenerated > compareTo->HateGenerated)
	{
		isWorse = true;
	}
	else if (currentWorst->HateGenerated == compareTo->HateGenerated)
	{
		//Hate generated is the same, on to mana cost
		if (currentWorst->ManaCost < compareTo->ManaCost)
		{
			isWorse = true;
		}
		else if (currentWorst->ManaCost == compareTo->ManaCost)
		{
			//Same mana cost, on to recast time
			if (currentWorst->RecastTime < compareTo->RecastTime)
			{
				isWorse = true;
			}
			else if (currentWorst->RecastTime == compareTo->RecastTime)
			{
				//Same recast, on to level, we want the lowest level
				if (currentWorst->ClassLevel[characterClass] < compareTo->ClassLevel[characterClass])
				{
					isWorse = true;
				}
			}
		}
	}

	return isWorse;
}

bool MQ2SpellsType::IsWorseMezSpell(_SPELL* const currentWorst, _SPELL* const compareTo, PSPAWNINFO spawnInfo)
{
	auto isWorse = false;
	const auto currentMax = GetSpellMax(currentWorst, 0);
	const auto compareMax = GetSpellMax(compareTo, 0);
	if (currentMax > compareMax) {
		isWorse = true;
	}
	else if (currentMax == compareMax) {
		//The mez spells are the same level, we'll get rid of the one that has the lower duration
		const auto currentDuration = GetSpellDuration(currentWorst, spawnInfo);
		const auto compareDuration = GetSpellDuration(compareTo, spawnInfo);
		if (currentDuration > compareDuration) {
			isWorse = true;
		}
		else if (currentDuration == compareDuration) {
			//Same duration, onto cast time
			const auto currentCastTime = GetCastTime(currentWorst);
			const auto compareCastTime = GetCastTime(compareTo);
			if (currentCastTime < compareCastTime) {
				isWorse = true;
			}
			else if (currentCastTime == compareCastTime) {
				//Same cast time, onto recast time
				if (currentWorst->RecastTime < compareTo->RecastTime) {
					isWorse = true;
				}
				else if (currentWorst->RecastTime == compareTo->RecastTime) {
					//Same recast, time to check mana, after this they're the same
					if (currentWorst->ManaCost < compareTo->ManaCost) {
						isWorse = true;
					}
				}
			}
		}
	}
	return isWorse;
}

bool MQ2SpellsType::IsWorseStunSpell(_SPELL* const currentWorst, _SPELL* const compareTo, const int characterClass)
{
	auto isWorse = false;
	const auto worstMax = GetSpellMax(currentWorst, 0);
	const auto iMax = GetSpellMax(compareTo, 0);
	if (worstMax > iMax) {
		isWorse = true;
	}
	else if (worstMax == iMax) {
		//The stun spells are the same level, we'll get rid of the one with the longest cast time
		const auto worstCastTime = GetCastTime(currentWorst);
		const auto iCastTime = GetCastTime(currentWorst);
		if (worstCastTime < iCastTime)
		{
			isWorse = true;
		}
		else if (worstCastTime == iCastTime)
		{
			//Same cast time, on to mana cost
			if (currentWorst->ManaCost > compareTo->ManaCost)
			{
				isWorse = true;
			}
			else if (currentWorst->ManaCost == compareTo->ManaCost)
			{
				//Same mana cost, on to recast time
				if (currentWorst->RecastTime < compareTo->RecastTime)
				{
					isWorse = true;
				}
				else if (currentWorst->RecastTime == compareTo->RecastTime)
				{
					//Same recast, now we just go with lowest level to help with fizzles I guess
					if (currentWorst->ClassLevel[characterClass] < compareTo->ClassLevel[characterClass])
					{
						isWorse = true;
					}
				}
			}
		}
	}
	return isWorse;
}

long long MQ2SpellsType::GetCastTime(PSPELL spell)
{

	VePointer<CONTENTS>pc;
	DWORD n = 0;
	const auto mct = static_cast<__int64>(GetCastingTimeModifier(reinterpret_cast<EQ_Spell*>(spell)) + GetFocusCastingTimeModifier(
		reinterpret_cast<EQ_Spell*>(spell), pc, false) + spell->CastTime);
	if (mct < (spell->CastTime / 2))
		return spell->CastTime / 2;
	return mct;
}

bool MQ2SpellsType::GETMEMBER()
{
	bool returnValue = false;
	if (ISINDEX()) {
		if (!strcmp(Index, "PoisonClicky"))
		{
			Dest.Ptr = FindItemByID(_poisonItemId);
			Dest.Type = pItemType;
			returnValue = true;
		}
		else
		{
			Dest.DWord = 0;
			PCHAR pName = GETFIRST();
			std::string name = std::string(pName);
			auto spell = Spells.find(name);
			if (spell != Spells.end()) {
				Dest.Ptr = spell->second;
			}
			Dest.Type = pSpellType;
			returnValue = true;
		}
	}
	else
	{
		PMQ2TYPEMEMBER pMethod = MQ2SpellsType::FindMethod(Member);
		if (pMethod) {
			switch ((SpellsMethods)pMethod->ID)
			{
			case FindSpells:
				returnValue = ConfigureSpells();
				break;
			}
		}
	}

	return returnValue;
}
