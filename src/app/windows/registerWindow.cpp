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

    auto test = roseInstance->viewCPU().viewRegisters();
    
    ImGui::Text("AF: 0x%04X", test.af);
    ImGui::Text("BC: 0x%04X", test.bc);
    ImGui::Text("DE: 0x%04X", test.de);
    ImGui::Text("HL: 0x%04X", test.hl);
    ImGui::Text("SP: 0x%04X", test.stackPointer);
    ImGui::Text("PC: 0x%04X", test.programCounter);

    ImGui::End();
}