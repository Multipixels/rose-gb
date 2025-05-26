# Made w/ help from Low Level Game Dev: https://www.youtube.com/watch?v=IBgfeZME2Vw

cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 23)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    set(RELEASE_BUILD OFF)
else()
    set(RELEASE_BUILD ON)
endif()

if(RELEASE_BUILD)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) #link time optimization
else()
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)
endif()

project(
  "RoseGB"
  VERSION 1.0
  DESCRIPTION "Game Boy Emulator"
  LANGUAGES CXX
)

# MY_SOURCES is a list of all .cpp files in the project
add_executable("RoseGB" 
    "src/main.cpp"
)
set_property(TARGET "RoseGB" PROPERTY CXX_STANDARD 23)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT "RoseGB")

if(RELEASE_BUILD)
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RELEASE_BUILD=1) 
    message("Release Build")
else()
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC DEVELOPMENT_BUILD=1) 
    message("Debug Build")
endif()

if(MSVC)
	target_compile_definitions("RoseGB" PUBLIC _CRT_SECURE_NO_WARNING)
endif()

target_include_directories(RoseGB PUBLIC 
    # "src/ast"
)

if(MSVC) # If using the VS compiler...
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
endif()

message("CMake Build Type: ${CMAKE_BUILD_TYPE}")