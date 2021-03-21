/******************************************************************************
MQ2Main.dll: MacroQuest2's extension DLL for EverQuest
Copyright (C) 2002-2003 Plazmic, 2003-2005 Lax

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
******************************************************************************/
#ifdef PRIVATE
#if defined(TEST)
#include "eqgame-private(test).h"
#endif
#endif

#define __ClientName                                              "eqgame"
#define __ExpectedVersionDate                                     "Mar 16 2021"
#define __ExpectedVersionTime                                     "08:52:05"
#define __ActualVersionDate_x                                      0xB45EE4
#define __ActualVersionTime_x                                      0xB45ED8
#define __ActualVersionBuild_x                                     0xB360C4

#define __ClientOverride                                           0
#define __MacroQuestWinClassName                                  "__MacroQuest2Tray(Test)"
#define __MacroQuestWinName                                       "MacroQuest2(Test)"

// Memory Protection
#define __MemChecker0_x                                            0x664140
#define __MemChecker1_x                                            0x9458C0
#define __MemChecker2_x                                            0x6DE330
#define __MemChecker3_x                                            0x6DE2A0
#define __MemChecker4_x                                            0x898CA0
#define __EncryptPad0_x                                            0xE46F40
#define __EncryptPad1_x                                            0xEA1740
#define __EncryptPad2_x                                            0xE56158
#define __EncryptPad3_x                                            0xE55D58
#define __EncryptPad4_x                                            0xE92550
#define __EncryptPad5_x                                            0xF95020
#define __AC1_x                                                    0x853860
#define __AC2_x                                                    0x618FBF
#define __AC3_x                                                    0x6203A1
#define __AC4_x                                                    0x624510
#define __AC5_x                                                    0x62ADCF
#define __AC6_x                                                    0x62F516
#define __AC7_x                                                    0x618A20
#define __AC1_Data                                                 0x11111111
#define __EP1_Data_x                                               0x24D588

// Direct Input
#define DI8__Main_x                                                0xF950CC
#define DI8__Keyboard_x                                            0xF950D0
#define DI8__Mouse_x                                               0xF9502C
#define DI8__Mouse_Copy_x                                          0xDA1D7C
#define DI8__Mouse_Check_x                                         0xF92B74
#define __AutoSkillArray_x                                         0xDA2C98
#define __Attack_x                                                 0xE40AC7
#define __Autofire_x                                               0xE40AC8
#define __BindList_x                                               0xD97448
#define g_eqCommandStates_x                                        0xD981B0
#define __Clicks_x                                                 0xDA1E34
#define __CommandList_x                                            0xD98D38
#define __CurrentMapLabel_x                                        0xFA5ACC
#define __CurrentSocial_x                                          0xC5246C
#define __DoAbilityList_x                                          0xDD85E8
#define __do_loot_x                                                0x5E1B40
#define __DrawHandler_x                                            0x1614820
#define __GroupCount_x                                             0xF8813A
#define __Guilds_x                                                 0xF8C610
#define __gWorld_x                                                 0xF8834C
#define __HWnd_x                                                   0xF95030
#define __heqmain_x                                                0xF95008
#define __InChatMode_x                                             0xDA1D64
#define __LastTell_x                                               0xDA3CE4
#define __LMouseHeldTime_x                                         0xDA1EA0
#define __Mouse_x                                                  0xF950B8
#define __MouseLook_x                                              0xDA1DFA
#define __MouseEventTime_x                                         0xF8E03C
#define __gpbCommandEvent_x                                        0xF88458
#define __NetStatusToggle_x                                        0xDA1DFD
#define __PCNames_x                                                0xDA3294
#define __RangeAttackReady_x                                       0xDA2F7C
#define __RMouseHeldTime_x                                         0xDA1E9C
#define __RunWalkState_x                                           0xDA1D68
#define __ScreenMode_x                                             0xED445C
#define __ScreenX_x                                                0xDA1D1C
#define __ScreenY_x                                                0xDA1D18
#define __ScreenXMax_x                                             0xDA1D20
#define __ScreenYMax_x                                             0xDA1D24
#define __ServerHost_x                                             0xF88623
#define __ServerName_x                                             0xDD85A8
#define __ShiftKeyDown_x                                           0xDA23F8
#define __ShowNames_x                                              0xDA3138
#define EverQuestInfo__bSocialChanged_x                            0xDD8630
#define __Socials_x                                                0xDD86A8
#define __SubscriptionType_x                                       0xFD9BA8
#define __TargetAggroHolder_x                                      0xFA8480
#define __ZoneType_x                                               0xDA21F8
#define __GroupAggro_x                                             0xFA84C0
#define __LoginName_x                                              0xF9579C
#define __Inviter_x                                                0xE40A44
#define __AttackOnAssist_x                                         0xDA30F4
#define __UseTellWindows_x                                         0xDA342C
#define __gfMaxZoomCameraDistance_x                                0xB3DDC4
#define __gfMaxCameraDistance_x                                    0xB66504
#define __pulAutoRun_x                                             0xDA1E18
#define __pulForward_x                                             0xDA3464
#define __pulBackward_x                                            0xDA3468
#define __pulTurnRight_x                                           0xDA346C
#define __pulTurnLeft_x                                            0xDA3470
#define __pulStrafeLeft_x                                          0xDA3474
#define __pulStrafeRight_x                                         0xDA3478

//// 
//Section 1: Vital Offsets 
//// 
#define instCRaid_x                                                0xF889A8
#define instEQZoneInfo_x                                           0xDA1FF0
#define pinstActiveBanker_x                                        0xF88944
#define pinstActiveCorpse_x                                        0xF8893C
#define pinstActiveGMaster_x                                       0xF88940
#define pinstActiveMerchant_x                                      0xF88938
#define pinstAltAdvManager_x                                       0xED52A0
#define pinstBandageTarget_x                                       0xF88954
#define pinstCamActor_x                                            0xED4450
#define pinstCDBStr_x                                              0xED4028
#define pinstCDisplay_x                                            0xF860B4
#define pinstCEverQuest_x                                          0xF95034
#define pinstEverQuestInfo_x                                       0xDA1D10
#define pinstCharData_x                                            0xF860A4
#define pinstCharSpawn_x                                           0xF8898C
#define pinstControlledMissile_x                                   0xF88998
#define pinstControlledPlayer_x                                    0xF8898C
#define pinstCResolutionHandler_x                                  0x1614A48
#define pinstCSidlManager_x                                        0x16139E4
#define pinstCXWndManager_x                                        0x16139DC
#define instDynamicZone_x                                          0xF8C4E8
#define pinstDZMember_x                                            0xF8C5F8
#define pinstDZTimerInfo_x                                         0xF8C5FC
#define pinstEqLogin_x                                             0xF950E8
#define instEQMisc_x                                               0xD8B8D8
#define pinstEQSoundManager_x                                      0xED5BB0
#define pinstEQSpellStrings_x                                      0xEC4CC8
#define instExpeditionLeader_x                                     0xF8C532
#define instExpeditionName_x                                       0xF8C572
#define pinstGroup_x                                               0xF88136
#define pinstImeManager_x                                          0x16139E0
#define pinstLocalPlayer_x                                         0xF88934
#define pinstMercenaryData_x                                       0xF8FB34
#define pinstMercenaryStats_x                                      0xFA854C
#define pinstModelPlayer_x                                         0xF8894C
#define pinstPCData_x                                              0xF860A4
#define pinstSkillMgr_x                                            0xF91C20
#define pinstSpawnManager_x                                        0xF906F8
#define pinstSpellManager_x                                        0xF91E60
#define pinstSpellSets_x                                           0xE396F0
#define pinstStringTable_x                                         0xF860AC
#define pinstSwitchManager_x                                       0xF85F48
#define pinstTarget_x                                              0xF88988
#define pinstTargetObject_x                                        0xF8609C
#define pinstTargetSwitch_x                                        0xF860A0
#define pinstTaskMember_x                                          0xD8B420
#define pinstTrackTarget_x                                         0xF88990
#define pinstTradeTarget_x                                         0xF88948
#define instTributeActive_x                                        0xD8B8F9
#define pinstViewActor_x                                           0xED444C
#define pinstWorldData_x                                           0xF860B0
#define pinstZoneAddr_x                                            0xDA2290
#define pinstPlayerPath_x                                          0xF90790
#define pinstTargetIndicator_x                                     0xF920C8
#define EQObject_Top_x                                             0xF86098
 
//// 
//Section 2:  UI Related Offsets 
//// 
#define pinstCAAWnd_x                                              0xED4490
#define pinstCAchievementsWnd_x                                    0xED4120
#define pinstCActionsWnd_x                                         0xED4420
#define pinstCAdvancedDisplayOptionsWindow_x                       0xED442C
#define pinstCAdvancedLootWnd_x                                    0xED4424
#define pinstCAdventureLeaderboardWnd_x                            0xF9F2F0
#define pinstCAdventureRequestWnd_x                                0xF9F3A0
#define pinstCAdventureStatsWnd_x                                  0xF9F450
#define pinstCAggroMeterWnd_x                                      0xED41A8
#define pinstCAlarmWnd_x                                           0xED4488
#define pinstCAlertHistoryWnd_x                                    0xED420C
#define pinstCAlertStackWnd_x                                      0xED41DC
#define pinstCAlertWnd_x                                           0xED41E0
#define pinstCAltStorageWnd_x                                      0xF9F7B0
#define pinstCAudioTriggersWindow_x                                0xEB6FF8
#define pinstCAuraWnd_x                                            0xED4468
#define pinstCAvaZoneWnd_x                                         0xED4108
#define pinstCBandolierWnd_x                                       0xED4478
#define pinstCBankWnd_x                                            0xED41E8
#define pinstCBarterMerchantWnd_x                                  0xFA09F0
#define pinstCBarterSearchWnd_x                                    0xFA0AA0
#define pinstCBarterWnd_x                                          0xFA0B50
#define pinstCBazaarConfirmationWnd_x                              0xED44A8
#define pinstCBazaarSearchWnd_x                                    0xED4130
#define pinstCBazaarWnd_x                                          0xED40E8
#define pinstCBlockedBuffWnd_x                                     0xED416C
#define pinstCBlockedPetBuffWnd_x                                  0xED4174
#define pinstCBodyTintWnd_x                                        0xED44BC
#define pinstCBookWnd_x                                            0xED4200
#define pinstCBreathWnd_x                                          0xED4494
#define pinstCBuffWindowNORMAL_x                                   0xED4164
#define pinstCBuffWindowSHORT_x                                    0xED4168
#define pinstCBugReportWnd_x                                       0xED411C
#define pinstCButtonWnd_x                                          0x1613C48
#define pinstCCastingWnd_x                                         0xED41A4
#define pinstCCastSpellWnd_x                                       0xED41B4
//#define pinstCCharacterCreationWnd_x                             0xDA8EBC
#define pinstCCharacterListWnd_x                                   0xED4148
#define pinstCChatWindowManager_x                                  0xFA15F8
#define pinstCClaimWnd_x                                           0xFA1750
#define pinstCColorPickerWnd_x                                     0xED415C
#define pinstCCombatAbilityWnd_x                                   0xED4438
#define pinstCCombatSkillsSelectWnd_x                              0xED443C
#define pinstCCompassWnd_x                                         0xED446C
#define pinstCConfirmationDialog_x                                 0xFA6618
#define pinstCContainerMgr_x                                       0xED449C
#define pinstCContextMenuManager_x                                 0x1613998
#define pinstCCursorAttachment_x                                   0xED419C
#define pinstCDynamicZoneWnd_x                                     0xFA1D18
#define pinstCEditLabelWnd_x                                       0xED40FC
#define pinstCEQMainWnd_x                                          0xFA1F60
#define pinstCEventCalendarWnd_x                                   0xED448C
#define pinstCExtendedTargetWnd_x                                  0xED41A0
#define pinstCPlayerCustomizationWnd_x                             0xED414C
#define pinstCFactionWnd_x                                         0xED41B0
#define pinstCFellowshipWnd_x                                      0xFA2160
#define pinstCFileSelectionWnd_x                                   0xED4444
#define pinstCFindItemWnd_x                                        0xED44C8
#define pinstCFindLocationWnd_x                                    0xFA22B8
#define pinstCFriendsWnd_x                                         0xED4440
#define pinstCGemsGameWnd_x                                        0xED4480
#define pinstCGiveWnd_x                                            0xED40F0
#define pinstCGroupSearchFiltersWnd_x                              0xED417C
#define pinstCGroupSearchWnd_x                                     0xFA26B0
#define pinstCGroupWnd_x                                           0xFA2760
#define pinstCGuildBankWnd_x                                       0xFA2810
#define pinstCGuildCreationWnd_x                                   0xFA28C0
#define pinstCGuildMgmtWnd_x                                       0xFA2970
#define pinstCharacterCreation_x                                   0xED4198
#define pinstCHelpWnd_x                                            0xED41D8
#define pinstCHeritageSelectionWnd_x                               0xED4150
#define pinstCHotButtonWnd_x                                       0xFA4AC8
#define pinstCHotButtonWnd1_x                                      0xFA4AC8
#define pinstCHotButtonWnd2_x                                      0xFA4ACC
#define pinstCHotButtonWnd3_x                                      0xFA4AD0
#define pinstCHotButtonWnd4_x                                      0xFA4AD4
#define pinstCIconSelectionWnd_x                                   0xED4118
#define pinstCInspectWnd_x                                         0xED4110
#define pinstCInventoryWnd_x                                       0xED41D4
#define pinstCInvSlotMgr_x                                         0xED4498
#define pinstCItemDisplayManager_x                                 0xFA5020
#define pinstCItemExpTransferWnd_x                                 0xFA5154
#define pinstCItemOverflowWnd_x                                    0xED40D0
#define pinstCJournalCatWnd_x                                      0xED44AC
//these are the same should probably rename to pinstCJournalNPCWnd at some point
#define pinstCJournalNPCWnd_x                                      0xED44A4
#define pinstCJournalTextWnd_x                                     0xED44A4
#define pinstCKeyRingWnd_x                                         0xED41E4
#define pinstCLargeDialogWnd_x                                     0xFA7298
#define pinstCLayoutCopyWnd_x                                      0xFA54A0
#define pinstCLFGuildWnd_x                                         0xFA5550
#define pinstCLoadskinWnd_x                                        0xED4484
#define pinstCLootFiltersCopyWnd_x                                 0xED3538
#define pinstCLootFiltersWnd_x                                     0xED44B0
#define pinstCLootSettingsWnd_x                                    0xED44B4
#define pinstCLootWnd_x                                            0xED4214
#define pinstCMailAddressBookWnd_x                                 0xED4140
#define pinstCMailCompositionWnd_x                                 0xED413C
#define pinstCMailIgnoreListWnd_x                                  0xED4144
#define pinstCMailWnd_x                                            0xED4138
#define pinstCManageLootWnd_x                                      0xED5720
#define pinstCMapToolbarWnd_x                                      0xED40F4
#define pinstCMapViewWnd_x                                         0xED40EC
#define pinstCMarketplaceWnd_x                                     0xED40D4
#define pinstCMerchantWnd_x                                        0xED40CC
#define pinstCMIZoneSelectWnd_x                                    0xFA5D88
#define pinstCMusicPlayerWnd_x                                     0xED447C
#define pinstCNameChangeMercWnd_x                                  0xED41CC
#define pinstCNameChangePetWnd_x                                   0xED41C8
#define pinstCNameChangeWnd_x                                      0xED4128
#define pinstCNoteWnd_x                                            0xED41D0
#define pinstCObjectPreviewWnd_x                                   0xED4134
#define pinstCOptionsWnd_x                                         0xED4160
#define pinstCOverseerWnd_x                                        0xED40C8
#define pinstCPetInfoWnd_x                                         0xED4418
#define pinstCPetitionQWnd_x                                       0xED4184
#define pinstCPlayerNotesWnd_x                                     0xED4474
#define pinstCPlayerWnd_x                                          0xED44CC
#define pinstCPopupWndManager_x                                    0xFA6618
#define pinstCProgressionSelectionWnd_x                            0xFA66C8
#define pinstCPurchaseGroupWnd_x                                   0xED40E0
#define pinstCPurchaseWnd_x                                        0xED40DC
#define pinstCPvPLeaderboardWnd_x                                  0xFA6778
#define pinstCPvPStatsWnd_x                                        0xFA6828
#define pinstCQuantityWnd_x                                        0xED41FC
#define pinstCRaceChangeWnd_x                                      0xED412C
#define pinstCRaidOptionsWnd_x                                     0xED41AC
#define pinstCRaidWnd_x                                            0xED41B8
#define pinstCRealEstateItemsWnd_x                                 0xED4158
#define pinstCRealEstateLayoutDetailsWnd_x                         0xED4194
#define pinstCRealEstateManageWnd_x                                0xED4180
#define pinstCRealEstateNeighborhoodWnd_x                          0xED4188
#define pinstCRealEstatePlotSearchWnd_x                            0xED418C
#define pinstCRealEstatePurchaseWnd_x                              0xED4190
#define pinstCRespawnWnd_x                                         0xED4470
#define pinstCRewardSelectionWnd_x                                 0xFA6F70
#define pinstCSelectorWnd_x                                        0xED40E4
#define pinstCSendMoneyWnd_x                                       0xED40F8
#define pinstCServerListWnd_x                                      0xED4448
#define pinstCSkillsSelectWnd_x                                    0xED4430
#define pinstCSkillsWnd_x                                          0xED4428
#define pinstCSocialEditWnd_x                                      0xED4114
#define pinstCSocialWnd_x                                          0xED44A0
#define pinstCSpellBookWnd_x                                       0xED41C4
#define pinstCStoryWnd_x                                           0xED44B8
#define pinstCTargetOfTargetWnd_x                                  0xFA85D0
#define pinstCTargetWnd_x                                          0xED410C
#define pinstCTaskOverlayWnd_x                                     0xED44C0
#define pinstCTaskSelectWnd_x                                      0xFA8728
#define pinstCTaskManager_x                                        0xC5D268
#define pinstCTaskTemplateSelectWnd_x                              0xFA87D8
#define pinstCTaskWnd_x                                            0xFA8888
#define pinstCTextEntryWnd_x                                       0xED4434
#define pinstCTimeLeftWnd_x                                        0xED4178
#define pinstCTipWndCONTEXT_x                                      0xFA8A8C
#define pinstCTipWndOFDAY_x                                        0xFA8A88
#define pinstCTitleWnd_x                                           0xFA8B38
#define pinstCTrackingWnd_x                                        0xED4100
#define pinstCTradeskillWnd_x                                      0xFA8CA0
#define pinstCTradeWnd_x                                           0xED40D8
#define pinstCTrainWnd_x                                           0xED441C
#define pinstCTributeBenefitWnd_x                                  0xFA8EA0
#define pinstCTributeMasterWnd_x                                   0xFA8F50
#define pinstCTributeTrophyWnd_x                                   0xFA9000
#define pinstCVideoModesWnd_x                                      0xED4124
#define pinstCVoiceMacroWnd_x                                      0xF924E0
#define pinstCVoteResultsWnd_x                                     0xED41C0
#define pinstCVoteWnd_x                                            0xED41BC
#define pinstCZoneGuideWnd_x                                       0xED41F8
#define pinstCZonePathWnd_x                                        0xED4204

#define pinstEQSuiteTextureLoader_x                                0xEA1D00
#define pinstItemIconCache_x                                       0xFA1F18
#define pinstLootFiltersManager_x                                  0xED35E8
#define pinstRewardSelectionWnd_x                                  0xFA6F70

//// 
// Section 3: Miscellaneous Offsets 
////
#define __CastRay_x                                                0x5DCE00
//it has no refs but we can possibly call it still 
#define __CastRay2_x                                               0x5DD090
#define __ConvertItemTags_x                                        0x5FA100
#define __CleanItemTags_x                                          0x47DA80
#define __DoesFileExist_x                                          0x948850
#define __EQGetTime_x                                              0x945530
#define __ExecuteCmd_x                                             0x5D52B0
#define __FixHeading_x                                             0x9E1DB0
#define __FlushDxKeyboard_x                                        0x6D9630
#define __GameLoop_x                                               0x6DCF30
#define __get_bearing_x                                            0x5DC9A0
#define __get_melee_range_x                                        0x5DD2D0
#define __GetAnimationCache_x                                      0x74BD00
#define __GetGaugeValueFromEQ_x                                    0x851CA0
#define __GetLabelFromEQ_x                                         0x8537E0
#define __GetXTargetType_x                                         0x9E4120
#define __HandleMouseWheel_x                                       0x6DE3C0
#define __HeadingDiff_x                                            0x9E1E10
#define __HelpPath_x                                               0xF8DCFC
#define __ExecuteFrontEnd_x                                        0x6D9E10
#define __NewUIINI_x                                               0x851970
#define __ProcessGameEvents_x                                      0x643200
#define __ProcessMouseEvent_x                                      0x642900
#define __SaveColors_x                                             0x5711D0
#define __STMLToText_x                                             0x97FB40
#define __ToggleKeyRingItem_x                                      0x52A930
#define CMemoryMappedFile__SetFile_x                               0xAD2550
#define CrashDetected_x                                            0x6DBB40
#define DrawNetStatus_x                                            0x6726A0
#define Expansion_HoT_x                                            0xDA30E0
#define Teleport_Table_Size_x                                      0xF884E0
#define Teleport_Table_x                                           0xF860B8
#define Util__FastTime_x                                           0x9450F0
#define __CopyLayout_x                                             0x65F3D0
#define __WndProc_x                                                0x6DC040
#define __ProcessKeyboardEvent_x                                   0x6DB580

//// 
// Section 4: Function Offsets 
//// 
// CAdvancedLootWnd
#define CAdvancedLootWnd__CAdvancedLootWnd_x                       0x4919C0
#define CAdvancedLootWnd__DoAdvLootAction_x                        0x49B1B0
#define CAdvancedLootWnd__DoSharedAdvLootAction_x                  0x49B030
#define CAdvancedLootWnd__AddPlayerToList_x                        0x495710
#define CAdvancedLootWnd__UpdateMasterLooter_x                     0x494950

// AltAdvManager 
#define AltAdvManager__GetCalculatedTimer_x                        0x57A1E0
#define AltAdvManager__IsAbilityReady_x                            0x578DD0
#define AltAdvManager__GetAAById_x                                 0x579170
#define AltAdvManager__CanTrainAbility_x                           0x5791E0
#define AltAdvManager__CanSeeAbility_x                             0x579570

// CharacterZoneClient
#define CharacterZoneClient__CharacterZoneClient_x                 0x4D1210
#define CharacterZoneClient__HasSkill_x                            0x4DC980
#define CharacterZoneClient__MakeMeVisible_x                       0x4DE0C0
#define CharacterZoneClient__IsStackBlocked_x                      0x4C8640
#define CharacterZoneClient__CanUseMemorizedSpellSlot_x            0x4C0E00
#define CharacterZoneClient__GetItemCountWorn_x                    0x4E0FC0
#define CharacterZoneClient__GetItemCountInInventory_x             0x4E10C0
#define CharacterZoneClient__GetCursorItemCount_x                  0x4E11C0
#define CharacterZoneClient__FindAffectSlot_x                      0x4CA880
#define CharacterZoneClient__BardCastBard_x                        0x4CD8A0
#define CharacterZoneClient__GetMaxEffects_x                       0x4C4D40
#define CharacterZoneClient__GetEffect_x                           0x4C0D40
#define CharacterZoneClient__GetOpenEffectSlot_x                   0x4CBE90
#define CharacterZoneClient__GetFirstEffectSlot_x                  0x4CBF40
#define CharacterZoneClient__GetLastEffectSlot_x                   0x4CBFE0
#define CharacterZoneClient__CalcAffectChange_x                    0x4CC1A0
#define CharacterZoneClient__CalcAffectChangeGeneric_x             0x4CC380
#define CharacterZoneClient__GetFocusReuseMod_x                    0x4B8610
#define CharacterZoneClient__FindItemByGuid_x                      0x4DF260
#define CharacterZoneClient__FindItemByRecord_x                    0x4DEBB0

// CBankWnd 
#define CBankWnd__GetNumBankSlots_x                                0x7070D0
#define CBankWnd__WndNotification_x                                0x706E70

//CBarterWnd
#define CBarterWnd__WndNotification_x                              0x711AE0

//CBarterSearchWnd
#define CBarterSearchWnd__WndNotification_x                        0x70C740
#define CBarterSearchWnd__UpdateInventoryList_x                    0x70A710

// CBazaarSearchWnd 
#define CBazaarSearchWnd__HandleBazaarMsg_x                        0x716150

// CButtonWnd 
#define CButtonWnd__SetCheck_x                                     0x97D0E0
#define CButtonWnd__CButtonWnd_x                                   0x97BA40

// CChatManager 
#define CChatManager__GetRGBAFromIndex_x                           0x739460
#define CChatManager__InitContextMenu_x                            0x732330
#define CChatManager__FreeChatWindow_x                             0x738020
#define CChatManager__SetLockedActiveChatWindow_x                  0x739140
#define CChatManager__CreateChatWindow_x                           0x738650

//ChatManagerClient
#define ChatManagerClient__Instance_x                              0x4F2040

// CContextMenu 
#define CContextMenu__CContextMenu_x                               0x992F00
#define CContextMenu__dCContextMenu_x                              0x993130
#define CContextMenu__AddMenuItem_x                                0x993140
#define CContextMenu__RemoveMenuItem_x                             0x993450
#define CContextMenu__RemoveAllMenuItems_x                         0x993470
#define CContextMenu__CheckMenuItem_x                              0x9934D0
#define CContextMenu__SetMenuItem_x                                0x993370
#define CContextMenu__AddSeparator_x                               0x9932D0

//CContextMenuManager
#define CContextMenuManager__AddMenu_x                             0x993A60
#define CContextMenuManager__RemoveMenu_x                          0x993AD0
#define CContextMenuManager__PopupMenu_x                           0x993B90
#define CContextMenuManager__Flush_x                               0x993A00
#define CContextMenuManager__GetMenu_x                             0x49D4E0
#define CContextMenuManager__CreateDefaultMenu_x                   0x745CB0

// CChatService
#define CChatService__GetNumberOfFriends_x                         0x91FC50
#define CChatService__GetFriendName_x                              0x91FC60

// CChatWindow 
#define CChatWindow__CChatWindow_x                                 0x739DC0
#define CChatWindow__Clear_x                                       0x73B220
#define CChatWindow__WndNotification_x                             0x73B9B0
#define CChatWindow__AddHistory_x                                  0x73AA80

// CComboWnd 
#define CComboWnd__DeleteAll_x                                     0x98FFD0
#define CComboWnd__Draw_x                                          0x98F470
#define CComboWnd__GetCurChoice_x                                  0x98FDA0
#define CComboWnd__GetListRect_x                                   0x98F920
#define CComboWnd__GetTextRect_x                                   0x990040
#define CComboWnd__InsertChoice_x                                  0x98FAB0
#define CComboWnd__SetColors_x                                     0x98FA80
#define CComboWnd__SetChoice_x                                     0x98FD80
#define CComboWnd__GetItemCount_x                                  0x98FDB0
#define CComboWnd__GetCurChoiceText_x                              0x98FDE0
#define CComboWnd__GetChoiceText_x                                 0x98FDC0
#define CComboWnd__InsertChoiceAtIndex_x                           0x98FB40

// CContainerWnd 
#define CContainerWnd__HandleCombine_x                             0x743340
#define CContainerWnd__vftable_x                                   0xB4F104
#define CContainerWnd__SetContainer_x                              0x744B70

// CDisplay
#define CDisplay__ZoneMainUI_x                                     0x56BDA0
#define CDisplay__PreZoneMainUI_x                                  0x56BDB0
#define CDisplay__CleanGameUI_x                                    0x570FB0
#define CDisplay__GetClickedActor_x                                0x563C80
#define CDisplay__GetUserDefinedColor_x                            0x55B9F0
//well they inlined it in jan 25 2021 test but the function is still left in exe so for now we can probably just call it...
#define CDisplay__GetWorldFilePath_x                               0x565790
#define CDisplay__is3dON_x                                         0x560510
#define CDisplay__ReloadUI_x                                       0x56B0C0
#define CDisplay__WriteTextHD2_x                                   0x560300
#define CDisplay__TrueDistance_x                                   0x567660
#define CDisplay__SetViewActor_x                                   0x5635A0
#define CDisplay__GetFloorHeight_x                                 0x5605D0
#define CDisplay__SetRenderWindow_x                                0x55EF50
#define CDisplay__ToggleScreenshotMode_x                           0x563070

// CEditBaseWnd 
#define CEditBaseWnd__SetSel_x                                     0x9B55E0

// CEditWnd 
#define CEditWnd__DrawCaret_x                                      0x9969D0
#define CEditWnd__EnsureCaretVisible_x                             0x998D50
#define CEditWnd__GetCaretPt_x                                     0x997BB0
#define CEditWnd__GetCharIndexPt_x                                 0x997960
#define CEditWnd__GetDisplayString_x                               0x997800
#define CEditWnd__GetHorzOffset_x                                  0x995F50
#define CEditWnd__GetLineForPrintableChar_x                        0x998C60
#define CEditWnd__GetSelStartPt_x                                  0x997C10
#define CEditWnd__GetSTMLSafeText_x                                0x997610
#define CEditWnd__PointFromPrintableChar_x                         0x9988A0
#define CEditWnd__SelectableCharFromPoint_x                        0x998A00
#define CEditWnd__SetEditable_x                                    0x997CE0
#define CEditWnd__SetWindowTextA_x                                 0x997360
#define CEditWnd__ReplaceSelection_x                               0x998460
#define CEditWnd__ReplaceSelection1_x                              0x9983E0

// CEverQuest 
#define CEverQuest__DoPercentConvert_x                             0x62EB90
#define CEverQuest__ClickedPlayer_x                                0x620180
#define CEverQuest__CreateTargetIndicator_x                        0x640170
#define CEverQuest__DeleteTargetIndicator_x                        0x640200
#define CEverQuest__DoTellWindow_x                                 0x4F2140
#define CEverQuest__OutputTextToLog_x                              0x4F2410
#define CEverQuest__DropHeldItemOnGround_x                         0x615170
#define CEverQuest__dsp_chat_x                                     0x4F27A0
#define CEverQuest__trimName_x                                     0x63B970
#define CEverQuest__Emote_x                                        0x62F250
#define CEverQuest__EnterZone_x                                    0x628F90
#define CEverQuest__GetBodyTypeDesc_x                              0x6346B0
#define CEverQuest__GetClassDesc_x                                 0x634CF0
#define CEverQuest__GetClassThreeLetterCode_x                      0x6352F0
#define CEverQuest__GetDeityDesc_x                                 0x63E920
#define CEverQuest__GetLangDesc_x                                  0x6354B0
#define CEverQuest__GetRaceDesc_x                                  0x634CD0
#define CEverQuest__InterpretCmd_x                                 0x63EF90
#define CEverQuest__LeftClickedOnPlayer_x                          0x6196F0
#define CEverQuest__LMouseUp_x                                     0x617720
#define CEverQuest__RightClickedOnPlayer_x                         0x61A2E0
#define CEverQuest__RMouseUp_x                                     0x6189E0
#define CEverQuest__SetGameState_x                                 0x614EF0
#define CEverQuest__UPCNotificationFlush_x                         0x63B890
#define CEverQuest__IssuePetCommand_x                              0x636AB0
#define CEverQuest__ReportSuccessfulHit_x                          0x630B60

// CGaugeWnd 
//not sure, need to call it to see if its correct CGaugeWnd__CalcFillRect_x
#define CGaugeWnd__CalcFillRect_x                                  0x756C80
#define CGaugeWnd__CalcLinesFillRect_x                             0x756CE0
#define CGaugeWnd__Draw_x                                          0x756290

// CGuild
#define CGuild__FindMemberByName_x                                 0x4B4430
#define CGuild__GetGuildName_x                                     0x4B2C50
#define CGuild__GetGuildIndex_x                                    0x4B3370

// CHotButtonWnd 
#define CHotButtonWnd__DoHotButton_x                               0x774140

//CHotButton
#define CHotButton__SetCheck_x                                     0x653800
#define CHotButton__SetButtonSize_x                                0x653BC0

// CInvSlotMgr 
#define CInvSlotMgr__FindInvSlot_x                                 0x781170
#define CInvSlotMgr__MoveItem_x                                    0x77FD10
#define CInvSlotMgr__SelectSlot_x                                  0x781230

// CInvSLot
#define CInvSlot__HandleRButtonUp_x                                0x77E560
#define CInvSlot__SliderComplete_x                                 0x77BA40
#define CInvSlot__GetItemBase_x                                    0x77B300
#define CInvSlot__UpdateItem_x                                     0x77B4F0

// CInvSlotWnd
#define CInvSlotWnd__DrawTooltip_x                                 0x782E80
#define CInvSlotWnd__CInvSlotWnd_x                                 0x782060
#define CInvSlotWnd__HandleLButtonUp_x                             0x782A00

// CItemDisplayWnd 
#define CItemDisplayWnd__SetSpell_x                                0x84BFB0
#define CItemDisplayWnd__UpdateStrings_x                           0x791F10
#define CItemDisplayWnd__InsertAugmentRequest_x                    0x78B8D0
#define CItemDisplayWnd__RemoveAugmentRequest_x                    0x78BE50
//only 1 arg now? need to check
#define CItemDisplayWnd__SetItem_x                                 0x792510
#define CItemDisplayWnd__AboutToShow_x                             0x791B60
#define CItemDisplayWnd__WndNotification_x                         0x793A90
#define CItemDisplayWnd__RequestConvertItem_x                      0x793340
#define CItemDisplayWnd__CItemDisplayWnd_x                         0x790B80
#define CItemDisplayWnd__dCItemDisplayWnd_x                        0x791980

//CWndDisplayManager
#define CWndDisplayManager__FindWindowA_x                          0x881240

//CItemDisplayManager
#define CItemDisplayManager__CreateWindowInstance_x                0x7983F0
#define CItemDisplayManager__ShowItem_x                            0x797990

// CLabel 
#define CLabel__UpdateText_x                                       0x79EB10

// CListWnd
#define CListWnd__CListWnd_x                                       0x963A40
#define CListWnd__dCListWnd_x                                      0x963D40
#define CListWnd__AddColumn_x                                      0x968790
#define CListWnd__AddColumn1_x                                     0x9688B0
#define CListWnd__AddLine_x                                        0x968C20
#define CListWnd__AddString_x                                      0x968A20
#define CListWnd__CalculateFirstVisibleLine_x                      0x968540
#define CListWnd__CalculateVSBRange_x                              0x968320
#define CListWnd__ClearSel_x                                       0x969510
#define CListWnd__ClearAllSel_x                                    0x969560
#define CListWnd__CloseAndUpdateEditWindow_x                       0x96A010
#define CListWnd__Compare_x                                        0x967C60
#define CListWnd__Draw_x                                           0x963F00
#define CListWnd__DrawColumnSeparators_x                           0x966A50
#define CListWnd__DrawHeader_x                                     0x966EB0
#define CListWnd__DrawItem_x                                       0x967500
#define CListWnd__DrawLine_x                                       0x966BC0
#define CListWnd__DrawSeparator_x                                  0x966AF0
#define CListWnd__EnableLine_x                                     0x966300
#define CListWnd__EnsureVisible_x                                  0x969F30
//no references in jan 25 2021 test exe we can probably still call it
#define CListWnd__ExtendSel_x                                      0x969450
#define CListWnd__GetColumnTooltip_x                               0x965E80
#define CListWnd__GetColumnMinWidth_x                              0x965EF0
#define CListWnd__GetColumnWidth_x                                 0x965E00
#define CListWnd__GetCurSel_x                                      0x9657A0
#define CListWnd__GetItemAtPoint_x                                 0x966580
//no references in jan 25 2021 test exe we can probably still call it
#define CListWnd__GetItemAtPoint1_x                                0x9665F0
#define CListWnd__GetItemColor_x                                   0x965B20
#define CListWnd__GetItemData_x                                    0x965820
#define CListWnd__GetItemHeight_x                                  0x965BD0
#define CListWnd__GetItemIcon_x                                    0x9659A0
#define CListWnd__GetItemRect_x                                    0x9663F0
#define CListWnd__GetItemText_x                                    0x965860
#define CListWnd__GetSelList_x                                     0x9695B0
#define CListWnd__GetSeparatorRect_x                               0x966860
#define CListWnd__InsertLine_x                                     0x969080
#define CListWnd__RemoveLine_x                                     0x9692A0
#define CListWnd__SetColors_x                                      0x968300
#define CListWnd__SetColumnJustification_x                         0x968030
#define CListWnd__SetColumnLabel_x                                 0x9689C0
#define CListWnd__SetColumnWidth_x                                 0x967F40
#define CListWnd__SetCurSel_x                                      0x9693A0
#define CListWnd__SetItemColor_x                                   0x969BF0
#define CListWnd__SetItemData_x                                    0x969BB0
#define CListWnd__SetItemText_x                                    0x9697D0
#define CListWnd__ShiftColumnSeparator_x                           0x9680F0
#define CListWnd__Sort_x                                           0x967DF0
#define CListWnd__ToggleSel_x                                      0x9693D0
#define CListWnd__SetColumnsSizable_x                              0x968190
#define CListWnd__SetItemWnd_x                                     0x969A70
#define CListWnd__GetItemWnd_x                                     0x9659F0
#define CListWnd__SetItemIcon_x                                    0x969850
#define CListWnd__CalculateCustomWindowPositions_x                 0x968640
#define CListWnd__SetVScrollPos_x                                  0x967F20

// CMapViewWnd 
#define CMapViewWnd__CMapViewWnd_x                                 0x7B5F60
#define CMapViewWnd__GetWorldCoordinates_x                         0x7B4580
#define CMapViewWnd__HandleLButtonDown_x                           0x7B1410
#define CMapViewWnd__WndNotification_x                             0x7B8840

// CMerchantWnd 
#define CMerchantWnd__DisplayBuyOrSellPrice_x                      0x7D91B0
#define CMerchantWnd__PurchasePageHandler__RequestGetItem_x        0x7D9B10
#define CMerchantWnd__PurchasePageHandler__RequestPutItem_x        0x7DA160
#define CMerchantWnd__SelectRecoverySlot_x                         0x7DD330
#define CMerchantWnd__MerchantPageHandler__SelectBuySellSlot_x     0x7D7C40
#define CMerchantWnd__SelectBuySellSlot_x                          0x7E34D0
#define CMerchantWnd__PurchasePageHandler__UpdateList_x            0x7D8E00

// CPacketScrambler
#define CPacketScrambler__ntoh_x                                   0x8ECC40
#define CPacketScrambler__hton_x                                   0x8ECC30

// CSidlManagerbase we should rename at some point
#define CSidlManager__FindAnimation1_x                             0x9861D0
#define CSidlManager__FindScreenPieceTemplate_x                    0x9865A0
#define CSidlManager__FindScreenPieceTemplate1_x                   0x9863D0
#define CSidlManager__CreateXWndFromTemplate_x                     0x989A50
#define CSidlManager__CreateXWndFromTemplate1_x                    0x989CE0
#define CSidlManagerbase__CreateXWnd_x                             0x989D20

//inlined since jan 25 2021 test but they left the function intact
#define CSidlManager__CreateHotButtonWnd_x                         0x842110
#define CSidlManager__CreateLabel_x                                0x841CE0

//CSidlManager
#define CSidlManager__CreateXWnd_x                                 0x841760

// CSidlScreenWnd 
#define CSidlScreenWnd__CalculateHSBRange_x                        0x981ED0
#define CSidlScreenWnd__CalculateVSBRange_x                        0x981DD0
#define CSidlScreenWnd__ConvertToRes_x                             0x9AF830
#define CSidlScreenWnd__CreateChildrenFromSidl_x                   0x981750
#define CSidlScreenWnd__CSidlScreenWnd1_x                          0x981440
#define CSidlScreenWnd__CSidlScreenWnd2_x                          0x981510
#define CSidlScreenWnd__dCSidlScreenWnd_x                          0x9815E0
#define CSidlScreenWnd__DrawSidlPiece_x                            0x982790
#define CSidlScreenWnd__EnableIniStorage_x                         0x982C70
#define CSidlScreenWnd__GetSidlPiece_x                             0x982980
#define CSidlScreenWnd__Init1_x                                    0x980F10
#define CSidlScreenWnd__LoadIniInfo_x                              0x982CC0
#define CSidlScreenWnd__LoadIniListWnd_x                           0x9838C0
#define CSidlScreenWnd__LoadSidlScreen_x                           0x980310
#define CSidlScreenWnd__StoreIniInfo_x                             0x983430
#define CSidlScreenWnd__StoreIniVis_x                              0x9837B0
#define CSidlScreenWnd__WndNotification_x                          0x982660
#define CSidlScreenWnd__GetChildItem_x                             0x982BF0
#define CSidlScreenWnd__HandleLButtonUp_x                          0x971100
#define CSidlScreenWnd__m_layoutCopy_x                             0x1613868

// CSkillMgr
#define CSkillMgr__IsAvailable_x                                   0x6C1060
#define CSkillMgr__GetSkillCap_x                                   0x6C1230
#define CSkillMgr__GetNameToken_x                                  0x6C08A0
#define CSkillMgr__IsActivatedSkill_x                              0x6C0990
#define CSkillMgr__IsCombatSkill_x                                 0x6C0900

// CSliderWnd 
#define CSliderWnd__GetValue_x                                     0x994B30
#define CSliderWnd__SetValue_x                                     0x994960
#define CSliderWnd__SetNumTicks_x                                  0x9949C0

// CSpellBookWnd 
#define CSpellBookWnd__MemorizeSet_x                               0x848990

// CStmlWnd
#define CStmlWnd__AppendSTML_x                                     0x99DF30
#define CStmlWnd__ParseSTML_x                                      0x99F0F0
#define CStmlWnd__CalculateHSBRange_x                              0x99EEB0
#define CStmlWnd__CalculateVSBRange_x                              0x99EE20
#define CStmlWnd__CanBreakAtCharacter_x                            0x9A3D20
#define CStmlWnd__FastForwardToEndOfTag_x                          0x9A49C0
#define CStmlWnd__ForceParseNow_x                                  0x99E4A0
#define CStmlWnd__GetNextTagPiece_x                                0x9A3C80
#define CStmlWnd__GetVisibleText_x                                 0x99E4C0
#define CStmlWnd__InitializeWindowVariables_x                      0x9A4810
#define CStmlWnd__MakeStmlColorTag_x                               0x99D5D0
#define CStmlWnd__MakeWndNotificationTag_x                         0x99D640
#define CStmlWnd__SetSTMLText_x                                    0x99C3B0
#define CStmlWnd__StripFirstSTMLLines_x                            0x9A5BE0
#define CStmlWnd__UpdateHistoryString_x                            0x9A4BC0

// CTabWnd 
#define CTabWnd__Draw_x                                            0x99B300
#define CTabWnd__DrawCurrentPage_x                                 0x99BC90
#define CTabWnd__DrawTab_x                                         0x99B880
#define CTabWnd__GetCurrentPage_x                                  0x99AA60
#define CTabWnd__GetPageInnerRect_x                                0x99AC90
#define CTabWnd__GetTabInnerRect_x                                 0x99ABD0
#define CTabWnd__GetTabRect_x                                      0x99AA90
#define CTabWnd__InsertPage_x                                      0x99AE80
#define CTabWnd__RemovePage_x                                      0x99AFD0
#define CTabWnd__SetPage_x                                         0x99AD10
//inlined but we can probably call it jan 25 2021
#define CTabWnd__SetPageRect_x                                     0x99B200
#define CTabWnd__UpdatePage_x                                      0x99B670
#define CTabWnd__GetPageFromTabIndex_x                             0x99B7C0
#define CTabWnd__GetCurrentTabIndex_x                              0x99AA50

// CPageWnd
//inlined in Jan 25 2021 test
//#define CPageWnd__GetTabText_x                                     0x479340
#define CPageWnd__SetTabText_x                                     0x99A420
#define CPageWnd__FlashTab_x                                       0x99A480

// CTextOverlay 
#define CTextOverlay__DisplayText_x                                0x4AC4B0

// CTextureFont
#define CTextureFont__DrawWrappedText_x                            0x96D5A0
#define CTextureFont__GetTextExtent_x                              0x96D8A0

// CXMLDataManager 
#define CXMLDataManager__GetXMLData_x                              0x9AC2E0

// CXMLSOMDocumentBase 
#define CXMLSOMDocumentBase__XMLRead_x                             0x9594F0

// CXStr 
// WARNING:  Be sure that none of these offsets are identical! 
// 
// Note:  dCXStr, CXStr1, & CXStr3 can be found in the 'BookWindow' constructor. 
#define CXStr__CXStr_x                                             0x544350
#define CXStr__CXStr1_x                                            0x482750
#define CXStr__CXStr3_x                                            0x941480
#define CXStr__dCXStr_x                                            0x478F60
#define CXStr__operator_equal_x                                    0x9416C0
#define CXStr__operator_equal1_x                                   0x941700
#define CXStr__operator_plus_equal1_x                              0x942160
#define CXStr__SetString_x                                         0x944000
#define CXStr__operator_char_p_x                                   0x941BB0
#define CXStr__GetChar_x                                           0x943960
#define CXStr__Delete_x                                            0x943230
#define CXStr__GetUnicode_x                                        0x9439D0
#define CXStr__Insert_x                                            0x943A30
#define CXStr__FindNext_x                                          0x943680
#define CXStr__Copy_x                                              0x943040

// CXWnd
//CTileLayoutWnd__SetOriginalAutoStretchInfo_x is here because its where I lookup the actual CXWnd Size.
#define CTileLayoutWnd__SetOriginalAutoStretchInfo_x               0x992B60
#define CXWnd__BringToTop_x                                        0x974B80
#define CXWnd__ClrFocus_x                                          0x974500
#define CXWnd__Destroy_x                                           0x9745B0
#define CXWnd__DoAllDrawing_x                                      0x970760
//inlined in jan 25 2021 we can probably still call it
#define CXWnd__DrawChildren_x                                      0x970730
#define CXWnd__DrawColoredRect_x                                   0x970D00
#define CXWnd__DrawTooltip_x                                       0x96ECF0
#define CXWnd__DrawTooltipAtPoint_x                                0x96EDB0
#define CXWnd__GetBorderFrame_x                                    0x9709A0
#define CXWnd__GetChildWndAt_x                                     0x974C20
#define CXWnd__GetClientClipRect_x                                 0x972D90
#define CXWnd__GetScreenClipRect_x                                 0x972E40
#define CXWnd__GetScreenRect_x                                     0x972FC0
#define CXWnd__GetRelativeRect_x                                   0x973080
#define CXWnd__GetTooltipRect_x                                    0x970D50
#define CXWnd__GetWindowTextA_x                                    0x4F1FE0
#define CXWnd__IsActive_x                                          0x971480
#define CXWnd__IsDescendantOf_x                                    0x973A30
#define CXWnd__IsReallyVisible_x                                   0x973A60
#define CXWnd__IsType_x                                            0x9753B0
#define CXWnd__Move_x                                              0x973AC0
#define CXWnd__Move1_x                                             0x973BC0
#define CXWnd__ProcessTransition_x                                 0x974690
#define CXWnd__Refade_x                                            0x973E90
#define CXWnd__Resize_x                                            0x974120
#define CXWnd__Right_x                                             0x974970
#define CXWnd__SetFocus_x                                          0x9744C0
#define CXWnd__SetFont_x                                           0x974530
#define CXWnd__SetKeyTooltip_x                                     0x975170
#define CXWnd__SetMouseOver_x                                      0x971E50
#define CXWnd__StartFade_x                                         0x973910
#define CXWnd__GetChildItem_x                                      0x974DA0
#define CXWnd__SetParent_x                                         0x973750
#define CXWnd__Minimize_x                                          0x974190

// CScreenPieceTemplate
#define CScreenPieceTemplate__IsType_x                             0x9B0880

// CXWndManager 
#define CXWndManager__DrawCursor_x                                 0x977C30
#define CXWndManager__DrawWindows_x                                0x977D80
#define CXWndManager__GetKeyboardFlags_x                           0x97A650
#define CXWndManager__HandleKeyboardMsg_x                          0x97A230
#define CXWndManager__RemoveWnd_x                                  0x97A920
#define CXWndManager__RemovePendingDeletionWnd_x                   0x97ADE0

// CDBStr
#define CDBStr__GetString_x                                        0x55A4F0

// EQ_Character 
#define EQ_Character__CastSpell_x                                  0x4C56C0
#define EQ_Character__Cur_HP_x                                     0x4D95F0
#define EQ_Character__Cur_Mana_x                                   0x4E16F0
#define EQ_Character__GetCastingTimeModifier_x                     0x4C8D30
#define EQ_Character__GetFocusCastingTimeModifier_x                0x4B8220
#define EQ_Character__GetFocusRangeModifier_x                      0x4B8370
#define EQ_Character__GetHPRegen_x                                 0x4E80F0
#define EQ_Character__GetEnduranceRegen_x                          0x4E86B0
#define EQ_Character__GetManaRegen_x                               0x4E8AF0
#define EQ_Character__Max_Endurance_x                              0x6821F0
#define EQ_Character__Max_HP_x                                     0x4D9420
#define EQ_Character__Max_Mana_x                                   0x681FE0
#define EQ_Character__doCombatAbility_x                            0x684B20
#define EQ_Character__UseSkill_x                                   0x4EAAF0
#define EQ_Character__GetConLevel_x                                0x67A300
#define EQ_Character__IsExpansionFlag_x                            0x5D3B10
#define EQ_Character__TotalEffect_x                                0x4CD1B0
#define EQ_Character__GetPCSpellAffect_x                           0x4C9B60
#define EQ_Character__SpellDuration_x                              0x4C95A0
#define EQ_Character__MySpellDuration_x                            0x4B68E0
#define EQ_Character__GetAdjustedSkill_x                           0x4DC740
#define EQ_Character__GetBaseSkill_x                               0x4DD6E0
#define EQ_Character__CanUseItem_x                                 0x4E1A20
#define EQ_Character__CanMedOnHorse_x                              0x4EA630

//ProfileManager
#define ProfileManager__GetCurrentProfile_x                        0x90D0F0

//PlayerClient (to us known as EQPlayer)
#define PlayerClient__GetPcClient_x                                0x699C30

//PcClient
#define PcClient__vftable_x                                        0xB42C5C
#define PcClient__PcClient_x                                       0x677560

//CCharacterListWnd
#define CCharacterListWnd__SelectCharacter_x                       0x4BFCD0
#define CCharacterListWnd__EnterWorld_x                            0x4BF6A0
#define CCharacterListWnd__Quit_x                                  0x4BF3C0
#define CCharacterListWnd__UpdateList_x                            0x4BF890

// EQ_Item (ItemClient)
#define EQ_Item__CanDrop_x                                         0x6599E0
#define EQ_Item__CreateItemTagString_x                             0x8E5CA0
#define EQ_Item__IsStackable_x                                     0x8EACA0
#define EQ_Item__GetImageNum_x                                     0x8E7970
#define EQ_Item__CreateItemClient_x                                0x658990
#define EQ_Item__GetItemValue_x                                    0x8E8C70
#define EQ_Item__ValueSellMerchant_x                               0x8EC970
#define EQ_Item__IsKeyRingItem_x                                   0x8EA490
#define EQ_Item__CanGoInBag_x                                      0x659B00
#define EQ_Item__IsEmpty_x                                         0x8E9F40
#define EQ_Item__GetMaxItemCount_x                                 0x8E9070
#define EQ_Item__GetHeldItem_x                                     0x8E7830
#define EQ_Item__CanGemFitInSlot_x                                 0x8E54A0

// EQ_LoadingS 
#define EQ_LoadingS__SetProgressBar_x                              0x57AFE0
#define EQ_LoadingS__Array_x                                       0xD8FD00

// EQ_PC 
#define EQ_PC__DestroyHeldItemOrMoney_x                            0x682CE0
#define EQ_PC__GetAlternateAbilityId_x                             0x8F69B0
#define EQ_PC__GetCombatAbility_x                                  0x8F6F30
#define EQ_PC__GetCombatAbilityTimer_x                             0x8F6FA0
#define EQ_PC__GetItemRecastTimer_x                                0x685120
#define EQ_PC__HasLoreItem_x                                       0x67ACB0
#define EQ_PC__AlertInventoryChanged_x                             0x679BB0
#define EQ_PC__GetPcZoneClient_x                                   0x6AA320
#define EQ_PC__RemoveMyAffect_x                                    0x688640
#define EQ_PC__GetKeyRingItems_x                                   0x8F7A30
#define EQ_PC__GetItemContainedRealEstateIds_x                     0x8F7590
#define EQ_PC__GetNonArchivedOwnedRealEstates_x                    0x8F7B80

// EQItemList 
#define EQItemList__EQItemList_x                                   0x5D9EA0
#define EQItemList__add_object_x                                   0x60A000
#define EQItemList__add_item_x                                     0x5DA480
#define EQItemList__delete_item_x                                  0x5DA4D0
#define EQItemList__FreeItemList_x                                 0x5DA3E0

// EQMisc
#define EQMisc__GetActiveFavorCost_x                               0x556620

// EQPlayer 
#define EQPlayer__ChangeBoneStringSprite_x                         0x69B660
#define EQPlayer__dEQPlayer_x                                      0x68DF00
#define EQPlayer__DoAttack_x                                       0x6A4060
#define EQPlayer__EQPlayer_x                                       0x68E750
#define EQPlayer__SetNameSpriteState_x                             0x692D10
#define EQPlayer__SetNameSpriteTint_x                              0x693BE0
#define PlayerBase__HasProperty_j_x                                0x9E0170
#define EQPlayer__IsTargetable_x                                   0x9E06D0
#define EQPlayer__CanSee_x                                         0x9E04C0
#define EQPlayer__CanSee1_x                                        0x9E0590
#define PlayerBase__GetVisibilityLineSegment_x                     0x9E0230

//PlayerZoneClient
#define PlayerZoneClient__ChangeHeight_x                           0x6A7E20
#define PlayerZoneClient__GetLevel_x                               0x6AA360
#define PlayerZoneClient__IsValidTeleport_x                        0x60B4A0
#define PlayerZoneClient__LegalPlayerRace_x                        0x572F90

//EQPlayerManager
#define EQPlayerManager__GetSpawnByID_x                            0x69E810
#define EQPlayerManager__GetSpawnByName_x                          0x69E8C0
#define EQPlayerManager__GetPlayerFromPartialName_x                0x69E950

// KeyPressHandler
#define KeypressHandler__Get_x                                     0x65D380
#define KeypressHandler__AttachAltKeyToEqCommand_x                 0x65D450
#define KeypressHandler__AttachKeyToEqCommand_x                    0x65D490
#define KeypressHandler__ClearCommandStateArray_x                  0x65E950
#define KeypressHandler__HandleKeyDown_x                           0x65E970
#define KeypressHandler__HandleKeyUp_x                             0x65EA10
#define KeypressHandler__SaveKeymapping_x                          0x65EFC0

// MapViewMap 
#define MapViewMap__Clear_x                                        0x7B1C10
#define MapViewMap__SaveEx_x                                       0x7B514F
#define MapViewMap__SetZoom_x                                      0x7BAD90

// PlayerPointManager
#define PlayerPointManager__GetAltCurrency_x                       0x90AF80

// StringTable 
#define StringTable__getString_x                                   0x905E50

// PcZoneClient
#define PcZoneClient__GetPcSkillLimit_x                            0x688290
#define PcZoneClient__RemovePetEffect_x                            0x6888F0
#define PcZoneClient__HasAlternateAbility_x                        0x681E40
#define PcZoneClient__GetCurrentMod_x                              0x4EE280
#define PcZoneClient__GetModCap_x                                  0x4EE180
#define PcZoneClient__CanEquipItem_x                               0x6824F0
#define PcZoneClient__GetItemByID_x                                0x6855F0
#define PcZoneClient__GetItemByItemClass_x                         0x685730
#define PcZoneClient__RemoveBuffEffect_x                           0x6889A0
#define PcZoneClient__BandolierSwap_x                              0x683290
#define PcZoneClient__GetLinkedSpellReuseTimer_x                   0x6850C0

//Doors
#define EQSwitch__UseSwitch_x                                      0x610000

//IconCache
#define IconCache__GetIcon_x                                       0x74B6A0

//CContainerMgr
#define CContainerMgr__OpenContainer_x                             0x742250
#define CContainerMgr__CloseContainer_x                            0x742530
#define CContainerMgr__OpenExperimentContainer_x                   0x743090

//CQuantityWnd
#define CQuantityWnd__Open_x                                       0x811200

//CHelpWnd
#define CHelpWnd__SetFile_x                                        0x651F40

//CLootWnd
#define CLootWnd__LootAll_x                                        0x7A6E40
#define CLootWnd__RequestLootSlot_x                                0x7A6080

//EQ_Spell
#define EQ_Spell__GetSpellLevelNeeded_x                            0x5A55B0
#define EQ_Spell__SpellAffects_x                                   0x5A5AB0
#define EQ_Spell__SpellAffectBase_x                                0x5A57D0
#define EQ_Spell__GetSpellAffectBySlot_x                           0x4D0BB0
#define EQ_Spell__GetSpellAffectByIndex_x                          0x4D0B60
#define EQ_Spell__IsSPAStacking_x                                  0x5A69C0
#define EQ_Spell__IsSPAIgnoredByStacking_x                         0x5A5E10
#define EQ_Spell__IsDegeneratingLevelMod_x                         0x5A69D0
#define EQ_Spell__IsLullSpell_x                                    0x5A6200
#define __IsResEffectSpell_x                                       0x4D0360

//EQSpellStrings
#define EQSpellStrings__GetString_x                                0x4B11F0

//EQ_Affect
#define EQ_Affect__GetAffectData_x                                 0x9159F0
#define EQ_Affect__SetAffectData_x                                 0x915FC0

//CTargetWnd
#define CTargetWnd__GetBuffCaster_x                                0x85DBD0
#define CTargetWnd__WndNotification_x                              0x85D360
#define CTargetWnd__RefreshTargetBuffs_x                           0x85D6C0
#define CTargetWnd__HandleBuffRemoveRequest_x                      0x85C140

//CTaskWnd
#define CTaskWnd__UpdateTaskTimers_x                               0x862750
#define CTaskWnd__ConfirmAbandonTask_x                             0x865820

//CTaskManager
#define CTaskManager__GetEntry_x                                   0x5541D0
#define CTaskManager__HandleMessage_x                              0x5520A0
#define CTaskManager__GetTaskStatus_x                              0x554280
#define CTaskManager__GetElementDescription_x                      0x554300

//EqSoundManager
#define EqSoundManager__WavePlay_x                                 0x5A01E0
#define EqSoundManager__PlayScriptMp3_x                            0x5A03E0
#define EqSoundManager__SoundAssistPlay_x                          0x6C5520
#define EqSoundManager__WaveInstancePlay_x                         0x6C4A10

//CCombatSkillsSelectWnd
#define CCombatSkillsSelectWnd__ShouldDisplayThisSkill_x           0x544000

//CTextureAnimation
#define CTextureAnimation__SetCurCell_x                            0x9998E0
#define CTextureAnimation__Draw_x                                  0x999B20
#define CTextureAnimation__AddBlankFrame_x                         0x999700

//CTAFrameDraw
#define CTAFrameDraw__Draw_x                                       0x995630

//CAltAbilityData
#define CAltAbilityData__GetMercCurrentRank_x                      0x5835C0
#define CAltAbilityData__GetMercMaxRank_x                          0x583550
#define CAltAbilityData__GetMaxRank_x                              0x577950

//CTargetRing
#define CTargetRing__Cast_x                                        0x64F750

//CharacterBase
#define CharacterBase__GetMemorizedSpell_x                         0x6587E0
#define CharacterBase__CreateItemGlobalIndex_x                     0x645E70
//this is a guess testing is needed
#define CharacterBase__GetItemPossession_x                         0x6587C0
#define CharacterBase__GetItemByGlobalIndex_x                      0x91D550
#define CharacterBase__GetItemByGlobalIndex1_x                     0x91D5A0
//#define CharacterBase__GetEffectId_x                               

//CCastSpellWnd
#define CCastSpellWnd__ForgetMemorizedSpell_x                      0x7270B0
#define CCastSpellWnd__IsBardSongPlaying_x                         0x727970
#define CCastSpellWnd__RefreshSpellGemButtons_x                    0x727A20

//messages
#define msg_spell_worn_off_x                                       0x5CB440
#define msg_new_text_x                                             0x5BF240
#define __msgTokenTextParam_x                                      0x5CD8B0
#define msgTokenText_x                                             0x5CDCC0

//SpellManager
#define SpellManager__vftable_x                                    0xB2D2FC
#define SpellManager__SpellManager_x                               0x6C9150
#define Spellmanager__LoadTextSpells_x                             0x6C9A50
#define SpellManager__GetSpellByGroupAndRank_x                     0x6C9320

//CCollisionInfoTargetVisibility
#define CCollisionInfoTargetVisibility__CCollisionInfoTargetVisibility_x   0x9E49D0

//ItemGlobalIndex
#define ItemGlobalIndex__IsKeyRingLocation_x                       0x5D3B60
#define ItemGlobalIndex__ItemGlobalIndex_x                         0x5D2030
#define ItemGlobalIndex__IsEquippedLocation_x                      0x672440
#define ItemGlobalIndex__IsValidIndex_x                            0x5D3CF0

//ItemBaseContainer
#define ItemBaseContainer__ItemBaseContainer_x                     0x9163F0
#define ItemBaseContainer__CreateItemGlobalIndex_x                 0x916740

//CLargeDialogWnd
#define CLargeDialogWnd__Open_x                                    0x79EF80

//CCursorAttachment
#define CCursorAttachment__AttachToCursor_x                        0x746F30
#define CCursorAttachment__AttachToCursor1_x                       0x746F70
#define CCursorAttachment__Deactivate_x                            0x748520

//CSidlManagerBase
#define CSidlManagerBase__CreateTabWnd_x                           0x98B290
#define CSidlManagerBase__CreatePageWnd_x                          0x98AA80
//int
#define CSidlManagerBase__FindButtonDrawTemplate_x                 0x985F50
//CXStr
#define CSidlManagerBase__FindButtonDrawTemplate1_x                0x985EE0

//CEQSuiteTextureLoader
#define CEQSuiteTextureLoader__GetDefaultUIPath_x                  0x9AAEB0
#define CEQSuiteTextureLoader__GetTexture_x                        0x9AAB30

//CFindItemWnd
#define CFindItemWnd__CFindItemWnd_x                               0x5242B0
#define CFindItemWnd__WndNotification_x                            0x525170
#define CFindItemWnd__Update_x                                     0x525D50
#define CFindItemWnd__PickupSelectedItem_x                         0x5239B0

//IString
#define IString__Append_x                                          0x513580

//Camera
#define CDisplay__cameraType_x                                     0xED4210
#define EverQuest__Cameras_x                                       0xDA3438

//LootFiltersManager
#define LootFiltersManager__AddItemLootFilter_x                    0x52EE60
#define LootFiltersManager__GetItemFilterData_x                    0x52E7A0
#define LootFiltersManager__RemoveItemLootFilter_x                 0x52E7D0
#define LootFiltersManager__SetItemLootFilter_x                    0x52E9E0

//COptionsWnd
#define COptionsWnd__FillChatFilterList_x                          0x7FDC70

//CResolutionHandler__UpdateResolution_x
#define CResolutionHandler__UpdateResolution_x                     0x9EA690
#define CResolutionHandler__GetWindowedStyle_x                     0x6BF9A0

//CColorPickerWnd
#define CColorPickerWnd__Open_x                                    0x73EBE0

//CDistillerInfo
#define CDistillerInfo__GetIDFromRecordNum_x                       0x9218C0
#define CDistillerInfo__Instance_x                                 0x921800

//CGroupWnd
#define CGroupWnd__WndNotification_x                               0x761890
#define CGroupWnd__UpdateDisplay_x                                 0x760AE0

//ItemBase
#define ItemBase__IsLore_x                                         0x8EA530
#define ItemBase__IsLoreEquipped_x                                 0x8EA5A0

//EQPlacedItemManager
#define EQPlacedItemManager__Instance_x                            0x609F60
#define EQPlacedItemManager__GetItemByGuid_x                       0x60A0A0
#define EQPlacedItemManager__GetItemByRealEstateAndRealEstateItemIds_x 0x60A100

//RealEstateManagerClient
#define RealEstateManagerClient__Instance_x                        0x6B40E0
#define RealEstateManagerClient__GetItemByRealEstateAndItemIds_x   0x6B89D0

//CFactionWnd
#define CFactionWnd__CFactionWnd_x                                 0x519D50

//FactionManagerClient
#define FactionManagerClient__Instance_x                           0x504B00
#define FactionManagerClient__HandleFactionMessage_x               0x505320
//work in progress, these needs to be investigated
#define FactionManagerClient__GetFactionStanding_x                 0x505B10
#define FactionManagerClient__GetMaxFaction_x                      0x505B2F
#define FactionManagerClient__GetMinFaction_x                      0x505AE0

//BaseProfile (PCHARINFO2)
#define BaseProfile__GetItemPossession_x                           0x511710

//ArrayClass
#define ArrayClass__DeleteElement_x                                0x96C210

//AggroMeterManagerClient
#define AggroMeterManagerClient__Instance_x                        0x49DF00

//ClientSOIManager
#define ClientSOIManager__GetSingleton_x                           0x511980

//MercenaryAlternateAdvancementManagerClient
#define MercenaryAlternateAdvancementManagerClient__Instance_x     0x582780

//CTargetManager
#define CTargetManager__Get_x                                      0x6CD0D0

//RealEstateManagerClient
#define RealEstateManagerClient__Instance_x                        0x6B40E0

//CBroadcast (returns what we called pinstCTextOverlay_x)
#define CBroadcast__Get_x                                          0x4AC270

//EQGroundItemListManager
#define EQGroundItemListManager__Instance_x                        0x5DA380

//EverQuestinfo
#define EverQuestinfo__IsItemPending_x                             0xE40ACC

//CAAWnd
#define CAAWnd__ShowAbility_x                                      0x6EAAE0
#define CAAWnd__UpdateSelected_x                                   0x6E7170
#define CAAWnd__Update_x                                           0x6E9E00

//CXRect
#define CXRect__operator_and_x                                     0x756D40

//CUnSerializeBuffer
#define CUnSerializeBuffer__GetString_x                            0x47D240

//
#define __eq_delete_x                                              0x9EAC75
#define __eq_new_x                                                 0x9EB1E4

//patterns
//LoginController__GiveTime_x
// 56 8B F1 E8 ? FD FF FF 8B CE 5E E9 ? ? FF FF C7 01
//Feb 16 2018 Test
//IDA Style Sig: 56 8B F1 E8 ? ? ? ? 8B CE
static PBYTE lpPattern = (PBYTE)"\x56\x8B\xF1\xE8\x00\x00\x00\x00\x8B\xCE";
static char lpMask[] = "xxxx????xx";

//__eqgraphics_fopen
//Jan 09 2020 EQGraphicsDX9.dll
//IDA Style Sig: E8 ? ? ? ? 83 C4 08 89 45 A0
//#define __eqgraphics_fopen_x                                       0x101473C8
//static PBYTE efPattern = (PBYTE)"\xE8\x00\x00\x00\x00\x83\xC4\x08\x89\x45\xA0";
//static char efMask[] = "x????xxxxxx";
//Jan 25 2021 Test
//E8 ? ? ? ? 8B D8 53
static PBYTE efPattern = (PBYTE)"\xE8\x00\x00\x00\x00\x8B\xD8\x53";
static char efMask[] = "x????xxx";

