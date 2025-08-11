#include "registerWindow.h"

#include "imgui.h"

RegisterWindow::RegisterWindow(rose::Rose* roseInstance)
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