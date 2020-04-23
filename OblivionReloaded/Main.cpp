#define HookD3DDevice 0
#define WaitForDebugger 0

#include "RenderHook.h"
#include "ShaderIOHook.h"
#include "FormHook.h"
#include "GrassMode.h"
#include "MountedCombat.h"
#include "CameraMode.h"
#include "SleepingMode.h"
#include "WeatherMode.h"
#include "Animation.h"
#include "Dodge.h"
#include "FlyCam.h"
#include "PluginVersion.h"
#include "MemoryManagement.h"

#if HookD3DDevice
#include "D3D9Hook.h"
#endif


extern "C" {

	bool OBSEPlugin_Query(const PluginInterface* Interface, PluginInfo* Info) {
		
		Info->InfoVersion = PluginInfo::kInfoVersion;
		Info->Name = "OblivionReloaded";
		Info->Version = 8;
		return true;

	}

	bool OBSEPlugin_Load(const PluginInterface* Interface) {

#ifdef _DEBUG
#if WaitForDebugger
		while (!IsDebuggerPresent()) Sleep(10);
#endif
#endif

		Logger::CreateLog("OblivionReloaded.log");
#if HookD3DDevice
		if (!Interface->IsEditor) CreateD3D9Hook();
#endif

		new SettingManager();
		new CommandManager();
		TheCommandManager->AddCommands(Interface);

		if (!Interface->IsEditor) {
			PluginVersion::CreateVersionString();
			new UtilityManager();

			TheSettingManager->LoadSettings();
			
			PerformGameInitialization();
			CreateShaderIOHook();
			CreateRenderHook();
			CreateFormLoadHook();
			CreateSettingsHook();
			CreateGameEventHook();
			CreateScriptHook();
			CreateAnimationHook();
			CreateShadowsHook();
			if (TheSettingManager->SettingsMain.Main.MemoryManagement) CreateMemoryManagementHook();
			if (TheSettingManager->SettingsMain.GrassMode.Enabled) CreateGrassHook();
			if (TheSettingManager->SettingsMain.MountedCombat.Enabled) CreateMountedCombatHook();
			if (TheSettingManager->SettingsMain.CameraMode.Enabled) CreateCameraModeHook();
			if (TheSettingManager->SettingsMain.EquipmentMode.Enabled) CreateEquipmentHook();
			if (TheSettingManager->SettingsMain.SleepingMode.Enabled) CreateSleepingModeHook();
			if (TheSettingManager->SettingsMain.Dodge.Enabled) CreateDodgeHook();
			if (TheSettingManager->SettingsMain.FlyCam.Enabled) CreateFlyCamHook();
			if (TheSettingManager->SettingsMain.WeatherMode.Enabled) CreateWeatherModeHook();

			WriteRelJump(0x0049849A, 0x004984A0); //Skips antialiasing deactivation if HDR is enabled on the D3DDevice
			WriteRelJump(0x004984BD, 0x004984CD); //Skips antialiasing deactivation if AllowScreenshot is enabled
			WriteRelJump(0x005DEE60, 0x005DEE68); //Skips antialiasing deactivation if HDR is enabled on loading the video menu
			WriteRelJump(0x005DF69E, 0x005DF755); //Skips HDR deactivation changing antialising (video menu)
			WriteRelJump(0x00497D5A, 0x00497D63); //Unlocks antialising bar if HDR is enabled (video menu)
			WriteRelJump(0x005DF8E9, 0x005DF983); //Skips antialising deactivation changing HDR (video menu)
			WriteRelJump(0x006738B1, 0x00673935); //Cancels the fPlayerDeathReloadTime

		}
		return true;

	}

};