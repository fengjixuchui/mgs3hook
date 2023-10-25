#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include "../imgui/imgui.h"
#include "../utils/config.hpp"
#include <vector>

class GameHook {
public:

	static bool sampleMod1Init;
	// patches
	// static bool imguiDraw;

	// other

	// dev
	static DWORD _getProcessID(void);
	static uintptr_t _getModuleBaseAddress(DWORD procId, const char* modName);
	static void _hook(void);
	static void _patch(char* dst, char* src, int size);
	static void _nop(char* dst, unsigned int size);
	static void onConfigLoad(const utils::Config& cfg);
	static void onConfigSave(utils::Config& cfg);

	static bool _hooked;
	static DWORD _pID;
	static uintptr_t _baseAddress;
	static uintptr_t actorPlayable;
	static inline utils::Config cfg{ "Game_Hook.cfg" };
	static inline const char* cfgString{ "Game_Hook.cfg" };
	static inline const char* dllName{"mgs3hook 1.0"};
	static inline const char* repoUrl{ "https://github.com/SSSiyan/mgs3hook" };

	// gui
	static void gameGui(void);
	static void under_line(const ImColor& col);

	static float trainerWidth;
	static float trainerMaxHeight;
	static float trainerHeightBorder;
	static float trainerVariableHeight;
	static float sameLineWidth;
	static float inputItemWidth;
private:
};
