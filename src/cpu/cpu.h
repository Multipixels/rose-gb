#pragma once
#include "../utility/definitions.h"

namespace cpu
{
	class CPU
	{
	public:
		void interpretInstruction();
	private:
		// Registers
		// Each 16 bits. BC, DE, FE can act as two 8-bit registers.
		// First 8 bits of accumulatorFlags is register A, last 8 bits are flags.

		// Flags
		// bit 7 "z": zero flag. used for conditional jumps, set if result of operation is 0
		// bit 6 "n": subtraction flag
		// bit 5 "h": half carry flag
		// bit 4 "c": carry flag
		u16 accumulatorFlags;
		u16 bc; 
		u16 de;
		u16 hl;
		u16 stackPointer;
		u16 programCounter;

		// CPU Instructions
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
		void op_cb00(); void op_cb01(); void op_cb02(); void op_cb03(); void op_cb04(); void op_cb05(); void op_cb06(); void op_cb07(); void op_cb08(); void op_cb09(); void op_cb0A(); void op_cb0B(); void op_cb0C(); void op_cb0D(); void op_cb0E(); void op_cb0F();
		void op_cb10(); void op_cb11(); void op_cb12(); void op_cb13(); void op_cb14(); void op_cb15(); void op_cb16(); void op_cb17(); void op_cb18(); void op_cb19(); void op_cb1A(); void op_cb1B(); void op_cb1C(); void op_cb1D(); void op_cb1E(); void op_cb1F();
		void op_cb20(); void op_cb21(); void op_cb22(); void op_cb23(); void op_cb24(); void op_cb25(); void op_cb26(); void op_cb27(); void op_cb28(); void op_cb29(); void op_cb2A(); void op_cb2B(); void op_cb2C(); void op_cb2D(); void op_cb2E(); void op_cb2F();
		void op_cb30(); void op_cb31(); void op_cb32(); void op_cb33(); void op_cb34(); void op_cb35(); void op_cb36(); void op_cb37(); void op_cb38(); void op_cb39(); void op_cb3A(); void op_cb3B(); void op_cb3C(); void op_cb3D(); void op_cb3E(); void op_cb3F();
		void op_cb40(); void op_cb41(); void op_cb42(); void op_cb43(); void op_cb44(); void op_cb45(); void op_cb46(); void op_cb47(); void op_cb48(); void op_cb49(); void op_cb4A(); void op_cb4B(); void op_cb4C(); void op_cb4D(); void op_cb4E(); void op_cb4F();
		void op_cb50(); void op_cb51(); void op_cb52(); void op_cb53(); void op_cb54(); void op_cb55(); void op_cb56(); void op_cb57(); void op_cb58(); void op_cb59(); void op_cb5A(); void op_cb5B(); void op_cb5C(); void op_cb5D(); void op_cb5E(); void op_cb5F();
		void op_cb60(); void op_cb61(); void op_cb62(); void op_cb63(); void op_cb64(); void op_cb65(); void op_cb66(); void op_cb67(); void op_cb68(); void op_cb69(); void op_cb6A(); void op_cb6B(); void op_cb6C(); void op_cb6D(); void op_cb6E(); void op_cb6F();
		void op_cb70(); void op_cb71(); void op_cb72(); void op_cb73(); void op_cb74(); void op_cb75(); void op_cb76(); void op_cb77(); void op_cb78(); void op_cb79(); void op_cb7A(); void op_cb7B(); void op_cb7C(); void op_cb7D(); void op_cb7E(); void op_cb7F();
		void op_cb80(); void op_cb81(); void op_cb82(); void op_cb83(); void op_cb84(); void op_cb85(); void op_cb86(); void op_cb87(); void op_cb88(); void op_cb89(); void op_cb8A(); void op_cb8B(); void op_cb8C(); void op_cb8D(); void op_cb8E(); void op_cb8F();
		void op_cb90(); void op_cb91(); void op_cb92(); void op_cb93(); void op_cb94(); void op_cb95(); void op_cb96(); void op_cb97(); void op_cb98(); void op_cb99(); void op_cb9A(); void op_cb9B(); void op_cb9C(); void op_cb9D(); void op_cb9E(); void op_cb9F();
		void op_cbA0(); void op_cbA1(); void op_cbA2(); void op_cbA3(); void op_cbA4(); void op_cbA5(); void op_cbA6(); void op_cbA7(); void op_cbA8(); void op_cbA9(); void op_cbAA(); void op_cbAB(); void op_cbAC(); void op_cbAD(); void op_cbAE(); void op_cbAF();
		void op_cbB0(); void op_cbB1(); void op_cbB2(); void op_cbB3(); void op_cbB4(); void op_cbB5(); void op_cbB6(); void op_cbB7(); void op_cbB8(); void op_cbB9(); void op_cbBA(); void op_cbBB(); void op_cbBC(); void op_cbBD(); void op_cbBE(); void op_cbBF();
		void op_cbC0(); void op_cbC1(); void op_cbC2(); void op_cbC3(); void op_cbC4(); void op_cbC5(); void op_cbC6(); void op_cbC7(); void op_cbC8(); void op_cbC9(); void op_cbCA(); void op_cbCB(); void op_cbCC(); void op_cbCD(); void op_cbCE(); void op_cbCF();
		void op_cbD0(); void op_cbD1(); void op_cbD2(); void op_cbD3(); void op_cbD4(); void op_cbD5(); void op_cbD6(); void op_cbD7(); void op_cbD8(); void op_cbD9(); void op_cbDA(); void op_cbDB(); void op_cbDC(); void op_cbDD(); void op_cbDE(); void op_cbDF();
		void op_cbE0(); void op_cbE1(); void op_cbE2(); void op_cbE3(); void op_cbE4(); void op_cbE5(); void op_cbE6(); void op_cbE7(); void op_cbE8(); void op_cbE9(); void op_cbEA(); void op_cbEB(); void op_cbEC(); void op_cbED(); void op_cbEE(); void op_cbEF();
		void op_cbF0(); void op_cbF1(); void op_cbF2(); void op_cbF3(); void op_cbF4(); void op_cbF5(); void op_cbF6(); void op_cbF7(); void op_cbF8(); void op_cbF9(); void op_cbFA(); void op_cbFB(); void op_cbFC(); void op_cbFD(); void op_cbFE(); void op_cbFF();
	};
}