#pragma once

#include <array>
#include <functional>
#include <string_view>

#include "../utility/definitions.h"
#include "../mmu/mmu.h"


namespace rose_core
{
	class CPU
	{
	public:
		struct Registers;

		CPU(MMU& mmu);
		CPU(MMU& mmu, u16 programCounterStart);

		// Simulates a single m-cycle.
		bool tick();
		void tickUntilNextInstruction();

		const Registers& viewRegisters() const;

		// Instruction information
		struct Instruction
		{
			u8 opcode;
			u8 bytes;
			u8 cycles;
			std::string humanReadable;
		};

		// Opcode to Human Readable Instructions, https://meganesu.github.io/generate-gb-opcodes/
		const std::array<Instruction, 256> instr_data { {
			{0x00, 1, 1, "NOP"}, {0x01, 3, 3, "LD BC, d16"}, {0x02, 1, 2, "LD (BC), A"}, {0x03, 1, 2, "INC BC"},
			{0x04, 1, 1, "INC B"}, {0x05, 1, 1, "DEC B"}, {0x06, 2, 2, "LD B, d8"}, {0x07, 1, 1, "RLCA"},
			{0x08, 3, 5, "LD (a16), SP"}, {0x09, 1, 2, "ADD HL, BC"}, {0x0A, 1, 2, "LD A, (BC)"}, {0x0B, 1, 2, "DEC BC"},
			{0x0C, 1, 1, "INC C"}, {0x0D, 1, 1, "DEC C"}, {0x0E, 2, 2, "LD C, d8"}, {0x0F, 1, 1, "RRCA"},

			{0x10, 2, 1, "STOP"}, {0x11, 3, 3, "LD DE, d16"}, {0x12, 1, 2, "LD (DE), A"}, {0x13, 1, 2, "INC DE"},
			{0x14, 1, 1, "INC D"}, {0x15, 1, 1, "DEC D"}, {0x16, 2, 2, "LD, d8"}, {0x17, 1, 1, "RLA"},
			{0x18, 2, 3, "JR s8"}, {0x19, 1, 2, "ADD HL, DE"}, {0x1A, 1, 2, "LD A, (DE)"}, {0x1B, 1, 2, "DEC DE"},
			{0x1C, 1, 1, "INC E"}, {0x1D, 1, 1, "DEC E"}, {0x1E, 2, 2, "LD E, d8"}, {0x1F, 1, 1, "RRA"},

			// 0x20, 0x28 is 3 or 2 cycles depending on if jump occurs or not
			{0x20, 2, 3, "JR NZ, s8"}, {0x21, 3, 3, "LD HL, d16"}, {0x22, 1, 2, "LD (HL+), A"}, {0x23, 1, 2, "INC HL"},
			{0x24, 1, 1, "INC H"}, {0x25, 1, 1, "DEC H"}, {0x26, 2, 2, "LD H, d8"}, {0x27, 1, 1, "DAA"},
			{0x28, 2, 3, "JR Z, s8"}, {0x29, 1, 2, "ADD HL, HL"}, {0x2A, 1, 2, "LD A, (HL+)"}, {0x2B, 1, 2, "DEC HL"},
			{0x2C, 1, 1, "INC L"}, {0x2D, 1, 1, "DEC L"}, {0x2E, 2, 2, "LD L, d8"}, {0x2F, 1, 1, "CPL"},

			// 0x30, 0x38 is 3 or 2 cycles depending on if jump occurs or not
			{0x30, 2, 3, "JR NC, s8"}, {0x31, 3, 3, "LD SP, d16"}, {0x32, 1, 2, "LD (HL-), A"}, {0x33, 1, 2, "INC SP"},
			{0x34, 1, 3, "INC (HL)"}, {0x35, 1, 3, "DEC (HL)"}, {0x36, 2, 3, "LD (HL), d8"}, {0x37, 1, 1, "SCF"},
			{0x38, 2, 3, "JR C, s8"}, {0x39, 1, 2, "ADD HL, SP"}, {0x3A, 1, 2, "LD A, (HL-)"}, {0x3B, 1, 2, "DEC SP"},
			{0x3C, 1, 1, "INC A"}, {0x3D, 1, 1, "DEC A"}, {0x3E, 2, 2, "LD A, d8"}, {0x3F, 1, 1, "CCF"},

			{0x40, 1, 1, "LD B, B"}, {0x41, 1, 1, "LD B, C"}, {0x42, 1, 1, "LD B, D"}, {0x43, 1, 1, "LD B, E"},
			{0x44, 1, 1, "LD B, H"}, {0x45, 1, 1, "LD B, L"}, {0x46, 1, 2, "LD B, (HL)"}, {0x47, 1, 1, "LD B, A"},
			{0x48, 1, 1, "LD C, B"}, {0x49, 1, 1, "LD C, C"}, {0x4A, 1, 1, "LD C, D"}, {0x4B, 1, 1, "LD C, E"},
			{0x4C, 1, 1, "LD C, H"}, {0x4D, 1, 1, "LD C, L"}, {0x4E, 1, 2, "LD C, (HL)"}, {0x4F, 1, 1, "LD C, A"},

			{0x50, 1, 1, "LD D, B"}, {0x51, 1, 1, "LD D, C"}, {0x52, 1, 1, "LD D, D"}, {0x53, 1, 1, "LD D, E"},
			{0x54, 1, 1, "LD D, H"}, {0x55, 1, 1, "LD D, L"}, {0x56, 1, 2, "LD D, (HL)"}, {0x57, 1, 1, "LD D, A"},
			{0x58, 1, 1, "LD E, B"}, {0x59, 1, 1, "LD E, C"}, {0x5A, 1, 1, "LD E, D"}, {0x5B, 1, 1, "LD E, E"},
			{0x5C, 1, 1, "LD E, H"}, {0x5D, 1, 1, "LD E, L"}, {0x5E, 1, 2, "LD E, (HL)"}, {0x5F, 1, 1, "LD E, A"},

			{0x60, 1, 1, "LD H, B"}, {0x61, 1, 1, "LD H, C"}, {0x62, 1, 1, "LD H, D"}, {0x63, 1, 1, "LD H, E"},
			{0x64, 1, 1, "LD H, H"}, {0x65, 1, 1, "LD H, L"}, {0x66, 1, 2, "LD H, (HL)"}, {0x67, 1, 1, "LD H, A"},
			{0x68, 1, 1, "LD L, B"}, {0x69, 1, 1, "LD L, C"}, {0x6A, 1, 1, "LD L, D"}, {0x6B, 1, 1, "LD L, E"},
			{0x6C, 1, 1, "LD L, H"}, {0x6D, 1, 1, "LD L, L"}, {0x6E, 1, 2, "LD L, (HL)"}, {0x6F, 1, 1, "LD L, A"},

			{0x70, 1, 2, "LD (HL), B"}, {0x71, 1, 2, "LD (HL), C"}, {0x72, 1, 2, "LD (HL), D"}, {0x73, 1, 2, "LD (HL), E"},
			{0x74, 1, 2, "LD (HL), H"}, {0x75, 1, 2, "LD (HL), L"}, {0x76, 1, 1, "HALT"}, {0x77, 1, 2, "LD (HL), A"},
			{0x78, 1, 1, "LD A, B"}, {0x79, 1, 1, "LD A, C"}, {0x7A, 1, 1, "LD A, D"}, {0x7B, 1, 1, "LD A, E"},
			{0x7C, 1, 1, "LD A, H"}, {0x7D, 1, 1, "LD A, L"}, {0x7E, 1, 2, "LD A, (HL)"}, {0x7F, 1, 1, "LD A, A"},

			{0x80, 1, 1, "ADD A, B"}, {0x81, 1, 1, "ADD A, C"}, {0x82, 1, 1, "ADD A, D"}, {0x83, 1, 1, "ADD A, E"},
			{0x84, 1, 1, "ADD A, H"}, {0x85, 1, 1, "ADD A, L"}, {0x86, 1, 2, "ADD A, (HL)"}, {0x87, 1, 1, "ADD A, A"},
			{0x88, 1, 1, "ADC A, B"}, {0x89, 1, 1, "ADC A, C"}, {0x8A, 1, 1, "ADC A, D"}, {0x8B, 1, 1, "ADC A, E"},
			{0x8C, 1, 1, "ADC A, H"}, {0x8D, 1, 1, "ADC A, L"}, {0x8E, 1, 2, "ADC A, (HL)"}, {0x8F, 1, 1, "ADC A, A"},

			{0x90, 1, 1, "SUB B"}, {0x91, 1, 1, "SUB C"}, {0x92, 1, 1, "SUB D"}, {0x93, 1, 1, "SUB E"},
			{0x94, 1, 1, "SUB H"}, {0x95, 1, 1, "SUB L"}, {0x96, 1, 2, "SUB (HL)"}, {0x97, 1, 1, "SUB A"},
			{0x98, 1, 1, "SBC A, B"}, {0x99, 1, 1, "SBC A, C"}, {0x9A, 1, 1, "SBC A, D"}, {0x9B, 1, 1, "SBC A, E"},
			{0x9C, 1, 1, "SBC A, H"}, {0x9D, 1, 1, "SBC A, L"}, {0x9E, 1, 2, "SBC A, (HL)"}, {0x9F, 1, 1, "SBC A, A"},

			{0xA0, 1, 1, "AND B"}, {0xA1, 1, 1, "AND C"}, {0xA2, 1, 1, "AND D"}, {0xA3, 1, 1, "AND E"},
			{0xA4, 1, 1, "AND H"}, {0xA5, 1, 1, "AND L"}, {0xA6, 1, 2, "AND (HL)"}, {0xA7, 1, 1, "AND A"},
			{0xA8, 1, 1, "XOR B"}, {0xA9, 1, 1, "XOR C"}, {0xAA, 1, 1, "XOR D"}, {0xAB, 1, 1, "XOR E"},
			{0xAC, 1, 1, "XOR H"}, {0xAD, 1, 1, "XOR L"}, {0xAE, 1, 2, "XOR (HL)"}, {0xAF, 1, 1, "XOR A"},

			{0xB0, 1, 1, "OR B"}, {0xB1, 1, 1, "OR C"}, {0xB2, 1, 1, "OR D"}, {0xB3, 1, 1, "OR E"},
			{0xB4, 1, 1, "OR H"}, {0xB5, 1, 1, "OR L"}, {0xB6, 1, 2, "OR (HL)"}, {0xB7, 1, 1, "OR A"},
			{0xB8, 1, 1, "CP B"}, {0xB9, 1, 1, "CP C"}, {0xBA, 1, 1, "CP D"}, {0xBB, 1, 1, "CP E"},
			{0xBC, 1, 1, "CP H"}, {0xBD, 1, 1, "CP L"}, {0xBE, 1, 2, "CP (HL)"}, {0xBF, 1, 1, "CP A"},

			// 0xC0, 0xC8, vary between 5 and 2 cycles depending on if jump occurs or not
			// 0xC2, 0xCA, vary between 4 and 3 cycles depending on if jump occurs or not
			// 0xC4, 0xCC, vary between 6 and 3 cycles depending on if jump occurs or not
			{0xC0, 1, 5, "RET NZ"}, {0xC1, 1, 3, "POP BC"}, {0xC2, 3, 4, "JP NZ, a16"}, {0xC3, 3, 4, "JP a16"},
			{0xC4, 3, 6, "CALL NZ, a16"}, {0xC5, 1, 4, "PUSH BC"}, {0xC6, 2, 2, "ADD A, d8"}, {0xC7, 1, 4, "RST 0"},
			{0xC8, 1, 5, "RET Z"}, {0xC9, 1, 4, "RET"}, {0xCA, 3, 4, "JP Z, a16"}, {0xCB, 0, 0, "calls CB table"},
			{0xCC, 3, 6, "CALL Z, a16"}, {0xCD, 3, 6, "CALL a16"}, {0xCE, 2, 2, "ADC A, d8"}, {0xCF, 1, 4, "RST 1"},

			// 0xD0, 0xD8, vary between 5 and 2 cycles depending on if jump occurs or not
			// 0xD2, 0xDA, vary between 4 and 3 cycles depending on if jump occurs or not
			// 0xD4, 0xDC, vary between 6 and 3 cycles depending on if jump occurs or not
			{0xD0, 1, 5, "RET NC"}, {0xD1, 1, 3, "POP DE"}, {0xD2, 3, 4, "JP NC, a16"}, {0xD3, 0, 0, "ILLEGAL"},
			{0xD4, 3, 6, "CALL NC, a16"}, {0xD5, 1, 4, "PUSH DE"}, {0xD6, 2, 2, "SUB d8"}, {0xD7, 1, 4, "RST 2"},
			{0xD8, 1, 5, "RET C"}, {0xD9, 1, 4, "RETI"}, {0xDA, 3, 4, "JP C, a16"}, {0xDB, 0, 0, "ILLEGAL"},
			{0xDC, 3, 6, "CALL C, a16"}, {0xDD, 0, 0, "ILLEGAL"}, {0xDE, 2, 2, "SBC A, d8"}, {0xDF, 1, 4, "RST 3"},

			{0xE0, 2, 3, "LD (a8), A"}, {0xE1, 1, 3, "POP HL"}, {0xE2, 1, 2, "LD (C), A"}, {0xE3, 0, 0, "ILLEGAL"},
			{0xE4, 0, 0, "ILLEGAL"}, {0xE5, 1, 4, "PUSH HL"}, {0xE6, 2, 2, "AND d8"}, {0xE7, 1, 4, "RST 4"},
			{0xE8, 2, 4, "ADD SP, s8"}, {0xE9, 1, 1, "JP HL"}, {0xEA, 3, 4, "LD (a16), A"}, {0xEB, 0, 0, "ILLEGAL"},
			{0xEC, 0, 0, "ILLEGAL"}, {0xED, 0, 0, "ILLEGAL"}, {0xEE, 2, 2, "XOR d8"}, {0xEF, 1, 4, "RST 5"},

			{0xF0, 2, 3, "LD A, (a8)"}, {0xF1, 1, 3, "POP AF"}, {0xF2, 1, 2, "LD A, (C)"}, {0xF3, 1, 1, "DI"},
			{0xF4, 0, 0, "ILLEGAL"}, {0xF5, 1, 4, "PUSH AF"}, {0xF6, 2, 2, "OR d8"}, {0xF7, 1, 4, "RST 6"},
			{0xF8, 2, 3, "LD HL, SP+s8"}, {0xF9, 1, 2, "LD SP, HL"}, {0xFA, 3, 4, "LD A, (a16)"}, {0xFB, 1, 1, "EI"},
			{0xFC, 0, 0, "ILLEGAL"}, {0xFD, 0, 0, "ILLEGAL"}, {0xFE, 2, 2, "CP d8"}, {0xFF, 1, 4, "RST 7"}
		} };

		// CB Opcodes to Human Readable Instructions, https://meganesu.github.io/generate-gb-opcodes/
		const std::array<Instruction, 256> instr_cb_data { {
			{0x00, 2, 2, "RLC B"}, {0x01, 2, 2, "RLC C"}, {0x02, 2, 2, "RLC D"}, {0x03, 2, 2, "RLC E"},
			{0x04, 2, 2, "RLC H"}, {0x05, 2, 2, "RLC L"}, {0x06, 2, 4, "RLC (HL)"}, {0x07, 2, 2, "RLC A"},
			{0x08, 2, 2, "RRC B"}, {0x09, 2, 2, "RRC C"}, {0x0A, 2, 2, "RRC D"}, {0x0B, 2, 2, "RRC E"},
			{0x0C, 2, 2, "RRC H"}, {0x0D, 2, 2, "RRC L"}, {0x0E, 2, 4, "RRC (HL)"}, {0x0F, 2, 2, "RRC A"},

			{0x10, 2, 2, "RL B"}, {0x11, 2, 2, "RL C"}, {0x12, 2, 2, "RL D"}, {0x13, 2, 2, "RL E"},
			{0x14, 2, 2, "RL H"}, {0x15, 2, 2, "RL L"}, {0x16, 2, 4, "RL (HL)"}, {0x17, 2, 2, "RL A"},
			{0x18, 2, 2, "RR B"}, {0x19, 2, 2, "RR C"}, {0x1A, 2, 2, "RR D"}, {0x1B, 2, 2, "RR E"},
			{0x1C, 2, 2, "RR H"}, {0x1D, 2, 2, "RR L"}, {0x1E, 2, 4, "RR (HL)"}, {0x1F, 2, 2, "RR A"},

			{0x20, 2, 2, "SLA B"}, {0x21, 2, 2, "SLA C"}, {0x22, 2, 2, "SLA D"}, {0x23, 2, 2, "SLA E"},
			{0x24, 2, 2, "SLA H"}, {0x25, 2, 2, "SLA L"}, {0x26, 2, 4, "SLA (HL)"}, {0x27, 2, 2, "SLA A"},
			{0x28, 2, 2, "SRA B"}, {0x29, 2, 2, "SRA C"}, {0x2A, 2, 2, "SRA D"}, {0x2B, 2, 2, "SRA E"},
			{0x2C, 2, 2, "SRA H"}, {0x2D, 2, 2, "SRA L"}, {0x2E, 2, 4, "SRA (HL)"}, {0x2F, 2, 2, "SRA A"},

			{0x30, 2, 2, "SWAP B"}, {0x31, 2, 2, "SWAP C"}, {0x32, 2, 2, "SWAP D"}, {0x33, 2, 2, "SWAP E"},
			{0x34, 2, 2, "SWAP H"}, {0x35, 2, 2, "SWAP L"}, {0x36, 2, 4, "SWAP (HL)"}, {0x37, 2, 2, "SWAP A"},
			{0x38, 2, 2, "SRL B"}, {0x39, 2, 2, "SRL C"}, {0x3A, 2, 2, "SRL D"}, {0x3B, 2, 2, "SRL E"},
			{0x3C, 2, 2, "SRL H"}, {0x3D, 2, 2, "SRL L"}, {0x3E, 2, 4, "SRL (HL)"}, {0x3F, 2, 2, "SRL A"},

			{0x40, 2, 2, "BIT 0, B"}, {0x41, 2, 2, "BIT 0, C"}, {0x42, 2, 2, "BIT 0, D"}, {0x43, 2, 2, "BIT 0, E"},
			{0x44, 2, 2, "BIT 0, H"}, {0x45, 2, 2, "BIT 0, L"}, {0x46, 2, 3, "BIT 0, (HL)"}, {0x47, 2, 2, "BIT 0, A"},
			{0x48, 2, 2, "BIT 1, B"}, {0x49, 2, 2, "BIT 1, C"}, {0x4A, 2, 2, "BIT 1, D"}, {0x4B, 2, 2, "BIT 1, E"},
			{0x4C, 2, 2, "BIT 1, H"}, {0x4D, 2, 2, "BIT 1, L"}, {0x4E, 2, 3, "BIT 1, (HL)"}, {0x4F, 2, 2, "BIT 1, A"},

			{0x50, 2, 2, "BIT 2, B"}, {0x51, 2, 2, "BIT 2, C"}, {0x52, 2, 2, "BIT 2, D"}, {0x53, 2, 2, "BIT 2, E"},
			{0x54, 2, 2, "BIT 2, H"}, {0x55, 2, 2, "BIT 2, L"}, {0x56, 2, 3, "BIT 2, (HL)"}, {0x57, 2, 2, "BIT 2, A"},
			{0x58, 2, 2, "BIT 3, B"}, {0x59, 2, 2, "BIT 3, C"}, {0x5A, 2, 2, "BIT 3, D"}, {0x5B, 2, 2, "BIT 3, E"},
			{0x5C, 2, 2, "BIT 3, H"}, {0x5D, 2, 2, "BIT 3, L"}, {0x5E, 2, 3, "BIT 3, (HL)"}, {0x5F, 2, 2, "BIT 3, A"},

			{0x60, 2, 2, "BIT 4, B"}, {0x61, 2, 2, "BIT 4, C"}, {0x62, 2, 2, "BIT 4, D"}, {0x63, 2, 2, "BIT 4, E"},
			{0x64, 2, 2, "BIT 4, H"}, {0x65, 2, 2, "BIT 4, L"}, {0x66, 2, 3, "BIT 4, (HL)"}, {0x67, 2, 2, "BIT 4, A"},
			{0x68, 2, 2, "BIT 5, B"}, {0x69, 2, 2, "BIT 5, C"}, {0x6A, 2, 2, "BIT 5, D"}, {0x6B, 2, 2, "BIT 5, E"},
			{0x6C, 2, 2, "BIT 5, H"}, {0x6D, 2, 2, "BIT 5, L"}, {0x6E, 2, 3, "BIT 5, (HL)"}, {0x6F, 2, 2, "BIT 5, A"},

			{0x70, 2, 2, "BIT 6, B"}, {0x71, 2, 2, "BIT 6, C"}, {0x72, 2, 2, "BIT 6, D"}, {0x73, 2, 2, "BIT 6, E"},
			{0x74, 2, 2, "BIT 6, H"}, {0x75, 2, 2, "BIT 6, L"}, {0x76, 2, 3, "BIT 6, (HL)"}, {0x77, 2, 2, "BIT 6, A"},
			{0x78, 2, 2, "BIT 7, B"}, {0x79, 2, 2, "BIT 7, C"}, {0x7A, 2, 2, "BIT 7, D"}, {0x7B, 2, 2, "BIT 7, E"},
			{0x7C, 2, 2, "BIT 7, H"}, {0x7D, 2, 2, "BIT 7, L"}, {0x7E, 2, 3, "BIT 7, (HL)"}, {0x7F, 2, 2, "BIT 7, A"},

			{0x80, 2, 2, "RES 0, B"}, {0x81, 2, 2, "RES 0, C"}, {0x82, 2, 2, "RES 0, D"}, {0x83, 2, 2, "RES 0, E"},
			{0x84, 2, 2, "RES 0, H"}, {0x85, 2, 2, "RES 0, L"}, {0x86, 2, 4, "RES 0, (HL)"}, {0x87, 2, 2, "RES 0, A"},
			{0x88, 2, 2, "RES 1, B"}, {0x89, 2, 2, "RES 1, C"}, {0x8A, 2, 2, "RES 1, D"}, {0x8B, 2, 2, "RES 1, E"},
			{0x8C, 2, 2, "RES 1, H"}, {0x8D, 2, 2, "RES 1, L"}, {0x8E, 2, 4, "RES 1, (HL)"}, {0x8F, 2, 2, "RES 1, A"},

			{0x90, 2, 2, "RES 2, B"}, {0x91, 2, 2, "RES 2, C"}, {0x92, 2, 2, "RES 2, D"}, {0x93, 2, 2, "RES 2, E"},
			{0x94, 2, 2, "RES 2, H"}, {0x95, 2, 2, "RES 2, L"}, {0x96, 2, 4, "RES 2, (HL)"}, {0x97, 2, 2, "RES 2, A"},
			{0x98, 2, 2, "RES 3, B"}, {0x99, 2, 2, "RES 3, C"}, {0x9A, 2, 2, "RES 3, D"}, {0x9B, 2, 2, "RES 3, E"},
			{0x9C, 2, 2, "RES 3, H"}, {0x9D, 2, 2, "RES 3, L"}, {0x9E, 2, 4, "RES 3, (HL)"}, {0x9F, 2, 2, "RES 3, A"},

			{0xA0, 2, 2, "RES 4, B"}, {0xA1, 2, 2, "RES 4, C"}, {0xA2, 2, 2, "RES 4, D"}, {0xA3, 2, 2, "RES 4, E"},
			{0xA4, 2, 2, "RES 4, H"}, {0xA5, 2, 2, "RES 4, L"}, {0xA6, 2, 4, "RES 4, (HL)"}, {0xA7, 2, 2, "RES 4, A"},
			{0xA8, 2, 2, "RES 5, B"}, {0xA9, 2, 2, "RES 5, C"}, {0xAA, 2, 2, "RES 5, D"}, {0xAB, 2, 2, "RES 5, E"},
			{0xAC, 2, 2, "RES 5, H"}, {0xAD, 2, 2, "RES 5, L"}, {0xAE, 2, 4, "RES 5, (HL)"}, {0xAF, 2, 2, "RES 5, A"},

			{0xB0, 2, 2, "RES 6, B"}, {0xB1, 2, 2, "RES 6, C"}, {0xB2, 2, 2, "RES 6, D"}, {0xB3, 2, 2, "RES 6, E"},
			{0xB4, 2, 2, "RES 6, H"}, {0xB5, 2, 2, "RES 6, L"}, {0xB6, 2, 4, "RES 6, (HL)"}, {0xB7, 2, 2, "RES 6, A"},
			{0xB8, 2, 2, "RES 7, B"}, {0xB9, 2, 2, "RES 7, C"}, {0xBA, 2, 2, "RES 7, D"}, {0xBB, 2, 2, "RES 7, E"},
			{0xBC, 2, 2, "RES 7, H"}, {0xBD, 2, 2, "RES 7, L"}, {0xBE, 2, 4, "RES 7, (HL)"}, {0xBF, 2, 2, "RES 7, A"},

			{0xC0, 2, 2, "SET 0, B"}, {0xC1, 2, 2, "SET 0, C"}, {0xC2, 2, 2, "SET 0, D"}, {0xC3, 2, 2, "SET 0, E"},
			{0xC4, 2, 2, "SET 0, H"}, {0xC5, 2, 2, "SET 0, L"}, {0xC6, 2, 4, "SET 0, (HL)"}, {0xC7, 2, 2, "SET 0, A"},
			{0xC8, 2, 2, "SET 1, B"}, {0xC9, 2, 2, "SET 1, C"}, {0xCA, 2, 2, "SET 1, D"}, {0xCB, 2, 2, "SET 1, E"},
			{0xCC, 2, 2, "SET 1, H"}, {0xCD, 2, 2, "SET 1, L"}, {0xCE, 2, 4, "SET 1, (HL)"}, {0xCF, 2, 2, "SET 1, A"},

			{0xD0, 2, 2, "SET 2, B"}, {0xD1, 2, 2, "SET 2, C"}, {0xD2, 2, 2, "SET 2, D"}, {0xD3, 2, 2, "SET 2, E"},
			{0xD4, 2, 2, "SET 2, H"}, {0xD5, 2, 2, "SET 2, L"}, {0xD6, 2, 4, "SET 2, (HL)"}, {0xD7, 2, 2, "SET 2, A"},
			{0xD8, 2, 2, "SET 3, B"}, {0xD9, 2, 2, "SET 3, C"}, {0xDA, 2, 2, "SET 3, D"}, {0xDB, 2, 2, "SET 3, E"},
			{0xDC, 2, 2, "SET 3, H"}, {0xDD, 2, 2, "SET 3, L"}, {0xDE, 2, 4, "SET 3, (HL)"}, {0xDF, 2, 2, "SET 3, A"},

			{0xE0, 2, 2, "SET 4, B"}, {0xE1, 2, 2, "SET 4, C"}, {0xE2, 2, 2, "SET 4, D"}, {0xE3, 2, 2, "SET 4, E"},
			{0xE4, 2, 2, "SET 4, H"}, {0xE5, 2, 2, "SET 4, L"}, {0xE6, 2, 4, "SET 4, (HL)"}, {0xE7, 2, 2, "SET 4, A"},
			{0xE8, 2, 2, "SET 5, B"}, {0xE9, 2, 2, "SET 5, C"}, {0xEA, 2, 2, "SET 5, D"}, {0xEB, 2, 2, "SET 5, E"},
			{0xEC, 2, 2, "SET 5, H"}, {0xED, 2, 2, "SET 5, L"}, {0xEE, 2, 4, "SET 5, (HL)"}, {0xEF, 2, 2, "SET 5, A"},

			{0xF0, 2, 2, "SET 6, B"}, {0xF1, 2, 2, "SET 6, C"}, {0xF2, 2, 2, "SET 6, D"}, {0xF3, 2, 2, "SET 6, E"},
			{0xF4, 2, 2, "SET 6, H"}, {0xF5, 2, 2, "SET 6, L"}, {0xF6, 2, 4, "SET 6, (HL)"}, {0xF7, 2, 2, "SET 6, A"},
			{0xF8, 2, 2, "SET 7, B"}, {0xF9, 2, 2, "SET 7, C"}, {0xFA, 2, 2, "SET 7, D"}, {0xFB, 2, 2, "SET 7, E"},
			{0xFC, 2, 2, "SET 7, H"}, {0xFD, 2, 2, "SET 7, L"}, {0xFE, 2, 4, "SET 7, (HL)"}, {0xFF, 2, 2, "SET 7, A"}
		} };
		
	private:
		// Reference to MMU
		MMU& m_mmu;

		bool m_executingInstruction = false;
		bool m_cbMode = false;
		int m_mCycle = 1;

		u8 m_currentOperation = 0x00;
		u8 m_currentOperationCB = 0x00; // Used when currentOp is CB

		u16 m_wz = 0x0000;
		u8& m_w = *((u8*)(&m_wz) + 1);
		u8& m_z = *(u8*)(&m_wz);

		void executeInstruction();
		void executeCBInstruction();
		u8 readByte();
		u8 readByte(u16 addr);
		void writeByte(u16 addr, u8 value);

		// Typedefs and Enums
		typedef u16 Register16;
		typedef u8 Register8;
		typedef bool Flag;

		typedef enum ConditionCode {
			Z,  // Execute if Z is set
			NZ, // Execute if Z is not set
			C,  // Execute if C is set
			NC  // Execute if C is not set
		} ConditionCode;

		typedef enum RSTVec {
			x00, x08, x10, x18,
			x20, x28, x30, x38
		} RSTVec;

		u8 convertRSTVec(RSTVec vec);
		
	public:
		typedef struct Registers
		{
			Register16 af = 0x0000;
			Register16 bc = 0x0000;
			Register16 de = 0x0000;
			Register16 hl = 0x0000;
			Register16 stackPointer = 0x0000;
			Register16 programCounter = 0x0100;

			Register8& a = *((Register8*)(&af) + 1);
			Register8& f = *(Register8*)(&af);

			Register8& b = *((Register8*)(&bc) + 1);
			Register8& c = *(Register8*)(&bc);

			Register8& d = *((Register8*)(&de) + 1);
			Register8& e = *(Register8*)(&de);

			Register8& h = *((Register8*)(&hl) + 1);
			Register8& l = *(Register8*)(&hl);
		} Registers;
	private:
		Registers m_registers;

		// Can only be set, not read. When set, set with a delay of 1 instruction.
		Flag ime = false;
		bool setIMENextCycle = false; // Set in EI

		void setIME(bool value);

		// Flags
			// bit 7 "z": zero flag. used for conditional jumps, set if result of operation is 0
			// bit 6 "n": subtraction flag
			// bit 5 "h": half carry flag
			// bit 4 "c": carry flag
		Flag getFlagZ();
		Flag getFlagN();
		Flag getFlagH();
		Flag getFlagC();

		void setFlagZ(bool value);
		void setFlagN(bool value);
		void setFlagH(bool value);
		void setFlagC(bool value);

		void setFlags(u4 value);
		void setFlags(bool z, bool n, bool h, bool c);

		void setFlagsForU8Overflow(u16 a, u16 b, u16 c);
		void setFlagsForU8Overflow(u16 a, u16 b);
		void setFlagsForU16Overflow(u16 a, u16 b);

		void setFlagsForU8Borrow(u8 a, u8 b);
		void setFlagsForU8Borrow(u8 a, u8 b, u8 c);

		bool willHalfCarry(u8 a, u8 b, bool add);
		bool willHalfCarry(u16 a, u16 b, bool add);
		bool willCarry(u8 a, u8 b, bool add);
		bool willCarry(u16 a, u16 b, bool add);

		u8 signedToPositiveUnsigned(s8 n);
		u16 signedToPositiveUnsigned(s16 n);

		bool ccStatus(ConditionCode cc);

		// CPU Instruction Set: https://rgbds.gbdev.io/docs/v0.9.4/gbz80.7 and https://gekkio.fi/files/gb-docs/gbctr.pdf
			// 8-bit Loads
		void LD_R8_R8(Register8& ra, Register8& rb);
		void LD_R8_N8(Register8& r);
		void LD_R8_HL(Register8& r);
		void LD_HL_R8(Register8& r);
		void LD_HL_N8();
		void LD_A_R16(Register16& r);
		void LD_R16_A(Register16& r);
		void LD_A_N16();
		void LD_N16_A();
		void LDH_A_C();
		void LDH_C_A();
		void LDH_A_N16();
		void LDH_N16_A();
		void LD_A_HLD();
		void LD_HLD_A();
		void LD_A_HLI();
		void LD_HLI_A();

			// 16-bit Loads
		void LD_R16_N16(Register16& r);
		void LD_N16_SP();
		void LD_SP_HL();
		void PUSH_R16(Register16& r);
		void POP_R16(Register16& r);
		void LD_HL_SP_S8();

			// 8-bit Arithmetic and Logic
		void ADD_A_R8(CPU::Register8& r);
		void ADD_A_HL();
		void ADD_A_N8();
		void ADC_A_R8(CPU::Register8& r);
		void ADC_A_HL();
		void ADC_A_N8();
		void SUB_A_R8(CPU::Register8& r);
		void SUB_A_HL();
		void SUB_A_N8();
		void SBC_A_R8(CPU::Register8& r);
		void SBC_A_HL();
		void SBC_A_N8();
		void CP_A_R8(CPU::Register8&);
		void CP_A_HL();
		void CP_A_N8();
		void INC_R8(CPU::Register8& r);
		void INC_HL();
		void DEC_R8(CPU::Register8& r);
		void DEC_HL();
		void AND_A_R8(CPU::Register8& r);
		void AND_A_HL();
		void AND_A_N8();
		void OR_A_R8(CPU::Register8& r);
		void OR_A_HL();
		void OR_A_N8();
		void XOR_A_R8(CPU::Register8& r);
		void XOR_A_HL();
		void XOR_A_N8();
		void CCF();
		void SCF();
		void DAA();
		void CPL();

			// 16-bit Arithmetic and Logic
		void INC_R16(CPU::Register16& r);
		void DEC_R16(CPU::Register16& r);
		void ADD_HL_R16(CPU::Register16& r);
		void ADD_SP_S8();

			// Rotate, Shift, Bit Operations
		void RL_C_A();
		void RR_C_A();
		void RL_A();
		void RR_A();
		void RL_C_R8(CPU::Register8& r);
		void RL_C_HL();
		void RR_C_R8(CPU::Register8& r);
		void RR_C_HL();
		void RL_R8(CPU::Register8& r);
		void RL_HL();
		void RR_R8(CPU::Register8& r);
		void RR_HL();
		void SLA_R8(CPU::Register8& r);
		void SLA_HL();
		void SRA_R8(CPU::Register8& r);
		void SRA_HL();
		void SWAP_R8(CPU::Register8& r);
		void SWAP_HL();
		void SRL_R8(CPU::Register8& r);
		void SRL_HL();
		void BIT_U3_R8(u3 u, CPU::Register8& r);
		void BIT_U3_HL(u3 u);
		void RES_U3_R8(u3 u, CPU::Register8& r);
		void RES_U3_HL(u3 u);
		void SET_U3_R8(u3 u, CPU::Register8& r);
		void SET_U3_HL(u3 u);

			// Control Flow
		void JP_N16();
		void JP_HL();
		void JP_CC_N16(ConditionCode cc);
		void JR_N8();
		void JR_CC_N8(ConditionCode p_cc);
		void CALL_N16();
		void CALL_CC_N16(ConditionCode cc);
		void RET();
		void RET_CC(ConditionCode cc);
		void RETI();
		void RST_VEC(RSTVec vec);

		// Miscellaneous
		void HALT();
		void STOP();
		void DI();
		void EI();
		void NOP();


		// OP Codes
			// 8 bit opcodes
		void op_00(); void op_01(); void op_02(); void op_03(); void op_04(); void op_05(); void op_06(); void op_07(); void op_08(); void op_09(); void op_0A(); void op_0B(); void op_0C(); void op_0D(); void op_0E(); void op_0F();
		void op_10(); void op_11(); void op_12(); void op_13(); void op_14(); void op_15(); void op_16(); void op_17(); void op_18(); void op_19(); void op_1A(); void op_1B(); void op_1C(); void op_1D(); void op_1E(); void op_1F();
		void op_20(); void op_21(); void op_22(); void op_23(); void op_24(); void op_25(); void op_26(); void op_27(); void op_28(); void op_29(); void op_2A(); void op_2B(); void op_2C(); void op_2D(); void op_2E(); void op_2F();
		void op_30(); void op_31(); void op_32(); void op_33(); void op_34(); void op_35(); void op_36(); void op_37(); void op_38(); void op_39(); void op_3A(); void op_3B(); void op_3C(); void op_3D(); void op_3E(); void op_3F();
		void op_40(); void op_41(); void op_42(); void op_43(); void op_44(); void op_45(); void op_46(); void op_47(); void op_48(); void op_49(); void op_4A(); void op_4B(); void op_4C(); void op_4D(); void op_4E(); void op_4F();
		void op_50(); void op_51(); void op_52(); void op_53(); void op_54(); void op_55(); void op_56(); void op_57(); void op_58(); void op_59(); void op_5A(); void op_5B(); void op_5C(); void op_5D(); void op_5E(); void op_5F();
		void op_60(); void op_61(); void op_62(); void op_63(); void op_64(); void op_65(); void op_66(); void op_67(); void op_68(); void op_69(); void op_6A(); void op_6B(); void op_6C(); void op_6D(); void op_6E(); void op_6F();
		void op_70(); void op_71(); void op_72(); void op_73(); void op_74(); void op_75(); void op_76(); void op_77(); void op_78(); void op_79(); void op_7A(); void op_7B(); void op_7C(); void op_7D(); void op_7E(); void op_7F();
		void op_80(); void op_81(); void op_82(); void op_83(); void op_84(); void op_85(); void op_86(); void op_87(); void op_88(); void op_89(); void op_8A(); void op_8B(); void op_8C(); void op_8D(); void op_8E(); void op_8F();
		void op_90(); void op_91(); void op_92(); void op_93(); void op_94(); void op_95(); void op_96(); void op_97(); void op_98(); void op_99(); void op_9A(); void op_9B(); void op_9C(); void op_9D(); void op_9E(); void op_9F();
		void op_A0(); void op_A1(); void op_A2(); void op_A3(); void op_A4(); void op_A5(); void op_A6(); void op_A7(); void op_A8(); void op_A9(); void op_AA(); void op_AB(); void op_AC(); void op_AD(); void op_AE(); void op_AF();
		void op_B0(); void op_B1(); void op_B2(); void op_B3(); void op_B4(); void op_B5(); void op_B6(); void op_B7(); void op_B8(); void op_B9(); void op_BA(); void op_BB(); void op_BC(); void op_BD(); void op_BE(); void op_BF();
		void op_C0(); void op_C1(); void op_C2(); void op_C3(); void op_C4(); void op_C5(); void op_C6(); void op_C7(); void op_C8(); void op_C9(); void op_CA(); void op_CB(); void op_CC(); void op_CD(); void op_CE(); void op_CF();
		void op_D0(); void op_D1(); void op_D2(); void op_D3(); void op_D4(); void op_D5(); void op_D6(); void op_D7(); void op_D8(); void op_D9(); void op_DA(); void op_DB(); void op_DC(); void op_DD(); void op_DE(); void op_DF();
		void op_E0(); void op_E1(); void op_E2(); void op_E3(); void op_E4(); void op_E5(); void op_E6(); void op_E7(); void op_E8(); void op_E9(); void op_EA(); void op_EB(); void op_EC(); void op_ED(); void op_EE(); void op_EF();
		void op_F0(); void op_F1(); void op_F2(); void op_F3(); void op_F4(); void op_F5(); void op_F6(); void op_F7(); void op_F8(); void op_F9(); void op_FA(); void op_FB(); void op_FC(); void op_FD(); void op_FE(); void op_FF();
		
			// 16 bit opcodes starting with CB
		void op_cb_00(); void op_cb_01(); void op_cb_02(); void op_cb_03(); void op_cb_04(); void op_cb_05(); void op_cb_06(); void op_cb_07(); void op_cb_08(); void op_cb_09(); void op_cb_0A(); void op_cb_0B(); void op_cb_0C(); void op_cb_0D(); void op_cb_0E(); void op_cb_0F();
		void op_cb_10(); void op_cb_11(); void op_cb_12(); void op_cb_13(); void op_cb_14(); void op_cb_15(); void op_cb_16(); void op_cb_17(); void op_cb_18(); void op_cb_19(); void op_cb_1A(); void op_cb_1B(); void op_cb_1C(); void op_cb_1D(); void op_cb_1E(); void op_cb_1F();
		void op_cb_20(); void op_cb_21(); void op_cb_22(); void op_cb_23(); void op_cb_24(); void op_cb_25(); void op_cb_26(); void op_cb_27(); void op_cb_28(); void op_cb_29(); void op_cb_2A(); void op_cb_2B(); void op_cb_2C(); void op_cb_2D(); void op_cb_2E(); void op_cb_2F();
		void op_cb_30(); void op_cb_31(); void op_cb_32(); void op_cb_33(); void op_cb_34(); void op_cb_35(); void op_cb_36(); void op_cb_37(); void op_cb_38(); void op_cb_39(); void op_cb_3A(); void op_cb_3B(); void op_cb_3C(); void op_cb_3D(); void op_cb_3E(); void op_cb_3F();
		void op_cb_40(); void op_cb_41(); void op_cb_42(); void op_cb_43(); void op_cb_44(); void op_cb_45(); void op_cb_46(); void op_cb_47(); void op_cb_48(); void op_cb_49(); void op_cb_4A(); void op_cb_4B(); void op_cb_4C(); void op_cb_4D(); void op_cb_4E(); void op_cb_4F();
		void op_cb_50(); void op_cb_51(); void op_cb_52(); void op_cb_53(); void op_cb_54(); void op_cb_55(); void op_cb_56(); void op_cb_57(); void op_cb_58(); void op_cb_59(); void op_cb_5A(); void op_cb_5B(); void op_cb_5C(); void op_cb_5D(); void op_cb_5E(); void op_cb_5F();
		void op_cb_60(); void op_cb_61(); void op_cb_62(); void op_cb_63(); void op_cb_64(); void op_cb_65(); void op_cb_66(); void op_cb_67(); void op_cb_68(); void op_cb_69(); void op_cb_6A(); void op_cb_6B(); void op_cb_6C(); void op_cb_6D(); void op_cb_6E(); void op_cb_6F();
		void op_cb_70(); void op_cb_71(); void op_cb_72(); void op_cb_73(); void op_cb_74(); void op_cb_75(); void op_cb_76(); void op_cb_77(); void op_cb_78(); void op_cb_79(); void op_cb_7A(); void op_cb_7B(); void op_cb_7C(); void op_cb_7D(); void op_cb_7E(); void op_cb_7F();
		void op_cb_80(); void op_cb_81(); void op_cb_82(); void op_cb_83(); void op_cb_84(); void op_cb_85(); void op_cb_86(); void op_cb_87(); void op_cb_88(); void op_cb_89(); void op_cb_8A(); void op_cb_8B(); void op_cb_8C(); void op_cb_8D(); void op_cb_8E(); void op_cb_8F();
		void op_cb_90(); void op_cb_91(); void op_cb_92(); void op_cb_93(); void op_cb_94(); void op_cb_95(); void op_cb_96(); void op_cb_97(); void op_cb_98(); void op_cb_99(); void op_cb_9A(); void op_cb_9B(); void op_cb_9C(); void op_cb_9D(); void op_cb_9E(); void op_cb_9F();
		void op_cb_A0(); void op_cb_A1(); void op_cb_A2(); void op_cb_A3(); void op_cb_A4(); void op_cb_A5(); void op_cb_A6(); void op_cb_A7(); void op_cb_A8(); void op_cb_A9(); void op_cb_AA(); void op_cb_AB(); void op_cb_AC(); void op_cb_AD(); void op_cb_AE(); void op_cb_AF();
		void op_cb_B0(); void op_cb_B1(); void op_cb_B2(); void op_cb_B3(); void op_cb_B4(); void op_cb_B5(); void op_cb_B6(); void op_cb_B7(); void op_cb_B8(); void op_cb_B9(); void op_cb_BA(); void op_cb_BB(); void op_cb_BC(); void op_cb_BD(); void op_cb_BE(); void op_cb_BF();
		void op_cb_C0(); void op_cb_C1(); void op_cb_C2(); void op_cb_C3(); void op_cb_C4(); void op_cb_C5(); void op_cb_C6(); void op_cb_C7(); void op_cb_C8(); void op_cb_C9(); void op_cb_CA(); void op_cb_CB(); void op_cb_CC(); void op_cb_CD(); void op_cb_CE(); void op_cb_CF();
		void op_cb_D0(); void op_cb_D1(); void op_cb_D2(); void op_cb_D3(); void op_cb_D4(); void op_cb_D5(); void op_cb_D6(); void op_cb_D7(); void op_cb_D8(); void op_cb_D9(); void op_cb_DA(); void op_cb_DB(); void op_cb_DC(); void op_cb_DD(); void op_cb_DE(); void op_cb_DF();
		void op_cb_E0(); void op_cb_E1(); void op_cb_E2(); void op_cb_E3(); void op_cb_E4(); void op_cb_E5(); void op_cb_E6(); void op_cb_E7(); void op_cb_E8(); void op_cb_E9(); void op_cb_EA(); void op_cb_EB(); void op_cb_EC(); void op_cb_ED(); void op_cb_EE(); void op_cb_EF();
		void op_cb_F0(); void op_cb_F1(); void op_cb_F2(); void op_cb_F3(); void op_cb_F4(); void op_cb_F5(); void op_cb_F6(); void op_cb_F7(); void op_cb_F8(); void op_cb_F9(); void op_cb_FA(); void op_cb_FB(); void op_cb_FC(); void op_cb_FD(); void op_cb_FE(); void op_cb_FF();
	};
}