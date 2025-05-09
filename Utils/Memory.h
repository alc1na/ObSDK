#pragma once
#include "Windows.h"
#include <type_traits>

template <typename R = void, typename... Args>
R Fastcall(void* address, Args&&... args) {
	return reinterpret_cast<R(__fastcall*)(Args...)>(address)(std::forward<Args>(args)...);
}

inline void SafeWrite(uint8_t* address, const uint8_t* bytes, const size_t len) {
	DWORD flOldProtect;
	VirtualProtect(address, len, PAGE_EXECUTE_READWRITE, &flOldProtect);
	memcpy(address, bytes, len);
	VirtualProtect(address, len, flOldProtect, &flOldProtect);
}