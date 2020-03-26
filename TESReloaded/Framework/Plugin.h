#pragma once

class PluginInterface {
public:
	UInt32	Version;
	UInt32	GameVersion;
	UInt32	EditorVersion;
	UInt32	IsEditor;

	bool	(*RegisterCommand)(CommandInfo* info);
	void	(*SetOpcodeBase)(UInt32 opcode);
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