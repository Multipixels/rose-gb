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

    ImGui::End();
}