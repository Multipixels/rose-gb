add_executable("RoseGB" 
    "main.cpp"
)
set_property(TARGET "RoseGB" PROPERTY CXX_STANDARD 23)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "RoseGB")
target_link_libraries(RoseGB PRIVATE vendor)

target_include_directories(RoseGB PUBLIC 
    # "src/ast"
)



if(MSVC)
	target_compile_definitions("RoseGB" PUBLIC _CRT_SECURE_NO_WARNING)
endif()