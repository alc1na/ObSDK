#pragma once
#include <cstdio>
#include <format>

#include "Misc.h"

namespace Log {
	namespace Detail {
		inline bool bDebug = false;
		inline bool bConsole = false;
		inline bool bInit = false;
		inline FILE* pFile = nullptr;

		inline void Write(const char* type, const char* fmt, const va_list va) {
			if (bConsole) {
				printf("%s ", type);
				(void)vprintf(fmt, va);
			}

			if (!bInit) {
				return;
			}

			(void)fputs(type, pFile);
			(void)fputc(' ', pFile);
			(void)vfprintf(pFile, fmt, va);
			(void)fflush(pFile);
		}
	}

	inline void Init(const char* name) {
		const auto logPath = GetDLLFolder() / name / ".log";
		Detail::pFile = _fsopen(logPath.string().c_str(), "wb+", _SH_DENYNO);
		Detail::bInit = Detail::pFile != nullptr;

#if defined(_DEBUG) || defined(_RELDBG)
		AllocConsole();
		(void)freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		Detail::bDebug = true;
		Detail::bConsole = true;
#endif
	}

	inline void EnableDebug() {
		Detail::bDebug = true;
	}

	inline void Debug(const char* fmt, ...) {
		if (Detail::bDebug) {
			va_list va;
			va_start(va, fmt);
			Detail::Write("[DEBUG]", fmt, va);
			va_end(va);
		}
	}

	inline void Info(const char* fmt, ...) {
		va_list va;
		va_start(va, fmt);
		Detail::Write("[INFO]", fmt, va);
		va_end(va);
	}

	inline void Warning(const char* fmt, ...) {
		va_list va;
		va_start(va, fmt);
		Detail::Write("[WARN]", fmt, va);
		va_end(va);
	}

	inline void Error(const char* fmt, ...) {
		va_list va;
		va_start(va, fmt);
		Detail::Write("[ERROR]", fmt, va);
		va_end(va);
	}
}
