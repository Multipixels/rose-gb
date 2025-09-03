set(ImGuiSource ../../vendor/ImGui/imgui.cpp 
                ../../vendor/ImGui/imgui.h 
                ../../vendor/ImGui/imgui_demo.cpp 
                ../../vendor/ImGui/imgui_draw.cpp 
                ../../vendor/ImGui/imgui_internal.h
                ../../vendor/ImGui/imgui_tables.cpp 
                ../../vendor/ImGui/imgui_widgets.cpp 
                ../../vendor/ImGui/imstb_rectpack.h 
                ../../vendor/ImGui/imstb_textedit.h
                ../../vendor/ImGui/imstb_truetype.h
                ../../vendor/ImGui/backends/imgui_impl_sdl3.cpp
                ../../vendor/ImGui/backends/imgui_impl_sdl3.h
                ../../vendor/ImGui/backends/imgui_impl_opengl3.cpp
                ../../vendor/ImGui/backends/imgui_impl_opengl3.h
                ../../vendor/ImGui/misc/cpp/imgui_stdlib.cpp
                ../../vendor/ImGui/misc/cpp/imgui_stdlib.h
)

add_library("RoseCore" STATIC
    ${ImGuiSource}
    "cartridge/cartridge.cpp" 
    "cartridge/cartridge.h" 
    "cpu/cpu.cpp"
    "cpu/cpu.h"
    "interruptHandler/interruptHandler.cpp"
    "interruptHandler/interruptHandler.h"
    "mmu/mmu.cpp"
    "mmu/mmu.h"
    "timer/timer.cpp"
    "timer/timer.h"
    "utility/definitions.h" 
    "rose.cpp" 
    "rose.h"
)

set_property(TARGET "RoseCore" PROPERTY CXX_STANDARD 23)
target_link_libraries(RoseCore PRIVATE vendor glad)

target_include_directories(RoseCore PUBLIC 
    "../../vendor/ImGui"
)

if(MSVC)
	target_compile_definitions("RoseCore" PUBLIC _CRT_SECURE_NO_WARNING)
endif()