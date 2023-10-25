#include "GameHook.hpp"

bool GameHook::sampleMod1Init = false;

// patch toggle bools

// gui

// system

// inventory

// dev values
uintptr_t GameHook::_baseAddress(NULL);
DWORD GameHook::_pID(NULL);
bool GameHook::_hooked(false);

// patches

// dev functions

DWORD GameHook::_getProcessID(void) {
	// search game window
	HWND hwnd = FindWindowA(NULL, "METAL GEAR SOLID 3 SNAKE EATER");
	if (hwnd == NULL) {
		// return if game window not found
		return 0;
	}
	DWORD pID;													  // process ID
	GetWindowThreadProcessId(hwnd, &pID);						  // get Process ID
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID); // open process
	if (pHandle == INVALID_HANDLE_VALUE) {
		// return if couldn't open the process
		return 0;
	}
	return pID;
}

uintptr_t GameHook::_getModuleBaseAddress(DWORD procId, const char* modName) {
	return (uintptr_t)GetModuleHandle(NULL);
}

void GameHook::_hook(void) {
	DWORD ID = GameHook::_getProcessID();
	if (ID <= 0)
		return;
	GameHook::_pID = ID;
	GameHook::_baseAddress = GameHook::_getModuleBaseAddress(ID, "METAL GEAR SOLID3.exe");
	GameHook::_hooked = true;
}

void GameHook::_patch(char* dst, char* src, int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void GameHook::_nop(char* dst, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset(dst, 0x90, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

void GameHook::under_line(const ImColor& col) {
	ImVec2 min = ImGui::GetItemRectMin();
	ImVec2 max = ImGui::GetItemRectMax();
	min.y = max.y;
	ImGui::GetWindowDrawList()->AddLine(min, max, col, 1.0f);
}

void GameHook::onConfigLoad(const utils::Config& cfg) {
	
}

void GameHook::onConfigSave(utils::Config& cfg) {

	cfg.save(cfgString);
}
