OSGlobal*				Global = NULL;
TES*					Tes = NULL;
PlayerCharacter*		Player = NULL;
SceneGraph*				WorldSceneGraph = NULL;
MasterDataHandler*		DataHandler = NULL;
MenuInterfaceManager*	MenuManager = NULL;
QueuedModelLoader*		ModelLoader = NULL;

#if defined(NEWVEGAS)
#define kNewOSGlobal			 0x0086C160
#define kNewTES					 0x0044FB20
#define kNewPlayerCharacter		 0x00938180
#define kNewSceneGraph			 0x00878610
#define kNewMasterDataHandler	 0x0045D270
#define kNewMenuInterfaceManager 0x0070A130
#define kNewQueuedModelLoader	 0x00442650

class GameInitialization {
public:
	OSGlobal*				TrackNewOSGlobal(HWND, HINSTANCE);
	TES*					TrackNewTES(char*, NiNode*, NiNode*, Sky*, NiNode*);
	PlayerCharacter*		TrackNewPlayerCharacter();
	SceneGraph*				TrackNewSceneGraph(char*, UInt8, NiCamera*);
	MasterDataHandler*		TrackNewMasterDataHandler();
	MenuInterfaceManager*	TrackNewMenuInterfaceManager();
	QueuedModelLoader*		TrackNewQueuedModelLoader();
};

OSGlobal* (__thiscall GameInitialization::* NewOSGlobal)(HWND, HINSTANCE);
OSGlobal* (__thiscall GameInitialization::* TrackNewOSGlobal)(HWND, HINSTANCE);
OSGlobal* GameInitialization::TrackNewOSGlobal(HWND Window, HINSTANCE Instance) { Global = (OSGlobal*)(this->*NewOSGlobal)(Window, Instance); return Global; }

TES* (__thiscall GameInitialization::* NewTES)(char*, NiNode*, NiNode*, Sky*, NiNode*);
TES* (__thiscall GameInitialization::* TrackNewTES)(char*, NiNode*, NiNode*, Sky*, NiNode*);
TES* GameInitialization::TrackNewTES(char* RootData, NiNode* ObjectLODRoot, NiNode* LODRoot, Sky* Sky, NiNode* WaterLOD) { Tes = (TES*)(this->*NewTES)(RootData, ObjectLODRoot, LODRoot, Sky, WaterLOD); return Tes; }

PlayerCharacter* (__thiscall GameInitialization::* NewPlayerCharacter)();
PlayerCharacter* (__thiscall GameInitialization::* TrackNewPlayerCharacter)();
PlayerCharacter* GameInitialization::TrackNewPlayerCharacter() { Player = (PlayerCharacter*)(this->*NewPlayerCharacter)(); return Player; }

SceneGraph* (__thiscall GameInitialization::* NewSceneGraph)(char*, UInt8, NiCamera*);
SceneGraph* (__thiscall GameInitialization::* TrackNewSceneGraph)(char*, UInt8, NiCamera*);
SceneGraph* GameInitialization::TrackNewSceneGraph(char* Name, UInt8 IsMinFarPlaneDistance, NiCamera* Camera) { SceneGraph* SG = (SceneGraph*)(this->*NewSceneGraph)(Name, IsMinFarPlaneDistance, Camera); if (!strcmp(Name, "World")) WorldSceneGraph = SG; return SG; }

MasterDataHandler* (__thiscall GameInitialization::* NewMasterDataHandler)();
MasterDataHandler* (__thiscall GameInitialization::* TrackNewMasterDataHandler)();
MasterDataHandler* GameInitialization::TrackNewMasterDataHandler() { DataHandler = (MasterDataHandler*)(this->*NewMasterDataHandler)(); return DataHandler; }

MenuInterfaceManager* (__thiscall GameInitialization::* NewMenuInterfaceManager)();
MenuInterfaceManager* (__thiscall GameInitialization::* TrackNewMenuInterfaceManager)();
MenuInterfaceManager* GameInitialization::TrackNewMenuInterfaceManager() { MenuManager = (MenuInterfaceManager*)(this->*NewMenuInterfaceManager)(); return MenuManager; }

QueuedModelLoader* (__thiscall GameInitialization::* NewQueuedModelLoader)();
QueuedModelLoader* (__thiscall GameInitialization::* TrackNewQueuedModelLoader)();
QueuedModelLoader* GameInitialization::TrackNewQueuedModelLoader() { ModelLoader = (QueuedModelLoader*)(this->*NewQueuedModelLoader)(); return ModelLoader; }
#elif defined(OBLIVION)
#define kNewOSGlobal			 0x00404A00
#define kNewTES					 0x00441970
#define kNewPlayerCharacter		 0x0066A740
#define kNewSceneGraph			 0x004114E0
#define kNewMasterDataHandler	 0x00446D80
#define kNewMenuInterfaceManager 0x005802B0
#define kNewQueuedModelLoader	 0x0043E950

class GameInitialization {
public:
	OSGlobal*				TrackNewOSGlobal(HWND, HINSTANCE);
	TES*					TrackNewTES(char*, NiNode*, NiNode*, Sky*);
	PlayerCharacter*		TrackNewPlayerCharacter();
	SceneGraph*				TrackNewSceneGraph(char*, UInt8, NiCamera*);
	MasterDataHandler*		TrackNewMasterDataHandler();
	MenuInterfaceManager*	TrackNewMenuInterfaceManager();
	QueuedModelLoader*		TrackNewQueuedModelLoader();
};

OSGlobal* (__thiscall GameInitialization::* NewOSGlobal)(HWND, HINSTANCE);
OSGlobal* (__thiscall GameInitialization::* TrackNewOSGlobal)(HWND, HINSTANCE);
OSGlobal* GameInitialization::TrackNewOSGlobal(HWND Window, HINSTANCE Instance) { Global = (OSGlobal*)(this->*NewOSGlobal)(Window, Instance); return Global; }

TES* (__thiscall GameInitialization::* NewTES)(char*, NiNode*, NiNode*, Sky*);
TES* (__thiscall GameInitialization::* TrackNewTES)(char*, NiNode*, NiNode*, Sky*);
TES* GameInitialization::TrackNewTES(char* RootData, NiNode* ObjectLODRoot, NiNode* LODRoot, Sky* Sky) { Tes = (TES*)(this->*NewTES)(RootData, ObjectLODRoot, LODRoot, Sky); return Tes; }

PlayerCharacter* (__thiscall GameInitialization::* NewPlayerCharacter)();
PlayerCharacter* (__thiscall GameInitialization::* TrackNewPlayerCharacter)();
PlayerCharacter* GameInitialization::TrackNewPlayerCharacter() { Player = (PlayerCharacter*)(this->*NewPlayerCharacter)(); return Player; }

SceneGraph* (__thiscall GameInitialization::* NewSceneGraph)(char*, UInt8, NiCamera*);
SceneGraph* (__thiscall GameInitialization::* TrackNewSceneGraph)(char*, UInt8, NiCamera*);
SceneGraph* GameInitialization::TrackNewSceneGraph(char* Name, UInt8 IsMinFarPlaneDistance, NiCamera* Camera) { SceneGraph* SG = (SceneGraph*)(this->*NewSceneGraph)(Name, IsMinFarPlaneDistance, Camera); if (!strcmp(Name, "World")) WorldSceneGraph = SG; return SG; }

MasterDataHandler* (__thiscall GameInitialization::* NewMasterDataHandler)();
MasterDataHandler* (__thiscall GameInitialization::* TrackNewMasterDataHandler)();
MasterDataHandler* GameInitialization::TrackNewMasterDataHandler() { DataHandler = (MasterDataHandler*)(this->*NewMasterDataHandler)(); return DataHandler; }

MenuInterfaceManager* (__thiscall GameInitialization::* NewMenuInterfaceManager)();
MenuInterfaceManager* (__thiscall GameInitialization::* TrackNewMenuInterfaceManager)();
MenuInterfaceManager* GameInitialization::TrackNewMenuInterfaceManager() { MenuManager = (MenuInterfaceManager*)(this->*NewMenuInterfaceManager)(); return MenuManager; }

QueuedModelLoader* (__thiscall GameInitialization::* NewQueuedModelLoader)();
QueuedModelLoader* (__thiscall GameInitialization::* TrackNewQueuedModelLoader)();
QueuedModelLoader* GameInitialization::TrackNewQueuedModelLoader() { ModelLoader = (QueuedModelLoader*)(this->*NewQueuedModelLoader)(); return ModelLoader; }
#elif defined(SKYRIM)

#endif

void PerformGameInitialization() {

	*((int*)&NewOSGlobal)				= kNewOSGlobal;
	TrackNewOSGlobal					= &GameInitialization::TrackNewOSGlobal;
	*((int*)&NewTES)					= kNewTES;
	TrackNewTES							= &GameInitialization::TrackNewTES;
	*((int*)&NewPlayerCharacter)		= kNewPlayerCharacter;
	TrackNewPlayerCharacter				= &GameInitialization::TrackNewPlayerCharacter;
	*((int*)&NewSceneGraph)				= kNewSceneGraph;
	TrackNewSceneGraph					= &GameInitialization::TrackNewSceneGraph;
	*((int*)&NewMasterDataHandler)		= kNewMasterDataHandler;
	TrackNewMasterDataHandler			= &GameInitialization::TrackNewMasterDataHandler;
	*((int*)&NewMenuInterfaceManager)	= kNewMenuInterfaceManager;
	TrackNewMenuInterfaceManager		= &GameInitialization::TrackNewMenuInterfaceManager;
	*((int*)&NewQueuedModelLoader)		= kNewQueuedModelLoader;
	TrackNewQueuedModelLoader			= &GameInitialization::TrackNewQueuedModelLoader;

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(&(PVOID&)NewOSGlobal,				*((PVOID*)&TrackNewOSGlobal));
	DetourAttach(&(PVOID&)NewTES,					*((PVOID*)&TrackNewTES));
	DetourAttach(&(PVOID&)NewPlayerCharacter,		*((PVOID*)&TrackNewPlayerCharacter));
	DetourAttach(&(PVOID&)NewSceneGraph,			*((PVOID*)&TrackNewSceneGraph));
	DetourAttach(&(PVOID&)NewMasterDataHandler,		*((PVOID*)&TrackNewMasterDataHandler));
	DetourAttach(&(PVOID&)NewMenuInterfaceManager,	*((PVOID*)&TrackNewMenuInterfaceManager));
	DetourAttach(&(PVOID&)NewQueuedModelLoader,		*((PVOID*)&TrackNewQueuedModelLoader));
	DetourTransactionCommit();

}

