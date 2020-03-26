#pragma once

#include "EquipmentManager.h"
#include "ScriptManager.h"
#include "SettingManager.h"
#include "CommandManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "RenderManager.h"
#include "FrameRateManager.h"
#include "UtilityManager.h"
#include "GameEventManager.h"
#include "GameMenuManager.h"
#include "KeyboardManager.h"
#include "ShadowManager.h"

extern SettingManager*		TheSettingManager;
extern CommandManager*		TheCommandManager;
extern TextureManager*		TheTextureManager;
extern ShaderManager*		TheShaderManager;
extern RenderManager*		TheRenderManager;
extern FrameRateManager*	TheFrameRateManager;
extern UtilityManager*		TheUtilityManager;
extern GameMenuManager*		TheGameMenuManager;
extern KeyboardManager*		TheKeyboardManager;
extern GameEventManager*	TheGameEventManager;
extern ShadowManager*		TheShadowManager;
extern EquipmentManager*	TheEquipmentManager;
extern ScriptManager*		TheScriptManager;

void InitializeManagers();