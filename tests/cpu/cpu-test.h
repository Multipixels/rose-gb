#pragma once

#include "cpu.h"

typedef enum ERegister {
	AF, BC, DE, HL, SP, PC, A, F, B, C, D, E, H, L
} ERegister;

rose_core::u16 getERegister(rose_core::CPU& cpu, ERegister eRegister);