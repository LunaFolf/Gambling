cmake_minimum_required(VERSION 3.16)
project(Gambling)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

set(SOURCE_FILES
        src/Main.cpp
)

add_executable(Gambling ${SOURCE_FILES})

target_include_directories(Gambling
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(Gambling
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
)

if (WIN32)
    if (CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(OPENAL_DLL "${sfml_SOURCE_DIR}/extlibs/bin/x64/openal32.dll")
    else()
        set(OPENAL_DLL "${sfml_SOURCE_DIR}/extlibs/bin/x86/openal32.dll")
    endif()
endif ()

add_custom_command(TARGET Gambling POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Assets
        $<TARGET_FILE_DIR:Gambling>/Assets
)

add_custom_command(TARGET Gambling POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:sfml-graphics>
        $<TARGET_FILE:sfml-window>
        $<TARGET_FILE:sfml-system>
        $<TARGET_FILE:sfml-audio>
        $<TARGET_FILE_DIR:Gambling>
)

add_custom_command(TARGET Gambling POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${OPENAL_DLL}"
        $<TARGET_FILE_DIR:Gambling>
)