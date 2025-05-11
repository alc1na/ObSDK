#pragma once
#include <string>

class IniFile {
	std::string m_path;
	const char* m_name;

public:
	explicit IniFile(const char* name) {
		m_name = name;
		m_path = (GetDLLFolder() / name / ".ini").string();
	}

	bool GetBool(const char* section, const char* label, const bool bDefault) const {
		char strOverride[10];
		GetPrivateProfileStringA(section, label, bDefault ? "true" : "false", strOverride, 9, m_path.c_str());
		return !_strnicmp(strOverride, "true", 10);
	}

	float GetFloat(const char* section, const char* label, const float fDefault) const {
		const auto strDefault = std::to_string(fDefault);
		char strValue[20];
		GetPrivateProfileStringA(section, label, strDefault.c_str(), strValue, 19, m_path.c_str());
		try {
			return std::stof(strValue);
		}
		catch (const std::exception&) {
			return fDefault;
		}
	}

	uint32_t GetInt(const char* section, const char* label, const uint32_t iDefault) const {
		return GetPrivateProfileIntA(section, label, static_cast<INT>(iDefault), m_path.c_str());
	}
};