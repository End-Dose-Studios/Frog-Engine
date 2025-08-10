#pragma once

#include "Window/Window.h"

#include <vulkan/vulkan.hpp>

namespace EngineCore {

    struct QueueFamilyIndices {
        uint32_t graphicsFamily{UINT32_MAX};
        uint32_t computeFamily{UINT32_MAX};
        uint32_t transferFamily{UINT32_MAX};
        uint32_t presentFamily{UINT32_MAX};

        uint32_t graphicsCount{UINT32_MAX};
        uint32_t computeCount{UINT32_MAX};
        uint32_t transferCount{UINT32_MAX};
        uint32_t presentCount{UINT32_MAX};

        bool idealComputeFamily{false};
        bool idealTransferFamily{false};

        [[nodiscard]] bool IsComplete() const {
            return (graphicsFamily < UINT32_MAX) && (computeFamily < UINT32_MAX) &&
                   (presentCount < UINT32_MAX);
        }
    };

    class EngineCore {
    public:
        EngineCore();
        ~EngineCore();

        void StartEngineCore();

#ifndef NDEBUG
        bool enableDebugExtensions{true};
#else
        bool enableDebugExtensions{false};
#endif

        Window window;

        vk::PhysicalDevice *selectedDevice{nullptr};
        vk::SurfaceKHR vkSurface;
        QueueFamilyIndices queueIndices;
        vk::Device vkDevice;

    private:
        void CreateInstance();
        void DestroyInstance() const;
        vk::Instance vkInstance;

        void CreateDebugMessenger();
        void DestroyDebugMessenger() const;
        vk::DebugUtilsMessengerEXT vkDebugMessenger;

        void GetPhysicalDevices();
        std::vector<vk::PhysicalDevice> physicalDevices;

        void CreateSurface();
        void DestroySurface() const;

        void GetQueueFamilyIndices();

        void CreateLogicalDevice();
        void DestroyLogicalDevice() const;
        vk::Queue vkGraphicsQueue;
        vk::Queue vkPresentQueue;
        vk::Queue vkTransferQueue;
        vk::Queue vkComputeQueue;
    };
} // namespace EngineCore