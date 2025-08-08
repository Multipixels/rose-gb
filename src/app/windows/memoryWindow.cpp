#include "memoryWindow.h"

#include "imgui.h"


MemoryWindow::MemoryWindow(rose::Rose* roseInstance)
    : roseInstance(roseInstance)
{
    
}

void MemoryWindow::Draw()
{
    static float f = 0.0f;

    static std::vector<u8> test = roseInstance->getMMU().getMemory();

    if (!ImGui::Begin("Memory"))                          // Create a window called "Hello, world!" and append into it.
    {
        ImGui::End();
        return;
    }

    if (ImGui::BeginTable("MemoryTable", 16))
    {
        ImGuiListClipper clipper;
        clipper.Begin(4096);

        while (clipper.Step())
        {
            for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
            {
                ImGui::TableNextRow();
                for (int column = 0; column < 16; column++)
                {
                    ImGui::TableSetColumnIndex(column);
                    ImGui::Text("%02X", test[16 * row + column]);
                }
            }
        }
        ImGui::EndTable();
    }

    ImGui::End();
}