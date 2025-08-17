#pragma once
#include "../utility/definitions.h"
#include "../mmu/mmu.h"

namespace rose_core
{
	class CPU
	{
	public:
		struct Registers;

		CPU(MMU& mmu);

		void executeInstruction();
		void executeCBInstruction();
		u8 getByte();
		u16 getBytePair();

		const Registers& viewRegisters() const;
	private:
		// Reference to MMU
		MMU& m_mmu;

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

			Register8& h = *((Register8*)(&h) + 1);
			Register8& l = *(Register8*)(&l);
		} Registers;
		Registers m_registers;

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

		bool ccStatus(ConditionCode cc);

		// CPU Instruction Set: https://rgbds.gbdev.io/docs/v0.9.4/gbz80.7
			// Loads
		void LD_R8_R8(Register8& ra, Register8& rb);
		void LD_R8_N8(Register8& r, u8 n);
		void LD_R16_N16(Register16& r, u16 n);
		void LD_HL_R8(Register8& r);
		void LD_HL_N8(u8 n);
		void LD_R8_HL(Register8& r);
		void LD_R16_A(Register16& r);
		void LD_N16_A(u16 n);
		void LDH_N16_A(u16 n);
		void LDH_C_A();
		void LD_A_R16(Register16& r);
		void LD_A_N16(u16 n);
		void LDH_A_N16(u16 n);
		void LDH_A_C();
		void LD_HLI_A();
		void LD_HLD_A();
		void LD_A_HLI();
		void LD_A_HLD();

			// 8-bit Arithmetic
		void ADC_A_R8(CPU::Register8& r);
		void ADC_A_HL();
		void ADC_A_N8(u8 n);
		void ADD_A_R8(CPU::Register8& r);
		void ADD_A_HL();
		void ADD_A_N8(u8 n);
		void CP_A_R8(CPU::Register8&);
		void CP_A_HL();
		void CP_A_N8(u8 n);
		void DEC_R8(CPU::Register8& r);
		void DEC_HL();
		void INC_R8(CPU::Register8& r);
		void INC_HL();
		void SBC_A_R8(CPU::Register8& r);
		void SBC_A_HL();
		void SBC_A_N8(u8 n);
		void SUB_A_R8(CPU::Register8& r);
		void SUB_A_HL();
		void SUB_A_N8(u8 n);

			// 16-bit Arithmetic
		void ADD_HL_R16(CPU::Register16& r);
		void DEC_R16(CPU::Register16& r);
		void INC_R16(CPU::Register16& r);

			// Bitwise Logic
		void AND_A_R8(CPU::Register8& r);
		void AND_A_HL();
		void AND_A_N8(u8 n);
		void CPL();
		void OR_A_R8(CPU::Register8& r);
		void OR_A_HL();
		void OR_A_N8(u8 n);
		void XOR_A_R8(CPU::Register8& r);
		void XOR_A_HL();
		void XOR_A_N8(u8 n);

			// Bit Flags
		void BIT_U3_R8(u3 u, CPU::Register8& r);
		void BIT_U3_HL(u3 u);
		void RES_U3_R8(u3 u, CPU::Register8& r);
		void RES_U3_HL(u3 u);
		void SET_U3_R8(u3 u, CPU::Register8& r);
		void SET_U3_HL(u3 u);

			// Bit Shifts
		void RL_R8(CPU::Register8& r);
		void RL_HL();
		void RL_A();
		void RL_C_R8(CPU::Register8& r);
		void RL_C_HL();
		void RL_C_A();
		void RR_R8(CPU::Register8& r);
		void RR_HL();
		void RR_A();
		void RR_C_R8(CPU::Register8& r);
		void RR_C_HL();
		void RR_C_A();
		void SLA_R8(CPU::Register8& r);
		void SLA_HL();
		void SRA_R8(CPU::Register8& r);
		void SRA_HL();
		void SRL_R8(CPU::Register8& r);
		void SRL_HL();
		void SWAP_R8(CPU::Register8& r);
		void SWAP_HL();

			// Jumps and Subroutines
		void CALL_N16(u16 n);
		void CALL_CC_N16(ConditionCode cc, u16 n);
		void JP_HL();
		void JP_N16(s16 n);
		void JP_CC_N16(ConditionCode cc, s16 n);
		void JR_N8(s8 n);
		void JR_CC_N8(ConditionCode cc, s8 n);
		void RET();
		void RET_CC(ConditionCode cc);
		void RETI();
		void RST_VEC(RSTVec vec);

			// Carry Flag
		void CCF();
		void SCF();

			// Stack Manipulation
		void ADD_HL_SP();
		void ADD_SP_S8(s8 s);
		void DEC_SP();
		void INC_SP();
		void LD_SP_N16(u16 n);
		void LD_N16_SP(u16 n);
		void LD_HL_SP_S8(s8 s);
		void LD_SP_HL();
		void POP_AF();
		void POP_R16(Register16& r);
		void PUSH_AF();
		void PUSH_R16(Register16& r);

			// Interrupt Related
		void DI();
		void EI();
		void HALT();

			// Miscellaneous
		void DAA();
		void NOP();
		void STOP();

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