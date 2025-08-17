#include "registerWindow.h"

#include "imgui.h"

RegisterWindow::RegisterWindow(rose_core::Rose* roseInstance)
    : roseInstance(roseInstance)
{

}

void RegisterWindow::Draw()
{
    if (!ImGui::Begin("Registers"))
    {
        ImGui::End();
        return;
    }

    auto registers = roseInstance->viewCPU().viewRegisters();
    
    ImGui::Text("AF: 0x%04X", registers.af);
    ImGui::Text("BC: 0x%04X", registers.bc);
    ImGui::Text("DE: 0x%04X", registers.de);
    ImGui::Text("HL: 0x%04X", registers.hl);
    ImGui::Text("SP: 0x%04X", registers.stackPointer);
    ImGui::Text("PC: 0x%04X", registers.programCounter);

    ImGui::End();
}