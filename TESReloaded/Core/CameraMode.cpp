#include "CameraMode.h"

#if defined(NEWVEGAS)
#define kSetDialogCamera 0x00953060
#define kUpdateCameraCollisions 0x0094A0C0
#define PlayerNode Player->renderData->niNode
#define kAction_AttackBow kAction_Attack_Latency
#define kAction_AttackBowArrowAttached kAction_Attack_Latency
static const UInt32 kUpdateCameraHook = 0x0094BDDA;
static const UInt32 kUpdateCameraReturn = 0x0094BDDF;
static const UInt32 kThirdPersonCameraHook = 0x00945C2D;
static const UInt32 kThirdPersonCameraReturn = 0x00945C34;
static const UInt32 kOnCameraPOVHook = 0x00942DC5;
static const UInt32 kOnCameraPOVReturn = 0x00942DCE;
static const UInt32 kCrosshairHook = 0x00000000;
static const UInt32 kCrosshairReturn1 = 0x00000000;
static const UInt32 kCrosshairReturn2 = 0x00000000;
#elif defined(OBLIVION)
#define kSetDialogCamera 0x0066C6F0
#define kUpdateCameraCollisions 0x0065F080
#define PlayerNode Player->niNode
static const UInt32 kUpdateCameraHook = 0x0066BE6E;
static const UInt32 kUpdateCameraReturn = 0x0066BE7C;
static const UInt32 kRenderFirstPersonHook = 0x0040CE48;
static const UInt32 kCrosshairHook = 0x00673421;
static const UInt32 kCrosshairReturn1 = 0x0067342A;
static const UInt32 kCrosshairReturn2 = 0x00673440;
#endif
static UInt8 Crosshair = 0;
static HighProcess* DialogActorProcess = NULL;

#if defined(OBLIVION) || defined(NEWVEGAS)
class CameraMode {

public:
	void TrackSetDialogCamera(Actor* Act, float Arg2, UInt8 Arg3);
	void TrackUpdateCameraCollisions(NiPoint3* CameraLocalPos, NiPoint3* PlayerWorldPos, UInt8 CameraChasing);

};

void (__thiscall CameraMode::* SetDialogCamera)(Actor*, float, UInt8);
void (__thiscall CameraMode::* TrackSetDialogCamera)(Actor*, float, UInt8);
void CameraMode::TrackSetDialogCamera(Actor* Act, float Arg2, UInt8 Arg3) {

	DialogActorProcess = (HighProcess*)Act->process;

}

void (__thiscall CameraMode::* UpdateCameraCollisions)(NiPoint3*, NiPoint3*, UInt8);
void (__thiscall CameraMode::* TrackUpdateCameraCollisions)(NiPoint3*, NiPoint3*, UInt8);
void CameraMode::TrackUpdateCameraCollisions(NiPoint3* CameraPosition, NiPoint3* PlayerPosition, UInt8 CameraChasing) {
	
	UInt8 DisableFading = Player->DisableFading;
	UInt8 SitSleepState = Player->GetSitSleepState();

	if (SitSleepState >= 8 && SitSleepState <= 10) Player->DisableFading = 1;
	if (TheRenderManager->FirstPersonView) {
		Player->DisableFading = 1;
		CameraChasing = !TheSettingManager->SettingsMain.CameraMode.ChasingFirst;
	}
	else {
		CameraChasing = !TheSettingManager->SettingsMain.CameraMode.ChasingThird;
	}
	(this->*UpdateCameraCollisions)(CameraPosition, PlayerPosition, CameraChasing);
	Player->DisableFading = DisableFading;

}

static NiPoint3 From = { 0.0f, 0.0f, 0.0f };
static NiPoint3 FromOffset = { 0.0f, 0.0f, 0.0f };
void UpdateCamera(NiAVObject* CameraNode, NiPoint3* LocalPosition) {
	
	bool CameraMode = TheSettingManager->SettingsMain.CameraMode.Enabled;
	UInt8 Crosshair = TheSettingManager->SettingsMain.CameraMode.Crosshair;
	NiPoint3* CameraPosition = &CameraNode->m_localTransform.pos;
	UInt8 SitSleepState = Player->GetSitSleepState();
	HighProcess* Proc = (HighProcess*)Player->process;

	if (Crosshair > 0) {
		if (Crosshair == 1) {
			TheUtilityManager->SetCrosshair(0);
		}
		else {
			SInt16 CurrentAction = Proc->currentAction;
			if (CurrentAction == HighProcess::kAction_AttackBow || CurrentAction == HighProcess::kAction_AttackBowArrowAttached)
				TheUtilityManager->SetCrosshair(1);
			else
				TheUtilityManager->SetCrosshair(0);
		}
	}
	if (SitSleepState < 8 || SitSleepState > 10) From.x = 0.0f;
	if (SitSleepState >= 8 && SitSleepState <= 10) {
		NiPoint3 v;
		NiMatrix33 mw, ml;
		float x, y, z, r;
		NiPoint3 Rot = { 0.0f, 0.0f, 0.0f };
		if (From.x == 0.0f) {
			From.x = CameraPosition->x;
			From.y = CameraPosition->y;
			From.z = CameraPosition->z - 20;
		}
		else {
			FromOffset = { 0.0f, 0.0f, 0.0f };
			if (TheKeyboardManager->OnControlPressed(2))
				FromOffset.x -= 5.0f;
			else if (TheKeyboardManager->OnControlPressed(3))
				FromOffset.x += 5.0f;
			if (TheKeyboardManager->OnControlPressed(0))
				FromOffset.y += 5.0f;
			else if (TheKeyboardManager->OnControlPressed(1))
				FromOffset.y -= 5.0f;
			if (TheKeyboardManager->OnControlPressed(4))
				FromOffset.z += 5.0f;
			else if (TheKeyboardManager->OnControlPressed(6))
				FromOffset.z -= 5.0f;
			if (FromOffset.x != 0.0f || FromOffset.y != 0.0f || FromOffset.z != 0.0f) {
				NiPoint3 r;
				TheUtilityManager->MatrixVectorMultiply(&r, &CameraNode->m_worldTransform.rot, &FromOffset);
				From.x += r.x;
				From.y += r.y;
				From.z += r.z;
			}
		}
		CameraPosition->x = From.x;
		CameraPosition->y = From.y;
		CameraPosition->z = From.z;
		NiPoint3* HeadPosition = &Proc->animData->nHead->m_worldTransform.pos;
		TheUtilityManager->GenerateRotationMatrixZXY(&mw, &Rot, 1);
		x = CameraPosition->x - HeadPosition->x;
		y = CameraPosition->y - HeadPosition->y;
		z = CameraPosition->z - HeadPosition->z;
		r = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		Rot.x = (atan2(y, x) * 180 / M_PI) + 90;
		Rot.y = (acos(z / r) * 180 / M_PI) - 90;
		Rot.z = 0;
		TheUtilityManager->GenerateRotationMatrixZXY(&ml, &Rot, 1);
		CameraNode->m_worldTransform.rot = mw;
		CameraNode->m_localTransform.rot = ml;
	}
	else if (CameraMode && (MenuManager->IsActive(Menu::MenuType::kMenuType_Dialog) || MenuManager->IsActive(Menu::MenuType::kMenuType_Persuasion))) {
		NiPoint3 v;
		NiMatrix33 mw, ml;
		float x, y, z, r;
		NiPoint3 Rot = { 0.0f, 0.0f, 0.0f };
		NiPoint3* HeadPosition = &Proc->animData->nHead->m_worldTransform.pos;
		TheUtilityManager->MatrixVectorMultiply(&v, &PlayerNode->m_worldTransform.rot, &TheSettingManager->SettingsMain.CameraMode.DialogOffset);
		CameraPosition->x = HeadPosition->x + v.x;
		CameraPosition->y = HeadPosition->y + v.y;
		CameraPosition->z = HeadPosition->z + v.z;
		HeadPosition = &DialogActorProcess->animData->nHead->m_worldTransform.pos;
		TheUtilityManager->GenerateRotationMatrixZXY(&mw, &Rot, 1);
		x = CameraPosition->x - HeadPosition->x;
		y = CameraPosition->y - HeadPosition->y;
		z = CameraPosition->z - HeadPosition->z;
		r = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		Rot.x = (atan2(y, x) * 180 / M_PI) + 90;
		Rot.y = (acos(z / r) * 180 / M_PI) - 90;
		Rot.z = 0;
		TheUtilityManager->GenerateRotationMatrixZXY(&ml, &Rot, 1);
		CameraNode->m_worldTransform.rot = mw;
		CameraNode->m_localTransform.rot = ml;
	}
	else if (CameraMode && !TheUtilityManager->IsVanityView()) {
		if (!Player->isThirdPerson) {
			if (!Proc->KnockedState && SitSleepState != 3 && SitSleepState != 5 && SitSleepState != 8 && SitSleepState != 9 && SitSleepState != 10) {
				NiPoint3* HeadPosition = &Proc->animData->nHead->m_worldTransform.pos;
				NiPoint3 r;
				TheUtilityManager->MatrixVectorMultiply(&r, &PlayerNode->m_worldTransform.rot, &TheSettingManager->SettingsMain.CameraMode.Offset);
				CameraPosition->x = HeadPosition->x + r.x;
				CameraPosition->y = HeadPosition->y + r.y;
				CameraPosition->z = HeadPosition->z + r.z;
				#if defined(NEWVEGAS) // to do: find it in oblivion!
				Player->ReticleOffset.x = r.x;
				Player->ReticleOffset.y = r.y;
				Player->ReticleOffset.z = r.z;
				#endif
			}
		}
	}
	LocalPosition->x = CameraPosition->x;
	LocalPosition->y = CameraPosition->y;
	LocalPosition->z = CameraPosition->z;

}

static __declspec(naked) void UpdateCameraHook()
{

	__asm
	{
#if defined(NEWVEGAS)
		push	0
		push	0
		push	ecx
		pushad
		lea		edx, [ebp - 0x60]
		push	edx
		push	eax
		call	UpdateCamera
		pop		eax
		pop		edx
		popad
#elif defined (OBLIVION)
		pushad
		lea		ecx, [esp + 0x58]
		push	ecx
		push	eax
		call	UpdateCamera
		pop		eax
		pop		ecx
		popad
#endif
		jmp		kUpdateCameraReturn
	}

}

void CreateCameraModeHook() {

	*((int *)&SetDialogCamera)				= kSetDialogCamera;
	TrackSetDialogCamera					= &CameraMode::TrackSetDialogCamera;
	*((int *)&UpdateCameraCollisions)		= kUpdateCameraCollisions;
	TrackUpdateCameraCollisions				= &CameraMode::TrackUpdateCameraCollisions;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)SetDialogCamera,			*((PVOID *)&TrackSetDialogCamera));
	DetourAttach(&(PVOID&)UpdateCameraCollisions,	*((PVOID *)&TrackUpdateCameraCollisions));
	DetourTransactionCommit();
	WriteRelJump(kUpdateCameraHook,			(UInt32)UpdateCameraHook);
#if defined(OBLIVION)
	WriteRelJump(0x0066B769, 0x0066B795); // Does not lower the player Z axis value (fixes the bug of the camera on feet after resurrection)

	Crosshair = TheSettingManager->SettingsMain.CameraMode.Crosshair;
#elif defined(NEWVEGAS)
	WriteRelJump(0x00761DE7, 0x00761DF4); // Avoids to toggle the body
	WriteRelJump(0x0093FC04, 0x0093FC3B); // Avoids to toggle the body
	WriteRelJump(0x00950244, 0x0095027E); // Avoids to toggle the body
#endif
}

void CreateCameraModeSleepingHook() {

	*((int *)&UpdateCameraCollisions)	= kUpdateCameraCollisions;
	TrackUpdateCameraCollisions			= &CameraMode::TrackUpdateCameraCollisions;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)UpdateCameraCollisions,	*((PVOID *)&TrackUpdateCameraCollisions));
	DetourTransactionCommit();

	WriteRelJump(kUpdateCameraHook, (UInt32)UpdateCameraHook);

}

#elif defined (SKYRIM)
#include "skse\GameReferences.h"
#include "skse\NiNodes.h"
#include "skse\GameCamera.h"

static bool TogglePOV = false;

class CameraMode {

public:
	int TrackSetCameraState(TESCameraState* CameraState);
	void TrackManageButtonEvent(ButtonEvent* Event, int Arg2);
	void TrackSetCameraPosition();

};

int (__thiscall CameraMode::* SetCameraState)(TESCameraState*);
int (__thiscall CameraMode::* TrackSetCameraState)(TESCameraState*);
int CameraMode::TrackSetCameraState(TESCameraState* CameraState) {
	
	PlayerCamera* Camera = (PlayerCamera*)this;
	bool IsWeaponOut = false;

	if (Camera->cameraNode->m_name && CameraState->camera->thirdPersonState2 != NULL) {
		if (CameraState->stateId == PlayerCamera::kCameraState_FirstPerson) {
			if (TheRenderManager->FirstPersonView && TogglePOV) {
				CameraState = Camera->thirdPersonState2;
				TheRenderManager->FirstPersonView = false;
			}
			else {
				CameraState = Camera->thirdPersonState2;
				TheRenderManager->FirstPersonView = true;
			}
		}
		else if (CameraState->stateId == PlayerCamera::kCameraState_ThirdPerson2) TheRenderManager->FirstPersonView = false;
		if (TheRenderManager->FirstPersonView && CameraState->stateId != PlayerCamera::kCameraState_ThirdPerson2) TheRenderManager->FirstPersonView = false;
		if (!TheRenderManager->FirstPersonView && CameraState->stateId == PlayerCamera::kCameraState_ThirdPerson2) {
			IsWeaponOut = (*g_thePlayer)->actorState.IsWeaponDrawn();
			Camera->AllowVanityMode = !IsWeaponOut;
			TheUtilityManager->UpdateOverShoulder(Camera, IsWeaponOut);
		}
		TogglePOV = false;
	}
	return (this->*SetCameraState)(CameraState);

}

void (__thiscall CameraMode::* ManageButtonEvent)(ButtonEvent*, int);
void (__thiscall CameraMode::* TrackManageButtonEvent)(ButtonEvent*, int);
void CameraMode::TrackManageButtonEvent(ButtonEvent* Event, int Arg2) {
	
	ThirdPersonState* State = (ThirdPersonState*)(this - 0x10); //ecx is ThirdPersonState for PlayerInputHandler (class is "shifted" due to the multi inheritance)
	
	(this->*ManageButtonEvent)(Event, Arg2);
	if (State->stateId == PlayerCamera::kCameraState_ThirdPerson2) {
		PlayerControls* Controls = PlayerControls::GetSingleton();
		if ((UInt8)TheUtilityManager->IsCamSwitchControlEnabled(Controls)) {
			if (State->TogglePOV) TogglePOV = true;
			if (TheRenderManager->FirstPersonView && *Event->GetControlID() == InputStringHolder::GetSingleton()->zoomOut) TheUtilityManager->SetCameraState(State);
		}
	}

}

void (__thiscall CameraMode::* SetCameraPosition)();
void (__thiscall CameraMode::* TrackSetCameraPosition)();
void CameraMode::TrackSetCameraPosition() {

	ThirdPersonState* State = (ThirdPersonState*)(this);
	
	if (TheRenderManager->FirstPersonView) {
		BSFixedString Head; TheUtilityManager->CreateBSString(&Head, "NPC Head [Head]");
		NiNode* ActorNode = (*g_thePlayer)->GetNiRootNode(0);
		NiPoint3* HeadPosition = &ActorNode->GetObjectByName(&Head)->m_worldTransform.pos;
		NiPoint3 v;
		TheUtilityManager->MatrixVectorMultiply(&v, &ActorNode->m_worldTransform.rot, &TheSettingManager->SettingsMain.CameraMode.Offset);
		State->CameraPosition.x = HeadPosition->x + v.x;
		State->CameraPosition.y = HeadPosition->y + v.y;
		State->CameraPosition.z = HeadPosition->z + v.z;
		State->OverShoulderPosX = State->OverShoulderPosY = State->OverShoulderPosZ = 0.0f;
		State->camera->AllowVanityMode = 0;
		TheUtilityManager->DisposeBSString(&Head);
	}
	(this->*SetCameraPosition)();
	
}

void CreateCameraModeHook()
{

	*((int *)&SetCameraState)			= 0x006533D0;
	TrackSetCameraState					= &CameraMode::TrackSetCameraState;
	*((int *)&ManageButtonEvent)		= 0x00840BE0;
	TrackManageButtonEvent				= &CameraMode::TrackManageButtonEvent;
	*((int *)&SetCameraPosition)		= 0x0083F690;
	TrackSetCameraPosition				= &CameraMode::TrackSetCameraPosition;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)SetCameraState,		*((PVOID *)&TrackSetCameraState));
	DetourAttach(&(PVOID&)ManageButtonEvent,	*((PVOID *)&TrackManageButtonEvent));
	DetourAttach(&(PVOID&)SetCameraPosition,	*((PVOID *)&TrackSetCameraPosition));
	DetourTransactionCommit();
	
	SafeWrite8(0x0083F69B, 0); // Stops PlayerCharacter fading

}
#endif