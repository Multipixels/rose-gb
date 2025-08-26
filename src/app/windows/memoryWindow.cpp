#include "memoryWindow.h"

#include "imgui.h"
#include "imgui_internal.h"


MemoryWindow::MemoryWindow(rose_core::Rose* roseInstance)
    : roseInstance(roseInstance)
{
    
}

void MemoryWindow::Draw()
{
    static float f = 0.0f;

    static const std::vector<rose_core::u8>& memory = roseInstance->viewMMU().getMemory();
    static const rose_core::CPU::Registers& registers = roseInstance->viewCPU().viewRegisters();

    if (!ImGui::Begin("Memory"))
    {
        ImGui::End();
        return;
    }

    static ImGuiTableFlags table_flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_HighlightHoveredColumn;
    static ImGuiTableColumnFlags column_flags = ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoReorder;
    const char* column_names[17] = { "Offset", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };

    bool scrollToInstr = ImGui::Button("Scroll To Current Instruction");

    if (ImGui::BeginTable("MemoryTable", 17, table_flags))
    {
        ImGuiListClipper clipper;
        clipper.Begin(4096);
        
        for (int i = 0; i < 17; i++)
            ImGui::TableSetupColumn(column_names[i], column_flags);

        ImGui::TableSetupScrollFreeze(1, 1);
        ImGui::TableHeadersRow();

        if (scrollToInstr)
        {
            scrollToInstr = true;
            float row_height = ImGui::GetTextLineHeightWithSpacing(); // Or your actual row height
            float target_scroll_pos = ((registers.programCounter >> 4) - 2) * row_height;
            ImGui::SetScrollY(target_scroll_pos);
        }

        while (clipper.Step())
        {
            for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);  

                if (row == ImGui::TableGetHoveredRow() + clipper.DisplayStart - 2)
                    ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::ColorConvertFloat4ToU32(ImVec4(0.212f, 0.314f, 0.443f, 1.0f)));

                ImGui::Text("%03X0", row);
                for (int column = 0; column < 16; column++)
                {
                    ImGui::TableSetColumnIndex(column + 1); // To account for frozen label column
                    
                    if (registers.programCounter == row * 16 + column)
                        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0.5f, 0, 1.0f)));

                    if (row == ImGui::TableGetHoveredRow() + clipper.DisplayStart - 2 && column == ImGui::TableGetHoveredColumn() - 1)
                        ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::ColorConvertFloat4ToU32(ImVec4(0.212f, 0.314f, 0.443f, 1.0f)));
                    ImGui::Text("%02X", memory[16 * row + column]);
                }
            }
        }
        ImGui::EndTable();
    }

    ImGui::End();
}