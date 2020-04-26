#include "RenderHook.h"

#if defined(NEWVEGAS)
#define kInitializeRenderer 0x0086D500
#define kRender 0x008706B0
#define kProcessImageSpaceShaders 0x00B55AC0
#define kBeginScene 0x00E74F40
#define kMenuRenderedTexture 0x011DED3C
static const UInt32 kRenderInterface = 0x007144D3;
static const UInt32 kRenderInterfaceReturn = 0x007144D8;
static const UInt32 kRenderInterfaceMethod = 0x007134D0;
static const UInt32 kRenderFirstPersonNode = 0x00870F74;
static const UInt32 kRenderFirstPersonNodeRepeat = 0x00870F30;
static const UInt32 kRenderFirstPersonNodeReturn = 0x00870F9B;
static const UInt32 kClearDepth = 0x008751BF;
static const UInt32 kClearDepthReturn = 0x008751CB;
static const UInt32 kSetTileShaderConstants = 0x00BCAAD7;
static const UInt32 kSetTileShaderConstantsReturn = 0x00BCAADE;
static const UInt32 kMultiBoundWaterHeightFix1 = 0x006FAE04;
static const UInt32 kMultiBoundWaterHeightFix2 = 0x006FAF50;
static UInt32 ClearMode = 0;
#elif defined(OBLIVION)
#define kInitializeRenderer 0x004052F0
#define kRender 0x0040C830
#define kProcessImageSpaceShaders 0x007B48E0
#define kBeginScene 0x0076BE00
#define kMenuRenderedTexture 0x00B333E8
static const UInt32 kRenderInterface = 0x0057F3F3;
static const UInt32 kRenderInterfaceReturn = 0x0057F3F8;
static const UInt32 kRenderInterfaceMethod = 0x0070E0A0; //NiCullingProcess::Process
#elif defined(SKYRIM)
#define kInitializeRenderer 0x00691030
#define kRender 0x0069BDF0
#define kProcessImageSpaceShaders 0x00C70DA0
#define kBeginScene 0x00CDA620
#define kMenuRenderedTexture 0x01B2E8D8
static const UInt32 kRenderInterface = 0x00A5CB57;
static const UInt32 kRenderInterfaceReturn = 0x00A5CB5C;
static const UInt32 kRenderInterfaceMethod = 0x00A623F0;
static const UInt32 kRenderFirstPersonNode = 0x0069BD27;
static const UInt32 kRenderFirstPersonNodeRepeat = 0x0069BCC4;
static const UInt32 kRenderFirstPersonNodeReturn = 0x0069BD32;
static const UInt32 kClearDepth = 0x00698BBA;
static const UInt32 kClearDepthReturn = 0x00698BC3;
static const UInt32 kSetShadowDistance = 0x00CBB140;
static const UInt32 kSetShadowDistanceReturn = 0x00CBB146;
static const UInt32 kSetShadowDistanceShader = 0x00CB7365;
static const UInt32 kSetShadowDistanceShaderReturn = 0x00CB736D;
static const UInt32 kFixSunFlags = 0x0069A92F;
static const UInt32 kFixSunFlagsReturn = 0x0069A938;
static UInt32 ClearMode = 0;
#endif

class RenderHook {
	
public:
	NiDX9Renderer* TrackInitializeRenderer();
	bool TrackBeginScene();
#if defined(NEWVEGAS)
	void TrackRender(BSRenderedTexture* RenderedTexture, int Arg2, int Arg3);
	void TrackRenderWorldSceneGraph(Sun* SkySun, UInt8 IsFirstPerson, UInt8 WireFrame, UInt8 Arg4);
	float TrackGetWaterHeightLOD();
#elif defined (OBLIVION)
	void TrackRender(BSRenderedTexture*);
	bool TrackEndTargetGroup(NiCamera*, NiRenderTargetGroup*);
	void TrackHDRRender(NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
	UInt32 TrackSetupShaderPrograms(NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32);
	void TrackCulling(NiCullingProcess*);
	void TrackCullingBSFadeNode(NiCullingProcess*);
	float TrackFarPlane();
	IDirect3DBaseTexture9* TrackPrepareTextureForRendering(NiTexture*, UInt32, UInt32, UInt32);
	HRESULT TrackSetSamplerState(UInt32, D3DSAMPLERSTATETYPE, UInt32, UInt8);
#elif defined(SKYRIM)
	void TrackRender(BSRenderedTexture* RenderedTexture, int Arg2, int Arg3);
	bool TrackSetupRenderingPass(UInt32 Arg1, UInt32 Arg2);
	void TrackRenderWorldSceneGraph(Sun* SkySun, UInt8 IsFirstPerson, UInt8 WireFrame);
#endif

};

NiDX9Renderer* (__thiscall RenderHook::* InitializeRenderer)();
NiDX9Renderer* (__thiscall RenderHook::* TrackInitializeRenderer)();
NiDX9Renderer* RenderHook::TrackInitializeRenderer() {
	
	NiDX9Renderer* Renderer = (this->*InitializeRenderer)();
	
	TheRenderManager = (RenderManager*)Renderer;
	TheRenderManager->Initialize();
	InitializeManagers();
	TheShaderManager->CreateEffects();
	return Renderer;

}

bool (__thiscall RenderHook::* BeginScene)();
bool (__thiscall RenderHook::* TrackBeginScene)();
bool RenderHook::TrackBeginScene() {

	TheShaderManager->BeginScene();
	return (this->*BeginScene)();

}
#if defined(NEWVEGAS)
void (__thiscall RenderHook::* Render)(BSRenderedTexture*, int, int);
void (__thiscall RenderHook::* TrackRender)(BSRenderedTexture*, int, int);
void RenderHook::TrackRender(BSRenderedTexture* RenderedTexture, int Arg2, int Arg3) {

	TheRenderManager->SetSceneGraph();
	TheShaderManager->UpdateConstants();
	if (TheSettingManager->SettingsMain.Develop.TraceShaders && TheKeyboardManager->OnKeyDown(TheSettingManager->SettingsMain.Develop.TraceShaders)) Logger::Log("RENDERING...");
	(this->*Render)(RenderedTexture, Arg2, Arg3);

}

void (__cdecl * SetupRenderingPass)(UInt32, NiD3DShader*) = (void (__cdecl *)(UInt32, NiD3DShader*))0x00B99390;
void __cdecl TrackSetupRenderingPass(UInt32 PassIndex, NiD3DShader* Shader) {
	
	SetupRenderingPass(PassIndex, Shader);

	NiGeometry* Geometry = *(NiGeometry**)(*(void**)0x011F91E0);
	NiD3DPass* Pass = *(NiD3DPass**)0x0126F74C;
	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)Pass->VertexShader;
	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)Pass->PixelShader;
	
	if (VertexShader) {
		if (VertexShader->ShaderProg) VertexShader->ShaderProg->SetCT();
		if (TheSettingManager->SettingsMain.Develop.TraceShaders && TheKeyboardManager->OnKeyDown(TheSettingManager->SettingsMain.Develop.TraceShaders)) Logger::Log("VertexShader: %s %s", VertexShader->ShaderName, Geometry->m_pcName);
	}
	if (PixelShader) {
		if (PixelShader->ShaderProg) PixelShader->ShaderProg->SetCT();
		if (TheSettingManager->SettingsMain.Develop.TraceShaders && TheKeyboardManager->OnKeyDown(TheSettingManager->SettingsMain.Develop.TraceShaders)) Logger::Log("PixelShader: %s %s", PixelShader->ShaderName, Geometry->m_pcName);
	}

}

void (__thiscall RenderHook::* RenderWorldSceneGraph)(Sun*, UInt8, UInt8, UInt8);
void (__thiscall RenderHook::* TrackRenderWorldSceneGraph)(Sun*, UInt8, UInt8, UInt8);
void RenderHook::TrackRenderWorldSceneGraph(Sun* SkySun, UInt8 IsFirstPerson, UInt8 WireFrame, UInt8 Arg4) {

	(this->*RenderWorldSceneGraph)(SkySun, IsFirstPerson, WireFrame, Arg4);
	if (!IsFirstPerson) TheRenderManager->ResolveDepthBuffer();

}

float (__thiscall RenderHook::* GetWaterHeightLOD)();
float (__thiscall RenderHook::* TrackGetWaterHeightLOD)();
float RenderHook::TrackGetWaterHeightLOD() {
	
	TESWorldSpace* Worldspace = (TESWorldSpace*)this;
	float r = Worldspace->waterHeight;

	if (*(void**)Worldspace == (void*)0x0103195C) {
		r = Worldspace->defaultWaterHeight;
		TESObjectCELL* Cell = Player->parentCell;

		if (Cell && Cell->flags0 & TESObjectCELL::kFlags0_HasWater) {
			r = Cell->GetWaterHeight(Player->renderData);
		}
		else {
			UInt8 GridSize = Tes->gridCellArray->gridSize;
			for (int x = 0; x < GridSize; x++) {
				for (int y = 0; y < GridSize; y++) {
					Cell = Tes->gridCellArray->GetCell(x, y);
					if (Cell && Cell->flags0 & TESObjectCELL::kFlags0_HasWater) {
						r = Cell->GetWaterHeight(Player->renderData);
						goto breakall;
					}
				}
			}
		}
	}
breakall:
	return r;

}

static const UInt32 NiDX9RendererClear = 0x007148C0;
static __declspec(naked) void ClearDepth()
{
	__asm
	{
		push	ClearMode
		push	0
		mov     ecx, [ebp + 0x8]
		call	NiDX9RendererClear
		jmp		kClearDepthReturn
	}
}

static const UInt32 RenderFirstPerson = 0x00875110;
static __declspec(naked) void RenderFirstPersonNode()
{
	__asm
	{
		call	RenderFirstPerson
		cmp		ClearMode, 0
		jnz		loc_jumpout
		mov		ClearMode, 4
		pushad
		mov		ecx, TheRenderManager
		call	RenderManager::ResolveDepthBuffer
		popad
		jmp		kRenderFirstPersonNodeRepeat

	loc_jumpout :
		mov		ClearMode, 0
		jmp		kRenderFirstPersonNodeReturn
	}
}

static UInt32* ShaderPackageSelector = (UInt32*)0x011F91C0;
static UInt32* ShaderPackageSelectorMax = (UInt32*)0x011F91BC;
void (__cdecl * SetShaderPackageSelector)(int, int, UInt8, int, char*, int) = (void (__cdecl *)(int, int, UInt8, int, char*, int))0x00B4F710;
void __cdecl TrackSetShaderPackageSelector(int Arg1, int Arg2, UInt8 Force1XShaders, int Arg4, char* GraphicsName, int Arg6) {

	SetShaderPackageSelector(Arg1, Arg2, Force1XShaders, Arg4, GraphicsName, Arg6);
	if (TheSettingManager->SettingsMain.Main.ShaderModel3) {
		if (*ShaderPackageSelector == 5 && *ShaderPackageSelectorMax == 5)
			*ShaderPackageSelector = *ShaderPackageSelectorMax = 7;
		else if (*ShaderPackageSelector == 6 && *ShaderPackageSelectorMax == 6)
			*ShaderPackageSelector = *ShaderPackageSelectorMax = 7;
	}

}

void RenderMainMenuMovie() {

	if (TheSettingManager->SettingsMain.Main.ReplaceIntro && MenuManager->IsActive(Menu::MenuType::kMenuType_Main))
		Binker::Render(TheRenderManager->device, TheSettingManager->CurrentPath, MainMenuMovie, TheRenderManager->width, TheRenderManager->height);
	else
		Binker::Close(TheRenderManager->device);

}

void SetTileShaderAlpha() {

	if (MenuManager->IsActive(Menu::MenuType::kMenuType_Main)) {
		NiVector4 TintColor = { 1.0f, 1.0f, 1.0f, 0.0f };
		float ViewProj[16];
		TheRenderManager->device->GetVertexShaderConstantF(0, ViewProj, 4);
		if ((int)ViewProj[3] == -1 && (int)ViewProj[7] == 1 && (int)ViewProj[15] == 1) TheRenderManager->device->SetPixelShaderConstantF(0, (const float*)&TintColor, 1);
	}

}

static __declspec(naked) void SetTileShaderConstants()
{

	__asm
	{
		pushad
		call	SetTileShaderAlpha
		popad
		cmp		byte ptr [esi + 0xAC], 0
		jmp		kSetTileShaderConstantsReturn
	}

}

float MultiBoundWaterHeightFix() {

	return Player->pos.z;

}

#elif defined(OBLIVION)
void (__thiscall RenderHook::* Render)(BSRenderedTexture*);
void (__thiscall RenderHook::* TrackRender)(BSRenderedTexture*);
void RenderHook::TrackRender(BSRenderedTexture* RenderedTexture) {
	
	TheRenderManager->SetSceneGraph();
	TheShaderManager->UpdateConstants();
	if (TheRenderManager->BackBuffer) TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface = TheRenderManager->defaultRTGroup->RenderTargets[1]->data->Surface;
	if (TheSettingManager->SettingsMain.Develop.TraceShaders && TheKeyboardManager->OnKeyDown(TheSettingManager->SettingsMain.Develop.TraceShaders)) Logger::Log("RENDERING...");
	(this->*Render)(RenderedTexture);

}

bool (__thiscall RenderHook::* EndTargetGroup)(NiCamera*, NiRenderTargetGroup*);
bool (__thiscall RenderHook::* TrackEndTargetGroup)(NiCamera*, NiRenderTargetGroup*);
bool RenderHook::TrackEndTargetGroup(NiCamera* Camera, NiRenderTargetGroup* TargetGroup) {

	if (TheRenderManager->BackBuffer) TargetGroup = TheRenderManager->defaultRTGroup;
	return (this->*EndTargetGroup)(Camera, TargetGroup);

}

void (__thiscall RenderHook::* HDRRender)(NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
void (__thiscall RenderHook::* TrackHDRRender)(NiScreenElements*, BSRenderedTexture**, BSRenderedTexture**, UInt8);
void RenderHook::TrackHDRRender(NiScreenElements* ScreenElements, BSRenderedTexture** RenderedTexture1, BSRenderedTexture** RenderedTexture2, UInt8 Arg4) {
	
	TheRenderManager->clearColor = D3DCOLOR_ARGB(0, 0, 0, 0);
	(this->*HDRRender)(ScreenElements, RenderedTexture1, RenderedTexture2, Arg4);

}

void (__thiscall RenderHook::* Culling)(NiCullingProcess*);
void (__thiscall RenderHook::* TrackCulling)(NiCullingProcess*);
void RenderHook::TrackCulling(NiCullingProcess* Process) {
	
	NiAVObject* Object = (NiAVObject*)this;
	
	if (Object && Object->m_pcName) {
		if (TheSettingManager->SettingsMain.Effects.Rain && (!memcmp(Object->m_pcName, "Current Precip Root", 19) || !memcmp(Object->m_pcName, "Last Precip Root", 16))) return;
	}
	(this->*Culling)(Process);

}

void (__thiscall RenderHook::* CullingBSFadeNode)(NiCullingProcess*);
void (__thiscall RenderHook::* TrackCullingBSFadeNode)(NiCullingProcess*);
void RenderHook::TrackCullingBSFadeNode(NiCullingProcess* Process) {
	
	BSFadeNode* Object = (BSFadeNode*)this;

	if (TheSettingManager->SettingsMain.FrameRate.Enabled && TheShaderManager->ShaderConst.currentWorldSpace) {
		if (Object->cMultType == 6 && !strstr(Object->m_pcName, "ImperialCity") && TheFrameRateManager->IsOutGrid(Object)) return;
	}
	(this->*CullingBSFadeNode)(Process);

}

float (__thiscall RenderHook::* FarPlane)();
float (__thiscall RenderHook::* TrackFarPlane)();
float RenderHook::TrackFarPlane() {
	
	float r = (this->*FarPlane)();

	if (TheSettingManager->SettingsMain.Main.FarPlaneDistance && r == 283840.0f) r = TheSettingManager->SettingsMain.Main.FarPlaneDistance;
	return r;

}

IDirect3DBaseTexture9* (__thiscall RenderHook::* PrepareTextureForRendering)(NiTexture*, UInt32, UInt32, UInt32);
IDirect3DBaseTexture9* (__thiscall RenderHook::* TrackPrepareTextureForRendering)(NiTexture*, UInt32, UInt32, UInt32);
IDirect3DBaseTexture9* RenderHook::TrackPrepareTextureForRendering(NiTexture* Texture, UInt32 Arg2, UInt32 Arg3, UInt32 Arg4) {
	
	TheShaderManager->ShaderConst.TextureData.x = Texture->GetWidth();
	TheShaderManager->ShaderConst.TextureData.y = Texture->GetHeight();
	return (this->*PrepareTextureForRendering)(Texture, Arg2, Arg3, Arg4);
	
}

UInt32 (__thiscall RenderHook::* SetupShaderPrograms)(NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32);
UInt32 (__thiscall RenderHook::* TrackSetupShaderPrograms)(NiGeometry*, NiSkinInstance*, NiSkinPartition::Partition*, NiGeometryBufferData*, NiPropertyState*, NiDynamicEffectState*, NiTransform*, UInt32);
UInt32 RenderHook::TrackSetupShaderPrograms(NiGeometry* Geometry, NiSkinInstance* SkinInstance, NiSkinPartition::Partition* SkinPartition, NiGeometryBufferData* GeometryBufferData, NiPropertyState* PropertyState, NiDynamicEffectState* EffectState, NiTransform* WorldTransform, UInt32 WorldBound) {

	NiD3DPass* Pass = ((NiD3DShader*)this)->CurrentPass;
	NiD3DVertexShaderEx* VertexShader = (NiD3DVertexShaderEx*)Pass->VertexShader;
	NiD3DPixelShaderEx* PixelShader = (NiD3DPixelShaderEx*)Pass->PixelShader;

	if (VertexShader) {
		if (VertexShader->ShaderProg && TheRenderManager->renderState->GetVertexShader() != VertexShader->ShaderHandle) VertexShader->ShaderProg->SetCT();
		if (TheSettingManager->SettingsMain.Develop.TraceShaders && TheKeyboardManager->OnKeyDown(TheSettingManager->SettingsMain.Develop.TraceShaders)) Logger::Log("VertexShader: %s %s", VertexShader->ShaderName, Geometry->m_pcName);
	}
	if (PixelShader) {
		if (PixelShader->ShaderProg && TheRenderManager->renderState->GetPixelShader() != PixelShader->ShaderHandle) PixelShader->ShaderProg->SetCT();
		if (TheSettingManager->SettingsMain.Develop.TraceShaders && TheKeyboardManager->OnKeyDown(TheSettingManager->SettingsMain.Develop.TraceShaders)) Logger::Log("PixelShader: %s %s", PixelShader->ShaderName, Geometry->m_pcName);
	}
	return (this->*SetupShaderPrograms)(Geometry, SkinInstance, SkinPartition, GeometryBufferData, PropertyState, EffectState, WorldTransform, WorldBound);

}

HRESULT (__thiscall RenderHook::* SetSamplerState)(UInt32, D3DSAMPLERSTATETYPE, UInt32, UInt8);
HRESULT (__thiscall RenderHook::* TrackSetSamplerState)(UInt32, D3DSAMPLERSTATETYPE, UInt32, UInt8);
HRESULT RenderHook::TrackSetSamplerState(UInt32 Sampler, D3DSAMPLERSTATETYPE Type, UInt32 Value, UInt8 Save) {

	if (TheSettingManager->SettingsMain.Main.AnisotropicFilter >= 2) {
		if (Type == D3DSAMP_MAGFILTER) {
			if (Value != D3DTEXF_NONE && Value != D3DTEXF_POINT) Value = D3DTEXF_LINEAR;
		}
		if (Type == D3DSAMP_MINFILTER) {
			if (Value != D3DTEXF_NONE && Value != D3DTEXF_POINT) Value = D3DTEXF_ANISOTROPIC;
		}
		if ((Type == D3DSAMP_MIPFILTER) && ((Value == D3DTEXF_POINT) || (Value == D3DTEXF_LINEAR))) {
			Value = D3DTEXF_LINEAR;
		}
	}
	return (this->*SetSamplerState)(Sampler, Type, Value, Save);

}

NiPixelData* (__cdecl * SaveGameScreenshot)(int*, int*) = (NiPixelData* (__cdecl *)(int*, int*))0x00411B70;
NiPixelData* __cdecl TrackSaveGameScreenshot(int* pWidth, int* pHeight) {
	
	NiPixelData* r = NULL;
	
	TheRenderManager->IsSaveGameScreenShot = 1;
	r = SaveGameScreenshot(pWidth, pHeight);
	TheRenderManager->IsSaveGameScreenShot = 0;
	return r;

}

static UInt32* ShaderPackageSelector = (UInt32*)0x00B42F48;
static UInt32* ShaderPackageSelectorMax = (UInt32*)0x00B42D74;
void (__cdecl * SetShaderPackageSelector)(int, int, UInt8, int, char*, int) = (void (__cdecl *)(int, int, UInt8, int, char*, int))0x007B45F0;
void __cdecl TrackSetShaderPackageSelector(int Arg1, int Arg2, UInt8 Force1XShaders, int Arg4, char* GraphicsName, int Arg6) {
	
	SetShaderPackageSelector(Arg1, Arg2, Force1XShaders, Arg4, GraphicsName, Arg6);
	if (TheSettingManager->SettingsMain.Main.ShaderModel3) {
		if (*ShaderPackageSelector == 5 && *ShaderPackageSelectorMax == 5)
			*ShaderPackageSelector = *ShaderPackageSelectorMax = 7;
		else if (*ShaderPackageSelector == 6 && *ShaderPackageSelectorMax == 6)
			*ShaderPackageSelector = *ShaderPackageSelectorMax = 7;
	}
	
}

void (__cdecl * RenderObject)(NiCamera*, NiNode*, NiCullingProcess*, NiVisibleArray*) = (void (__cdecl *)(NiCamera*, NiNode*, NiCullingProcess*, NiVisibleArray*))0x0070C0B0;
void __cdecl TrackRenderObject(NiCamera* Camera, NiNode* Object, NiCullingProcess* CullingProcess, NiVisibleArray* VisibleArray) {

	bool CameraMode = TheSettingManager->SettingsMain.CameraMode.Enabled;

	if (CameraMode) {
		if (Object == WorldSceneGraph && TheRenderManager->FirstPersonView) Player->niNode->m_flags &= ~NiAVObject::kFlag_AppCulled;
		if (Object == Player->firstPersonNiNode) return;
	}
	RenderObject(Camera, Object, CullingProcess, VisibleArray);
	if (Object == WorldSceneGraph && (!TheRenderManager->FirstPersonView || CameraMode  /*|| Player->firstPersonNiNode->m_flags & NiAVObject::kFlag_AppCulled */)) {
		TheRenderManager->ResolveDepthBuffer();
	}
	else if (Object == Player->firstPersonNiNode) {
		TheRenderManager->ResolveDepthBuffer();
//		TheRenderManager->Clear(NULL, NiRenderer::kClear_ZBUFFER);
//		RenderObject(Camera, Object, CullingProcess, VisibleArray);  //This is responsible of double hand effects in some conditions when in First person without CameraMode.
	}

}

#elif defined(SKYRIM)
void (__thiscall RenderHook::* Render)(BSRenderedTexture*, int, int);
void (__thiscall RenderHook::* TrackRender)(BSRenderedTexture*, int, int);
void RenderHook::TrackRender(BSRenderedTexture* RenderedTexture, int Arg2, int Arg3) {
	
	TheRenderManager->SetSceneGraph();
	TheShaderManager->UpdateConstants();
	if (TheSettingManager->SettingsMain.Develop.TraceShaders) Logger::Log("RENDERING...");
	(this->*Render)(RenderedTexture, Arg2, Arg3);

}

bool (__thiscall RenderHook::* SetupRenderingPass)(UInt32, UInt32);
bool (__thiscall RenderHook::* TrackSetupRenderingPass)(UInt32, UInt32);
bool RenderHook::TrackSetupRenderingPass(UInt32 Arg1, UInt32 Arg2) {

	bool r = (this->*SetupRenderingPass)(Arg1, Arg2);
	NiD3DVertexShaderEx* VertexShader = *(NiD3DVertexShaderEx**)0x01BABFB4;
	NiD3DPixelShaderEx* PixelShader = *(NiD3DPixelShaderEx**)0x01BABFB0;
	
	if (VertexShader) {
		if (VertexShader->ShaderProg) VertexShader->ShaderProg->SetCT();
		if (TheSettingManager->SettingsMain.Develop.TraceShaders) Logger::Log("SetVertexShader: %s", VertexShader->ShaderName);
	}
	if (PixelShader) {
		if (PixelShader->ShaderProg) PixelShader->ShaderProg->SetCT();
		if (TheSettingManager->SettingsMain.Develop.TraceShaders) Logger::Log("SetPixelShader: %s", PixelShader->ShaderName);
	}
	return r;

}

void (__thiscall RenderHook::* RenderWorldSceneGraph)(Sun*, UInt8, UInt8);
void (__thiscall RenderHook::* TrackRenderWorldSceneGraph)(Sun*, UInt8, UInt8);
void RenderHook::TrackRenderWorldSceneGraph(Sun* SkySun, UInt8 IsFirstPerson, UInt8 WireFrame) {

	(this->*RenderWorldSceneGraph)(SkySun, IsFirstPerson, WireFrame);
	if (!IsFirstPerson) TheRenderManager->ResolveDepthBuffer();

}

static const UInt32 NiDX9RendererClear = 0x00CD5D00;
static __declspec(naked) void ClearDepth()
{
	__asm
	{
		push	ClearMode
		push	0
		call	NiDX9RendererClear
		jmp		kClearDepthReturn
	}
}

static const UInt32 RenderFirstPersonShadow = 0x00695740;
static __declspec(naked) void RenderFirstPersonNode()
{
	__asm
	{
		cmp		ClearMode, 0
		jnz		loc_jumpout
		mov		ClearMode, 4
		pushad
		mov		ecx, TheRenderManager
		call	RenderManager::ResolveDepthBuffer
		popad
		jmp		kRenderFirstPersonNodeRepeat

	loc_jumpout:
		call	RenderFirstPersonShadow
		mov		ClearMode, 0
		jmp		kRenderFirstPersonNodeReturn
	}
}

void SetShadowDistanceValue(float* Distance, UInt32 Pass) {

	if (Pass == 0) *Distance /= TheSettingManager->SettingsMain.ShadowMode.NearQuality;

}

static __declspec(naked) void SetShadowDistance()
{
	__asm
	{
		faddp   st(1), st
		fstp	dword ptr [esp + 0x4C]
		lea		ecx, [esp + 0x4C]
		mov		edx, [esp + 0x74]
		pushad
		pushfd
		push	edx
		push	ecx
		call	SetShadowDistanceValue
		add		esp, 8
		popfd
		popad
		jmp		kSetShadowDistanceReturn
	}
}

static __declspec(naked) void SetShadowDistanceShader()
{
	__asm
	{
		lea		ecx, [esp + 0xE0 - 0xC4 + 4]
		pushad
		pushfd
		push	0
		push	ecx
		call	SetShadowDistanceValue
		add		esp, 8
		popfd
		popad
		mov		ecx, [esp + 0xE0 - 0xC4 + 4]
		mov		[esp + esi * 4 + 0xE0 - 0x98], ecx
		jmp		kSetShadowDistanceShaderReturn
	}
}

static __declspec(naked) void FixSunFlags()
{
	static int max = 0;

	__asm
	{
		or		eax, 0x4002
		add		eax, 0x2B
		push	eax
		mov		eax, [esp + 0x90 - 0x74]
		mov		max, eax
		mov		eax, 0x1BA7680
		mov		eax, [eax]
		mov		eax, [eax + 0x138]
		cmp		max, eax
		je		loc_fix
		jmp		kFixSunFlagsReturn

	loc_fix:
		pop		eax
		mov		eax, 0x0040402D
		push	eax
		jmp		kFixSunFlagsReturn
	}
}

#endif

void (__cdecl * ProcessImageSpaceShaders)(NiDX9Renderer*, BSRenderedTexture*, BSRenderedTexture*) = (void (__cdecl *)(NiDX9Renderer*, BSRenderedTexture*, BSRenderedTexture*))kProcessImageSpaceShaders;
void __cdecl TrackProcessImageSpaceShaders(NiDX9Renderer* Renderer, BSRenderedTexture* RenderedTexture1, BSRenderedTexture* RenderedTexture2) {
	
	BSRenderedTexture* MenuRenderedTexture = *(BSRenderedTexture**)kMenuRenderedTexture;
	
	if (TheRenderManager->BackBuffer) TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface = TheRenderManager->BackBuffer;
	ProcessImageSpaceShaders(Renderer, RenderedTexture1, RenderedTexture2);
	if ((!RenderedTexture2 || MenuRenderedTexture) && TheRenderManager->currentRTGroup) TheShaderManager->RenderEffects(TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface);
	if (TheRenderManager->IsSaveGameScreenShot) {
		if (MenuRenderedTexture)
			TheRenderManager->device->StretchRect(MenuRenderedTexture->RenderTargetGroup->RenderTargets[0]->data->Surface, NULL, TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface, &TheRenderManager->SaveGameScreenShotRECT, D3DTEXF_NONE);
		else
			TheRenderManager->device->StretchRect(TheRenderManager->defaultRTGroup->RenderTargets[0]->data->Surface, NULL, TheRenderManager->currentRTGroup->RenderTargets[0]->data->Surface, &TheRenderManager->SaveGameScreenShotRECT, D3DTEXF_NONE);
	}

}

static __declspec(naked) void RenderInterface()
{
	
	__asm
	{
#if defined(NEWVEGAS)
		pushad
		call	RenderMainMenuMovie
		popad
#endif
		call	kRenderInterfaceMethod
		pushad
		mov		ecx, TheGameMenuManager
		call	GameMenuManager::Render
		popad
		jmp		kRenderInterfaceReturn
	}

}

void CreateRenderHook() {

	*((int *)&InitializeRenderer)			= kInitializeRenderer;
	TrackInitializeRenderer					= &RenderHook::TrackInitializeRenderer;
	*((int *)&Render)						= kRender;
	TrackRender								= &RenderHook::TrackRender;
	*((int *)&BeginScene)					= kBeginScene;
	TrackBeginScene							= &RenderHook::TrackBeginScene;
#if defined(NEWVEGAS)
	*((int *)&RenderWorldSceneGraph)		= 0x00873200;
	TrackRenderWorldSceneGraph				= &RenderHook::TrackRenderWorldSceneGraph;
	*((int *)&GetWaterHeightLOD)			= 0x0045CD80;
	TrackGetWaterHeightLOD					= &RenderHook::TrackGetWaterHeightLOD;
#elif defined(OBLIVION)
	*((int *)&SetupShaderPrograms)			= 0x0077A1F0;
	TrackSetupShaderPrograms				= &RenderHook::TrackSetupShaderPrograms;
	*((int *)&EndTargetGroup)				= 0x007AAA30;
	TrackEndTargetGroup						= &RenderHook::TrackEndTargetGroup;
	*((int *)&HDRRender)					= 0x007BDFC0;
	TrackHDRRender							= &RenderHook::TrackHDRRender;
	*((int *)&Culling)						= 0x0070AB40;
	TrackCulling							= &RenderHook::TrackCulling;
	*((int *)&CullingBSFadeNode)			= 0x004A0920;
	TrackCullingBSFadeNode					= &RenderHook::TrackCullingBSFadeNode;
	*((int *)&FarPlane)						= 0x00410EE0;
	TrackFarPlane							= &RenderHook::TrackFarPlane;
	*((int *)&PrepareTextureForRendering)	= 0x0077AC90;
	TrackPrepareTextureForRendering			= &RenderHook::TrackPrepareTextureForRendering;
	*((int *)&SetSamplerState)				= 0x0077B610;
	TrackSetSamplerState					= &RenderHook::TrackSetSamplerState;
#elif defined(SKYRIM)
	*((int *)&SetupRenderingPass)			= 0x00CC4E80;
	TrackSetupRenderingPass					= &RenderHook::TrackSetupRenderingPass;
	*((int *)&RenderWorldSceneGraph)		= 0x00692290;
	TrackRenderWorldSceneGraph				= &RenderHook::TrackRenderWorldSceneGraph;
#endif

    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)InitializeRenderer,			*((PVOID *)&TrackInitializeRenderer));
	DetourAttach(&(PVOID&)Render,						*((PVOID *)&TrackRender));
	DetourAttach(&(PVOID&)BeginScene,					*((PVOID *)&TrackBeginScene));
	DetourAttach(&(PVOID&)ProcessImageSpaceShaders,				   &TrackProcessImageSpaceShaders);
#if defined(NEWVEGAS)
	DetourAttach(&(PVOID&)RenderWorldSceneGraph,		*((PVOID *)&TrackRenderWorldSceneGraph));
	DetourAttach(&(PVOID&)GetWaterHeightLOD,			*((PVOID *)&TrackGetWaterHeightLOD));
	DetourAttach(&(PVOID&)SetupRenderingPass,					   &TrackSetupRenderingPass);
	DetourAttach(&(PVOID&)SetShaderPackageSelector,				   &TrackSetShaderPackageSelector);
#elif defined(OBLIVION)
	DetourAttach(&(PVOID&)SetupShaderPrograms,			*((PVOID *)&TrackSetupShaderPrograms));
	DetourAttach(&(PVOID&)EndTargetGroup,				*((PVOID *)&TrackEndTargetGroup));
	DetourAttach(&(PVOID&)HDRRender,					*((PVOID *)&TrackHDRRender));
	DetourAttach(&(PVOID&)Culling,						*((PVOID *)&TrackCulling));
	DetourAttach(&(PVOID&)CullingBSFadeNode,			*((PVOID *)&TrackCullingBSFadeNode));
	DetourAttach(&(PVOID&)FarPlane,						*((PVOID *)&TrackFarPlane));
	DetourAttach(&(PVOID&)PrepareTextureForRendering,	*((PVOID *)&TrackPrepareTextureForRendering));
	DetourAttach(&(PVOID&)SetSamplerState,				*((PVOID *)&TrackSetSamplerState));
	DetourAttach(&(PVOID&)SaveGameScreenshot,					   &TrackSaveGameScreenshot);
	DetourAttach(&(PVOID&)SetShaderPackageSelector,				   &TrackSetShaderPackageSelector);
	DetourAttach(&(PVOID&)RenderObject,							   &TrackRenderObject);
#elif defined(SKYRIM)
	DetourAttach(&(PVOID&)SetupRenderingPass,			*((PVOID *)&TrackSetupRenderingPass));
	DetourAttach(&(PVOID&)RenderWorldSceneGraph,		*((PVOID *)&TrackRenderWorldSceneGraph));
#endif
    DetourTransactionCommit();

	WriteRelJump(kRenderInterface, (UInt32)RenderInterface);
	
#if defined(NEWVEGAS)
	WriteRelJump(0x004E4C3B, 0x004E4C42); // Needs to fix reflections when cell water height is not like worldspace water height
	WriteRelJump(0x004E4DA4, 0x004E4DAC); // Needs to fix reflections on distant water
	SafeWrite32(0x00E7624D, 0xBC4); // Extends the NiDX9Renderer allocation from size 0xB80 to 0xBC4 to store additional data
	WriteRelJump(kClearDepth,					(UInt32)ClearDepth);
	WriteRelJump(kRenderFirstPersonNode,		(UInt32)RenderFirstPersonNode);
	WriteRelCall(kMultiBoundWaterHeightFix1,	(UInt32)MultiBoundWaterHeightFix);
	WriteRelCall(kMultiBoundWaterHeightFix2,	(UInt32)MultiBoundWaterHeightFix);
	if (TheSettingManager->SettingsMain.Main.ReplaceIntro) WriteRelJump(kSetTileShaderConstants, (UInt32)SetTileShaderConstants);
#elif defined(OBLIVION)
	SafeWrite32(0x0076BD75, 0xB44); // Extends the NiDX9Renderer allocation from size 0xB00 to 0xB44 to store additional data
	SafeWrite32(0x0049BFAF, TheSettingManager->SettingsMain.Main.WaterReflectionMapSize); // Constructor
	SafeWrite32(0x007C1045, TheSettingManager->SettingsMain.Main.WaterReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C104F, TheSettingManager->SettingsMain.Main.WaterReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C10F9, TheSettingManager->SettingsMain.Main.WaterReflectionMapSize); // RenderedSurface
	SafeWrite32(0x007C1103, TheSettingManager->SettingsMain.Main.WaterReflectionMapSize); // RenderedSurface
	SafeWrite8(0x00A38280, 0x5A); // Fixes the "purple water bug"
	SafeWrite8(0x0040CE11, 0); // Stops to clear the depth buffer when rendering the 1st person node
	if (TheSettingManager->SettingsMain.Main.AnisotropicFilter >= 2) {
		SafeWrite8(0x007BE1D3, TheSettingManager->SettingsMain.Main.AnisotropicFilter);
		SafeWrite8(0x007BE32B, TheSettingManager->SettingsMain.Main.AnisotropicFilter);
	}
	*LocalWaterHiRes = 1; //Fixes a bug on the WaterHeightMapConstructor (the constructor is called before initializing the value with the bUseWaterHiRes ini value)
#elif defined(SKYRIM)
	SafeWrite32(0x00CDB659, 0x8C4); // Extends the NiDX9Renderer allocation from size 0x880 to 0x8C4 to store additional data
	WriteRelJump(kClearDepth,				(UInt32)ClearDepth);
	WriteRelJump(kRenderFirstPersonNode,	(UInt32)RenderFirstPersonNode);
	if (TheSettingManager->SettingsMain.ShadowMode.Enabled) {
		WriteRelJump(kSetShadowDistance,		(UInt32)SetShadowDistance);
		WriteRelJump(kSetShadowDistanceShader,	(UInt32)SetShadowDistanceShader);
		if (TheSettingManager->SettingsMain.ShadowMode.MultiPointsLighting) {
			WriteRelJump(0x0069A7FF,	0x0069A8A7);
			WriteRelJump(kFixSunFlags,	(UInt32)FixSunFlags);
		}
	}
#endif

}
