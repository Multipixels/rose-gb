#include "cpu.h"

#include "iostream"

namespace rose_core {

	CPU::CPU(MMU& p_mmu)
		: m_mmu(p_mmu)
	{
	}

	CPU::CPU(MMU& p_mmu, u16 p_programCounterStart)
		: m_mmu(p_mmu)
	{
		m_registers.programCounter = p_programCounterStart;
	}

	void CPU::executeInstruction()
	{
		if (m_registers.programCounter > 0xFFFF) throw;
		switch (getByte()) {
		case 0x00: op_00(); break; case 0x01: op_01(); break; case 0x02: op_02(); break; case 0x03: op_03(); break;
		case 0x04: op_04(); break; case 0x05: op_05(); break; case 0x06: op_06(); break; case 0x07: op_07(); break;
		case 0x08: op_08(); break; case 0x09: op_09(); break; case 0x0A: op_0A(); break; case 0x0B: op_0B(); break;
		case 0x0C: op_0C(); break; case 0x0D: op_0D(); break; case 0x0E: op_0E(); break; case 0x0F: op_0F(); break;

		case 0x10: op_10(); break; case 0x11: op_11(); break; case 0x12: op_12(); break; case 0x13: op_13(); break;
		case 0x14: op_14(); break; case 0x15: op_15(); break; case 0x16: op_16(); break; case 0x17: op_17(); break;
		case 0x18: op_18(); break; case 0x19: op_19(); break; case 0x1A: op_1A(); break; case 0x1B: op_1B(); break;
		case 0x1C: op_1C(); break; case 0x1D: op_1D(); break; case 0x1E: op_1E(); break; case 0x1F: op_1F(); break;

		case 0x20: op_20(); break; case 0x21: op_21(); break; case 0x22: op_22(); break; case 0x23: op_23(); break;
		case 0x24: op_24(); break; case 0x25: op_25(); break; case 0x26: op_26(); break; case 0x27: op_27(); break;
		case 0x28: op_28(); break; case 0x29: op_29(); break; case 0x2A: op_2A(); break; case 0x2B: op_2B(); break;
		case 0x2C: op_2C(); break; case 0x2D: op_2D(); break; case 0x2E: op_2E(); break; case 0x2F: op_2F(); break;

		case 0x30: op_30(); break; case 0x31: op_31(); break; case 0x32: op_32(); break; case 0x33: op_33(); break;
		case 0x34: op_34(); break; case 0x35: op_35(); break; case 0x36: op_36(); break; case 0x37: op_37(); break;
		case 0x38: op_38(); break; case 0x39: op_39(); break; case 0x3A: op_3A(); break; case 0x3B: op_3B(); break;
		case 0x3C: op_3C(); break; case 0x3D: op_3D(); break; case 0x3E: op_3E(); break; case 0x3F: op_3F(); break;

		case 0x40: op_40(); break; case 0x41: op_41(); break; case 0x42: op_42(); break; case 0x43: op_43(); break;
		case 0x44: op_44(); break; case 0x45: op_45(); break; case 0x46: op_46(); break; case 0x47: op_47(); break;
		case 0x48: op_48(); break; case 0x49: op_49(); break; case 0x4A: op_4A(); break; case 0x4B: op_4B(); break;
		case 0x4C: op_4C(); break; case 0x4D: op_4D(); break; case 0x4E: op_4E(); break; case 0x4F: op_4F(); break;

		case 0x50: op_50(); break; case 0x51: op_51(); break; case 0x52: op_52(); break; case 0x53: op_53(); break;
		case 0x54: op_54(); break; case 0x55: op_55(); break; case 0x56: op_56(); break; case 0x57: op_57(); break;
		case 0x58: op_58(); break; case 0x59: op_59(); break; case 0x5A: op_5A(); break; case 0x5B: op_5B(); break;
		case 0x5C: op_5C(); break; case 0x5D: op_5D(); break; case 0x5E: op_5E(); break; case 0x5F: op_5F(); break;

		case 0x60: op_60(); break; case 0x61: op_61(); break; case 0x62: op_62(); break; case 0x63: op_63(); break;
		case 0x64: op_64(); break; case 0x65: op_65(); break; case 0x66: op_66(); break; case 0x67: op_67(); break;
		case 0x68: op_68(); break; case 0x69: op_69(); break; case 0x6A: op_6A(); break; case 0x6B: op_6B(); break;
		case 0x6C: op_6C(); break; case 0x6D: op_6D(); break; case 0x6E: op_6E(); break; case 0x6F: op_6F(); break;

		case 0x70: op_70(); break; case 0x71: op_71(); break; case 0x72: op_72(); break; case 0x73: op_73(); break;
		case 0x74: op_74(); break; case 0x75: op_75(); break; case 0x76: op_76(); break; case 0x77: op_77(); break;
		case 0x78: op_78(); break; case 0x79: op_79(); break; case 0x7A: op_7A(); break; case 0x7B: op_7B(); break;
		case 0x7C: op_7C(); break; case 0x7D: op_7D(); break; case 0x7E: op_7E(); break; case 0x7F: op_7F(); break;

		case 0x80: op_80(); break; case 0x81: op_81(); break; case 0x82: op_82(); break; case 0x83: op_83(); break;
		case 0x84: op_84(); break; case 0x85: op_85(); break; case 0x86: op_86(); break; case 0x87: op_87(); break;
		case 0x88: op_88(); break; case 0x89: op_89(); break; case 0x8A: op_8A(); break; case 0x8B: op_8B(); break;
		case 0x8C: op_8C(); break; case 0x8D: op_8D(); break; case 0x8E: op_8E(); break; case 0x8F: op_8F(); break;

		case 0x90: op_90(); break; case 0x91: op_91(); break; case 0x92: op_92(); break; case 0x93: op_93(); break;
		case 0x94: op_94(); break; case 0x95: op_95(); break; case 0x96: op_96(); break; case 0x97: op_97(); break;
		case 0x98: op_98(); break; case 0x99: op_99(); break; case 0x9A: op_9A(); break; case 0x9B: op_9B(); break;
		case 0x9C: op_9C(); break; case 0x9D: op_9D(); break; case 0x9E: op_9E(); break; case 0x9F: op_9F(); break;

		case 0xA0: op_A0(); break; case 0xA1: op_A1(); break; case 0xA2: op_A2(); break; case 0xA3: op_A3(); break;
		case 0xA4: op_A4(); break; case 0xA5: op_A5(); break; case 0xA6: op_A6(); break; case 0xA7: op_A7(); break;
		case 0xA8: op_A8(); break; case 0xA9: op_A9(); break; case 0xAA: op_AA(); break; case 0xAB: op_AB(); break;
		case 0xAC: op_AC(); break; case 0xAD: op_AD(); break; case 0xAE: op_AE(); break; case 0xAF: op_AF(); break;

		case 0xB0: op_B0(); break; case 0xB1: op_B1(); break; case 0xB2: op_B2(); break; case 0xB3: op_B3(); break;
		case 0xB4: op_B4(); break; case 0xB5: op_B5(); break; case 0xB6: op_B6(); break; case 0xB7: op_B7(); break;
		case 0xB8: op_B8(); break; case 0xB9: op_B9(); break; case 0xBA: op_BA(); break; case 0xBB: op_BB(); break;
		case 0xBC: op_BC(); break; case 0xBD: op_BD(); break; case 0xBE: op_BE(); break; case 0xBF: op_BF(); break;

		case 0xC0: op_C0(); break; case 0xC1: op_C1(); break; case 0xC2: op_C2(); break; case 0xC3: op_C3(); break;
		case 0xC4: op_C4(); break; case 0xC5: op_C5(); break; case 0xC6: op_C6(); break; case 0xC7: op_C7(); break;
		case 0xC8: op_C8(); break; case 0xC9: op_C9(); break; case 0xCA: op_CA(); break; case 0xCB: op_CB(); break;
		case 0xCC: op_CC(); break; case 0xCD: op_CD(); break; case 0xCE: op_CE(); break; case 0xCF: op_CF(); break;

		case 0xD0: op_D0(); break; case 0xD1: op_D1(); break; case 0xD2: op_D2(); break; case 0xD3: op_D3(); break;
		case 0xD4: op_D4(); break; case 0xD5: op_D5(); break; case 0xD6: op_D6(); break; case 0xD7: op_D7(); break;
		case 0xD8: op_D8(); break; case 0xD9: op_D9(); break; case 0xDA: op_DA(); break; case 0xDB: op_DB(); break;
		case 0xDC: op_DC(); break; case 0xDD: op_DD(); break; case 0xDE: op_DE(); break; case 0xDF: op_DF(); break;

		case 0xE0: op_E0(); break; case 0xE1: op_E1(); break; case 0xE2: op_E2(); break; case 0xE3: op_E3(); break;
		case 0xE4: op_E4(); break; case 0xE5: op_E5(); break; case 0xE6: op_E6(); break; case 0xE7: op_E7(); break;
		case 0xE8: op_E8(); break; case 0xE9: op_E9(); break; case 0xEA: op_EA(); break; case 0xEB: op_EB(); break;
		case 0xEC: op_EC(); break; case 0xED: op_ED(); break; case 0xEE: op_EE(); break; case 0xEF: op_EF(); break;

		case 0xF0: op_F0(); break; case 0xF1: op_F1(); break; case 0xF2: op_F2(); break; case 0xF3: op_F3(); break;
		case 0xF4: op_F4(); break; case 0xF5: op_F5(); break; case 0xF6: op_F6(); break; case 0xF7: op_F7(); break;
		case 0xF8: op_F8(); break; case 0xF9: op_F9(); break; case 0xFA: op_FA(); break; case 0xFB: op_FB(); break;
		case 0xFC: op_FC(); break; case 0xFD: op_FD(); break; case 0xFE: op_FE(); break; case 0xFF: op_FF(); break;
		}
	}

	void CPU::executeCBInstruction()
	{
		if (m_registers.programCounter > 0xFFFF) throw;
		switch (getByte()) {
		case 0x00: op_cb_00(); break; case 0x01: op_cb_01(); break; case 0x02: op_cb_02(); break; case 0x03: op_cb_03(); break;
		case 0x04: op_cb_04(); break; case 0x05: op_cb_05(); break; case 0x06: op_cb_06(); break; case 0x07: op_cb_07(); break;
		case 0x08: op_cb_08(); break; case 0x09: op_cb_09(); break; case 0x0A: op_cb_0A(); break; case 0x0B: op_cb_0B(); break;
		case 0x0C: op_cb_0C(); break; case 0x0D: op_cb_0D(); break; case 0x0E: op_cb_0E(); break; case 0x0F: op_cb_0F(); break;

		case 0x10: op_cb_10(); break; case 0x11: op_cb_11(); break; case 0x12: op_cb_12(); break; case 0x13: op_cb_13(); break;
		case 0x14: op_cb_14(); break; case 0x15: op_cb_15(); break; case 0x16: op_cb_16(); break; case 0x17: op_cb_17(); break;
		case 0x18: op_cb_18(); break; case 0x19: op_cb_19(); break; case 0x1A: op_cb_1A(); break; case 0x1B: op_cb_1B(); break;
		case 0x1C: op_cb_1C(); break; case 0x1D: op_cb_1D(); break; case 0x1E: op_cb_1E(); break; case 0x1F: op_cb_1F(); break;

		case 0x20: op_cb_20(); break; case 0x21: op_cb_21(); break; case 0x22: op_cb_22(); break; case 0x23: op_cb_23(); break;
		case 0x24: op_cb_24(); break; case 0x25: op_cb_25(); break; case 0x26: op_cb_26(); break; case 0x27: op_cb_27(); break;
		case 0x28: op_cb_28(); break; case 0x29: op_cb_29(); break; case 0x2A: op_cb_2A(); break; case 0x2B: op_cb_2B(); break;
		case 0x2C: op_cb_2C(); break; case 0x2D: op_cb_2D(); break; case 0x2E: op_cb_2E(); break; case 0x2F: op_cb_2F(); break;

		case 0x30: op_cb_30(); break; case 0x31: op_cb_31(); break; case 0x32: op_cb_32(); break; case 0x33: op_cb_33(); break;
		case 0x34: op_cb_34(); break; case 0x35: op_cb_35(); break; case 0x36: op_cb_36(); break; case 0x37: op_cb_37(); break;
		case 0x38: op_cb_38(); break; case 0x39: op_cb_39(); break; case 0x3A: op_cb_3A(); break; case 0x3B: op_cb_3B(); break;
		case 0x3C: op_cb_3C(); break; case 0x3D: op_cb_3D(); break; case 0x3E: op_cb_3E(); break; case 0x3F: op_cb_3F(); break;

		case 0x40: op_cb_40(); break; case 0x41: op_cb_41(); break; case 0x42: op_cb_42(); break; case 0x43: op_cb_43(); break;
		case 0x44: op_cb_44(); break; case 0x45: op_cb_45(); break; case 0x46: op_cb_46(); break; case 0x47: op_cb_47(); break;
		case 0x48: op_cb_48(); break; case 0x49: op_cb_49(); break; case 0x4A: op_cb_4A(); break; case 0x4B: op_cb_4B(); break;
		case 0x4C: op_cb_4C(); break; case 0x4D: op_cb_4D(); break; case 0x4E: op_cb_4E(); break; case 0x4F: op_cb_4F(); break;

		case 0x50: op_cb_50(); break; case 0x51: op_cb_51(); break; case 0x52: op_cb_52(); break; case 0x53: op_cb_53(); break;
		case 0x54: op_cb_54(); break; case 0x55: op_cb_55(); break; case 0x56: op_cb_56(); break; case 0x57: op_cb_57(); break;
		case 0x58: op_cb_58(); break; case 0x59: op_cb_59(); break; case 0x5A: op_cb_5A(); break; case 0x5B: op_cb_5B(); break;
		case 0x5C: op_cb_5C(); break; case 0x5D: op_cb_5D(); break; case 0x5E: op_cb_5E(); break; case 0x5F: op_cb_5F(); break;

		case 0x60: op_cb_60(); break; case 0x61: op_cb_61(); break; case 0x62: op_cb_62(); break; case 0x63: op_cb_63(); break;
		case 0x64: op_cb_64(); break; case 0x65: op_cb_65(); break; case 0x66: op_cb_66(); break; case 0x67: op_cb_67(); break;
		case 0x68: op_cb_68(); break; case 0x69: op_cb_69(); break; case 0x6A: op_cb_6A(); break; case 0x6B: op_cb_6B(); break;
		case 0x6C: op_cb_6C(); break; case 0x6D: op_cb_6D(); break; case 0x6E: op_cb_6E(); break; case 0x6F: op_cb_6F(); break;

		case 0x70: op_cb_70(); break; case 0x71: op_cb_71(); break; case 0x72: op_cb_72(); break; case 0x73: op_cb_73(); break;
		case 0x74: op_cb_74(); break; case 0x75: op_cb_75(); break; case 0x76: op_cb_76(); break; case 0x77: op_cb_77(); break;
		case 0x78: op_cb_78(); break; case 0x79: op_cb_79(); break; case 0x7A: op_cb_7A(); break; case 0x7B: op_cb_7B(); break;
		case 0x7C: op_cb_7C(); break; case 0x7D: op_cb_7D(); break; case 0x7E: op_cb_7E(); break; case 0x7F: op_cb_7F(); break;

		case 0x80: op_cb_80(); break; case 0x81: op_cb_81(); break; case 0x82: op_cb_82(); break; case 0x83: op_cb_83(); break;
		case 0x84: op_cb_84(); break; case 0x85: op_cb_85(); break; case 0x86: op_cb_86(); break; case 0x87: op_cb_87(); break;
		case 0x88: op_cb_88(); break; case 0x89: op_cb_89(); break; case 0x8A: op_cb_8A(); break; case 0x8B: op_cb_8B(); break;
		case 0x8C: op_cb_8C(); break; case 0x8D: op_cb_8D(); break; case 0x8E: op_cb_8E(); break; case 0x8F: op_cb_8F(); break;

		case 0x90: op_cb_90(); break; case 0x91: op_cb_91(); break; case 0x92: op_cb_92(); break; case 0x93: op_cb_93(); break;
		case 0x94: op_cb_94(); break; case 0x95: op_cb_95(); break; case 0x96: op_cb_96(); break; case 0x97: op_cb_97(); break;
		case 0x98: op_cb_98(); break; case 0x99: op_cb_99(); break; case 0x9A: op_cb_9A(); break; case 0x9B: op_cb_9B(); break;
		case 0x9C: op_cb_9C(); break; case 0x9D: op_cb_9D(); break; case 0x9E: op_cb_9E(); break; case 0x9F: op_cb_9F(); break;

		case 0xA0: op_cb_A0(); break; case 0xA1: op_cb_A1(); break; case 0xA2: op_cb_A2(); break; case 0xA3: op_cb_A3(); break;
		case 0xA4: op_cb_A4(); break; case 0xA5: op_cb_A5(); break; case 0xA6: op_cb_A6(); break; case 0xA7: op_cb_A7(); break;
		case 0xA8: op_cb_A8(); break; case 0xA9: op_cb_A9(); break; case 0xAA: op_cb_AA(); break; case 0xAB: op_cb_AB(); break;
		case 0xAC: op_cb_AC(); break; case 0xAD: op_cb_AD(); break; case 0xAE: op_cb_AE(); break; case 0xAF: op_cb_AF(); break;

		case 0xB0: op_cb_B0(); break; case 0xB1: op_cb_B1(); break; case 0xB2: op_cb_B2(); break; case 0xB3: op_cb_B3(); break;
		case 0xB4: op_cb_B4(); break; case 0xB5: op_cb_B5(); break; case 0xB6: op_cb_B6(); break; case 0xB7: op_cb_B7(); break;
		case 0xB8: op_cb_B8(); break; case 0xB9: op_cb_B9(); break; case 0xBA: op_cb_BA(); break; case 0xBB: op_cb_BB(); break;
		case 0xBC: op_cb_BC(); break; case 0xBD: op_cb_BD(); break; case 0xBE: op_cb_BE(); break; case 0xBF: op_cb_BF(); break;

		case 0xC0: op_cb_C0(); break; case 0xC1: op_cb_C1(); break; case 0xC2: op_cb_C2(); break; case 0xC3: op_cb_C3(); break;
		case 0xC4: op_cb_C4(); break; case 0xC5: op_cb_C5(); break; case 0xC6: op_cb_C6(); break; case 0xC7: op_cb_C7(); break;
		case 0xC8: op_cb_C8(); break; case 0xC9: op_cb_C9(); break; case 0xCA: op_cb_CA(); break; case 0xCB: op_cb_CB(); break;
		case 0xCC: op_cb_CC(); break; case 0xCD: op_cb_CD(); break; case 0xCE: op_cb_CE(); break; case 0xCF: op_cb_CF(); break;

		case 0xD0: op_cb_D0(); break; case 0xD1: op_cb_D1(); break; case 0xD2: op_cb_D2(); break; case 0xD3: op_cb_D3(); break;
		case 0xD4: op_cb_D4(); break; case 0xD5: op_cb_D5(); break; case 0xD6: op_cb_D6(); break; case 0xD7: op_cb_D7(); break;
		case 0xD8: op_cb_D8(); break; case 0xD9: op_cb_D9(); break; case 0xDA: op_cb_DA(); break; case 0xDB: op_cb_DB(); break;
		case 0xDC: op_cb_DC(); break; case 0xDD: op_cb_DD(); break; case 0xDE: op_cb_DE(); break; case 0xDF: op_cb_DF(); break;

		case 0xE0: op_cb_E0(); break; case 0xE1: op_cb_E1(); break; case 0xE2: op_cb_E2(); break; case 0xE3: op_cb_E3(); break;
		case 0xE4: op_cb_E4(); break; case 0xE5: op_cb_E5(); break; case 0xE6: op_cb_E6(); break; case 0xE7: op_cb_E7(); break;
		case 0xE8: op_cb_E8(); break; case 0xE9: op_cb_E9(); break; case 0xEA: op_cb_EA(); break; case 0xEB: op_cb_EB(); break;
		case 0xEC: op_cb_EC(); break; case 0xED: op_cb_ED(); break; case 0xEE: op_cb_EE(); break; case 0xEF: op_cb_EF(); break;

		case 0xF0: op_cb_F0(); break; case 0xF1: op_cb_F1(); break; case 0xF2: op_cb_F2(); break; case 0xF3: op_cb_F3(); break;
		case 0xF4: op_cb_F4(); break; case 0xF5: op_cb_F5(); break; case 0xF6: op_cb_F6(); break; case 0xF7: op_cb_F7(); break;
		case 0xF8: op_cb_F8(); break; case 0xF9: op_cb_F9(); break; case 0xFA: op_cb_FA(); break; case 0xFB: op_cb_FB(); break;
		case 0xFC: op_cb_FC(); break; case 0xFD: op_cb_FD(); break; case 0xFE: op_cb_FE(); break; case 0xFF: op_cb_FF(); break;
		}
	}

	u8 CPU::getByte()
	{
		u8 returnValue = m_mmu.getU8(m_registers.programCounter);
		m_registers.programCounter++;
		return returnValue;
	}

	u16 CPU::getBytePair()
	{
		u16 returnValue = m_mmu.getU16(m_registers.programCounter);
		m_registers.programCounter += 2;
		return returnValue;
	}

	const CPU::Registers& CPU::viewRegisters() const
	{
		return m_registers;
	}

	u8 CPU::convertRSTVec(RSTVec p_vec)
	{
		switch (p_vec) {
		case x00: return 0x00;
		case x08: return 0x08;
		case x10: return 0x10;
		case x18: return 0x18;
		case x20: return 0x20;
		case x28: return 0x28;
		case x30: return 0x30;
		case x38: return 0x38;
		}
		return 0x00;
	}

	CPU::Flag CPU::getFlagZ() { return (m_registers.f & 0b10000000) >> 7; }
	CPU::Flag CPU::getFlagN() { return (m_registers.f & 0b01000000) >> 6; }
	CPU::Flag CPU::getFlagH() { return (m_registers.f & 0b00100000) >> 5; }
	CPU::Flag CPU::getFlagC() { return (m_registers.f & 0b00010000) >> 4; }

	// https://stackoverflow.com/questions/47981/how-to-set-clear-and-toggle-a-single-bit
	void CPU::setFlagZ(bool p_value) { m_registers.f = (m_registers.f & ~(1 << 7)) | (p_value << 7); }
	void CPU::setFlagN(bool p_value) { m_registers.f = (m_registers.f & ~(1 << 6)) | (p_value << 6); }
	void CPU::setFlagH(bool p_value) { m_registers.f = (m_registers.f & ~(1 << 5)) | (p_value << 5); }
	void CPU::setFlagC(bool p_value) { m_registers.f = (m_registers.f & ~(1 << 4)) | (p_value << 4); }

	void CPU::setFlags(u4 p_value) { m_registers.f = p_value.value; }
	void CPU::setFlags(bool p_z, bool p_n, bool p_h, bool p_c) { m_registers.f = (p_z << 7) | (p_n << 6) | (p_h << 5) | (p_c << 4); }

	void CPU::setFlagsForU8Overflow(u16 p_a, u16 p_b, u16 p_c)
	{
		u8 res = p_a + p_b + p_c;
		if (res == 0) setFlagZ(true);
		else setFlagZ(false);

		setFlagN(false);

		u8 halfRes = (p_a & 0x0F) + (p_b & 0x0F) + p_c;
		if (halfRes >= 0x10) setFlagH(true);
		else setFlagH(false);

		u16 overflowRes = p_a + p_b + p_c;
		if (overflowRes >= 0x0100) setFlagC(true);
		else setFlagC(false);
	}

	void CPU::setFlagsForU8Overflow(u16 p_a, u16 p_b)
	{
		u8 res = p_a + p_b;
		if (res == 0) setFlagZ(true);
		else setFlagZ(false);

		setFlagN(false);

		u8 halfRes = (p_a & 0x0F) + (p_b & 0x0F);
		if (halfRes >= 0x10) setFlagH(true);
		else setFlagH(false);

		u16 overflowRes = p_a + p_b;
		if (overflowRes >= 0x0100) setFlagC(true);
		else setFlagC(false);
	}

	void CPU::setFlagsForU16Overflow(u16 p_a, u16 p_b)
	{
		u16 res = p_a + p_b;
		if (res == 0) setFlagZ(true);
		else setFlagZ(false);

		setFlagN(false);

		u16 halfRes = (p_a & 0x0FFF) + (p_b & 0x0FFF);
		if (halfRes >= 0x1000) setFlagH(true);
		else setFlagH(false);

		u32 overflowRes = p_a + p_b;
		if (overflowRes >= 0x10000) setFlagC(true);
		else setFlagC(false);
	}

	void CPU::setFlagsForU8Borrow(u8 p_a, u8 p_b)
	{
		u8 res = p_a - p_b;
		if (res == 0) setFlagZ(true);
		else setFlagZ(false);

		setFlagN(true);

		if ((p_a & 0x0F) < (p_b & 0x0F)) setFlagH(true);
		else setFlagH(false);

		if (p_a < p_b) setFlagC(true);
		else setFlagC(false);
	}

	void CPU::setFlagsForU8Borrow(u8 p_a, u8 p_b, u8 p_c)
	{
		u8 res = p_a - p_b - p_c;
		if (res == 0) setFlagZ(true);
		else setFlagZ(false);

		setFlagN(true);

		if ((p_a & 0x0F) < ((p_b + p_c) & 0x0F)) setFlagH(true);
		else setFlagH(false);

		if (p_a < p_b + p_c) setFlagC(true);
		else setFlagC(false);
	}

	bool CPU::willHalfCarry(u8 p_a, u8 p_b, bool p_add)
	{
		if (p_add)
			return (p_a & 0xF) + (p_b & 0xF) > 0x10;
		else
			return (p_a & 0xF) < (p_b & 0xF);
	}

	bool CPU::willHalfCarry(u16 p_a, u16 p_b, bool p_add)
	{
		if (p_add)
			return (p_a & 0xFFF) + (p_b & 0xFFF) > 0x1000;
		else
			return p_a < p_b;
	}

	bool CPU::willCarry(u8 p_a, u8 p_b, bool p_add)
	{
		if (p_add)
			return (u16)p_a + (u16)p_b > 0x100;
		else
			return p_a < p_b;
	}

	bool CPU::willCarry(u16 p_a, u16 p_b, bool p_add)
	{
		if (p_add)
			return (u32)p_a + (u32)p_b > 0x10000;
		else
			return p_a < p_b;
	}

	u8 CPU::signedToPositiveUnsigned(s8 n)
	{
		if (n >= 0) return n;
		return ~n + 1;
	}

	u16 CPU::signedToPositiveUnsigned(s16 n)
	{
		if (n >= 0) return n;
		return ~n + 1;
	}

	bool CPU::ccStatus(ConditionCode p_cc)
	{
		switch (p_cc) {
		case Z: return getFlagZ();
		case NZ: return !getFlagZ();
		case C: return getFlagC();
		case NC: return !getFlagC();
		}
		return false;
	}

	// Loads
	void CPU::LD_R8_R8(Register8& p_ra, Register8& p_rb) { p_ra = p_rb; }
	void CPU::LD_R8_N8(Register8& p_r, u8 p_n) { p_r = p_n; }
	void CPU::LD_R16_N16(Register16& p_r, u16 p_n) { p_r = p_n; }
	void CPU::LD_HL_R8(Register8& p_r) { m_mmu.setU8(m_registers.hl, p_r); }
	void CPU::LD_HL_N8(u8 p_n) { m_mmu.setU8(m_registers.hl, p_n); }
	void CPU::LD_R8_HL(Register8& p_r) { p_r = m_mmu.getU8(m_registers.hl); }
	void CPU::LD_R16_A(Register16& p_r) { m_mmu.setU8(p_r, m_registers.a); }
	void CPU::LD_N16_A(u16 p_n) { m_mmu.setU8(p_n, m_registers.a); }
	void CPU::LDH_N16_A(u8 p_n) { m_mmu.setU8(0xFF00 + p_n, m_registers.a); }
	void CPU::LDH_C_A() { m_mmu.setU8(0xFF00 + m_registers.c, m_registers.a); }
	void CPU::LD_A_R16(Register16& p_r) { m_registers.a = m_mmu.getU8(p_r); }
	void CPU::LD_A_N16(u16 p_n) { m_registers.a = m_mmu.getU8(p_n); }
	void CPU::LDH_A_N16(u8 p_n) { m_registers.a = m_mmu.getU8(0xFF00 + p_n); }
	void CPU::LDH_A_C() { m_registers.a = m_mmu.getU8(0xFF00 + m_registers.c); }
	void CPU::LD_HLI_A() { m_mmu.setU8(m_registers.hl, m_registers.a); m_registers.hl++; }
	void CPU::LD_HLD_A() { m_mmu.setU8(m_registers.hl, m_registers.a); m_registers.hl--; }
	void CPU::LD_A_HLI() { m_registers.a = m_mmu.getU8(m_registers.hl); m_registers.hl++; }
	void CPU::LD_A_HLD() { m_registers.a = m_mmu.getU8(m_registers.hl); m_registers.hl--; }

	// 8-bit Arithmetic
	void CPU::ADC_A_R8(Register8& p_r) { Flag isCarry = getFlagC(); setFlagsForU8Overflow(m_registers.a, p_r, getFlagC()); m_registers.a += p_r + isCarry; }
	void CPU::ADC_A_HL() { Flag isCarry = getFlagC();  setFlagsForU8Overflow(m_registers.a, m_mmu.getU8(m_registers.hl), getFlagC()); m_registers.a += m_mmu.getU8(m_registers.hl) + isCarry;  }
	void CPU::ADC_A_N8(u8 p_n) { Flag isCarry = getFlagC(); setFlagsForU8Overflow(m_registers.a, p_n, getFlagC()); m_registers.a += p_n + isCarry;  }
	void CPU::ADD_A_R8(Register8& p_r) { setFlagsForU8Overflow(m_registers.a, p_r); m_registers.a += p_r;  }
	void CPU::ADD_A_HL() { setFlagsForU8Overflow(m_registers.a, m_mmu.getU8(m_registers.hl)); m_registers.a += m_mmu.getU8(m_registers.hl);  }
	void CPU::ADD_A_N8(u8 p_n) { setFlagsForU8Overflow(m_registers.a, p_n); m_registers.a += p_n;  }
	void CPU::CP_A_R8(Register8& p_r) { setFlagsForU8Borrow(m_registers.a, p_r); }
	void CPU::CP_A_HL() { setFlagsForU8Borrow(m_registers.a, m_mmu.getU8(m_registers.hl)); }
	void CPU::CP_A_N8(u8 p_n) { setFlagsForU8Borrow(m_registers.a, p_n); }
	void CPU::DEC_R8(Register8& p_r) { if ((p_r & 0xF) == 0b0000) { setFlagH(true); } else { setFlagH(false); } p_r--; setFlagN(true);  if (p_r == 0) { setFlagZ(true); } else { setFlagZ(false); } }
	void CPU::DEC_HL() { if ((m_mmu.getU8(m_registers.hl) & 0xF) == 0b0000) { setFlagH(true); } else { setFlagH(false); } m_mmu.setU8(m_registers.hl, m_mmu.getU8(m_registers.hl) - 1); setFlagN(true); if (m_mmu.getU8(m_registers.hl) == 0) { setFlagZ(true); } else { setFlagZ(false); } }
	void CPU::INC_R8(Register8& p_r) { if ((p_r & 0xF) == 0b1111) { setFlagH(true); } else { setFlagH(false); } (p_r)++; setFlagN(false); if (p_r == 0) { setFlagZ(true); } else { setFlagZ(false); } }
	void CPU::INC_HL() { if ((m_registers.hl & 0xF) == 0b1111) { setFlagH(true); } else { setFlagH(false); } m_mmu.setU8(m_registers.hl, m_mmu.getU8(m_registers.hl) + 1); setFlagN(false); if (m_registers.hl == 0) { setFlagZ(true); } else { setFlagZ(false); } }
	void CPU::SBC_A_R8(Register8& p_r) { Flag isCarry = getFlagC(); setFlagsForU8Borrow(m_registers.a, p_r, getFlagC()); m_registers.a = m_registers.a - p_r - isCarry;  }
	void CPU::SBC_A_HL() { Flag isCarry = getFlagC(); setFlagsForU8Borrow(m_registers.a, m_mmu.getU8(m_registers.hl), getFlagC()); m_registers.a = m_registers.a - m_mmu.getU8(m_registers.hl) - isCarry; }
	void CPU::SBC_A_N8(u8 p_n) { Flag isCarry = getFlagC(); setFlagsForU8Borrow(m_registers.a, p_n, getFlagC()); m_registers.a = m_registers.a - p_n - isCarry; }
	void CPU::SUB_A_R8(Register8& p_r) { setFlagsForU8Borrow(m_registers.a, p_r); m_registers.a = m_registers.a - p_r; }
	void CPU::SUB_A_HL() { setFlagsForU8Borrow(m_registers.a, m_mmu.getU8(m_registers.hl)); m_registers.a = m_registers.a - m_mmu.getU8(m_registers.hl); }
	void CPU::SUB_A_N8(u8 p_n) { setFlagsForU8Borrow(m_registers.a, p_n); m_registers.a = m_registers.a - p_n; }

	// 16-bit Arithmetic
	void CPU::ADD_HL_R16(Register16& p_r) { setFlagN(false); setFlagH(willHalfCarry(m_registers.hl, p_r, true)); setFlagC(willCarry(m_registers.hl, p_r, true)); m_registers.hl += p_r; }
	void CPU::DEC_R16(Register16& p_r) { p_r--; }
	void CPU::INC_R16(Register16& p_r) { p_r++; }

	// Bitwise Logic
	void CPU::AND_A_R8(Register8& p_r) { setFlags(!(m_registers.a & p_r), false, true, false); m_registers.a &= p_r;  }
	void CPU::AND_A_HL() { setFlags(!(m_registers.a & m_mmu.getU8(m_registers.hl)), false, 1, false); m_registers.a &= m_mmu.getU8(m_registers.hl);  }
	void CPU::AND_A_N8(u8 p_n) { setFlags(!(m_registers.a & p_n), false, true, false); m_registers.a &= p_n;  }
	void CPU::CPL() { m_registers.a = ~m_registers.a; setFlagN(true); setFlagH(true); }
	void CPU::OR_A_R8(Register8& p_r) { m_registers.a |= p_r; setFlags(!m_registers.a, false, false, false); }
	void CPU::OR_A_HL() { m_registers.a |= m_mmu.getU8(m_registers.hl); setFlags(!m_registers.a, false, false, false); }
	void CPU::OR_A_N8(u8 p_n) { m_registers.a |= p_n; setFlags(!m_registers.a, false, false, false); }
	void CPU::XOR_A_R8(Register8& p_r) { m_registers.a ^= p_r; setFlags(!m_registers.a, false, false, false); }
	void CPU::XOR_A_HL() { m_registers.a ^= m_mmu.getU8(m_registers.hl); setFlags(!m_registers.a, false, false, false); }
	void CPU::XOR_A_N8(u8 p_n) { m_registers.a ^= p_n; setFlags(!m_registers.a, false, false, false); }

	// Bit Flags
	void CPU::BIT_U3_R8(u3 p_u, Register8& p_r) { setFlags(!((p_r >> p_u.value) & 0b1), false, true, getFlagC()); }
	void CPU::BIT_U3_HL(u3 p_u) { setFlags(!((m_mmu.getU8(m_registers.hl) >> p_u.value) & 0x1), false, true, getFlagC()); }
	void CPU::RES_U3_R8(u3 p_u, Register8& p_r) { p_r &= ~(0xFF & (0b1 << p_u.value)); }
	void CPU::RES_U3_HL(u3 p_u) { m_mmu.setU8(m_registers.hl, m_mmu.getU8(m_registers.hl) & ~(0xFF & (0b1 << p_u.value))); }
	void CPU::SET_U3_R8(u3 p_u, Register8& p_r) { p_r |= (0b1 << p_u.value); }
	void CPU::SET_U3_HL(u3 p_u) { m_mmu.setU8(m_registers.hl, m_mmu.getU8(m_registers.hl) | (0b1 << p_u.value)); }

	// Bit Shifts
	void CPU::RL_R8(Register8& p_r) { u8 temp = p_r & 0x80; p_r = (p_r << 1) | (int)getFlagC(); setFlags(!p_r, false, false, temp);  }
	void CPU::RL_HL() { u8 temp = m_mmu.getU8(m_registers.hl) & 0x80; m_mmu.setU8(m_registers.hl, (m_mmu.getU8(m_registers.hl) << 1) | (int)getFlagC()); setFlags(!m_mmu.getU8(m_registers.hl), false, false, temp); }
	void CPU::RL_A() { u8 temp = m_registers.a & 0x80; m_registers.a = (m_registers.a << 1) | (int)getFlagC(); setFlags(false, false, false, temp); }
	void CPU::RL_C_R8(Register8& p_r) { u8 temp = p_r & 0x80; p_r = (p_r << 1) | (temp >> 7); setFlags(!p_r, false, false, temp); }
	void CPU::RL_C_HL() { u8 temp = m_mmu.getU8(m_registers.hl) & 0x80; m_mmu.setU8(m_registers.hl, (m_mmu.getU8(m_registers.hl) << 1) | (temp >> 7)); setFlags(!m_mmu.getU8(m_registers.hl), false, false, temp); }
	void CPU::RL_C_A() { u8 temp = m_registers.a & 0x80; m_registers.a = (m_registers.a << 1) | (temp >> 7); setFlags(false, false, false, temp); }
	void CPU::RR_R8(Register8& p_r) { u8 temp = p_r & 0x01; p_r = (p_r >> 1) | (getFlagC() << 7); setFlags(!p_r, false, false, temp); }
	void CPU::RR_HL() { u8 temp = m_mmu.getU8(m_registers.hl) & 0x01; m_mmu.setU8(m_registers.hl, (m_mmu.getU8(m_registers.hl) >> 1) | (getFlagC() << 7)); setFlags(!m_mmu.getU8(m_registers.hl), false, false, temp); }
	void CPU::RR_A() { u8 temp = m_registers.a & 0x01; m_registers.a = (m_registers.a >> 1) | (getFlagC() << 7); setFlags(false, false, false, temp); }
	void CPU::RR_C_R8(Register8& p_r) { u8 temp = p_r & 0x01; p_r = (p_r >> 1) | (temp << 7); setFlags(!p_r, false, false, temp); }
	void CPU::RR_C_HL() { u8 temp = m_mmu.getU8(m_registers.hl) & 0x01; m_mmu.setU8(m_registers.hl, (m_mmu.getU8(m_registers.hl) >> 1) | (temp << 7)); setFlags(!m_mmu.getU8(m_registers.hl), false, false, temp); }
	void CPU::RR_C_A() { u8 temp = m_registers.a & 0x01; m_registers.a = (m_registers.a >> 1) | (temp << 7); setFlags(false, false, false, temp); }
	void CPU::SLA_R8(Register8& p_r) { setFlags(0, 0, 0, p_r & 0x80); p_r = (p_r << 1); setFlagZ(!p_r); }
	void CPU::SLA_HL() { setFlags(0, 0, 0, m_mmu.getU8(m_registers.hl) & 0x80); m_mmu.setU8(m_registers.hl, m_mmu.getU8(m_registers.hl) << 1); setFlagZ(!m_mmu.getU8(m_registers.hl)); }
	void CPU::SRA_R8(Register8& p_r) { setFlags(0, 0, 0, p_r & 0x01);  p_r = (p_r & 0x80) | (p_r >> 1); setFlagZ(!p_r); }
	void CPU::SRA_HL() { setFlags(0, 0, 0, m_mmu.getU8(m_registers.hl) & 0x01); m_mmu.setU8(m_registers.hl, (m_mmu.getU8(m_registers.hl) & 0x80) | (m_mmu.getU8(m_registers.hl) >> 1)); setFlagZ(!m_mmu.getU8(m_registers.hl)); }
	void CPU::SRL_R8(Register8& p_r) { setFlags(0, 0, 0, p_r & 0x01); p_r = p_r >> 1; setFlagZ(!p_r);}
	void CPU::SRL_HL() { setFlags(0, 0, 0, m_mmu.getU8(m_registers.hl) & 0x01); m_mmu.setU8(m_registers.hl, m_mmu.getU8(m_registers.hl) >> 1); setFlagZ(!m_mmu.getU8(m_registers.hl));}
	void CPU::SWAP_R8(Register8& p_r) { p_r = (p_r << 4) | (p_r >> 4); setFlags(!p_r, false, false, false); }
	void CPU::SWAP_HL() { m_mmu.setU8(m_registers.hl, (m_mmu.getU8(m_registers.hl) << 4) | (m_mmu.getU8(m_registers.hl) >> 4)); setFlags(!m_mmu.getU8(m_registers.hl), false, false, false); }

	// Jumps and Subroutines
	void CPU::CALL_N16(u16 p_n) { m_registers.stackPointer -= 2; m_mmu.setU16(m_registers.stackPointer, ((p_n & 0xFF) << 8) | (p_n >> 8)); JP_N16(p_n); }
	void CPU::CALL_CC_N16(ConditionCode cc, u16 n) { if (ccStatus(cc)) CALL_N16(n); }
	void CPU::JP_HL() { m_registers.programCounter = m_registers.hl; }
	void CPU::JP_N16(s16 p_n) { m_registers.programCounter = p_n; }
	void CPU::JP_CC_N16(ConditionCode cc, s16 n) { if (ccStatus(cc)) m_registers.programCounter = n; }
	void CPU::JR_N8(s8 p_n) { m_registers.programCounter += p_n; }
	void CPU::JR_CC_N8(ConditionCode cc, s8 n) { if (ccStatus(cc)) m_registers.programCounter += n; }
	void CPU::RET() { POP_R16(m_registers.programCounter); }
	void CPU::RET_CC(ConditionCode p_cc) { if (ccStatus(p_cc)) POP_R16(m_registers.programCounter); }
	void CPU::RETI() { EI(); RET(); }
	void CPU::RST_VEC(RSTVec p_vec) { CALL_N16(convertRSTVec(p_vec)); }

	// Carry Flag
	void CPU::CCF() { setFlagN(false); setFlagH(false); setFlagC(!getFlagC()); }
	void CPU::SCF() { setFlagN(false); setFlagH(false); setFlagC(true); }

	// Stack Manipulation
	void CPU::ADD_HL_SP() { setFlagsForU16Overflow(m_registers.stackPointer, m_registers.hl); m_registers.hl += m_registers.stackPointer; }
	void CPU::ADD_SP_S8(s8 p_s) { setFlagZ(false); setFlagN(false); setFlagH(willHalfCarry(m_registers.stackPointer, (u16)signedToPositiveUnsigned(p_s), p_s >= 0)); setFlagC(willCarry(m_registers.stackPointer, (u16)signedToPositiveUnsigned(p_s), p_s >= 0)); m_registers.stackPointer += p_s;  }
	void CPU::DEC_SP() { m_registers.stackPointer--; }
	void CPU::INC_SP() { m_registers.stackPointer++; }
	void CPU::LD_SP_N16(u16 p_n) { m_mmu.setU16(m_registers.stackPointer, p_n); }
	void CPU::LD_N16_SP(u16 p_n) { m_mmu.setU16(p_n, ((m_registers.stackPointer & 0xFF) << 8) | (m_registers.stackPointer >> 8)); }
	void CPU::LD_HL_SP_S8(s8 p_s) { setFlagZ(false); setFlagN(false); setFlagH(willHalfCarry(m_registers.stackPointer, (u16)signedToPositiveUnsigned(p_s), p_s >= 0)); setFlagC(willCarry(m_registers.stackPointer, (u16)signedToPositiveUnsigned(p_s), p_s >= 0)); m_registers.stackPointer += p_s; m_registers.hl = m_registers.stackPointer; }
	void CPU::LD_SP_HL() { m_registers.stackPointer = m_registers.hl; }
	void CPU::POP_AF() { m_registers.af = m_mmu.getU16(m_registers.stackPointer); m_registers.stackPointer += 2; }
	void CPU::POP_R16(Register16& p_r) { p_r = m_mmu.getU16(m_registers.stackPointer); m_registers.stackPointer += 2; }
	void CPU::PUSH_AF() { m_registers.stackPointer -= 2; m_mmu.setU16(m_registers.stackPointer, ((m_registers.af & 0xFF) << 8) | (m_registers.af >> 8)); }
	void CPU::PUSH_R16(Register16& p_r) { m_registers.stackPointer -= 2; m_mmu.setU16(m_registers.stackPointer, ((p_r & 0xFF) << 8) | (p_r >> 8)); }

	// Interrupt Related
	void CPU::DI() { /* TODO: https://rgbds.gbdev.io/docs/v0.9.4/gbz80.7#DI */ }
	void CPU::EI() { /* TODO: https://rgbds.gbdev.io/docs/v0.9.4/gbz80.7#EI */ }
	void CPU::HALT() { /* TODO: https://rgbds.gbdev.io/docs/v0.9.4/gbz80.7#HALT */ }

	// Miscellaneous
	void CPU::DAA() { u8 adjustment = 0; if (getFlagN()) { if (getFlagH()) { adjustment += 0x06; } if (getFlagC()) { adjustment += 0x60; } m_registers.a -= adjustment; } else { if (getFlagH() || ((m_registers.a & 0xF) > 0x9)) { adjustment += 0x6; } if (getFlagC() || m_registers.a > 0x99) { adjustment += 0x60; setFlagC(true); } m_registers.a += adjustment; }; setFlagC(m_registers.a == 0); setFlagH(0); }
	void CPU::NOP() { ; } // Do nothing
	void CPU::STOP() { /* TODO: https://rgbds.gbdev.io/docs/v0.9.4/gbz80.7#STOP */ }

	// Operator Codes
	void CPU::op_00() { /* does nothing */ }
	void CPU::op_01() { LD_R16_N16(m_registers.bc, getBytePair()); }
	void CPU::op_02() { LD_R16_A(m_registers.bc); }
	void CPU::op_03() { INC_R16(m_registers.bc); }
	void CPU::op_04() { INC_R8(m_registers.b); }
	void CPU::op_05() { DEC_R8(m_registers.b); }
	void CPU::op_06() { LD_R8_N8(m_registers.b, getByte()); }
	void CPU::op_07() { RL_C_A(); }
	void CPU::op_08() { LD_N16_SP(getBytePair()); }
	void CPU::op_09() { ADD_HL_R16(m_registers.bc); }
	void CPU::op_0A() { LD_A_R16(m_registers.bc); }
	void CPU::op_0B() { DEC_R16(m_registers.bc); }
	void CPU::op_0C() { INC_R8(m_registers.c); }
	void CPU::op_0D() { DEC_R8(m_registers.c); }
	void CPU::op_0E() { LD_R8_N8(m_registers.c, getByte()); }
	void CPU::op_0F() { RR_C_A(); }

	void CPU::op_10() { STOP(); }
	void CPU::op_11() { LD_R16_N16(m_registers.de, getBytePair());; }
	void CPU::op_12() { LD_R16_A(m_registers.de); }
	void CPU::op_13() { INC_R16(m_registers.de); }
	void CPU::op_14() { INC_R8(m_registers.d); }
	void CPU::op_15() { DEC_R8(m_registers.d); }
	void CPU::op_16() { LD_R8_N8(m_registers.d, getByte()); }
	void CPU::op_17() { RL_A(); }
	void CPU::op_18() { JR_N8(getByte()); } 
	void CPU::op_19() { ADD_HL_R16(m_registers.de); }
	void CPU::op_1A() { LD_A_R16(m_registers.de); }
	void CPU::op_1B() { DEC_R16(m_registers.de); }
	void CPU::op_1C() { INC_R8(m_registers.e); }
	void CPU::op_1D() { DEC_R8(m_registers.e); }
	void CPU::op_1E() { LD_R8_N8(m_registers.e, getByte()); }
	void CPU::op_1F() { RR_A(); }

	void CPU::op_20() { JR_CC_N8(NZ, getByte()); }
	void CPU::op_21() { LD_R16_N16(m_registers.hl, getBytePair());; }
	void CPU::op_22() { LD_HLI_A(); }
	void CPU::op_23() { INC_R16(m_registers.hl); }
	void CPU::op_24() { INC_R8(m_registers.h); }
	void CPU::op_25() { DEC_R8(m_registers.h); }
	void CPU::op_26() { LD_R8_N8(m_registers.h, getByte()); }
	void CPU::op_27() { DAA(); }
	void CPU::op_28() { JR_CC_N8(Z, getByte()); }
	void CPU::op_29() { ADD_HL_R16(m_registers.hl); }
	void CPU::op_2A() { LD_A_HLI(); }
	void CPU::op_2B() { DEC_R16(m_registers.hl);; }
	void CPU::op_2C() { INC_R8(m_registers.l); }
	void CPU::op_2D() { DEC_R8(m_registers.l); }
	void CPU::op_2E() { LD_R8_N8(m_registers.l, getByte()); }
	void CPU::op_2F() { CPL(); }

	void CPU::op_30() { JR_CC_N8(NC, getByte()); }
	void CPU::op_31() { LD_R16_N16(m_registers.stackPointer, getBytePair());; }
	void CPU::op_32() { LD_HLD_A(); }
	void CPU::op_33() { INC_R16(m_registers.stackPointer); }
	void CPU::op_34() { INC_HL(); }
	void CPU::op_35() { DEC_HL(); }
	void CPU::op_36() { LD_HL_N8(getByte()); }
	void CPU::op_37() { SCF(); }
	void CPU::op_38() { JR_CC_N8(C, getByte()); }
	void CPU::op_39() { ADD_HL_R16(m_registers.stackPointer); }
	void CPU::op_3A() { LD_A_HLD(); }
	void CPU::op_3B() { DEC_R16(m_registers.stackPointer);; }
	void CPU::op_3C() { INC_R8(m_registers.a); }
	void CPU::op_3D() { DEC_R8(m_registers.a); }
	void CPU::op_3E() { LD_R8_N8(m_registers.a, getByte()); }
	void CPU::op_3F() { CCF(); }

	void CPU::op_40() { LD_R8_R8(m_registers.b, m_registers.b); }
	void CPU::op_41() { LD_R8_R8(m_registers.b, m_registers.c); }
	void CPU::op_42() { LD_R8_R8(m_registers.b, m_registers.d); }
	void CPU::op_43() { LD_R8_R8(m_registers.b, m_registers.e); }
	void CPU::op_44() { LD_R8_R8(m_registers.b, m_registers.h); }
	void CPU::op_45() { LD_R8_R8(m_registers.b, m_registers.l); }
	void CPU::op_46() { LD_R8_HL(m_registers.b); }
	void CPU::op_47() { LD_R8_R8(m_registers.b, m_registers.a); }
	void CPU::op_48() { LD_R8_R8(m_registers.c, m_registers.b); }
	void CPU::op_49() { LD_R8_R8(m_registers.c, m_registers.c); }
	void CPU::op_4A() { LD_R8_R8(m_registers.c, m_registers.d); }
	void CPU::op_4B() { LD_R8_R8(m_registers.c, m_registers.e); }
	void CPU::op_4C() { LD_R8_R8(m_registers.c, m_registers.h); }
	void CPU::op_4D() { LD_R8_R8(m_registers.c, m_registers.l); }
	void CPU::op_4E() { LD_R8_HL(m_registers.c); }
	void CPU::op_4F() { LD_R8_R8(m_registers.c, m_registers.a); }

	void CPU::op_50() { LD_R8_R8(m_registers.d, m_registers.b); }
	void CPU::op_51() { LD_R8_R8(m_registers.d, m_registers.c); }
	void CPU::op_52() { LD_R8_R8(m_registers.d, m_registers.d); }
	void CPU::op_53() { LD_R8_R8(m_registers.d, m_registers.e); }
	void CPU::op_54() { LD_R8_R8(m_registers.d, m_registers.h); }
	void CPU::op_55() { LD_R8_R8(m_registers.d, m_registers.l); }
	void CPU::op_56() { LD_R8_HL(m_registers.d); }
	void CPU::op_57() { LD_R8_R8(m_registers.d, m_registers.a); }
	void CPU::op_58() { LD_R8_R8(m_registers.e, m_registers.b); }
	void CPU::op_59() { LD_R8_R8(m_registers.e, m_registers.c); }
	void CPU::op_5A() { LD_R8_R8(m_registers.e, m_registers.d); }
	void CPU::op_5B() { LD_R8_R8(m_registers.e, m_registers.e); }
	void CPU::op_5C() { LD_R8_R8(m_registers.e, m_registers.h); }
	void CPU::op_5D() { LD_R8_R8(m_registers.e, m_registers.l); }
	void CPU::op_5E() { LD_R8_HL(m_registers.e); }
	void CPU::op_5F() { LD_R8_R8(m_registers.e, m_registers.a); }

	void CPU::op_60() { LD_R8_R8(m_registers.h, m_registers.b); }
	void CPU::op_61() { LD_R8_R8(m_registers.h, m_registers.c); }
	void CPU::op_62() { LD_R8_R8(m_registers.h, m_registers.d); }
	void CPU::op_63() { LD_R8_R8(m_registers.h, m_registers.e); }
	void CPU::op_64() { LD_R8_R8(m_registers.h, m_registers.h); }
	void CPU::op_65() { LD_R8_R8(m_registers.h, m_registers.l); }
	void CPU::op_66() { LD_R8_HL(m_registers.h); }
	void CPU::op_67() { LD_R8_R8(m_registers.h, m_registers.a); }
	void CPU::op_68() { LD_R8_R8(m_registers.l, m_registers.b); }
	void CPU::op_69() { LD_R8_R8(m_registers.l, m_registers.c); }
	void CPU::op_6A() { LD_R8_R8(m_registers.l, m_registers.d); }
	void CPU::op_6B() { LD_R8_R8(m_registers.l, m_registers.e); }
	void CPU::op_6C() { LD_R8_R8(m_registers.l, m_registers.h); }
	void CPU::op_6D() { LD_R8_R8(m_registers.l, m_registers.l); }
	void CPU::op_6E() { LD_R8_HL(m_registers.l); }
	void CPU::op_6F() { LD_R8_R8(m_registers.l, m_registers.a); }

	void CPU::op_70() { LD_HL_R8(m_registers.b); }
	void CPU::op_71() { LD_HL_R8(m_registers.c); }
	void CPU::op_72() { LD_HL_R8(m_registers.d); }
	void CPU::op_73() { LD_HL_R8(m_registers.e); }
	void CPU::op_74() { LD_HL_R8(m_registers.h); }
	void CPU::op_75() { LD_HL_R8(m_registers.l); }
	void CPU::op_76() { HALT(); }
	void CPU::op_77() { LD_HL_R8(m_registers.a); }
	void CPU::op_78() { LD_R8_R8(m_registers.a, m_registers.b); }
	void CPU::op_79() { LD_R8_R8(m_registers.a, m_registers.c); }
	void CPU::op_7A() { LD_R8_R8(m_registers.a, m_registers.d); }
	void CPU::op_7B() { LD_R8_R8(m_registers.a, m_registers.e); }
	void CPU::op_7C() { LD_R8_R8(m_registers.a, m_registers.h); }
	void CPU::op_7D() { LD_R8_R8(m_registers.a, m_registers.l); }
	void CPU::op_7E() { LD_R8_HL(m_registers.a); }
	void CPU::op_7F() { LD_R8_R8(m_registers.a, m_registers.a); }

	void CPU::op_80() { ADD_A_R8(m_registers.b); }
	void CPU::op_81() { ADD_A_R8(m_registers.c); }
	void CPU::op_82() { ADD_A_R8(m_registers.d); }
	void CPU::op_83() { ADD_A_R8(m_registers.e); }
	void CPU::op_84() { ADD_A_R8(m_registers.h); }
	void CPU::op_85() { ADD_A_R8(m_registers.l); }
	void CPU::op_86() { ADD_A_HL(); }
	void CPU::op_87() { ADD_A_R8(m_registers.a); }
	void CPU::op_88() { ADC_A_R8(m_registers.b); }
	void CPU::op_89() { ADC_A_R8(m_registers.c); }
	void CPU::op_8A() { ADC_A_R8(m_registers.d); }
	void CPU::op_8B() { ADC_A_R8(m_registers.e); }
	void CPU::op_8C() { ADC_A_R8(m_registers.h); }
	void CPU::op_8D() { ADC_A_R8(m_registers.l); }
	void CPU::op_8E() { ADC_A_HL(); }
	void CPU::op_8F() { ADC_A_R8(m_registers.a); }

	void CPU::op_90() { SUB_A_R8(m_registers.b); }
	void CPU::op_91() { SUB_A_R8(m_registers.c); }
	void CPU::op_92() { SUB_A_R8(m_registers.d); }
	void CPU::op_93() { SUB_A_R8(m_registers.e); }
	void CPU::op_94() { SUB_A_R8(m_registers.h); }
	void CPU::op_95() { SUB_A_R8(m_registers.l); }
	void CPU::op_96() { SUB_A_HL(); }
	void CPU::op_97() { SUB_A_R8(m_registers.a); }
	void CPU::op_98() { SBC_A_R8(m_registers.b); }
	void CPU::op_99() { SBC_A_R8(m_registers.c); }
	void CPU::op_9A() { SBC_A_R8(m_registers.d); }
	void CPU::op_9B() { SBC_A_R8(m_registers.e); }
	void CPU::op_9C() { SBC_A_R8(m_registers.h); }
	void CPU::op_9D() { SBC_A_R8(m_registers.l); }
	void CPU::op_9E() { SBC_A_HL(); }
	void CPU::op_9F() { SBC_A_R8(m_registers.a); }

	void CPU::op_A0() { AND_A_R8(m_registers.b); }
	void CPU::op_A1() { AND_A_R8(m_registers.c); }
	void CPU::op_A2() { AND_A_R8(m_registers.d); }
	void CPU::op_A3() { AND_A_R8(m_registers.e); }
	void CPU::op_A4() { AND_A_R8(m_registers.h); }
	void CPU::op_A5() { AND_A_R8(m_registers.l); }
	void CPU::op_A6() { AND_A_HL(); }
	void CPU::op_A7() { AND_A_R8(m_registers.a); }
	void CPU::op_A8() { XOR_A_R8(m_registers.b); }
	void CPU::op_A9() { XOR_A_R8(m_registers.c); }
	void CPU::op_AA() { XOR_A_R8(m_registers.d); }
	void CPU::op_AB() { XOR_A_R8(m_registers.e); }
	void CPU::op_AC() { XOR_A_R8(m_registers.h); }
	void CPU::op_AD() { XOR_A_R8(m_registers.l); }
	void CPU::op_AE() { XOR_A_HL(); }
	void CPU::op_AF() { XOR_A_R8(m_registers.a); }

	void CPU::op_B0() { OR_A_R8(m_registers.b); }
	void CPU::op_B1() { OR_A_R8(m_registers.c); }
	void CPU::op_B2() { OR_A_R8(m_registers.d); }
	void CPU::op_B3() { OR_A_R8(m_registers.e); }
	void CPU::op_B4() { OR_A_R8(m_registers.h); }
	void CPU::op_B5() { OR_A_R8(m_registers.l); }
	void CPU::op_B6() { OR_A_HL(); }
	void CPU::op_B7() { OR_A_R8(m_registers.a); }
	void CPU::op_B8() { CP_A_R8(m_registers.b); }
	void CPU::op_B9() { CP_A_R8(m_registers.c); }
	void CPU::op_BA() { CP_A_R8(m_registers.d); }
	void CPU::op_BB() { CP_A_R8(m_registers.e); }
	void CPU::op_BC() { CP_A_R8(m_registers.h); }
	void CPU::op_BD() { CP_A_R8(m_registers.l); }
	void CPU::op_BE() { CP_A_HL(); }
	void CPU::op_BF() { CP_A_R8(m_registers.a); }

	void CPU::op_C0() { RET_CC(NZ); }
	void CPU::op_C1() { POP_R16(m_registers.bc); }
	void CPU::op_C2() { JP_CC_N16(NZ, getBytePair()); }
	void CPU::op_C3() { JP_N16(getBytePair()); }
	void CPU::op_C4() { CALL_CC_N16(NZ, getBytePair()); }
	void CPU::op_C5() { PUSH_R16(m_registers.bc); }
	void CPU::op_C6() { ADD_A_N8(getByte()); }
	void CPU::op_C7() { RST_VEC(x00); }
	void CPU::op_C8() { RET_CC(Z); }
	void CPU::op_C9() { RET(); }
	void CPU::op_CA() { JP_CC_N16(Z, getBytePair()); }
	void CPU::op_CB() { executeCBInstruction(); } // Switch to CB opcodes
	void CPU::op_CC() { CALL_CC_N16(Z, getBytePair()); }
	void CPU::op_CD() { CALL_N16(getBytePair()); }
	void CPU::op_CE() { ADC_A_N8(getByte()); }
	void CPU::op_CF() { RST_VEC(x08); }

	void CPU::op_D0() { RET_CC(NC); }
	void CPU::op_D1() { POP_R16(m_registers.de); }
	void CPU::op_D2() { JP_CC_N16(NC, getBytePair()); }
	void CPU::op_D3() { throw; }
	void CPU::op_D4() { CALL_CC_N16(NC, getBytePair()); }
	void CPU::op_D5() { PUSH_R16(m_registers.de); }
	void CPU::op_D6() { SUB_A_N8(getByte()); }
	void CPU::op_D7() { RST_VEC(x10); }
	void CPU::op_D8() { RET_CC(C); }
	void CPU::op_D9() { RETI(); }
	void CPU::op_DA() { JP_CC_N16(C, getBytePair()); }
	void CPU::op_DB() { throw; }
	void CPU::op_DC() { CALL_CC_N16(C, getBytePair()); }
	void CPU::op_DD() { throw; }
	void CPU::op_DE() { SBC_A_N8(getByte()); }
	void CPU::op_DF() { RST_VEC(x18); }

	void CPU::op_E0() { LDH_N16_A(getByte()); }
	void CPU::op_E1() { POP_R16(m_registers.hl); }
	void CPU::op_E2() { LDH_C_A(); }
	void CPU::op_E3() { throw; }
	void CPU::op_E4() { throw; }
	void CPU::op_E5() { PUSH_R16(m_registers.hl); }
	void CPU::op_E6() { AND_A_N8(getByte()); }
	void CPU::op_E7() { RST_VEC(x20); }
	void CPU::op_E8() { ADD_SP_S8(getByte()); }
	void CPU::op_E9() { JP_HL(); }
	void CPU::op_EA() { LD_N16_A(getBytePair()); }
	void CPU::op_EB() { throw; }
	void CPU::op_EC() { throw; }
	void CPU::op_ED() { throw; }
	void CPU::op_EE() { XOR_A_N8(getByte()); }
	void CPU::op_EF() { RST_VEC(x28); }

	void CPU::op_F0() { LDH_A_N16(getByte()); }
	void CPU::op_F1() { POP_R16(m_registers.af); }
	void CPU::op_F2() { LDH_A_C(); }
	void CPU::op_F3() { DI(); }
	void CPU::op_F4() { throw; }
	void CPU::op_F5() { PUSH_R16(m_registers.af); }
	void CPU::op_F6() { OR_A_N8(getByte()); }
	void CPU::op_F7() { RST_VEC(x30); }
	void CPU::op_F8() { LD_HL_SP_S8(getByte()); }
	void CPU::op_F9() { LD_SP_HL(); }
	void CPU::op_FA() { LD_A_N16(getBytePair()); }
	void CPU::op_FB() { EI(); }
	void CPU::op_FC() { throw; }
	void CPU::op_FD() { throw; }
	void CPU::op_FE() { CP_A_N8(getByte()); }
	void CPU::op_FF() { RST_VEC(x38); }

	void CPU::op_cb_00() { RL_C_R8(m_registers.b); }
	void CPU::op_cb_01() { RL_C_R8(m_registers.c); }
	void CPU::op_cb_02() { RL_C_R8(m_registers.d); }
	void CPU::op_cb_03() { RL_C_R8(m_registers.e); }
	void CPU::op_cb_04() { RL_C_R8(m_registers.h); }
	void CPU::op_cb_05() { RL_C_R8(m_registers.l); }
	void CPU::op_cb_06() { RL_C_HL(); }
	void CPU::op_cb_07() { RL_C_R8(m_registers.a); }
	void CPU::op_cb_08() { RR_C_R8(m_registers.b); }
	void CPU::op_cb_09() { RR_C_R8(m_registers.c); }
	void CPU::op_cb_0A() { RR_C_R8(m_registers.d); }
	void CPU::op_cb_0B() { RR_C_R8(m_registers.e); }
	void CPU::op_cb_0C() { RR_C_R8(m_registers.h); }
	void CPU::op_cb_0D() { RR_C_R8(m_registers.l); }
	void CPU::op_cb_0E() { RR_C_HL(); }
	void CPU::op_cb_0F() { RR_C_R8(m_registers.a); }

	void CPU::op_cb_10() { RL_R8(m_registers.b); }
	void CPU::op_cb_11() { RL_R8(m_registers.c); }
	void CPU::op_cb_12() { RL_R8(m_registers.d); }
	void CPU::op_cb_13() { RL_R8(m_registers.e); }
	void CPU::op_cb_14() { RL_R8(m_registers.h); }
	void CPU::op_cb_15() { RL_R8(m_registers.l); }
	void CPU::op_cb_16() { RL_HL(); }
	void CPU::op_cb_17() { RL_R8(m_registers.a); }
	void CPU::op_cb_18() { RR_R8(m_registers.b); }
	void CPU::op_cb_19() { RR_R8(m_registers.c); }
	void CPU::op_cb_1A() { RR_R8(m_registers.d); }
	void CPU::op_cb_1B() { RR_R8(m_registers.e); }
	void CPU::op_cb_1C() { RR_R8(m_registers.h); }
	void CPU::op_cb_1D() { RR_R8(m_registers.l); }
	void CPU::op_cb_1E() { RR_HL(); }
	void CPU::op_cb_1F() { RR_R8(m_registers.a); }

	void CPU::op_cb_20() { SLA_R8(m_registers.b); }
	void CPU::op_cb_21() { SLA_R8(m_registers.c); }
	void CPU::op_cb_22() { SLA_R8(m_registers.d); }
	void CPU::op_cb_23() { SLA_R8(m_registers.e); }
	void CPU::op_cb_24() { SLA_R8(m_registers.h); }
	void CPU::op_cb_25() { SLA_R8(m_registers.l); }
	void CPU::op_cb_26() { SLA_HL(); }
	void CPU::op_cb_27() { SLA_R8(m_registers.a); }
	void CPU::op_cb_28() { SRA_R8(m_registers.b); }
	void CPU::op_cb_29() { SRA_R8(m_registers.c); }
	void CPU::op_cb_2A() { SRA_R8(m_registers.d); }
	void CPU::op_cb_2B() { SRA_R8(m_registers.e); }
	void CPU::op_cb_2C() { SRA_R8(m_registers.h); }
	void CPU::op_cb_2D() { SRA_R8(m_registers.l); }
	void CPU::op_cb_2E() { SRA_HL(); }
	void CPU::op_cb_2F() { SRA_R8(m_registers.a); }

	void CPU::op_cb_30() { SWAP_R8(m_registers.b); }
	void CPU::op_cb_31() { SWAP_R8(m_registers.c); }
	void CPU::op_cb_32() { SWAP_R8(m_registers.d); }
	void CPU::op_cb_33() { SWAP_R8(m_registers.e); }
	void CPU::op_cb_34() { SWAP_R8(m_registers.h); }
	void CPU::op_cb_35() { SWAP_R8(m_registers.l); }
	void CPU::op_cb_36() { SWAP_HL(); }
	void CPU::op_cb_37() { SWAP_R8(m_registers.a); }
	void CPU::op_cb_38() { SRL_R8(m_registers.b); }
	void CPU::op_cb_39() { SRL_R8(m_registers.c); }
	void CPU::op_cb_3A() { SRL_R8(m_registers.d); }
	void CPU::op_cb_3B() { SRL_R8(m_registers.e); }
	void CPU::op_cb_3C() { SRL_R8(m_registers.h); }
	void CPU::op_cb_3D() { SRL_R8(m_registers.l); }
	void CPU::op_cb_3E() { SRL_HL(); }
	void CPU::op_cb_3F() { SRL_R8(m_registers.a); }
	
	void CPU::op_cb_40() { BIT_U3_R8({0}, m_registers.b); }
	void CPU::op_cb_41() { BIT_U3_R8({0}, m_registers.c); }
	void CPU::op_cb_42() { BIT_U3_R8({0}, m_registers.d); }
	void CPU::op_cb_43() { BIT_U3_R8({0}, m_registers.e); }
	void CPU::op_cb_44() { BIT_U3_R8({0}, m_registers.h); }
	void CPU::op_cb_45() { BIT_U3_R8({0}, m_registers.l); }
	void CPU::op_cb_46() { BIT_U3_HL({0}); }
	void CPU::op_cb_47() { BIT_U3_R8({0}, m_registers.a); }
	void CPU::op_cb_48() { BIT_U3_R8({1}, m_registers.b); }
	void CPU::op_cb_49() { BIT_U3_R8({1}, m_registers.c); }
	void CPU::op_cb_4A() { BIT_U3_R8({1}, m_registers.d); }
	void CPU::op_cb_4B() { BIT_U3_R8({1}, m_registers.e); }
	void CPU::op_cb_4C() { BIT_U3_R8({1}, m_registers.h); }
	void CPU::op_cb_4D() { BIT_U3_R8({1}, m_registers.l); }
	void CPU::op_cb_4E() { BIT_U3_HL({1}); }
	void CPU::op_cb_4F() { BIT_U3_R8({1}, m_registers.a); }

	void CPU::op_cb_50() { BIT_U3_R8({2}, m_registers.b); }
	void CPU::op_cb_51() { BIT_U3_R8({2}, m_registers.c); }
	void CPU::op_cb_52() { BIT_U3_R8({2}, m_registers.d); }
	void CPU::op_cb_53() { BIT_U3_R8({2}, m_registers.e); }
	void CPU::op_cb_54() { BIT_U3_R8({2}, m_registers.h); }
	void CPU::op_cb_55() { BIT_U3_R8({2}, m_registers.l); }
	void CPU::op_cb_56() { BIT_U3_HL({2}); }
	void CPU::op_cb_57() { BIT_U3_R8({2}, m_registers.a); }
	void CPU::op_cb_58() { BIT_U3_R8({3}, m_registers.b); }
	void CPU::op_cb_59() { BIT_U3_R8({3}, m_registers.c); }
	void CPU::op_cb_5A() { BIT_U3_R8({3}, m_registers.d); }
	void CPU::op_cb_5B() { BIT_U3_R8({3}, m_registers.e); }
	void CPU::op_cb_5C() { BIT_U3_R8({3}, m_registers.h); }
	void CPU::op_cb_5D() { BIT_U3_R8({3}, m_registers.l); }
	void CPU::op_cb_5E() { BIT_U3_HL({3}); }
	void CPU::op_cb_5F() { BIT_U3_R8({3}, m_registers.a); }

	void CPU::op_cb_60() { BIT_U3_R8({4}, m_registers.b); }
	void CPU::op_cb_61() { BIT_U3_R8({4}, m_registers.c); }
	void CPU::op_cb_62() { BIT_U3_R8({4}, m_registers.d); }
	void CPU::op_cb_63() { BIT_U3_R8({4}, m_registers.e); }
	void CPU::op_cb_64() { BIT_U3_R8({4}, m_registers.h); }
	void CPU::op_cb_65() { BIT_U3_R8({4}, m_registers.l); }
	void CPU::op_cb_66() { BIT_U3_HL({4}); }
	void CPU::op_cb_67() { BIT_U3_R8({4}, m_registers.a); }
	void CPU::op_cb_68() { BIT_U3_R8({5}, m_registers.b); }
	void CPU::op_cb_69() { BIT_U3_R8({5}, m_registers.c); }
	void CPU::op_cb_6A() { BIT_U3_R8({5}, m_registers.d); }
	void CPU::op_cb_6B() { BIT_U3_R8({5}, m_registers.e); }
	void CPU::op_cb_6C() { BIT_U3_R8({5}, m_registers.h); }
	void CPU::op_cb_6D() { BIT_U3_R8({5}, m_registers.l); }
	void CPU::op_cb_6E() { BIT_U3_HL({5}); }
	void CPU::op_cb_6F() { BIT_U3_R8({5}, m_registers.a); }

	void CPU::op_cb_70() { BIT_U3_R8({6}, m_registers.b); }
	void CPU::op_cb_71() { BIT_U3_R8({6}, m_registers.c); }
	void CPU::op_cb_72() { BIT_U3_R8({6}, m_registers.d); }
	void CPU::op_cb_73() { BIT_U3_R8({6}, m_registers.e); }
	void CPU::op_cb_74() { BIT_U3_R8({6}, m_registers.h); }
	void CPU::op_cb_75() { BIT_U3_R8({6}, m_registers.l); }
	void CPU::op_cb_76() { BIT_U3_HL({6}); }
	void CPU::op_cb_77() { BIT_U3_R8({6}, m_registers.a); }
	void CPU::op_cb_78() { BIT_U3_R8({7}, m_registers.b); }
	void CPU::op_cb_79() { BIT_U3_R8({7}, m_registers.c); }
	void CPU::op_cb_7A() { BIT_U3_R8({7}, m_registers.d); }
	void CPU::op_cb_7B() { BIT_U3_R8({7}, m_registers.e); }
	void CPU::op_cb_7C() { BIT_U3_R8({7}, m_registers.h); }
	void CPU::op_cb_7D() { BIT_U3_R8({7}, m_registers.l); }
	void CPU::op_cb_7E() { BIT_U3_HL({7}); }
	void CPU::op_cb_7F() { BIT_U3_R8({7}, m_registers.a); }

	void CPU::op_cb_80() { RES_U3_R8({0}, m_registers.b); }
	void CPU::op_cb_81() { RES_U3_R8({0}, m_registers.c); }
	void CPU::op_cb_82() { RES_U3_R8({0}, m_registers.d); }
	void CPU::op_cb_83() { RES_U3_R8({0}, m_registers.e); }
	void CPU::op_cb_84() { RES_U3_R8({0}, m_registers.h); }
	void CPU::op_cb_85() { RES_U3_R8({0}, m_registers.l); }
	void CPU::op_cb_86() { RES_U3_HL({0}); }
	void CPU::op_cb_87() { RES_U3_R8({0}, m_registers.a); }
	void CPU::op_cb_88() { RES_U3_R8({1}, m_registers.b); }
	void CPU::op_cb_89() { RES_U3_R8({1}, m_registers.c); }
	void CPU::op_cb_8A() { RES_U3_R8({1}, m_registers.d); }
	void CPU::op_cb_8B() { RES_U3_R8({1}, m_registers.e); }
	void CPU::op_cb_8C() { RES_U3_R8({1}, m_registers.h); }
	void CPU::op_cb_8D() { RES_U3_R8({1}, m_registers.l); }
	void CPU::op_cb_8E() { RES_U3_HL({1}); }
	void CPU::op_cb_8F() { RES_U3_R8({1}, m_registers.a); }

	void CPU::op_cb_90() { RES_U3_R8({2}, m_registers.b); }
	void CPU::op_cb_91() { RES_U3_R8({2}, m_registers.c); }
	void CPU::op_cb_92() { RES_U3_R8({2}, m_registers.d); }
	void CPU::op_cb_93() { RES_U3_R8({2}, m_registers.e); }
	void CPU::op_cb_94() { RES_U3_R8({2}, m_registers.h); }
	void CPU::op_cb_95() { RES_U3_R8({2}, m_registers.l); }
	void CPU::op_cb_96() { RES_U3_HL({2}); }
	void CPU::op_cb_97() { RES_U3_R8({2}, m_registers.a); }
	void CPU::op_cb_98() { RES_U3_R8({3}, m_registers.b); }
	void CPU::op_cb_99() { RES_U3_R8({3}, m_registers.c); }
	void CPU::op_cb_9A() { RES_U3_R8({3}, m_registers.d); }
	void CPU::op_cb_9B() { RES_U3_R8({3}, m_registers.e); }
	void CPU::op_cb_9C() { RES_U3_R8({3}, m_registers.h); }
	void CPU::op_cb_9D() { RES_U3_R8({3}, m_registers.l); }
	void CPU::op_cb_9E() { RES_U3_HL({3}); }
	void CPU::op_cb_9F() { RES_U3_R8({3}, m_registers.a); }

	void CPU::op_cb_A0() { RES_U3_R8({4}, m_registers.b); }
	void CPU::op_cb_A1() { RES_U3_R8({4}, m_registers.c); }
	void CPU::op_cb_A2() { RES_U3_R8({4}, m_registers.d); }
	void CPU::op_cb_A3() { RES_U3_R8({4}, m_registers.e); }
	void CPU::op_cb_A4() { RES_U3_R8({4}, m_registers.h); }
	void CPU::op_cb_A5() { RES_U3_R8({4}, m_registers.l); }
	void CPU::op_cb_A6() { RES_U3_HL({4}); }
	void CPU::op_cb_A7() { RES_U3_R8({4}, m_registers.a); }
	void CPU::op_cb_A8() { RES_U3_R8({5}, m_registers.b); }
	void CPU::op_cb_A9() { RES_U3_R8({5}, m_registers.c); }
	void CPU::op_cb_AA() { RES_U3_R8({5}, m_registers.d); }
	void CPU::op_cb_AB() { RES_U3_R8({5}, m_registers.e); }
	void CPU::op_cb_AC() { RES_U3_R8({5}, m_registers.h); }
	void CPU::op_cb_AD() { RES_U3_R8({5}, m_registers.l); }
	void CPU::op_cb_AE() { RES_U3_HL({5}); }
	void CPU::op_cb_AF() { RES_U3_R8({5}, m_registers.a); }

	void CPU::op_cb_B0() { RES_U3_R8({6}, m_registers.b); }
	void CPU::op_cb_B1() { RES_U3_R8({6}, m_registers.c); }
	void CPU::op_cb_B2() { RES_U3_R8({6}, m_registers.d); }
	void CPU::op_cb_B3() { RES_U3_R8({6}, m_registers.e); }
	void CPU::op_cb_B4() { RES_U3_R8({6}, m_registers.h); }
	void CPU::op_cb_B5() { RES_U3_R8({6}, m_registers.l); }
	void CPU::op_cb_B6() { RES_U3_HL({6}); }
	void CPU::op_cb_B7() { RES_U3_R8({6}, m_registers.a); }
	void CPU::op_cb_B8() { RES_U3_R8({7}, m_registers.b); }
	void CPU::op_cb_B9() { RES_U3_R8({7}, m_registers.c); }
	void CPU::op_cb_BA() { RES_U3_R8({7}, m_registers.d); }
	void CPU::op_cb_BB() { RES_U3_R8({7}, m_registers.e); }
	void CPU::op_cb_BC() { RES_U3_R8({7}, m_registers.h); }
	void CPU::op_cb_BD() { RES_U3_R8({7}, m_registers.l); }
	void CPU::op_cb_BE() { RES_U3_HL({7}); }
	void CPU::op_cb_BF() { RES_U3_R8({7}, m_registers.a); }

	void CPU::op_cb_C0() { SET_U3_R8({0}, m_registers.b); }
	void CPU::op_cb_C1() { SET_U3_R8({0}, m_registers.c); }
	void CPU::op_cb_C2() { SET_U3_R8({0}, m_registers.d); }
	void CPU::op_cb_C3() { SET_U3_R8({0}, m_registers.e); }
	void CPU::op_cb_C4() { SET_U3_R8({0}, m_registers.h); }
	void CPU::op_cb_C5() { SET_U3_R8({0}, m_registers.l); }
	void CPU::op_cb_C6() { SET_U3_HL({0}); }
	void CPU::op_cb_C7() { SET_U3_R8({0}, m_registers.a); }
	void CPU::op_cb_C8() { SET_U3_R8({1}, m_registers.b); }
	void CPU::op_cb_C9() { SET_U3_R8({1}, m_registers.c); }
	void CPU::op_cb_CA() { SET_U3_R8({1}, m_registers.d); }
	void CPU::op_cb_CB() { SET_U3_R8({1}, m_registers.e); }
	void CPU::op_cb_CC() { SET_U3_R8({1}, m_registers.h); }
	void CPU::op_cb_CD() { SET_U3_R8({1}, m_registers.l); }
	void CPU::op_cb_CE() { SET_U3_HL({1}); }
	void CPU::op_cb_CF() { SET_U3_R8({1}, m_registers.a); }

	void CPU::op_cb_D0() { SET_U3_R8({2}, m_registers.b); }
	void CPU::op_cb_D1() { SET_U3_R8({2}, m_registers.c); }
	void CPU::op_cb_D2() { SET_U3_R8({2}, m_registers.d); }
	void CPU::op_cb_D3() { SET_U3_R8({2}, m_registers.e); }
	void CPU::op_cb_D4() { SET_U3_R8({2}, m_registers.h); }
	void CPU::op_cb_D5() { SET_U3_R8({2}, m_registers.l); }
	void CPU::op_cb_D6() { SET_U3_HL({2}); }
	void CPU::op_cb_D7() { SET_U3_R8({2}, m_registers.a); }
	void CPU::op_cb_D8() { SET_U3_R8({3}, m_registers.b); }
	void CPU::op_cb_D9() { SET_U3_R8({3}, m_registers.c); }
	void CPU::op_cb_DA() { SET_U3_R8({3}, m_registers.d); }
	void CPU::op_cb_DB() { SET_U3_R8({3}, m_registers.e); }
	void CPU::op_cb_DC() { SET_U3_R8({3}, m_registers.h); }
	void CPU::op_cb_DD() { SET_U3_R8({3}, m_registers.l); }
	void CPU::op_cb_DE() { SET_U3_HL({3}); }
	void CPU::op_cb_DF() { SET_U3_R8({3}, m_registers.a); }

	void CPU::op_cb_E0() { SET_U3_R8({4}, m_registers.b); }
	void CPU::op_cb_E1() { SET_U3_R8({4}, m_registers.c); }
	void CPU::op_cb_E2() { SET_U3_R8({4}, m_registers.d); }
	void CPU::op_cb_E3() { SET_U3_R8({4}, m_registers.e); }
	void CPU::op_cb_E4() { SET_U3_R8({4}, m_registers.h); }
	void CPU::op_cb_E5() { SET_U3_R8({4}, m_registers.l); }
	void CPU::op_cb_E6() { SET_U3_HL({4}); }
	void CPU::op_cb_E7() { SET_U3_R8({4}, m_registers.a); }
	void CPU::op_cb_E8() { SET_U3_R8({5}, m_registers.b); }
	void CPU::op_cb_E9() { SET_U3_R8({5}, m_registers.c); }
	void CPU::op_cb_EA() { SET_U3_R8({5}, m_registers.d); }
	void CPU::op_cb_EB() { SET_U3_R8({5}, m_registers.e); }
	void CPU::op_cb_EC() { SET_U3_R8({5}, m_registers.h); }
	void CPU::op_cb_ED() { SET_U3_R8({5}, m_registers.l); }
	void CPU::op_cb_EE() { SET_U3_HL({5}); }
	void CPU::op_cb_EF() { SET_U3_R8({5}, m_registers.a); }

	void CPU::op_cb_F0() { SET_U3_R8({6}, m_registers.b); }
	void CPU::op_cb_F1() { SET_U3_R8({6}, m_registers.c); }
	void CPU::op_cb_F2() { SET_U3_R8({6}, m_registers.d); }
	void CPU::op_cb_F3() { SET_U3_R8({6}, m_registers.e); }
	void CPU::op_cb_F4() { SET_U3_R8({6}, m_registers.h); }
	void CPU::op_cb_F5() { SET_U3_R8({6}, m_registers.l); }
	void CPU::op_cb_F6() { SET_U3_HL({6}); }
	void CPU::op_cb_F7() { SET_U3_R8({6}, m_registers.a); }
	void CPU::op_cb_F8() { SET_U3_R8({7}, m_registers.b); }
	void CPU::op_cb_F9() { SET_U3_R8({7}, m_registers.c); }
	void CPU::op_cb_FA() { SET_U3_R8({7}, m_registers.d); }
	void CPU::op_cb_FB() { SET_U3_R8({7}, m_registers.e); }
	void CPU::op_cb_FC() { SET_U3_R8({7}, m_registers.h); }
	void CPU::op_cb_FD() { SET_U3_R8({7}, m_registers.l); }
	void CPU::op_cb_FE() { SET_U3_HL({7}); }
	void CPU::op_cb_FF() { SET_U3_R8({7}, m_registers.a); }
}