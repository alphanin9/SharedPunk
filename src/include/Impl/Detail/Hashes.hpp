#pragma once
namespace shared::detail::Hashes
{
#pragma region Assert
constexpr auto Assert_RaiseAssert = 4285205681u;
#pragma endregion

#pragma region FileSystem
constexpr auto FileStream_dtor = 1924865980u;
constexpr auto FileSystem_GetSaveFolder = 4293661415u;

constexpr auto RedFileManager_Instance = 3788966949u;
constexpr auto RedFileManager_OpenFileStream = 1917464012u;
constexpr auto RedFileManager_FindFiles = 4051576167u;

constexpr auto FileSystem_MergeFileToPath = 1194333091u;
constexpr auto FileSystem_MergeDirToPath = 836113218u; // Does a few more checks for stuff
#pragma endregion

#pragma region GameDefinition
constexpr auto GameDefinition_ToWorldID = 1002050525u;
#pragma endregion

#pragma region Ink
constexpr auto InkSystem_Instance = 2635337807u;
constexpr auto InkSystemRequestsHandler_StartSession = 1357913210u;
constexpr auto InkSystemRequestsHandler_ExitToMainMenu = 3105624475u;

constexpr auto InkLoadingScreenHandler_SetUnknownVar = 3771669141u;
constexpr auto InkLoadingLayer_SetUnknownVar = 1370036335u;
#pragma endregion

#pragma region PlayerSystem
constexpr auto PlayerSystem_GetPlayerControlledGameObject = 3420005096u;
#pragma endregion

#pragma region Quest
constexpr auto Quest_SetSaveDataLoadingScreen_NodeType_ExecuteNode = 3489736669u;
constexpr auto Quest_FactsDBManagerNodeDefinition_ExecuteNode = 3679006322u;

constexpr auto QuestsSystem_AddQuest = 1617892594u;
constexpr auto QuestsSystem_CreateContext = 3144298192u;
constexpr auto QuestPhaseInstance_ExecuteNode = 3227858325u;
#pragma endregion

#pragma region SafeAreaManager
constexpr auto SafeAreaManager_IsPointInSafeArea = 2322404505u;
#pragma endregion

#pragma region Save
constexpr auto SaveNodeAccessor_ctor = 3391557872u;
constexpr auto SaveNodeAccessor_dtor = 2159741197u;
constexpr auto SaveNodeAccessor_IsGoodNode = 2352744844u;
#pragma endregion

#pragma region SaveMetadata
constexpr auto SaveMetadata_LoadSaveMetadataFromFile = 1649938065u;
#pragma endregion

#pragma region ScriptableSystem
constexpr auto ScriptableSystem_QueueRequest = 376512876u;
#pragma endregion

#pragma region ScriptableSystemsContainer
constexpr auto ScriptableSystemsContainer_GetSystemByName = 655630607u;
#pragma endregion

#pragma region Session
constexpr auto SessionData_dtor = 3460762581u;
constexpr auto SessionData_AddArgumentToList = 188748408u;
#pragma endregion

#pragma region Telemetry
constexpr auto Telemetry_LoadUsedFactsForImportantFactsList = 3923848734u;
#pragma endregion

#pragma region World
constexpr auto World_IsInInterior = 3384552122u;
#pragma endregion
}; // namespace detail::Hashes