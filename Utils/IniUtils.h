#pragma once
#include <string>

inline bool GetIniBool(const char* path, const char* section, const char* label, const bool defaultValue) {
	char strOverride[10];
	GetPrivateProfileStringA(section, label, defaultValue ? "true" : "false", strOverride, 9, path);
	return !_strnicmp(strOverride, "true", 10);
}

inline float GetIniFloat(const char* path, const char* section, const char* label, const float defaultValue) {
	const auto strDefault = std::to_string(defaultValue);
	char strValue[20];
	GetPrivateProfileStringA(section, label, strDefault.c_str(), strValue, 9, path);
	try {
		return std::stof(strValue);
	}
	catch (const std::exception&) {
		return defaultValue;
	}
}