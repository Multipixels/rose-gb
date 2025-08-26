#pragma once

#include "mmu.h"

void loadTestCartridge(std::string path, rose_core::MMU& mmu);
void loadVectorToMemory(std::vector<rose_core::u8>& values, rose_core::MMU& mmu);