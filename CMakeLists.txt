cmake_minimum_required(VERSION 3.31) #NOLINT
project(FrogEngine)

set(CMAKE_CXX_STANDARD 23)

set(GLFW_INCLUDE_DIRS "C:/glfw-3.4/Include")
set(GLFW_LIB "C:/glfw-3.4/lib-vc2022/glfw3.lib")

find_package(Vulkan REQUIRED)

add_executable(FrogEngine Assets/App.rc
        main.cpp
        EngineCore/EngineCore.cpp
        EngineCore/EngineCore.h
        EngineCore/Window/Window.cpp
        EngineCore/Window/Window.h
        EngineCore/VulkanEngine/VulkanEngine.cpp
        EngineCore/VulkanEngine/VulkanEngine.h
        EngineCore/VulkanEngine/Instance.cpp
        EngineCore/VulkanEngine/DebugMessenger.cpp
        EngineCore/VulkanEngine/PhysicalDevice.cpp
        EngineCore/VulkanEngine/QueueFamilies.cpp
        Loader/Loader.cpp
        Loader/Loader.h
        GraphicsEngine/GraphicsEngine.cpp
        GraphicsEngine/GraphicsEngine.h
)

target_include_directories(FrogEngine
        PRIVATE ${GLFW_INCLUDE_DIRS})

target_link_libraries(FrogEngine
        PUBLIC ${GLFW_LIB}
        PUBLIC Vulkan::Vulkan)

if (MSVC)
    set_target_properties(FrogEngine PROPERTIES
            LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup"
    )
endif ()

add_custom_command(TARGET FrogEngine POST_BUILD
        COMMAND cmd.exe /c "${CMAKE_SOURCE_DIR}/Assets/compile.bat"
        COMMAND cmd.exe /c "FrogPacker ${CMAKE_SOURCE_DIR}/Assets ${CMAKE_SOURCE_DIR}/build-${CMAKE_BUILD_TYPE}/Packages"
)