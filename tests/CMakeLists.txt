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

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable("RoseTests" 
    ${ImGuiSource}

    "cpu/cpu-test.cpp"
    "cpu/cpu-test.h"
    "mmu/mmu-test.cpp"
    "mmu/mmu-test.h"

    "../src/cpu/cpu.cpp"
    "../src/cpu/cpu.h"
    "../src/mmu/mmu.cpp"
    "../src/mmu/mmu.h"
    "../src/rose.cpp" 
    "../src/rose.h"
    "../src/cartridge/cartridge.cpp" 
    "../src/cartridge/cartridge.h" 
    "../src/utility/definitions.h"
)

target_link_libraries(
    RoseTests PRIVATE vendor glad
    GTest::gtest_main
)

set_property(TARGET "RoseTests" PROPERTY CXX_STANDARD 23)

target_include_directories(RoseTests PUBLIC 
    "../vendor/ImGui"
    "../src"
    "../src/cartridge"
    "../src/cpu"
    "../src/mmu"
    "../src/utility"
)

if(MSVC)
	target_compile_definitions("RoseTests" PUBLIC _CRT_SECURE_NO_WARNING)
endif()
    
include(GoogleTest)
gtest_discover_tests(RoseTests)
