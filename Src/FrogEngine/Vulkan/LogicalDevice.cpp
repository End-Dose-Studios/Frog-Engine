#include <iostream>
#include <set>
#include <vector>

#include <Vulkan.h>

namespace FrogEngine {
    void Vulkan::CreateLogicalDevice() {
        std::set const queue_indices{queueIndices.graphicsFamily, queueIndices.presentFamily,
                                     queueIndices.computeFamily, queueIndices.transferFamily};

        std::vector<vk::DeviceQueueCreateInfo> queue_infos;
        constexpr float QUEUE_PRIORITY = 1.0F;

        for (uint32_t const queue_index: queue_indices) {
            vk::DeviceQueueCreateInfo queue_info{};
            queue_info.queueFamilyIndex = queue_index;
            queue_info.queueCount = 1;
            queue_info.pQueuePriorities = &QUEUE_PRIORITY;

            queue_infos.push_back(queue_info);
        }

        const std::vector<const char *> device_extensions{vk::KHRSwapchainExtensionName};
        std::vector<const char *> validation_layers{};
        if (enableDebugExtensions) {
            validation_layers.emplace_back("VK_LAYER_KHRONOS_validation");
        }

        const vk::PhysicalDeviceFeatures device_features = selectedDevice->getFeatures();

        vk::DeviceCreateInfo device_info{};
        device_info.queueCreateInfoCount = static_cast<uint32_t>(queue_infos.size());
        device_info.pQueueCreateInfos = queue_infos.data();
        device_info.enabledLayerCount = static_cast<uint32_t>(validation_layers.size());
        device_info.ppEnabledLayerNames = validation_layers.data();
        device_info.enabledExtensionCount = static_cast<uint32_t>(device_extensions.size());
        device_info.ppEnabledExtensionNames = device_extensions.data();
        device_info.pEnabledFeatures = &device_features;

        vkDevice = selectedDevice->createDevice(device_info);
        std::println(std::cout, "------Logical-Device-Created------");


        vkGraphicsQueue = vkDevice.getQueue(queueIndices.graphicsFamily, 0);
        vkGraphicsQueue = vkDevice.getQueue(queueIndices.presentFamily, 0);
        vkGraphicsQueue = vkDevice.getQueue(queueIndices.transferFamily, 0);
        vkGraphicsQueue = vkDevice.getQueue(queueIndices.computeFamily, 0);
    }

    void Vulkan::DestroyLogicalDevice() const {
        vkDevice.destroy();
        std::println(std::cout, "-----Logical-Device-Destroyed-----");
    }

} // namespace FrogEngine