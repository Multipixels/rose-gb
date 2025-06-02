#pragma once

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
		short accumulatorFlags;
		short bc; 
		short de;
		short hl;
		short stackPointer;
		short programCounter;
	};
}