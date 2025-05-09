#pragma once
#include <cinttypes>
#include <cstdio>
#include <unordered_set>
#include <ranges>

#include "Zydis/Zydis.h"

#define HOOK_DEBUG false

namespace HookLib {
	inline void PrintAsm(uint8_t* address, size_t length) {
		// Initialize decoder context
		ZydisDecoder decoder;
		ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

		// Initialize formatter. Only required when you actually plan to do instruction
		// formatting ("disassembling"), like we do here
		ZydisFormatter formatter;
		ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

		// Loop over the instructions in our buffer.
		// The runtime-address (instruction pointer) is chosen arbitrary here in order to better
		// visualize relative addressing
		ZyanU64 runtime_address = reinterpret_cast<ZyanU64>(address);
		ZyanUSize offset = 0;
		ZydisDecodedInstruction instruction;
		ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
		while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, address + offset, length - offset,
			&instruction, operands))) {
			// Print current instruction pointer.
			printf("%016" PRIX64 "  ", runtime_address);

			// Format & print the binary instruction structure to human-readable format
			char buffer[256];
			ZydisFormatterFormatInstruction(&formatter, &instruction, operands,
				instruction.operand_count_visible, buffer, sizeof(buffer), runtime_address, ZYAN_NULL);
			puts(buffer);

			offset += instruction.length;
			runtime_address += instruction.length;
		}
	}

	namespace Asm {
		inline size_t CalculateClobberSize(const uint8_t* address, const size_t overwriteSize) {
			ZydisDecoder decoder;
			ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

			ZyanUSize offset = 0;
			ZydisDecodedInstruction instruction;
			ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];

			while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, address + offset, 50, &instruction, operands))) {
				offset += instruction.length;

				if (offset > overwriteSize) {
					return offset;
				}
			}

			return 0;
		}

		inline std::vector<uint8_t> Encode(const ZydisEncoderRequest& req) {
			ZyanU8 encoded_instruction[ZYDIS_MAX_INSTRUCTION_LENGTH];
			ZyanUSize encoded_length = sizeof(encoded_instruction);

			if (ZYAN_FAILED(ZydisEncoderEncodeInstruction(&req, encoded_instruction, &encoded_length))) {
				return {};
			}

			std::vector<uint8_t> result{};
			for (ZyanUSize i = 0; i < encoded_length; ++i) {
				result.emplace_back(encoded_instruction[i]);
			}
			return result;
		}

		inline std::vector<uint8_t> Mov(const ZydisRegister r1, const ZydisRegister r2) {
			ZydisEncoderRequest req = {};

			req.mnemonic = ZYDIS_MNEMONIC_MOV;
			req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
			req.operand_count = 2;
			req.operands[0].type = ZYDIS_OPERAND_TYPE_REGISTER;
			req.operands[0].reg.value = r1;
			req.operands[1].type = ZYDIS_OPERAND_TYPE_REGISTER;
			req.operands[0].reg.value = r2;

			return Encode(req);
		}

		inline std::vector<uint8_t> Mov(const ZydisRegister r1, const uint64_t imm1) {
			ZydisEncoderRequest req = {};

			req.mnemonic = ZYDIS_MNEMONIC_MOV;
			req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
			req.operand_count = 2;
			req.operands[0].type = ZYDIS_OPERAND_TYPE_REGISTER;
			req.operands[0].reg.value = r1;
			req.operands[1].type = ZYDIS_OPERAND_TYPE_IMMEDIATE;
			req.operands[1].imm.u = imm1;

			return Encode(req);
		}

		inline std::vector<uint8_t> Jmp(const ZydisRegister r1) {
			ZydisEncoderRequest req = {};

			req.mnemonic = ZYDIS_MNEMONIC_JMP;
			req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
			req.operand_count = 1;
			req.operands[0].type = ZYDIS_OPERAND_TYPE_REGISTER;
			req.operands[0].reg.value = r1;

			return Encode(req);
		}

		inline std::vector<uint8_t> Call(const ZydisRegister r1) {
			ZydisEncoderRequest req = {};

			req.mnemonic = ZYDIS_MNEMONIC_CALL;
			req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
			req.operand_count = 1;
			req.operands[0].type = ZYDIS_OPERAND_TYPE_REGISTER;
			req.operands[0].reg.value = r1;

			return Encode(req);
		}

		inline std::vector<uint8_t> Jmp(const uint64_t addr) {
			std::vector<uint8_t> trampoline = {};
			std::ranges::copy(Mov(ZYDIS_REGISTER_R10, addr), std::back_inserter(trampoline));
			std::ranges::copy(Jmp(ZYDIS_REGISTER_R10), std::back_inserter(trampoline));
			return trampoline;
		}

		inline std::vector<uint8_t> JmpRel(const int32_t reloff) {
			ZydisEncoderRequest req = {};

			req.mnemonic = ZYDIS_MNEMONIC_JMP;
			req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
			req.operand_count = 1;
			req.operands[0].type = ZYDIS_OPERAND_TYPE_IMMEDIATE;
			req.operands[0].imm.s = reloff;

			return Encode(req);
		}

		inline std::vector<uint8_t> Call(const uint64_t addr) {
			std::vector<uint8_t> trampoline = {};
			std::ranges::copy(Mov(ZYDIS_REGISTER_R10, addr), std::back_inserter(trampoline));
			std::ranges::copy(Call(ZYDIS_REGISTER_R10), std::back_inserter(trampoline));
			return trampoline;
		}

		inline std::vector<uint8_t> CallRel(const int32_t reloff) {
			ZydisEncoderRequest req = {};

			req.mnemonic = ZYDIS_MNEMONIC_CALL;
			req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
			req.operand_count = 1;
			req.operands[0].type = ZYDIS_OPERAND_TYPE_IMMEDIATE;
			req.operands[0].imm.s = reloff;

			return Encode(req);
		}

		inline std::vector<uint8_t> Push(const ZydisRegister r1) {
			ZydisEncoderRequest req = {};

			req.mnemonic = ZYDIS_MNEMONIC_PUSH;
			req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
			req.operand_count = 1;
			req.operands[0].type = ZYDIS_OPERAND_TYPE_REGISTER;
			req.operands[0].reg.value = r1;

			return Encode(req);
		}

		inline std::vector<uint8_t> Pop(const ZydisRegister r1) {
			ZydisEncoderRequest req = {};

			req.mnemonic = ZYDIS_MNEMONIC_POP;
			req.machine_mode = ZYDIS_MACHINE_MODE_LONG_64;
			req.operand_count = 1;
			req.operands[0].type = ZYDIS_OPERAND_TYPE_REGISTER;
			req.operands[0].reg.value = r1;

			return Encode(req);
		}

		template <typename Collection>
		inline std::vector<uint8_t> PushMultiReg(const Collection& registers) {
			std::vector<uint8_t> result{};
			for (const auto& reg : registers) {
				std::ranges::copy(Push(reg), std::back_inserter(result));
			}
			return result;
		}

		template <typename Collection>
		inline std::vector<uint8_t> PopMultiReg(const Collection& registers) {
			std::vector<uint8_t> result{};
			for (const auto& reg : registers) {
				std::ranges::copy(Pop(reg), std::back_inserter(result));
			}
			return result;
		}
	}

	namespace Detail {
		constexpr size_t HOOK_BUFFER_LENGTH = 16384;
		inline uint8_t* hookBuffer = nullptr;
		inline size_t hookBufferIdx = 0;

		const std::vector<ZydisRegister> VOLATILE_REGISTERS = {
			ZYDIS_REGISTER_RAX,
			ZYDIS_REGISTER_RCX,
			ZYDIS_REGISTER_RDX,
			ZYDIS_REGISTER_R8,
			ZYDIS_REGISTER_R9,
			ZYDIS_REGISTER_R10,
			ZYDIS_REGISTER_R11,

			ZYDIS_REGISTER_XMM0,
			ZYDIS_REGISTER_XMM1,
			ZYDIS_REGISTER_XMM2,
			ZYDIS_REGISTER_XMM3,
			ZYDIS_REGISTER_XMM4,
			ZYDIS_REGISTER_XMM5,
		};

		inline void InitHookBuffer() {
			hookBuffer = static_cast<uint8_t*>(VirtualAlloc(nullptr, HOOK_BUFFER_LENGTH, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
		}

		inline void RealignHookBuffer() {
			hookBufferIdx = (hookBufferIdx + 7) & ~7;
		}

		inline void Emit(const std::vector<uint8_t>& bytes) {
			memcpy(&hookBuffer[hookBufferIdx], bytes.data(), bytes.size());
			hookBufferIdx += bytes.size();
		}

		inline void Emit(const std::vector<uint8_t>&& bytes) {
			memcpy(&hookBuffer[hookBufferIdx], bytes.data(), bytes.size());
			hookBufferIdx += bytes.size();
		}

		template <typename... Args>
		void Emit(const std::vector<uint8_t>& bytes, Args&... rest) {
			Emit(bytes);
			Emit(rest...);
		}

		template <typename... Args>
		void Emit(const std::vector<uint8_t>&& bytes, Args&&... rest) {
			Emit(bytes);
			Emit(rest...);
		}

		inline void Emit(uint8_t* addr, const std::vector<uint8_t>&& bytes) {
			DWORD flOldProtect;
			VirtualProtect(addr, bytes.size(), PAGE_EXECUTE_READWRITE, &flOldProtect);
			memcpy(addr, bytes.data(), bytes.size());
			VirtualProtect(addr, bytes.size(), flOldProtect, nullptr);
		}

		inline void Emit(uint8_t* addr, const std::vector<uint8_t>& bytes) {
			DWORD flOldProtect;
			VirtualProtect(addr, bytes.size(), PAGE_EXECUTE_READWRITE, &flOldProtect);
			memcpy(addr, bytes.data(), bytes.size());
			VirtualProtect(addr, bytes.size(), flOldProtect, nullptr);
		}

		template <typename... Args>
		void Emit(uint8_t* addr, const std::vector<uint8_t>&& bytes, Args&&... rest) {
			Emit(addr, bytes);
			Emit(addr, rest);
		}

		template <typename... Args>
		void Emit(uint8_t* addr, const std::vector<uint8_t>& bytes, Args&&... rest) {
			Emit(addr, bytes);
			Emit(addr, rest);
		}

		inline std::unordered_set<ZydisRegister> GetDependentRegisters(const uint8_t* address, const size_t maxSearch = 1024) {
			std::unordered_set<ZydisRegister> unresolvedRegisters = {};
			for (const auto& reg : VOLATILE_REGISTERS) {
				unresolvedRegisters.insert(reg);
			}

			std::unordered_set<ZydisRegister> readRegisters{};
			std::unordered_set<ZydisRegister> writtenRegisters{};

			// Initialize decoder context
			ZydisDecoder decoder;
			ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

			// Initialize formatter. Only required when you actually plan to do instruction
			// formatting ("disassembling"), like we do here
			ZydisFormatter formatter;
			ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

			// Loop over the instructions in our buffer.
			// The runtime-address (instruction pointer) is chosen arbitrary here in order to better
			// visualize relative addressing
			ZyanU64 runtime_address = reinterpret_cast<ZyanU64>(address);
			ZyanUSize offset = 0;
			const ZyanUSize length = maxSearch;
			ZydisDecodedInstruction instruction;
			ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
			while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, address + offset, length - offset,
				&instruction, operands))) {
				// // Print current instruction pointer.

				for (int i = 0; i < instruction.operand_count; i++) {
					const auto& operand = operands[i];
					const auto& reg = operand.reg.value;

					// Skip registers we already resolved...
					if (!unresolvedRegisters.contains(reg)) {
						continue;
					}

					// Registers that are read need to be tracked / saved
					if (operand.actions & ZYDIS_OPERAND_ACTION_READ) {
						readRegisters.insert(reg);
#if HOOK_DEBUG
						printf("[READ]  %016" PRIX64 "  ", runtime_address);

						// Format & print the binary instruction structure to human-readable format
						char buffer[256];
						ZydisFormatterFormatInstruction(&formatter, &instruction, operands,
							instruction.operand_count_visible, buffer, sizeof(buffer), runtime_address, ZYAN_NULL);
						puts(buffer);
#endif
					}

					// Written registers don't need to be saved
					else if (operand.actions & ZYDIS_OPERAND_ACTION_WRITE) {
						writtenRegisters.insert(reg);
#if HOOK_DEBUG
						printf("[WRITE] %016" PRIX64 "  ", runtime_address);

						// Format & print the binary instruction structure to human-readable format
						char buffer[256];
						ZydisFormatterFormatInstruction(&formatter, &instruction, operands,
							instruction.operand_count_visible, buffer, sizeof(buffer), runtime_address, ZYAN_NULL);
						puts(buffer);
#endif
					}

					// Not read from or written to
					else {
						continue;
					}

					// Resolved..
					unresolvedRegisters.erase(reg);
				}

				offset += instruction.length;
				runtime_address += instruction.length;
			}

			return unresolvedRegisters;
		}

		inline void CopyReplacedBytes(uint8_t* address, uint8_t* dst, size_t* idx, size_t length) {
			std::vector<uint8_t> result{};

			ZydisDecoder decoder;
			ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_64, ZYDIS_STACK_WIDTH_64);

			// Initialize formatter. Only required when you actually plan to do instruction
			// formatting ("disassembling"), like we do here
			ZydisFormatter formatter;
			ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);

			ZyanUSize offset = 0;
			ZydisDecodedInstruction instruction;
			ZydisDecodedOperand operands[ZYDIS_MAX_OPERAND_COUNT];
			ZyanU64 runtime_address = reinterpret_cast<ZyanU64>(address);

			while (ZYAN_SUCCESS(ZydisDecoderDecodeFull(&decoder, address + offset, length, &instruction, operands))) {
				if (offset > length) {
					break;
				}

				ZydisEncoderRequest req = {};
				ZydisEncoderDecodedInstructionToEncoderRequest(&instruction, operands, instruction.operand_count, &req);

				ZyanU8 encoded_instruction[ZYDIS_MAX_INSTRUCTION_LENGTH];
				ZyanUSize encoded_length = sizeof(encoded_instruction);

				// req.mnemonic = instruction.mnemonic;
				// req.machine_mode = instruction.machine_mode;
				// req.operand_count = instruction.operand_count;
				//
				// for (int i = 0; i < instruction.raw.prefix_count; i++) {
				// 	req.prefixes |= instruction.raw.prefixes[i].value;
				// }

#if HOOK_DEBUG
				printf("[WRITE] %016" PRIX64 "  ", runtime_address);

				// Format & print the binary instruction structure to human-readable format
				char buffer[256];
				ZydisFormatterFormatInstruction(&formatter, &instruction, operands,
					instruction.operand_count_visible, buffer, sizeof(buffer), runtime_address, ZYAN_NULL);
				puts(buffer);
#endif

				// for (int i = 0; i < operands->size; i++) {
				// 	const auto& operand = operands[i];
				// 	auto& op = req.operands[i];
				// 	op.type = operand.type;
				//
				// 	if (operand.type == ZYDIS_OPERAND_TYPE_POINTER) {
				// 		op.ptr.segment = operand.ptr.segment;
				// 		op.ptr.offset = operand.ptr.offset;
				// 	} else {
				// 		if (operand.type == ZYDIS_OPERAND_TYPE_REGISTER) {
				// 			op.reg.value = operand.reg.value;
				// 		}
				//
				// 		else if (operand.type == ZYDIS_OPERAND_TYPE_MEMORY) {
				// 			op.mem.base = operand.mem.base;
				// 			op.mem.index = operand.mem.index;
				// 			op.mem.scale = operand.mem.scale;
				// 			op.mem.displacement = operand.mem.disp.value;
				// 			op.mem.size = operand.size;
				// 		}
				//
				// 		else if (operand.type == ZYDIS_OPERAND_TYPE_IMMEDIATE) {
				// 			if (operand.imm.is_relative) {
				// 				if (operand.imm.is_signed) {
				// 					const auto abs = reinterpret_cast<int64_t>(address + offset + instruction.length) + operand.imm.value.s;
				// 					const auto rel = abs - (reinterpret_cast<int64_t>(idx) + instruction.length);
				// 					op.imm.s = rel;
				// 				} else {
				// 					const auto abs = reinterpret_cast<uint64_t>(address + offset + instruction.length) + operand.imm.value.u;
				// 					const auto rel = abs - (reinterpret_cast<uint64_t>(idx) + instruction.length);
				// 					op.imm.u = rel;
				// 				}
				// 			} else {
				// 				if (operand.imm.is_signed) {
				// 					op.imm.s = operand.imm.value.s;
				// 				} else {
				// 					op.imm.u = operand.imm.value.u;
				// 				}
				// 			}
				// 		}
				// 	}
				// }

				offset += instruction.length;
				runtime_address += instruction.length;

				if (ZYAN_FAILED(ZydisEncoderEncodeInstruction(&req, encoded_instruction, &encoded_length))) {
					printf("Failed to encode instruction\n");
					continue;
				}

				for (ZyanUSize e = 0; e < encoded_length; ++e) {
					dst[*idx] = encoded_instruction[e];
					(*idx)++;
				}
			}

			SuspendThread(GetCurrentThread());
		}
	}

	inline void Init() {
		constexpr auto module = "OblivionRemastered-Win64-Shipping.exe";
		const auto hmod = GetModuleHandleA(module);
		if (!hmod) {
			constexpr auto emsg = "GetModuleHandleA returned nullptr.\n";
			puts(emsg);
			throw std::runtime_error(std::string(emsg));
		}

		MODULEINFO info{};
		if (!GetModuleInformation(GetCurrentProcess(), hmod, &info, sizeof(info))) {
			constexpr auto emsg = "GetModuleInformation returned FALSE.\n";
			puts(emsg);
			throw std::runtime_error(std::string(emsg));
		}

		const auto base = static_cast<uint8_t*>(info.lpBaseOfDll);
		uint8_t* pBuf{ nullptr };

		SYSTEM_INFO si;
		GetSystemInfo(&si);
		const auto pageSize = si.dwPageSize;

		for (const auto dir : { +1, -1 }) {
			constexpr size_t step = 65536;

			for (int64_t offset = step; offset < 0x80000000; offset += step) {
				const auto curAddr = base + (dir * offset);

				MEMORY_BASIC_INFORMATION mbi;
				if (VirtualQuery(curAddr, &mbi, sizeof(mbi)) && mbi.State == MEM_FREE && mbi.RegionSize >= pageSize) {
					pBuf = static_cast<uint8_t*>(VirtualAlloc(mbi.BaseAddress, pageSize, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE));
					if (pBuf) {
						break;
					}
				}
			}

			if (pBuf) {
				break;
			}
		}

		if (!pBuf) {
			throw std::runtime_error("Failed to allocate hook buffer.");
		}

		Detail::hookBuffer = pBuf;
	}

	inline int32_t CalcReloff(const uint8_t* source, const uint8_t* dest) {
		return static_cast<int32_t>(reinterpret_cast<int64_t>(dest) - reinterpret_cast<int64_t>(source));
	}

	template <typename T>
	void CreatePrologueHook(uint8_t* address, T& hook, T** oFunc) {
		const auto bufInit = Detail::hookBufferIdx;
		auto& hookBuffer = Detail::hookBuffer;
		auto& hookBufferIdx = Detail::hookBufferIdx;

		const auto clobberSize = Asm::CalculateClobberSize(address, 5);

		Detail::Emit(Asm::Jmp(reinterpret_cast<uint64_t>(hook)));
		memcpy(&hookBuffer[hookBufferIdx], address, clobberSize);
		if (oFunc) {
			*oFunc = reinterpret_cast<T*>(&hookBuffer[hookBufferIdx]);
		}
		hookBufferIdx += clobberSize;

		Detail::Emit(address, Asm::JmpRel(CalcReloff(address + 5, &hookBuffer[bufInit])));
		Detail::Emit(Asm::JmpRel(CalcReloff(&hookBuffer[hookBufferIdx] + 5, address + clobberSize)));
		Detail::RealignHookBuffer();

#if HOOK_DEBUG
		printf("Clobber size: %llu\n", clobberSize);

		printf("Hook location: \n");
		PrintAsm(address, 15);

		printf("Orig tramp: \n");
		PrintAsm(&hookBuffer[bufInit], hookBufferIdx - bufInit);
#endif
	}

	template <typename T>
	void CreatePrologueHook(uint8_t* address, T& hook) {
		CreatePrologueHook(address, hook, static_cast<T**>(nullptr));
	}

	inline void CreateInlineHook(uint8_t* address, void (*hook)()) {
		const auto bufInit = Detail::hookBufferIdx;
		auto& hookBuffer = Detail::hookBuffer;
		auto& hookBufferIdx = Detail::hookBufferIdx;

		// Registers that get read before written in original code
		const auto dependentRegisters = Detail::GetDependentRegisters(address);

		// Save all registers
		Detail::Emit(
			Asm::PushMultiReg(dependentRegisters),
			Asm::Call(reinterpret_cast<uint64_t>(hook)),
			Asm::PopMultiReg(dependentRegisters)
		);

		// Copy replaced bytes
		const auto clobberSize = Asm::CalculateClobberSize(address, 5);
		memcpy(&hookBuffer[hookBufferIdx], address, clobberSize);
		hookBufferIdx += clobberSize;

		// Return jump
		Detail::Emit(Asm::JmpRel(CalcReloff(&hookBuffer[hookBufferIdx] + 5, address + clobberSize)));

		// Hook spot
		Detail::Emit(address, Asm::JmpRel(CalcReloff(address + 5, &hookBuffer[bufInit])));
		Detail::RealignHookBuffer();

#if HOOK_DEBUG
		printf("Hook location: \n");
		PrintAsm(address, jmpIntoTrampoline.size());

		printf("Trampoline: \n");
		PrintAsm(&hookBuffer[bufInit], hookBufferIdx - bufInit);
#endif
	}

	inline void CreateInlineHook(uint8_t* address, void (*hook)(uint8_t*)) {
		const auto bufInit = Detail::hookBufferIdx;
		auto& hookBuffer = Detail::hookBuffer;
		auto& hookBufferIdx = Detail::hookBufferIdx;

		// Registers that get read before written in original code
		const auto dependentRegisters = Detail::GetDependentRegisters(address);

		// Save all registers
		Detail::Emit(
			Asm::PushMultiReg(dependentRegisters),
			Asm::Push(ZYDIS_REGISTER_ECX),
			Asm::Mov(ZYDIS_REGISTER_ECX, ZYDIS_REGISTER_EBP),
			Asm::Call(reinterpret_cast<uint64_t>(hook)),
			Asm::Pop(ZYDIS_REGISTER_ECX),
			Asm::PopMultiReg(dependentRegisters)
		);

		// Copy replaced bytes
		const auto jmpIntoTrampoline = Asm::Jmp(reinterpret_cast<uint64_t>(&hookBuffer[bufInit]));
		const auto clobberSize = Asm::CalculateClobberSize(address, jmpIntoTrampoline.size());
		memcpy(&hookBuffer[hookBufferIdx], address, clobberSize);
		hookBufferIdx += clobberSize;

		// Return jump
		Detail::Emit(Asm::Jmp(reinterpret_cast<uint64_t>(address + clobberSize)));

		// Hook spot
		Detail::Emit(address, jmpIntoTrampoline);
		Detail::RealignHookBuffer();

#if HOOK_DEBUG
		printf("Hook location: \n");
		PrintAsm(address, jmpIntoTrampoline.size());

		printf("Trampoline: \n");
		PrintAsm(&hookBuffer[bufInit], hookBufferIdx - bufInit);
#endif
	}
}
