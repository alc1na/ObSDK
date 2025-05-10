#pragma once
#include <cstdint>
#include <Psapi.h>
#include <stdexcept>
#include <string>
#include <vector>
#include <intrin.h>
#include <functional>

#include "Hooklib.h"

// struct Pattern {
// 	std::string m_pattern{};
// 	size_t m_first{};
// 	size_t m_first_offset{};
// 	bool m_isReloff = false;
// 	size_t m_reloffStart = 0;
// 	size_t m_reloffLength = 0;
//
// 	// AVX512 members
// 	std::vector<__m512i> m_avx512_vec{};
// 	std::vector<uint64_t> m_avx512_mask{};
// 	__m512i m_avx512_lookahead{};
//
// 	// AVX256 members
// 	std::vector<__m256i> m_avx256_vec{};
// 	std::vector<uint32_t> m_avx256_mask{};
// 	__m256i m_avx256_lookahead{};
//
// 	// Default members
// 	std::vector<uint8_t> m_default_bytes{};
// 	std::vector<bool> m_default_mask{};
//
// 	// ReSharper disable once CppNonExplicitConvertingConstructor
// 	Pattern(const char* pattern) {
// 		m_pattern = pattern;
// 		static bool loggedSupport = false;
//
// 		// AVX512
// 		if (__check_isa_support(__IA_SUPPORT_VECTOR512)) {
// 			_init_AVX512();
// 		
// 			if (!loggedSupport) {
// 				printf("Pattern scans are using AVX512\n");
// 				loggedSupport = true;
// 			}
// 		
// 			return;
// 		}
//
// 		// AVX256
// 		if (__check_isa_support(__IA_SUPPORT_VECTOR256)) {
// 			_init_AVX256();
//
// 			if (!loggedSupport) {
// 				printf("Pattern scans are using AVX256\n");
// 				loggedSupport = true;
// 			}
//
// 			return;
// 		}
//
// 		if (!loggedSupport) {
// 			printf("Pattern scans are not using enhanced ISA\n");
// 			loggedSupport = true;
// 		}
//
// 		// Slow/fallback
// 		_init_default();
// 	}
//
// 	Pattern(const char* pattern, const size_t reloffStart, const size_t reloffLen) : Pattern(pattern) {
// 		m_isReloff = true;
// 		m_reloffStart = reloffStart;
// 		m_reloffLength = reloffLen;
// 	}
//
// 	void _init_AVX256() {
// 		uint8_t buf[32]{};
// 		size_t bufIdx{};
// 		uint32_t bufMask{ 0 };
//
// 		bool setFirst = false;
//
// 		const auto toByte = [](const char c) -> uint8_t {
// 			if (c >= '0' && c <= '9') {
// 				return c - '0';
// 			}
//
// 			if (c >= 'A' && c <= 'F') {
// 				return c - 'A' + 10;
// 			}
//
// 			if (c >= 'a' && c <= 'f') {
// 				return c - 'a' + 10;
// 			}
//
// 			return 0;
// 			};
//
// 		for (size_t i = 0; i < m_pattern.size(); i++) {
// 			if (m_pattern[i] == ' ') {
// 				continue;
// 			}
//
// 			// Not a wildcard
// 			if (m_pattern[i] != '?') {
// 				bufMask |= 1ui64 << bufIdx;
//
// 				if (i < m_pattern.size() - 1) {
// 					const auto byte = (toByte(m_pattern[i]) << 4) | toByte(m_pattern[i + 1]);
//
// 					if (!setFirst) {
// 						m_avx256_lookahead = _mm256_set1_epi8(static_cast<int8_t>(byte));
// 						m_first_offset = bufIdx;
// 						setFirst = true;
// 					}
//
// 					buf[bufIdx] = byte;
// 					i++;
// 				}
// 			}
//
// 			// Flush
// 			if (++bufIdx == 32) {
// 				this->m_avx256_vec.emplace_back(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&buf[0])));
// 				this->m_avx256_mask.push_back(bufMask);
//
// 				memset(&buf[0], 0, 32);
// 				bufMask = {};
// 				bufIdx = 0;
// 			}
// 		}
//
// 		// Flush
// 		if (bufIdx != 0) {
// 			this->m_avx256_vec.emplace_back(_mm256_loadu_si256(reinterpret_cast<const __m256i*>(&buf[0])));
// 			this->m_avx256_mask.push_back(bufMask);
// 		}
// 	}
//
// 	void _init_AVX512() {
// 		uint8_t buf[64]{};
// 		size_t bufIdx{};
// 		uint64_t bufMask{ 0 };
//
// 		bool setFirst = false;
//
// 		const auto toByte = [](const char c) -> uint8_t {
// 			if (c >= '0' && c <= '9') {
// 				return c - '0';
// 			}
//
// 			if (c >= 'A' && c <= 'F') {
// 				return c - 'A' + 10;
// 			}
//
// 			if (c >= 'a' && c <= 'f') {
// 				return c - 'a' + 10;
// 			}
//
// 			return 0;
// 			};
//
// 		for (size_t i = 0; i < m_pattern.size(); i++) {
// 			if (m_pattern[i] == ' ') {
// 				continue;
// 			}
//
// 			// Not a wildcard
// 			if (m_pattern[i] != '?') {
// 				bufMask |= 1ui64 << bufIdx;
//
// 				if (i < m_pattern.size() - 1) {
// 					const auto byte = (toByte(m_pattern[i]) << 4) | toByte(m_pattern[i + 1]);
//
// 					if (!setFirst) {
// 						m_avx512_lookahead = _mm512_set1_epi8(static_cast<int8_t>(byte));
// 						m_first_offset = bufIdx;
// 						setFirst = true;
// 					}
//
// 					buf[bufIdx] = byte;
// 					i++;
// 				}
// 			}
//
// 			// Flush
// 			if (++bufIdx == 64) {
// 				this->m_avx512_vec.emplace_back(_mm512_loadu_epi8(&buf[0]));
// 				this->m_avx512_mask.push_back(bufMask);
//
// 				memset(&buf[0], 0, 64);
// 				bufMask = {};
// 				bufIdx = 0;
// 			}
// 		}
//
// 		// Flush
// 		if (bufIdx != 0) {
// 			this->m_avx512_vec.emplace_back(_mm512_loadu_epi8(&buf[0]));
// 			this->m_avx512_mask.push_back(bufMask);
// 		}
// 	}
//
// 	void _init_default() {
// 		bool setFirst = false;
// 		const auto toByte = [](const char c) -> uint8_t {
// 			if (c >= '0' && c <= '9') {
// 				return c - '0';
// 			}
//
// 			if (c >= 'A' && c <= 'F') {
// 				return c - 'A' + 10;
// 			}
//
// 			return 0;
// 			};
//
// 		size_t bufIdx = 0;
// 		for (size_t i = 0; i < m_pattern.size(); i++) {
// 			if (m_pattern[i] == ' ') {
// 				continue;
// 			}
//
// 			// Not a wildcard
// 			if (m_pattern[i] != '?') {
// 				if (i < m_pattern.size() - 1) {
// 					const auto byte = (toByte(m_pattern[i]) << 4) | toByte(m_pattern[i + 1]);
//
// 					if (!setFirst) {
// 						m_first_offset = bufIdx;
// 						m_first = byte;
// 						setFirst = true;
// 					}
//
// 					m_default_bytes.push_back(byte);
// 					m_default_mask.push_back(false);
//
// 					i++;
// 				}
// 			}
// 			else {
// 				m_default_bytes.push_back(0);
// 				m_default_mask.push_back(true);
// 			}
//
// 			bufIdx++;
// 		}
// 	}
//
// 	std::tuple<uint8_t*, size_t> _check_AVX256(const void* _addr) const {
// 		const auto addr = const_cast<uint8_t*>(static_cast<const uint8_t*>(_addr));
//
// 		// Default to skip `width` bytes
// 		// If starting byte is found in scan, this will be reduced to start there
// 		size_t nextStart = 32;
//
// 		for (size_t i = 0; i < m_avx256_mask.size(); i++) {
// 			const auto offset = (i * 32);
// 			const auto ptr = reinterpret_cast<const __m256i*>(addr + offset);
// 			const auto mem = _mm256_loadu_si256(ptr);
//
// 			// Get a bitmask of bytes that don't match
// 			const auto cmp = _mm256_cmpeq_epi8(m_avx256_vec[i], mem);
// 			const auto res = (_mm256_movemask_epi8(cmp) ^ UINT32_MAX) & m_avx256_mask[i];
//
// 			if (i == 0) {
// 				// Scan bytes for any matching first byte in pattern
// 				// Count starting from LSB to first '1' bit
// 				// Will be 32 if not found, otherwise next start value
// 				constexpr auto mask = (UINT32_MAX - 1);
// 				const auto lookahead_cmp = _mm256_cmpeq_epi8(m_avx256_lookahead, mem);
// 				const auto lookahead_result = _mm256_movemask_epi8(lookahead_cmp) & mask;
//
// 				if (lookahead_result > 0) {
// 					const auto bit = _tzcnt_u32(lookahead_result);
//
// 					// < 32 means it was found
// 					// In case of wildcards in first bytes of pattern,
// 					// need to adjust next starting pos based on first actual byte
// 					// * but only if nextStart > first real byte offset
// 					// Pattern: ?? ?? AA
// 					// Mem: xx xx xx xx xx xx AA
// 					// Next start would be 6, but pattern starts with two wildcards
// 					// Adjust nextStart to 4
// 					if (bit < 32 && bit > m_first_offset) {
// 						nextStart = bit - m_first_offset;
// 					}
// 				}
// 			}
//
// 			// Found a mismatch
// 			if (res > 0) {
// 				return { nullptr, nextStart };
// 			}
// 		}
//
// 		// Pattern is a for a RIP relative offset
// 		// AB CD ? ? ? ? EF GH
// 		// Where ? ? ? ? points to an RIP relative address
// 		if (m_isReloff) {
// 			const auto relOff = *reinterpret_cast<int32_t*>(addr + m_reloffStart);
// 			const auto rip = (addr + m_reloffStart + m_reloffLength);
// 			const auto ptr = rip + relOff;
// 			return { ptr, nextStart };
// 		}
//
// 		// Matches at start address
// 		return { addr, nextStart };
// 	}
//
// 	std::tuple<uint8_t*, size_t> _check_AVX512(const void* _addr) const {
// 		const auto addr = const_cast<uint8_t*>(static_cast<const uint8_t*>(_addr));
//
// 		// Default to skip `width` bytes
// 		// If starting byte is found in scan, this will be reduced to start there
// 		size_t nextStart = 64;
//
// 		for (size_t i = 0; i < m_avx512_mask.size(); i++) {
// 			const auto offset = (i * 64);
// 			const auto mem = _mm512_loadu_epi8(addr + offset);
//
// 			// Get a bitmask of bytes that don't match
// 			const auto res = _mm512_mask_cmpneq_epi8_mask(m_avx512_mask[i], m_avx512_vec[i], mem);
//
// 			if (i == 0) {
// 				// Scan bytes for any matching first byte in pattern
// 				// Count starting from LSB to first '1' bit
// 				// Will be 32 if not found, otherwise next start value
// 				constexpr auto mask = (UINT64_MAX - 1);
// 				const auto lookahead_result = _mm512_mask_cmpeq_epi8_mask(mask, m_avx512_lookahead, mem);
//
// 				if (lookahead_result > 0) {
// 					const auto bit = _tzcnt_u64(lookahead_result);
//
// 					// < 32 means it was found
// 					// In case of wildcards in first bytes of pattern,
// 					// need to adjust next starting pos based on first actual byte
// 					// * but only if nextStart > first real byte offset
// 					// Pattern: ?? ?? AA
// 					// Mem: xx xx xx xx xx xx AA
// 					// Next start would be 6, but pattern starts with two wildcards
// 					// Adjust nextStart to 4
// 					if (bit < 64 && bit > m_first_offset) {
// 						nextStart = bit - m_first_offset;
// 					}
// 				}
// 			}
//
// 			// Found a mismatch
// 			if (res > 0) {
// 				return { nullptr, nextStart };
// 			}
// 		}
//
// 		// Pattern is a for a RIP relative offset
// 		// AB CD ? ? ? ? EF GH
// 		// Where ? ? ? ? points to an RIP relative address
// 		if (m_isReloff) {
// 			const auto relOff = *reinterpret_cast<int32_t*>(addr + m_reloffStart);
// 			const auto rip = (addr + m_reloffStart + m_reloffLength);
// 			const auto ptr = rip + relOff;
// 			return { ptr, nextStart };
// 		}
//
// 		// Matches at start address
// 		return { addr, nextStart };
// 	}
//
// 	std::tuple<uint8_t*, size_t> _check_default(const void* _addr) const {
// 		const auto addr = const_cast<uint8_t*>(static_cast<const uint8_t*>(_addr));
//
// 		// Default to skip `width` bytes
// 		// If starting byte is found in scan, this will be reduced to start there
// 		bool setNextStart = false;
// 		size_t nextStart = 1;
//
// 		for (size_t i = 0; i < m_default_bytes.size(); i++) {
// 			const auto mem = addr[i];
//
// 			if (mem == m_first) {
// 				if (i > 0) {}
// 			}
//
// 			// Found next potential pattern starting point
// 			if (!setNextStart && mem == m_first && i > 0 && i > m_first_offset) {
// 				nextStart = i - m_first_offset;
// 				setNextStart = true;
// 			}
//
// 			if (!m_default_mask[i] && mem != m_default_bytes[i]) {
// 				return { nullptr, nextStart };
// 			}
// 		}
//
// 		// Pattern is a for a RIP relative offset
// 		// AB CD ? ? ? ? EF GH
// 		// Where ? ? ? ? points to an RIP relative address
// 		if (m_isReloff) {
// 			const auto relOff = *reinterpret_cast<int32_t*>(addr + m_reloffStart);
// 			const auto rip = (addr + m_reloffStart + m_reloffLength);
// 			const auto ptr = rip + relOff;
// 			return { ptr, nextStart };
// 		}
//
// 		// Matches at start address
// 		return { addr, nextStart };
// 	}
//
// 	// Returns pointer if found + minimum number of bytes until pattern should be scanned again
// 	std::tuple<uint8_t*, size_t> check(const void* _addr) const {
// 		if (__check_isa_support(__IA_SUPPORT_VECTOR512)) {
// 			return _check_AVX512(_addr);
// 		}
//
// 		// AVX256
// 		if (__check_isa_support(__IA_SUPPORT_VECTOR256)) {
// 			return _check_AVX256(_addr);
// 		}
//
// 		// Fallback
// 		return _check_default(_addr);
// 	}
// };


struct Pattern {
	std::vector<uint8_t> bytes{};
	std::vector<bool> mask{};

	std::string m_pattern;

	size_t m_first{};
	size_t m_first_offset;

	bool m_isReloff = false;
	size_t m_reloffStart = 0;
	size_t m_reloffLength = 0;

	// ReSharper disable once CppNonExplicitConvertingConstructor
	Pattern(const char* pattern) {
		m_pattern = pattern;

		bool setFirst = false;
		const auto toByte = [](const char c) -> uint8_t {
			if (c >= '0' && c <= '9') {
				return c - '0';
			}

			if (c >= 'A' && c <= 'F') {
				return c - 'A' + 10;
			}

			return 0;
			};

		size_t bufIdx = 0;
		for (size_t i = 0; i < m_pattern.size(); i++) {
			if (pattern[i] == ' ') {
				continue;
			}

			// Not a wildcard
			if (pattern[i] != '?') {
				if (i < m_pattern.size() - 1) {
					const auto byte = (toByte(pattern[i]) << 4) | toByte(pattern[i + 1]);

					if (!setFirst) {
						m_first_offset = bufIdx;
						m_first = byte;
						setFirst = true;
					}

					bytes.push_back(byte);
					mask.push_back(false);

					i++;
				}
			}
			else {
				bytes.push_back(0);
				mask.push_back(true);
			}

			bufIdx++;
		}
	}

	Pattern(const char* pattern, const size_t reloffStart, const size_t reloffLen) : Pattern(pattern) {
		m_isReloff = true;
		m_reloffStart = reloffStart;
		m_reloffLength = reloffLen;
	}

	// Returns pointer if found + minimum number of bytes until pattern should be scanned again
	std::tuple<uint8_t*, size_t> check(const void* _addr) const {
		const auto addr = const_cast<uint8_t*>(static_cast<const uint8_t*>(_addr));

		// Default to skip `width` bytes
		// If starting byte is found in scan, this will be reduced to start there
		bool setNextStart = false;
		size_t nextStart = 1;

		for (size_t i = 0; i < bytes.size(); i++) {
			const auto mem = addr[i];

			if (mem == m_first) {
				if (i > 0) {
				}
			}

			// Found next potential pattern starting point
			if (!setNextStart && mem == m_first && i > 0 && i > m_first_offset) {
				nextStart = i - m_first_offset;
				setNextStart = true;
			}

			if (!mask[i] && mem != bytes[i]) {
				return { nullptr, nextStart };
			}
		}

		// Pattern is a for a RIP relative offset
		// AB CD ? ? ? ? EF GH
		// Where ? ? ? ? points to an RIP relative address
		if (m_isReloff) {
			const auto relOff = *reinterpret_cast<int32_t*>(addr + m_reloffStart);
			const auto rip = (addr + m_reloffStart + m_reloffLength);
			const auto ptr = rip + relOff;
			return { ptr, nextStart };
		}

		// Matches at start address
		return { addr, nextStart };
	}
};

namespace Scanner {
	using handler_t = std::function<void(uint8_t*)>;
	using pattern_info_t = std::tuple<Pattern, handler_t>;
	inline std::vector<pattern_info_t> handlers{};

	template <typename T = uint8_t*>
	void Add(const Pattern& pat, T* ptr) {
		handlers.push_back({
			pat, [=](uint8_t* addr) {
				*ptr = reinterpret_cast<T>(addr);
			}
		});
	}

	template <typename T = uint8_t*>
	void Add(const Pattern& pat, const handler_t& callback) {
		handlers.emplace_back(pat, callback);
	}

	template <typename F>
	void AddPrologueHook(const Pattern& pat, F& hook, F* * oFunc) {
		handlers.emplace_back(pat, [=](uint8_t* addr) {
			HookLib::CreatePrologueHook(addr, hook, oFunc);
		});
	}

	inline void AddInlineHook(const Pattern& pat, void(*hook)()) {
		handlers.emplace_back(pat, [=](uint8_t* addr) {
			HookLib::CreateInlineHook(addr, hook);
		});
	}

	inline void AddInlineHook(const Pattern& pat, void(*hook)(uint8_t*)) {
		handlers.emplace_back(pat, [=](uint8_t* addr) {
			HookLib::CreateInlineHook(addr, hook);
		});
	}

	inline void Scan() {
		MODULEINFO info{};
		if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(nullptr), &info, sizeof(info))) {
			constexpr auto emsg = "GetModuleInformation returned FALSE.\n";
			puts(emsg);
			throw std::runtime_error(std::string(emsg));
		}

		std::vector<std::tuple<size_t, pattern_info_t*>> nextIndices{};
		for (auto& handler : handlers) {
			nextIndices.emplace_back(0, &handler);
		}

		const auto base = static_cast<uint8_t*>(info.lpBaseOfDll);
		const auto size = static_cast<size_t>(info.SizeOfImage);

		for (auto curAddr = base; curAddr <= (base + size - 32); curAddr++) {
			for (auto& [next, ph] : nextIndices) {
				// Already found
				if (next == UINT32_MAX) {
					continue;
				}

				if (next == 0) {
					const auto& [pattern, callback] = *ph;
					const auto [addr, skip] = pattern.check(curAddr);

					if (addr) {
						printf("Found pattern at 0x%p : %s\n", static_cast<void*>(addr), pattern.m_pattern.c_str());

						// Skip in future
						next = UINT32_MAX;
						callback(addr);
					}
					else {
						next = skip - 1;
					}
				}
				else {
					next--;
				}
			}
		}

		for (auto& [next, ph] : nextIndices) {
			// Already found
			if (next != UINT32_MAX) {
				const auto& [pattern, callback] = *ph;
				printf("Failed to find pattern: %s\n", pattern.m_pattern.c_str());
			}
		}
	}
};

inline uint8_t* ScanPattern(const char* pattern) {
	MODULEINFO info{};
	if (!GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(nullptr), &info, sizeof(info))) {
		char eMsg[512] = {};
		(void)sprintf_s(eMsg, 512, "Failed to find pattern '%s'\nGetModuleInformation returned FALSE.\n", pattern);
		printf("%s\n", eMsg);
		throw std::runtime_error(std::string(eMsg));
	}

	const auto base = static_cast<uint8_t*>(info.lpBaseOfDll);
	const auto size = static_cast<size_t>(info.SizeOfImage);
	printf("Base: 0x%p\nSize: %llx\n", static_cast<void*>(base), size);

	Pattern pat{pattern};
	for (auto curAddr = base; curAddr <= (base + size - 64);) {
		const auto [result, next] = pat.check(curAddr);
		if (result) {
			return curAddr;
		}

		curAddr += next;
	}

	return nullptr;
}
