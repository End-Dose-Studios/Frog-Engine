cmake_minimum_required(VERSION 3.31) # NOLINT
project(FrogEngine)

set(CMAKE_CXX_STANDARD 23)

# =========================
# Optimizations for Release
# =========================
add_compile_options(
        $<$<CONFIG:Release>:/O2>
        $<$<CONFIG:Release>:/Oi>
        $<$<CONFIG:Release>:/GL>
        $<$<CONFIG:Release>:/Gy>
        $<$<CONFIG:Release>:/fp:fast>
        $<$<CONFIG:Release>:/Ot>
        $<$<CONFIG:Release>:/MP>
)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG /OPT:REF /OPT:ICF"
)

# =====================
# Optimizations for Debug
# =====================
add_compile_options(
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Debug>:/Zi>
        $<$<CONFIG:Debug>:/MP>
)

# =====================
# Include Directories
# =====================
set(FROG_ENGINE_INCLUDE_DIRS "C:/Main/Coding/C/FrogEngine/Include")
set(GLFW_INCLUDE_DIRS "C:/glfw-3.4/Include")
set(GLFW_LIB "C:/glfw-3.4/lib-vc2022/glfw3.lib")
find_package(Vulkan REQUIRED)

# =====================
# Static Library Target
# =====================
add_library(FrogEngine STATIC
        Include/Window.h
        Include/FrogEngine.h
        Include/Vulkan.h
        Include/GraphicsEngine.h
        Include/AssetEngine.h
        Src/FrogEngine/FrogEngine.cpp
        Src/FrogEngine/Window/Window.cpp
        Src/FrogEngine/Vulkan/Instance.cpp
        Src/FrogEngine/Vulkan/DebugMessenger.cpp
        Src/FrogEngine/Vulkan/PhysicalDevice.cpp
        Src/FrogEngine/Vulkan/QueueFamilies.cpp
        Src/FrogEngine/Vulkan/Surface.cpp
        Src/FrogEngine/Vulkan/LogicalDevice.cpp
        src/AssetEngine/AssetEngine.cpp
        src/GraphicsEngine/GraphicsEngine.cpp
        src/GraphicsEngine/Swapchain.cpp
        src/GraphicsEngine/SwapchainImages.cpp
        src/AssetEngine/AssetCreator.cpp
        Src/FrogEngine/Vulkan/Vulkan.cpp
)

# =====================
# Include Paths
# =====================
target_include_directories(FrogEngine
        PUBLIC ${GLFW_INCLUDE_DIRS}
        ${FROG_ENGINE_INCLUDE_DIRS}
)

# =====================
# Link External Libraries
# =====================
target_link_libraries(FrogEngine
        PUBLIC ${GLFW_LIB}
        Vulkan::Vulkan
)