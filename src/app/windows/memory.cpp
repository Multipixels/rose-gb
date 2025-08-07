#include "memory.h"

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

    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        test[0]++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", test[0]);

    ImGui::End();
}