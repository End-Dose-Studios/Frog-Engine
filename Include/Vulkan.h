#pragma once

#include <vulkan/vulkan.hpp>

namespace FrogEngine {
    class FrogEngine;
}
namespace FrogEngine::Vulkan {

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

        [[nodiscard]] bool isComplete() const {
            return (graphicsFamily < UINT32_MAX) && (computeFamily < UINT32_MAX) &&
                   (presentCount < UINT32_MAX);
        }
    };

    class Vulkan {
    public:
        explicit Vulkan(FrogEngine *frog_engine_ptr);
        ~Vulkan();

        void initVulkan();

#ifndef NDEBUG
        bool enableDebugExtensions{true};
#else
        bool enableDebugExtensions{false};
#endif

        vk::PhysicalDevice *selectedDevice{nullptr};
        vk::SurfaceKHR vkSurface;
        QueueFamilyIndices queueIndices;
        vk::Device vkDevice;

        FrogEngine *frogEnginePtr;

    private:
        void createInstance();
        void destroyInstance() const;
        vk::Instance vkInstance;

        void createDebugMessenger();
        void destroyDebugMessenger() const;
        vk::DebugUtilsMessengerEXT vkDebugMessenger;

        void getPhysicalDevices();
        std::vector<vk::PhysicalDevice> physicalDevices;

        void createSurface();
        void destroySurface() const;

        void getQueueFamilyIndices();

        void createLogicalDevice();
        void destroyLogicalDevice() const;
        vk::Queue vkGraphicsQueue;
        vk::Queue vkPresentQueue;
        vk::Queue vkTransferQueue;
        vk::Queue vkComputeQueue;
    };
}