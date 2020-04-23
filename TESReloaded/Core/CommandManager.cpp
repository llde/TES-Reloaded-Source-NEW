#include "PluginVersion.h"
#include "WeatherMode.h"
#include "FormHook.h"

#if defined(NEWVEGAS)
#define CommandPrefix "NVR"
#elif defined(OBLIVION)
#define CommandPrefix "OR"
#elif defined(SKYRIM)
#define CommandPrefix "SR"
#endif

CommandParam SetCustomConstantParams[5] = {

	{ "string",	CommandParam::ParamType::kParamType_String, 0 },
	{ "float",  CommandParam::ParamType::kParamType_Float,  0 },
	{ "float",  CommandParam::ParamType::kParamType_Float,  0 },
	{ "float",  CommandParam::ParamType::kParamType_Float,  0 },
	{ "float",  CommandParam::ParamType::kParamType_Float,  0 },

};

CommandParam SetExtraEffectEnabledParams[2] = {

	{ "string",	CommandParam::ParamType::kParamType_String,  0 },
	{ "int",	CommandParam::ParamType::kParamType_Integer, 0 },

};

#if defined(SKYRIM)
bool Cmd_GetSKSEVersion_Execute(COMMAND_ARGS)
{
	Console_Print("SKSE v%d.%d.%d, Release %d", SKSE_VERSION_INTEGER, SKSE_VERSION_INTEGER_MINOR, SKSE_VERSION_INTEGER_BETA, SKSE_VERSION_RELEASEIDX);
	return true;
}

bool Cmd_ClearInvalidRegistrations_Execute(COMMAND_ARGS)
{
	UInt32 count = (*g_skyrimVM)->ClearInvalidRegistrations();
	Console_Print("Removed %d invalid OnUpdate registration(s)", count);
	return true;
}
#endif

static bool CommandExecuter_GetVersion(CommandArgs Args) {

	TheCommandManager->Commands.GetVersion(Args.result);
	return true;

}
static CommandInfo CommandInfo_GetVersion = { CommandPrefix"GetVersion", "", 0, "Returns the plugin version (console command only)", 0, 0, NULL, CommandExecuter_GetVersion, NULL, NULL, 0 };

static bool CommandExecuter_GetLocationName(CommandArgs Args) {

	TheCommandManager->Commands.GetLocationName(Args.result);
	return true;

}
static CommandInfo CommandInfo_GetLocationName = { CommandPrefix"GetLocationName", "", 0, "Gets the name of the current worldspace and current cell (console command only)", 0, 0, NULL, CommandExecuter_GetLocationName, NULL, NULL, 0 };

static bool CommandExecuter_SetExtraEffectEnabled(CommandArgs Args) {

	char Name[80];
	int Value;

	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Name, &Value)) TheCommandManager->Commands.SetExtraEffectEnabled(Args.result, Name, Value);
	return true;

}
static CommandInfo CommandInfo_SetExtraEffectEnabled = { CommandPrefix"SetExtraEffectEnabled", "", 0, "Enables or disables a custom effect", 0, 2, SetExtraEffectEnabledParams, CommandExecuter_SetExtraEffectEnabled, NULL, NULL, 0 };

static bool CommandExecuter_SetCustomConstant(CommandArgs Args) {

	char Name[80];
	float Value[4];
	
	if (ExtractArgs(Args.paramInfo, Args.arg1, Args.opcodeOffset, Args.thisObj, Args.Obj, Args.scriptObj, Args.eventList, &Name, &Value[0], &Value[1], &Value[2], &Value[3])) TheCommandManager->Commands.SetCustomConstant(Args.result, Name, Value);
	return true;

}
static CommandInfo CommandInfo_SetCustomConstant = { CommandPrefix"SetCustomConstant", "", 0, "Sets the value of a custom constant", 0, 5, SetCustomConstantParams, CommandExecuter_SetCustomConstant, NULL, NULL, 0 };

static bool CommandExecuter_GetWeatherName(CommandArgs Args) {

	TheCommandManager->Commands.GetWeatherName(Args.result);
	return true;

}
static CommandInfo CommandInfo_GetWeatherName = { CommandPrefix"GetWeatherName", "", 0, "Returns the plugin version (console command only)", 0, 0, NULL, CommandExecuter_GetWeatherName, NULL, NULL, 0 };



static bool CommandExecuter_ORPurgeAll(CommandArgs* args) {
	return true;
}
static CommandInfo CommandInfo_ORPurgeAll = { CommandPrefix"ORPurgeAll", "", 0, "", 0, 0, NULL, CommandExecuter_ORPurgeAll, NULL, NULL, 0 };

static bool CommandExecuter_ORPurgeRAM(CommandArgs* args) {
	return true;
}

static CommandInfo CommandInfo_ORPurgeRAM = { CommandPrefix"ORPurgeRAM", "", 0, "", 0, 0, NULL, CommandExecuter_ORPurgeRAM, NULL, NULL, 0 };

static bool CommandExecuter_IsThirdPersonCameraMode(CommandArgs* args) {
	if (TheSettingManager->SettingsMain.CameraMode.Enabled == 1) *args->result = 1;
	else   *args->result = Player->isThirdPerson;
	return true;
}

#if defined(SKYRIM)
#define CommandPrefix ""
DEFINE_COMMAND_PLUGIN(GetSKSEVersion,			 , "Returns the SKSE version", 0, 0, NULL, NULL);
DEFINE_COMMAND_PLUGIN(ClearInvalidRegistrations, , "Clears invalid event registrations", 0, 0, NULL, NULL);
#define CommandPrefix "SR"
#endif

#if defined(OBLIVION) || defined(NEWVEGAS)
CommandManager::CommandManager() {

	Logger::Log("Starting the command manager...");
	TheCommandManager = this;

	ConsolePatched = false;

}



void ReplaceCommands(const PluginInterface* Interface) {
	if (TheSettingManager->SettingsMain.Main.ReplaceCommands) {
		Logger::Log("Replacing Commands");
		CommandTableInterface* cti = (CommandTableInterface*)Interface->QueryInterface(Interface_CommandTable);
		if (cti == NULL) {
			Logger::Log("Can't obtain the CommandTableInterface from OBSE. Cannot replace commands");
			return;
		}
#if defined(OBLIVION)  //I don't know new vegas enough
		CommandInfo* comm = cti->GetByName("IsThirdPerson");
		if (comm) {
			comm->execute = CommandExecuter_IsThirdPersonCameraMode;
		}
		else {
			Logger::Log("Can't substitute IsThirdPerson command");
		}
#endif
	}
}


void CommandManager::AddCommands(const PluginInterface* Interface) {
	
	Interface->SetOpcodeBase(0x3000);
	Interface->RegisterCommand(&CommandInfo_GetVersion);
	Interface->RegisterCommand(&CommandInfo_GetLocationName);
	Interface->RegisterCommand(&CommandInfo_SetExtraEffectEnabled);
	Interface->RegisterCommand(&CommandInfo_SetCustomConstant);
	Interface->RegisterCommand(&CommandInfo_GetWeatherName);
	ReplaceCommands(Interface);
}
#elif defined (SKYRIM)
CommandTable	commandTable;

const CommandInfo* commandsStart = (CommandInfo*)0x0124E880;
const CommandInfo* commandsEnd = (CommandInfo*)0x01255B30;

static const CommandTable::PatchLocation kPatch_ScriptCommands_Start[] =
{
	{ 0x00516B0B, 0x00 },
	{ 0x00516CD4, 0x04 },
	{ 0x00516D6D, 0x08 },
	{ 0x00517D87, 0x00 },
	{ 0x0051B33F, 0x00 },
	{ 0x00542459, 0x0C },
	{ 0x00542471, 0x00 },
	{ 0x00542489, 0x04 },
	{ 0x005424A5, 0x0C },
	{ 0x005424BF, 0x04 },
	{ 0x005424DD, 0x00 },
	{ 0x005424FF, 0x00 },
	{ 0x0054251D, 0x04 },
	{ 0x00542543, 0x00 },
	{ 0x0054255A, 0x00 },
	{ 0x005EA479, 0x20 },
	{ 0x005EA485, 0x10 },
	{ 0x005EA54E, 0x12 },
	{ 0x005EA591, 0x12 },
	{ 0x005EA59D, 0x14 },
	{ 0x005EA5D8, 0x12 },
	{ 0x005EA5E5, 0x14 },
	{ 0x005EA646, 0x12 },
	{ 0x005EA652, 0x14 },
	{ 0x005EA680, 0x12 },
	{ 0x005EA6F1, 0x12 },
	{ 0x005EA723, 0x12 },
	{ 0x005EA72F, 0x14 },
	{ 0x005EA785, 0x12 },
	{ 0x005EA7C3, 0x12 },
	{ 0x005EA7CF, 0x14 },
	{ 0x005EA878, 0x12 },
	{ 0x005EA8A7, 0x14 },
	{ 0x005EA984, 0x12 },
	{ 0x005EA9A6, 0x14 },
	{ 0x005EAABE, 0x12 },
	{ 0x005EAB08, 0x12 },
	{ 0x005EAB18, 0x14 },
	{ 0x005EABB1, 0x14 },
	{ 0x006A2D0C, 0x12 },
	{ 0x006A2D39, 0x14 },
	{ 0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_End[] =
{
	{ 0x00516C12, 0x08 },
	{ 0x00516CFF, 0x04 },
	{ 0 },
};

static const CommandTable::PatchLocation kPatch_ScriptCommands_MaxIdx[] =
{
	{ 0x00502C10 + 0x0087 + 1,	0 },
	{ 0x00516AD0 + 0x0029 + 2,	(UInt32)(-0x1001) },
	{ 0x00516C10 + 0x0000 + 6,	0 },
	{ 0x00517C20 + 0x0156 + 1,	(UInt32)(-0x1001) },
	{ 0x0051ABE0 + 0x0751 + 2,	(UInt32)(-0x1001) },
	{ 0x005E98C0 + 0x000D + 2,	(UInt32)(-0x1001) },
	{ 0x005E98C0 + 0x001D + 1,	(UInt32)(-0x1001) },
	{ 0x005E98C0 + 0x0029 + 2,	(UInt32)(-0x1001) },
	{ 0 },
};

static const CommandTable::PatchSet kPatchSet =
{
	kPatch_ScriptCommands_Start,
	kPatch_ScriptCommands_End,
	kPatch_ScriptCommands_MaxIdx
};

void (__cdecl * ToggleConsole)() = (void (__cdecl *)())0x00847210;
void __cdecl TrackToggleConsole() {

	if (!TheCommandManager->ConsolePatched) {
		commandTable.Init(0x1000, 0x1480);
		commandTable.Read(commandsStart, commandsEnd);
		commandTable.Add();
		commandTable.Add(&kCommandInfo_GetSKSEVersion);
		commandTable.Add(&kCommandInfo_ClearInvalidRegistrations);
		commandTable.Add();
		commandTable.Add(&kCommandInfo_GetVersion);
		commandTable.Add(&kCommandInfo_GetLocationName);
		commandTable.Add(&kCommandInfo_SetCustomShaderEnabled);
		commandTable.Add(&kCommandInfo_SetCustomConstant);
		commandTable.Add();
		commandTable.PatchEXE(&kPatchSet);
		TheCommandManager->ConsolePatched = true;
	}
	ToggleConsole();

}

void CreateConsoleCommandHook()
{
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)ToggleConsole,	&TrackToggleConsole);
	DetourTransactionCommit();
}

CommandManager::CommandManager()
{
	Logger::Log("Starting the command manager...");
	ConsolePatched = false;
}
#endif

void CommandManager::PluginCommands::GetVersion(double* result) {

	if (MenuManager->IsActive(Menu::MenuType::kMenuType_Console)) PrintToConsole(PluginVersion::VersionString);
	*result = 1;

}

void CommandManager::PluginCommands::GetLocationName(double* result) {

	if (MenuManager->IsActive(Menu::MenuType::kMenuType_Console)) {
		const char* worldName = NULL;
		const char* regionName = NULL;
		const char* cellName = TheShaderManager->ShaderConst.currentCell->GetEditorName();

		std::string s = "Worldspace: ";
		if (TESWorldSpace* currentWS = TheShaderManager->ShaderConst.currentWorldSpace) worldName = currentWS->GetEditorName();
		if (worldName != NULL)
			s += worldName;
		else
			s += "(no worldspace)";
		s += ", Region: ";
		if (TESRegionEx* currentRE = (TESRegionEx*)TheShaderManager->ShaderConst.currentRegion) regionName = currentRE->EditorName;
		if (regionName != NULL)
			s += regionName;
		else
			s += "(no region)";
		s += ", Cell: ";
		s += cellName;
		PrintToConsole(s.c_str());
	}
	*result = 1;

}

void CommandManager::PluginCommands::SetExtraEffectEnabled(double* result, const char* Name, bool Value) {

	TheShaderManager->SetExtraEffectEnabled(Name, Value);
	*result = 1;

}

void CommandManager::PluginCommands::SetCustomConstant(double* result, const char* Name, D3DXVECTOR4 Value) {

	TheShaderManager->SetCustomConstant(Name, Value);
	*result = 1;

}

void CommandManager::PluginCommands::GetWeatherName(double* result) {

	if (MenuManager->IsActive(Menu::MenuType::kMenuType_Console)) {
		const char* weatherName = NULL;

		if (TESWeatherEx* currentWE = (TESWeatherEx*)TheShaderManager->ShaderConst.pWeather) weatherName = currentWE->EditorName;
		std::string s = "Weather: ";
		if (weatherName != NULL)
			s += weatherName;
		else
			s += "(no weather)";
		PrintToConsole(s.c_str());
	}
	*result = 1;

}
