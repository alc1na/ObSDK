#pragma once
#include <filesystem>

inline std::filesystem::path GetDLLFolder() {
	HMODULE hinstDLL;
	GetModuleHandleExA(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
		reinterpret_cast<LPCSTR>(&GetDLLFolder),
		&hinstDLL
	);

	char sIniPath[MAX_PATH];
	GetModuleFileNameA(hinstDLL, sIniPath, MAX_PATH);
	return std::filesystem::path(sIniPath).parent_path();
}
