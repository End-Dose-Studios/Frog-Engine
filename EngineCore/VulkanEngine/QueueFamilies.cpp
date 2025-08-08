#include <iostream>

#include "VulkanEngine.h"

namespace EngineCore {
    void VulkanEngine::GetQueueFamilyIndices(const vk::SurfaceKHR *surface) {
        println(std::cout, "------Getting-Queue-Families------");

        const auto queue_families = selectedDevice->getQueueFamilyProperties();

        for (int i = 0; i < queue_families.size(); i++) {
            const vk::QueueFamilyProperties family = queue_families[i];

            println(std::cout, "\tQueue Family: {}, Count: {}", i, family.queueCount);

            if ((family.queueFlags & vk::QueueFlagBits::eGraphics) && !queueFamilies.IsComplete()) {
                queueFamilies.graphicsFamily = i;
                queueFamilies.graphicsCount = family.queueCount;
            }

            if (const vk::Bool32 present_support =
                        selectedDevice->getSurfaceSupportKHR(i, *surface);
                present_support && !queueFamilies.IsComplete()) {
                queueFamilies.presentFamily = i;
                queueFamilies.presentCount = family.queueCount;
            }

            if ((family.queueFlags & vk::QueueFlagBits::eTransfer) &&
                !queueFamilies.idealTransferFamily) {
                queueFamilies.transferFamily = i;
                queueFamilies.transferCount = family.queueCount;
            }

            if ((family.queueFlags & vk::QueueFlagBits::eCompute) &&
                !queueFamilies.idealComputeFamily) {
                queueFamilies.computeFamily = i;
                queueFamilies.computeCount = family.queueCount;
            }

            if (queueFamilies.transferFamily != queueFamilies.graphicsFamily) {
                queueFamilies.idealTransferFamily = true;
            }
            if (queueFamilies.computeFamily != queueFamilies.graphicsFamily &&
                (queueFamilies.computeFamily != queueFamilies.transferFamily)) {
                queueFamilies.idealComputeFamily = true;
            }
        }
        if (!queueFamilies.IsComplete())
            throw std::runtime_error("Queue families are not complete.");

        std::println(std::cout, "\tChosen queues:");
        std::println(std::cout, "\t  Graphic: {}", queueFamilies.graphicsFamily);
        std::println(std::cout, "\t  Transfer: {}", queueFamilies.transferFamily);
        std::println(std::cout, "\t  Compute: {}", queueFamilies.computeFamily);
    }
} // namespace EngineCore