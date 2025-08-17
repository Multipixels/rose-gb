#include "playControlWindow.h"

#include "imgui.h"

PlayControlWindow::PlayControlWindow(rose_core::Rose* roseInstance)
    : roseInstance(roseInstance)
{

}

void PlayControlWindow::Draw()
{
    if (!ImGui::Begin("Play Controls"))
    {
        ImGui::End();
        return;
    }

    if (ImGui::Button("Play"))
    {
        roseInstance->togglePause();
    }

    if (ImGui::Button("Step"))
    {
        roseInstance->stepForward();
    }

    ImGui::End();
}