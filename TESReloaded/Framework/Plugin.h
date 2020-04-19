#pragma once

class PluginInterface {
public:
#if defined(OBLIVION)
	enum InterfaceQueryEnum
	{
		kInterface_Serialization = 1,
		// added v0019
		kInterface_CommandTable  = 6,
	};
#else if defined(NEWVEGAS)
	enum InterfaceQueryEnum
	{
		kInterface_Serialization = 0,
		//Added v0002
		kInterface_CommandTable  = 3 ,
	};
#endif
	UInt32	Version;
	UInt32	GameVersion;
	UInt32	EditorVersion;
	UInt32	IsEditor;

	bool	(*RegisterCommand)(CommandInfo* info);
	void	(*SetOpcodeBase)(UInt32 opcode);
	void*   (*QueryInterface)(InterfaceQueryEnum id);

};

class PluginInfo {
public:
	enum {
		kInfoVersion = 2
	};

	UInt32		InfoVersion;
	const char* Name;
	UInt32		Version;
};