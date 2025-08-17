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

add_executable("RoseApp" 
    ${ImGuiSource}
    "main.cpp"
    "windows/memoryWindow.cpp"
    "windows/memoryWindow.h"
    "windows/playControlWindow.cpp"
    "windows/playControlWindow.h"
    "windows/registerWindow.cpp"
    "windows/registerWindow.h"
)

find_package(OpenGL REQUIRED)

target_link_libraries(
    RoseApp PRIVATE vendor glad RoseCore OpenGL::GL
)

set_property(TARGET "RoseApp" PROPERTY CXX_STANDARD 23)
set_target_properties("RoseApp" PROPERTIES WIN32_EXECUTABLE TRUE)

target_include_directories(RoseApp PUBLIC 
    "../../vendor/ImGui"
    "windows"
    "../core"
    "../core/cartridge"
    "../core/cpu"
    "../core/mmu"
    "../core/utility"
)

if(MSVC)
	target_compile_definitions("RoseApp" PUBLIC _CRT_SECURE_NO_WARNING)
endif()
