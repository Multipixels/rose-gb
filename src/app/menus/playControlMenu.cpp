#include "playControlMenu.h"

#include "imgui.h"

PlayControlMenu::PlayControlMenu(rose_core::Rose* roseInstance)
    : roseInstance(roseInstance)
{

}

void PlayControlMenu::Draw()
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