#pragma once

#include <vulkan/vulkan.hpp>

class GLFWwindow;
namespace EngineCore {
    class EngineCore;

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

    class VulkanEngine {
    public:
        VulkanEngine();
        ~VulkanEngine();

        void InitVulkanEngine(const EngineCore *engine_core);

        vk::Instance *GetInstancePtr();
        const vk::SurfaceKHR *GetSurfacePtr() const;
        vk::PhysicalDevice *GetPhysicalDevicePtr() const;
        const QueueFamilyIndices *GetQueueFamilyIndicesPtr() const;
        const vk::Device *GetDevicePtr() const;

#ifndef NDEBUG
        bool enableDebugExtensions{true};
#else
        bool enableDebugExtensions{false};
#endif

        GLFWwindow *windowPtr;

    private:
        void CreateInstance();
        void DestroyInstance() const;
        vk::Instance vkInstance;

        void CreateDebugMessenger();
        void DestroyDebugMessenger() const;
        vk::DebugUtilsMessengerEXT vkDebugMessenger;

        void GetPhysicalDevices();
        std::vector<vk::PhysicalDevice> physicalDevices;
        vk::PhysicalDevice *selectedDevice{nullptr};

        void CreateSurface();
        void DestroySurface() const;
        vk::SurfaceKHR vkSurface;

        void GetQueueFamilyIndices();
        QueueFamilyIndices queueIndices;

        void CreateLogicalDevice();
        void DestroyLogicalDevice() const;
        vk::Device vkDevice;
        vk::Queue vkGraphicsQueue;
        vk::Queue vkPresentQueue;
        vk::Queue vkTransferQueue;
        vk::Queue vkComputeQueue;
    };
} // namespace EngineCore