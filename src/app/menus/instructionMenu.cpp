#include "instructionMenu.h"

#include "imgui.h"

InstructionMenu::InstructionMenu(rose_core::Rose* roseInstance)
    : roseInstance(roseInstance)
{

}

void InstructionMenu::Draw()
{
    if (!ImGui::Begin("Instruction History"))
    {
        ImGui::End();
        return;
    }

    static const rose_core::CPU& cpu = roseInstance->viewCPU();
    static const std::vector<rose_core::u8>& memory = roseInstance->viewMMU().getMemory();
    static const std::array<rose_core::u16, 10>& instrHistory = roseInstance->tempViewInstrHistory();

    static ImGuiTableFlags table_flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_HighlightHoveredColumn;
    static ImGuiTableColumnFlags column_flags = ImGuiTableColumnFlags_WidthFixed | ImGuiTableColumnFlags_NoHide | ImGuiTableColumnFlags_NoReorder;
    const char* column_names[6] = { "Address", "Instruction", "Opcode", "Value 1", "Value 2", "Cycles"};

    if (ImGui::BeginTable("InstructionsTable", 6, table_flags))
    {
        for (int i = 0; i < 6; i++)
            ImGui::TableSetupColumn(column_names[i], column_flags);
        ImGui::TableSetupScrollFreeze(1, 1);
        ImGui::TableHeadersRow();
        
        int index = roseInstance->tempViewInstrHistoryHead();
        for (int i = 0; i < 10; i++)
        {
            int address = roseInstance->tempViewInstrHistory()[(index + i) % 10];
            if ((index + i) % 10 >= roseInstance->tempViewInstrRan()) continue;

            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            ImGui::Text("0x%04X", address);

            bool isCB = false;
            rose_core::CPU::Instruction currentInstr;
            if (memory[address] == 0xCB)
            {
                address++;
                isCB = true;
            }
            rose_core::u8 opcode = memory[address];
            currentInstr = cpu.instr_data[opcode];

            ImGui::TableSetColumnIndex(1);
            ImGui::Text(currentInstr.humanReadable.c_str());

            ImGui::TableSetColumnIndex(2);
            if (!isCB)
                ImGui::Text("0x%02X", memory[address]);
            else
                ImGui::Text("0xCB%02X", memory[address]);

            ImGui::TableSetColumnIndex(3);
            if (currentInstr.bytes >= 2)
                ImGui::Text("0x%02X", memory[address + 1]);

            ImGui::TableSetColumnIndex(4);
            if (currentInstr.bytes >= 3)
                ImGui::Text("0x%02X", memory[address + 2]);

            ImGui::TableSetColumnIndex(5);
            ImGui::Text("%d", currentInstr.cycles);
        }

        ImGui::EndTable();
    }
        
    ImGui::End();
}