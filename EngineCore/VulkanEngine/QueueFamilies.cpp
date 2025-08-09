#include <iostream>

#include "VulkanEngine.h"

namespace EngineCore {
    void VulkanEngine::GetQueueFamilyIndices() {
        println(std::cout, "------Getting-Queue-Families------");

        const auto queue_families = selectedDevice->getQueueFamilyProperties();

        println(std::cout, "Queue Families: {}", queue_families.size());

        for (int i = 0; i < queue_families.size(); i++) {
            const vk::QueueFamilyProperties family = queue_families[i];

            println(std::cout, "  Queue Family: {}, Count: {}", i, family.queueCount);

            if ((family.queueFlags & vk::QueueFlagBits::eGraphics) && !queueIndices.IsComplete()) {
                queueIndices.graphicsFamily = i;
                queueIndices.graphicsCount = family.queueCount;
            }

            if (const vk::Bool32 present_support =
                        selectedDevice->getSurfaceSupportKHR(i, vkSurface);
                present_support && !queueIndices.IsComplete()) {
                queueIndices.presentFamily = i;
                queueIndices.presentCount = family.queueCount;
            }

            if ((family.queueFlags & vk::QueueFlagBits::eTransfer) &&
                !queueIndices.idealTransferFamily) {
                queueIndices.transferFamily = i;
                queueIndices.transferCount = family.queueCount;
            }

            if ((family.queueFlags & vk::QueueFlagBits::eCompute) &&
                !queueIndices.idealComputeFamily) {
                queueIndices.computeFamily = i;
                queueIndices.computeCount = family.queueCount;
            }

            if (queueIndices.transferFamily != queueIndices.graphicsFamily) {
                queueIndices.idealTransferFamily = true;
            }
            if (queueIndices.computeFamily != queueIndices.graphicsFamily &&
                (queueIndices.computeFamily != queueIndices.transferFamily)) {
                queueIndices.idealComputeFamily = true;
            }
        }
        if (!queueIndices.IsComplete())
            throw std::runtime_error("Queue families are not complete.");

        std::println(std::cout, "Chosen queues:");
        std::println(std::cout, "  Graphic: {}", queueIndices.graphicsFamily);
        std::println(std::cout, "  Present: {}", queueIndices.presentFamily);
        std::println(std::cout, "  Transfer: {}", queueIndices.transferFamily);
        std::println(std::cout, "  Compute: {}", queueIndices.computeFamily);
    }
} // namespace EngineCore