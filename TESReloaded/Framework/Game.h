#pragma once

#include "GameNi.h"
#include "GameHavok.h"

class ModInfo;
class Actor;
class ActorAnimData;
class MagicItem;
class MagicTarget;
class CombatController;
class SpellItem;
class EffectNode;
class DialoguePackage;
class BirthSign;
class AlchemyItem;
class ActiveEffect;
class ModelKF;
class BaseProcess;
class Creature;
class SkinInfo;
class BoundObjectListHead;
class Character;
class WaterSurfaceManager;
class WaterPlaneData;
class Script;
class EnchantmentItem;
class ScriptEventList;
class ShadowSceneLight;
class Menu;
class ExtraDataList;
class MediaSet;
class MediaLocationController;
class Tile;
class TileText;

class TESForm;
class TESObjectREFR;
class TESObjectCELL;
class TESObjectBOOK;
class TESObjectARMO;
class TESObjectLIGH;
class TESObjectANIO;
class TESObjectLAND;
class TESPathGrid;
class TESTopic;
class TESTopicInfo;
class TESRegion;
class TESRegionList;
class TESQuest;
class TESClass;
class TESNPC;
class TESSound;
class TESHair;
class TESEyes;
class TESRace;
class TESLandTexture;
class TESFaction;
class TESCombatStyle;
class TESLoadScreen;
class TESEffectShader;
class TESRegionDataManager;
class TESPackageData;
class TESChildCell { public: virtual TESObjectCELL* GetChildCell(); }; assert(sizeof(TESChildCell) == 0x004);
class TESImageSpace;
class TESImageSpaceModifier;
class TESReputation;
class TESChallenge;
class TESRecipe;
class TESRecipeCategory;
class TESAmmoEffect;
class TESCasino;
class TESCaravanDeck;
class TESLoadScreenType;

class BSBound;
class BSFogProperty;
class BSRenderedTexture;
class BSTempNodeManager;
class BSAnimGroupSequence;
class BSFile;
class BSGameSound;
class BSSoundInfo;

class BGSHeadPart;
class BGSEncounterZone;
class BGSCameraShot;
class BGSAcousticSpace;
class BGSRagdoll;
class BGSVoiceType;
class BGSImpactData;
class BGSImpactDataSet;
class BGSProjectile;
class BGSExplosion;
class BGSRadiationStage;
class BGSDehydrationStage;
class BGSHungerStage;
class BGSSleepDeprivationStage;
class BGSDebris;
class BGSBodyPartData;
class BGSNote;
class BGSListForm;
class BGSMenuIcon;
class BGSMessage;
class BGSLightingTemplate;
class BGSMusicType;
class BGSAddonNode;

class CommandParam {
public:
	enum ParamType {
		kParamType_String			= 0x00,
		kParamType_Integer			= 0x01,
		kParamType_Float			= 0x02,
	};

	const char* typeStr;
	UInt32		typeID;		// ParamType
	UInt32		isOptional;
};
assert(sizeof(CommandParam) == 0x00C);

struct CommandArgs {
	CommandParam*	 paramInfo;		// 00
	void*			 arg1;			// 04
	TESObjectREFR*   thisObj;		// 08
	TESObjectREFR*	 Obj;			// 0C
	Script*			 scriptObj;		// 10
	ScriptEventList* eventList;		// 14
	double*			 result;		// 18
	UInt32*			 opcodeOffset;	// 1C
};
assert(sizeof(CommandArgs) == 0x020);

struct CommandInfo {
	const char*		longName;		// 00
	const char*		shortName;		// 04
	UInt32			opcode;			// 08
	const char*		helpText;		// 0C
	UInt16			needsParent;	// 10
	UInt16			numParams;		// 12
	CommandParam*	params;			// 14
	void*			execute;		// 18
	void*			parse;			// 1C
	void*			eval;			// 20
	UInt32			flags;			// 24
};
assert(sizeof(CommandInfo) == 0x028);

template <class Item>
class TList {
public:
	struct TNode {
		Item*	item;
		TNode*	next;

		Item*	Item() const { return item; }
		TNode*	Next() const { return next; }
	};

	class Iterator {
	public:
		TNode* m_cur;

		Iterator() : m_cur(NULL) {}
		Iterator(TNode* node) : m_cur(node) {}
		Iterator operator++() { if (!End()) m_cur = m_cur->Next(); return *this; }
		bool End() { return m_cur == NULL; }
		const Item* operator->() { return (m_cur) ? m_cur->Item() : NULL; }
		const Item* operator*() { return (m_cur) ? m_cur->Item() : NULL; }
		const Iterator& operator=(const Iterator& rhs) {
			m_cur = rhs.m_cur;
			return *this;
		}
		Item* Get() { return (m_cur) ? m_cur->Item() : NULL; }
	};

	const Iterator Begin() const { return Iterator(const_cast<TNode*>(&First)); }

	TNode First;
};
assert(sizeof(TList<void>) == 0x008);

class BSString {
public:
#if defined(OBLIVION)
	bool Set(const char* src) { return ThisCall(0x004028D0, this, src, 0); }
#endif
	char*	m_data;		// 00
	UInt16	m_dataLen;  // 04
	UInt16	m_bufLen;	// 06

};
assert(sizeof(BSString) == 0x008);

class RGBA {
public:
	UInt8	r;
	UInt8	g;
	UInt8	b;
	UInt8	a;
};
assert(sizeof(RGBA) == 0x004);

#if defined(NEWVEGAS)
class BSExtraData {
public:
	enum ExtraDataType {
		kExtraData_Havok = 0x01,
		kExtraData_Cell3D = 0x02,
		kExtraData_CellWaterType = 0x03,
		kExtraData_RegionList = 0x04,
		kExtraData_SeenData = 0x05,
		kExtraData_CellMusicType = 0x07,
		kExtraData_CellClimate = 0x08,
		kExtraData_ProcessMiddleLow = 0x09,
		kExtraData_CellCanopyShadowMask = 0x0A,
		kExtraData_DetachTime = 0x0B,
		kExtraData_PersistentCell = 0x0C,
		kExtraData_Script = 0x0D,
		kExtraData_Action = 0x0E,
		kExtraData_StartingPosition = 0x0F,
		kExtraData_Anim = 0x10,
		kExtraData_UsedMarkers = 0x12,
		kExtraData_DistantData = 0x13,
		kExtraData_RagdollData = 0x14,
		kExtraData_InventoryChanges = 0x15,
		kExtraData_Worn = 0x16,
		kExtraData_WornLeft = 0x17,
		kExtraData_PackageStartLocation = 0x18,
		kExtraData_Package = 0x19,
		kExtraData_TrespassPackage = 0x1A,
		kExtraData_RunOncePacks = 0x1B,
		kExtraData_ReferencePointer = 0x1C,
		kExtraData_Follower = 0x1D,
		kExtraData_LevCreaModifier = 0x1E,
		kExtraData_Ghost = 0x1F,
		kExtraData_OriginalReference = 0x20,
		kExtraData_Ownership = 0x21,
		kExtraData_Global = 0x22,
		kExtraData_Rank = 0x23,
		kExtraData_Count = 0x24,
		kExtraData_Health = 0x25,
		kExtraData_Uses = 0x26,
		kExtraData_TimeLeft = 0x27,
		kExtraData_Charge = 0x28,
		kExtraData_Light = 0x29,
		kExtraData_Lock = 0x2A,
		kExtraData_Teleport = 0x2B,
		kExtraData_MapMarker = 0x2C,
		kExtraData_LeveledCreature = 0x2E,
		kExtraData_LeveledItem = 0x2F,
		kExtraData_Scale = 0x30,
		kExtraData_Seed = 0x31,
		kExtraData_NonActorMagicCaster = 0x32,
		kExtraData_NonActorMagicTarget = 0x33,
		kExtraData_PlayerCrimeList = 0x35,
		kExtraData_EnableStateParent = 0x37,
		kExtraData_EnableStateChildren = 0x38,
		kExtraData_ItemDropper = 0x39,
		kExtraData_DroppedItemList = 0x3A,
		kExtraData_RandomTeleportMarker = 0x3B,
		kExtraData_MerchantContainer = 0x3C,
		kExtraData_SavedHavokData = 0x3D,
		kExtraData_CannotWear = 0x3E,
		kExtraData_Poison = 0x3F,
		kExtraData_Unk040 = 0x40,	// referenced during LoadFormInModule (in oposition to kExtraData_Light)
		kExtraData_LastFinishedSequence = 0x41,
		kExtraData_SavedAnimation = 0x42,
		kExtraData_NorthRotation = 0x43,
		kExtraData_XTarget = 0x44,
		kExtraData_FriendHits = 0x45,
		kExtraData_HeadingTarget = 0x46,
		kExtraData_RefractionProperty = 0x48,
		kExtraData_StartingWorldOrCell = 0x49,
		kExtraData_Hotkey = 0x4A,
		kExtraData_EditorRefMovedData = 0x4C,
		kExtraData_InfoGeneralTopic = 0x4D,
		kExtraData_HasNoRumors = 0x4E,
		kExtraData_Sound = 0x4F,
		kExtraData_TerminalState = 0x50,
		kExtraData_LinkedRef = 0x51,
		kExtraData_LinkedRefChildren = 0x52,
		kExtraData_ActivateRef = 0x53,
		kExtraData_ActivateRefChildren = 0x54,
		kExtraData_TalkingActor = 0x55,
		kExtraData_ObjectHealth = 0x56,
		kExtraData_DecalRefs = 0x57,
		kExtraData_CellImageSpace = 0x59,
		kExtraData_NavMeshPortal = 0x5A,
		kExtraData_ModelSwap = 0x5B,
		kExtraData_Radius = 0x5C,
		kExtraData_Radiation = 0x5D,
		kExtraData_FactionChanges = 0x5E,
		kExtraData_DismemberedLimbs = 0x5F,
		kExtraData_MultiBound = 0x61,
		kExtraData_MultiBoundData = 0x62,
		kExtraData_MultiBoundRef = 0x63,
		kExtraData_ReflectedRefs = 0x65,
		kExtraData_ReflectorRefs = 0x66,
		kExtraData_EmittanceSource = 0x67,
		kExtraData_RadioData = 0x68,
		kExtraData_CombatStyle = 0x69,
		kExtraData_Primitive = 0x6B,
		kExtraData_OpenCloseActivateRef = 0x6C,
		kExtraData_AnimNoteReciever = 0x6D,
		kExtraData_Ammo = 0x6E,
		kExtraData_PatrolRefData = 0x6F,
		kExtraData_PackageData = 0x70,
		kExtraData_OcclusionPlane = 0x71,
		kExtraData_CollisionData = 0x72,
		kExtraData_SayTopicInfoOnceADay = 0x73,
		kExtraData_EncounterZone = 0x74,
		kExtraData_SayToTopicInfo = 0x75,
		kExtraData_OcclusionPlaneRefData = 0x76,
		kExtraData_PortalRefData = 0x77,
		kExtraData_Portal = 0x78,
		kExtraData_Room = 0x79,
		kExtraData_HealthPerc = 0x7A,
		kExtraData_RoomRefData = 0x7B,
		kExtraData_GuardedRefData = 0x7C,
		kExtraData_CreatureAwakeSound = 0x7D,
		kExtraData_WaterZoneMap = 0x7E,
		kExtraData_IgnoredBySandbox = 0x80,
		kExtraData_CellAcousticSpace = 0x81,
		kExtraData_ReservedMarkers = 0x82,
		kExtraData_WeaponIdleSound = 0x83,
		kExtraData_WaterLightRefs = 0x84,
		kExtraData_LitWaterRefs = 0x85,
		kExtraData_WeaponAttackSound = 0x86,
		kExtraData_ActivateLoopSound = 0x87,
		kExtraData_PatrolRefInUseData = 0x88,
		kExtraData_AshPileRef = 0x89,
		kExtraData_CreatureMovementSound = 0x8A,
		kExtraData_FollowerSwimBreadcrumbs = 0x8B,
		//										= 0x8C,
		kExtraData_WeaponModFlags = 0x8D,
		//
		kExtraData_0x90 = 0x90,	// referenced in LoadGame but no data
		kExtraData_0x91 = 0x91,	// referenced in LoadGame but no data
		kExtraData_SpecialRenderFlags = 0x92
	};

	virtual bool	Compare(BSExtraData* compareWith);	// compare type, data, return true if not equal

	UInt8			type;		// 004
	UInt8			pad[3];		// 005
	BSExtraData*	next;		// 008
};
assert(sizeof(BSExtraData) == 0x0C);

class InventoryChanges : public BSExtraData {
public:
	class EntryData {
	public:
		TList<ExtraDataList>*	extendData;
		SInt32					countDelta;
		TESForm*				type;
	};

	class Data {
	public:
		TList<EntryData>*	data;
		TESObjectREFR*		owner;
		float				totalWeight;	// of all items in inventory. cached, is -1 if needs to be recalculated
		float				armorWeight;	// weight of equipped armor. cached as above. Both take armor weight perks into account
	};

	Data*	data;			// 00C
};
assert(sizeof(InventoryChanges) == 0x10);

class ExtraDataList {
public:
	virtual	void				Destroy(bool bNoDealloc);	// removes and frees all of m_data

	bool						HasType(UInt32 type) { UInt32 index = (type >> 3); UInt8 bitMask = 1 << (type % 8); return (m_presenceBitfield[index] & bitMask) != 0; }
	BSExtraData*				GetByType(UInt32 type) { if (HasType(type)) { for (BSExtraData* Data = m_data; Data; Data = Data->next) { if (Data->type == type) return Data; } } return NULL; }
	bool						IsWorn() { return (HasType(BSExtraData::ExtraDataType::kExtraData_Worn) || HasType(BSExtraData::ExtraDataType::kExtraData_WornLeft)); }
	InventoryChanges::Data*		GetInventoryChangesData() { return (InventoryChanges::Data*)ThisCall(0x00418520, this); }

	BSExtraData*				m_data;						// 004
	UInt8						m_presenceBitfield[0x15];	// 008 - if a bit is set, then the extralist should contain that extradata - bits are numbered starting from the lsb
	UInt8						pad[3];
};
assert(sizeof(ExtraDataList) == 0x20);

class MagicCaster {
public:
	virtual void			Unk_00();
	virtual void			Unk_01();
	virtual void			Unk_02();
	virtual void			CastSpell(MagicItem* spell, bool arg2, MagicTarget* magicTarget, float arg4, bool arg5);
	virtual void			Unk_04();
	virtual void			Unk_05();
	virtual void			Unk_06();
	virtual void			Unk_07();
	virtual void			Unk_08();
	virtual void			Unk_09();
	virtual void			Unk_0A();
	virtual TESObjectREFR*	GetParent();
	virtual void			Unk_0C();
	virtual void			Unk_0D();
	virtual void			Unk_0E();
	virtual void			Unk_0F();
	virtual void			Unk_10(MagicItem* spell);
	virtual void			Unk_11();
	virtual void			Unk_12(MagicTarget* magicTarget);
	virtual void			Unk_13();

	UInt32	unk04[2];	// 04
};
assert(sizeof(MagicCaster) == 0xC);

class MagicTarget {
public:
	virtual bool			ApplyEffect(MagicCaster* magicCaster, MagicItem* magicItem, ActiveEffect* activeEffect, bool arg4);
	virtual TESObjectREFR*	GetParent();
	virtual void*			GetEffectList(); //ActiveEffectList*
	virtual void			Unk_03();
	virtual void			Unk_04();
	virtual void			Unk_05();
	virtual void			Unk_06();
	virtual void			Unk_07();
	virtual void			Unk_08();
	virtual float			Unk_09(MagicCaster* magicCaster, MagicItem* magicItem, ActiveEffect* activeEffect);
	virtual void			Unk_0A();
	virtual void			Unk_0B();

	UInt32	unk04[3];	// 04
};
assert(sizeof(MagicTarget) == 0x10);

class BaseFormComponent {
public:
	virtual void	Init();
	virtual void	Free();
	virtual void	CopyFromBase(BaseFormComponent* component);
	virtual bool	CompareWithBase(BaseFormComponent* src);
};
assert(sizeof(BaseFormComponent) == 0x004);

class TESDescription : public BaseFormComponent {
public:
	virtual const char* GetText(TESForm* parentForm, UInt32 recordCode);

	UInt32	formDiskOffset;	// 04
};
assert(sizeof(TESDescription) == 0x008);

class TESModel : public BaseFormComponent {
public:
	enum {
		kFacegenFlag_Head		= 0x01,
		kFacegenFlag_Torso		= 0x02,
		kFacegenFlag_RightHand	= 0x04,
		kFacegenFlag_LeftHand	= 0x08,
	};

	virtual void*	Destroy(bool noDealloc);	// 04
	virtual char*	GetModelPath(void);
	virtual void	SetModelPath(char* path);	// 06

	BSString	nifPath;		// 04
	UInt32		unk0C;			// 0C	referenced when saving Texture Hashes, init'd as a byte or is it a pointer to a structure starting with a byte followed by a pointer to some allocated data ?
	void*		unk10;		// 10
	UInt8		facegenFlags;	// 14
	UInt8		pad15[3];		// 15
};
assert(sizeof(TESModel) == 0x018);

class TESModelAnim : public TESModel {};
assert(sizeof(TESModelAnim) == 0x018);

class TESScriptableForm : public BaseFormComponent {
public:
	Script* script;		// 004
	UInt8	unk1;		// 008
	UInt8	pad[3];		// 009
};
assert(sizeof(TESScriptableForm) == 0x00C);

class TESEnchantableForm : public BaseFormComponent {
public:
	EnchantmentItem* enchantItem;	// 04
	UInt16			 enchantment;	// 08
	UInt16			 unk1;			// 0A
	UInt32			 unk2;			// 0C
};
assert(sizeof(TESEnchantableForm) == 0x010);

class TESValueForm : public BaseFormComponent {
public:
	enum {
		kModified_GoldValue = 0x00000008,
	};
	UInt32	value;
};
assert(sizeof(TESValueForm) == 0x008);

class TESWeightForm : public BaseFormComponent {
public:
	float	weight;
};
assert(sizeof(TESWeightForm) == 0x008);

class TESHealthForm : public BaseFormComponent {
public:
	UInt32	health;
};
assert(sizeof(TESHealthForm) == 0x008);

class TESAttackDamageForm : public BaseFormComponent {
public:
	UInt16	damage;
	UInt16	unk0;	// bitmask? perhaps 2 UInt8s?
};
assert(sizeof(TESAttackDamageForm) == 0x008);

class BGSAmmoForm : public BaseFormComponent {
public:
	TESForm* ammo; // 04	either TESAmmo or BGSListForm
};
assert(sizeof(BGSAmmoForm) == 0x008);

class BGSClipRoundsForm : public BaseFormComponent {
public:
	UInt8	clipRounds;
	UInt8	padding[3];
};
assert(sizeof(BGSClipRoundsForm) == 0x008);

class BGSDestructibleObjectForm : public BaseFormComponent {
public:
	void*	data;			// 04 DestructibleData*
};
assert(sizeof(BGSDestructibleObjectForm) == 0x08);

class BGSRepairItemList : public BaseFormComponent {
public:
	void*	listForm;	// 04 BGSListForm*
};
assert(sizeof(BGSRepairItemList) == 0x08);

class BGSEquipType : public BaseFormComponent {
public:
	UInt32	equipType;	// 04
};
assert(sizeof(BGSEquipType) == 0x08);

class BGSPreloadable : public BaseFormComponent {
public:
	virtual void	Fn_04();
};
assert(sizeof(BGSPreloadable) == 0x04);

class BGSMessageIcon : public BaseFormComponent {
public:
	UInt32	icon[3];		// 004 TESIcon class
};
assert(sizeof(BGSMessageIcon) == 0x10);

class BGSBipedModelList : public BaseFormComponent {
public:
	void*	models;		// 004 BGSListForm*
};
assert(sizeof(BGSBipedModelList) == 0x08);

class BGSPickupPutdownSounds : public BaseFormComponent {
public:
	TESSound* pickupSound;		// 004
	TESSound* putdownSound;		// 008
};
assert(sizeof(BGSPickupPutdownSounds) == 0x0C);

class TESModelTextureSwap : public TESModel {
public:
	virtual void*	Destroy(bool noDealloc);
	virtual char*	GetPath();
	virtual void	SetPath(char* path);
	virtual void*	Unk_07();
	
	class Texture {
	public:
		UInt32	textureID;			// 00
		UInt32	index3D;			// 04
		char	textureName[0x80];	// 08
	};

	TList<Texture>	textureList;	// 018
};
assert(sizeof(TESModelTextureSwap) == 0x020);

class TESForm : public BaseFormComponent {
public:
	enum FormType {
		kFormType_None = 0,					// 00
		kFormType_TES4,
		kFormType_Group,
		kFormType_GMST,
		kFormType_TextureSet,
		kFormType_MenuIcon,
		kFormType_Global,
		kFormType_Class,
		kFormType_Faction,					// 08
		kFormType_HeadPart,
		kFormType_Hair,
		kFormType_Eyes,
		kFormType_Race,
		kFormType_Sound,
		kFormType_AcousticSpace,
		kFormType_Skill,
		kFormType_Effect,					// 10
		kFormType_Script,
		kFormType_LandTexture,
		kFormType_Enchantment,
		kFormType_Spell,
		kFormType_Activator,
		kFormType_TalkingActivator,
		kFormType_Terminal,
		kFormType_Armor,					// 18	inv object
		kFormType_Book,						// 19	inv object
		kFormType_Clothing,					// 1A	inv object
		kFormType_Container,
		kFormType_Door,
		kFormType_Ingredient,				// 1D	inv object
		kFormType_Light,					// 1E	inv object
		kFormType_Misc,						// 1F	inv object
		kFormType_Stat,					// 20
		kFormType_StaticCollection,
		kFormType_MoveableStatic,
		kFormType_PlaceableWater,
		kFormType_Grass,
		kFormType_Tree,
		kFormType_Flora,
		kFormType_Furniture,
		kFormType_Weapon,					// 28	inv object
		kFormType_Ammo,						// 29	inv object
		kFormType_NPC,						// 2A
		kFormType_Creature,					// 2B
		kFormType_LeveledCreature,			// 2C
		kFormType_LeveledCharacter,			// 2D
		kFormType_Key,						// 2E	inv object
		kFormType_AlchemyItem,				// 2F	inv object
		kFormType_IdleMarker,				// 30
		kFormType_Note,						// 31	inv object
		kFormType_ConstructibleObject,		// 32	inv object
		kFormType_Projectile,
		kFormType_LeveledItem,				// 34	inv object
		kFormType_Weather,
		kFormType_Climate,
		kFormType_Region,
		kFormType_NAVI,						// 38
		kFormType_Cell,
		kFormType_Reference,				// 3A
		kFormType_ACHR,						// 3B
		kFormType_ACRE,						// 3C
		kFormType_PMIS,						// 3D
		kFormType_PGRE,						// 3E
		kFormType_PBEA,						// 3F
		kFormType_PFLA,						// 40
		kFormType_WorldSpace,
		kFormType_Land,
		kFormType_NavMesh,
		kFormType_TLOD,
		kFormType_DIAL,
		kFormType_INFO,
		kFormType_Quest,
		kFormType_Idle,						// 48
		kFormType_Package,
		kFormType_CombatStyle,
		kFormType_LoadScreen,
		kFormType_LeveledSpell,
		kFormType_ANIO,
		kFormType_Water,
		kFormType_EffectShader,
		kFormType_TOFT,						// 50	table of Offset (see OffsetData in Worldspace)
		kFormType_Explosion,
		kFormType_Debris,
		kFormType_ImageSpace,
		kFormType_ImageSpaceModifier,
		kFormType_ListForm,					// 55
		kFormType_Perk,
		kFormType_BodyPartData,
		kFormType_AddonNode,				// 58
		kFormType_ActorValueInfo,
		kFormType_RadiationStage,
		kFormType_CameraShot,
		kFormType_CameraPath,
		kFormType_VoiceType,
		kFormType_ImpactData,
		kFormType_ImpactDataSet,
		kFormType_ARMA,						// 60
		kFormType_EncounterZone,
		kFormType_Message,
		kFormType_Ragdoll,
		kFormType_DOBJ,
		kFormType_LightingTemplate,
		kFormType_SoundFile,
		kFormType_ItemMod,					// 67	inv object
		kFormType_Reputation,				// 68
		kFormType_PCBE,						// 69 Continuous Beam
		kFormType_Recipe,
		kFormType_RecipeCategory,
		kFormType_CasinoChip,				// 6C	inv object
		kFormType_Casino,
		kFormType_LoadScreenType,
		kFormType_MediaSet,
		kFormType_MediaLocationController,	// 70
		kFormType_Challenge,
		kFormType_AmmoEffect,
		kFormType_CaravanCard,				// 73	inv object
		kFormType_CaravanMoney,				// 74	inv object
		kFormType_CaravanDeck,
		kFormType_DehydrationStages,
		kFormType_HungerStages,
		kFormType_SleepDeprivationStages,	// 78
	};

	virtual void*		Destroy(bool noDealloc);			// func_00C in GECK ?? I think ??
	virtual void		Unk_05();						// Might be set default value (called from constructor)
	virtual void		Unk_06();						// Might be clear values
	virtual bool		Unk_07();
	virtual bool		LoadForm(ModInfo* modInfo);		// func_010 in GECK
	virtual bool		Unk_09(void* arg);					// points to LoadForm on TESForm
	virtual bool		AppendForm(ModInfo* modInfo);		// (ie SaveForm + append to modInfo)
	virtual void		SaveForm(void);						// saves in same format as in .esp	//	func_013 in GECK
	virtual bool		LoadForm2(ModInfo* modInfo);		// just calls LoadForm
	virtual void		WriteFormInfo(ModInfo* modInfo);	// does some saving stuff, then calls Fn0A
	virtual bool		Unk_0E(void* arg);					// prepares a GRUP formInfo
	virtual bool		Sort(TESForm* form);				// returns if the argument is "greater or equal" to this form
	virtual TESForm*	CreateForm(void* arg0, void* mapToAddTo);	// makes a new form, 
	virtual void		Unk_11(void* arg);
	virtual void		MarkAsModified(UInt32 changedFlags);		// enable changed flag?
	virtual void		MarkAsUnmodified(UInt32 changedFlags);		// disable changed flag?
	virtual UInt32		GetSaveSize(UInt32 changedFlags);	// bytes taken by the delta flags for this form, UNRELIABLE, not (always) overriden
	virtual void		Unk_15(void* arg);					// collect referenced forms?
	virtual void		SaveGame(UInt32 changedFlags);		// Used as part of CopyFromBase with LoadGame.
	virtual void		LoadGame(void* arg);				// load from BGSLoadFormBuffer arg
	virtual void		LoadGame2(UInt32 changedFlags);		// load from TESSaveLoadGame
	virtual void		Unk_19(void* arg);
	virtual void		Unk_1A(void* arg0, void* arg1);
	virtual void		Unk_1B(void* arg0, void* arg1);
	virtual void		Revert(UInt32 changedFlags);		// reset changes in form
	virtual void		Unk_1D(void* arg);
	virtual void		Unk_1E(void* arg);
	virtual bool		Unk_1F(void* arg);
	virtual void		Unk_20(void* arg);
	virtual void		Unk_21(void* arg);
	virtual void		InitItem();
	virtual UInt32		GetTypeID();
	virtual void		GetDebugName(BSString* dst);
	virtual bool		IsQuestItem();
	virtual bool		Unk_26();		// 00000040
	virtual bool		Unk_27();		// 00010000
	virtual bool		Unk_28();		// 00010000
	virtual bool		Unk_29();		// 00020000
	virtual bool		Unk_2A();		// 00020000
	virtual bool		Unk_2B();		// 00080000
	virtual bool		Unk_2C();		// 02000000
	virtual bool		Unk_2D();		// 40000000
	virtual bool		Unk_2E();		// 00000200
	virtual void		Unk_2F(bool set);	// 00000200
	virtual bool		Unk_30();		// returns false
	virtual void		Unk_31(bool set);	// 00000020 then calls Fn12 MarkAsModified
	virtual void		Unk_32(bool set);	// 00000002 with a lot of housekeeping
	virtual void		SetQuestItem(bool set);	// 00000400 then calls Fn12 MarkAsModified
	virtual void		Unk_34(bool set);	// 00000040 then calls Fn12 MarkAsModified
	virtual void		Unk_35(bool set);	// 00010000 then calls Fn12 MarkAsModified
	virtual void		Unk_36(bool set);	// 00020000
	virtual void		Unk_37();		// write esp format
	virtual void		readOBNDSubRecord(ModInfo* modInfo);	// read esp format
	virtual bool		Unk_39();
	virtual bool		Unk_3A();
	virtual bool		Unk_3B();
	virtual bool		Unk_3C();	// is REFR
	virtual bool		Unk_3D();
	virtual bool		Unk_3E();
	virtual bool		Unk_3F();	// returnTrue for refr whose baseForm is a TESActorBase
	virtual bool		Unk_40();	// Called from GetActorValue, might be is Actor (called also from AddItem and PlayGroup)
	virtual UInt32		Unk_41();
	virtual void		CopyFrom(const TESForm* form);
	virtual bool		Compare(TESForm* form);
	virtual bool		CheckFormGRUP(void* arg);	// Checks the group is valid for the form
	virtual void		InitFormGRUP(void* dst, void* arg1);	// Fills the groupInfo with info valid for the form
	virtual bool		Unk_46();
	virtual bool		Unk_47();
	virtual bool		Unk_48(UInt32 formType);	// returns if the same FormType is passed in
	virtual bool		Unk_49(void* arg0, void* arg1, void* arg2, void* arg3, void* arg4);	// looks to be func33 in Oblivion
	virtual void		SetRefID(UInt32 refID, bool generateID);
	virtual const char* GetName();	// not sure which objects this works on, doesn't seem to work on player or random objects
	virtual const char* GetEditorName(); // returns nothing at runtime (return the editorname for TESObjectCELL)
	virtual bool		SetEditorName(const char* name);

	enum {
		kModified_FormFlags = 0x00000001,
		kModified_GoldValue = 0x08,
		kModified_Name		= 0x80
	};

	enum {
		kFormFlags_QuestItem			= 0x00000400,
		kFormFlags_Destroyed			= 0x00002000,
		kFormFlags_IgnoresFriendlyHits	= 0x00100000,
	};

	UInt8				typeID;					// 004
	UInt8				typeIDPad[3];			// 005
	UInt32				flags;					// 008
	UInt32				refID;					// 00C
	TList<ModInfo>		modRefList;				// 010
};
assert(sizeof(TESForm) == 0x018);

class TESPackage : public TESForm {
public:
	enum {
		kPackageFlag_OffersServices =			1 << 0,
		kPackageFlag_MustReachLocation =		1 << 1,
		kPackageFlag_MustComplete =				1 << 2,
		kPackageFlag_LockDoorsAtStart =			1 << 3,
		kPackageFlag_LockDoorsAtEnd =			1 << 4, 	// set by CHANGE_PACKAGE_WAITING ?
		kPackageFlag_LockDoorsAtLocation =		1 << 5,
		kPackageFlag_UnlockDoorsAtStart =		1 << 6,
		kPackageFlag_UnlockDoorsAtEnd =			1 << 7,
		kPackageFlag_UnlockDoorsAtLocation =	1 << 8,
		kPackageFlag_ContinueIfPCNear =			1 << 9,
		kPackageFlag_OncePerDay =				1 << 10,
		kPackageFlag_Unk11 =					1 << 11,
		kPackageFlag_SkipFalloutBehavior =		1 << 12,
		kPackageFlag_AlwaysRun =				1 << 13,
		kPackageFlag_Unk14 =					1 << 14,
		kPackageFlag_NeverRun =					1 << 15,	// Save only ?
		kPackageFlag_Unk16 =					1 << 16,
		kPackageFlag_AlwaysSneak =				1 << 17,
		kPackageFlag_AllowSwimming =			1 << 18,
		kPackageFlag_AllowFalls =				1 << 19,
		kPackageFlag_ArmorUnequipped =			1 << 20,
		kPackageFlag_WeaponsUnequipped =		1 << 21,
		kPackageFlag_DefensiveCombat =			1 << 22,
		kPackageFlag_WeaponsDrawn =				1 << 23,
		kPackageFlag_NoIdleAnims =				1 << 24,
		kPackageFlag_PretendInCombat =			1 << 25,
		kPackageFlag_ContinueDuringCombat =		1 << 26,
		kPackageFlag_NoCombatAlert =			1 << 27,
		kPackageFlag_NoWarnAttackBehavior =		1 << 28,
		kPackageFlag_Unk29 =					1 << 29,
		kPackageFlag_Unk30 =					1 << 30,
		kPackageFlag_Unk31 =					1 << 31
	};

	enum {	// From OBSE and FNVEdit. Runtimes has 0x24 types!
		kPackageType_Find =	0,		// 00
		kPackageType_Follow,
		kPackageType_Escort,
		kPackageType_Eat,
		kPackageType_Sleep,
		kPackageType_Wander,
		kPackageType_Travel,
		kPackageType_Accompany,
		kPackageType_UseItemAt,
		kPackageType_Ambush,
		kPackageType_FleeNotCombat,
		kPackageType_Unk11,
		kPackageType_Sandbox,
		kPackageType_Patrol,
		kPackageType_Guard,
		kPackageType_Dialogue,
		kPackageType_UseWeapon,			// 10

		// unless shown otherwise kPackageType_CombatController,	// Actor::GetCombatController returns package only if type matches this
		// start conversation can lead to a package of type 1C, which is recorded in PlayerCharacter::Unk0224

		kPackType_MAX
	};

	// 8
	struct PackageTime {
		enum {
			kDay_Any = 0,
			kTime_Any = 0xFF,
		};

		enum {
			kMonth_January = 0,
			kMonth_February,
			kMonth_March,
			kMonth_April,
			kMonth_May,
			kMonth_June,
			kMonth_July,
			kMonth_August,
			kMonth_September,
			kMonth_October,
			kMonth_November,
			kMonth_December,
			kMonth_Spring,	// march, april, may
			kMonth_Summer,	// june, july, august
			kMonth_Autumn,	// september, august, november (in Geck)
			kMonth_Winter,	// december, january, february

			kMonth_Any = 0xFF,
		};

		enum {
			kWeekday_Sundays = 0,
			kWeekday_Morndays,
			kWeekday_Tuesdays,
			kWeekday_Wednesdays,
			kWeekday_Thursdays,
			kWeekday_Frydays,
			kWeekday_Saturdays,
			kWeekday_Weekdays,
			kWeekday_Weekends,
			kWeekday_MWF,
			kWeekday_TT,

			kWeekday_Any = 0xFF
		};

		UInt8	month;
		UInt8	weekDay;
		UInt8	date;
		UInt8	time;
		UInt32	duration;
	};

	union ObjectType {
		TESForm*		form;
		TESObjectREFR*	refr;
		UInt32			objectCode;
	};

	// order only somewhat related to kFormType_XXX (values off by 17, 20, or 21)
	enum {	
		kObjectType_None	=	0,
		kObjectType_Activators,
		kObjectType_Armor,
		kObjectType_Books,
		kObjectType_Clothing,
		kObjectType_Containers,
		kObjectType_Doors,
		kObjectType_Ingredients,
		kObjectType_Lights,
		kObjectType_Misc,
		kObjectType_Flora,
		kObjectType_Furniture,
		kObjectType_WeaponsAny,
		kObjectType_Ammo,
		kObjectType_NPCs,
		kObjectType_Creatures,
		kObjectType_Keys,				//	10
		kObjectType_Alchemy,
		kObjectType_Food,
		kObjectType_AllCombatWearable,
		kObjectType_AllWearable,
		kObjectType_WeaponsRanged,
		kObjectType_WeaponsMelee,
		kObjectType_WeaponsNone,
		kObjectType_ActorEffectAny,
		kObjectType_ActorEffectRangeTarget,
		kObjectType_ActorEffectRangeTouch,
		kObjectType_ActorEffectRangeSelf,
		kObjectType_ActorsAny,

		kObjectType_Max,						//	1E
	};

	class LocationData {
	public:
		enum {
			kPackLocation_NearReference		= 0,
			kPackLocation_InCell			= 1,
			kPackLocation_CurrentLocation	= 2,
			kPackLocation_EditorLocation	= 3,
			kPackLocation_ObjectID			= 4,
			kPackLocation_ObjectType		= 5,
			kPackLocation_LinkedReference	= 6,

			kPackLocation_Max,
		};

		UInt8		locationType;	// 000
		UInt8		pad[3];
		UInt32		radius;			// 004
		ObjectType  object;			// 008
	};

	enum {
		kTargetType_Refr		= 0,
		kTargetType_BaseObject	= 1,
		kTargetType_TypeCode	= 2,
		
		kTargetType_Max	= 3,
	};

	class TargetData {
	public:
		UInt8		targetType;	// 00
		UInt8		pad[3];		// 01
		ObjectType	target;		// 04
		UInt32		count;		// 08 can be distance too
		float		unk0C;		// 0C
	};

	enum eProcedure {			// UInt32	// Checked the Geck Wiki. Not consistent with s_procNames (which has a diffferent order and 0x37 procedures)
		kProcedure_TRAVEL = 0,
		kProcedure_ACTIVATE,
		kProcedure_ACQUIRE,
		kProcedure_WAIT,
		kProcedure_DIALOGUE,
		kProcedure_GREET,
		kProcedure_GREET_DEAD,
		kProcedure_WANDER,
		kProcedure_SLEEP,
		kProcedure_OBSERVE_COMBAT,
		kProcedure_EAT,
		kProcedure_FOLLOW,
		kProcedure_ESCORT,
		kProcedure_COMBAT,
		kProcedure_ALARM,
		kProcedure_PURSUE,
		kProcedure_FLEE,					// 0x10
		kProcedure_DONE,
		kProcedure_YELD,
		kProcedure_TRAVEL_TARGET,
		kProcedure_CREATE_FOLLOW,
		kProcedure_GET_UP,
		kProcedure_MOUNT_HORSE,
		kProcedure_DISMOUNT_HORSE,
		kProcedure_DO_NOTHING,
		kProcedure_UNK019,
		kProcedure_UNK01A,
		kProcedure_ACCOMPANY,
		kProcedure_USE_ITEM_AT,
		kProcedure_SANDMAN,
		kProcedure_WAIT_AMBUSH,
		kProcedure_SURFACE,					// 0x20
		kProcedure_WAIT_FOR_SPELL,
		kProcedure_CHOOSE_CAST,
		kProcedure_FLEE_NON_COMBAT,
		kProcedure_REMOVE_WORN_ITEMS,
		kProcedure_SEARCH,
		kProcedure_CLEAR_MOUNT_POSITION,
		kProcedure_SUMMON_CREATURE_DEFEND,
		kProcedure_AVOID_AREA,
		kProcedure_UNEQUIP_ARMOR,
		kProcedure_PATROL,
		kProcedure_USE_WEAPON,
		kProcedure_DIALOGUE_ACTIVATE,
		kProcedure_GUARD,
		kProcedure_SANDBOX,
		kProcedure_USE_IDLE_MARKER,
		kProcedure_TAKE_BACK_ITEM,
		kProcedure_SITTING,					// 0x30
		kProcedure_MOVEMENT_BLOCKED,
		kProcedure_CANIBAL_FEED,			// 0x32

		kProcedure_MAX						// 0x33
	};

	// In DialoguePackage, there are 0x58 virtual functions (including 0x4E from TESForm)

	UInt32				procedureArrayIndex;	// 018 index into array of array of eProcedure terminated by 0x2C. -1 if no procedure array exists for package type.
	UInt32				packageFlags;		// 01C
	UInt8				type;				// 020
	UInt8				pad021[1];			// 021
	UInt16				behaviorFlags;		// O22
	UInt32				specificFlags;		// 024
	TESPackageData*		packageData;		// 028
	LocationData*		location;			// 02C
	TargetData*			target;				// 030	target ?
	UInt32				unk034;				// 034	idles
	PackageTime			time;				// 038
	UInt32				unk040[(0x80 - 0x40) >> 2];		// 040	040 is a tList of Condition, 7C is an Interlocked counter
};
assert(sizeof(TESPackage) == 0x80);

class PackageInfo {
public:
	TESPackage*		package;		// 00
	TESPackageData*	packageData;	// 04
	TESObjectREFR*	targetRef;		// 08
	UInt32			unk0C;			// 0C	Initialized to 0FFFFFFFFh, set to 0 on start
	float			unk10;			// 10	Initialized to -1.0	. Set to GameHour on start so some time
	UInt32			flags;			// 14	Flags, bit0 would be not created and initialized
};
assert(sizeof(PackageInfo) == 0x18);

class TESIdleForm : public TESForm {
public:
	enum {
		eIFgf_groupIdle = 0,
		eIFgf_groupMovement = 1,
		eIFgf_groupLeftArm = 2,
		eIFgf_groupLeftHand = 3,
		eIFgf_groupLeftWeapon = 4,
		eIFgf_groupLeftWeaponUp = 5,
		eIFgf_groupLeftWeaponDown = 6,
		eIFgf_groupSpecialIdle = 7,
		eIFgf_groupWholeBody = 20,
		eIFgf_groupUpperBody = 20,

		eIFgf_flagOptionallyReturnsAFile = 128,
		eIFgf_flagUnknown = 64,
	};

	struct Data {
		UInt8			groupFlags;		// 000	animation group and other flags
		UInt8			loopMin;		// 001
		UInt8			loopMax;		// 002
		UInt8			fil03B;			// 003
		UInt16			replayDelay;	// 004
		UInt8			flags;			// 006	bit0 is No attacking
		UInt8			fil03F;			// 007
	};

	TESModelAnim		anim;			// 018
	TList<void*>		conditions;		// 030 Condition list
	Data				data;			// 038
	UInt32				unk040;			// 040	NiFormArray, contains all idle anims in path if eIFgf_flagUnknown is set
	TESIdleForm*		parent;			// 044
	TESIdleForm*		previous;		// 048
	BSString			str04C;			// 04C
};
assert(sizeof(TESIdleForm) == 0x54);

class TESTexture : public BaseFormComponent {
public:
	BSString	ddsPath;		// 04
};
assert(sizeof(TESTexture) == 0x0C);

class TESIcon : public TESTexture { };
assert(sizeof(TESIcon) == 0x0C);

class TESFullName : public BaseFormComponent {
public:
	BSString	name;		// 004
};
assert(sizeof(TESFullName) == 0x0C);

class TESWeather : public TESForm {
public:
	enum { kNumColorTypes = 11 };
	enum { kNumTimeOfDay = 6 };

	enum {
		eColor_SkyUpper = 0,
		eColor_Fog = 1,
		eColor_CloudsLower = 2,
		eColor_Ambient = 3,
		eColor_Sunlight = 4,
		eColor_Sun = 5,
		eColor_Stars = 6,
		eColor_SkyLower = 7,
		eColor_Horizon = 8,
		eColor_CloudsUpper = 9,
		eColor_Lightning = 10,
	};

	enum {
		eTime_Sunrise = 0,
		eTime_Day = 1,
		eTime_Sunset = 2,
		eTime_Night = 3,
		eTime_Midnight = 4,
		eTime_HighNoon = 5,
	};

	struct ColorData {
		RGBA colors[6];
	};

	struct FogInfo {
		float nearFog;
		float farFog;
		float pow;
	};

	struct WeatherSound {
		UInt32		soundID;	// refID of TESSound
		UInt32		type;		// 0 - Default; 1 - Precip; 2 - Wind; 3 - Thunder
	};

	UInt32					unk018;						// 018
	void*					imageSpaceMods[6];			// 01C TESImageSpaceModifier*
	TESTexture				layerTextures[4];			// 034
	UInt8					cloudSpeed[4];				// 064
	UInt32					unk068[24];					// 068
	TESModel				model;						// 0C8
	UInt8					windSpeed;					// 0E0
	UInt8					cloudSpeedLower;			// 0E1
	UInt8					cloudSpeedUpper;			// 0E2
	UInt8					transDelta;					// 0E3
	UInt8					sunGlare;					// 0E4
	UInt8					sunDamage;					// 0E5
	UInt8					precipitationBeginFadeIn;	// 0E6
	UInt8					precipitationEndFadeOut;	// 0E7
	UInt8					lightningBeginFadeIn;		// 0E8
	UInt8					lightningEndFadeOut;		// 0E9
	UInt8					lightningFrequency;			// 0EA
	UInt8					precipType;					// 0EB
	UInt32					lightningColor;				// 0EC
	FogInfo					fogDay;						// 0F0
	FogInfo					fogNight;					// 0FC
	ColorData				colors[10];					// 108
	TList<WeatherSound>		sounds;						// 1F8
	UInt32					unk200[91];					// 200
};
assert(sizeof(TESWeather) == 0x36C);

class TESClimate : public TESForm {
public:
	class WeatherType {
	public:
		TESWeather* weather;
		UInt32		chance;
		void*		global; //TESGlobal*
	};

	TESModel			nightSky;			// 18
	TList<WeatherType>	weatherTypes;		// 30
	TESTexture			sun;				// 38
	TESTexture			sunGlare;			// 44
	UInt8				sunriseBegin;		// 50
	UInt8				sunriseEnd;			// 51
	UInt8				sunsetBegin;		// 52
	UInt8				sunsetEnd;			// 53
	UInt8				volatility;			// 54
	UInt8				phaseLength;		// 55
	UInt8				pad56[2];			// 56
};
assert(sizeof(TESClimate) == 0x58);

class TESWaterForm : public TESForm {
public:
	struct Data34 {
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
		UInt32	unkC;	// C
	};

	// E4 (to adjust....copied from Skyrim)
	struct Properties {
		float	unk00;		// 00 - init'd to .1
		float	unk04;		// 04 - init'd to 90
		float	unk08;		// 08 - init'd to .5
		float	unk0C;		// 0C - init'd to 1
		float	sunSpecularPower;
		float	reflectivityAmount;
		float	fresnelAmount;
		float	unk1C;		// 1C - init'd to 0
		float	fogNearAW;	// Above water fog near place distance
		float	fogFarAW;	// Above water fog far plane distance
		UInt8	shallowColorR;
		UInt8	shallowColorG;
		UInt8	shallowColorB;
		UInt8	shallowColorA;
		UInt8	deepColorR;
		UInt8	deepColorG;
		UInt8	deepColorB;
		UInt8	deepColorA;
		UInt8	reflectionColorR;
		UInt8	reflectionColorG;
		UInt8	reflectionColorB;
		UInt8	reflectionColorA;
		UInt8	unk34;		// 34 - init'd to 0
		UInt8	pad35[3];	// 35
		float	unk38;		// 38 - init'd to 0.1
		float	unk3C;		// 3C - init'd to 0.6
		float	unk40;		// 40 - init'd to 0.985
		float	unk44;		// 44 - init'd to 2
		float	displacementStartingSize;
		float	displacementForce;
		float	displacementVelocity;
		float	displacementFalloff;
		float	displacementDampner;
		float	unk5C;		// 5C - init'd to .05
		float	noiseFalloff;
		float	noiseWindDirectionL1;
		float	noiseWindDirectionL2;
		float	noiseWindDirectionL3;
		float	noiseWindSpeedL1;
		float	noiseWindSpeedL2;
		float	noiseWindSpeedL3;
		float	unk7C;		// 7C - init'd to 300
		float	unk80;		// 80 - init'd to 300
		float	fogAmountAW; // Above water fog amount
		float	unk88;		// 88 - not init'd
		float	fogAmountUW; // Underwater water fog amount
		float	fogNearUW;	// Underwater fog near place distance
		float	fogFarUW;	// Underwater fog far plane distance
		float	refractionMagnitude;
		float	specularPower;
		float	unkA0;		// A0 - init'd to 1
		float	specularRadius;
		float	specularbrightness;
		float	noiseUVScaleL1;
		float	noiseUVScaleL2;
		float	noiseUVScaleL3;
		float	noiseAmplitudeScaleL1;
		float	noiseAmplitudeScaleL2;
		float	noiseAmplitudeScaleL3;
		float	reflectionMagnitude;
		float	sunSparkleMagnitude;
		float	sunSpecularMagnitude;
		float	depthReflections;
		float	depthRefractions;
		float	depthNormals;
		float	depthSpecularLight;
		float	sunSparklePower;
	};

	TESFullName				fullName;		// 018
	TESAttackDamageForm		attackDamage;	// 024
	UInt32					unk02C;			// 02C
	UInt32					unk030;			// 030
	Data34					unk034;			// 034
	Data34					unk044;			// 044
	Data34					unk054;			// 054
	TESTexture				unk064;			// 064
	UInt32					unk070;			// 070
	Data34					unk074;			// 074
	Properties				properties;		// 084
	UInt32					unk168[11];		// 168
};
assert(sizeof(TESWaterForm) == 0x194);

class TESWorldSpace : public TESForm {
public:
	struct CoordXY {
		float	X;	// 000
		float	Y;	// 004
	};

	struct DCoordXY {
		SInt32	X;	// 000
		SInt32	Y;	// 004
	};

	struct WCoordXY {
		SInt16	X;	// 000
		SInt16	Y;	// 002
	};

	struct OffsetData {
		UInt32**	unk000;	// 000 array of UInt32 stored in OFST record (indexed by relative CellXY).
		CoordXY		min;		// 004 NAM0
		CoordXY		max;		// 00C NAM9
		UInt32		fileOffset;	// 014 TESWorldspace file offset in modInfo
	};

	struct MapData {
		DCoordXY	usableDimensions;
		WCoordXY	cellNWCoordinates;
		WCoordXY	cellSECoordinates;
	};

	class LODData {
	public:
		class LODNode {
		public:
			LODData*		parent;			// 00
			UInt32			lodLevel;		// 04
			UInt32			cellXY;			// 08
			UInt8			byte0C;			// 0C
			UInt8			byte0D;			// 0D
			UInt8			byte0E;			// 0E
			UInt8			byte0F;			// 0F
			UInt32			ukn10;			// 10
			void*			object;			// 14
			UInt32			ukn18;			// 18
			UInt32			ukn1C;			// 1C
			LODNode*		linked[4];		// 20
			UInt32			unk30;			// 30
			float			flt34;			// 34
			float			flt38;			// 38
			float			flt3C;			// 3C
			float			flt40;			// 40
			float			flt44;			// 44
			float			flt48;			// 48
			float			flt4C;			// 4C
			UInt32			unk50;			// 50
			UInt32			ukn54;			// 54
			UInt32			ukn58;			// 58
			UInt8			byte5C;			// 5C
			UInt8			byte5D;			// 5D
			UInt8			byte5E;			// 5E
			UInt8			byte5F;			// 5F
		};

		TESWorldSpace*		world;		// 00
		LODNode*			lodNode;	// 04
		NiNode*				node08;		// 08
		NiNode*				node0C;		// 0C
		UInt32				coordNW;	// 10
		UInt32				coordSE;	// 14
		UInt32				ukn18;		// 18
		UInt32				ukn1C;		// 1C
		UInt32				ukn20;		// 20
		UInt32				lodLevel;	// 24
		UInt8				byte28;		// 28
		UInt8				byte29;		// 29
		UInt8				byte2A;		// 2A
		UInt8				byte2B;		// 2B
		UInt32				array2C[0x10];	// 2C BSSimpleArray<TESObjectREFR>
	};

	class ImpactData {
	public:
		enum MaterialType {
		  eMT_Stone = 0,
		  eMT_Dirt,
		  eMT_Grass,
		  eMT_Glass,
		  eMT_Metal,
		  eMT_Wood,
		  eMT_Organic,
		  eMT_Cloth,
		  eMT_Water,
		  eMT_HollowMetal,
		  eMT_OrganicBug,
		  eMT_OrganicGlow,

		  eMT_Max
		};

		NiTMap<BGSImpactData*, BGSImpactData*>	impactImpactMap[eMT_Max];	// 000
		char									footstepMaterials[0x12C];	// 030
	};

	TESFullName				fullName;			// 018 confirmed
	TESTexture				texture;			// 024 confirmed ICON
	NiTMap<UInt32, TESObjectCELL>*	cellMap;			// 030 confirmed
	TESObjectCELL*			cell;				// 034 should be the Permanent cell
	UInt32					unk038;				// 038
	LODData*				lodData;			// 03C looks to be the LOD data (That is what is returned when checking the parent "Use LOD data" flag)
	TESClimate*				climate;			// 040 confirmed CNAM
	void*					imageSpace;		// 044 confirmed INAM TESImageSpace*
	ImpactData*				impacts;			// 048 confirmed
	UInt8					flags;				// 04C confirmed DATA
	UInt8					unk04D;				// 04D filler
	UInt16					parentFlags;		// 04E init'd to FF if has a parent. 5 is use ImageSpace, 4 is use parent climate, 3 is use parent Water, 1 is use parent LOD data, 0 is use parent LAND data
	NiTMap<UInt32, void*>	pointerMap;			// 050 confirmed NiTPointerMap<BSSimpleList<TESObjectREFR>>
	TList<void*>			lst060;				// 060
	TList<void*>			lst068;				// 068 confirmed as tList
	TESWorldSpace*			parent;				// 070 confirmed
	TESWaterForm*			waterFormFirst;		// 074 confirmed NAM2
	TESWaterForm*			waterFormLast;		// 078 confirmed NAM3 LOD Water type for xEdit
	float					waterHeight;		// 07C confirmed NAM4
	MapData					mapData;			// 080 confirmed MNAM
	float					worldMapScale;		// 090 confirmed ONAM for three floats
	float					worldMapCellX;		// 094 confirmed
	float					worldMapCellY;		// 098 confirmed
	void*					music;				// 09C confirmed ZNAM BGSMusicType*
	CoordXY					min;				// 0A0 confirmed NAM0 min of all Offset_Data.min
	CoordXY					max;				// 0A8 confirmed NAM9 max of all Offset_data.max
	NiTMap<ModInfo*, OffsetData*> offsetMap;			// 0B0 guarded by an isESM NiTMapBase<ModInfo *,TESWorldSpace::Offset_Data *>
	BSString				str0C0;				// 0C0
	float					defaultLandHeight;	// 0C8 confirmed DNAM for the two
	float					defaultWaterHeight;	// 0CC
	void*					encounterZone;		// 0D0 confirmed BGSEncounterZone*
	TESTexture				canopyShadow;		// 0D4 confirmed NNAM
	TESTexture				waterNoiseTexture;	// 0E0 confirmed XNAM
};
assert(sizeof(TESWorldSpace) == 0xEC);

class TESGlobal : public TESForm {
public:
	enum {
		kType_Short = 's',
		kType_Long  = 'l',
		kType_Float = 'f'
	};

	BSString	name;		// 018
	UInt8		type;		// 020
	UInt8		pad21[3];	// 021
	float		data;		// 024
};
assert(sizeof(TESGlobal) == 0x028);

class TESRegion : public TESForm {
public:
	void*			dataEntries;	// 18 RegionDataEntryList*
	void*			areaEntries;	// 1C RegionAreaEntryList*
	TESWorldSpace*	worldSpace;		// 20
	TESWeather*		weather;		// 24
	UInt32			unk28[4];		// 28
};
assert(sizeof(TESRegion) == 0x38);

class TESRegionList {
public:
	void**			_vtbl;		// 000
	TList<TESRegion> list;		// 004
};
assert(sizeof(TESRegionList) == 0x0C);

class TESObject : public TESForm {
public:
	virtual UInt32	Unk_4E();
	virtual bool	Unk_4F();
	virtual UInt32	Unk_50();
	virtual bool	Unk_51();
	virtual void	Unk_52(void* arg);
	virtual NiNode* Unk_53(TESObjectREFR* refr, void* arg1);
	virtual void	Unk_54(void* arg);
	virtual bool	IsInternal();
	virtual bool	IsInternalMarker();
	virtual void	Unk_57();
	virtual bool	Unk_58();	// BoundObject: Calls Unk_5F on the object model
	virtual bool	Unk_59(void* arg);
	virtual void	Unk_5A(void* arg0, void* arg1);
	virtual UInt32	Unk_5B();
	virtual UInt32	Unk_5C();
	virtual bool	Unk_5D(TESObjectREFR* refr);	// if false, no NiNode gets returned by Unk_53, true for NPC
};
assert(sizeof(TESObject) == 0x018);

class TESBoundObject : public TESObject {
public:
	virtual NiNode* CreateNiNode(TESObjectREFR* refr);	// calls Fn53, for NPC calls ReadBones, for LevelledActor level them if necessary
	virtual bool	Unk_5F(void);

	BoundObjectListHead*	head;		// 018
	TESBoundObject*			prev;		// 01C
	TESBoundObject*			next;		// 020
	SInt16					bounds[6];	// 024
};
assert(sizeof(TESBoundObject) == 0x030);

class TESObjectSTAT : public TESBoundObject {
public:
	TESModelTextureSwap		model;		// 30
	UInt32					unk50[2];	// 50
};
assert(sizeof(TESObjectSTAT) == 0x058);

class TESObjectIMOD : public TESBoundObject {
public:
	TESFullName					name;				// 030
	TESModelTextureSwap			model;				// 03C
	TESIcon						icon;				// 05C
	TESScriptableForm			scriptForm;			// 068
	TESDescription				description;		// 074
	TESValueForm				value;				// 07C
	TESWeightForm				weight;				// 084
	BGSDestructibleObjectForm	destructible;		// 08C
	BGSMessageIcon				messageIcon;		// 094
	BGSPickupPutdownSounds		pickupPutdownSounds;// 0A4
};
assert(sizeof(TESObjectIMOD) == 0x0B0);

class TESObjectWEAP : public TESBoundObject {
public:
	enum EWeaponType {
		kWeapType_HandToHandMelee = 0,
		kWeapType_OneHandMelee,
		kWeapType_TwoHandMelee,
		kWeapType_OneHandPistol,
		kWeapType_OneHandPistolEnergy,
		kWeapType_TwoHandRifle,
		kWeapType_TwoHandAutomatic,
		kWeapType_TwoHandRifleEnergy,
		kWeapType_TwoHandHandle,
		kWeapType_TwoHandLauncher,
		kWeapType_OneHandGrenade,
		kWeapType_OneHandMine,
		kWeapType_OneHandLunchboxMine,
		kWeapType_OneHandThrown,
		kWeapType_Last	// During animation analysis, player weapon can be classified as 0x0C = last
	};

	enum EWeaponSounds {
		kWeapSound_Shoot3D = 0,
		kWeapSound_Shoot2D,
		kWeapSound_Shoot3DLooping,
		kWeapSound_NoAmmo,
		kWeapSound_Swing = kWeapSound_NoAmmo,
		kWeapSound_Block,
		kWeapSound_Idle,
		kWeapSound_Equip,
		kWeapSound_Unequip
	};

	enum EHandGrip {
		eHandGrip_Default = 0xFF,
		eHandGrip_1 = 0xE6,
		eHandGrip_2 = 0xE7,
		eHandGrip_3 = 0xE8,
		eHandGrip_4 = 0xE9,
		eHandGrip_5 = 0xEA,
		eHandGrip_6 = 0xEB,
		eHandGrip_Count = 7,
	};

	enum EAttackAnimations {
		eAttackAnim_Default = 0xff,	// 11111111
		eAttackAnim_Attack3 = 0x26,	// 00100110
		eAttackAnim_Attack4 = 0x2c, // 00101100
		eAttackAnim_Attack5 = 0x32,	// 00110010
		eAttackAnim_Attack6 = 0x38, // 
		eAttackAnim_Attack7 = 0x3e,
		eAttackAnim_Attack8 = 0x44,
		eAttackAnim_AttackLeft = 0x1a,
		eAttackAnim_AttackLoop = 0x4a,
		eAttackAnim_AttackRight = 0x20,
		eAttackAnim_AttackSpin = 0x50,
		eAttackAnim_AttackSpin2 = 0x56,
		eAttackAnim_AttackThrow = 0x6d,
		eAttackAnim_AttackThrow2 = 0x73,
		eAttackAnim_AttackThrow3 = 0x79,
		eAttackAnim_AttackThrow4 = 0x7F,
		eAttackAnim_AttackThrow5 = 0x85,
		eAttackAnim_PlaceMine = 0x61,
		eAttackAnim_PlaceMine2 = 0x67,
		eAttackAnim_Count = 19,
	};

	enum ReloadAnim {
		eReload_A = 0,
		eReload_B,
		eReload_C,
		eReload_D,
		eReload_E,
		eReload_F,
		eReload_G,
		eReload_H,
		eReload_I,
		eReload_J,
		eReload_K,
		eReload_L,
		eReload_M,
		eReload_N,
		eReload_O,
		eReload_P,
		eReload_Q,
		eReload_R,
		eReload_S,
		eReload_W,
		eReload_X,
		eReload_Y,
		eReload_Z,
		eReload_Count,
	};

	enum EWeaponFlags1 {
		eFlag_IgnoresNormalWeapResist = 0x1,
		eFlag_IsAutomatic = 0x2,
		eFlag_HasScope = 0x4,
		eFlag_CantDrop = 0x8,
		eFlag_HideBackpack = 0x10,
		eFlag_EmbeddedWeapon = 0x20,
		eFlag_No1stPersonISAnims = 0x40,
		Eflag_NonPlayable = 0x80
	};

	enum EWeaponFlags2 {
		eFlag_PlayerOnly = 0x1,
		eFlag_NPCsUseAmmo = 0x2,
		eFlag_NoJamAfterReload = 0x4,
		eFlag_ActionPointOverride = 0x8,
		eFlag_MinorCrime = 0x10,
		eFlag_FixedRange = 0x20,
		eFlag_NotUsedNormalCombat = 0x40,
		eFlag_DamageToWeaponOverride = 0x80,
		eFlag_No3rdPersonISAnims = 0x100,
		eFlag_BurstShot = 0x200,
		eFlag_RumbleAlternate = 0x400,
		eFlag_LongBurst = 0x800,
	};

	enum EEmbedWeapAV {
		eEmbedAV_Perception = 0,
		eEmbedAV_Endurance,
		eEmbedAV_LeftAttack,
		eEmbedAV_RightAttack,
		eEmbedAV_LeftMobility,
		eEmbedAV_RightMobility,
		eEmbedAV_Brain,
	};

	enum EOnHit {
		eOnHit_Normal = 0,
		eOnHit_DismemberOnly,
		eOnHit_ExplodeOnly,
		eOnHit_NoDismemberOrExplode,
	};

	enum ERumblePattern {
		eRumblePattern_Constant = 0,
		eRumblePattern_Square,
		eRumblePattern_Triangle,
		eRumblePattern_Sawtooth
	};

	enum ECritDamageFlags {
		eCritDamage_OnDeath = 0x1
	};

	enum {
		kWeaponModEffect_None = 0,
		kWeaponModEffect_IncreaseDamage,
		kWeaponModEffect_IncreaseClipCapacity,
		kWeaponModEffect_DecreaseSpread,
		kWeaponModEffect_DecreaseWeight,
		kWeaponModEffect_Unused05,
		kWeaponModEffect_RegenerateAmmo,
		kWeaponModEffect_DecreaseEquipTime,
		kWeaponModEffect_IncreaseRateOfFire,		// 8
		kWeaponModEffect_IncreaseProjectileSpeed,
		kWeaponModEffect_IncreaseMaxCondition,
		kWeaponModEffect_Silence,
		kWeaponModEffect_SplitBeam,
		kWeaponModEffect_VATSBonus,
		kWeaponModEffect_IncreaseZoom,				// 14
	};

	// bases
	TESFullName					fullName;			// 030
	TESModelTextureSwap			textureSwap;		// 03C
	TESIcon						icon;				// 05C
	TESScriptableForm			scritpable;			// 068
	TESEnchantableForm			enchantable;		// 074
	TESValueForm				value;				// 084
	TESWeightForm				weight;				// 08C
	TESHealthForm				health;				// 094
	TESAttackDamageForm			attackDmg;			// 09C
	BGSAmmoForm					ammo;				// 0A4
	BGSClipRoundsForm			clipRounds;			// 0AC
	BGSDestructibleObjectForm	destructible;		// 0B4
	BGSRepairItemList			repairItemList;		// 0BC
	BGSEquipType				equipType;			// 0C4
	BGSPreloadable				preloadable;		// 0CC
	BGSMessageIcon				messageIcon;		// 0D0
	BGSBipedModelList			bipedModelList;		// 0E0
	BGSPickupPutdownSounds		pickupPutdownSounds;// 0E8

	UInt8				eWeaponType;		// 0F4
	UInt8				pad[3];
	float				animMult;			// 0F8
	float				reach;				// 0FC
	UInt8				weaponFlags1;		// 100
	UInt8				handGrip;			// 101
	UInt8				ammoUse;			// 102
	UInt8				reloadAnim;			// 103
	float				minSpread;			// 104
	float				spread;				// 108
	UInt32				unk10C;				// 10C
	float				sightFOV;			// 110
	UInt32				unk114;				// 114
	void*				projectile;			// 118 BGSProjectile*
	UInt8				baseVATSChance;		// 11C
	UInt8				attackAnim;			// 11D
	UInt8				numProjectiles;		// 11E
	UInt8				embedWeaponAV;		// 11F
	float				minRange;			// 120
	float				maxRange;			// 124
	UInt32				onHit;				// 128
	UInt32				weaponFlags2;		// 12C
	float				animAttackMult;		// 130
	float				fireRate;			// 134
	float				AP;					// 138
	float				rumbleLeftMotor;	// 13C
	float				rumbleRightMotor;	// 140
	float				rumbleDuration;		// 144
	float				damageToWeaponMult;	// 148
	float				animShotsPerSec;	// 14C
	float				animReloadTime;		// 150
	float				animJamTime;		// 154		
	float				aimArc;				// 158
	UInt32				weaponSkill;		// 15C - actor value
	UInt32				rumblePattern;		// 160 - reload anim?
	float				rumbleWavelength;	// 164
	float				limbDamageMult;		// 168
	UInt32				resistType;			// 16c - actor value
	float				sightUsage;			// 170
	float				semiAutoFireDelayMin;	// 174
	float				semiAutoFireDelayMax;	// 178
	UInt32				unk17C;				// 17C - 0-0x10: 0x8:str req 0x10: - skill req  - 0xb:kill impulse B158 - mod 1 val B15C - Mod 2 val Effects: 0x1: e(zoom) 0x2: a 0x3:0 0x4-6: Values c-e Mod Effects Val2:1-3 
	UInt32				effectMods[3];		// 180
	float				value1Mod[3];		// 18C
	UInt32				powerAttackAnimOverride;	// 198
	UInt32				strRequired;		// 19C
	UInt8				pad1A0;				// 1A0
	UInt8				modReloadAnim;		// 1A1
	UInt8				pad1A2[2];			// 1A2
	float				regenRate;			// 1A4
	float				killImpulse;		// 1A8
	float				value2Mod[3];		// 1AC
	float				impulseDist;		// 1B8
	UInt32				skillRequirement;	// 1BC
	UInt16				criticalDamage;		// 1C0
	UInt8				unk1C2[2];			// 1C2
	float				criticalPercent;	// 1C4
	UInt8				critDamageFlags;	// 1C8
	UInt8				pad1C9[3];			// 1C9
	SpellItem*			 criticalEffect;	// 1CC
	TESModel			shellCasingModel;	// 1DO
	TESModel			targetNIF;			// 1E8 - target NIF
	TESModel			model200;			// 200 - could be a texture swap
	UInt32				unk218;				// 218
	TESSound*			sounds[12];			// 21C
	void*				impactDataSet;		// 24C BGSImpactDataSet*
	TESObjectSTAT*		worldStatic;		// 250
	TESObjectSTAT*		mod1Static;			// 254
	TESObjectSTAT*		mod2Static;			// 258
	TESObjectSTAT*		mod3Static;			// 25C
	TESObjectSTAT*		mod12Static;		// 260
	TESObjectSTAT*		mod13Static;		// 264
	TESObjectSTAT*		mod23Static;		// 268
	TESObjectSTAT*		mod123Static;		// 26C
	TESModelTextureSwap	textureMod1;		// 270 Mod 1
	TESModelTextureSwap	textureMod2;		// 290 Mod 2
	TESModelTextureSwap	textureMod3;		// 2B0 Mod 3
	TESModelTextureSwap	textureMod12;		// 2D0 Mod 1-2
	TESModelTextureSwap	textureMod13;		// 2F0 Model 1-3
	TESModelTextureSwap	textureMod23;		// 310 Model 2-3
	TESModelTextureSwap	textureMod123;		// 330 Model 1-2-3
	TESObjectIMOD*		itemMod[3];			// 350
	BSString			embeddedNodeName;	// 35C
	UInt32				soundLevel;			// 364
	UInt32				unk368;				// 368
	UInt32				unk36C;				// 36C
	SpellItem*			VATSEffect;			// 370
	UInt32				unk374;				// 374
	UInt32				unk378;				// 378
	UInt32				unk37C;				// 37C
	UInt32				recharge;			// 380 maybe recharge
	UInt32				unk384;				// 384
};
assert(sizeof(TESObjectWEAP) == 0x388);

class BGSPerkEntry {
public:
	virtual void	Fn_00();
	virtual void	Fn_01();
	virtual void	Fn_02();
	virtual void	Fn_03();
	virtual void	Fn_04();
	virtual void	Fn_05();
	virtual void	Fn_06();
	virtual void	Fn_07();
	virtual void	Fn_08();
	virtual void	Fn_09();
	virtual void	Fn_0A();
	virtual void	Fn_0B();
	virtual void	Fn_0C();
	virtual void	Fn_0D();

	UInt8				rank;				// 04 +1 for value shown in GECK
	UInt8				priority;			// 05
	UInt16				type;				// 06 (Quest: 0xC24, Ability: 0xB27, Entry Point: 0xD16)
};
assert(sizeof(BGSPerkEntry) == 0x08);

class BGSPerk : public TESForm {
public:
	struct PerkData {
		bool				isTrait;	// 00
		UInt8				minLevel;	// 01
		UInt8				numRanks;	// 02
		bool				isPlayable;	// 03
		bool				isHidden;	// 04
		UInt8				unk05;		// 05 todo: collapse to pad[3] after verifying isPlayable and isHidden
		UInt8				unk06;		// 06
		UInt8				unk07;		// 07
	};

	TESFullName				fullName;			// 18
	TESDescription			description;		// 24
	TESIcon					icon;				// 2C
	PerkData				data;				// 38
	TList<void*>			conditions;			// 40 Condition List
	TList<BGSPerkEntry>		entries;			// 48
};
assert(sizeof(BGSPerk) == 0x50);

class TESObjectREFRData {
public:
	UInt32	unk00;
	UInt32	unk04;
	float	waterHeight;
	float	unk0C;
	UInt32	unk10;		// flags most likely
	NiNode* niNode;
	// possibly more, need to find alloc
};
assert(sizeof(TESObjectREFRData) == 0x18);

class TESObjectCELL : public TESForm {
public:
	enum {
		kFlags0_Interior					= 1 << 0,
		kFlags0_HasWater					= 1 << 1,
		kFlags0_InvertFastTravelBehavior	= 1 << 2,
		kFlags0_PublicPlace					= 1 << 5,
		kFlags0_HandChanged					= 1 << 6,
		kFlags0_BehaveLikeExterior			= 1 << 7,
	};

	struct CellCoordinates {
		SInt32	x;
		SInt32	y;
	};
	
	struct LightingData {
		RGBA		ambient;
		RGBA		directional;
		RGBA		fog;
		float		fogNear;
		float		fogFar;
		// it continues....
	};
	
	struct StructC4 {
		NiNode*								node;		// 00
		TList<TESObjectREFR>				list04;		// 04
		NiTMap<TESObjectREFR*, NiNode*>		map0C;		// 0C
		NiTMap<TESForm*, TESObjectREFR*>	map1C;		// 1C
		NiTMap<TESObjectREFR*, NiNode*>		map2C;		// 2C
		NiTMap<TESObjectREFR*, NiNode*>		map3C;		// 3C
		TList<TESObjectREFR>				list4C;		// 4C
		TList<void>							list54;		// 54
		TList<TESObjectREFR>				list5C;		// 5C
	};
	
	float					GetWaterHeight(TESObjectREFRData* RenderData) { if (RenderData) return RenderData->waterHeight; return ThisCallF(0x005471E0, this); }
	TESWaterForm*			GetWaterForm() { return NULL; }

	TESFullName				fullName;			// 018	// 030 in GECK
	UInt8					flags0;				// 024
	UInt8					flags1;				// 025
	UInt8					flags2;				// 026	// 5 or 6 would mean cell is loaded, name based on OBSE
	UInt8					unk027;				// 027
	ExtraDataList			extraDataList;		// 028
	union {										// 048
		CellCoordinates*	coords;				// if exterior
		LightingData*		lighting;			// if interior
	};
	TESObjectLAND*			land;				// 04C
	float					waterHeight;		// 050
	UInt32					unk54;				// 054
	TESTexture				noiseTexture;		// 058
	void*					navMeshArray;		// 064 BSSimpleArray<NavMesh>
	UInt32					unk68[15];			// 068	80 is CellRefLock semaphore
	UInt32					actorCount;			// 0A4
	UInt16					countVWD;			// 0A8
	UInt16					unk0AA;				// 0AA
	TList<TESObjectREFR>	objectList;			// 0AC
	NiNode*					niNode0B4;			// 0B4
	NiNode*					niNode0B8;			// 0B8
	UInt32					unk0BC;				// 0BC
	TESWorldSpace*			worldSpace;			// 0C0
	StructC4*				structC4;			// 0C4
	float					unk0C8;				// 0C8
	UInt32					unk0CC;				// 0CC
	UInt32					unk0D0;				// 0D0
	void*					portalGraph;		// 0D4 BSPortalGraph*
	BGSLightingTemplate*	lightingTemplate;	// 0D8
	UInt32					unk0DC;				// 0DC
};
assert(sizeof(TESObjectCELL) == 0xE0);

class TESObjectREFR : public TESForm {
public:
	virtual void		Unk_4E();	// GetStartingPosition(Position, Rotation, WorldOrCell)
	virtual void		Unk_4F();
	virtual void		Unk_50();
	virtual void		Unk_51();
	virtual bool		CastShadows();
	virtual void		Unk_53();
	virtual void		Unk_54();
	virtual void		Unk_55();
	virtual void		Unk_56();
	virtual void		Unk_57();
	virtual void		Unk_58();
	virtual void		Unk_59();
	virtual void		Unk_5A();
	virtual void		Unk_5B();
	virtual void		Unk_5C();
	virtual void		Unk_5D();
	virtual void		Unk_5E();
	virtual TESObjectREFR* RemoveItem(TESForm* toRemove, ExtraDataList* extraList, UInt32 count, UInt32 unk3, UInt32 unk4, TESObjectREFR* destRef, UInt32 unk6, UInt32 unk7, UInt32 unk8, UInt8 unk9);	// 40 unk2 quantity? Returns the reference assigned to the removed item.
	virtual void		Unk_60();
	virtual void		Unk_61();	// Linked to AddItem, (item, count, ExtraDataList), func0042 in OBSE
	virtual void		Unk_62();	// Linked to Unequip (and or equip maybe)
	virtual void		Unk_63();
	virtual void		AddItem(TESForm* item, ExtraDataList* xDataList, UInt32 Quantity);	// Needs confirmation
	virtual void		Unk_65();
	virtual void		Unk_66();
	virtual void		Unk_67();					// Actor: GetMagicEffectList
	virtual bool		GetIsChildSize(bool checkHeight);		// 068 Actor: GetIsChildSize
	virtual UInt32		GetActorUnk0148();			// result can be interchanged with baseForm, so TESForm* ?
	virtual void		SetActorUnk0148(UInt32 arg0);
	virtual void		Unk_6B();
	virtual void		Unk_6C();	// REFR: GetBSFaceGenNiNodeSkinned
	virtual void		Unk_6D();	// REFR: calls 006C
	virtual void		Unk_6E();	// MobileActor: calls 006D then NiNode::Func0040
	virtual void		Unk_6F();
	virtual void		Unk_70();
	virtual void		AnimateNiNode();					// same in FOSE ! identical to Func0052 in OBSE which says (inits animation-related data, and more)
	virtual void		GenerateNiNode(bool arg0);				// same in FOSE !
	virtual void		Set3D(NiNode* niNode, bool unloadArt);	// same in FOSE !
	virtual NiNode*		GetNiNode();						// same in FOSE !
	virtual void		Unk_75();
	virtual void		Unk_76();
	virtual void		Unk_77();
	virtual void		Unk_78();
	virtual ActorAnimData*	GetActorAnimData();			// 0079
	virtual void*			GetValidBip01Names();	// 007A	returns ValidBip01Names*
	virtual void*		CallGetValidBip01Names(); // returns ValidBip01Names*
	virtual void		SetValidBip01Names(UInt32 validBip01Names);
	virtual void		GetPos();				// GetPos or GetDistance
	virtual void		Unk_7E(UInt32 arg0);
	virtual void		Unk_7F();
	virtual void		Unk_80(UInt32 arg0);
	virtual void		Unk_81(UInt32 arg0);
	virtual void		Unk_82();
	virtual UInt32		Unk_83();
	virtual void		Unk_84(UInt32 arg0);
	virtual UInt8		GetSitSleepState();		// Get 01AC
	virtual bool		Unk_86();			// return false for Projectile, Actor and Creature, true for character and PlayerCharacter
	virtual bool		Unk_87();			// seems to always return 0
	virtual bool		Unk_88();			// seems to always return 0
	virtual void		Unk_89();
	virtual void		Unk_8A();			// SetParentCell (Interior only ?)
	virtual UInt8		GetLifeState(UInt8 Arg1);
	virtual bool		Unk_8C();
	virtual bool		Unk_8D();
	virtual void		Unk_8E();
	virtual void		Unk_8F();

	enum {
		kFlags_Unk00000002	= 0x00000002,
		kFlags_Deleted		= 0x00000020,		// refr removed from .esp or savegame
		kFlags_Persistent	= 0x00000400,		//shared bit with kFormFlags_QuestItem
		kFlags_Temporary	= 0x00004000,
		kFlags_Taken		= kFlags_Deleted | kFlags_Unk00000002,

		kChanged_Inventory = 0x08000000,
	};

	TESChildCell		childCell;				// 018
	UInt32				unk1C;					// 01C
	TESForm*			baseForm;				// 020
	NiPoint3			rot;					// 024
	NiPoint3			pos;					// 030 
	float				scale;					// 03C 
	TESObjectCELL*		parentCell;				// 040
	ExtraDataList		extraDataList;			// 044
	TESObjectREFRData*	renderData;				// 064	- (05C in FOSE)
};
assert(sizeof(TESObjectREFR) == 0x068);

class MobileObject : public TESObjectREFR {
public:
	virtual void		StartHighProcess();		// 090
	virtual void		Unk_91();
	virtual void		Unk_92();
	virtual void		Unk_93();
	virtual void		Unk_94();
	virtual void		Unk_95();
	virtual void		Unk_96();
	virtual void		Unk_97();
	virtual void		Unk_98();
	virtual void		Unk_99();
	virtual void		Unk_9A();
	virtual void		Unk_9B();
	virtual void		Unk_9C();
	virtual void		Unk_9D();
	virtual void		Unk_9E();
	virtual void		Unk_9F();
	virtual void		Unk_A0();	// StartConversation(targetActor, subjectLocationData, targetLocationData, headTrack, allowMovement, arg, topicID, arg, arg
	virtual void		Unk_A1();
	virtual void		Unk_A2();
	virtual void		Unk_A3();
	virtual void		Unk_A4();
	virtual void		Unk_A5();
	virtual void		Unk_A6();
	virtual void		Unk_A7();
	virtual void		Unk_A8();
	virtual void		Unk_A9();
	virtual void		Unk_AA();
	virtual void		Unk_AB();
	virtual void		Unk_AC();
	virtual void		Unk_AD();
	virtual void		Unk_AE();
	virtual void		Unk_AF();
	virtual void		Unk_B0();
	virtual void		Unk_B1();
	virtual void		Unk_B2();
	virtual void		Unk_B3();
	virtual void		Unk_B4();
	virtual void		Unk_B5();
	virtual void		Unk_B6();
	virtual void		Unk_B7();
	virtual void		Unk_B8();
	virtual void		Unk_B9();
	virtual void		Unk_BA();
	virtual void		Unk_BB();
	virtual void		Unk_BC();
	virtual void		Unk_BD();
	virtual void		Unk_BE();
	virtual void		Unk_BF();
	virtual void		Unk_C0();

	BaseProcess*	process;		// 068
	UInt32			unk06C;			// 06C - loaded	set to the talking actor ref when initialising ExtraTalkingActor
	UInt32			unk070;			// 070 - loaded
	UInt32			unk074;			// 074 - loaded
	UInt32			unk078;			// 078 - loaded
	UInt8			unk07C;			// 07C - loaded
	UInt8			unk07D;			// 07D - loaded
	UInt8			unk07E;			// 07E - loaded
	UInt8			unk07F;			// 07F - loaded
	UInt8			unk080;			// 080 - loaded
	UInt8			unk081;			// 081 - loaded
	UInt8			unk082;			// 082 - cleared when starting combat on player
	UInt8			unk083;			// 083 - loaded
	UInt8			unk084;			// 084 - loaded
	UInt8			unk085;			// 085 - loaded
	UInt8			unk086;			// 086 - loaded
	UInt8			unk087;			// 087	Init'd to the inverse of NoLowLevelProcessing
};
assert(sizeof(MobileObject) == 0x088);

class ActorValuesOwner {
public:

	virtual UInt32	GetBaseActorValue(UInt32 avCode);		// GetBaseActorValue (used from Eval) result in EAX
	virtual float	GetBaseAVFloat(UInt32 avCode);			// GetBaseActorValue internal, result in st
	virtual float	Fn_02(UInt32 avCode);					// GetActorValue internal, result in EAX
	virtual UInt32	GetActorValue(UInt32 avCode);			// GetActorValue (used from Eval) result in EAX
	virtual float	Fn_04(UInt32 avCode);					// GetBaseActorValue04 (internal) result in st
	virtual float	GetActorValueDamage(UInt32 avCode);
	virtual float	Fn_06(UInt32 avCode);					// GetDamageActorValue or GetModifiedActorValue		called from Fn_08, result in st, added to Fn_01
	virtual UInt32	Fn_07(UInt32 avCode);					// Manipulate GetPermanentActorValue, maybe convert to integer.
	virtual float	GetPermanentActorValue(UInt32 avCode);	// GetPermanentActorValue (used from Eval) result in EAX
	virtual void*	Fn_09();								// GetActorBase (= this - 0x100) or GetActorBase (= this - 0x0A4)
	virtual UInt16	GetLevel();								// GetLevel (from ActorBase)
};
assert(sizeof(ActorValuesOwner) == 0x004);

class CachedValuesOwner {
public:
	virtual float	Fn_00();
	virtual float	Fn_01();
	virtual float	Fn_02();
	virtual float	Fn_03();
	virtual float	Fn_04();
	virtual float	Fn_05();
	virtual float	Fn_06();
	virtual float	Fn_07();
	virtual float	Fn_08();
	virtual float	Fn_09();
	virtual float	Fn_0A();
	virtual UInt32	Fn_0B();
	virtual UInt32	Fn_0C();
	virtual float	Fn_0D();
	virtual float	Fn_0E();
	virtual bool	Fn_0F();
};
assert(sizeof(CachedValuesOwner) == 0x004);

class PathingLocation {
public:
	virtual void	Unk_00();
	virtual void	Unk_01();
	virtual void	Unk_02();

	UInt32			unk04[9];	// 04
};
assert(sizeof(PathingLocation) == 0x028);

class ActorMover {
public:
	virtual void		Unk_00();
	virtual void		Unk_01();
	virtual void		Unk_02();
	virtual void		Unk_03();
	virtual void		Unk_04();
	virtual void		Unk_05();
	virtual void		Unk_06();
	virtual void		Unk_07();
	virtual UInt32		GetMovementFlags();
	//	Running		0x200
	//	Sneaking	0x400

	// bit 11 = swimming 
	// bit 9 = sneaking
	// bit 8 = run
	// bit 7 = walk
	// bit 0 = keep moving (Q)
	virtual void		Unk_09();
	virtual void		Unk_0A();
	virtual void		Unk_0B();
	virtual void		Unk_0C();
	virtual void		Unk_0D();
	virtual void		Unk_0E();

	UInt32				unk04[6];			// 04
	void*				pathingRequest;		// 1C PathingRequest*
	void*				pathingSolution;	// 20 PathingSolution*
	void*				pathHandler;		// 24 DetailedActorPathHandler*
	Actor*				actor;				// 28
	UInt32				unk2C;				// 2C
	void*				pathingMsgQueue;	// 30 ActorPathingMessageQueue*
	UInt32				movementFlags1;		// 34
	UInt32				unk38;				// 38
	UInt32				movementFlags2;		// 3C
	UInt32				unk40;				// 40
	PathingLocation		pathingLocation;	// 44
	UInt32				unk6C;				// 6C
	UInt8				unk70[4];			// 70
	UInt32				unk74;				// 74
	UInt32				unk78;				// 78
	UInt32				unk7C;				// 7C
	UInt32				unk80;				// 80
	UInt32				unk84;				// 84
};
assert(sizeof(ActorMover) == 0x088);

class Actor : public MobileObject {
public:
	enum ActorVal {
		kActorVal_Aggression			= 0,
		kActorVal_Confidence			= 1,
		kActorVal_Energy				= 2,
		kActorVal_Responsibility		= 3,
		kActorVal_Mood					= 4,

		kActorVal_Strength				= 5,
		kActorVal_Perception			= 6,
		kActorVal_Endurance				= 7,
		kActorVal_Charisma				= 8,
		kActorVal_Intelligence			= 9,
		kActorVal_Agility				= 10,
		kActorVal_Luck					= 11,
		kActorVal_SpecialStart = kActorVal_Strength,
		kActorVal_SpecialEnd = kActorVal_Luck,

		kActorVal_ActionPoints			= 12,
		kActorVal_CarryWeight			= 13,
		kActorVal_CritChance			= 14,
		kActorVal_HealRate				= 15,
		kActorVal_Health				= 16,
		kActorVal_MeleeDamage			= 17,
		kActorVal_DamageResistance		= 18,
		kActorVal_PoisonResistance		= 19,
		kActorVal_RadResistance			= 20,
		kActorVal_SpeedMultiplier		= 21,
		kActorVal_Fatigue				= 22,
		kActorVal_Karma					= 23,
		kActorVal_XP					= 24,

		kActorVal_Head					= 25,
		kActorVal_Torso					= 26,
		kActorVal_LeftArm				= 27,
		kActorVal_RightArm				= 28,
		kActorVal_LeftLeg				= 29,
		kActorVal_RightLeg				= 30,
		kActorVal_Brain					= 31,
		kActorVal_BodyPartStart = kActorVal_Head,
		kActorVal_BodyPartEnd = kActorVal_Brain,

		kActorVal_Barter				= 32,
		kActorVal_BigGuns				= 33,
		kActorVal_EnergyWeapons			= 34,
		kActorVal_Explosives			= 35,
		kActorVal_Lockpick				= 36,
		kActorVal_Medicine				= 37,
		kActorVal_MeleeWeapons			= 38,
		kActorVal_Repair				= 39,
		kActorVal_Science				= 40,
		kActorVal_Guns					= 41,
		kActorVal_Sneak					= 42,
		kActorVal_Speech				= 43,
		kActorVal_Survival				= 44,
		kActorVal_Unarmed				= 45,
		kActorVal_SkillsStart = kActorVal_Barter,
		kActorVal_SkillsEnd = kActorVal_Unarmed,

		kActorVal_InventoryWeight		= 46,
		kActorVal_Paralysis				= 47,
		kActorVal_Invisibility			= 48,
		kActorVal_Chameleon				= 49,
		kActorVal_NightEye				= 50,
		kActorVal_Turbo					= 51,
		kActorVal_FireResistance		= 52,
		kActorVal_WaterBreathing		= 53,
		kActorVal_RadLevel				= 54,
		kActorVal_BloodyMess			= 55,
		kActorVal_UnarmedDamage			= 56,
		kActorVal_Assistance			= 57,

		kActorVal_ElectricResistance	= 58,
		kActorVal_FrostResistance		= 59,

		kActorVal_EnergyResistance		= 60,
		kActorVal_EMPResistance			= 61,
		kActorVal_Var1Medical			= 62,
		kActorVal_Var2					= 63,
		kActorVal_Var3					= 64,
		kActorVal_Var4					= 65,
		kActorVal_Var5					= 66,
		kActorVal_Var6					= 67,
		kActorVal_Var7					= 68,
		kActorVal_Var8					= 69,
		kActorVal_Var9					= 70,
		kActorVal_Var10					= 71,

		kActorVal_IgnoreCrippledLimbs	= 72,
		kActorVal_Dehydration			= 73,
		kActorVal_Hunger				= 74,
		kActorVal_Sleepdeprevation		= 75,
		kActorVal_Damagethreshold		= 76,
		kActorVal_FalloutMax			= kActorVal_Damagethreshold,
		kActorVal_NoActorValue			= 256,
	};

	virtual void		Unk_C1();
	virtual void		Unk_C2();
	virtual void		Unk_C3();
	virtual void		Unk_C4();
	virtual void		Unk_C5();
	virtual void		Unk_C6();
	virtual void		SetIgnoreCrime(bool ignoreCrime);
	virtual bool		GetIgnoreCrime();
	virtual void		Unk_C9();
	virtual void		Unk_CA();
	virtual void		Unk_CB();
	virtual void		Unk_CC();
	virtual void		Unk_CD();
	virtual void		Unk_CE();
	virtual void		Unk_CF();
	virtual void		Unk_D0();
	virtual void		Unk_D1();
	virtual void		Unk_D2();
	virtual void		Unk_D3();
	virtual void		Unk_D4();
	virtual void		Unk_D5();
	virtual void		Unk_D6();
	virtual void		Unk_D7();
	virtual bool		IsPlayerRef();
	virtual void		Unk_D9();
	virtual void		Unk_DA();
	virtual void		Unk_DB();
	virtual void		Unk_DC();
	virtual void		Unk_DD();
	virtual void		Unk_DE();
	virtual void		Unk_DF();
	virtual void		Unk_E0();
	virtual void		Unk_E1();
	virtual void		Unk_E2();
	virtual void		Unk_E3();
	virtual UInt32		GetActorType();	// Creature = 0, Character = 1, PlayerCharacter = 2
	virtual void		SetActorValue(UInt32 avCode, float value);
	virtual void		SetActorValueInt(UInt32 avCode, UInt32 value);
	virtual void		Unk_E7();
	virtual void		Unk_E8();
	virtual void		Unk_E9();
	virtual void		Unk_EA();
	virtual void		DamageActorValue(UInt32 avCode, float damage, Actor* attacker);
	virtual void		Unk_EC();
	virtual void		Unk_ED();
	virtual void		Unk_EE();
	virtual InventoryChanges::EntryData* GetPreferedWeapon(UInt32 unk);
	virtual void		Unk_F0();
	virtual void		Unk_F1();
	virtual void		Unk_F2();
	virtual void		Unk_F3();
	virtual void		Unk_F4();
	virtual void		Unk_F5();
	virtual void		Unk_F6();
	virtual void		Unk_F7();
	virtual void		Unk_F8();
	virtual void		Unk_F9();
	virtual void		Unk_FA();
	virtual void		Unk_FB(TESForm* form, UInt32 arg2, UInt8 arg3, UInt8 arg4);
	virtual void		Unk_FC();
	virtual void		Unk_FD();
	virtual void		Unk_FE();
	virtual void		Unk_FF();
	virtual void		Unk_100();
	virtual void		Unk_101();
	virtual void		Unk_102();
	virtual void		Unk_103();
	virtual void		Unk_104();
	virtual void		Unk_105();
	virtual void		Unk_106();
	virtual void		Unk_107();
	virtual void		Unk_108();
	virtual void		Unk_109();
	virtual CombatController* GetCombatController();
	virtual Actor*		GetCombatTarget();
	virtual void		Unk_10C();
	virtual void		Unk_10D();
	virtual void		Unk_10E();
	virtual float		GetTotalArmorDR();
	virtual float		GetTotalArmorDT();
	virtual UInt32		Unk_111();
	virtual void		Unk_112();
	virtual void		Unk_113();
	virtual void		Unk_114();
	virtual void		Unk_115();
	virtual float		CalcSpeedMult();
	virtual void		Unk_117();
	virtual void		Unk_118();
	virtual void		Unk_119();
	virtual void		Unk_11A();
	virtual void		Unk_11B();
	virtual void		Unk_11C();
	virtual void		Unk_11D();
	virtual void		Unk_11E();
	virtual void		Unk_11F();
	virtual void		Unk_120();
	virtual void		Unk_121();
	virtual void		RewardXP(UInt32 amount);
	virtual void		Unk_123();
	virtual void		Unk_124();
	virtual void		Unk_125();
	virtual void		SetPerkRank(BGSPerk* perk, UInt8 rank, bool alt);
	virtual void		RemovePerk(BGSPerk* perk, bool alt);
	virtual UInt8		GetPerkRank(BGSPerk* perk, bool alt);
	virtual void		Unk_129();
	virtual void		Unk_12A();
	virtual void		Unk_12B();
	virtual void		Unk_12C();
	virtual void		Unk_12D();
	virtual void		DoHealthDamage(Actor* attacker, float damage);
	virtual void		Unk_12F();
	virtual void		Unk_130();
	virtual float		Unk_131();
	virtual void		Unk_132();
	virtual void		Unk_133();
	virtual void		Unk_134();
	virtual void		Unk_135();
	virtual void		Unk_136();

	UInt32				GetBaseActorValue(ActorVal Code) { return this->avOwner.GetBaseActorValue(Code); }
	UInt32				GetActorValue(ActorVal Code) { return this->avOwner.GetActorValue(Code); }
	void				EquipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List, UInt32 Unk3 = 0, bool Lock = false, UInt32 Unk5 = 0) { ThisCall(0x0088C650, this, Form, Quantity, List, Unk3, Lock, Unk5); }
	void				UnequipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List, UInt32 Unk3 = 0, bool Lock = false, UInt32 Unk5 = 0) { ThisCall(0x0088C790, this, Form, Quantity, List, Unk3, Lock, Unk5); }
	bool				IsFemale() { return ThisCall(0x0087F4C0, this); }

	MagicCaster			magicCaster;				// 088
	MagicTarget			magicTarget;				// 094
	ActorValuesOwner	avOwner;					// 0A4
	CachedValuesOwner	cvOwner;					// 0A8
	void*				ragDollController;			// 0AC bhkRagdollController*
	void*				ragDollPentrationUtil;		// 0B0 bhkRagdollPenetrationUtil*
	UInt32				unk0B4;						// 0B4-
	float				flt0B8;						// 0B8
	UInt8				byte0BC;					// 0BC-
	UInt8				byte0BD;					// 0BD
	UInt8				byte0BE;					// 0BE
	UInt8				byte0BF;					// 0BF
	Actor*				killer;					// 0C0
	UInt8				byte0C4;					// 0C4-
	UInt8				byte0C5;					// 0C5
	UInt8				byte0C6;					// 0C6
	UInt8				byte0C7;					// 0C7
	float				flt0C8;						// 0C8
	float				flt0CC;						// 0CC
	TList<void>			list0D0;					// 0D0
	UInt8				byte0D8;					// 0D8
	UInt8				byte0D9;					// 0D9
	UInt8				byte0DA;					// 0DA
	UInt8				byte0DB;					// 0DB
	UInt32				unk0DC;						// 0DC
	TList<void>			list0E0;					// 0E0
	UInt8				byte0E8;					// 0E8	const 1
	UInt8				byte0E9;					// 0E9
	UInt8				byte0EA;					// 0EA
	UInt8				byte0EB;					// 0EB
	UInt32				unk0EC;						// 0EC
	UInt8				byte0F0;					// 0F0-
	UInt8				byte0F1;					// 0F1-
	UInt8				byte0F2;					// 0F2
	UInt8				byte0F3;					// 0F3
	TList<void>			list0F4;					// 0F4
	TList<void>			list0FC;					// 0FC
	bool				isInCombat;					// 104
	UInt8				jipActorFlags1;				// 105
	UInt8				jipActorFlags2;				// 106
	UInt8				jipActorFlags3;				// 107
	UInt32				LifeState;					// 108	saved as byte HasHealth = 1 or 2, optionally 6, 5 = IsRestrained
	UInt32				criticalStage;				// 10C
	UInt32				unk110;						// 110-
	float				flt114;						// 114
	UInt8				byte118;					// 118-
	UInt8				byte119;					// 119+
	UInt16				jip11A;						// 11A+
	UInt32				unk11C;						// 11C-
	UInt32				unk120;						// 120-
	bool				forceRun;					// 124
	bool				forceSneak;					// 125
	UInt8				byte126;					// 126-
	UInt8				byte127;					// 127-
	Actor*				combatTarget;				// 128
	void*				combatTargets;				// 12C BSSimpleArray<Actor*>*
	void*				combatAllies;				// 130 BSSimpleArray<Actor*>*
	UInt8				byte134;					// 134-
	UInt8				byte135;					// 135+
	UInt16				jip136;						// 136+
	UInt32				unk138;						// 138-
	UInt32				unk13C;						// 13C-
	UInt32				actorFlags;					// 140	0x80000000 - IsEssential
	bool				ignoreCrime;				// 144
	UInt8				byte145;					// 145	Has to do with package evaluation
	UInt8				byte146;					// 146	Has to do with package evaluation
	UInt8				byte147;					// 147
	UInt32				unk148;						// 148-
	UInt8				inWater;					// 14C
	UInt8				isSwimming;					// 14D
	UInt16				jip14E;						// 14E+
	UInt32				unk150;						// 150-
	float				flt154;						// 154
	float				flt158;						// 158
	UInt8				byte15C;					// 15C-
	UInt8				byte15D;					// 15D-
	UInt16				jip15E;						// 15E+
	NiPoint3			startingPos;				// 160
	float				flt16C;						// 16C
	TESForm*			startingWorldOrCell;		// 170
	UInt8				byte174;					// 174-
	UInt8				byte175;					// 175-
	UInt16				jip176;						// 176+
	float				flt178;						// 178
	float				flt17C;						// 17C
	float				flt180;						// 180
	float				flt184;						// 184
	float				flt188;						// 188
	UInt8				byte18C;					// 18C-
	bool				isTeammate;					// 18D
	UInt8				byte18E;					// 18E-
	UInt8				byte18F;					// 18F
	ActorMover*			actorMover;					// 190
	UInt32				unk194;						// 194-
	UInt32				unk198;						// 198-
	float				flt19C;						// 19C
	UInt32				unk1A0;						// 1A0-
	UInt32				unk1A4;						// 1A4-
	UInt32				unk1A8;						// 1A8-
	UInt32				SitSleepState;				// 1AC-
	UInt8				byte1B0;					// 1B0-
	bool				forceHit;					// 1B1-
	UInt8				byte1B2;					// 1B2
	UInt8				byte1B3;					// 1B3
};
assert(sizeof(Actor) == 0x1B4);

class Creature : public Actor {
public:
	virtual void	Unk_137();

	UInt32			unk1B4[3];			// 1B4
};
assert(sizeof(Creature) == 0x1C0);

class Character : public Actor {
public:
	virtual void	Unk_137();
	virtual void	Unk_138();

	void*			validBip01Names;	// 1B4 ValidBip01Names*
	float			flt1B8;				// 1B8
	float			flt1BC;				// 1BC
	UInt8			isTrespassing;		// 1C0
	UInt8			byt1C1;				// 1C1
	UInt16			unk1C2;				// 1C2
	float			unk1C4;				// 1C4
};
assert(sizeof(Character) == 0x1C8);

class PlayerCharacter : public Character {
public:
	// used to flag controls as disabled in disabledControlFlags
	enum {
		kControlFlag_Movement		= 1 << 0,
		kControlFlag_Look			= 1 << 1,
		kControlFlag_Pipboy			= 1 << 2,
		kControlFlag_Fight			= 1 << 3,
		kControlFlag_POVSwitch		= 1 << 4,
		kControlFlag_RolloverText	= 1 << 5,
		kControlFlag_Sneak			= 1 << 6,
	};

	virtual void		Unk_139();
	virtual void		Unk_13A();
	
	void				UpdateInventory() {}

	UInt32						unk1C8[(0x244-0x1C8) >> 2];		// 1C8	0224 is a package of type 1C, 208 could be a DialogPackage, 206 questObjectiveTargets is valid
	float						unk244[0x4D];					// 244	have to be a set of ActorValue
	float						unk378[0x4D];					// 378	have to be a set of ActorValue
	UInt32						unk4AC;							// 4AC
	float						unk4B0[0x4D];					// 4B0	have to be a set of ActorValue
	TList<void>					notes;							// 5E4 TList<BGSNote>
	void*						unk5EC;						// 5EC ImageSpaceModifierInstanceDOF*
	void*						unk5F0;						// 5F0 ImageSpaceModifierInstanceDOF*
	void*						unk5F4;						// 5F4 ImageSpaceModifierInstanceDRB*
	UInt32						unk5F8;							// 5F8
	TList<Actor>				teammates;						// 5FC
	UInt32						unk604[(0x648 - 0x604) >> 2];	// 604
	UInt8						unk648;							// 648
	UInt8						unk649;							// 649
	UInt8						isThirdPerson;					// 64A
	UInt8						isThirdPersonBody;				// 64B
	UInt8						bThirdPerson;					// 64C
	UInt8						DisableFading;					// 64D
	UInt8						unk64E;							// 64E
	UInt8						isPipBoy;						// 64F
	UInt8						unk650;							// 650
	UInt8						AlwaysRun;						// 651
	UInt8						AutoMove;						// 652
	UInt8						unk653;							// 653
	UInt32						unk654[7];						// 654
	float						worldFOV;						// 670
	float						firstPersonFOV;					// 674
	float						overShoulderFOV;				// 678
	UInt32						unk67C;							// 67C
	UInt8						disabledControlFlags;			// 680 kControlFlag_xxx
	UInt8						unk0681[3];						// 681
	UInt32						unk684[(0x68C - 0x684) >> 2];	// 684
	void*						playerVB01N;					// 68C ValidBip01Names*
	ActorAnimData*				firstPersonAnimData;			// 690
	NiNode*						firstPersonNiNode;				// 694
	UInt32						unk698[(0x6A8-0x698) >> 2];		// 698
	TESTopic*					topic;							// 6A8
	UInt32						unk6AC[3];						// 6AC
	TESQuest*					quest;							// 6B8
	TList<void>					questObjectiveList;				// 6BC TList<BGSQuestObjective>
	UInt32						unk6C4[39];				// 6C4
	TESRegion*					currentRegion;			// 760
	TESRegionList				regionsList;			// 764
	UInt32						unk770[10];				// 770
	UInt8						isTravelPackage;		// 798
	UInt8						isWakeUpPackage;		// 799
	UInt8						isDrinkPackage;			// 79A
	UInt8						isUnkPackage;			// 79B
	UInt32						unk79C[7];				// 79C
	UInt8						gameDifficulty;			// 7B8
	UInt8						pad7B9[3];				// 7B9
	bool						isHardcore;				// 7BC
	UInt8						pad7BD[3];				// 7BD
	UInt32						unk7C0[49];				// 7C0
	TList<void>					perkEntries[74];		// 884 TList<BGSEntryPointPerkEntry>
	UInt32						unkAD4[161];			// AD4
	NiPoint3					ReticleOffset;			// D58
	void*						combatActors;			// D64 CombatActors
	UInt32						teammateCount;			// D68
	UInt32						unkD6C[5];				// D6C
	NiNode*						niNodeD80;				// D80
	UInt32						unkD84[12];				// D84
	NiNode*						niNodeDB4;				// DB4
	UInt32						unkDB8[7];				// DB8
	NiPoint3					vectorDD4;				// DD4
	NiPoint3					cameraPos;				// DE0
	void*						rigidBody;				// DEC bhkRigidBody
	bool						isInCombat;				// DF0
	bool						isUnseen;				// DF1
	UInt8						byteDF2;				// DF2
	UInt8						byteDF3;				// DF3
	UInt32						unkDF4[23];				// DF4
};
assert(sizeof(PlayerCharacter) == 0xE50);

struct ActorHitInfo {
	TESObjectREFR*		source;			// 00
	Actor*				target;			// 04
	void*				projectile;		// 08 Projectile*
	UInt32				unk0C;			// 0C
	SInt32				hitLocation;	// 10
	float				healthDmg;		// 14
	float				unk18;			// 18
	float				unk1C;			// 1C
	float				limbDmg;		// 20
	float				unk24;			// 24
	float				unk28;			// 28
	float				unk2C;			// 2C
	TESObjectWEAP*		weapon;			// 30
	float				healthPerc;		// 34
	UInt32				unk38[8];		// 38
	UInt32				flags;			// 58
	float				unk5C;			// 5C
	UInt32				unk60;			// 60
};
assert(sizeof(ActorHitInfo) == 0x064);

class BaseProcess {
public:
	virtual void	FreeThis(bool noDealloc);
	virtual void	Unk_01();
	virtual void	Unk_02();
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05();
	virtual void	Unk_06();
	virtual void	Unk_07();
	virtual void	Unk_08();
	virtual void	Unk_09();
	virtual void	Unk_0A();
	virtual void	Unk_0B();
	virtual void	Unk_0C();
	virtual void	Unk_0D();
	virtual void	Unk_0E();
	virtual void	Unk_0F();
	virtual void	Unk_10();
	virtual void	Unk_11();
	virtual void	Unk_12();
	virtual void	Unk_13();
	virtual void	Unk_14();
	virtual void	Unk_15();
	virtual void	Unk_16();
	virtual void	Unk_17();
	virtual void	Unk_18();
	virtual void	Unk_19();
	virtual void	Unk_1A();
	virtual void	Unk_1B();
	virtual void	Unk_1C();
	virtual void	Unk_1D();
	virtual void	Unk_1E();
	virtual void	Unk_1F();
	virtual void	Unk_20();
	virtual void	Unk_21();
	virtual void	Unk_22();
	virtual void	Unk_23();
	virtual void	Unk_24();
	virtual void	Unk_25();
	virtual void	Unk_26();
	virtual void	Unk_27();
	virtual void	Unk_28();
	virtual void	Unk_29();
	virtual void	Unk_2A();
	virtual void	Unk_2B();
	virtual void	Unk_2C();
	virtual void	Unk_2D();
	virtual void	Unk_2E();
	virtual void	Unk_2F();
	virtual void	Unk_30();
	virtual void	Unk_31();
	virtual void	Unk_32();
	virtual void	Unk_33();
	virtual void	Unk_34();
	virtual void	Unk_35();
	virtual void	Unk_36();
	virtual void	Unk_37();
	virtual void	Unk_38();
	virtual void	Unk_39();
	virtual void	Unk_3A();
	virtual void	Unk_3B();
	virtual void	Unk_3C();
	virtual void	Unk_3D();
	virtual void	Unk_3E();
	virtual void	Unk_3F();
	virtual void	Unk_40();
	virtual void	Unk_41();
	virtual void	Unk_42();
	virtual void	Unk_43();
	virtual void	Unk_44();
	virtual void	Unk_45();
	virtual void	Unk_46();
	virtual void	Unk_47();
	virtual void	Unk_48();
	virtual void	Unk_49();
	virtual TESForm* GetLowProcess40();
	virtual void	Unk_4B();
	virtual void	Unk_4C();
	virtual void	Unk_4D();
	virtual void	Unk_4E();
	virtual void	Unk_4F();
	virtual void	Unk_50();
	virtual void	Unk_51();
	virtual InventoryChanges::EntryData* GetWeaponInfo();
	virtual InventoryChanges::EntryData* GetAmmoInfo();
	virtual void	Unk_54();
	virtual void	Unk_55();
	virtual void	Unk_56();
	virtual void	Unk_57();
	virtual void	Unk_58();
	virtual void	Unk_59();
	virtual void	Unk_5A();
	virtual void	Unk_5B();
	virtual void	Unk_5C();
	virtual void	Unk_5D();	// Called by 5E with count itemExtraList item
	virtual void	Unk_5E();	// EquipItem and UnEquipItem doEquip item count itemExtraList bytes = [equipArgC lockUnequip unk unEquipArcC lockEquip arg14 ] (arg as from Actor::(Un)EquipItem)
	virtual void	Unk_5F();
	virtual void	Unk_60();
	virtual void	Unk_61();
	virtual void	Unk_62();
	virtual void	Unk_63();
	virtual void	Unk_64();
	virtual void	Unk_65();
	virtual void	Unk_66();
	virtual void	Unk_67();
	virtual void	Unk_68();
	virtual void	Unk_69();
	virtual void	Unk_6A();
	virtual void	Unk_6B();
	virtual void	Unk_6C();
	virtual void	Unk_6D();
	virtual void	Unk_6E();
	virtual void	Unk_6F();
	virtual void	Unk_70();
	virtual void	Unk_71();
	virtual void	Unk_72();
	virtual void	Unk_73();
	virtual void	Unk_74();
	virtual void	Unk_75();
	virtual void	Unk_76();
	virtual void	Unk_77();
	virtual void	Unk_78();
	virtual void	Unk_79();
	virtual void	Unk_7A();
	virtual void	Unk_7B();
	virtual void	Unk_7C();
	virtual void	Unk_7D();
	virtual void	Unk_7E();
	virtual void	Unk_7F();
	virtual void	Unk_80();
	virtual void	Unk_81();
	virtual void	Unk_82();
	virtual TESPackage* GetInterruptPackage();
	virtual void	SetInterruptPackage(TESPackage* package, Actor* onActor);
	virtual void	StopInterruptPackage();
	virtual void	Unk_86();	// 086 - SetInterruptPackageTargetRef
	virtual void	Unk_87();	// 087 - SetInterruptPackageTargetRef
	virtual void	Unk_88();	// 088 - IncreaseInterruptPackageUnk00C
	virtual void	Unk_89();
	virtual void	Unk_8A();
	virtual TESPackage* GetStablePackage();
	virtual void	SetStablePackage(TESPackage* package, Actor* onActor);
	virtual void	StopStablePackage();
	virtual void	Unk_8E();
	virtual void	Unk_8F();
	virtual void	Unk_90();
	virtual void	Unk_91();
	virtual void	Unk_92();	// Only HighProcess, get Unk0454
	virtual void	Unk_93();
	virtual void	Unk_94();
	virtual void	Unk_95();
	virtual void	Unk_96();
	virtual void	Unk_97();
	virtual void	Unk_98();
	virtual void	Unk_99();
	virtual void	Unk_9A();
	virtual void	Unk_9B();
	virtual void	Unk_9C();
	virtual void	Unk_9D();
	virtual void	Unk_9E();
	virtual TESPackage* GetCurrentPackage();
	virtual UInt32	GetPackageInfo0C();
	virtual void	Unk_A1();
	virtual void	Unk_A2();
	virtual bhkCharacterController* GetCharacterController();
	virtual void	Unk_A4();
	virtual void	Unk_A5();
	virtual void	Unk_A6();
	virtual void	Unk_A7();
	virtual void	Unk_A8();
	virtual void	Unk_A9();
	virtual void	Unk_AA();
	virtual void	Unk_AB();
	virtual void	Unk_AC();
	virtual void	Unk_AD();
	virtual void	Unk_AE();
	virtual void	Unk_AF();
	virtual void	Unk_B0();
	virtual void	Unk_B1();
	virtual void	Unk_B2();
	virtual void	Unk_B3();
	virtual void	Unk_B4();
	virtual void	Unk_B5();
	virtual void	Unk_B6();
	virtual void	Unk_B7();
	virtual void	Unk_B8();
	virtual void	Unk_B9();
	virtual void	Unk_BA();
	virtual void	Unk_BB();
	virtual void	Unk_BC();
	virtual void	Unk_BD();
	virtual void	Unk_BE();
	virtual void	SetDiveBreath(float breath);
	virtual float	GetDiveBreath();
	virtual void	Unk_C1();
	virtual void	Unk_C2();
	virtual void	Unk_C3();
	virtual void	Unk_C4();
	virtual void	Unk_C5();
	virtual void	Unk_C6();
	virtual bool	GetAlerted();
	virtual void	SetAlert(bool alert);
	virtual void	Unk_C9();
	virtual void	Unk_CA();
	virtual void	Unk_CB();
	virtual void	Unk_CC();
	virtual void	Unk_CD();
	virtual void	Unk_CE();
	virtual void	Unk_CF();
	virtual void	Unk_D0();
	virtual void	Unk_D1();
	virtual void	Unk_D2();
	virtual void	Unk_D3();
	virtual void	Unk_D4();
	virtual void	Unk_D5();
	virtual void	Unk_D6();
	virtual void	Unk_D7();
	virtual void	Unk_D8();
	virtual void	Unk_D9();
	virtual void	Unk_DA();
	virtual void	Unk_DB();
	virtual void	Unk_DC();
	virtual void	Unk_DD();
	virtual void	Unk_DE();
	virtual void	Unk_DF();
	virtual void	Unk_E0();
	virtual void	Unk_E1();
	virtual void	Unk_E2();
	virtual TESIdleForm* GetIdleForm10C();
	virtual void	SetIdleForm10C(TESIdleForm* idleForm);
	virtual void	StopIdle();
	virtual void	Unk_E6();
	virtual void	Unk_E7();	// float GetActorValue
	virtual void	Unk_E8();
	virtual void	Unk_E9();
	virtual void	Unk_EA();
	virtual void	Unk_EB();
	virtual void	Unk_EC();
	virtual void	Unk_ED();
	virtual void	Unk_EE();
	virtual void	Unk_EF();
	virtual void	Unk_F0();
	virtual void	Unk_F1();
	virtual void	Unk_F2();
	virtual void	Unk_F3();
	virtual void	Unk_F4();
	virtual void	Unk_F5();
	virtual void	Unk_F6();
	virtual void	Unk_F7();
	virtual void	Unk_F8();
	virtual SInt16	GetCurrentAction();
	virtual void	Unk_FA();
	virtual void	Unk_FB();
	virtual void	Unk_FC();
	virtual void	Unk_FD();
	virtual void	Unk_FE();
	virtual void	Unk_FF();
	virtual void	Unk_100();
	virtual void	Unk_101();
	virtual void	Unk_102();
	virtual SInt32	GetKnockedState();
	virtual void	SetKnockedState(char state);
	virtual void	Unk_105();
	virtual void	Unk_106();
	virtual void	Unk_107();
	virtual void	Unk_108();
	virtual void	Unk_109();
	virtual void	Unk_10A();
	virtual void	Unk_10B();
	virtual void	Unk_10C();
	virtual void	Unk_10D();
	virtual void	Unk_10E();
	virtual void	Unk_10F();
	virtual void	Unk_110();
	virtual void	Unk_111();
	virtual void	Unk_112();
	virtual void	Unk_113();
	virtual void	Unk_114();
	virtual bool	IsWeaponOut();
	virtual void	SetWeaponOut(Actor* actor, bool weaponOut);
	virtual void	Unk_117();
	virtual void	Unk_118();
	virtual void	Unk_119(Actor* actor);
	virtual void	Unk_11A(UInt32 unk);
	virtual void	Unk_11B();
	virtual void	Unk_11C();
	virtual void	Unk_11D();
	virtual void	Unk_11E();
	virtual void	Unk_11F();
	virtual void	Unk_120();
	virtual void	Unk_121();
	virtual void	Unk_122();
	virtual void	Unk_123();
	virtual void	Unk_124();
	virtual void	Unk_125();
	virtual void	Unk_126();
	virtual void	Unk_127();
	virtual void	Unk_128();
	virtual void	Unk_129();
	virtual void	Unk_12A();
	virtual void	Unk_12B();
	virtual void	Unk_12C();
	virtual void	Unk_12D();
	virtual void	Unk_12E();
	virtual void	Unk_12F();
	virtual void	Unk_130();
	virtual void	Unk_131();
	virtual void	Unk_132();
	virtual void	Unk_133();
	virtual void	Unk_134();
	virtual void	Unk_135();
	virtual void	Unk_136();
	virtual void	Unk_137();
	virtual void	Unk_138();
	virtual void	Unk_139();
	virtual void	Unk_13A();
	virtual void	Unk_13B();
	virtual void	Unk_13C();
	virtual void	Unk_13D();
	virtual void	Unk_13E();
	virtual void	Unk_13F(UInt32 unk);
	virtual void	Unk_140();
	virtual void*	GetDetectionData(Actor* target, UInt32 detecting);
	virtual void	Unk_142();
	virtual void	Unk_143();
	virtual void	Unk_144();
	virtual void	Unk_145();
	virtual void	Unk_146();
	virtual void	Unk_147();
	virtual void	Unk_148();
	virtual void	Unk_149();
	virtual void	Unk_14A();
	virtual void	Unk_14B();
	virtual void	Unk_14C();
	virtual void	Unk_14D();
	virtual void	Unk_14E();
	virtual void	Unk_14F();
	virtual void	Unk_150();
	virtual void	Unk_151();
	virtual void	Unk_152();
	virtual void	Unk_153();
	virtual void	Unk_154();
	virtual void	Unk_155();
	virtual void	Unk_156();
	virtual void	Unk_157();
	virtual void	Unk_158();
	virtual void	Unk_159();
	virtual void	Unk_15A();
	virtual void	Unk_15B();
	virtual void	Unk_15C();
	virtual void	Unk_15D();
	virtual void	Unk_15E();
	virtual void	Unk_15F();
	virtual void	Unk_160();
	virtual void	Unk_161();
	virtual void	Unk_162();
	virtual void	Unk_163();
	virtual void	Unk_164();
	virtual void	Unk_165();
	virtual void	Unk_166();
	virtual void	Unk_167();
	virtual void	Unk_168();
	virtual void	Unk_169();
	virtual void	Unk_16A();
	virtual float	GetActorAlpha();
	virtual void	SetActorAlpha(float alpha);
	virtual void	Unk_16D();
	virtual void	Unk_16E();
	virtual void	Unk_16F();
	virtual void	Unk_170();
	virtual void	Unk_171();
	virtual void	Unk_172();
	virtual void	Unk_173();
	virtual void	Unk_174();
	virtual void	Unk_175();
	virtual void	Unk_176();
	virtual void	Unk_177();
	virtual void	Unk_178();
	virtual void	Unk_179();
	virtual void	Unk_17A();
	virtual void	Unk_17B();
	virtual void	Unk_17C();
	virtual void	Unk_17D();
	virtual void	Unk_17E();
	virtual void	Unk_17F();
	virtual void	Unk_180();
	virtual void	Unk_181();
	virtual void	Unk_182();
	virtual void	Unk_183();
	virtual void	Unk_184();
	virtual void	SetQueuedIdleFlags(UInt32 flags);
	virtual void	Unk_186();
	virtual void	Unk_187();
	virtual void	Unk_188();
	virtual void	Unk_189();
	virtual void	Unk_18A(Actor* actor);
	virtual void	Unk_18B();
	virtual void	Unk_18C();
	virtual void	Unk_18D();
	virtual void	Unk_18E();
	virtual void	Unk_18F();
	virtual void	Unk_190();
	virtual void	Unk_191();
	virtual void	Unk_192(UInt8 unk);
	virtual void	Unk_193();
	virtual void	Unk_194();
	virtual void	Unk_195();
	virtual void	Unk_196();
	virtual void	Unk_197();
	virtual void	Unk_198();
	virtual void	Unk_199();
	virtual void	Unk_19A();
	virtual void	Unk_19B();
	virtual void	Unk_19C();
	virtual void	Unk_19D();
	virtual void	Unk_19E();
	virtual void	Unk_19F();
	virtual void	Unk_1A0();
	virtual void	Unk_1A1();
	virtual void	Unk_1A2();
	virtual void	Unk_1A3();
	virtual void	Unk_1A4();
	virtual void	Unk_1A5();
	virtual void	Unk_1A6();
	virtual void	Unk_1A7();
	virtual void	Unk_1A8();
	virtual void	Unk_1A9();
	virtual void	Unk_1AA();
	virtual void	Unk_1AB();
	virtual void	Unk_1AC();
	virtual void	Unk_1AD();
	virtual void	Unk_1AE();
	virtual void	Unk_1AF();
	virtual void	Unk_1B0();
	virtual void	Unk_1B1();
	virtual void	Unk_1B2();
	virtual void	Unk_1B3();
	virtual void	Unk_1B4();
	virtual void	Unk_1B5();
	virtual void	Unk_1B6();
	virtual void	Unk_1B7();
	virtual void	Unk_1B8();
	virtual void	Unk_1B9();
	virtual void	Unk_1BA();
	virtual void	Unk_1BB();
	virtual void	Unk_1BC();
	virtual void	Unk_1BD();
	virtual void	Unk_1BE();
	virtual void	Unk_1BF();
	virtual void	Unk_1C0();
	virtual void	Unk_1C1();
	virtual void	Unk_1C2();
	virtual void	Unk_1C3();
	virtual void	Unk_1C4();
	virtual void	Unk_1C5();
	virtual TESIdleForm* GetIdleForm350();
	virtual void	SetIdleForm350(TESIdleForm* idleForm);
	virtual void	Unk_1C8();
	virtual void	Unk_1C9();
	virtual void	Unk_1CA();
	virtual void	Unk_1CB();
	virtual void	Unk_1CC();
	virtual float	GetLightAmount();
	virtual void	SetLightAmount(float lightAmount);
	virtual void	Unk_1CF();
	virtual void	Unk_1D0();
	virtual void	Unk_1D1();
	virtual void	Unk_1D2();
	virtual void	Unk_1D3();
	virtual void	Unk_1D4();
	virtual void	Unk_1D5();
	virtual void	Unk_1D6();
	virtual void	Unk_1D7();
	virtual void	Unk_1D8();
	virtual void	Unk_1D9();
	virtual void	Unk_1DA();
	virtual float	GetRadsSec();
	virtual ActorHitInfo* GetHitInfo();
	virtual void	CopyHitInfo(ActorHitInfo* hitInfo);
	virtual void	ResetHitInfo();
	virtual ActorHitInfo* GetHitInfo254();
	virtual void	CopyHitInfo254(ActorHitInfo* hitInfo);
	virtual void	ResetHitInfo254();
	virtual void	Unk_1E2();
	virtual void	Unk_1E3();
	virtual void	Unk_1E4();
	virtual void	Unk_1E5();
	virtual void	Unk_1E6();
	virtual void	Unk_1E7();
	virtual void	Unk_1E8();
	virtual void	Unk_1E9();
	virtual void	Unk_1EA();
	virtual void	Unk_1EB();
	virtual void	Unk_1EC();
	virtual void	Unk_1ED();	// Leads to Last Target

	class Data2C {
	public:
		float	unk00[12];
		UInt32	unk30[2];
		float	unk38[2];
		UInt8	unk40;
		UInt8	pad41[3];
		UInt32	flags;		// 44	flags, bit28 = IsGhost
	};

	PackageInfo		currentPackage;	// 04
	float			unk1C;			// 1C	not initialized, only by descendant!
	float			unk20;			// 20	not initialized, only by descendant to -1.0! flt020 gets set to GameHour minus one on package evaluation
	UInt32			unk24;			// 24	not initialized, only by descendant!
	UInt32			processLevel;	// 28	not initialized, only by descendant to 3 for Low, 2 for MidlleLow, 1 MiddleHighProcess and 0 for HigProcess
	Data2C*			unk2C;			// 2C
};
assert(sizeof(BaseProcess) == 0x030);

class LowProcess : public BaseProcess {
public:
	struct FloatPair {
		float	flt000;
		float	flt004;
	};

	class ActorValueModifier {
	public:
		UInt8	actorValue;	// 00 Might allow for other values
		UInt8	pad[3];		// 01
		float	damage;		// 04
	};

	struct ActorValueModifiers {
		TList<ActorValueModifier>	avModifierList;	// 00
		UInt8						unk008;			// 08
		UInt8						pad009[3];		// 09
		void**						modifiedAV;	// 0C	array of damaged actorValue
	};

	virtual void	Unk_1EE();
	virtual void	Unk_1EF();
	virtual void	Unk_1F0();
	virtual void	Unk_1F1();
	virtual void	Unk_1F2();
	virtual void	Unk_1F3();
	virtual void	Unk_1F4();
	virtual void	Unk_1F5();
	virtual void	Unk_1F6();
	virtual void	Unk_1F7();
	virtual void	Unk_1F8();
	virtual void	Unk_1F9();
	virtual void	Unk_1FA();
	virtual void	Unk_1FB();
	virtual void	Unk_1FC();
	virtual void	Unk_1FD();
	virtual void	Unk_1FE();
	virtual void	Unk_1FF();
	virtual void	Unk_200();
	virtual void	Unk_201();
	virtual void	Unk_202();
	virtual void	Unk_203();
	virtual void	Unk_204();
	virtual void	Unk_205();
	virtual void	Unk_206();

	UInt8				byte30;		// 8 = IsAlerted
	UInt8				pad31[3];
	UInt32				unk34;
	FloatPair			unk38;
	TESForm*			unk40;		// Used when picking idle anims.
	UInt32				unk44;		// not initialized!	refr, expected actor, might be CombatTarget
	UInt32				unk48;
	UInt32				unk4C;
	UInt32				unk50;
	UInt32				unk54;		// not initialized!
	UInt32				unk58;
	UInt32				unk5C;
	TList<UInt32>		unk60;		// List
	UInt32				unk68;
	UInt32				unk6C;
	TList<TESForm>		unk70;
	TList<UInt32>		unk78;
	TList<UInt32>		unk80;
	UInt32				unk88;
	UInt32				unk8C;
	UInt32				unk90;
	UInt32				unk94;
	ActorValueModifiers	damageModifiers;
	float				gameDayDied;
	UInt32				unkAC;		// not initialized!
	UInt32				unkB0;		// not initialized!
};
assert(sizeof(LowProcess) == 0x0B4);

class MiddleLowProcess : public LowProcess {
public:
	virtual void		Unk_207();

	UInt32				unk0B4;			// B4
	ActorValueModifiers	tempModifiers;	// B8
};
assert(sizeof(MiddleLowProcess) == 0x0C8);

class MiddleHighProcess : public MiddleLowProcess {
public:
	virtual void	SetAnimation(UInt32 newAnimation);
	virtual void	Unk_209();
	virtual void	Unk_20A();
	virtual void	Unk_20B();
	virtual void	Unk_20C();
	virtual void	Unk_20D();
	virtual void	Unk_20E();
	virtual void	Unk_20F();
	virtual void	Unk_210();
	virtual void	Unk_211();
	virtual void	Unk_212();
	virtual void	Unk_213();
	virtual void	Unk_214();
	virtual void	Unk_215();
	virtual void	Unk_216();
	virtual void	Unk_217();
	virtual void	Unk_218();
	virtual void	Unk_219();
	virtual void	Unk_21A();
	virtual void	Unk_21B();

	TList<TESForm>						unk0C8;				// 0C8
	TList<UInt32>						unk0D0;				// 0D0
	UInt32								unk0D8[3];			// 0D8
	PackageInfo							interruptPackage;	// 0E4
	UInt8								unk0FC[12];			// 0FC	Saved as one, might be Pos/Rot given size
	UInt32								unk108;				// 108
	TESIdleForm*						idleForm10C;		// 10C
	UInt32								unk110;				// 110  EntryData, also handled as part of weapon code. AmmoInfo.
	InventoryChanges::EntryData*	weaponInfo;			// 114
	InventoryChanges::EntryData*	ammoInfo;			// 118
	void*								unk11C;				// 11C QueuedFile*
	UInt8								byt120;				// 120
	UInt8								byt121;				// 121
	UInt8								byt122;				// 122
	UInt8								fil123;				// 123
	UInt32								unk124;				// 124
	UInt32								unk128;				// 128 Gets copied over during TESNPC.CopyFromBase
	UInt8								byt12C;				// 12C
	UInt8								byt12D;				// 12D
	UInt8								byt12E;				// 12E
	UInt8								byt12F;				// 12F
	void*								ptr130;			// 130	its an animation. Current Animation?
	UInt8								byt134;				// 134
	bool								isWeaponOut;		// 135
	UInt8								byt136;				// 136
	UInt8								byt137;				// 137
	bhkCharacterController*				charCtrl;			// 138
	UInt8								KnockedState;		// 13C
	UInt8								unk13D[3];			// 13D
	UInt32								unk140[8];			// 140
	MagicItem*							magicItem160;		// 160
	UInt32								unk164[3];			// 164
	float								actorAlpha;			// 170
	UInt32								unk174;				// 174
	void*								unk178;				// 178 BSFaceGenAnimationData*
	UInt32								unk17C[15];			// 17C
	void*								unk1B8;				// 1B8
	MagicTarget*						magicTarget1BC;		// 1BC
	ActorAnimData*						animData;			// 1C0
	BSAnimGroupSequence*				animSequence[3];	// 1C4
	UInt32								unk1D0[3];			// 1D0
	NiNode*								limbNodes[15];		// 1DC
	NiNode*								unk218;				// 218
	NiNode*								unk21C;				// 21C
	void*								ptr220;				// 220
	BSBound*							boundingBox;		// 224
	UInt32								unk228[3];			// 228
	float								radsSec234;			// 234
	float								rads238;			// 238
	float								waterRadsSec;		// 23C
	ActorHitInfo*						hitInfo240;			// 240
	UInt32								unk244;				// 244
	void*								unk248;				// 248 BSFaceGenNiNode*
	void*								unk24C;				// 24C BSFaceGenNiNode*
	NiTriShape*							unk250;				// 250
	ActorHitInfo*						hitInfo254;			// 254
	UInt32								unk258;				// 258
};
assert(sizeof(MiddleHighProcess) == 0x25C);

class HighProcess : public MiddleHighProcess {
public:
	enum {
		kAction_None = -1,
		kAction_Equip_Weapon = 0,
		kAction_Unequip_Weapon = 1,
		kAction_Attack = 2,
		kAction_Attack_Follow_Through = 3,
		kAction_Attack_Latency = 4,
		kAction_Attack_Throw_Attach = 5,
		kAction_Attack_Throw_Release = 6,
		kAction_Block = 7,
		kAction_Stagger = 8,
		kAction_Reload = 9,
		kAction_Dodge = 10,
		kAction_Wait_For_Lower_Body_Anim = 11,
		kAction_Wait_For_Special_Idle = 12,
		kAction_Force_Script_Anim = 13,
	};

	TList<void>*				detectedActors;		// 25C TList<DetectionData>*
	TList<void>*				detectingActors;	// 260 TList<DetectionData>*
	void*						ptr264;				// 264
	void*						ptr268;				// 268
	void*						ptr26C;				// 26C
	UInt32						unk270;				// 270
	TList<void>					unk274;				// 274 TList<CombatTarget>
	UInt32						unk27C;				// 27C
	UInt32						unk280;				// 280
	UInt32						unk284[24];			// 284
	void*						ptr2E4;				// 2E4 NiBSBoneLODController*
	UInt32						unk2E8;				// 2E8
	SInt16						currentAction;		// 2EC
	UInt8						pad2EE[2];			// 2EE
	BSAnimGroupSequence*		currentSequence;	// 2F0
	UInt32						unk2F4[18];			// 2F4
	float						diveBreath;			// 33C
	UInt32						unk340[4];			// 340
	TESIdleForm*				idleForm350;		// 350
	UInt32						unk354[4];			// 354
	void**						ptr364;				// 364 NiBSplineCompTransformInterpolator**
	UInt32						unk368[23];			// 368
	float						lightAmount;		// 3C4
	UInt32						unk3C8[8];			// 3C8
	UInt32						fadeType;			// 3E8
	float						delayTime;			// 3EC
	UInt32						unk3F0;				// 3F0
	UInt32						unk3F4;				// 3F4
	UInt32						unk3F8[3];			// 3F8
	Actor*						combatTarget;		// 404
	UInt32						unk408[5];			// 408
	TESObjectREFR*				packageTarget;		// 41C
	UInt32						unk420;				// 420
	UInt32						queuedIdleFlags;	// 424
	UInt32						unk428[3];			// 428
	void*						ptr434;				// 434 bhkShapePhantom*
	UInt32						unk438;				// 438
	float						unk43C;				// 43C
	float						radsSec440;			// 440
	UInt8						plantedExplosive;	// 444
	UInt8						pad445[3];			// 445
	UInt32						unk448[9];			// 448
};
assert(sizeof(HighProcess) == 0x46C);

class AnimSequenceBase {
public:
	virtual void					Destructor(UInt8 Arg);
	virtual void					AddAnimGroupSequence(BSAnimGroupSequence* AnimGroupSequence);
	virtual void					Unk_02();
	virtual UInt8					IsSingle();
	virtual BSAnimGroupSequence*	GetAnimGroupSequence(int Index); // Index is not used if Single (returns the anim); Index = -1 returns a random anim in the NiTList<BSAnimGroupSequence>* for Multiple
	virtual BSAnimGroupSequence*	GetAnimGroupSequence2(void* Unk01);
	virtual void					Unk_06();
};
assert(sizeof(AnimSequenceBase) == 0x004);

class AnimSequenceSingle : public AnimSequenceBase {
public:
	BSAnimGroupSequence* Anim;	// 04
};
assert(sizeof(AnimSequenceSingle) == 0x008);

class AnimSequenceMultiple : public AnimSequenceBase {
public:
	NiTList<BSAnimGroupSequence>* Anims;	// 04
};
assert(sizeof(AnimSequenceMultiple) == 0x008);

class ActorAnimData {
public:
	UInt32						unk000;				// 000
	Actor*						actor;				// 004
	NiNode*						RootNode;			// 008
	NiNode*						AccumNode;			// 00C
	UInt32						unk010;				// 010
	float						unk014;				// 014
	float						unk018;				// 018
	UInt32						unk01C;				// 01C
	float						unk020;				// 020
	UInt32						unk024;				// 024
	NiNode*						nPelvis;			// 028
	NiNode*						nBip01;				// 02C
	NiNode*						nLForearm;			// 030
	NiNode*						nHead;				// 034
	NiNode*						nWeapon;			// 038
	UInt32						unk03C[2];			// 03C
	NiNode*						nNeck1;				// 044
	UInt32						unk048[34];			// 048
	float						unk0D0;				// 0D0
	UInt32						unk0D4;				// 0D4
	NiControllerManager*		manager;			// 0D8
	NiTMap<UInt32, AnimSequenceBase>*	animsMap;			// 0DC
	BSAnimGroupSequence*		animSequences[8];	// 0E0
	BSAnimGroupSequence*		animSeq100;			// 100
	UInt32						unk104;				// 104
	UInt32						unk108;				// 108
	float						unk10C;				// 10C
	float						unk110;				// 110
	float						unk114;				// 114
	float						unk118;				// 118
	float						unk11C;				// 11C
	UInt32						unk120;				// 120
	void*						unk124;				// 124
	void*						unk128;				// 128
};
assert(sizeof(ActorAnimData) == 0x12C);

class SkyObject {
public:
	virtual void*	Destroy(bool doFree);
	virtual void	Fn_01(void);
	virtual void	Fn_02(NiNode* niNode);
	virtual void	Update(void* sky, float value);

	NiNode*				RootNode;	// 04
};
assert(sizeof(SkyObject) == 0x08);

class Sun : public SkyObject {
public:
	NiBillboardNode*	SunBillboard;		// 08
	NiBillboardNode*	SunGlareBillboard;	// 0C
	NiTriShape*			SunGeometry;		// 10
	NiTriShape*			SunGlareGeometry;	// 14
	NiTArray<NiPick*>*	SunPickList;		// 18
	NiDirectionalLight* SunDirLight;		// 1C
	float				flt20;				// 20
	UInt8				byte24;				// 24
	UInt8				byte25;				// 25
	UInt8				byte26;				// 26
	UInt8				byte27;				// 27
	void*				shaderAccum;		// 28 BSShaderAccumulator*
};
assert(sizeof(Sun) == 0x2C);

class Atmosphere : public SkyObject {		// From Oblivion
public:
	NiAVObject*		Mesh;					// 08
	BSFogProperty*	fogProperty;			// 0C
	UInt32			unk10;					// 10
	NiNode*			Quad;					// 14
	UInt8			unk18;					// 18
	UInt8			pad18[3];

};
assert(sizeof(Atmosphere) == 0x01C);

class Stars : public SkyObject {			// From Oblivion
public:
	UInt32			unk08;					// 08
	float			unk0C;					// 0C
};
assert(sizeof(Stars) == 0x010);

class Clouds : public SkyObject {
public:

	NiTriStrips*		layer0;	// 08	(NiTriStrips)
	NiTriStrips*		layer1;	// 0C		"
	NiTriStrips*		layer2;	// 10		"
	NiTriStrips*		layer3;	// 14		"
	UInt32			unk18[4];	// 18
	float			flt28;		// 28
	float			flt2C;		// 2C
	float			flt30;		// 30
	float			flt34;		// 34
	float			flt38;		// 38
	float			flt3C;		// 3C
	float			flt40;		// 40
	float			flt44;		// 44
	float			flt48;		// 48
	float			flt4C;		// 4C
	float			flt50;		// 50
	float			flt54;		// 54
	UInt32			numLayers;	// 58
};
assert(sizeof(Clouds) == 0x05C);

class Precipitation {
public:
	virtual void*	Destroy(bool doFree);

	NiNode*		node04;		// 04
	NiNode*		node08;		// 08
	UInt32		unk0C;		// 0C
	float		unk10;		// 10
	UInt32		unk14;		// 14
};
assert(sizeof(Precipitation) == 0x018);

class Moon : public SkyObject {
public:
	NiNode*			MoonNode;				// 08
	NiNode*			ShadowNode;				// 0C
	NiTriShape*		MoonMesh;				// 10
	NiTriShape*		ShadowMesh;				// 14
	char*			texture_full;			// 18
	UInt32			unk1C;					// 1C
	char*			texture_three_wan;		// 20
	UInt32			unk24;					// 24
	char*			texture_half_wan;		// 28
	UInt32			unk2C;					// 2C
	char*			texture_one_wan;		// 30
	UInt32			unk34;					// 34
	UInt32			unk38;					// 38
	UInt32			unk3C;					// 3C
	char*			texture_one_wax;		// 40
	UInt32			unk44;					// 44
	char*			texture_half_wax;		// 48
	UInt32			unk4C;					// 4C
	char*			texture_three_wax;		// 50
	UInt32			unk54;					// 54
	float			unk58;					// 58
	float			unk5C;					// 5C
	float			unk60;					// 60
	float			unk64;					// 64
	float			unk68;					// 68
	UInt32			unk6C;					// 6C
	UInt32			unk70;					// 70
	float			unk74;					// 74
	float			unk78;					// 78
};
assert(sizeof(Moon) == 0x07C);

class Sky {
public:
	void ForceWeather(TESWeather* Weather) { ThisCall(0x0063D0E0, this, Weather, 0); }

	void**			_vtbl;				// 000
	NiNode*			nodeSkyRoot;		// 004
	NiNode*			nodeMoonsRoot;		// 008
	TESClimate*		firstClimate;		// 00C
	TESWeather*		firstWeather;		// 010
	TESWeather*		secondWeather;		// 014
	TESWeather*		weather018;			// 018
	TESWeather*		weatherOverride;	// 01C
	Atmosphere*		atmosphere;			// 020
	Stars*			stars;				// 024
	Sun*			sun;				// 028
	Clouds*			clouds;				// 02C
	Moon*			masserMoon;			// 030
	Moon*			secundaMoon;		// 034
	Precipitation*	precipitation;		// 038
	NiPoint3		vector03C;			// 03C
	NiColor			waterReflection;	// 048
	NiPoint3		vector054;			// 054
	NiColor			sunAmbient;			// 060
	NiColor			sunDirectional;		// 06C
	NiPoint3		vector078;			// 078
	NiPoint3		vector084;			// 084
	NiPoint3		vector090;			// 090
	NiPoint3		vector09C;			// 09C
	NiPoint3		vector0A8;			// 0A8
	NiPoint3		vector0B4;			// 0B4
	NiColor			sunFog;				// 0C0
	float			windSpeed;			// 0CC
	float			windDirection;		// 0D0
	UInt32			unk0D4[6];			// 0D4
	float			gameHour;			// 0EC
	float			lastUpdateHour;		// 0F0
	float			weatherPercent;		// 0F4
	UInt32			unk0F8;				// 0F8
	UInt32			unk0FC;				// 0FC
	float			lightningFxPerc;	// 100
	UInt32			unk104;				// 104
	float			flt108;				// 108
	float			flt10C;				// 10C
	float			flt110;				// 110
	UInt32			unk114;				// 114
	UInt32			flags;				// 118
	void*			ismif11C;			// 11C ImageSpaceModifierInstanceForm*
	void*			ismif120;			// 120
	void*			ismif124;			// 124
	void*			ismif128;			// 128
	float			flt12C;				// 12C
	float			flt130;				// 130
	float			flt134;				// 134
};
assert(sizeof(Sky) == 0x138);

class GridArray {
public:
	virtual void*	Destroy(bool doFree);
	virtual void	Fn_01(void);
	virtual void	Fn_02(void);
	virtual void	Fn_03(void);
	virtual void	Fn_04(void);
	virtual void	Fn_05(void);
};
assert(sizeof(GridArray) == 0x04);

class GridCellArray : public GridArray {
public:
	virtual void	Fn_06(void);
	virtual void	Fn_07(void);
	virtual void	Fn_08(void);
	virtual void	Fn_09(void);

	TESObjectCELL*	GetCell(UInt32 x, UInt32 y) { return *(TESObjectCELL**)ThisCall(0x004BA490, this, x, y); }

	SInt32			worldX;			// 04	X coord of current cell within worldspace
	SInt32			worldY;			// 08	Y coord "
	UInt8			gridSize;		// 0C	Init'd to uGridsToLoad
	UInt8			pad0D[3];		// 0D
	TESObjectCELL** gridCells;		// 10	Size is gridSize^2
	float			posX;			// 14	worldX * 4096
	float			posY;			// 18	worldY * 4096
	UInt32			unk1C[3];		// 1C
};
assert(sizeof(GridCellArray) == 0x028);

class TES {
public:
	virtual void		Fn_00(UInt32 arg1, UInt32 arg2, UInt32 arg3, UInt32 arg4, UInt32 arg5);
	
	void				PurgeCells() {}

	UInt32								unk04;				// 04
	GridCellArray*						gridCellArray;		// 08
	NiNode*								objectLODRoot;		// 0C
	NiNode*								landLOD;			// 10
	NiNode*								waterLOD;			// 14
	BSTempNodeManager*					tempNodeMgr;		// 18
	NiDirectionalLight*					directionalLight;	// 1C
	void*								ptr20;				// 20
	SInt32								extCoordX;			// 24
	SInt32								extCoordY;			// 28
	SInt32								unk2C[2];			// 2C
	TESObjectCELL*						currentInterior;	// 34
	TESObjectCELL**						interiorsBuffer;	// 38
	TESObjectCELL**						exteriorsBuffer;	// 3C
	UInt32								unk40[9];			// 40
	WaterSurfaceManager*				waterSurfaceManager;	// 64
	Sky*								sky;				// 68
	TList<void>							activeIMODs;		// 6C TList<ImageSpaceModifierInstance>
	UInt32								unk74[3];			// 74
	float								unk80[2];			// 80
	TESWorldSpace						*currentWrldspc;	// 88
	TList<void>							list8C;				// 8C
	TList<void>							list94;				// 94
	TList<void>							list9C;				// 9C
	void*								unkA4;				// A4 QueuedFile*
	NiSourceTexture*					unkA8;				// A8
	void*								unkAC;				// AC QueuedFile*
	void*								ptrB0;				// B0
	UInt32								unkB4[2];			// B4
	void*								navMeshInfoMap;		// BC NavMeshInfoMap*
	void*								unkC0;				// C0 LoadedAreaBound*
};
assert(sizeof(TES) == 0xC4);

class TESGameSound {
public:
	UInt32			unk00[3];	// 00
	UInt32			hashKey;	// 0C
	UInt32			unk10[4];	// 10
	float			x;			// 20
	float			y;			// 24
	float			z;			// 28
	UInt32			unk2C[4];	// 2C
	float			unk3C;		// 3C
	UInt32			unk40[3];	// 40
	const char*		name;		// 4C
	UInt32			unk50;		// 50
	UInt32			unk54;		// 54
};
assert(sizeof(TESGameSound) == 0x058);

class Tile {
public:
	enum TileValue {
		kTileValue_x = 0xFA1,
		kTileValue_y,
		kTileValue_visible,
		kTileValue_class,
		kTileValue_clipwindow = 0xFA6,
		kTileValue_stackingtype,
		kTileValue_locus,
		kTileValue_alpha,
		kTileValue_id,
		kTileValue_disablefade,
		kTileValue_listindex,
		kTileValue_depth,
		kTileValue_clips,
		kTileValue_target,
		kTileValue_height,
		kTileValue_width,
		kTileValue_red,
		kTileValue_green,
		kTileValue_blue,
		kTileValue_tile,
		kTileValue_childcount,
		kTileValue_child_count = kTileValue_childcount,
		kTileValue_justify,
		kTileValue_zoom,
		kTileValue_font,
		kTileValue_wrapwidth,
		kTileValue_wraplimit,
		kTileValue_wraplines,
		kTileValue_pagenum,
		kTileValue_ishtml,
		kTileValue_cropoffsety,
		kTileValue_cropy = kTileValue_cropoffsety,
		kTileValue_cropoffsetx,
		kTileValue_cropx = kTileValue_cropoffsetx,
		kTileValue_menufade,
		kTileValue_explorefade,
		kTileValue_mouseover,
		kTileValue_string,
		kTileValue_shiftclicked,
		kTileValue_clicked = 0xFC7,
		kTileValue_clicksound = 0xFCB,
		kTileValue_filename,
		kTileValue_filewidth,
		kTileValue_fileheight,
		kTileValue_repeatvertical,
		kTileValue_repeathorizontal,
		kTileValue_animation = 0xFD2,
		kTileValue_linecount = 0xDD4,
		kTileValue_pagecount,
		kTileValue_xdefault,
		kTileValue_xup,
		kTileValue_xdown,
		kTileValue_xleft,
		kTileValue_xright,
		kTileValue_xbuttona = 0xFDD,
		kTileValue_xbuttonb,
		kTileValue_xbuttonx,
		kTileValue_xbuttony,
		kTileValue_xbuttonlt,
		kTileValue_xbuttonrt,
		kTileValue_xbuttonlb,
		kTileValue_xbuttonrb,
		kTileValue_xbuttonstart = 0xFE7,
		kTileValue_mouseoversound,
		kTileValue_draggable,
		kTileValue_dragstartx,
		kTileValue_dragstarty,
		kTileValue_dragoffsetx,
		kTileValue_dragoffsety,
		kTileValue_dragdeltax,
		kTileValue_dragdeltay,
		kTileValue_dragx,
		kTileValue_dragy,
		kTileValue_wheelable,
		kTileValue_wheelmoved,
		kTileValue_systemcolor,
		kTileValue_brightness,
		kTileValue_linegap = 0xFF7,
		kTileValue_resolutionconverter,
		kTileValue_texatlas,
		kTileValue_rotateangle,
		kTileValue_rotateaxisx,
		kTileValue_rotateaxisy,

		kTileValue_user0 = 0x1004,
		kTileValue_user1,
		kTileValue_user2,
		kTileValue_user3,
		kTileValue_user4,
		kTileValue_user5,
		kTileValue_user6,
		kTileValue_user7,
		kTileValue_user8,
		kTileValue_user9,
		kTileValue_user10,
		kTileValue_user11,
		kTileValue_user12,
		kTileValue_user13,
		kTileValue_user14,
		kTileValue_user15,
		kTileValue_user16,

		kTileValue_max
	};

	virtual Tile*		Destroy(bool doFree);
	virtual void		Init(Tile* parent, const char* name, Tile* replacedChild);
	virtual NiNode*		CalcNode();
	virtual UInt32		GetType();		// returns one of kTileValue_XXX
	virtual const char* GetTypeStr();	// 4-byte id
	virtual bool		Unk_05(UInt32 arg0, UInt32 arg1);
	virtual UInt32		UpdateField(UInt32 valueID, float floatValue, const char* strValue);
	virtual void		Unk_07();
	virtual UInt32		Unk_08();
	virtual void		Unk_09(UInt32 arg0, UInt32 arg1, UInt32 arg2);

	class ChildNode {
	public:
		ChildNode*	next;
		ChildNode*	prev;
		Tile*		child;
	};

	struct Value {
		UInt32		id;		// 00
		Tile*		parent;	// 04
		float		num;	// 08
		char*		str;	// 0C
		void*		action;	// 10
	};

	void						SetFloat(UInt32 Index, float Value) { ThisCall(0x00A012D0, this, Index, Value, 1); }

	ChildNode*					firstChild;		// 04
	ChildNode*					lastChild;		// 08
	UInt32						childCount;		// 0C
	NiTList<Value>				valueList;		// 10
	BSString					name;			// 20
	Tile*						parent;			// 28
	NiNode*						node;			// 2C
	UInt32						flags;			// 30
	UInt8						unk34;			// 34
	UInt8						unk35;			// 35
	UInt8						pad35[2];		// 36
};
assert(sizeof(Tile) == 0x38);

class TileImage : public Tile {
public:
	float		flt038;			// 38
	UInt32		unk03C;			// 3C
	void*		shaderProp;		// 40 TileShaderProperty*
	UInt8		byt044;			// 44
	UInt8		pad044[3];		// 45-47
};
assert(sizeof(TileImage) == 0x48);

class TileRect : public Tile {
public:
	UInt32	unk38;	// 38
};
assert(sizeof(TileRect) == 0x3C);

class TileMenu : public TileRect {
public:
	Menu*	menu;	// 3C
};
assert(sizeof(TileMenu) == 0x40);

class Menu {
public:
	enum MenuType {
		kMenuType_None = 0,			// for gamemode
		kMenuType_BigFour,			// F1 - F4 menus
		kMenuType_Any,
		kMenuType_Console,
		kMenuType_Main,

		kMenuType_Min =				0x3E9,
		kMenuType_Message =			kMenuType_Min,
		kMenuType_Inventory,
		kMenuType_Stats,
		kMenuType_HUDMain,
		kMenuType_Loading =			0x3EF,
		kMenuType_Container,
		kMenuType_Dialog,
		kMenuType_SleepWait =		0x3F4,
		kMenuType_Start,
		kMenuType_LockPick,
		kMenuType_Quantity =		0x3F8,
		kMenuType_Map =				0x3FF,
		kMenuType_Book =			0x402,
		kMenuType_LevelUp,
		kMenuType_Persuasion =		0x40A,
		kMenuType_Repair,
		kMenuType_RaceSex,
		kMenuType_Credits =			0x417,
		kMenuType_CharGen,
		kMenuType_TextEdit =		0x41B,
		kMenuType_Barter =			0x41D,
		kMenuType_Surgery,
		kMenuType_Hacking,
		kMenuType_VATS,
		kMenuType_Computers,
		kMenuType_RepairServices,
		kMenuType_Tutorial,
		kMenuType_SpecialBook,
		kMenuType_ItemMod,
		kMenuType_LoveTester =		0x432,
		kMenuType_CompanionWheel,
		kMenuType_TraitSelect,
		kMenuType_Recipe,
		kMenuType_SlotMachine =		0x438,
		kMenuType_Blackjack,
		kMenuType_Roulette,
		kMenuType_Caravan,
		kMenuType_Trait =			0x43C,
		kMenuType_Max =				kMenuType_Trait,
	};

	virtual void	Destructor(bool arg0);		// pass false to free memory
	virtual void	SetField(UInt32 idx, Tile* value);
	virtual void	Unk_02(UInt32 arg0, UInt32 arg1);	// show menu?
	virtual void	HandleClick(UInt32 buttonID, Tile* clickedButton); // buttonID = <id> trait defined in XML
	virtual void	HandleMouseover(UInt32 arg0, Tile * activeTile);	//called on mouseover, activeTile is moused-over Tile
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_06(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_07(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_08(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_09(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0A(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0B();
	virtual bool	HandleKeyboardInput(char inputChar);	//for keyboard shortcuts, return true if handled
	virtual UInt32	GetID();
	virtual bool	Unk_0E(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0F();
	virtual void	Unk_10();
	virtual void	Unk_11();

	TileMenu*		tile;		// 04
	UInt32			unk08;		// 08
	UInt32			unk0C;		// 0C
	UInt32			unk10;		// 10
	UInt32			unk14;		// 14
	UInt32			unk18;		// 18
	UInt32			unk1C;		// 1C
	UInt32			id;			// 20
	UInt32			unk24;		// 24
};
assert(sizeof(Menu) == 0x28);

class HUDMainMenu : public Menu {
public:
	struct QueuedMessage {
		char	msgText[0x204];			// 000
		char	iconPate[MAX_PATH];		// 204
		char	soundPath[MAX_PATH];	// 308
		float	displayTime;			// 40C
	};

	UInt32					unk028;			// 028
	TileImage*				tile02C;		// 02C
	TileText*				tile030;		// 030
	TileRect*				tile034;		// 034
	TileRect*				tile038;		// 038
	TileRect*				tile03C;		// 03C
	TileImage*				tile040;		// 040
	TileImage*				tile044;		// 044
	TileText*				tile048;		// 048
	TileText*				tile04C;		// 04C
	TileImage*				tile050;		// 050
	TileImage*				tile054;		// 054
	TileText*				tile058;		// 058
	TileRect*				tile05C;		// 05C
	TileRect*				tile060;		// 060
	TileText*				tile064;		// 064
	TileText*				tile068;		// 068
	TileImage*				tile06C;		// 06C
	TileImage*				tile070;		// 070
	TileText*				tile074;		// 074
	TileText*				tile078;		// 078
	TileImage*				tile07C;		// 07C
	TileImage*				tile080;		// 080
	TileText*				tile084;		// 084
	TileText*				sneakLabel;		// 088
	TileImage*				tile08C;		// 08C
	TileText*				tile090;		// 090
	TileImage*				tile094;		// 094
	TileText*				tile098;		// 098
	TileRect*				tile09C;		// 09C
	TileText*				tile0A0;		// 0A0
	TileImage*				tile0A4;		// 0A4
	TileText*				tile0A8;		// 0A8
	TileText*				tile0AC;		// 0AC
	TileText*				tile0B0;		// 0B0
	TileText*				tile0B4;		// 0B4
	TileText*				tile0B8;		// 0B8
	TileText*				tile0BC;		// 0BC
	TileText*				tile0C0;		// 0C0
	TileImage*				tile0C4;		// 0C4
	TileRect*				tile0C8;		// 0C8
	TileText*				tile0CC;		// 0CC
	TileImage*				tile0D0;		// 0D0
	TileImage*				tile0D4;		// 0D4
	TileImage*				tile0D8;		// 0D8
	TileText*				tile0DC;		// 0DC
	TileText*				tile0E0;		// 0E0
	TileImage*				tile0E4;		// 0E4
	TileText*				tile0E8;		// 0E8
	TileText*				tile0EC;		// 0EC
	TileText*				tile0F0;		// 0F0
	TileImage*				crosshair;		// 0F4
	TileImage*				tile0F8;		// 0F8
	TileImage*				tile0FC;		// 0FC
	TileImage*				tile100;		// 100
	TileImage*				tile104;		// 104
	TileImage*				tile108;		// 108
	TileImage*				tile10C;		// 10C
	TileImage*				tile110;		// 110
	TileRect*				tile114;		// 114
	TileRect*				tile118;		// 118
	TileRect*				tile11C;		// 11C
	TileRect*				tile120;		// 120
	TileRect*				tile124;		// 124
	TileRect*				tile128;		// 128
	TileRect*				tile12C;		// 12C
	TileRect*				tile130;		// 130
	TileRect*				tile134;		// 134
	TileRect*				tile138;		// 138
	TileRect*				tile13C;		// 13C
	TileRect*				tile140;		// 140
	TileRect*				tile144;		// 144
	void*					tile148;		// 148 Tile3D*
	TileRect*				tile14C;		// 14C
	TileRect*				tile150;		// 150
	TileImage*				tile154;		// 154
	TileImage*				tile158;		// 158
	TileText*				tile15C;		// 15C
	TileRect*				tile160;		// 160
	TileText*				tile164;		// 164
	TileText*				tile168;		// 168
	TileText*				tile16C;		// 16C
	TileImage*				tile170;		// 170
	TileImage*				tile174;		// 174
	TileText*				tile178;		// 178
	TileText*				tile17C;		// 17C
	TileImage*				tile180;		// 180
	UInt32					unk184[2];		// 184
	TList<QueuedMessage>	queuedMessages;	// 18C
	UInt32					currMsgKey;		// 194
	UInt32					array198[4];	// 198 BSSimpleArray<void>
	UInt32					unk1A8[4];		// 1A8
	TESObjectREFR*			crosshairRef;	// 1B8
	UInt32					unk1BC[3];		// 1BC
	TileRect*				tile1C8;		// 1C8
	TileRect*				tile1CC;		// 1CC
	UInt32					unk1D0;			// 1D0
	TileRect*				tile1D4;		// 1D4
	TileRect*				tile1D8;		// 1D8
	TileRect*				tile1DC;		// 1DC
	TileRect*				tile1E0;		// 1E0
	TileRect*				tile1E4;		// 1E4
	TileRect*				tile1E8;		// 1E8
	UInt32					unk1EC[5];		// 1EC
	NiControllerSequence*	niContSeq;		// 200
	UInt32					unk204[6];		// 204
	Actor*					healthTarget;	// 21C
	UInt32					unk220[4];		// 220
	void*					ptr230;			// 230
	void*					ptr234;			// 234
	UInt32					unk238[16];		// 238
};
assert(sizeof(HUDMainMenu) == 0x278);

class ModInfo {
public:
	struct ChunkInfo {
		UInt32	type;		// e.g. 'GRUP', 'GLOB', etc
		UInt16	length;
		UInt16	pad;
	};

	struct FormInfo {  // Record Header in FNVEdit
		UInt32		recordType;			// 00 i.e. 'FACT', 'GMST'						Signature
		UInt32		dataSize;			// 04 looks like size of entire record			Data Size
		UInt32		formFlags;			// 08 copied to TESForm->flags					Record Flags
		UInt32		formID;				// 0C											FormID
		UInt32		unk10;				// 10											Version Control Info 1
		UInt16		formVersion;		// 14 always initialized to 0F on SaveForm.		Form Version
		UInt16		unk16;				// 16                                           Version Control Info 2
	};

	struct GroupInfo { // Record Header in FNVEdit
		UInt32		recordType;			// 00 'GRUP'									Signature
		UInt32		groupSize;			// 04 Size of entire record						Size
		UInt32		groupLabel;			// 08 copied to TESForm->flags					Label
		UInt32		groupType;			// 0C forms, dialog, cell...					Type
		UInt32		unk10;				// 10											Stamp
		UInt16		unk14;				// 14											Part of Unknown
		UInt16		unk16;				// 16                                           Part of Unknown
	};

	struct FileHeader {	// File header in FNVEdit Signature 'HEDR'
		float	version;		//	00
		UInt32	recordCount;	//	04
		UInt32	nextObectID;	//	08
	};

	struct	MasterSize {	// Data member of the master list in WIN32_FIND_DATA format
		UInt32	low;
		UInt32	high;
	};

	TList<void>			unkList;			// 000 treated as ModInfo during InitializeForm, looks to be a linked list of modInfo
	void*				pointerMap;			// 008 *NiTPointerMap<TESFile*>*
	UInt32				unk00C;				// 00C
	BSFile*				unkFile;			// 010
	UInt32				unk014;				// 014 
	void*				unk018;				// 018 seen all zeroes. size unknown, seen not valid pointer in FalloutNV.esm
	void*				unk01C;				// 01C as above
	char				name[0x104];		// 020
	char				filepath[0x104];	// 124
	UInt32				unk228;				// 228
	UInt32				unk22C;				// Masters are init'd to dword_1186740 (0x2800) same val as BSFile+10? Buffer size ?
	UInt32				unk230;				// 230
	UInt32				unk234;				// 234
	UInt32				unk238;				// 238
	UInt32				unk23C;				// 23C
	FormInfo			formInfo;			// 240
	ChunkInfo			subRecordHeader;	// 258
	UInt32				unk260;				// 260 could be file size, has it is compared with fileOffset during load module. But filesize would be an Int64 !
	UInt32				fileOffset;			// 264
	UInt32				dataOffset;			// 268 index into dataBuf
	UInt32				subrecordBytesRead;	// 26C generates error on Read if != expected length
	FormInfo			writeInfo;			// 270 "used" to add record to the plugin.
	UInt32				writeOffset;		// 288
	UInt32				subrecordBytesToWrite;	// 28C
	TList<void>			tList290;			// 290 looks to be a list of form or a list of formInfo. referenced from TESForm::WriteForm
	UInt8				unk298;				// 298
	UInt8				bIsBigEndian;		// 299
	UInt8				unk29A;				// 29A
	UInt8				pad29B;
	UInt32				fileData[80];		// 29C WIN32_FIND_DATA?
	FileHeader			header;				// 3DC
	UInt8				flags;				// 3E8	Bit 0 is ESM . Runtime: Bit 2 is Valid, Bit 3 is Unselected Editor: 2 is selected, 3 is active, 4 may be invalid, 6 is endian, 14 controls VCI.
	UInt8				pad3E9[3];
	TList<char*>*		refModNames;		// 3EC	paired with 3F0
	UInt32				unk3F0;				// 3F0
	TList<MasterSize*>* refModData;		// 3F4 most likely full of 0
	UInt32				unk3F8;				// 3F8
	UInt32				numRefMods;			// 3FC related to modindex; see 4472D0
	ModInfo**			refModInfo;		// 400 used to look up modInfo based on fixed mod index, double-check
	UInt32				unk404;				// 404
	UInt32				unk408;				// 408
	UInt8				modIndex;			// 40C init to 0xFF
	UInt8				pad40D[3];
	BSString			author;				// 410
	BSString			description;		// 418
	void*				dataBuf;			// 420 
	UInt32				dataBufSize;		// 424 looks like size of entire record
	UInt8				unk428;				// 428 decide if forms needs to be reloaded on LoadFiles
	UInt8				pad429[3];
};
assert(sizeof(ModInfo) == 0x42C);

class ModList {
public:
	TList<ModInfo>		modInfoList;		// 00
	UInt32				loadedModCount;		// 08
	ModInfo*			loadedMods[0xFF];	// 0C
};
assert(sizeof(ModList) == 0x408);

class MasterDataHandler {
public:
	UInt32							unk00;					// 000
	BoundObjectListHead*			boundObjects;			// 004
	TList<TESPackage>				packageList;			// 008
	TList<TESWorldSpace>			worldSpaceList;			// 010
	TList<TESClimate>				climateList;			// 018
	TList<TESImageSpace>			imageSpaceList;			// 020
	TList<TESImageSpaceModifier>	imageSpaceModList;		// 028
	TList<TESWeather>				weathers;				// 030
	TList<EnchantmentItem>			enchantmentItemList;	// 038
	TList<SpellItem>				spellItemList;			// 040
	TList<BGSHeadPart>				headPartList;			// 048
	TList<TESHair>					hairList;				// 050
	TList<TESEyes>					eyeList;				// 058
	TList<TESRace>					raceList;				// 060
	TList<BGSEncounterZone>			encounterZoneList;		// 068
	TList<TESLandTexture>			landTextureList;		// 070
	TList<BGSCameraShot>			cameraShotList;			// 078
	TList<TESClass>					classList;				// 080
	TList<TESFaction>				factionList;			// 088
	TList<TESReputation>			reputationList;			// 090
	TList<TESChallenge>				challengeList;			// 098
	TList<TESRecipe>				recipeList;				// 0A0
	TList<TESRecipeCategory>		recipeCategoryList;		// 0A8
	TList<TESAmmoEffect>			ammoEffectList;			// 0B0
	TList<TESCasino>				casinoList;				// 0B8
	TList<TESCaravanDeck>			caravanDeckList;		// 0C0
	TList<Script>					scriptList;				// 0C8
	TList<TESSound>					soundList;				// 0D0
	TList<BGSAcousticSpace>			acousticSpaceList;		// 0D8
	TList<BGSRagdoll>				ragdollList;			// 0E0
	TList<TESGlobal>				globalList;				// 0E8
	TList<BGSVoiceType>				voiceTypeList;			// 0F0
	TList<BGSImpactData>			impactDataList;			// 0F8
	TList<BGSImpactDataSet>			impactDataSetList;		// 100
	TList<TESTopic>					topicList;				// 108
	TList<TESTopicInfo>				topicInfoList;			// 110
	TList<TESQuest>					questList;				// 118
	TList<TESCombatStyle>			combatStyleList;		// 120
	TList<TESLoadScreen>			loadScreenList;			// 128
	TList<TESWaterForm>				waterFormList;			// 130
	TList<TESEffectShader>			effectShaderList;		// 138
	TList<BGSProjectile>			projectileList;			// 140
	TList<BGSExplosion>				explosionList;			// 148
	TList<BGSRadiationStage>		radiationStageList;		// 150
	TList<BGSDehydrationStage>		dehydrationStageList;	// 158
	TList<BGSHungerStage>			hungerStageList;		// 160
	TList<BGSSleepDeprivationStage>	sleepDepriveStageList;	// 168
	TList<BGSDebris>				debrisList;				// 170
	TList<BGSPerk>					perkList;				// 178
	TList<BGSBodyPartData>			bodyPartDataList;		// 180
	TList<BGSNote>					noteList;				// 188
	TList<BGSListForm>				listFormList;			// 190
	TList<BGSMenuIcon>				menuIconList;			// 198
	TList<TESObjectANIO>			anioList;				// 1A0
	TList<BGSMessage>				messageList;			// 1A8
	TList<BGSLightingTemplate>		lightingTemplateList;	// 1B0
	TList<BGSMusicType>				musicTypeList;			// 1B8
	TList<TESLoadScreenType>		loadScreenTypeList;		// 1C0
	TList<MediaSet>					mediaSetList;			// 1C8
	TList<MediaLocationController>	mediaLocControllerList;	// 1D0
	TESRegionList*					regionList;			// 1D8
	NiTArray<TESObjectCELL*>		cellArray;				// 1DC
	NiTArray<BGSAddonNode*>			addonArray;				// 1EC
	UInt32							unk1FC[3];				// 1FC	208 looks like next created refID
	UInt32							nextCreatedRefID;		// 208	Init'd to FF000800
	UInt32							unk20C;					// 20C	last unselected mod in modList. GECK: active ESM
	ModList							modList;				// 210
	UInt8							unk618;					// 618
	UInt8							unk619;					// 619
	UInt8							unk61A;					// 61A	referenced during LoadForm (ie TESSpellList). bit 1 might mean refID to pointer conversion not done. For GECK means save in progress
	UInt8							unk61B;					// 61B
	UInt32							unk61C;					// 61C
	UInt8							unk620;					// 620
	UInt8							loading;				// 621	Init'd to 0 after loadForms
	UInt8							unk622;					// 622	referenced during loading of modules
	UInt8							unk623;					// 623
	void*							regionManager;			// 624 TESRegionManager*
	InventoryChanges::Data*			vendorContainer;		// 628
	UInt32							unk62C;					// 62C	
	UInt32							unk630;					// 630
	UInt32							unk634;					// 634
	UInt32							unk638;					// 638
};
assert(sizeof(MasterDataHandler) == 0x63C);

class BSRenderedTexture : public NiObject {
public:
	NiRenderTargetGroup*	RenderTargetGroup;	// 008
	UInt32					unk00C[5];			// 00C
	UInt32					unk020;				// 020
	UInt32					unk024;				// 024
	UInt32					unk028;				// 028
	UInt32					unk02C;				// 02C
	NiRenderedTexture*		RenderedTexture;	// 030
	UInt32					unk034;				// 034
	UInt32					unk038;				// 038
	UInt32					unk03C;				// 03C
};
assert(sizeof(BSRenderedTexture) == 0x40);

class NiShadeProperty : public NiProperty {
public:
	UInt32	Unk018;		// 018
	UInt32	Unk01C;		// 01C
};
assert(sizeof(NiShadeProperty) == 0x20);

class SpeedTreeLeafShaderProperty : public NiShadeProperty {
public:
	struct LeafData {
		UInt32		unk00;
		UInt32		unk04;
		float*		leafBase; // pointer to float4[48]
	};
	UInt32		Unk020[26]; // 020 This is a padding. SpeedTreeLeafShaderProperty could be inherited from other classes after NiShadeProperty or it has no inheritance.
	LeafData*	leafData;	// 088
};
assert(offsetof(SpeedTreeLeafShaderProperty, leafData) == 0x88);
assert(sizeof(SpeedTreeLeafShaderProperty) == 0x8C);

class BSFadeNode : public NiNode {
public:
	float			fltAC[4];		// AC
	UInt32			unkBC[2];		// BC
	UInt32			unkC4;			// C4
	UInt32			unkC8;			// C8
	TESObjectREFR* unkCC;			// CC
	UInt32			unkD0[5];		// D0
};
assert(sizeof(BSFadeNode) == 0xE4);

class BSTreeModel : public NiRefObject {
public:
	UInt32					Unk08;				// 08
	UInt32					Unk0C;				// 0C
	UInt32					Unk10;				// 10
	UInt32					Unk14;				// 14
	UInt32					Unk18;				// 18
	UInt32					Unk1C;				// 1C
	UInt32					Unk20;				// 20
	UInt32					Unk24;				// 24
	UInt32					Unk28;				// 28
	void*					Unk2C;				// 2C BSShaderTextureSet*
	NiSourceTexture*		LeavesTexture;		// 30
	void*					Unk34;				// 34 BSShaderTextureSet*
	UInt32					Unk38;				// 38
	float					Unk3C;				// 3C
	UInt32					Unk40;				// 40
	UInt8					Unk44;				// 44
	UInt8					pad44[3];
	float					Unk48;				// 48
	float					Unk4C;				// 4C
};
assert(sizeof(BSTreeModel) == 0x50);

class BSTreeNode : public BSFadeNode {
public:
	BSTreeModel*		TreeModel;		// E4
	UInt32				UnkE0;			// E8
	UInt32				UnkE4;			// EC
	UInt32				UnkE8;			// F0
	float				UnkEC;			// F4

};
assert(sizeof(BSTreeNode) == 0xF8);

class InputGlobal {
public:
	enum {
		kFlag_HasJoysticks =	1 << 0,
		kFlag_HasMouse =		1 << 1,
		kFlag_HasKeyboard =		1 << 2,
		kFlag_BackgroundMouse =	1 << 3,
	};
	
	enum {
		kMaxDevices = 8,
	};

	class Joystick {
		UInt32	unk000[0x244 >> 2];
	};

	struct JoystickObjectsInfo {
		enum {
			kHasXAxis = 1 << 0,
			kHasYAxis = 1 << 1,
			kHasZAxis = 1 << 2,
			kHasXRotAxis = 1 << 3,
			kHasYRotAxis = 1 << 4,
			kHasZRotAxis = 1 << 5
		};

		UInt32	axis;
		UInt32	buttons;
	};

	struct Unk1AF8 {
		UInt32	bufLen;
		UInt8	unk04[0x2C - 4];
	};

	UInt32					unk0000;							// 0000
	UInt32					flags;								// 0004
	IDirectInput8*			dinputInterface;					// 0008
	IDirectInputDevice8*	joystickInterfaces[kMaxDevices];	// 000C - format is c_dfDIJoystick
	IDirectInputDevice8*	keyboardInterface;					// 002C - format is c_dfDIKeyboard
	IDirectInputDevice8*	mouseInterface;						// 0030 - format is c_dfDIMouse2
	UInt32					unk0030[0x140];						// 0034
	Joystick				devices[kMaxDevices];				// 0534
	DIDEVCAPS				devCaps[kMaxDevices];				// 1754
	JoystickObjectsInfo		devInfo[kMaxDevices];				// 18B4
	UInt32					numJoysticks;						// 18F4
	UInt8					CurrentKeyState[0x100];				// 18F8
	UInt8					PreviousKeyState[0x100];			// 19F8
	Unk1AF8					unk1AF8;							// 1AF8
	DIMOUSESTATE2			CurrentMouseState;					// 1B24
	DIMOUSESTATE2			PreviousMouseState;					// 1B38
	UInt32					oldMouseButtonSwap;					// 1B4C - state of SwapMouseButton when program launched
	UInt32					unk1B50;							// 1B50
	UInt32					oldDoubleClickTime;					// 1B54
	UInt32					unk1B54[(0x1B90 - 0x1B54) >> 2];	// 1B58
	UInt8					KeyboardInputControls[28];			// 1B94
	UInt8					MouseInputControls[28];				// 1BB0
	UInt8					JoystickInputControls[28];			// 1BCC
	UInt32					unk1BE4[(0x1C00 - 0x1BE4) >> 2];	// 1BE4
};
assert(sizeof(InputGlobal) == 0x1C04);

class BSAudioManager {
public:
	enum Volumes {
		kMaster = 0,
		kFoot,
		kVoice,
		kEffects,
		kMusic,
		kRadio,
		kVATSCamera,
	};

	void**						_vtbl;					// 000
	UInt32                      unk004[10];				// 004
	void*						unk02C;					// 02C
	float                       flt030;					// 030
	UInt32                      unk034[2];				// 034
	void*						unk03C;					// 03C
	UInt32                      unk040[5];				// 040
	NiTMap<UInt32, BSGameSound>	playingSounds;			// 054
	NiTMap<UInt32, BSSoundInfo> playingSoundInfos1;		// 064
	NiTMap<UInt32, BSSoundInfo> playingSoundInfos2;		// 074
	NiTMap<UInt32, NiAVObject>  soundPlayingObjects;	// 084
	TList<BSGameSound>			gameSounds;				// 094
	UInt32                      unk09C;					// 09C
	UInt32                      unk0A0;					// 0A0
	UInt32                      unk0A4;					// 0A4
	UInt32                      unk0A8;					// 0A8
	_RTL_CRITICAL_SECTION		criticalSectionAC;
	_RTL_CRITICAL_SECTION		criticalSectionC4;
	_RTL_CRITICAL_SECTION		criticalSectionDC;
	_RTL_CRITICAL_SECTION		criticalSectionF4;
	_RTL_CRITICAL_SECTION		criticalSection10C;
	UInt32						unk124;
	UInt32						unk128;
	UInt32						unk12C;
	UInt32						time130;
	UInt8						byte134;
	UInt8						byte135;
	UInt8						pad136[2];
	UInt32						threadID;
	void*						audioMgrThread;			// 13C BSAudioManagerThread*
	float                       volumes[12];			// 140
	UInt32                      unk170[4];				// 170
	UInt32                      nextMapKey;				// 180
	UInt8						ignoreTimescale;
	UInt8						byte185;
	UInt8						byte186;
	UInt8						byte187;
};
assert(sizeof(BSAudioManager) == 0x188);

class SoundGlobal { // BSWin32Audio
public:
	void					Play(TESSound* Sound) {}

	void**					_vtbl;						// 000
	UInt8					IsInitialized;				// 004
	UInt8					IsInitialized2;
	UInt8					pad004[2];
	UInt32					unk008;						// 008
	UInt32					unk00C;						// 00C
	void*					AudioListener;				// 010 BSWin32AudioListener*
	UInt32					unk014[9];					// 014
	IDirectSound8*			dsoundInterface;			// 038
	IDirectSoundBuffer8*	primaryBufferInterface;		// 03C
	DSCAPS					soundCaps;					// 040
	UInt32					unkA0;						// 0A0
};
assert(sizeof(SoundGlobal) == 0x0A4);

class OSGlobal {
public:
	void			RenderShadowMaps() { ThisCall(0x00871290, this); }
	InputGlobal*	GetInput() { return *(InputGlobal**)0x011F35CC; }
	SoundGlobal*	GetSound() { return *(SoundGlobal**)0x011F6D98; }
	void			PurgeModels() {}

	UInt8			unk00;				// 00
	UInt8			quitGame;			// 01	// The seven are initialized to 0, this one is set by QQQ
	UInt8			exitToMainMenu;		// 02
	UInt8			unk03;				// 03
	UInt8			unk04;				// 04
	UInt8			unk05;				// 05
	UInt8			FlyCam;				// 06
	UInt8			disableAI;			// 07
	HWND			window;				// 08
	HINSTANCE		procInstance;		// 0C
	UInt32			mainThreadID;		// 10
	HANDLE			mainThreadHandle;	// 14
	void*			unk18;				// 18 ScrapHeapManager::Buffer*
	UInt32			unk1C;				// 1C
	UInt32			unk20;				// 20
	UInt32			unk24;				// 24
	UInt32			unk28[24];			// 28
	void*			accumulator0;		// 88 BSShaderAccumulator*
	void*			accumulator1;		// 8C BSShaderAccumulator*
	void*			accumulator2;		// 90 BSShaderAccumulator*
	void*			accumulator3;		// 94 BSShaderAccumulator*
	void*			accumulator4;		// 98 BSShaderAccumulator*
	UInt32			unk9C;				// 9C
	NiCamera*		camera;				// A0
};
assert(sizeof(OSGlobal) == 0x0A4);

class MenuInterfaceManager {
public:
	bool IsActive(UInt32 MenuType) {
		if (MenuType == Menu::MenuType::kMenuType_Main) return (menuStack[0] == Menu::MenuType::kMenuType_Loading && menuStack[1] == Menu::MenuType::kMenuType_Start) || (menuStack[0] == menuStack[1] == Menu::MenuType::kMenuType_Console && menuStack[1] == Menu::MenuType::kMenuType_Loading && menuStack[2] == Menu::MenuType::kMenuType_Start);
		return menuStack[0] == MenuType;
	}

	UInt32					flags;				// 000
	SceneGraph*				MenuRoot;			// 004
	SceneGraph*				MenuRoot3D;			// 008
	UInt8					currentMode;		// 00C	1 = GameMode; 2 = MenuMode
	UInt8					pad00D[3];			// 00D
	UInt32					unk010;				// 010
	UInt32					unk014;				// 014
	UInt32					pickLength;			// 018
	UInt32					unk01C[3];			// 01C
	TileImage*				cursor;				// 028
	float					unk02C;				// 02C
	float					unk030;				// 030
	float					unk034;				// 034
	float					cursorX;			// 038
	float					unk03C;				// 03C
	float					cursorY;			// 040
	UInt32					unk044[11];			// 044
	TList<TESObjectREFR>	selectableRefs;		// 070
	UInt32					unk078;				// 078
	bool					debugText;			// 07C
	UInt8					byte07D;			// 07D
	UInt8					byte07E;			// 07E
	UInt8					byte07F;			// 07F
	NiNode*					niNode080;			// 080
	NiNode*					niNode084;			// 084
	UInt32					unk088;				// 088
	void*					shaderAccum08C;		// 08C BSShaderAccumulator*
	void*					shaderAccum090;		// 090 BSShaderAccumulator*
	void*					shadowScene094;		// 094 ShadowSceneNode*
	void*					shadowScene098;		// 098 ShadowSceneNode*
	Tile*					menuRoot;			// 09C
	Tile*					unk0A0;				// 0A0 seen "Strings"
	NiNode*					unk0A4;				// 0A4 saw Tile? seen NiNode
	UInt32					unk0A8;				// 0A8
	NiObject*				unk0AC;				// 0AC seen NiAlphaProperty
	UInt32					unk0B0[3];			// 0B0
	Tile*					activeTileAlt;		// 0BC
	UInt32					unk0C0[3];			// 0B0
	Tile*					activeTile;			// 0CC
	Menu*					activeMenu;			// 0D0
	Tile*					tile0D4;			// 0D4
	Menu*					menu0D8;			// 0D8
	UInt32					unk0DC[2];			// 0DC
	UInt8					msgBoxButton;		// 0E4 -1 if no button pressed
	UInt8					pad0E5[3];			// 0E5
	UInt32					unk0E8;				// 0E8
	UInt32					unk0EC;				// 0EC
	TESObjectREFR*			debugSelection;		// 0F0	compared to activated object during Activate
	UInt32					unk0F4;				// 0F4
	UInt32					unk0F8;				// 0F8
	TESObjectREFR*			crosshairRef;		// 0FC
	UInt32					unk100[4];			// 100
	UInt8					byte110;			// 110
	UInt8					pad111[3];			// 111
	UInt32					menuStack[10];		// 114
	void*					ptr13C;				// 13C	Points to a struct, possibly. First member is *bhkSimpleShapePhantom
	UInt32					unk140[5];			// 140
	UInt32					unk154;				// 154
	UInt32					unk158;				// 158
	UInt32					unk15C[6];			// 15C
	void*					pipboyManager;		// 174 FOPipboyManager*
	UInt32					unk178;				// 178
	NiTArray<void>			array17C;			// 17C NiTPrimitiveArray@PackedMenu@BGSMenuPacker
	UInt32					unk18C[130];		// 18C
	NiObject				*unk394;			// 394 seen NiSourceTexture
	UInt32					unk398[47];			// 398
	NiTArray<void>			array454;			// 454 NiTPrimitiveArray@TextureType@BSTextureManager
	NiTArray<void>			array464;			// 464 NiTPrimitiveArray@FilterMode@NiTexturingProperty
	UInt32					unk474[18];			// 474
	UInt32					unk4BC;				// 4BC
	UInt32					unk4C0[48];			// 4C0
};
assert(sizeof(MenuInterfaceManager) == 0x580);

class ExtraHavok : public BSExtraData {
public:
	bhkWorld*		world;	// 00C
	UInt32			unk10;	// 010
};
assert(sizeof(ExtraHavok) == 0x014);

class TimeGlobals {
public:
	TESGlobal* GameYear;		// 00
	TESGlobal* GameMonth;		// 04
	TESGlobal* GameDay;			// 08
	TESGlobal* GameHour;		// 0C
	TESGlobal* GameDaysPassed;	// 10
	TESGlobal* TimeScale;		// 14

	static float GetGameTime() { TimeGlobals* Globals = (TimeGlobals*)0x011DE7B8; return Globals->GameHour->data * 60.0f * 60.0f; }

};
assert(sizeof(TimeGlobals) == 0x018); // Static class, size could be larger

class QueuedModelLoader {
public:
	UInt32	Unk000[7]; // LockFreeMaps for models
};
assert(sizeof(QueuedModelLoader) == 0x01C);

static float* LocalGrassWindMagnitudeMax = (float*)0x00000000;
static float* LocalGrassWindMagnitudeMin = (float*)0x00000000;

static bool  (__cdecl* ExtractArgs)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...) = (bool (__cdecl*)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...))0x005ACCB0;
static bool  (__cdecl* LoadForm)(TESForm*, UInt32) = (bool (__cdecl*)(TESForm*, UInt32))0x004601D0;
static bool  (__cdecl* ShowUIMessageBox)(const char*, UInt32, UInt32, void*, UInt32, UInt32, float, float, const char*, ...) = (bool (__cdecl*)(const char*, UInt32, UInt32, void*, UInt32, UInt32, float, float, const char*, ...))0x00703E80;
static bool  (__cdecl* ShowUIMessage)(const char*, UInt32, const char*, const char*, float, bool) = (bool (__cdecl*)(const char*, UInt32, const char*, const char*, float, bool))0x007052F0;
static void  (* PrintToConsole)(const char*, ...) = (void (*)(const char*, ...))0x00703C00;
#elif defined(OBLIVION)
class BSExtraData {
public:
	enum ExtraDataType {
		kExtraData_Havok = 0x02,
		kExtraData_Cell3D = 0x03,
		kExtraData_WaterHeight = 0x04,
		kExtraData_CellWaterType = 0x05,
		kExtraData_RegionList = 0x08,
		kExtraData_SeenData = 0x09,
		kExtraData_EditorID = 0x0A,
		kExtraData_CellMusicType = 0x0B,
		kExtraData_CellClimate = 0x0C,
		kExtraData_ProcessMiddleLow = 0x0D,
		kExtraData_EditorCommonDialogData = 0x0E,
		kExtraData_CellCanopyShadowMask = 0x0F,
		kExtraData_DetachTime = 0x10,
		kExtraData_PersistentCell = 0x11,
		kExtraData_Script = 0x12,
		kExtraData_Action = 0x13,
		kExtraData_StartingPosition = 0x14,
		kExtraData_Anim = 0x15,

		kExtraData_UsedMarkers = 0x17,
		kExtraData_DistantData = 0x18,
		kExtraData_RagDollData = 0x19,
		kExtraData_InventoryChanges = 0x1A,
		kExtraData_Worn = 0x1B,
		kExtraData_WornLeft = 0x1C,

		kExtraData_StartLocation = 0x1E,
		kExtraData_Package = 0x1F,
		kExtraData_TresPassPackage = 0x20,
		kExtraData_RunOncePacks = 0x21,
		kExtraData_ReferencePointer = 0x22,
		kExtraData_Follower = 0x23,
		kExtraData_LevCreaModifier = 0x24,
		kExtraData_Ghost = 0x25,
		kExtraData_OriginalReference = 0x26,
		kExtraData_Ownership = 0x27,
		kExtraData_Global = 0x28,
		kExtraData_Rank = 0x29,
		kExtraData_Count = 0x2A,
		kExtraData_Health = 0x2B,
		kExtraData_Uses = 0x2C,
		kExtraData_TimeLeft = 0x2D,
		kExtraData_Charge = 0x2E,
		kExtraData_Soul = 0x2F,
		kExtraData_Light = 0x30,
		kExtraData_Lock = 0x31,
		kExtraData_Teleport = 0x32,
		kExtraData_MapMarker = 0x33,

		kExtraData_LeveledCreature = 0x35,
		kExtraData_LeveledItem = 0x36,
		kExtraData_Scale = 0x37,
		kExtraData_Seed = 0x38,
		kExtraData_NonActorMagicCaster = 0x39,

		kExtraData_CrimeGold = 0x3D,
		kExtraData_OblivionEntry = 0x3E,
		kExtraData_EnableStateParent = 0x3F,
		kExtraData_EnableStateChildren = 0x40,
		kExtraData_ItemDropper = 0x41,
		kExtraData_DroppedItemList = 0x42,
		kExtraData_RandomTeleportMarker = 0x43,
		kExtraData_MerchantContainer = 0x44,

		kExtraData_PersuasionPercent = 0x46,
		kExtraData_CannotWear = 0x47,
		kExtraData_Poison = 0x48,

		kExtraData_LastFinishedSequence = 0x4A,
		kExtraData_SavedMovementData = 0x4B,
		kExtraData_NorthRotation = 0x4C,
		kExtraData_XTarget = 0x4D,
		kExtraData_FriendHitList = 0x4E,
		kExtraData_HeadingTarget = 0x4F,
		kExtraData_BoundArmor = 0x50,
		kExtraData_RefractionProperty = 0x51,
		kExtraData_InvestmentGold = 0x52,
		kExtraData_StartingWorldOrCell = 0x53,

		kExtraData_QuickKey = 0x55,

		kExtraData_EditorRefMoveData = 0x57,
		kExtraData_TravelHorse = 0x58,
		kExtraData_InfoGeneralTopic = 0x59,
		kExtraData_HasNoRumors = 0x5A,
		kExtraData_ExtraSound = 0x5B,
		kExtraData_HaggleAmount = 0x5C,
	};

	virtual bool	Compare(BSExtraData* compareWith);	// compare type, data, return true if not equal

	UInt8			type;		// 004
	UInt8			pad[3];		// 005
	BSExtraData*	next;		// 008
};
assert(sizeof(BSExtraData) == 0x0C);

class InventoryChanges : public BSExtraData {
public:
	class EntryData {
	public:
		bool	IsWorn(bool Left) { return ThisCall(0x00484E80, this, Left); }

		TList<ExtraDataList>*	extendData;
		SInt32					countDelta;
		TESForm*				type;
	};

	class Data {
	public:
		TList<EntryData>*	data;
		TESObjectREFR*		owner;
		float				totalWeight;	// of all items in inventory. cached, is -1 if needs to be recalculated
		float				armorWeight;	// weight of equipped armor. cached as above. Both take armor weight perks into account
	};

	Data*	data;			// 00C
};
assert(sizeof(InventoryChanges) == 0x10);

class ExtraDataList {
public:
	virtual	void			Destroy(bool bNoDealloc);	// removes and frees all of m_data
	
	bool					HasType(UInt32 type) { UInt32 index = (type >> 3); UInt8 bitMask = 1 << (type % 8); return (m_presenceBitfield[index] & bitMask) != 0; }
	BSExtraData*			GetByType(UInt32 type) { if (HasType(type)) { for (BSExtraData* Data = m_data; Data; Data = Data->next) { if (Data->type == type) return Data; } } return NULL; }
	bool					IsWorn() { return (HasType(BSExtraData::ExtraDataType::kExtraData_Worn) || HasType(BSExtraData::ExtraDataType::kExtraData_WornLeft)); }
	bool					SetWorn(bool Status, bool Left) { return ThisCall(0x0041F200, this, Status, Left); }
	InventoryChanges::Data*	GetInventoryChangesData() { return (InventoryChanges::Data*)ThisCall(0x0041E6F0, this); }
	//float					GetHealthValue() { return ThisCallF(0x0041E810, this); }
	//void					SetHealthValue(float Value) { ThisCall(0x0041ECB0, this, Value); }

	BSExtraData*			m_data;					// 004
	UInt8					m_presenceBitfield[0x0C];	// 008 - if a bit is set, then the extralist should contain that extradata - bits are numbered starting from the lsb
};
assert(sizeof(ExtraDataList) == 0x14);

class MagicCaster {
public:
	virtual void			Unk_00(UInt32 arg0, UInt32 arg1);
	virtual void			Unk_01(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void			Unk_02(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void			Unk_03();
	virtual void			Unk_04();
	virtual void			Unk_05();
	virtual void			Unk_06();
	virtual bool			Unk_07(MagicItem* magicItem, float* arg1, UInt32* outMagicItemType, UInt32 arg3);
	virtual TESObjectREFR*	GetParentRefr();
	virtual NiNode*			GetMagicNode();	// looks up "magicnode" node in caster's NiNode
	virtual void			Unk_0A();
	virtual float			GetSpellEffectiveness(float arg0, float arg1);	// seen (0, 0)
	virtual MagicItem*		GetQueuedMagicItem();		// calls through to MiddleHighProcess
	virtual void			Unk_0D();
	virtual void			Unk_0E();
	virtual void			Unk_0F();
	virtual void			Unk_10(MagicItem* magicItem, UInt32 mgefCode, UInt32 unk2);	// activate effect?

	enum {
		kState_Inactive = 0,
		kState_Aim = 1,
		kState_Cast = 2,
		kState_FindTargets = 4,
		// these seem to be considered "errors" by the game
		kState_SpellDisabled = 5,
		kState_AlreadyCasting = 6,
		kState_CannotCast = 7
	};

	NiNode* magicNode;		// 004 cached during casting anim
	UInt32	state;			// 008
};
assert(sizeof(MagicCaster) == 0x0C);

class MagicTarget {
public:
	virtual void			Destructor();
	virtual	TESObjectREFR*	GetParent();
	virtual EffectNode*		GetEffectList();

	UInt8	unk04;			// 004
	UInt8	pad05[3];
};
assert(sizeof(MagicTarget) == 0x08);

class ActorValues {
public:
	struct Entry {
		UInt32		avCode;
		float		value;
	};

	TList<Entry>	avList;			// 00
	Entry*			magicka;		// 08
	Entry*			fatigue;		// 0C
	Entry**			avArray;		// 10 array of more AV modifiers, size 0x12?
};
assert(sizeof(ActorValues) == 0x14);

class BaseFormComponent {
public:
	virtual void	Destructor();	// 00
	virtual void	Unk_01();
	virtual void	CopyFromBase(BaseFormComponent* component);
	virtual bool	CompareWithBase(BaseFormComponent* src);
};
assert(sizeof(BaseFormComponent) == 0x004);

class TESDescription : public BaseFormComponent {
public:
	virtual const char* GetText(TESForm* parentForm, UInt32 recordCode);

	UInt32	formDiskOffset;	// 04
};
assert(sizeof(TESDescription) == 0x008);

class TESModel : public BaseFormComponent {
public:
	virtual void			Unk_04();
	virtual const char*		GetModelPath();
	virtual void			SetModelPath(const char* path);

	BSString	nifPath;	// 004
	float		editorSize;	// 00C 'size' field in editor, from MODB subrecord. Only present for objects defined in Oblivion.esm?
	UInt8		unk10;		// 010
	UInt8		pad11[3];
	void*		unk14;		// 014
};
assert(sizeof(TESModel) == 0x018);

class TESModelAnim : public TESModel {};
assert(sizeof(TESModelAnim) == 0x018);

class TESScriptableForm : public BaseFormComponent {
public:
	Script* script;		// 004
	UInt8	unk1;		// 008
	UInt8	pad[3];		// 009
};
assert(sizeof(TESScriptableForm) == 0x00C);

class TESEnchantableForm : public BaseFormComponent {
public:
	EnchantmentItem* enchantItem;	// 04
	UInt16			 enchantment;	// 08
	UInt16			 unk1;			// 0A
	UInt32			 unk2;			// 0C
};
assert(sizeof(TESEnchantableForm) == 0x010);

class TESValueForm : public BaseFormComponent {
public:
	enum {
		kModified_GoldValue = 0x00000008,
	};
	UInt32	value;
};
assert(sizeof(TESValueForm) == 0x008);

class TESWeightForm : public BaseFormComponent {
public:
	float	weight;
};
assert(sizeof(TESWeightForm) == 0x008);

class TESHealthForm : public BaseFormComponent {
public:
	UInt32	health;
};
assert(sizeof(TESHealthForm) == 0x008);

class TESAttackDamageForm : public BaseFormComponent {
public:
	UInt16	damage;
	UInt16	unk0;	// bitmask? perhaps 2 UInt8s?
};
assert(sizeof(TESAttackDamageForm) == 0x008);

class TESForm : public BaseFormComponent {
public:
	enum FormType {
		kFormType_None = 0,
		kFormType_TES4,
		kFormType_Group,
		kFormType_GMST,
		kFormType_Global,
		kFormType_Class,
		kFormType_Faction,
		kFormType_Hair,
		kFormType_Eyes,
		kFormType_Race,
		kFormType_Sound,
		kFormType_Skill,
		kFormType_Effect,
		kFormType_Script,
		kFormType_LandTexture,
		kFormType_Enchantment,
		kFormType_Spell,		// 10
		kFormType_BirthSign,
		kFormType_Activator,
		kFormType_Apparatus,
		kFormType_Armor,
		kFormType_Book,
		kFormType_Clothing,
		kFormType_Container,
		kFormType_Door,
		kFormType_Ingredient,
		kFormType_Light,
		kFormType_Misc,
		kFormType_Stat,	// ???
		kFormType_Grass,
		kFormType_Tree,
		kFormType_Flora,
		kFormType_Furniture,	// 20
		kFormType_Weapon,
		kFormType_Ammo,
		kFormType_NPC,
		kFormType_Creature,
		kFormType_LeveledCreature,
		kFormType_SoulGem,
		kFormType_Key,
		kFormType_AlchemyItem,
		kFormType_SubSpace,
		kFormType_SigilStone,
		kFormType_LeveledItem,
		kFormType_SNDG,
		kFormType_Weather,
		kFormType_Climate,
		kFormType_Region,
		kFormType_Cell,			// 30
		kFormType_REFR,
		kFormType_ACHR,
		kFormType_ACRE,
		kFormType_PathGrid,
		kFormType_WorldSpace,
		kFormType_Land,
		kFormType_TLOD,	// tile low lod?
		kFormType_Road,
		kFormType_Dialog,
		kFormType_DialogInfo,
		kFormType_Quest,
		kFormType_Idle,
		kFormType_Package,
		kFormType_CombatStyle,
		kFormType_LoadScreen,
		kFormType_LeveledSpell,	// 40
		kFormType_ANIO,
		kFormType_Water,
		kFormType_EffectShader,
		kFormType_TOFT
	};

	virtual void	Destroy(bool Dealloc);
	virtual void	Unk_05();	// destroy form components
	virtual void	Unk_06();	// call unk01 on form components
	virtual bool	LoadForm(ModInfo* modInfo);
	virtual void	Unk_08();	// calls load form
	virtual void	Unk_09();	// save form
	virtual void	Unk_0A();	// calls save form
	virtual void	Unk_0B();
	virtual void	Unk_0C();
	virtual void	Unk_0D();
	virtual void	Unk_0E();
	virtual void	Unk_0F();
	virtual void	MarkAsModified(UInt32 mask);	// 10
	virtual void	ClearModified(UInt32 mask);
	virtual void	Unk_12();
	virtual UInt32	GetSaveSize(UInt32 modifiedMask);
	virtual void	SaveGame(UInt32 modifiedMask);	// output buffer not passed as param, accessed indirectly via g_createdBaseObjList
	virtual void	LoadGame(UInt32 modifiedMask, UInt32 unk);
	virtual void	Unk_16();	// post-load fixup (convert refids in to pointers, etc)
	virtual void	Unk_17();
	virtual void	Unk_18();
	virtual void	Unk_19();
	virtual void	Unk_1A();
	virtual void	DoPostFixup();	// initialize form after other forms loaded
	virtual void	Unk_1C();
	virtual void	GetDescription(BSString* dst);
	virtual void	Unk_1E();
	virtual void	Unk_1F();
	virtual void	Unk_20();	// 20
	virtual void	Unk_21();
	virtual void	Unk_22();
	virtual void	Unk_23();
	virtual void	Unk_24(UInt8 arg);
	virtual void	SetQuestItem(bool isQuestItem);
	virtual void	Unk_26();
	virtual void	Unk_27();
	virtual void	Unk_28();
	virtual bool	Unk_29();
	virtual bool	Unk_2A();	// return true if the form is a reference?
	virtual bool	Unk_2B();
	virtual void	Unk_2C();
	virtual void	CopyFrom(TESForm* form);
	virtual bool	Compare(TESForm* form);
	virtual void	Unk_2F();
	virtual void	Unk_30();	// 30
	virtual void	Unk_31();
	virtual void	Unk_32();
	virtual bool	Unk_33(TESObjectREFR* refr0, TESObjectREFR* refr1, UInt32 unk2); // related to activate, refr1 is activating refr, refr0 is a reference to this TESForm being activated, seen unk2 == 0
	virtual char*	GetName();	// not sure which objects this works on, doesn't seem to work on player or random objects
	virtual char*	GetEditorName(); // returns nothing at runtime (return the editorname for TESObjectCELL)
	virtual bool	SetEditorName(const char* name);

	enum {
		kModified_FormFlags = 0x00000001,
		kModified_GoldValue = 0x08,
		kModified_Name = 0x80
	};

	enum {
		kFormFlags_QuestItem = 0x00000400,
		kFormFlags_Destroyed = 0x00002000,
		kFormFlags_IgnoresFriendlyHits = 0x00100000,
	};

	UInt8				typeID;					// 004
	UInt8				typeIDPad[3];			// 005
	UInt32				flags;					// 008
	UInt32				refID;					// 00C
	TList<ModInfo>		modRefList;				// 010
};
assert(sizeof(TESForm) == 0x018);

class TESPackage : public TESForm {
public:
	enum {
		kPackageFlag_OffersServices			= 1 << 0,
		kPackageFlag_MustReachLocation		= 1 << 1,
		kPackageFlag_MustComplete			= 1 << 2,
		kPackageFlag_LockDoorsAtStart		= 1 << 3,
		kPackageFlag_LockDoorsAtEnd			= 1 << 4,
		kPackageFlag_LockDoorsAtLocation	= 1 << 5,
		kPackageFlag_UnlockDoorsAtStart		= 1 << 6,
		kPackageFlag_UnlockDoorsAtEnd		= 1 << 7,
		kPackageFlag_UnlockDoorsAtLocation	= 1 << 8,
		kPackageFlag_ContinueIfPCNear		= 1 << 9,
		kPackageFlag_OncePerDay				= 1 << 10,
		kPackageFlag_Unk11					= 1 << 11,
		kPackageFlag_SkipFalloutBehavior	= 1 << 12,
		kPackageFlag_AlwaysRun				= 1 << 13,
		kPackageFlag_Unk14					= 1 << 14,
		kPackageFlag_Unk15					= 1 << 15,
		kPackageFlag_Unk16					= 1 << 16,
		kPackageFlag_AlwaysSneak			= 1 << 17,
		kPackageFlag_AllowSwimming			= 1 << 18,
		kPackageFlag_AllowFalls				= 1 << 19,
		kPackageFlag_ArmorUnequipped		= 1 << 20,
		kPackageFlag_WeaponsUnequipped		= 1 << 21,
		kPackageFlag_DefensiveCombat		= 1 << 22,
		kPackageFlag_UseHorse				= 1 << 23,
		kPackageFlag_NoIdleAnims			= 1 << 24,
		kPackageFlag_Unk25					= 1 << 25,
		kPackageFlag_Unk26					= 1 << 26,
		kPackageFlag_Unk27					= 1 << 27,
		kPackageFlag_Unk28					= 1 << 28,
		kPackageFlag_Unk29					= 1 << 29,
		kPackageFlag_Unk30					= 1 << 30,
		kPackageFlag_Unk31					= 1 << 31,
	};

	enum {
		kPackageType_Find = 0,
		kPackageType_Follow,
		kPackageType_Escort,
		kPackageType_Eat,
		kPackageType_Sleep,
		kPackageType_Wander,
		kPackageType_Travel,
		kPackageType_Accompany,
		kPackageType_UseItemAt,
		kPackageType_Ambush,
		kPackageType_FleeNotCombat,
		kPackageType_CastMagic,
		kPackageType_CombatController,	// Actor::GetCombatController returns package only if type matches this
		kPackType_Unk0D,				// also related to dynamic combat packages?
		kPackType_MAX
	};

	struct Time {
		enum {
			kDay_Any = 0,
			kTime_Any = 0xFF,
		};

		enum {
			kMonth_January = 0,
			kMonth_February,
			kMonth_March,
			kMonth_April,
			kMonth_May,
			kMonth_June,
			kMonth_July,
			kMonth_August,
			kMonth_September,
			kMonth_October,
			kMonth_November,
			kMonth_December,
			kMonth_Spring,	// march, april, may
			kMonth_Summer,	// june, july, august
			kMonth_Fall,	// september, august, november
			kMonth_Winter,	// december, january, february
			kMonth_Any = 0xFF,
		};

		enum {
			kWeekday_Sundas = 0,
			kWeekday_Morndas,
			kWeekday_Tirdas,
			kWeekday_Middas,
			kWeekday_Turdas,
			kWeekday_Fredas,
			kWeekday_Loredas,
			kWeekday_Weekdays,
			kWeekday_Weekends,
			kWeekday_MWF,
			kWeekday_TT,
			kWeekday_Any = 0xFF
		};

		UInt8	month;
		UInt8	weekDay;
		UInt8	date;
		UInt8	time;
		UInt32	duration;
	};

	union ObjectType {
		TESForm*		form;
		TESObjectREFR*	refr;
		UInt32			objectCode;
	};

	// order only somewhat related to kFormType_XXX (values off by 17, 20, or 21)
	enum {
		kObjectType_Activator = 0x01,
		kObjectType_Apparatus,
		kObjectType_Armor,
		kObjectType_Book,
		kObjectType_Clothing,
		kObjectType_Container,
		kObjectType_Door,
		kObjectType_Ingredient,
		kObjectType_Light,
		kObjectType_Misc,
		kObjectType_Flora,
		kObjectType_Furniture,
		kObjectType_WeaponAny,
		kObjectType_Ammo,
		kObjectType_NPC,
		kObjectType_Creature,		// 10
		kObjectType_Soulgem,
		kObjectType_Key,
		kObjectType_Alchemy,
		kObjectType_Food,
		kObjectType_CombatWearable,
		kObjectType_Wearable,
		kObjectType_WeaponNone,
		kObjectType_WeaponMelee,
		kObjectType_WeaponRanged,
		kObjectType_SpellsAny,
		kObjectType_SpellsTarget,
		kObjectType_SpellsTouch,
		kObjectType_SpellsSelf,
		kObjectType_SpellsAlteration,
		kObjectType_SpellsConjuration,
		kObjectType_SpellsDestruction,	// 20
		kObjectType_SpellsIllusion,
		kObjectType_SpellsMysticism,
		kObjectType_SpellsRestoration,
		kObjectType_Max = 0x24,
	};

	struct LocationData {
		enum {
			kPackLocation_NearReference = 0,
			kPackLocation_InCell = 1,
			kPackLocation_CurrentLocation = 2,
			kPackLocation_EditorLocation = 3,
			kPackLocation_ObjectID = 4,
			kPackLocation_ObjectType = 5,
			kPackLocation_Max,
		};

		UInt8		locationType;
		UInt8		pad[3];
		UInt32		radius;
		ObjectType  object;
	};

	enum {
		kTargetType_Refr = 0,
		kTargetType_BaseObject = 1,
		kTargetType_TypeCode = 2,
	};

	struct TargetData {
		UInt8		targetType;
		UInt8		pad[3];
		ObjectType	target;
		UInt32		count;
	};

	enum eProcedure {			// UInt32
		kProcedure_TRAVEL = 0,
		kProcedure_WANDER,
		kProcedure_ACTIVATE,
		kProcedure_AQUIRE,	// sic
		kProcedure_SLEEP,
		kProcedure_EAT,
		kProcedure_FOLLOW,
		kProcedure_ESCORT,
		kProcedure_ALARM,
		kProcedure_COMBAT,
		kProcedure_FLEE,
		kProcedure_YIELD,
		kProcedure_DIALOGUE,
		kProcedure_WAIT,
		kProcedure_TRAVEL_TARGET,
		kProcedure_PURSUE,
		kProcedure_GREET,					// 0x10
		kProcedure_CREATE_FOLLOW,
		kProcedure_OBSERVE_COMBAT,
		kProcedure_OBSERVE_DIALOGUE,
		kProcedure_GREET_DEAD,
		kProcedure_WARN,
		kProcedure_GET_UP,
		kProcedure_MOUNT_HORSE,
		kProcedure_DISMOUNT_HORSE,
		kProcedure_DO_NOTHING,
		kProcedure_CAST_SPELL,
		kProcedure_AIM,
		kProcedure_NOTIFY,
		kProcedure_ACCOMPANY,
		kProcedure_USE_ITEM_AT,
		kProcedure_FEED,
		kProcedure_AMBUSH_WAIT,				// 0x20
		kProcedure_SURFACE,
		kProcedure_WAIT_FOR_SPELL,
		kProcedure_CHOOSE_CAST,
		kProcedure_FLEE_NON_COMBAT,
		kProcedure_REMOVE_WORN_ITEMS,
		kProcedure_SEARCH,
		kProcedure_CLEAR_MOUNT_POSITION,
		kProcedure_SUMMON_CREATURE_DEFEND,
		kProcedure_MOVEMENT_BLOCKED,
		kProcedure_UNEQUIP_ARMOR,
		kProcedure_DONE,					// 0x2B

		kProcedure_MAX						// 0x2C
	};

	UInt32			procedureArrayIndex;	// 018 index into array of array of eProcedure terminated by 0x2C (-1 if no procedure array exists for package type)
	UInt32			packageFlags;			// 01C
	UInt8			type;					// 020
	UInt8			pad021[3];				// 021
	LocationData*	location;				// 024
	TargetData*		target;					// 028
	Time			time;					// 02C
	UInt32			conditionList[2];		// 034 ConditionEntry
};
assert(sizeof(TESPackage) == 0x3C);

class TESIdleForm : public TESForm {
public:
	enum {
		kFlags_LowerBody = 0,
		kFlags_LeftArm,
		kFlags_LeftHand,
		kFlags_RightArm,
		kFlags_SpecialIdle,
		kFlags_WholeBody,
		kFlags_UpperBody,
		kFlags_MustReturnFile = 0x7F
	};

	TESModelAnim	animModel;		// 18

	TList<void*>	conditions;		// 30 Condition List
	UInt32			animFlags;		// 38
	NiFormArray*	children;		// 3C
	TESIdleForm*	parent;			// 40
	TESIdleForm*	previous;		// 44
};
assert(sizeof(TESIdleForm) == 0x48);

class TESTexture : public BaseFormComponent {
public:
	BSString	ddsPath;		// 04
};
assert(sizeof(TESTexture) == 0x0C);

class TESIcon : public TESTexture { };
assert(sizeof(TESIcon) == 0x0C);

class TESFullName : public BaseFormComponent {
public:
	BSString	name;		// 004
};
assert(sizeof(TESFullName) == 0x0C);

class TESWeather : public TESForm {
public:
	enum { kNumColorTypes = 10 };
	enum { kNumTimeOfDay = 4 };

	struct FogInfo {
		float nearFog;
		float farFog;
	};

	enum {
		eHDR_EyeAdpat = 0,
		eHDR_BlurRadius,
		eHDR_BlurPasses,
		eHDR_EmissiveMult,
		eHDR_TargetLUM,
		eHDR_UpperLUMClamp,
		eHDR_BrightScale,
		eHDR_BrightClamp,
		eHDR_LUMRampNoTex,
		eHDR_LUMRampMin,
		eHDR_LUMRampMax,
		eHDR_SunlightDimmer,
		eHDR_GrassDimmer,
		eHDR_TreeDimmer,
		eHDR_Last = eHDR_TreeDimmer,
	};

	enum {
		eColor_SkyUpper = 0,
		eColor_Fog,
		eColor_CloudsLower,
		eColor_Ambient,
		eColor_Sunlight,
		eColor_Sun,
		eColor_Stars,
		eColor_SkyLower,
		eColor_Horizon,
		eColor_CloudsUpper,
		eColor_Lightning,
	};

	enum {
		eTime_Sunrise = 0,
		eTime_Day,
		eTime_Sunset,
		eTime_Night,
	};

	struct ColorData {
		RGBA colors[4];
	};

	struct SoundData {
		UInt32	refID;
		UInt32	count;
	};

	enum { // Alenet: this enum seems wrong because rainy weather is 4
		kType_None = 0,
		kType_Pleasant = 1,
		kType_Cloudy = 2,
		kType_Rainy = 3,
		kType_Snow = 4
	};

	TESTexture		upperLayer;		// 018
	TESTexture		lowerLayer;		// 024
	TESModel		model;			// 030
	UInt8			windSpeed;
	UInt8			cloudSpeedLower;
	UInt8			cloudSpeedUpper;
	UInt8			transDelta;
	UInt8			sunGlare;
	UInt8			sunDamage;
	UInt8			precipitationBeginFadeIn;
	UInt8			precipitationEndFadeOut;
	UInt8			lightningBeginFadeIn;
	UInt8			lightningEndFadeOut;
	UInt8			lightningFrequency;
	UInt8			precipType;
	RGBA			lightningColor;
	FogInfo			fogDay;			// 058
	FogInfo			fogNight;		// 060
	ColorData		colors[10];		// 068
	SoundData*		unk108;	// these are the bits and pieces of the sound data
	SoundData*		unk10C;	// in the one decoded case there are only 2 - so this may be a head/tail interface
	float			hdrInfo[14];		// 110
};
assert(sizeof(TESWeather) == 0x148);

class TESClimate : public TESForm {
public:
	enum {
		kClimate_Masser = 0x80,
		kClimate_Secunda = 0x40,
		kClimate_PhaseLengthMask = 0x3F,
	};

	struct WeatherType {
		TESWeather* weather;
		UInt32		chance;
	};

	TESModel			nightSky;		// 018
	TList<WeatherType>	weatherTypes;	// 030
	TESTexture			sun;			// 038
	TESTexture			sunGlare;		// 044
	UInt8				sunriseBegin;	// 050
	UInt8				sunriseEnd;		// these are the number of 10 minute increments past midnight
	UInt8				sunsetBegin;	// 6 increments per hour
	UInt8				sunsetEnd;
	UInt8				volatility;		// 054
	UInt8				phaseLength;
	UInt8				pad[2];
};
assert(sizeof(TESClimate) == 0x058);

class TESWaterForm : public TESForm {
public:
	enum {								// use to index into simValues array
		kWaterVal_WindVelocity = 0,
		kWaterVal_WindDirection,
		kWaterVal_WaveAmplitude,
		kWaterVal_WaveFrequency,
		kWaterVal_SunPower,
		kWaterVal_Reflectivity,
		kWaterVal_FresnelAmount,
		kWaterVal_ScrollX,
		kWaterVal_ScrollY,
		kWaterVal_FogDistNear,
		kWaterVal_FogDistFar,

		kWaterVal_Max
	};

	TESAttackDamageForm	damageForm;			// 18
	TESTexture			texture;			// 20
	UInt8				opacity;			// 2C init'ed to 0x4B
	UInt8				waterType;			//    looks like flags
	UInt8				pad2E[2];
	UInt32				unk30;				// 30
	UInt16				unk34;				// 34
	UInt16				unk36;
	TESSound*			loopSound;		// 38
	float				waterSimVals[11];	// 3C .. 64
	UInt8				shallowColorR;		// 68
	UInt8				shallowColorG;
	UInt8				shallowColorB;
	UInt8				shallowColorA;
	UInt8				deepColorR;			// 6C
	UInt8				deepColorG;
	UInt8				deepColorB;
	UInt8				deepColorA;
	UInt8				reflectColorR;		// 70
	UInt8				reflectColorG;
	UInt8				reflectColorB;
	UInt8				reflectColorA;
	UInt32				textureBlend;		// 74
	float				rainSimVals[5];		// 78 .. 88
	float				displacementSimVals[5];	// 8C .. 9C
	UInt32				unkA0[3];			// A0 .. A8 look like pointers to day/night/underwater water forms
};
assert(sizeof(TESWaterForm) == 0x0AC);

class TESWorldSpace : public TESForm {
public:
	enum {
		// "Can't Wait" flag does not appear to be saved by editor
		kFlag_SmallWorld	= 1 << 0,
		kFlag_NoFastTravel	= 1 << 1,
		kFlag_OblivionWorld = 1 << 2,
		kFlag_NoLODWater	= 1 << 4,
	};

	TESFullName						fullName;			// 018
	TESTexture						texture;			// 024
	NiTMap<UInt32, TESObjectCELL>*  cellMap;			// 030 - key is coordinates of cell: (x << 16 + y)
	TESObjectCELL*					unk034;				// 034
	NiTMap<UInt32, void>			map;				// 038
	TESWorldSpace*					worldSpace048;		// 048
	UInt32							unk04C[(0x58 - 0x4C) >> 2];	// 04C
	TESClimate*						climate;			// 058
	UInt32							worldFlags;			// 05C
	UInt32							unk060;				// 060
	NiTMap<UInt32, void>			map064;				// 064
	Character*						character;			// 074
	void*							ptr078;				// 078
	TESWorldSpace*					parentWorldspace;	// 07C
	UInt32							unk080[(0xC0 - 0x80) >> 2];	// 080
	BSString						editorID;			// 0C0
	NiTMap<UInt32, void>			map0C8;				// 0C8
	UInt32							unk0D8[(0xE0 - 0xD8) >> 2];	// 0D8
};
assert(sizeof(TESWorldSpace) == 0x0E0);

class TESGlobal : public TESForm {
public:
	enum {
		kType_Short = 's',
		kType_Long  = 'l',
		kType_Float = 'f'
	};

	BSString	name;		// 018
	UInt8		type;		// 020
	UInt8		pad21[3];	// 021
	float		data;		// 024
};
assert(sizeof(TESGlobal) == 0x028);

class TESSkill : public TESForm {
public:
	enum {
		kSkill_Armorer = 0x0C,
		kSkill_Athletics,
		kSkill_Blade,
		kSkill_Block,
		kSkill_Blunt,		// 10
		kSkill_HandToHand,
		kSkill_HeavyArmor,
		kSkill_Alchemy,
		kSkill_Alteration,
		kSkill_Conjuration,
		kSkill_Destruction,
		kSkill_Illusion,
		kSkill_Mysticism,	// 18
		kSkill_Restoration,
		kSkill_Acrobatics,
		kSkill_LightArmor,
		kSkill_Marksman,
		kSkill_Mercantile,
		kSkill_Security,
		kSkill_Sneak,
		kSkill_Speechcraft,	// 20
	};

	TESDescription	description;	// 018
	TESTexture		texture;		// 020
	UInt32			skill;			// 02C
	UInt32			attribute;		// 030
	UInt32			specialization;	// 034
	float			useValue0;		// 038 - amount to learn on successful action
	float			useValue1;		// 03C - action is different for each skill
	TESDescription	levelQuote[4];	// 040

};
assert(sizeof(TESSkill) == 0x060);

class TESRegion : public TESForm {
public:
	struct Unk018 {
		UInt32	unk0;
		UInt32	unk4;
		UInt8	unk8;
		UInt8	pad9[3];
	};

	struct Unk01C {
		UInt32	unk0;
		Unk01C* next;
	};

	Unk018*			unk018;				// 018
	Unk01C*			unk01C;				// 01C
	TESWorldSpace*  worldSpace;	// 020
	TESWeather*		weather;		// 024
	float			unk028;					// 028
};
assert(sizeof(TESRegion) == 0x02C);

class TESObject : public TESForm {
public:
	virtual void	Unk_37();
	virtual void	Unk_38();
	virtual void	Unk_39();
	virtual void	Unk_3A();
	virtual void	Unk_3B();
	virtual void	Unk_3C();
	virtual void	Unk_3D();
	virtual void	Unk_3E();
	virtual void	Unk_3F();
	virtual void	Unk_40();
	virtual void	Unk_41();
	virtual void	Unk_42();
	virtual void	Unk_43();
	virtual void	Unk_44();
};
assert(sizeof(TESObject) == 0x018);

class TESBoundObject : public TESObject {
public:
	virtual void	Unk_45();
	virtual void	Unk_46();
	virtual void	Unk_47();

	BoundObjectListHead* head;	// 018
	TESBoundObject*		 prev;	// 01C
	TESBoundObject*		 next;	// 020

};
assert(sizeof(TESBoundObject) == 0x024);

class TESSoundFile : public BaseFormComponent {
public:
	BSString	fileName;	// 004
	BSString	editorID;	// 00C
};
assert(sizeof(TESSoundFile) == 0x014);

class TESBoundAnimObject : public TESBoundObject {
public:
	TESSoundFile	soundFile;			// 024
};
assert(sizeof(TESBoundAnimObject) == 0x038);

class TESSound : public TESBoundAnimObject {
public:
	enum {
		kFlags_RandomFrequencyShift = 1,
		//...
		kFlags_Loop = 1 << 4,
		kFlags_MenuSound = 1 << 5,
		kFlags_2D = 1 << 6,
		//...
	};

	UInt8			minAttenuation;		// 038 not taken directly from CS
	UInt8			maxAttenuation;		// 039 likewise. Different ratios for each
	UInt8			frequencyAdjust;	// 03A
	UInt8			unk9;				// 03B
	UInt32			flags;				// 03C
	UInt16			staticAttenuation;	// 040 - CS value * -100
	UInt16			unk12;				// 042 related to start/end times
};
assert(sizeof(TESSound) == 0x44);

class TESObjectWEAP : public TESBoundObject {
public:
	enum {
		kType_BladeOneHand = 0,
		kType_BladeTwoHand,
		kType_BluntOneHand,
		kType_BluntTwoHand,
		kType_Staff,
		kType_Bow,

		kType_Max,
	};

	TESFullName			fullName;		// 024
	TESModel			model;			// 030
	TESIcon				icon;			// 048
	TESScriptableForm	scriptable;		// 054
	TESEnchantableForm	enchantable;	// 060
	TESValueForm		value;			// 070
	TESWeightForm		weight;			// 078
	TESHealthForm		health;			// 080
	TESAttackDamageForm	attackDmg;		// 088
	UInt32				type;			// 090
	float				speed;			// 094
	float				reach;			// 098
	UInt32				ignoreNormalWeaponResist;	// 09C
};

class TESObjectCELL : public TESForm {
public:
	enum {
		kModified_DetachTime = 0x08000000,
		kModified_CellFlags = 0x00000008,
		kModified_SeenData = 0x10000000,
		kModified_FullName = 0x00000010,
		kModified_Ownership = 0x00000020,
		kModified_Pathgrid = 0x01000000,
	};
	enum {
		kFlags0_Interior = 1 << 0,
		kFlags0_HasWater = 1 << 1,
		kFlags0_Unk2 = 1 << 2,
		kFlags0_ForceHideLand = 1 << 3,	// shared bit - for exterior
		kFlags0_OblivionInterior = 1 << 3,	// shared bit - for interior
		kFlags0_Unk4 = 1 << 4,
		kFlags0_Public = 1 << 5,
		kFlags0_HandChanged = 1 << 6,
		kFlags0_BehaveLikeExterior = 1 << 7,
	};
	struct CellCoordinates {
		SInt32	x;
		SInt32	y;
	};
	struct LightingData {
		RGBA		ambient;
		RGBA		directional;
		RGBA		fog;
		float		fogNear;
		float		fogFar;
		UInt32		rotXY;
		UInt32		rotZ;
		float		directionalFade;
		float		fogClipDistance;
	};

	float			GetWaterHeight() { return ThisCallF(0x004CACE0, this); }
	TESWaterForm*	GetWaterForm() { return NULL; }

	TESFullName			 fullName;		// 018
	UInt8				 flags0;		// 024
	UInt8				 flags1;		// 025
	UInt8				 flags2;		// 026
	UInt8				 pad27;			// 027
	ExtraDataList		 extraDataList;	// 028 includes ExtraEditorID
	union {
		CellCoordinates* coords;		// if exterior
		LightingData*	 lighting;		// if interior
	};									// 3C
	TESObjectLAND*		 land;			// 040
	TESPathGrid*		 pathGrid;		// 044
	TList<TESObjectREFR> objectList;	// 048
	TESWorldSpace*		 worldSpace;	// 050
	NiNode*				 unk6;			// 054
};
assert(sizeof(TESObjectCELL) == 0x058);

class TESObjectREFR : public TESForm {
public:
	enum {
		kChanged_IsEmpty				= 0x00010000,
		kChanged_Inventory				= 0x08000000,
		kChanged_Animation				= 0x02000000,
		kChanged_Move					= 0x00000004,
		kChanged_HavokMove				= 0x00000008,
		kChanged_MapMarkerFlags			= 0x00000400,
		kChanged_HadHavokMoveFlag		= 0x00000800,
		kChanged_Scale					= 0x00000010,
		kChanged_DoorOpenDefaultState	= 0x00040000,
		kChanged_DoorOpenState			= 0x00080000,
		kChanged_DoorExtraTeleport		= 0x00100000,
		kChanged_ExtraOwner				= 0x00000080,
	};

	enum {
		kFlags_Persistent = 0x00000400,
		kFlags_Disabled = 0x00000800,
		kFlags_Unk00000002 = 0x00000002,
		kFlags_Deleted = 0x00000020,
		kFlags_Unk128 = 0x80000000,
		kFlags_Temporary = 0x00004000,
		kFlags_Taken = kFlags_Deleted | kFlags_Unk00000002
	};

	virtual void			Unk_37();
	virtual void			Unk_38();	// 38
	virtual void			Unk_39();
	virtual void			Unk_3A();
	virtual float			GetScale();
	virtual void			GetStartingAngle(float* pos);
	virtual void			GetStartingPos(float* pos);
	virtual void			Unk_3E();
	virtual void			Unk_3F();
	virtual void			RemoveItem(TESForm* toRemove, ExtraDataList* extraList, int Quantity, UInt8 unk4, UInt8 unk5, TESObjectREFR* destRef, float* unk7, float* unk8, UInt8 unk9, UInt8 unk10);	// 40
	virtual void			Unk_41();
	virtual UInt8			Equip(TESForm* toEquip, int Quantity, ExtraDataList* extraList, UInt32 unk4);
	virtual UInt8			Unequip(TESForm* toUnequip, int Quantity, ExtraDataList* extraList);
	virtual void			Unk_44();
	virtual void			AddItem(TESForm* toAdd, ExtraDataList* extraList, int Quantity);
	virtual void			Unk_46();
	virtual void			Unk_47();
	virtual void			Unk_48();
	virtual MagicTarget*	GetMagicTarget();
	virtual void			Unk_4A();
	virtual void			Unk_4B();
	virtual void			Unk_4C();
	virtual void			Unk_4D();
	virtual void			Unk_4E();
	virtual void			Unk_4F();
	virtual void			Unk_50();	// 50
	virtual void			Unk_51();
	virtual void			Unk_52();			// inits animation-related data, and more
	virtual NiNode*			GenerateNiNode();
	virtual void			Set3D(NiNode* niNode);
	virtual NiNode*			GetNiNode();
	virtual void			Unk_56();
	virtual void			Unk_57(UInt32 arg0);
	virtual void			Unk_58();
	virtual ActorAnimData*	GetActorAnimData();
	virtual void			Unk_5A();
	virtual void			Unk_5B();
	virtual TESForm*		GetBaseForm();	// returns type this object references
	virtual NiPoint3*		GetPos();
	virtual void			Unk_5E();
	virtual void			Unk_5F();
	virtual UInt32			Unk_60(UInt32 Arg1);	// gets something from the ridden creature or actor
	virtual void			Unk_61();
	virtual void			Unk_62();
	virtual UInt8			GetSitSleepState(); // calls the Process::GetSitSleepState
	virtual bool			IsActor();
	virtual void			ChangeCell(TESObjectCELL* newCell);
	virtual UInt8			GetLifeState(UInt8 Arg1);
	virtual UInt8			GetKnockedState(); // calls the Process::GetKnockedState
	virtual void			Unk_68();
	virtual void			Unk_69();
	
	InventoryChanges::EntryData* GetInventoryItem(UInt32 Index) { return (InventoryChanges::EntryData*)ThisCall(0x004D88F0, this, Index, 0); }

	TESChildCell		childCell;		// 018
	TESForm*			baseForm;		// 01C
	NiPoint3			rot;			// 020
	NiPoint3			pos;			// 02C
	float				scale;			// 038 
	NiNode*				niNode;			// 03C
	TESObjectCELL*		parentCell;		// 040
	ExtraDataList		extraDataList;	// 044
};
assert(sizeof(TESObjectREFR) == 0x058);

class MobileObject : public TESObjectREFR {
public:
	virtual void	Unk_6A();	// 6A
	virtual void	Unk_6B();
	virtual void	Unk_6C();
	virtual void	Move();
	virtual void	Jump();
	virtual void	Unk_6F();
	virtual void	Unk_70();	// 70
	virtual void	Unk_71();
	virtual void	Unk_72();
	virtual void	Unk_73();
	virtual void	Unk_74();
	virtual void	Unk_75();
	virtual void	Unk_76();
	virtual void	Unk_77();
	virtual void	Unk_78();
	virtual void	Unk_79();
	virtual void	Unk_7A();
	virtual void	Unk_7B();
	virtual void	Unk_7C();
	virtual float	GetJumpScale();
	virtual void	Unk_7E();
	virtual void	Unk_7F();
	virtual void	Unk_80();	// 80
	virtual SInt32	GetFame();

	BaseProcess*	process;			// 058
};
assert(sizeof(MobileObject) == 0x05C);

class Actor : public MobileObject {
public:
	enum ActorVal {
		kActorVal_Strength = 0,		// 0x00
		kActorVal_Intelligence,
		kActorVal_Willpower,
		kActorVal_Agility,
		kActorVal_Speed,
		kActorVal_Endurance,		//0x05
		kActorVal_Personality,
		kActorVal_Luck,
		kActorVal_Health,
		kActorVal_Magicka,
		kActorVal_Fatigue,			// 0x0a
		kActorVal_Encumbrance,
		kActorVal_Armorer,
		kActorVal_Athletics,
		kActorVal_Blade,
		kActorVal_Block,			// 0x0f
		kActorVal_Blunt,			// 0x10
		kActorVal_HandToHand,
		kActorVal_HeavyArmor,
		kActorVal_Alchemy,
		kActorVal_Alteration,
		kActorVal_Conjuration,		// 0x15
		kActorVal_Destruction,
		kActorVal_Illusion,
		kActorVal_Mysticism,
		kActorVal_Restoration,
		kActorVal_Acrobatics,		// 0x1a
		kActorVal_LightArmor,
		kActorVal_Marksman,
		kActorVal_Mercantile,
		kActorVal_Security,
		kActorVal_Sneak,			// 0x1f
		kActorVal_Speechcraft,		// 0x20
		kActorVal_Aggression,
		kActorVal_Confidence,
		kActorVal_Energy,
		kActorVal_Responsibility,
		kActorVal_Bounty,			// 0x25
		kActorVal_Fame,
		kActorVal_Infamy,
		kActorVal_MagickaMultiplier,
		kActorVal_NightEyeBonus,
		kActorVal_AttackBonus,		// 0x2a
		kActorVal_DefendBonus,
		kActorVal_CastingPenalty,
		kActorVal_Blindness,
		kActorVal_Chameleon,
		kActorVal_Invisibility,		// 0x2f
		kActorVal_Paralysis,		// 0x30
		kActorVal_Silence,
		kActorVal_Confusion,
		kActorVal_DetectItemRange,
		kActorVal_SpellAbsorbChance,
		kActorVal_SpellReflectChance,// 0x35
		kActorVal_SwimSpeedMultiplier,
		kActorVal_WaterBreathing,
		kActorVal_WaterWalking,
		kActorVal_StuntedMagicka,
		kActorVal_DetectLifeRange,	// 0x3a
		kActorVal_ReflectDamage,
		kActorVal_Telekinesis,
		kActorVal_ResistFire,
		kActorVal_ResistFrost,
		kActorVal_ResistDisease,	// 0x3f
		kActorVal_ResistMagic,		// 0x40
		kActorVal_ResistNormalWeapons,
		kActorVal_ResistParalysis,
		kActorVal_ResistPoison,
		kActorVal_ResistShock,
		kActorVal_Vampirism,		// 0x45
		kActorVal_Darkness,
		kActorVal_ResistWaterDamage,
		kActorVal_OblivionMax,
	};

	virtual SInt32	GetInfamy();
	virtual void	Resurrect(UInt8 Unk1, UInt8 Unk2, UInt8 Unk3);
	virtual void	Unk_84();
	virtual void	Unk_85();
	virtual void	Unk_86();
	virtual void	Unk_87();
	virtual void	ApplyDamage(float damage, float arg1, Actor* attacker);
	virtual void	Unk_89();
	virtual void	ProcessControls();
	virtual void	Unk_8B();
	virtual void	SetPackageDismount();
	virtual void	Unk_8D();
	virtual void	Unk_8E();
	virtual void	Unk_8F();
	virtual void	OnAlarmAttack(Actor* attackVictim, UInt32 arg1);	// 90 tries to send alarm when 'this' attacks victim
	virtual void	Unk_91();
	virtual void	Unk_92();	// SendTrespassAlarm
	virtual void	Unk_93();
	virtual void	Unk_94();
	virtual void	Unk_95();
	virtual void	Unk_96();
	virtual void	Unk_97();
	virtual bool	GetVampireHasFed();
	virtual void	SetVampireHasFed(bool bFed);
	virtual void	GetBirthSign();
	virtual void	Unk_9B();
	virtual void	Unk_9C();
	virtual void	Unk_9D();
	virtual void	Unk_9E();
	virtual void	Unk_9F();
	virtual void	Unk_A0();	// A0
	virtual UInt32	GetActorValue(UInt32 avCode);								// current, cumulative value
	virtual float	GetAV_F(UInt32 avCode);
	virtual void	SetAV_F(UInt32 avCode, float val);							// base value
	virtual void	SetActorValue(UInt32 avCode, UInt32 val);
	virtual void	ModMaxAV_F(UInt32 avCode, float amt, Actor* arg2);
	virtual void	ModMaxAV(UInt32 avCode, SInt32 amt, Actor* arg2);
	virtual void	ApplyScriptAVMod_F(UInt32 avCode, float amt, UInt32 arg2);	// script cmds Mod/ForceAV
	virtual void	ApplyScriptAVMod(UInt32 avCode, SInt32 amt, Actor* arg2);
	virtual void	DamageAV_F(UInt32 avCode, float amt, Actor* arg2);			// modifier <= 0, console ModAV cmd, damage health, etc
	virtual void	DamageAV(UInt32 value, UInt32 amount, UInt32 unk);
	virtual void	ModBaseAV_F(UInt32 avCode, float amt);
	virtual void	ModBaseAV(UInt32 avCode, SInt32 amt);
	virtual void	Unk_AD();
	virtual void	Unk_AE();
	virtual void	Unk_AF();
	virtual void	Unk_B0();	// B0
	virtual void	Unk_B1();
	virtual void	Unk_B2();
	virtual void	Unk_B3(TESObjectREFR* activatedRefr, UInt32 quantity); // called after Activate by TESForm::Unk33()
	virtual void	Unk_B4();
	virtual void	Unk_B5();
	virtual void	Unk_B6();
	virtual void	Unk_B7();	// AddSpell?
	virtual void	Unk_B8();	// RemoveSpell?
	virtual void	Unk_B9();
	virtual void	Unk_BA();
	virtual void	Unk_BB();
	virtual void	Unk_BC();
	virtual void	Unk_BD();
	virtual void	Unk_BE();
	virtual void	Unk_BF();
	virtual void	Unk_C0();	// C0
	virtual void	Unk_C1();
	virtual void	Unk_C2();
	virtual void	Unk_C3();
	virtual void	ManageAlarm();
	virtual void	Unk_C5();
	virtual void	Unk_C6();
	virtual void	Unk_C7();
	virtual void	AddPackageWakeUp();
	virtual void	Unk_C9();
	virtual void	Unk_CA();
	virtual void	Unk_CB();
	virtual CombatController* GetCombatController();
	virtual bool	IsInCombat(bool unk);
	virtual TESForm* GetCombatTarget();
	virtual void	Unk_CF();
	virtual void	Unk_D0();	// D0
	virtual void	Unk_D1();
	virtual void	Unk_D2();
	virtual void	Unk_D3();
	virtual bool	IsYielding();
	virtual void	Unk_D5();
	virtual void	Unk_D6();
	virtual void	Unk_D7();
	virtual void	Unk_D8();
	virtual void	Unk_D9();
	virtual void	Unk_DA();
	virtual void	Unk_DB();
	virtual void	Unk_DC();
	virtual void	Unk_DD();
	virtual void	Unk_DE();
	virtual void	Unk_DF();
	virtual Creature* GetMountedHorse();	// E0 returns this->horseOrRider, only for Character
	virtual void	Unk_E1();
	virtual void	Unk_E2();
	virtual void	Unk_E3();
	virtual void	Unk_E4();
	virtual void	Unk_E5();
	virtual void	Unk_E6();
	virtual void	ModExperience(UInt32 actorValue, UInt32 scaleIndex, float baseDelta);
	virtual void	Unk_E8();
	virtual void	Unk_E9();
	virtual void	Unk_EA();
	virtual void	AttackHandling(UInt32 unused, TESObjectREFR* arrowRef, TESObjectREFR* target);	// args all null for melee attacks
	virtual void	Unk_EC();
	virtual void	Unk_ED();	// something with blocking
	virtual void	OnHealthDamage(Actor* attacker, float damage);

	UInt32			GetBaseActorValue(ActorVal Code) { return ThisCall(0x005F1910, this, Code); }
	void			EquipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List, UInt32 Unk3 = 0, bool Lock = false) { ThisCall(0x005FAEA0, this, Form, Quantity, List, Unk3, Lock); }
	void			UnequipItem(TESForm* Form, UInt32 Quantity, ExtraDataList* List, UInt32 Unk3 = 0, bool Lock = false, UInt32 Unk5 = 0) { ThisCall(0x005F2E70, this, Form, Quantity, List, Unk3, Lock, Unk5); }
	bool			IsFemale() { return ThisCall(0x005E1DF0, this); }

	MagicCaster		magicCaster;					// 05C
	MagicTarget		magicTarget;					// 068
	UInt32			unk070;							// 070
	UInt32			unk074;							// 074
	UInt8			unk078;							// 078
	UInt8			pad078[3];						// 079
	Actor*			unk07C;							// 07C
	UInt32			unk080;							// 080
	float			unk084;							// 084
	ActorValues		avModifiers;					// 088
	UInt32			greaterPowerList[2];			// 09C PowerListEntry
	UInt32			unk0A4;							// 0A4
	UInt32			unk0A8;							// 0A8
	float			unk0AC;							// 0AC
	UInt32			LifeState;						// 0B0
	UInt32			unk0B4;							// 0B4
	UInt32			unk0B8;							// 0B8
	float			unk0BC;							// 0BC
	UInt8			unk0C0;							// 0C0
	UInt8			pad0C0[3];						// 0C1
	UInt32			unk0C4;							// 0C4
	UInt8			unk0C8;							// 0C8
	UInt8			unk0C9;							// 0C9
	UInt8			unk0CA;							// 0CA
	UInt8			pad0C8;							// 0CB
	TESObjectREFR*	unk0CC;							// 0CC
	UInt32			unk0D0;							// 0D0
	Actor*			horseOrRider;					// 0D4 For Character, currently ridden horse; For horse (Creature), currently riding Character
	UInt8			unk0D8;							// 0D8
	UInt8			pad0D8[3];						// 0D9
	float			unk0DC;							// 0DC
	UInt32			unk0E0;							// 0E0
	Actor*			unk0E4;							// 0E4
	UInt32			unk0E8;							// 0E8
	UInt32			unk0EC;							// 0EC
	UInt32			unk0F0;							// 0F0
	float			unk0F4;							// 0F4
	UInt32			unk0F8;							// 0F8
	UInt8			unk0FC;							// 0FC
	UInt8			unk0FD;							// 0FD //It is set to 0 when Process::GetCurDay == TimeGlobals::GetDay
	UInt8			pad0FC[2];						// 0FE
	float			unk100;							// 100
};
assert(sizeof(Actor) == 0x104);

class Creature : public Actor {
public:
	UInt32		unk104;				// 104
};
assert(sizeof(Creature) == 0x108);

class Character : public Actor {
public:
	SkinInfo*	ActorSkinInfo;						// 104
	UInt32		unk108;								// 108
};
assert(sizeof(Character) == 0x10C);

class PlayerCharacter : public Character {
public:
	enum {
		kMiscStat_DaysInPrison = 0,
		kMiscStat_DaysPassed,
		kMiscStat_SkillIncreases,
		kMiscStat_TrainingSessions,
		kMiscStat_LargestBounty,
		kMiscStat_CreaturesKilled,
		kMiscStat_PeopleKilled,
		kMiscStat_PlacesDiscovered,
		kMiscStat_LocksPicked,
		kMiscStat_LockpicksBroken,
		kMiscStat_SoulsTrapped,	// 10
		kMiscStat_IngredientsEaten,
		kMiscStat_PotionsMade,
		kMiscStat_OblivionGatesShut,
		kMiscStat_HorsesOwned,
		kMiscStat_HousesOwned,
		kMiscStat_StoresInvestedIn,
		kMiscStat_BooksRead,
		kMiscStat_SkillBooksRead,
		kMiscStat_ArtifactsFound,
		kMiscStat_HoursSlept,	// 20
		kMiscStat_HoursWaited,
		kMiscStat_DaysAsAVampire,
		kMiscStat_LastDayAsAVampire,
		kMiscStat_PeopleFedOn,
		kMiscStat_JokesTold,
		kMiscStat_DiseasesContracted,
		kMiscStat_NirnrootsFound,
		kMiscStat_ItemsStolen,
		kMiscStat_ItemsPickpocketed,
		kMiscStat_Trespasses,	// 30
		kMiscStat_Assaults,
		kMiscStat_Murders,
		kMiscStat_HorsesStolen,
		kMiscStat_Max			// 34
	};

	struct TopicList {
		TESTopic* topic;
		TopicList* next;
	};

	struct Unk5B0 {
		float unk[21];
	};

	void			RestoreCamera() { ThisCall(0x0066C600, this); }
	void			SetCameraFOV(float FoV) { ThisCall(0x00664A40, this, FoV); }
	void			UpdateInventory() { void (*UpdateInventoryMenu)() = (void(*)())0x005AADC0; ThisCall(0x00668CC0, this); ThisCall(0x006575B0, this->process, this, 1, 0, 0); ThisCall(0x0060E260, this); UpdateInventoryMenu(); }

	UInt8			unk10C;										// 10C
	UInt8			pad10D[3];									// 10D
	UInt32			unk110;										// 110
	UInt8			unk114;										// 114
	UInt8			unk115;										// 115
	UInt8			isInSEWorld;								// 116
	UInt8			unk117;										// 117
	DialoguePackage* dialoguePackage;							// 118
	UInt32			unk11C;										// 11C
	UInt32			unk120;										// 120
	UInt32			unk124;										// 124
	UInt32			unk128;										// 128
	UInt8			isMovingToNewSpace;							// 12C
	UInt8			pad12C[3];
	float			skillExp[21];								// 130	current experience for each skill
	UInt32			majorSkillAdvances;							// 184
	UInt32			skillAdv[21];								// 188 number of advances for each skill
	UInt8			bCanLevelUp;								// 1DC
	UInt8			unk1DD[3];									// 1DD
	Creature*		lastRiddenHorse;							// 1E0
	UInt32			unk1E4;										// 1E4
	UInt32			unk1E8;										// 1E8
	UInt32			unk1EC;										// 1EC
	UInt32			unk1F0;										// 1F0
	UInt32			unk1F4;										// 1F4
	UInt32			unk1F8;										// 1F8
	UInt32			unk1FC;										// 1FC
	UInt32			unk200;										// 200
	float			maxAVModifiers[kActorVal_OblivionMax];		// 204
	float			scriptAVModifiers[kActorVal_OblivionMax];	// 324
	float			unk444;							// 444
	float			unk448;							// 448
	float			unk44C;							// 44C
	UInt32			unk450[(0x570 - 0x450) >> 2];	// 450
	TESObjectREFR*	lastActivatedLoadDoor;			// 570 - most recently activated load door
	UInt32			unk574;							// 574
	UInt32			unk578;							// 578
	UInt32			unk57CState;					// 57C
	UInt32			unk580;							// 580
	UInt32			unk584;							// 584
	UInt8			isThirdPerson;					// 588
	UInt8			DisableFading;					// 589
	UInt8			unk58A;							// 58A
	UInt8			AlwaysRun;						// 58B
	UInt8			AutoMove;						// 58C
	UInt8			pad58D[3];						// 58D
	UInt32			HoursToSleep;					// 590
	UInt8			isSleeping;						// 594
	UInt8			pad594[3];
	float			FoV;							// 598
	float			unk59C;							// 59C
	float			unk5A0;							// 5A0
	float			unk5A4;							// 5A4
	UInt32			unk5A8;							// 5A8
	UInt32			unk5AC;							// 5AC
	Unk5B0*			unk5B0;							// 5B0 - freed when running SetInCharGen 0
	UInt8**			attributeBonuses;				// 5B4
	UInt16			unk5B8;							// 5B8
	UInt8			unk5BA;							// 5BA
	UInt8			unk5BB;							// 5BB
	UInt32			trainingSessionsUsed;			// 5BC reset on level-up
	UInt8			unk5C0;							// 5C0
	UInt8			pad5C0[3];
	TESObjectREFR*	ObjectToActivate;				// 5C4
	SkinInfo*		firstPersonSkinInfo;			// 5C8
	ActorAnimData*	firstPersonAnimData;			// 5CC
	NiNode*			firstPersonNiNode;				// 5D0
	float			firstPersonNiNodeWTranslateZ;	// 5D4
	UInt32			unk5D8;							// 5D8
	ActorAnimData*	defaultAnimData;				// 5DC
	UInt32			unk5E0;							// 5E0
	TESTopic*		unk5E4;							// 5E4
	UInt32			unk5E8;							// 5E8
	UInt32			unk5EC;							// 5EC
	UInt32			unk5F0;							// 5F0
	TESQuest*		activeQuest;					// 5F4
	UInt32			unk5F8;							// 5F8
	UInt32			unk5FC;							// 5FC
	UInt32			unk600;							// 600
	UInt32			unk604;							// 604
	UInt32			JailedState;					// 608
	UInt32			unk60C;							// 60C
	UInt8			unk610;							// 610
	UInt8			isAMurderer;					// 611
	UInt8			pad612[2];						// 612
	UInt32			AmountStolenSold;				// 614
	float			unk618;							// 618
	float			unk61C;							// 61C
	UInt32			unk620;							// 620
	MagicItem*		activeMagicItem;				// 624
	TESObjectBOOK*	book;							// 628
	UInt32			unk62C;							// 62C
	UInt32			unk630;							// 630
	UInt32			unk634;							// 634
	UInt32			unk638;							// 638
	UInt32			unk63C;							// 63C
	float			unk640;							// 640
	BirthSign*		birthSign;						// 644
	UInt32			unk648[(0x650 - 0x648) >> 2];	// 648
	TESClass*		wtfClass;						// 650 - this is not the player class! use OBLIVION_CAST(this, TESForm, TESNPC)->npcClass
	UInt32			unk654;							// 654
	UInt32			miscStats[kMiscStat_Max];		// 658
	AlchemyItem*	alchemyItem;					// 6E0
	UInt8			bVampireHasFed; 				// 6E4 returned by vtbl+260, set by vtbl+264
	UInt8			isInCharGen;					// 6E5
	UInt8			pad6E6[2];						// 6E6
	TESRegion*		currentRegion;					// 6E8
	UInt32			unk6EC;							// 6EC
	UInt32			unk6F0;							// 6F0
	UInt32			unk6F4;							// 6F4
	UInt32			unk6F8;							// 6F8
	UInt32			unk6FC;							// 6FC
	UInt32			unk700;							// 700
	UInt32			unk704;							// 704
	UInt32			unk708;							// 708
	UInt32			unk70C;							// 70C
	UInt32			TickCount;						// 710
	UInt32			unk714;							// 714
	UInt32			unk718;							// 718
	UInt8			isTravelPackage;				// 71C
	UInt8			isWakeUpPackage;				// 71D
	UInt8			pad71E[2];
	UInt32			unk720;							// 720
	UInt32			unk724;							// 724
	UInt32			unk728;							// 728
	UInt32			unk72C;							// 72C
	UInt32			unk730;							// 730
	float			gameDifficultyLevel;			// 734 ranges from -1 to 1
	UInt32			unk738;							// 738
	UInt32			unk73C;							// 73C
	UInt32			unk740;							// 740
	UInt32			unk744;							// 744
	UInt8			isFlyCam;						// 748
	UInt8			pad748[3];						// 749
	float			FlyCamRotZ;						// 74C
	float			FlyCamRotX;						// 750
	float			FlyCamPosX;						// 754
	float			FlyCamPosY;						// 758
	float			FlyCamPosZ;						// 75C
	UInt32			unk760[(0x7A4 - 0x760) >> 2];	// 760
	float			requiredSkillExp[21];			// 7A4 total amt of exp needed to increase each skill
	UInt32			unk7F8;							// 7F8
	float			unk7FC;							// 7FC
	float			unk800;							// 800
};
assert(sizeof(PlayerCharacter) == 0x804);

class BaseProcess {
public:
	enum {
		kMovementFlag_Sneaking = 0x00000400,	// overridden by kMovementFlag_Swimming
		kMovementFlag_Swimming = 0x00000800
	};

	virtual void	Destructor();
	virtual void	Copy(BaseProcess* SourceProcess);
	virtual UInt32	GetProcessLevel();	// 0 - high, 3 - low
	virtual void	Unk_03(Actor* Act, UInt32 Arg1);
	virtual void	ManagePackProcedure(Actor* Act);
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);
	virtual bool	Unk_06(UInt32 arg0, UInt32 arg1);
	virtual void	SetCurHour(float Hour);
	virtual void	Unk_08();
	virtual bool	Unk_09();
	virtual float	GetCurHour();
	virtual UInt32	GetCurPackedDate();
	virtual void	SetCurPackedDate(UInt32 arg0);
	virtual UInt32	GetCurDay();
	virtual UInt32	GetCurMonth();
	virtual UInt32	GetCurYear();
	virtual void	Unk_10(UInt32 arg0);
	virtual UInt32	Unk_11();
	virtual void	Unk_12(UInt32 arg0);
	virtual void	Unk_13();
	virtual UInt32	Unk_14();
	virtual void	Unk_15(UInt32 arg0);
	virtual void	Unk_16(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_17();
	virtual void	Unk_18(UInt32 arg0);
	virtual bool	Unk_19();
	virtual void	Unk_1A(UInt32 arg0);
	virtual bool	Unk_1B(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_1C(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual UInt32	Unk_1D(UInt32 arg0);
	virtual UInt32	Unk_1E(UInt32 arg0);
	virtual float	Unk_1F(UInt32 arg0);
	virtual void	Unk_20(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_21(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual bool	Unk_22();
	virtual void	Unk_23(UInt32 arg0);
	virtual void	Unk_24(UInt32 arg0);
	virtual void	Unk_25();
	virtual void	UpdateUnk088();
	virtual float	GetUnk088();
	virtual void	SetUnk088(float arg0);
	virtual void	Unk_29();
	virtual void*	SetDetected(Actor* detectedActor, UInt8 detectionState, bool hasLOS, SInt32 detectionLevel);
	virtual bool	Unk_2B();
	virtual void	Unk_2C(UInt32 arg0);

	virtual void	Unk_2C_1_2();	// added in 1.2 patch, all following virtuals are now shifted +1

	virtual void	Unk_2D(UInt32 arg0);
	virtual void	Unk_2E(UInt32 arg0);
	virtual bool	Unk_2F();
	virtual void	Unk_30(UInt32 arg0);
	virtual bool	Unk_31();
	virtual TESObjectREFR* GetUnk02C();
	virtual void	SetUnk02C(TESObjectREFR* obj);
	virtual UInt32	Unk_34();
	virtual void	Unk_35(UInt32 arg0);
	virtual void	Unk_36(UInt32 arg0);
	virtual UInt32	Unk_37();
	virtual void	Unk_38(UInt32 arg0);
	virtual UInt32	Unk_39(UInt32 arg0);
	virtual UInt32	Unk_3A(UInt32 arg0);
	virtual InventoryChanges::EntryData* GetEquippedWeaponData(bool arg0);
	virtual UInt32	Unk_3C(UInt32 arg0);
	virtual InventoryChanges::EntryData* GetEquippedAmmoData(bool arg0);
	virtual UInt32	Unk_3E();
	virtual void	Unk_3F(UInt32 arg0);
	virtual bool	Unk_40(UInt32 arg0, UInt32 arg1);
	virtual bool	Unk_41(UInt32 arg0);
	virtual bool	Unk_42(UInt32 arg0);
	virtual bool	Unk_43(UInt32 arg0);
	virtual bool	Unk_44(UInt32 arg0);
	virtual UInt32	Unk_45(UInt32 arg0);
	virtual UInt32	Unk_46(UInt32 arg0);
	virtual UInt32	Unk_47(UInt32 arg0);
	virtual UInt32	Unk_48(UInt32 arg0);
	virtual UInt32	Unk_49(UInt32 arg0);
	virtual UInt32	Unk_4A(UInt32 arg0);
	virtual UInt32	Unk_4B(UInt32 arg0);
	virtual UInt32	Unk_4C(UInt32 arg0);
	virtual bool	Unk_4D();
	virtual bool	Unk_4E();
	virtual UInt8	GetUnk084();
	virtual void					SetUnk084(UInt8 arg0);
	virtual bool					GetUnk01E();
	virtual void					SetUnk01E(UInt32 arg0);
	virtual void					Unk_53(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3);
	virtual void					SetUnk024(UInt32 arg);
	virtual void					Unk_55();
	virtual void					Unk_56();
	virtual void					Unk_57();
	virtual void					GetUnk028(float arg);
	virtual float					SetUnk028();
	virtual void					Unk_5A();
	virtual void					Unk_5B();
	virtual void					Unk_5C();
	virtual void					SetCurrentPackage(TESPackage* Package);
	virtual TESPackage::eProcedure	SetCurrentPackProcedure(TESPackage::eProcedure PackProcedure);
	virtual TESPackage::eProcedure	GetCurrentPackProcedure();
	virtual TESPackage*				GetCurrentPackage();	// returns MiddleHighProcess::pkg0C0 if not NULL, else BaseProcess::package
	virtual void					Unk_61(UInt32 arg0);			// marks ScriptEventList::kEvent_OnPackageDone
	virtual bhkCharacterProxy**		GetCharProxy(bhkCharacterProxy** characterProxy);	// increfs and returns the proxy (or sets to NULL)
	virtual void					Unk_63(void* obj);
	virtual void					Unk_64();
	virtual void					Unk_65();
	virtual void					Unk_66();
	virtual void					Unk_67();
	virtual void					Unk_68();
	virtual void					Unk_69();
	virtual void					Unk_6A();
	virtual void					Unk_6B();
	virtual void	Unk_6C();
	virtual void	Unk_6D();
	virtual void	Unk_6E();
	virtual void	Unk_6F();
	virtual void	Unk_70();
	virtual bool	GetLOS(UInt32 arg0, TESObjectREFR* target);	// arg0 unused
	virtual void	Unk_72();
	virtual void	Unk_73();
	virtual void	Unk_74();
	virtual void	Unk_75();
	virtual void	Unk_76();
	virtual void	Unk_77();
	virtual void	Unk_78();
	virtual void	Unk_79();
	virtual void	Unk_7A();
	virtual void	Unk_7B();
	virtual void	Unk_7C();
	virtual void	Unk_7D();
	virtual void	Unk_7E();
	virtual void	Unk_7F();
	virtual void	Unk_80();
	virtual void	Unk_81();
	virtual void	Unk_82();
	virtual UInt8	GetIsAlerted();
	virtual void	SetIsAlerted(UInt8 IsAlerted);
	virtual void	Unk_85();
	virtual void	Unk_86();
	virtual void	Unk_87();
	virtual void	Unk_88();
	virtual void	Unk_89();
	virtual void	Unk_8A();
	virtual void	Unk_8B();
	virtual void	Unk_8C();
	virtual void	Unk_8D();
	virtual void	Unk_8E();
	virtual void	Unk_8F();
	virtual void	Unk_90();
	virtual UInt8	GetUnk020();
	virtual void	SetUnk020(UInt8 arg);
	virtual void	Unk_93();
	virtual void	Unk_94();
	virtual void	Unk_95();
	virtual void	Unk_96();
	virtual void	Unk_97();
	virtual void	Unk_98();
	virtual void	Unk_99();
	virtual void	Unk_9A();
	virtual void	Unk_9B();
	virtual void	Unk_9C();
	virtual void	Unk_9D();
	virtual void	Unk_9E();
	virtual void	Unk_9F();
	virtual void	Unk_A0();
	virtual void	Unk_A1();
	virtual void	Unk_A2();
	virtual void	Unk_A3();
	virtual void	Unk_A4();
	virtual void	Unk_A5();
	virtual void	Unk_A6();
	virtual void	Unk_A7();
	virtual void	Unk_A8();
	virtual void	Unk_A9();
	virtual MagicItem*				GetQueuedMagicItem();	// returns MiddleHighProcess+144
	virtual void					Unk_AB();
	virtual void					Unk_AC();
	virtual void					Unk_AD();
	virtual void					Unk_AE();
	virtual UInt32					GetMovementFlags();
	virtual void					Unk_B0();
	virtual void					Unk_B1();
	virtual void					Unk_B2();
	virtual SInt16					GetCurrentAction();
	virtual BSAnimGroupSequence*	GetCurrentActionAnimSequence();
	virtual SInt16					SetCurrentAction(SInt16 action, BSAnimGroupSequence* sequence);
	virtual void					Unk_B6();
	virtual void					Unk_B7();
	virtual UInt8					GetKnockedState();
	virtual UInt8					SetKnockedState(UInt8 KnockedState);
	virtual void					Unk_BA();
	virtual void					Unk_BB();
	virtual void					KnockbackActor(Actor* target, float arg1, float arg2, float arg3, float arg4); // arg3 is a multiplier, arg4 appears to be base force to apply
	virtual void					Unk_BD();
	virtual UInt8					GetCombatMode();
	virtual UInt8					SetCombatMode(UInt8 CombatMode);
	virtual UInt8					GetWeaponOut();
	virtual UInt8					SetWeaponOut(UInt8 WeaponOut);
	virtual void					Unk_C2();
	virtual void*					Unk_C3();	// returns some pointer
	virtual void					Unk_C4();
	virtual void	Unk_C5();
	virtual void	SetUnk16C(UInt8 arg);
	virtual UInt8	GetUnk16C();
	virtual float	GetUnk0F8();
	virtual void	SetUnk0F8(float arg);
	virtual void	Unk_CA();
	virtual void	Unk_CB();
	virtual void	Unk_CC();
	virtual void	Unk_CD();
	virtual void	Unk_CE();
	virtual void	Unk_CF();
	virtual void	Unk_D0();
	virtual void	Unk_D1();
	virtual void	Unk_D2();
	virtual void	Unk_D3();
	virtual void	Unk_D4();
	virtual void	Unk_D5();
	virtual void	Unk_D6();
	virtual void	Unk_D7();
	virtual void	Unk_D8();
	virtual void	Unk_D9();
	virtual UInt8	GetSitSleepState();
	virtual void	Unk_DB();
	virtual void	Unk_DC();
	virtual TESObjectREFR* GetFurniture();
	virtual void	Unk_DE();
	virtual void	Unk_DF();
	virtual void	Unk_E0();
	virtual void	Unk_E1();
	virtual void	Unk_E2();
	virtual UInt8	GetUnk01C();
	virtual void	SetUnk01C(UInt8 arg);
	virtual UInt8	GetUnk180();
	virtual void	SetUnk180(UInt8 arg);
	virtual void	Unk_E7();
	virtual void	Unk_E8();
	virtual void	Unk_E9();
	virtual float	GetLightAmount(Actor* actor, UInt32 unk1);
	virtual void	Unk_EB();
	virtual void*	GetDetectionState(Actor* target);	// returns HighProcess::DetectionList::Data *
	virtual void	Unk_ED();
	virtual void	Unk_EE();
	virtual void	Unk_EF();
	virtual void	Unk_F0();
	virtual void	Unk_F1();
	virtual void	Unk_F2();
	virtual void	Unk_F3();
	virtual void	Unk_F4();
	virtual void	Unk_F5();
	virtual void	Unk_F6();
	virtual void	Unk_F7();
	virtual void	Unk_F8();
	virtual void	Unk_F9();
	virtual void	Unk_FA();
	virtual void	Unk_FB();
	virtual void	Unk_FC();
	virtual void	Unk_FD();
	virtual void	Unk_FE();
	virtual void	Unk_FF();
	virtual void	Unk_100();
	virtual void	Unk_101();
	virtual void	CreatePath();
	virtual void	GetCurrentPath();
	virtual void	Unk_104();
	virtual void	Unk_105();
	virtual void	Unk_106();
	virtual void	Unk_107();
	virtual void	Unk_108();
	virtual void	Unk_109();
	virtual void	Unk_10A();
	virtual void	Unk_10B();
	virtual void	Unk_10C();
	virtual void	Unk_10D();
	virtual void	Unk_10E();
	virtual void	Unk_10F();
	virtual void	Unk_110();
	virtual void	Unk_111();
	virtual void	Unk_112();
	virtual void	Unk_113();
	virtual void	Unk_114();
	virtual void	Unk_115();
	virtual void	Unk_116();
	virtual void	Unk_117();
	virtual void	Unk_118();
	virtual void	Unk_119();
	virtual void	Unk_11A();
	virtual void	Unk_11B();
	virtual void	Unk_11C();
	virtual void	Unk_11D();
	virtual void	Unk_11E();
	virtual void	Unk_11F();
	virtual void	Unk_120();
	virtual void	Unk_121();
	virtual void	Unk_122();
	virtual void	Unk_123();
	virtual void	Unk_124();
	virtual void	Unk_125();
	virtual void	Unk_126();
	virtual void	Unk_127();
	virtual void	Unk_128();
	virtual void	Unk_129();
	virtual void	Unk_12A();
	virtual void	Unk_12B();
	virtual void	Unk_12C();
	virtual void	Unk_12D();
	virtual void	Unk_12E();
	virtual void	Unk_12F();
	virtual void	Unk_130();
	virtual void	Unk_131();
	virtual void	Unk_132();
	virtual void	Unk_133();
	virtual const char* Unk_134();
	virtual void	Unk_135();
	virtual void	Unk_136();
	virtual void	Unk_137();
	virtual void	Unk_138();
	virtual void	Unk_139();
	virtual void	Unk_13A();
	virtual float	GetUnk08C();
	virtual void	SetUnk08C(float arg);
	virtual void	Unk_13D();
	virtual void	Unk_13E();
	virtual void	Unk_13F();
	virtual void	Unk_140();

	TESPackage::eProcedure	editorPackProcedure;	// 004
	TESPackage*				editorPackage;			// 008
};
assert(sizeof(BaseProcess) == 0x0C);

class LowProcess : public BaseProcess {
public:
	virtual void	Unk_141();
	virtual void	Unk_142();
	virtual void	Unk_143();
	virtual void	Unk_144();
	virtual void	Alarm(Actor* Act);
	virtual void	Unk_146();
	virtual void	Unk_147();
	virtual void	Unk_148();
	virtual void	Unk_149();
	virtual void	Unk_14A();
	virtual void	Unk_14B();
	virtual void	Unk_14C();
	virtual void	Unk_14D();
	virtual void	Unk_14E();
	virtual void	Unk_14F();
	virtual void	Unk_150();
	virtual void	Unk_151();
	virtual void	Unk_152();
	virtual void	Unk_153();
	virtual void	Unk_154();
	virtual void	Unk_155();
	virtual void	Unk_156();
	virtual UInt8	MountHorse(Actor* Act);				// 560
	virtual UInt8	DismountHorse(Actor* Act);			// 564
	virtual void	Unk_159();

	float			unk00C;				// 00C - initialized to -1
	float			unk010;				// 010
	float			curHour;			// 014 - initialized to -1
	UInt32			curPackedDate;		// 018 - (year << 13) | (month << 9) | day
	UInt8			unk01C;				// 01C
	UInt8			unk01D;				// 01D
	UInt8			unk01E;				// 01E
	UInt8			IsAlerted;			// 01F
	UInt8			unk020;				// 020
	UInt8			pad021[3];			// 021
	TESForm*		usedItem;			// 024 for idles like reading book, making potions, etc
	float			unk028;				// 028
	Actor*			Follow;				// 02C
	TESObjectREFR*	unk030;	// 030 seen XMarkerHeading refs here
	void*			pathing;			// 034
	UInt32			unk038;				// 038
	UInt32			unk03C;				// 03C
	UInt32			unk040;				// 040
	UInt32			unk044;				// 044
	UInt32			unk048;				// 048
	UInt32			unk04C;				// 04C
	UInt32			unk050;				// 050
	UInt32			unk054;				// 054
	UInt32			unk058;				// 058
	UInt32			unk05C;				// 05C
	UInt32			unk060;				// 060
	UInt32			unk064;				// 064
	UInt32			unk068;				// 068
	UInt32			unk06C;				// 06C
	ActorValues		avDamageModifiers;	// 070
	UInt8			unk084;				// 084
	UInt8			pad085[3];			// 085
	float			unk088;				// 088 - counter in seconds
	float			unk08C;				// 08C
};
assert(sizeof(LowProcess) == 0x90);

class MiddleLowProcess : public LowProcess {
public:
	virtual void	Unk_15A();

	UInt32			unk090;				// 090
	ActorValues		maxAVModifiers;		// 094
};
assert(sizeof(MiddleLowProcess) == 0xA8);

class MiddleHighProcess : public MiddleLowProcess {
public:
	virtual void	Unk_15B();
	virtual void	Unk_15C();
	virtual void	Unk_15D();
	virtual void	Unk_15E();
	virtual void	Unk_15F();
	virtual void	Dialogue(Actor* Act);
	virtual void	RemoveWornItems(Actor* Act, UInt8 Arg2, int Arg3);
	virtual void	Travel(Actor* Act, UInt8 Arg2, float Arg3, int Arg4 = 0);
	virtual void	Unk_163();
	virtual void	Unk_164();

	struct Unk128 {
		UInt32	unk0;	// 0
		UInt32	unk4;	// 4
		UInt32	unk8;	// 8
		UInt16	unkC;	// C
		UInt8	unkE;	// E
		UInt8	padF;	// F
	};

	struct EffectListNode {
		ActiveEffect*	effect;		// 0
		EffectListNode* next;		// 4
	};

	UInt32				unk0A8;		// 0A8
	UInt32				unk0AC;		// 0AC
	UInt32				unk0B0;		// 0B0
	UInt32				unk0B4;		// 0B4
	UInt32				unk0B8;		// 0B8
	float				unk0BC;		// 0BC
	TESPackage*			currentPackage;	// 0C0 if null, editorPackage applies
	UInt32				unk0C4;		// 0C4
	UInt8				unk0C8;		// 0C8
	UInt8				pad0C9[3];	// 0C9
	TESPackage::eProcedure	currentPackProcedure; // 0CC
	UInt8				unk0D0;		// 0D0
	UInt8				pad0D0[15];	// 0D1 - never initialized
	UInt32				unk0E0;		// 0E0
	InventoryChanges::EntryData* equippedWeaponData;	// 0E4
	InventoryChanges::EntryData* equippedLightData;	// 0E8
	InventoryChanges::EntryData* equippedAmmoData;		// 0EC
	InventoryChanges::EntryData* equippedShieldData;   // 0F0
	UInt8				unk0F4;		// 0F4
	UInt8				unk0F5;		// 0F5
	UInt8				pad0F6[2];	// 0F6
	float				unk0F8;		// 0F8
	NiNode*				WeaponNode;		// 0FC
	NiNode*				TorchNode;		// 100
	NiNode*				LForearmTwistNode;	// 104
	NiNode*				SideWeaponNode;	// 108
	NiNode*				QuiverNode;		// 10C
	NiNode*				unk110;		// 110
	UInt8				CombatMode;	// 114
	UInt8				WeaponState;// 115
	UInt8				pad116[2];	// 116
	bhkCharacterProxy*	charProxy;	// 118 - seen bhkCharacterProxy
	UInt8				KnockedState;	// 11C
	UInt8				SitSleepState;	// 11D
	UInt8				pad11E;		// 11E
	UInt8				pad11F;		// 11F
	TESObjectREFR*		Furniture;	// 120
	UInt8				unk124;		// 124 - init'd to 0x7F
	Unk128				unk128;		// 128
	UInt16				unk138;		// 138
	UInt8				pad13A[2];	// 13A
	UInt32				unk13C;		// 13C
	UInt32				unk140;		// 140
	MagicItem*			queuedMagicItem;	// 144 set before calling sub_69AF30 after Addspell cmd, unset upon return
	UInt32				unk148;		// 148
	UInt8				unk14C;		// 14C looks like true if casting, or possibly a casting state
	UInt8				pad14D[3];	// 14D
	UInt32				unk150;		// 150
	float				actorAlpha;	// 154 valid values 0-1
	float				unk158;		// 158
	NiExtraData*		unk15C;		// 15C seen BSFaceGenAnimationData*, reset when modifying character face
	UInt8				unk160;		// 160
	UInt8				unk161;		// 161
	UInt8				pad162[2];	// 162
	UInt32				unk164;		// 164
	UInt8				unk168;		// 168
	UInt8				unk169;		// 169
	UInt8				unk16A;		// 16A
	UInt8				unk16B;		// 16B
	UInt8				unk16C;		// 16C
	UInt8				unk16D;		// 16D
	UInt8				pad16E[2];	// 16E
	UInt32				unk170;		// 170
	EffectListNode*		effectList;	// 174
	UInt32				unk178;		// 178
	ActorAnimData*		animData;	// 17C
	UInt8				unk180;		// 180
	UInt8				pad181[3];	// 181
	NiObject*			unk184;	// 184 - seen BSShaderPPLightingProperty
	BSBound*			boundingBox;	// 188
};
assert(sizeof(MiddleHighProcess) == 0x18C);

class HighProcess : public MiddleHighProcess {
public:
	enum {
		kActionType_Default = 0,
		kActionType_Action,
		kActionType_Script,
		kActionType_Combat,
		kActionType_Dialog,
		kActionType_Max
	};

	enum {
		kDetectionState_Lost = 0,
		kDetectionState_Unseen,
		kDetectionState_Noticed,
		kDetectionState_Seen,
		kDetectionState_Max
	};

	struct DetectionList {
		struct Data {
			Actor*			actor;
			UInt8			detectionState;
			UInt8			pad04[3];
			UInt8			hasLOS;
			UInt8			pad08[3];
			SInt32			detectionLevel;
		};

		Data* data;
		DetectionList* next;

		Data* Info() const { return data; }
		DetectionList* Next() const { return next; }
	};

	// this appears to be a common linked list class
	struct Node190 {
		void* data;
		Node190* next;
	};

	struct Unk1BC {
		UInt32	unk0;
		UInt32	unk4;
		UInt32	unk8;
		UInt32	unkC;
	};

	struct Unk20C {
		UInt32	unk0;
		UInt32	unk4;
		UInt32	unk8;
	};

	struct Unk27C {
		UInt32	unk0;
		UInt32	unk4;
		UInt32	unk8;
	};

	enum {
		kAction_None = -1,
		kAction_EquipWeapon,
		kAction_UnequipWeapon,
		kAction_Attack,
		kAction_AttackFollowThrough,
		kAction_AttackBow,
		kAction_AttackBowArrowAttached,
		kAction_Block,
		kAction_Recoil,
		kAction_Stagger,
		kAction_Dodge,
		kAction_LowerBodyAnim,
		kAction_SpecialIdle,
		kAction_ScriptAnimation,
	};

	enum {
		kMovement_Forward = 0x0001,
		kMovement_Backward = 0x0002,
		kMovement_Left = 0x0004,
		kMovement_Right = 0x0008,
		kMovement_TurnLeft = 0x0010,
		kMovement_TurnRight = 0x0020,
		kMovement_Walk = 0x0100,
		kMovement_Run = 0x0200,
		kMovement_Sneak = 0x0400,	// overridden by kMovementFlag_Swimming
		kMovement_Swim = 0x0800,
		kMovement_Jump = 0x1000, //Jump and above appear not to be used.
		kMovement_Fly = 0x2000,
		kMovement_Fall = 0x4000,
		kMovement_Slide = 0x8000,
	};
	
	void					PlaySoundITMTorchHeldLP(Actor* Act) { ThisCall(0x00633540, this, Act); }
	void					StopSoundITMTorchHeldLP() { ThisCall(0x006334D0, this, 1); }

	DetectionList*			detectionList;	// 18C
	Node190					unk190;		// 190
	UInt32					unk198;		// 198
	float					unk19C;		// 19C - idle chatter comment timer
	UInt8					unk1A0;		// 1A0
	UInt8					pad1A1[3];	// 1A1
	UInt32					unk1A4;		// 1A4
	UInt32					unk1A8;		// 1A8
	UInt32					unk1AC;		// 1AC
	UInt32					unk1B0;		// 1B0 - uninitialized
	UInt32					unk1B4;		// 1B4 - uninitialized
	UInt32					unk1B8;		// 1B8
	Unk1BC					unk1BC;		// 1BC
	UInt32					unk1CC;		// 1CC - uninitialized
	UInt8					unk1D0;		// 1D0
	UInt8					unk1D1;		// 1D1
	UInt32					unk1D4;		// 1D4
	UInt32					unk1D8;		// 1D8
	UInt32					unk1DC;		// 1DC
	UInt32					unk1E0;		// 1E0
	UInt8					unk1E4;		// 1E4
	UInt8					pad1E5[3];	// 1E5
	UInt32					unk1E8;		// 1E8
	void*					LODController;		// 1EC NiBSBoneLODController
	UInt32					unk1F0;								// 1F0
	SInt16					currentAction;		// 1F4
	UInt8					pad1F6[2];			// 1F6
	BSAnimGroupSequence*	currentActionAnim;	// 1F8
	UInt16					movementFlags;						// 1FC
	UInt8	pad1FE[2];	// 1FE
	UInt32	unk200;		// 200
	float	unk204;		// 204
	UInt16	unk208;		// 208
	UInt8	pad20A[2];	// 20A
	Unk20C	unk20C;		// 20C
	UInt32	unk218;		// 218
	float	unk21C;		// 21C
	UInt32	unk220;		// 220
	UInt32  lightSound; // 224 TESGameSound* (ITMTorchHeldLP sound). It is set/removed when equipping/unequipping torch.
	UInt8	unk228;		// 228
	UInt8	pad229[3];	// 229
	float	unk22C;		// 22C
	float	unk230;		// 230 - initialized to ((rand() % 5000) * .001) + 10
	UInt32	unk234;		// 234 - not initialized
	float	swimBreath;	// 238 - initialized to 0x41A00000
	UInt8	unk23C;		// 23C
	UInt8	unk23D[3];	// 23D
	UInt32	unk240;		// 240
	UInt8	unk244;		// 244
	UInt8	unk245[3];	// 245
	float	unk248;		// 248
	UInt8	unk24C;		// 24C
	UInt8	pad24D[3];	// 24D
	UInt32	unk250;		// 250
	UInt32	unk254;		// 254
	UInt32	unk258;		// 258
	UInt8	unk25C;		// 25C
	UInt8	unk25D;		// 25D
	UInt8	pad25E[2];	// 25E
	float	unk260;		// 260
	UInt32	unk264;		// 264
	NiObject* unk268;	// 268 - decref'able pointer
	float	unk26C;		// 26C
	UInt32	unk270;		// 270
	UInt32	unk274;		// 274
	UInt8	unk278;		// 278
	UInt8	pad279[3];	// 279
	Unk27C	unk27C;		// 27C
	UInt32	unk288;		// 288
	UInt32	unk28C;		// 28C
	UInt8	unk290;		// 290
	UInt8	pad291[3];	// 291
	float	unk294;		// 294
	UInt32	unk298;		// 298
	UInt32	unk29C;		// 29C
	UInt32	unk2A0;		// 2A0
	UInt32	unk2A4;		// 2A4
	UInt8	unk2A8;		// 2A8
	UInt8	unk2A9;		// 2A9
	UInt8	pad2AA[2];	// 2AA
	float	unk2AC;		// 2AC
	float	unk2B0;		// 2B0
	UInt32	unk2B4;		// 2B4
	UInt8	unk2B8;		// 2B8
	UInt8	unk2B9;		// 2B9
	UInt8	pad2BA[2];	// 2BA
	UInt32	unk2BC;		// 2BC
	float	unk2C0;		// 2C0
	TESObjectREFR*	unk2C4;	// 2C4
	TESObjectREFR*	actionTarget[kActionType_Max];	// 2C8
	UInt8			actionActive[kActionType_Max];		// 2DC - true if the specified action is running
	UInt8			pad2E1[3];	// 2E1
	TESObjectREFR*	unk2E4;	// 2E4
	UInt8			unk2E8;		// 2E8
	UInt8			pad2E9[3];	// 2E9
};
assert(sizeof(HighProcess) == 0x2EC);

class SkinInfo {
public:
	NiNode*			Bip01Node;				// 000
	UInt32			unk004;
	NiNode*			HeadNode;				// 008
	UInt32			unk00C;
	NiNode*			Finger1Node;			// 010
	UInt32			unk014;
	NiNode*			LFinger1Node;			// 018
	UInt32			unk01C;
	NiNode*			WeaponNode;				// 020
	UInt32			unk024;
	NiNode*			BackWeaponNode;			// 028
	UInt32			unk02C;
	NiNode*			SideWeaponNode;			// 030
	UInt32			unk034;
	NiNode*			QuiverNode;				// 038
	UInt32			unk03C;
	NiNode*			LForearmTwistNode;		// 040
	UInt32			unk044;
	NiNode*			TorchNode;				// 048
	UInt32			unk04C;
	UInt32			unk050;
	Actor*			Actor054;				// 054
	UInt32			unk058;
	TESForm*		unk05C;
	TESModel*		unk060;
	NiNode*			unk064;
	UInt32			unk068;
	TESForm*		UpperBodyForm;			// 06C
	TESModel*		UpperBodyModel;			// 070
	NiNode*			UpperBodyObject;		// 074
	UInt32			unk078;
	TESForm*		LowerBodyForm;			// 07C
	TESModel*		LowerBodyModel;			// 080
	NiNode*			LowerBodyObject;		// 084
	UInt32			unk088;
	TESForm*		HandForm;				// 08C
	TESModel*		HandModel;				// 090
	NiNode*			HandObject;				// 094
	UInt32			unk098;
	TESForm*		FootForm;				// 09C
	TESModel*		FootModel;				// 0A0
	NiNode*			FootObject;				// 0A4
	UInt32			unk0A8;
	UInt32			unk0AC;
	UInt32			unk0B0;
	NiNode*			unk0B4;
	UInt32			unk0B8;
	UInt32			unk0BC;
	UInt32			unk0C0;
	NiNode*			unk0C4;
	UInt32			unk0C8;
	UInt32			unk0CC;
	UInt32			unk0D0;
	NiNode*			unk0D4;
	UInt32			unk0D8;
	TESObjectWEAP*	WeaponForm;				// 0DC
	TESModel*		WeaponModel;			// 0E0
	NiNode*			WeaponObject;			// 0E4
	UInt32			unk0E8;
	TESForm*		unk0EC;
	TESModel*		unk0F0;
	NiNode*			unk0F4;
	UInt32			unk0F8;
	TESForm*		unk0FC;
	TESModel*		unk100;
	NiNode*			unk104;
	UInt32			unk108;
	TESForm*		AmmoForm;				// 10C
	TESModel*		AmmoModel;				// 110
	NiNode*			AmmoObject;				// 114
	UInt32			unk118;
	TESObjectARMO*	ShieldForm;				// 11C
	TESModel*		ShieldModel;			// 120
	NiNode*			ShieldObject;			// 124
	UInt32			unk128;
	TESObjectLIGH*	LightForm;				// 12C
	TESModel*		LightModel;				// 130
	NiNode*			LightObject;			// 134
	UInt32			unk138;
	UInt32			unk13C;
	UInt32			unk140;
	UInt32			unk144;
	UInt32			unk148;
	UInt32			unk14C;
	Actor*			Actor150;				// 150
};
assert(sizeof(SkinInfo) == 0x154);

class AnimSequenceBase {
public:
	virtual void					Destructor(UInt8 Arg);
	virtual void					AddAnimGroupSequence(BSAnimGroupSequence* AnimGroupSequence);
	virtual void					Unk_02();
	virtual UInt8					IsSingle();
	virtual BSAnimGroupSequence*	GetAnimGroupSequence(int Index); // Index is not used if Single (returns the anim); Index = -1 returns a random anim in the NiTList<BSAnimGroupSequence>* for Multiple
	virtual void					Unk_05();
};
assert(sizeof(AnimSequenceBase) == 0x004);

class AnimSequenceSingle : public AnimSequenceBase {
public:
	BSAnimGroupSequence* Anim;	// 04
};
assert(sizeof(AnimSequenceSingle) == 0x008);

class AnimSequenceMultiple : public AnimSequenceBase {
public:
	NiTList<BSAnimGroupSequence>* Anims;	// 04
};
assert(sizeof(AnimSequenceMultiple) == 0x008);

class ActorAnimData {
public:
	void						QueueIdle(TESIdleForm* Idle, Actor* Act, UInt32 Flags) { ThisCall(0x00477DB0, this, Idle, Act, Flags, 3); }

	UInt32						unk00;					//00 no virtual table
	NiNode*						RootNode;				//04 seen BSFadeNode for 3rd Person, NiNode for 1st
	NiNode*						AccumNode;				//08
	UInt32						unk0C[6];				//0C
	NiNode*						nBip01;					//24
	NiNode*						nLForearm;				//28
	NiNode*						nTorch;					//2C
	NiNode*						nWeapon;				//30
	NiNode*						nHead;					//34
	UInt32						unk38;					//38
	UInt16						animsMapKey[5];			//3C
	UInt16						unk44;					//44
	int							unk48State[5];			//48
	UInt32						unk4C[15];				//4C
	NiControllerManager*		manager;				//98
	NiTMap<UInt32, AnimSequenceBase>*	animsMap;				//9C
	BSAnimGroupSequence*		animSequences[5];		//A0
	ModelKF*					modelB4;				//B4
	ModelKF*					modelB8;				//B8
	float						unkBC;					//BC
	float						unkC0;					//C0
	float						unkC4;					//C4
	UInt32						unkC8[3];				//C8
	UInt32						unkD4;					//D4
	void*						unkD8;					//D8 looks like struct with idle anim transform data
};
assert(sizeof(ActorAnimData) == 0xDC);

class TESAnimGroup : public NiRefObject {
public:
	enum {
		kAnimGroup_Idle = 0,
		kAnimGroup_DynamicIdle,
		kAnimGroup_SpecialIdle,
		kAnimGroup_Forward,
		kAnimGroup_Backward,
		kAnimGroup_Left,
		kAnimGroup_Right,
		kAnimGroup_FastForward,
		kAnimGroup_FastBackward,
		kAnimGroup_FastLeft,
		kAnimGroup_FastRight,
		kAnimGroup_DodgeForward,
		kAnimGroup_DodgeBack,
		kAnimGroup_DodgeLeft,
		kAnimGroup_DodgeRight,
		kAnimGroup_TurnLeft,
		kAnimGroup_TurnRight,
		kAnimGroup_Equip,
		kAnimGroup_Unequip,
		kAnimGroup_AttackBow,
		kAnimGroup_AttackLeft,
		kAnimGroup_AttackRight,
		kAnimGroup_AttackPower,
		kAnimGroup_AttackForwardPower,
		kAnimGroup_AttackBackPower,
		kAnimGroup_AttackLeftPower,
		kAnimGroup_AttackRightPower,
		kAnimGroup_BlockIdle,
		kAnimGroup_BlockHit,
		kAnimGroup_BlockAttack,
		kAnimGroup_Recoil,
		kAnimGroup_Stagger,
		kAnimGroup_Death,
		kAnimGroup_TorchIdle,
		kAnimGroup_CastSelf,
		kAnimGroup_CastTouch,
		kAnimGroup_CastTarget,
		kAnimGroup_CastSelfAlt,
		kAnimGroup_CastTouchAlt,
		kAnimGroup_CastTargetAlt,
		kAnimGroup_JumpStart,
		kAnimGroup_JumpLoop,
		kAnimGroup_JumpLand,
		kAnimGroup_Max,
	};

	UInt8		animGroup;		//008 This value is used with the animType (as UInt16) as key for the ActorAnimData NiTPointerMap<AnimSequenceBase>*
	UInt8		animType;		//009
	UInt8		animOR;			//00A Oblivion doesn't use this. Used by Oblivion Reloaded if installed.
	UInt8		pad008;			//00B
	UInt32		numFrames;		//00C count of group frames (Start, Detach, Attack, End, etc)
	float**		frameData;		//010 pointer to float array of group frame times (size numFrames)
	UInt32		unk014;			//014
	UInt32		unk018;			//018
	UInt32		unk01C;			//01C
	UInt8		unk020;			//020
	UInt8		unk021;
	UInt8		pad022[2];
	UInt32		unk024;			//024
	void*		unk028;			//028
};
assert(sizeof(TESAnimGroup) == 0x02C);

class SkyObject {
public:
	virtual NiNode* GetObjectNode();						
	virtual void	Initialize(UInt32 u1);			
	virtual void	func_03(UInt32 u1, UInt32 u2);	

	NiNode*			RootNode;						// 04	
};
assert(sizeof(SkyObject) == 0x008);

class Sun : public SkyObject {
public:
	NiBillboardNode*	SunBillboard;			// 08
	NiBillboardNode*	SunGlareBillboard;		// 0C
	NiTriShape*			SunGeometry;			// 10
	NiTriShape*			SunGlareGeometry;		// 14
	NiTArray<NiPick*>*	SunPickList;			// 18 NiPick::Record
	NiDirectionalLight* SunDirLight;			// 1C
	float				unk20;					// 20
	UInt8				unk24;					// 24
	UInt8				pad25[3];				// 25
};
assert(sizeof(Sun) == 0x028);

class Atmosphere : public SkyObject {
public:
	NiAVObject*		Mesh;					// 08
	BSFogProperty*	fogProperty;			// 0C
	UInt32			unk10;					// 10
	NiNode*			Quad;					// 14
	UInt8			unk18;					// 18
	UInt8			pad18[3];

};
assert(sizeof(Atmosphere) == 0x01C);

class Stars : public SkyObject {
public:
	UInt32			unk08;					// 08
	float			unk0C;					// 0C
};
assert(sizeof(Stars) == 0x010);

class Clouds : public SkyObject {
public:
	UInt32			unk08;					// 08
	UInt32			unk0C;					// 0C
	UInt32			unk10;					// 10
	UInt32			unk14;					// 14
};
assert(sizeof(Clouds) == 0x018);

class Moon : public SkyObject {
public:
	NiNode*			MoonNode;				// 08
	NiNode*			ShadowNode;				// 0C
	NiTriShape*		MoonMesh;				// 10
	NiTriShape*		ShadowMesh;				// 14
	char*			texture_full;			// 18
	UInt32			unk1C;					// 1C
	char*			texture_three_wan;		// 20
	UInt32			unk24;					// 24
	char*			texture_half_wan;		// 28
	UInt32			unk2C;					// 2C
	char*			texture_one_wan;		// 30
	UInt32			unk34;					// 34
	UInt32			unk38;					// 38
	UInt32			unk3C;					// 3C
	char*			texture_one_wax;		// 40
	UInt32			unk44;					// 44
	char*			texture_half_wax;		// 48
	UInt32			unk4C;					// 4C
	char*			texture_three_wax;		// 50
	UInt32			unk54;					// 54
	float			unk58;					// 58
	float			unk5C;					// 5C
	float			unk60;					// 60
	float			unk64;					// 64
	float			unk68;					// 68
	UInt32			unk6C;					// 6C
	UInt32			unk70;					// 70
	float			unk74;					// 74
	float			unk78;					// 78
};
assert(sizeof(Moon) == 0x07C);

class Precipitation {
public:
	void**			_vtbl;					// 00
	UInt32			unk04;					// 04
	UInt32			unk08;					// 08
	UInt32			unk0C;					// 0C
	float			unk10;					// 10
	UInt32			unk14;					// 14
};
assert(sizeof(Precipitation) == 0x018);

class Sky {
public:
	void ForceWeather(TESWeather* Weather) { ThisCall(0x00542260, this, Weather, 0); }

	void**			_vtbl;							// 000
	NiNode*			nodeSkyRoot;					// 004
	NiNode*			nodeMoonsRoot;					// 008
	TESClimate*		firstClimate;					// 00C
	TESWeather*		firstWeather;					// 010
	TESWeather*		secondWeather;					// 014 Previous weather when in transition
	TESWeather*		weather018;						// 018
	TESWeather*		weatherOverride;				// 01C
	Atmosphere*		atmosphere;						// 020
	Stars*			stars;							// 024
	Sun*			sun;							// 028
	Clouds*			clouds;							// 02C
	Moon*			masserMoon;						// 030
	Moon*			secundaMoon;					// 034
	Precipitation*	precipitation;					// 038
	UInt32			unk03C[(0x0B4 - 0x03C) >> 2];	// 03C
	float			unk0B4;							// 0B4
	float			unk0B8;							// 0B8
	float			unk0BC;							// 0BC
	float			windSpeed;						// 0C0
	float			unk0C4;							// 0C4
	float			unk0C8;							// 0C8
	float			unk0CC;							// 0CC
	float			unk0D0;							// 0D0
	float			unk0D4;							// 0D4
	float			weatherPercent;					// 0D8
	UInt32			unk0DC;							// 0DC
	UInt32			unk0E0;							// 0E0
	float			unk0E4;							// 0E4
	UInt32			unk0E8;							// 0E8
	UInt32			unk0EC;							// 0EC
	float			unk0F0;							// 0F0
	float			unk0F4;							// 0F4
	UInt32			unk0F8;							// 0F8
	UInt32			Flags0FC;						// 0FC
	UInt8			unk100;							// 100
	UInt8			unk101[3];						// 101
};
assert(sizeof(Sky) == 0x104);

class GridArray {
public:
	virtual void Fn_00();
	virtual void Fn_01();
	virtual void Fn_02();
	virtual void Fn_03();
	virtual void Fn_04();
	virtual void Fn_05();
	virtual void Fn_06();
	virtual void Fn_07();
	virtual void Fn_08();
	virtual void Fn_09();
};
assert(sizeof(GridArray) == 0x004);

class GridDistantArray : public GridArray {
public:
	struct DistantGridEntry {
		UInt32			unk00;
		UInt32			unk04;
		UInt32			unk08;
		UInt32			unk0C;
	};

	UInt32				worldX;		// 04
	UInt32				worldY;		// 08
	UInt32				size;		// 0C grid is size^2, size = uGridsToLoadValue + 2 * uGridDistantCount
	DistantGridEntry*	grid;		// 10 dynamically alloc'ed array of GridEntry[size^2]
};
assert(sizeof(GridDistantArray) == 0x014);

class GridCellArray : public GridArray {
public:
	class CellInfo {
	public:
		WaterPlaneData* waterData;
		NiNode* niNode;
		// ...
	};

	class GridEntry {
	public:
		TESObjectCELL* cell;
		CellInfo* info;
	};

	TESObjectCELL*		GetCell(UInt32 x, UInt32 y) { return ((GridEntry*)ThisCall(0x00482150, this, x, y))->cell; }

	UInt32				worldX;		// 04 worldspace x coordinate of cell at center of grid (player's cell)
	UInt32				worldY;		// 08 worldspace y
	UInt32				size;		// 0C grid is size^2, size = uGridsToLoad
	GridEntry*			grid;		// 10 dynamically alloc'ed array of GridEntry[size^2]
	float				posX;		// 14 4096*worldX (exterior cells are 4096 square units)
	float				posY;		// 18 4096*worldY
	float				unk1C;		// 1C
	UInt8				unk20;		// 20
	UInt8				pad20[3];
	BSRenderedTexture*	canopyShadowMap;		// 24
};
assert(sizeof(GridCellArray) == 0x028);

class TES {
public:
	virtual void Unk_00(UInt32 arg0, UInt32 arg1, UInt32 arg2, UInt32 arg3, TESWorldSpace* worldSpace);

	struct Unk8C {
		TESNPC* npc;
		UInt32	unk4;	// size?
	};
	
	void				PurgeCells() { ThisCall(0x00442630, this, 1, 0); ThisCall(0x0043FC20, this, 0); }

	GridDistantArray*	gridDistantArray;		// 04
	GridCellArray*		gridCellArray;			// 08
	NiNode*				ObjectLODRoot;			// 0C
	NiNode*				LODRoot;				// 10
	BSTempNodeManager*	tempNodeManager;		// 14
	NiDirectionalLight* niDirectionalLight;		// 18
	BSFogProperty*		fogProperty;			// 1C
	int					extXCoord;				// 20
	int					extYCoord;				// 24
	int					unk28;					// 28
	int					unk2C;					// 2C
	TESObjectCELL*		currentExteriorCell;	// 30
	TESObjectCELL*		currentInteriorCell;	// 34
	TESObjectCELL**		interiorCellBufferArray;// 38
	TESObjectCELL**		exteriorCellBufferArray;// 3C
	UInt32				unk40;					// 40
	UInt32				unk44;					// 44
	UInt32				unk48;					// 48 seen 0x7FFFFFFF; seen caching unk20 in editor
	UInt32				unk4C;					// 4C seen 0x7FFFFFFF; seen caching unk24 in editor
	UInt8				unk50;					// 50
	UInt8				unk51;					// 51
	UInt8				unk52;					// 52
	UInt8				CellBorders;			// 53
	WaterSurfaceManager* waterSurfaceManager;	// 54
	WaterPlaneData*		waterNodeData;			// 58
	Sky*				sky;					// 5C
	UInt32				unk60;					// 60
	UInt32				unk64;					// 64
	UInt32				unk68;					// 68
	float				unk6C;					// 6C
	float				unk70;					// 70
	TESWorldSpace*		currentWorldSpace;		// 74
	UInt32				unk78[5];				// 78
	TList<Unk8C>		list8C;					// 8C
	NiSourceTexture*	bloodDecals[3];			// 94 blood.dds, lichblood.dds, whillothewispblood.dds
	TList<void*>		listA0;					// A0 data is some struct containing NiNode*
	UInt8				unkA8;					// A8
	UInt8				unkA9;					// A9
	UInt8				padA8[2];
};
assert(sizeof(TES) == 0x0AC);

class TESGameSound {
public:
	enum {
		kType_Voice = 1 << 2,
		kType_Footstep = 1 << 3,
	};

	UInt8			typeFlags;	// 00	for calculating volume based on OSSoundGlobals::foot/voice/effectVolume
	UInt8			unk01;
	UInt8			unk02[2];
	UInt32			unk04[2];	// 04
	UInt32			hashKey;	// 0C
	UInt32			unk10[4];	// 10
	float			x;			// 20
	float			y;			// 24
	float			z;			// 28
	UInt32			unk2C[4];	// 2C
	float			unk3C;		// 3C
	UInt32			unk40[3];	// 40
	const char*		name;		// 4C
	UInt32			unk50;		// 50
	UInt32			unk54;		// 54
};
assert(sizeof(TESGameSound) == 0x058);

class BSAnimGroupSequence : public NiControllerSequence {
public:
	TESAnimGroup*	animGroup;	//068
};
assert(sizeof(BSAnimGroupSequence) == 0x06C);

class Tile {
public:
	enum TileValue {
		//...

		kTileValue_visible = 0x00000FA1,
		kTileValue_class,
		kTileValue_listclip,
		kTileValue_clipwindow,
		kTileValue_stackingtype,
		kTileValue_locus,
		kTileValue_alpha,
		kTileValue_id,
		kTileValue_disablefade,
		kTileValue_listindex,
		kTileValue_depth,
		kTileValue_y,
		kTileValue_x,
		kTileValue_user0,
		kTileValue_user1,
		kTileValue_user2,
		kTileValue_user3,
		kTileValue_user4,
		kTileValue_user5,
		kTileValue_user6,
		kTileValue_user7,
		kTileValue_user8,
		kTileValue_user9,
		kTileValue_user10,
		kTileValue_user11,
		kTileValue_user12,
		kTileValue_user13,
		kTileValue_user14,
		kTileValue_user15,
		kTileValue_user16,
		kTileValue_user17,
		kTileValue_user18,
		kTileValue_user19,
		kTileValue_user20,
		kTileValue_user21,
		kTileValue_user22,
		kTileValue_user23,
		kTileValue_user24,
		kTileValue_user25,
		kTileValue_clips,
		kTileValue_target,
		kTileValue_height,
		kTileValue_width,
		kTileValue_red,
		kTileValue_green,
		kTileValue_blue,
		kTileValue_tile,
		kTileValue_childcount,
		kTileValue_child_count = kTileValue_childcount,
		kTileValue_justify,
		kTileValue_zoom,
		kTileValue_font,
		kTileValue_wrapwidth,
		kTileValue_wraplimit,
		kTileValue_wraplines,
		kTileValue_pagenum,
		kTileValue_ishtml,
		kTileValue_cropoffsety,
		kTileValue_cropy = kTileValue_cropoffsety,
		kTileValue_cropoffsetx,
		kTileValue_cropx = kTileValue_cropoffsetx,
		kTileValue_menufade,
		kTileValue_explorefade,
		kTileValue_mouseover,
		kTileValue_string,
		kTileValue_shiftclicked,
		kTileValue_focusinset,
		kTileValue_clicked,
		kTileValue_clickcountbefore,
		kTileValue_clickcountafter,
		kTileValue_clickedfunc,
		kTileValue_clicksound,
		kTileValue_filename,

		//...

		kTileValue_xdefault = 0x00000FF0,
		kTileValue_xup,
		kTileValue_xdown,
		kTileValue_xleft,
		kTileValue_xright,
		kTileValue_xscroll,
		kTileValue_xlist,
		kTileValue_xbuttona,
		kTileValue_xbuttonb,
		kTileValue_xbuttonx,
		kTileValue_xbuttony,
		kTileValue_xbuttonlt,
		kTileValue_xbuttonrt,
		kTileValue_xbuttonlb,
		kTileValue_xbuttonrb,

		//...
	};

	virtual void		Destructor();
	virtual void		Unk_01(UInt32 unk0, const char* str, UInt32 unk2);
	virtual NiNode*		Unk_02();
	virtual UInt32		GetTypeID();
	virtual const char* GetType();
	virtual UInt32		UpdateField(UInt32 valueID, float floatValue, const char* strValue);
	virtual void		Unk_06();

	struct Value {
		union Operand {
			Value* ref;
			float* immediate;
		};

		struct Expression {
			Expression* prev;
			Expression* next;
			Operand		operand;	// how does it tell if it's ref or immediate?
			UInt16		opcode;		// i.e. 7D1 "copy", 7D2 "add", etc
			UInt16		unkE;
			Value*		src;
		};

		// linked list of compiled xml expression. Preliminary!
		struct ExpressionList {
			Expression* info;
			ExpressionList* next;
		};

		Tile*			parentTile;	// 00 - Tile * back to owning tile
		float			num;		// 04
		BSString		str;		// 08
		ExpressionList	exprList;	// 10
		UInt16			id;			// 18
		UInt8			bIsNum;		// 1A 0 = string, 1 = number
		UInt8			pad1B;		// 1B
	};
	
	Tile::Value* Tile::GetValueByType(UInt32 valueType) {

		for (NiTList<Value>::Node* node = valueList.start; node; node = node->next) {
			if (node->data && node->data->id == valueType) return node->data;
		}
		return NULL;

	}

	bool Tile::GetFloatValue(UInt32 valueType, float* out) {

		Value* val = GetValueByType(valueType);

		if (val) {
			*out = val->num;
			return true;
		}
		return false;

	}

	UInt8			unk04;		// 04 - 0 = base tile
	UInt8			unk05;		// 05 - looks like bool, possibly bModified? Seems only used for x, y, width, height changed
	UInt8			unk06;		// 06
	UInt8			pad07;		// 07
	BSString		name;		// 08
	Tile*			parent;		// 10
	NiTList<Value>	valueList;	// 14
	UInt32			unk24;		// 24	// NiNode *
	void*			unk28;		// 28
	UInt32			flags;		// 2C
	NiTList<Tile>	childList;	// 30
};
assert(sizeof(Tile) == 0x040);

class TileRect : public Tile {
public:
	enum {
		kID = 0x0385
	};

	UInt32	unk40;	// 40
};
assert(sizeof(TileRect) == 0x044);

class TileMenu : public TileRect {
public:
	Menu*	menu;	// 44
};
assert(sizeof(TileMenu) == 0x048);

class Menu {
public:
	enum MenuType {
		kMenuType_None = 0,			// for gamemode
		kMenuType_BigFour,			// F1 - F4 menus
		kMenuType_Any,
		kMenuType_Console,

		kMenuType_Message = 0x3E9,
		kMenuType_Inventory,
		kMenuType_Stats,
		kMenuType_HUDMain,
		kMenuType_HUDInfo,
		kMenuType_HUDReticle,
		kMenuType_Loading,
		kMenuType_Container,
		kMenuType_Dialog,
		kMenuType_HUDSubtitle,
		kMenuType_Generic,
		kMenuType_SleepWait,
		kMenuType_Pause,
		kMenuType_LockPick,
		kMenuType_Options,
		kMenuType_Quantity,
		kMenuType_Audio,
		kMenuType_Video,
		kMenuType_VideoDisplay,
		kMenuType_Gameplay,
		kMenuType_Controls,
		kMenuType_Magic,
		kMenuType_Map,
		kMenuType_MagicPopup,
		kMenuType_Negotiate,
		kMenuType_Book,
		kMenuType_LevelUp,
		kMenuType_Training,
		kMenuType_BirthSign,
		kMenuType_Class,
		kMenuType_unk407,
		kMenuType_Skills,
		kMenuType_unk409,
		kMenuType_Persuasion,
		kMenuType_Repair,
		kMenuType_RaceSex,
		kMenuType_SpellPurchase,
		kMenuType_Load,
		kMenuType_Save,
		kMenuType_Alchemy,
		kMenuType_Spellmaking,
		kMenuType_Enchantment,
		kMenuType_EffectSetting,
		kMenuType_Main,
		kMenuType_Breath,
		kMenuType_QuickKeys,
		kMenuType_Credits,
		kMenuType_SigilStone,
		kMenuType_Recharge,
		kMenuType_unk41A,
		kMenuType_TextEdit,

		kMenuType_Max
	};

	virtual void	Destructor(bool arg0);		// pass false to free memory
	virtual void	SetField(UInt32 idx, Tile* value);
	virtual void	Unk_02(UInt32 arg0, UInt32 arg1);	// show menu?
	virtual void	HandleClick(UInt32 buttonID, Tile* clickedButton); // buttonID = <id> trait defined in XML
	virtual void	HandleMouseover(UInt32 arg0, Tile* activeTile);	//called on mouseover, activeTile is moused-over Tile
	virtual void	Unk_05(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_06(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_07(UInt32 arg0, UInt32 arg1, UInt32 arg2);
	virtual void	Unk_08(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_09(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0A(UInt32 arg0, UInt32 arg1);
	virtual void	Unk_0B(void);
	virtual bool	HandleKeyboardInput(char inputChar);	//for keyboard shortcuts, return true if handled
	virtual UInt32	GetID();
	virtual bool	Unk_0E(UInt32 arg0, UInt32 arg1);

	TileMenu* tile;			// 04
	UInt32	  unk08;		// 08
	UInt32	  unk0C;		// 0C
	UInt32	  unk10;		// 10
	UInt32	  unk14;		// 14
	UInt32	  unk18;		// 18
	UInt32	  unk1C;		// 1C - initialized to 1
	UInt32	  id;			// 20 - uninitialized
	UInt32	  unk24;		// 24 - initialized to 4, is 8 if enabled?
};
assert(sizeof(Menu) == 0x028);

class ModInfo {
public:
	enum {
		kFlag_IsMaster = 1 << 0,
		kFlag_Loaded = 1 << 2,
		kFlag_Active = 1 << 3
	};

	template <typename tData> struct Node {
		tData*		 data;
		Node<tData>* next;
	};

	struct ChunkInfo {
		UInt32	type;		// e.g. 'GRUP', 'GLOB', etc
		UInt32	length;
	};

	struct FormInfo {	// ###TODO double check this, see 46B910 (TESForm virtual func, accepts Unk23C* as arg)
		ChunkInfo	chunkInfo;
		UInt32		flags;
		UInt32		formID;
		UInt32		unk10;
	};

	struct SizeInfo	{ // as seen in the editor
		UInt32		fileSizeLow;			// WIN32_FIND_DATA::nFileSizeLow 
		UInt32		fileSizeHigh;			// WIN32_FIND_DATA::nFileSizeHigh
	};

	UInt32			unk000;							// 000 appears to indicate status of file (open, closed, etc) 2, 9, 0C do stuff
	UInt32			unk004;							// 004
	UInt32			unk008;							// 008
	UInt32			unk00C;							// 00C
	BSFile*			bsFile;							// 010
	UInt32			unk014;							// 014
	UInt32			unk018;							// 018
	char			name[0x104];					// 01C
	char			filepath[0x104];				// 120 relative to "Oblivion\"
	UInt32			unk224;							// 224
	UInt32			unk228;							// 228 init to *(0xB055CC), seen 0x2800
	UInt32			unk22C[(0x23C - 0x22C) >> 2];	// 22C
	FormInfo		formInfo;						// 23C
	UInt32			chunkType250;					// 250
	UInt32			unk254[(0x3D0 - 0x254) >> 2];	// 254
	UInt32			version;						// 3D0 plugin version (0.8/1.0)
	UInt32			formCount;						// 3D4 record/form count
	UInt32			nextFormID;						// 3D8 used by TESFile::sub_486BF0 in the editor
	UInt32			flags;							// 3DC
	Node<char>		masterList;						// 3E0 linked list of .esm dependencies
	Node<SizeInfo>	masterSizeInfo;					// 3E8 linked list of file size info for above list
	UInt32			idx;							// 3F0
	void*			unk3F4;							// 3F4
	UInt32			unk3F8;							// 3F8
	UInt32			unk3FC;							// 3FC
	UInt8			unk400;							// 400 init to -1
	UInt8			pad401[3];
	BSString		authorName;						// 404
	BSString		modDescription;					// 40C
	UInt32			unk414;							// 414
	UInt32			unk418;							// 418
};
assert(sizeof(ModInfo) == 0x41C);

class ModList {
public:
	TList<ModInfo>		modInfoList;		// 00
	UInt32				loadedModCount;		// 08
	ModInfo*			loadedMods[0xFF];	// 0C
};
assert(sizeof(ModList) == 0x408);

class MasterDataHandler {
public:
	struct Unk8B8 {											// as seen in the editor
		UInt32				unk00;							// 00
		UInt32				unk04;							// 04
		UInt32				unk08;							// 08 initialized to (numLoadedMods << 24) | 0x800 during plugin load
		ModInfo*			activeFile;						// 0C active plugin
	};

	BoundObjectListHead*	boundObjects;					// 000
	TList<TESPackage>		packages;						// 004
	TList<TESWorldSpace>	worldSpaces;					// 00C
	TList<TESClimate>		climates;						// 014
	TList<TESWeather>		weathers;						// 01C
	TList<EnchantmentItem>	enchantmentItems;				// 024
	TList<SpellItem>		spellitems;						// 02C
	TList<TESHair>			hairs;							// 034
	TList<TESEyes>			eyes;							// 03C
	TList<TESRace>			races;							// 044
	TList<TESLandTexture>	landTextures;					// 04C
	TList<TESClass>			classes;						// 054
	TList<TESFaction>		factions;						// 05C
	TList<Script>			scripts;						// 064
	TList<TESSound>			sounds;							// 06C
	TList<TESGlobal>		globals;						// 074
	TList<TESTopic>			topics;							// 07C
	TList<TESQuest>			quests;							// 084
	TList<BirthSign>		birthsigns;						// 08C
	TList<TESCombatStyle>	combatStyles;					// 094
	TList<TESLoadScreen>	loadScreens;					// 09C
	TList<TESWaterForm>		waterForms;						// 0A4
	TList<TESEffectShader>	effectShaders;					// 0AC
	TList<TESObjectANIO>	objectAnios;					// 0B4
	TESRegionList*			regionList;						// 0BC
	NiTLargeArray<TESObjectCELL*>	cellArray;				// 0C0
	TESSkill				skills[0x15];					// 0D8
	Unk8B8					unk8B8;							// 8B8
	ModList					modList;						// 8C8
	UInt32					unkCD0[(0xCD8 - 0xCD0) >> 2];	// CD0
	TESRegionDataManager*	regionDataManager;				// CD8
	UInt32					unkCDC;							// CDC
};
assert(sizeof(MasterDataHandler) == 0xCE0);

class BSFadeNode : public NiNode {
public:
	UInt8	unk0DC;			// 0DC
	UInt8	unk0DD[3];		// 0DD
	float	fFarDistSqr;	// 0E0
	float	fNearDistSqr;	// 0E4
	float	unk0E8;			// 0E8
	UInt8	cMultType;		// 0EC
	UInt8	unk0ED[3];		// 0ED
};
assert(sizeof(BSFadeNode) == 0x0F0);

class BSRenderedTexture : public NiRefObject {
public:
	NiRenderTargetGroup* RenderTargetGroup;	// 008
	UInt32				 unk008[5];			// 00C
	NiRenderedTexture*	 RenderedTexture;	// 020
};
assert(sizeof(BSRenderedTexture) == 0x024);

class BSShaderProperty : public NiShadeProperty {
public:
	class RenderPass {
	public:
		UInt32	unk00;		// 00 - vtbl?
		UInt16	type;		// 04 - see 007B4920
		UInt8	isFPass;	// 06
	};

	virtual UInt32	Unk_15();		// returns 0 - may be a 'get type'
	virtual bool	Unk_16(UInt32 arg);	// returns 0
	virtual void*	Unk_17(UInt32 arg0, UInt32 arg1);
	virtual UInt16	Unk_18(UInt32 arg);	// returns 1
	virtual void*	Unk_19();		// returns &unk58

	enum {
		kSpecular			= 0x00000001,
		kSkinned			= 0x00000002,
		kLowDetail			= 0x00000004,
		kMultiTexture		= 0x00000008,
		kMultiSpecular		= 0x00000010,
		kEnvmapReflection	= 0x00000080,
		kAlphaBaseTexture	= 0x00000100,

		kScenegraph_Shift	= 28,
		kScenegraph_Mask	= 0x0F,
	};

	UInt32				passInfo;				// 01C
	float				alpha;					// 020 - init'd to 1
	UInt32				lastRenderPassState;	// 024 - init'd to 0
	NiTList<RenderPass>	passes;					// 028
	NiTList<RenderPass>	unk38;					// 038
	NiTList<RenderPass>	unk48;					// 048
	NiTList<RenderPass>	unk58;					// 058
	UInt32				unk068;					// 068
};
assert(sizeof(BSShaderProperty) == 0x06C);

class BSShaderLightingProperty : public BSShaderProperty {
public:
	NiTList<ShadowSceneLight*>	lights;	// 06C
	UInt32	unk07C;						// 07C
	NiTList<void*>				decals;	// 080 DECAL_DATA
	UInt32	unk090;						// 090
	float	unk094;						// 094
	UInt32	refID;						// 098
};
assert(sizeof(BSShaderLightingProperty) == 0x09C);

class SpeedTreeShaderLightingProperty : public BSShaderLightingProperty {
public:
	virtual void*	Unk_1A();
	virtual UInt32	Unk_1B();				// same as DistanceLODShaderProperty 1A-1D with unk0A4
	virtual void	Unk_1C(UInt32 arg);
	virtual UInt32	Unk_1D();
	virtual void	Unk_1E(UInt32 arg);
	virtual void	Unk_1F(NiObject* obj);	// set unk09C, destroy old object
	virtual UInt32	Unk_20();				// get unk0A0
	virtual void	Unk_21(UInt32 arg);		// set unk0A0
	virtual UInt32	Unk_22();				// return 0 or 3 based on unk0A0
	virtual void	Unk_23(UInt32 arg);		// set unk0A0 to 1 or 3 based on arg

	struct Str0A4
	{
		UInt32	pad00[2];	// 00
		UInt32	unk08;		// 08
		UInt16	unk0C;		// 0C
	};

	NiObject*	unk09C;	// 09C
	UInt32		unk0A0;	// 0A0
	Str0A4*		unk0A4;	// 0A4
};
assert(sizeof(SpeedTreeShaderLightingProperty) == 0x0A8);

class SpeedTreeLeafShaderProperty : public SpeedTreeShaderLightingProperty {
public:
	virtual SpeedTreeLeafShaderProperty* Unk_24(void);	// allocate a new SpeedTreeLeafShaderProperty
	virtual NiAdditionalGeometryData*	 Unk_25(void);	// allocate a new NiAdditionalGeometryData
	virtual UInt16						 Unk_26(void);	// return unk0AC
	virtual void*						 Unk_27(void);	// return unk0A8
	virtual UInt32						 Unk_28(void);	// return unk0A8 ? unk0A8[8] : 0
	virtual void						 Unk_29(void);	// call a fn on unk0A8 if it exists

	struct LeafData {
		UInt32		unk00;
		UInt32		unk04;
		float*		leafBase; // pointer to float4[48]
	};

	LeafData*	leafData;	// 0A8
	UInt16		unk0AC;		// 0AC
	UInt8		unk0AE[2];	// 0AE
};
assert(sizeof(SpeedTreeLeafShaderProperty) == 0x0B0);

class BSTreeModel : public NiRefObject {
public:
	UInt32					Unk08;				// 08
	UInt32					Unk0C;				// 0C
	UInt32					Unk10;				// 10
	UInt32					Unk14;				// 14
	UInt32					Unk18;				// 18
	UInt32					Unk1C;				// 1C
	UInt32					Unk20;				// 20
	UInt32					Unk24;				// 24
	UInt32					Unk28;				// 28
	UInt32					Unk2C;				// 2C
	NiSourceTexture*		BranchesTexture;	// 30
	NiTexturingProperty*	BranchesProp;		// 34
	NiSourceTexture*		LeavesTexture;		// 38
	NiTexturingProperty*	LeavesProp;			// 3C
	UInt32					Unk40;				// 40
	UInt32					Unk44;				// 44
	UInt32					Unk48;				// 48
	UInt32					Unk4C;				// 4C
	UInt32					Unk50;				// 50
	UInt32					Unk54;				// 54
};
assert(sizeof(BSTreeModel) == 0x058);

class BSTreeNode : public NiNode {
public:
	BSTreeModel*		TreeModel;		// DC
	UInt32				UnkE0;			// E0
	UInt32				UnkE4;			// E4
	UInt32				UnkE8;			// E8
	float				UnkEC;			// EC
};
assert(sizeof(BSTreeNode) == 0x0F0);

class InputGlobal {
public:
	enum {
		kFlag_HasJoysticks = 1 << 0,
		kFlag_HasMouse = 1 << 1,
		kFlag_HasKeyboard = 1 << 2,
		kFlag_BackgroundMouse = 1 << 3,
	};
	enum {
		kMaxDevices = 8,
	};

	struct Joystick {
		UInt32	unk000[0x244 >> 2];
	};

	struct JoystickObjectsInfo {
		enum {
			kHasXAxis = 1 << 0,
			kHasYAxis = 1 << 1,
			kHasZAxis = 1 << 2,
			kHasXRotAxis = 1 << 3,
			kHasYRotAxis = 1 << 4,
			kHasZRotAxis = 1 << 5
		};
		UInt32	axis;
		UInt32	buttons;
	};

	struct Unk1AF4 {
		UInt32	bufLen;
		UInt8	unk04[0x2C - 4];
	};

	UInt32				 flags;										// 0000
	IDirectInput8*		 dinputInterface;							// 0004
	IDirectInputDevice8* joystickInterfaces[kMaxDevices];			// 0008 - format is c_dfDIJoystick
	IDirectInputDevice8* keyboardInterface;							// 0028 - format is c_dfDIKeyboard
	IDirectInputDevice8* mouseInterface;							// 002C - format is c_dfDIMouse2
	UInt32				 unk0030[0x140];							// 0030
	Joystick			 devices[kMaxDevices];						// 0530
	DIDEVCAPS			 devCaps[kMaxDevices];						// 1750
	JoystickObjectsInfo	 devInfo[kMaxDevices];						// 18B0
	UInt32				 numJoysticks;								// 18F0
	UInt8				 CurrentKeyState[0x100];					// 18F4
	UInt8				 PreviousKeyState[0x100];					// 19F4
	Unk1AF4				 unk1AF4;									// 1AF4
	DIMOUSESTATE2		 CurrentMouseState;							// 1B20
	DIMOUSESTATE2		 PreviousMouseState;						// 1B34
	UInt32				 oldMouseButtonSwap;						// 1B48 - state of SwapMouseButton when program launched
	UInt32				 doubleClickTime;							// 1B4C - GetDoubleClickTime
	UInt32				 unk1B50[(0x1B7C - 0x1B50) >> 2];			// 1B50
	UInt8				 unk1B7C;									// 1B7C
	UInt8				 unk1B7D;									// 1B7D
	UInt8				 KeyboardInputControls[29];					// 1B7E
	UInt8				 MouseInputControls[29];					// 1B9B
	UInt8				 JoystickInputControls[29];					// 1BB8
	UInt8				 pad1BD7;									// 1BD7
};
assert(sizeof(InputGlobal) == 0x1BD8);

class SoundGlobal {
public:
	enum {
		kFlags_HasDSound = 1 << 0,
		kFlags_HasHardware3D = 1 << 2,
	};

	void Play(TESSound* Sound) { TESGameSound* GameSound = (TESGameSound*)ThisCall(0x006AE0A0, this, Sound->refID, 0x101, 0); ThisCall(0x006B7190, GameSound, 0); ThisCall(0x006B73E0, GameSound); }
	
	UInt32					unk000;						// 000
	UInt32					unk004;						// 004
	IDirectSound8*			dsoundInterface;			// 008
	IDirectSoundBuffer8*	primaryBufferInterface;		// 00C
	DSCAPS					soundCaps;					// 010
	UInt32					unk070;						// 070
	UInt32					unk074;						// 074
	IDirectSound3DListener* listenerInterface;			// 078
	UInt32					unk07C;						// 07C
	float					PlayerPosX;					// 080
	float					PlayerPosY;					// 084
	float					PlayerPosZ;					// 088
	UInt32					unk08C[(0x0A4 - 0x08C) >> 2];	// 08C
	UInt8					unk0A4;						// 0A4
	UInt8					unk0A5;						// 0A5
	UInt8					unk0A6;						// 0A6
	UInt8					pad0A7;						// 0A7
	UInt32					unk0A8;						// 0A8
	UInt32					flags;						// 0AC - flags?
	UInt32					unk0B0;						// 0B0
	UInt32					unk0B4;						// 0B4
	float					masterVolume;				// 0B8
	float					footVolume;					// 0BC
	float					voiceVolume;				// 0C0
	float					effectsVolume;				// 0C4
	UInt32					unk0C8;						// 0C8 - time
	UInt32					unk0CC;						// 0CC - time
	UInt32					unk0D0;						// 0D0 - time
	UInt32					unk0D4[(0x0DC - 0x0D4) >> 2];	// 0D4
	UInt32					unk0DC;						// 0DC
	UInt32					unk0E0[(0x2F0 - 0x0E0) >> 2];	// 0E0
	float					musicVolume;				// 2F0
	float					unk2F4;						// 2F4
	float					musicVolume2;				// 2F8
	UInt32					unk2FC;						// 2FC
	NiTMap<UInt32, TESGameSound>*	gameSoundMap;				// 300
	NiTMap<UInt32, NiAVObject>*		niObjectMap;				// 304
	NiTList<void>*			soundMessageMap;			// 308 - AudioManager::SoundMessage *
	UInt32					unk30C[(0x320 - 0x30C) >> 2];	// 30C
	NiTList<UInt32>*		soundMessageList;			// 320
	UInt32					unk324;						// 324
};
assert(sizeof(SoundGlobal) == 0x328);

class OSGlobal {
public:
	void			RenderShadowMaps() { ThisCall(0x004073D0, this); }
	InputGlobal*	GetInput() { return this->input; }
	SoundGlobal*	GetSound() { return this->sound; }
	void			PurgeModels() { ThisCall(0x00404C60, this, 1); }

	UInt8			quitGame;			// 00
	UInt8			exitToMainMenu;		// 01
	UInt8			unk02;				// 02
	UInt8			unk03;				// 03
	UInt8			unk04;				// 04
	UInt8			pad05[3];			// 05
	HWND			window;				// 08
	HINSTANCE		procInstance;		// 0C
	UInt32			mainThreadID;		// 10
	HANDLE			mainThreadHandle;	// 14
	UInt32			unk18;				// 18
	UInt32			unk1C;				// 1C
	InputGlobal*	input;				// 20
	SoundGlobal*	sound;				// 24
};
assert(sizeof(OSGlobal) == 0x028);

class MenuInterfaceManager {
public:
	bool			IsActive(UInt32 MenuType) { return activeMenuType == MenuType; }

	SceneGraph*		MenuRoot;						// 000
	SceneGraph*		MenuRoot3D;						// 004
	UInt8			unk008;							// 008
	UInt8			pad008[3];
	UInt32			unk00C;							// 00C
	UInt32			unk010;							// 010
	UInt32			unk014;							// 014
	void*			unk018;							// 018 NiDirectionalLight *
	Tile*			cursor;							// 01C
	UInt32			unk020[(0x050 - 0x020) >> 2];	// 020
	bool			debugTextOn;					// 050
	UInt8			unk051[3];
	NiNode*			unk054[(0x064 - 0x054) >> 2];	// 054
	NiNode*			unk064;							// 064 ShadowSceneNode *
	Tile*			menuRoot;						// 068
	Tile*			strings;						// 06C
	NiNode*			unk070;							// 070
	UInt32			unk074;							// 074
	void*			unk078;							// 078 NiAlphaProperty*
	UInt32			unk07C;							// 07C
	Tile*			hudReticule;					// 080
	UInt32			unk084;							// 084
	Tile*			altActiveTile;					// 088 appears to be active tile when activeTile is null and keyboard navigation used
	UInt32			unk08C;							// 08C
	UInt32			unk090;							// 090
	UInt32			unk094;							// 094
	Tile*			activeTile;						// 098 - moused-over tile
	Menu*			activeMenu;						// 09C - menu over which the mouse cursor is placed
	UInt32			unk0A0;							// 0A0
	UInt32			unk0A4;							// 0A4
	UInt32			unk0A8;							// 0A8
	UInt32			unk0AC;							// 0AC
	UInt8			msgBoxButton;					// 0B0
	UInt8			unk0B1[3];						// 0B1
	void*			unk0B4;							// 0B4 - stores callback for ShowMessageBox() (anything else?)
	UInt32			unk0B8;							// 0B8	
	TESObjectREFR*	debugSelection;					// 0BC
	UInt32			unk0C0[(0x0E0 - 0x0C0) >> 2];	// 0C0
	UInt32			activeMenuType;					// 0E0
	UInt32			unk0E4[(0x134 - 0x0E4) >> 2];	// 0E4
};
assert(offsetof(MenuInterfaceManager, activeMenu) == 0x09C);
assert(sizeof(MenuInterfaceManager) == 0x134);

class ExtraHavok : public BSExtraData {
public:
	bhkWorld*		world;	// 00C
	UInt32			unk10;	// 010
};
assert(sizeof(ExtraHavok) == 0x014);

class TimeGlobals {
public:
	TESGlobal* GameYear;		// 00
	TESGlobal* GameMonth;		// 04
	TESGlobal* GameDay;			// 08
	TESGlobal* GameHour;		// 0C
	TESGlobal* GameDaysPassed;	// 10
	TESGlobal* TimeScale;		// 14

	static float GetGameTime() { TimeGlobals* Globals = (TimeGlobals*)0x00B332E0; return Globals->GameHour->data * 60.0f * 60.0f; }

};
assert(sizeof(TimeGlobals) == 0x018); // Static class, size could be larger

class QueuedModelLoader {
public:
	void RemoveModel(char* WeaponModelPath) { ThisCall(0x004384E0, this, WeaponModelPath, 1, 1); }

	UInt32	Unk000[7]; // LockFreeMaps for models

};
assert(sizeof(QueuedModelLoader) == 0x01C);

static const float*		WaterBlend						= (float*)0x00B45E50;
static float*			LocalGrassWindMagnitudeMax		= (float*)0x00B46068;
static float*			LocalGrassWindMagnitudeMin		= (float*)0x00B46064;
static UInt8*			LocalWaterHiRes					= (UInt8*)0x00B45FD0;

static void* (__cdecl* MemoryAlloc)(size_t) = (void* (__cdecl*)(size_t))0x00401F00;
static void  (__cdecl* MemoryDealloc)(void*) = (void (__cdecl*)(void*))0x00401F20;
static bool  (__cdecl* ExtractArgs)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...) = (bool (__cdecl*)(CommandParam*, void*, UInt32*, TESObjectREFR*, TESObjectREFR*, Script*, ScriptEventList*, ...))0x004FAE80;
static void  (__cdecl* DrawGrass)(TESObjectCELL*, NiNode*, float, float, float, float, float, int, float, float, float) = (void (__cdecl*)(TESObjectCELL*, NiNode*, float, float, float, float, float, int, float, float, float))0x004EB3F0;
static bool  (__cdecl* ShowUIMessageBox)(const char*, void*, UInt32, const char*, ...) = (bool (__cdecl*)(const char*, void*, UInt32, const char*, ...))0x00579C10;
static bool  (__cdecl* ShowUIMessage)(const char*, UInt32, UInt32, float) = (bool (__cdecl*)(const char*, UInt32, UInt32, float))0x0057ACC0;
static bool  (__cdecl* LoadForm)(TESForm*, UInt32) = (bool (__cdecl*)(TESForm*, UInt32))0x00447050;
static void  (* PrintToConsole)(const char*, ...) = (void (*)(const char*, ...))0x00579B60;

#elif defined(SKYRIM)

#endif
//return *(SceneGraph**)0x01B2E8BC;
//
//
//Sky* UtilityManager::GetSky() {
//
//#if defined(NEWVEGAS)
//	return *(Sky**)0x011CCB78;
//#elif defined(OBLIVION)
//	return *(Sky**)0x00B365C4;
//#elif defined(SKYRIM)
//	return *(Sky**)0x01B1160C;
//#endif
//
//}
//
//TES* UtilityManager::GetTES() {
//
//#if defined(NEWVEGAS)
//	return *(TES**)0x11DEA10;
//#elif defined(OBLIVION)
//	return *(TES**)0x00B333A0;
//#elif defined(SKYRIM)
//	return NULL;
//#endif
//
//}
//
//TESObjectCELL* UtilityManager::GetCell(UInt32 x, UInt32 y) {
//
//#if defined(NEWVEGAS)
//	return *(TESObjectCELL**)ThisCall(0x004BA490, GetTES()->gridCellArray, x, y);
//#elif defined(OBLIVION)
//	return ((GridCellArray::GridEntry*)ThisCall(0x00482150, Tes->gridCellArray, x, y))->cell;
//#elif defined(SKYRIM)
//	return NULL;
//#endif
//}
//
//void UtilityManager::RenderShadowMaps() {
//
//#if defined(NEWVEGAS)
//	ThisCall(0x00871290, (*g_osGlobals));
//#elif defined(OBLIVION)
//	ThisCall(0x004073D0, Global);
//#endif
//
//}
//
//float UtilityManager::GetGameTime() {
//
//#if defined(NEWVEGAS)
//	TimeGlobals* Globals = (TimeGlobals*)0x011DE7B8;
//	return Globals->GameHour->data * 60.0f * 60.0f;
//#elif defined(OBLIVION)
//	TimeGlobals* Globals = (TimeGlobals*)0x00B332E0;
//	return Globals->GameHour->data * 60.0f * 60.0f;
//#elif defined(SKYRIM)
//	class TimeGlobals {
//	public:
//		UInt32		unk00;			// 00 virtual table?
//		TESGlobal* GameYear;		// 04
//		TESGlobal* GameMonth;		// 08
//		TESGlobal* GameDay;		// 0C
//		TESGlobal* GameHour;		// 10
//		TESGlobal* GameDaysPassed;	// 14
//		TESGlobal* TimeScale;		// 18
//		UInt32		unk1C;			// 1C
//		UInt32		unk20;			// 20
//	};
//	TimeGlobals* Globals = (TimeGlobals*)0x012E5690;
//	return Globals->GameHour->data * 60.0f * 60.0f;
//#endif
//
//}
//UInt8 UtilityManager::GetSitSleepState(Actor* Act) {
//
//#if defined(NEWVEGAS)
//	return Act->GetSitSleepState();
//#elif defined(OBLIVION)
//	return Act->GetSitSleepState();
//#elif defined(SKYRIM)
//	return Act->actorState.flags04 >> 14 & 0xF;
//#endif
//
//	void UtilityManager::RestoreCamera() {
//#if defined(OBLIVION)
//		ThisCall(0x0066C600, Player);
//#elif defined(SKYRIM)
//		ThisCall(0x00730EE0, *g_thePlayer, 0);
//#endif
//}
//
//	void UtilityManager::SetCameraFOV(SceneGraph* WorldSceneGraph, float FoV) {
//#if defined(NEWVEGAS)
//		ThisCall(0x00C52020, WorldSceneGraph, FoV, 0, NULL, 0);
//#elif defined(OBLIVION)
//		ThisCall(0x00664A40, Player, FoV);
//#elif defined(SKYRIM)
//		ThisCall(0x00B17960, WorldSceneGraph, FoV, 0, NULL, 0);
//#endif
//}
//
//	bool UtilityManager::IsMainMenu() {
//
//#if defined(NEWVEGAS)
//		InterfaceManager* Im = *(InterfaceManager**)0x011D8A80;
//		return (Im->menuStack[0] == 1007 && Im->menuStack[1] == 1013) || (Im->menuStack[0] == 3 && Im->menuStack[1] == 1007 && Im->menuStack[2] == 1013);
//#elif defined(OBLIVION)
//		UInt32(*GetMenuMode)() = (UInt32(*)())0x00579060;
//		return GetMenuMode() == 1044;
//#elif defined(SKYRIM)
//		return MenuManager::GetSingleton()->IsMenuOpen(&UIStringHolder::GetSingleton()->mainMenu);
//#endif
//
//}
//
//	bool UtilityManager::IsMenu(UInt32 MenuType) {
//
//#if defined(NEWVEGAS)
//		bool (*IsMenuOpen)() = (bool(*)())0x00702360;
//		bool(__cdecl * IsMenuMode)(UInt32) = (bool(*)(UInt32))0x00702450;
//		if (MenuType == 0)
//			return IsMenuOpen();
//		else
//			return IsMenuMode(MenuType);
//#elif defined(OBLIVION)
//		bool (*IsMenuOpen)() = (bool(*)())0x00578F60;
//		bool(__cdecl * IsMenuMode)(UInt32) = (bool(*)(UInt32))0x0057C140;
//		if (MenuType == 0)
//			return IsMenuOpen();
//		else
//			return IsMenuMode(MenuType);
//#elif defined(SKYRIM)
//		if (MenuType == 1009)
//			return MenuManager::GetSingleton()->IsMenuOpen(&UIStringHolder::GetSingleton()->dialogueMenu);
//		else
//			return false;
//#endif
//
//}
//	bool UtilityManager::IsMenu() {
//		bool(__cdecl * MenuMode)() = (bool(*)())0x00578F60;
//		return MenuMode();
//}
//}
//bool UtilityManager::IsConsole() {
//
//#if defined(NEWVEGAS)
//	return IsConsoleMode();
//#elif defined(OBLIVION)
//	return *(bool*)0x00B361AC;
//#elif defined(SKYRIM)
//	return MenuManager::GetSingleton()->IsMenuOpen(&UIStringHolder::GetSingleton()->console);
//#endif
//
//}
//void UtilityManager::ForceWeather(TESWeather* Weather) {
//
//#if defined(NEWVEGAS)
//	ThisCall(0x0063D0E0, GetSky(), Weather, 0);
//#elif defined(OBLIVION)
//	ThisCall(0x00542260, Tes->sky, Weather, 0);
//#elif defined(SKYRIM)
//	ThisCall(0x006A3FB0, GetSky(), Weather, 0);
//#endif
//
//}

//float UtilityManager::GetWaterHeight() {
//
//#if defined(NEWVEGAS)
//	if ((*g_thePlayer)->renderState)
//		return (*g_thePlayer)->renderState->waterHeight;
//	else
//		return ThisCallF(kGetWaterHeight, (*g_thePlayer)->parentCell);
//#elif defined(OBLIVION)
//	return ThisCallF(kGetWaterHeight, Player->parentCell);
//#elif defined(SKYRIM)
//	return ThisCallF(kGetWaterHeight, (*g_thePlayer));
//#endif
//
//}

//TESWaterForm* UtilityManager::GetWaterForm(TESObjectCELL* Cell) {
//
//#if defined(NEWVEGAS)
//	return NULL;
//#elif defined(OBLIVION)
//	return NULL;
//#elif defined(SKYRIM)
//	return (TESWaterForm*)ThisCall(0x004C0800, Cell);
//#endif
//
//}


//#if defined(NEWVEGAS)
//#define kMessageBoxButtonTextYes 0x00000000
//#define kMessageBoxButtonTextNo 0x00000000
//#define kGetFarPlaneDistance 0x00C52450
//#define kPackGeometryBuffer 0x00E71FE0
//#define kPackSkinnedGeometryBuffer 0x00E6D780
//#define kCalculateBoneMatrixes 0x00E6FE30
//#elif defined(OBLIVION)
//#define kMessageBoxButtonTextYes 0x00B38CF8
//#define kMessageBoxButtonTextNo 0x00B38D00
//#elif defined(SKYRIM)
//#define kMessageBoxButtonTextYes 0x01B17FA0
//#define kMessageBoxButtonTextNo 0x01B17FAC
//#define kGetWaterHeight 0x004D62D0
//#define kGetFarPlaneDistance 0x00B17D50
//#endif

extern OSGlobal*				Global;
extern TES*						Tes;
extern PlayerCharacter*			Player;
extern SceneGraph*				WorldSceneGraph;
extern MasterDataHandler*		DataHandler;
extern MenuInterfaceManager*	MenuManager;
extern QueuedModelLoader*		ModelLoader;

void PerformGameInitialization();