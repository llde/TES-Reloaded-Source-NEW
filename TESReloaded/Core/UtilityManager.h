#pragma once

class UtilityManager {
public:
	UtilityManager();

	bool								IsVanityView();
	void								SetCrosshair(bool Enabled);
	bool								ShowMessageBox(const char* Message, void* Callback, const char* Button0, const char* Button1 = NULL, const char* Button2 = NULL, const char* Button3 = NULL, const char* Button4 = NULL, const char* Button5 = NULL, const char* Button6 = NULL, const char* Button7 = NULL, const char* Button8 = NULL, const char* Button9 = NULL);
	void								ShowMessage(const char* Message);
	void								MatrixMultiply(NiMatrix33* ss, NiMatrix33* sm1, NiMatrix33* sm2);
	void								MatrixVectorMultiply(NiPoint3* r, NiMatrix33* sm, NiPoint3* v);
	void								GenerateRotationMatrixZXY(NiMatrix33* m, NiPoint3* v, bool degrees);
	float								RadiansToDegrees(float radians);
	float								DegreesToRadians(float degrees);
	void								NormalizeVector(D3DXVECTOR4* vector);
#if defined(OBLIVION)
	UInt8								GetAnimSequence(NiTMap<UInt32, AnimSequenceBase>* AnimsMap, UInt16 AnimGroupKey, AnimSequenceBase** AnimSequence);
#elif defined(SKYRIM)
	void								QueueNiNodeUpdate(Actor* Act);
	void								UpdateOverShoulder(PlayerCamera* Camera, bool IsWeaponOut);
	bool								IsCamSwitchControlEnabled(PlayerControls* Controls);
	void								SetCameraState(TESCameraState* State);
	BSFixedString*						CreateBSString(BSFixedString* FixedString, char* Value);
	void								DisposeBSString(BSFixedString* FixedString);
#endif

private:
	class NiMatrix33L { public: float data[9]; };

};