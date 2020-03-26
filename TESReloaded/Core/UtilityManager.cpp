UtilityManager::UtilityManager() {
	
	Logger::Log("Starting the utility manager...");
	TheUtilityManager = this;

}

bool UtilityManager::IsVanityView() {

#if defined(NEWVEGAS)
	return *(bool*)0x011E07B8;
#elif defined(OBLIVION)
	return *(bool*)0x00B3BB04;
#elif defined(SKYRIM)
	return false;
#endif

}

void UtilityManager::SetCrosshair(bool Enabled) {
	
#if defined(NEWVEGAS)
	HUDMainMenu **HMainMenu = (HUDMainMenu**)0x11D96C0;
	(*HMainMenu)->crosshair->SetFloat(0x0FA3, (float)Enabled);
#elif defined(OBLIVION)
	void (__cdecl* SetCrossHair)(UInt32) = (void (__cdecl*)(UInt32))0x00578CF0;
	SetCrossHair(Enabled);
#elif defined(SKYRIM)
	
#endif

}

bool UtilityManager::ShowMessageBox(const char* Message, void* Callback, const char* Button0, const char* Button1, const char* Button2, const char* Button3, const char* Button4, const char* Button5, const char* Button6, const char* Button7, const char* Button8, const char* Button9) {
	
#if defined(NEWVEGAS)
	return ShowUIMessageBox(Message, 0, 0, Callback, 0, 0x17, 0.0f, 0.0f, Button0, Button1, Button2, Button3, Button4, Button5, Button6, Button7, Button8, Button9, NULL);
#elif defined(OBLIVION)
	return ShowUIMessageBox(Message, Callback, 1, Button0, Button1, Button2, Button3, Button4, Button5, Button6, Button7, Button8, Button9, NULL);
#elif defined(SKYRIM)
	bool (__cdecl* ShowUIMessageBox)(const char*, void*, UInt32, UInt32, UInt32, ...) = (bool (__cdecl*)(const char*, void*, UInt32, UInt32, UInt32, ...))0x0087AC60;
	return ShowUIMessageBox(Message, Callback, 1, 25, 4, *MessageBoxButtonYes, *MessageBoxButtonNo, NULL);
#endif

}

void UtilityManager::ShowMessage(const char* Message) {

#if defined(NEWVEGAS)
	ShowUIMessage(Message, 0, NULL, NULL, 2.0f, 0);
#elif defined(OBLIVION)
	ShowUIMessage(Message, NULL, 1, 2.0f);
#elif defined(SKYRIM)
	void (__cdecl* ShowUIMessage)(const char*, const char*, bool) = (void (__cdecl*)(const char*, const char*, bool))0x008997A0;
	return ShowUIMessage(Message, NULL, 1);
#endif
}

void UtilityManager::MatrixMultiply(NiMatrix33* ss, NiMatrix33* sm1, NiMatrix33* sm2) {

	NiMatrix33L* s = (NiMatrix33L*)ss;
	NiMatrix33L* m1 = (NiMatrix33L*)sm1;
	NiMatrix33L* m2 = (NiMatrix33L*)sm2;

	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) {
			s->data[3 * y + x] = 0;
			for (int i = 0; i < 3; i++) {
				s->data[3 * y + x] += m1->data[3 * y + i] * m2->data[3 * i + x];
			}
		}
	}

}

void UtilityManager::MatrixVectorMultiply(NiPoint3* r, NiMatrix33* sm, NiPoint3* v) {
	
	NiMatrix33L* m = (NiMatrix33L*)sm;

	r->x = m->data[0] * v->x + m->data[1] * v->y + m->data[2] * v->z;
	r->y = m->data[3] * v->x + m->data[4] * v->y + m->data[5] * v->z;
	r->z = m->data[6] * v->x + m->data[7] * v->y + m->data[8] * v->z;

}

void UtilityManager::GenerateRotationMatrixZXY(NiMatrix33* sm, NiPoint3* v, bool degrees) {
	
	NiMatrix33L* m = (NiMatrix33L*)sm;
	float a = v->x;
	float b = v->y;
	float c = v->z;

	if (degrees) {
		a = DegreesToRadians(a);
		b = DegreesToRadians(b);
		c = DegreesToRadians(c);
	}
	m->data[0] = cos(a) * cos(c) - sin(a) * sin(b) * sin(c);
	m->data[1] = -cos(b) * sin(a);
	m->data[2] = cos(a) * sin(c) + cos(c) * sin(a) * sin(b);
	m->data[3] = cos(c) * sin(a) + cos(a) * sin(b) * sin(c);
	m->data[4] = cos(a) * cos(b);
	m->data[5] = sin(a) * sin(c) - cos(a) * cos(c) * sin(b);
	m->data[6] = -cos(b) * sin(c);
	m->data[7] = sin(b);
	m->data[8] = cos(b) * cos(c);

}

float UtilityManager::RadiansToDegrees(float radians)
{
	return radians * 180.0f / M_PI;
}

float UtilityManager::DegreesToRadians(float degrees) {

	return degrees * M_PI / 180.0f;

}

void UtilityManager::NormalizeVector(D3DXVECTOR4* vector) {
	
	float len = sqrt((vector->x * vector->x) + (vector->y * vector->y) + (vector->z * vector->z));
	if (len) {
		vector->x = vector->x / len;
		vector->y = vector->y / len;
		vector->z = vector->z / len;
	}
	else {
		vector->x = 0.0f;
		vector->y = 0.0f;
		vector->z = 1.0f;
	}

}
#if defined(OBLIVION)
UInt8 UtilityManager::GetAnimSequence(NiTMap<UInt32, AnimSequenceBase>* AnimsMap, UInt16 AnimGroupKey, AnimSequenceBase** AnimSequence) {

	return (UInt8)ThisCall(0x00470960, AnimsMap, AnimGroupKey, AnimSequence);

}
#elif defined(SKYRIM)
void UtilityManager::QueueNiNodeUpdate(Actor* Act)
{
	ThisCall(0x00730EE0, Act, 0);
}

void UtilityManager::UpdateOverShoulder(PlayerCamera* Camera, bool IsWeaponOut)
{
	ThisCall(0x0083C7E0, Camera, IsWeaponOut);
}

bool UtilityManager::IsCamSwitchControlEnabled(PlayerControls* Controls)
{
	return ThisCall(0x00772A20, Controls);
}

void UtilityManager::SetCameraState(TESCameraState* State)
{
	ThisCall(0x006533D0, State->camera, State->camera->thirdPersonState2);
}

BSFixedString* UtilityManager::CreateBSString(BSFixedString* FixedString, char* Value)
{
	return (BSFixedString*)ThisCall(0x00A511C0, FixedString, Value);
}

void UtilityManager::DisposeBSString(BSFixedString* FixedString)
{
	ThisCall(0x00A511B0, FixedString);
}
#endif