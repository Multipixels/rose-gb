#include "registerMenu.h"

#include "imgui.h"

RegisterMenu::RegisterMenu(rose_core::Rose* roseInstance)
    : roseInstance(roseInstance)
{

}

void RegisterMenu::Draw()
{
    if (!ImGui::Begin("Registers"))
    {
        ImGui::End();
        return;
    }

    static const rose_core::CPU::Registers& registers = roseInstance->viewCPU().viewRegisters();
    
    ImGui::Text("AF: 0x%04X", registers.af);
    ImGui::Text("BC: 0x%04X", registers.bc);
    ImGui::Text("DE: 0x%04X", registers.de);
    ImGui::Text("HL: 0x%04X", registers.hl);
    ImGui::Text("SP: 0x%04X", registers.stackPointer);
    ImGui::Text("PC: 0x%04X", registers.programCounter);

    ImGui::End();
}