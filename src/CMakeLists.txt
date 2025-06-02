set(ImGuiSource ../vendor/ImGui/imgui.cpp 
                ../vendor/ImGui/imgui.h 
                ../vendor/ImGui/imgui_demo.cpp 
                ../vendor/ImGui/imgui_draw.cpp 
                ../vendor/ImGui/imgui_internal.h
                ../vendor/ImGui/imgui_tables.cpp 
                ../vendor/ImGui/imgui_widgets.cpp 
                ../vendor/ImGui/imstb_rectpack.h 
                ../vendor/ImGui/imstb_textedit.h
                ../vendor/ImGui/imstb_truetype.h
                ../vendor/ImGui/backends/imgui_impl_sdl3.cpp
                ../vendor/ImGui/backends/imgui_impl_sdl3.h
                ../vendor/ImGui/backends/imgui_impl_opengl3.cpp
                ../vendor/ImGui/backends/imgui_impl_opengl3.h
                ../vendor/ImGui/misc/cpp/imgui_stdlib.cpp
                ../vendor/ImGui/misc/cpp/imgui_stdlib.h
)

add_executable("RoseGB" 
    "main.cpp"
    ${ImGuiSource}
    "cpu/cpu.cpp"
    "cpu/cpu.h"
    "mmu/mmu.cpp"
    "mmu/mmu.h"
    "rose.cpp" 
    "rose.h"
    "cartridge/cartridge.cpp" 
    "cartridge/cartridge.h" 
    "utility/definitions.h")

set_property(TARGET "RoseGB" PROPERTY CXX_STANDARD 23)
target_link_libraries(RoseGB PRIVATE vendor glad)

target_include_directories(RoseGB PUBLIC 
    "../vendor/ImGui"
    # "src/ast"
)



if(MSVC)
	target_compile_definitions("RoseGB" PUBLIC _CRT_SECURE_NO_WARNING)
endif()