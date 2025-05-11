#pragma once
#include <cstdio>
#include <format>

class Logger {
	std::string m_path{};
	FILE* m_file = nullptr;
	bool m_init = false;
	bool m_debug = false;

public:
	Logger() = default;
	Logger(Logger& other) = delete;
	Logger(Logger&& other) noexcept {
		this->operator=(std::move(other));
	}

	Logger& operator=(Logger&& other) noexcept {
		m_path = std::move(other.m_path);
		m_file = other.m_file;
		m_init = other.m_init;
		m_debug = other.m_debug;

		other.m_path = {};
		other.m_file = nullptr;
		other.m_init = false;
		other.m_debug = false;
		return *this;
	}

	explicit Logger(std::string&& path) : m_path(std::move(path)) {
		m_file = _fsopen(m_path.c_str(), "wb+", _SH_DENYNO);
		m_init = m_file != nullptr;

#ifdef _DEBUG
		AllocConsole();
		(void)freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		m_debug = true;
#endif
	}

	explicit Logger(std::filesystem::path&& path) : Logger(path.string()) {}

	~Logger() {
		if (m_file) {
			(void)fclose(m_file);
			m_file = nullptr;
		}

		m_init = false;
	}

	void EnableDebug() {
		m_debug = true;
	}

	void Debug(const char* fmt, ...) const {
		if (m_debug) {
			va_list va;
			va_start(va, fmt);
			Write("[DEBUG]", fmt, va);
			va_end(va);
		}
	}

	void Warning(const char* fmt, ...) const {
		va_list va;
		va_start(va, fmt);
		Write("[WARN]", fmt, va);
		va_end(va);
	}

	void Info(const char* fmt, ...) const {
		va_list va;
		va_start(va, fmt);
		Write("[INFO]", fmt, va);
		va_end(va);
	}

	void Error(const char* fmt, ...) const {
		va_list va;
		va_start(va, fmt);
		Write("[ERROR]", fmt, va);
		va_end(va);
	}

private:
	void Write(const char* type, const char* fmt, const va_list va) const {
#ifdef _DEBUG
		(void)puts(type);
		(void)putc(' ');
		(void)vprintf(fmt, va);
#endif

		if (!m_init) {
			return;
		}

		(void)fputs(type, m_file);
		(void)fputc(' ', m_file);
		(void)vfprintf(m_file, fmt, va);
		fflush(m_file);
	}
};
