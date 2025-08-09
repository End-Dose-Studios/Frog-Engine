#include <iostream>

#include "../../EngineCore/VulkanEngine/VulkanEngine.h"
#include "VulkanGraphics.h"

namespace Graphics {
    void VulkanGraphics::CreateSwapchainImages() {
        swapchainImages = vulkanEnginePtr->GetDevicePtr()->getSwapchainImagesKHR(vkSwapchain);

        for (const auto &image: swapchainImages) {
            vk::ImageViewCreateInfo image_view_info{};
            image_view_info.image = image;
            image_view_info.viewType = vk::ImageViewType::e2D;
            image_view_info.format = swapchainSurfaceFormat.format;

            vk::ComponentMapping component_mapping{};
            component_mapping.r = vk::ComponentSwizzle::eIdentity;
            component_mapping.g = vk::ComponentSwizzle::eIdentity;
            component_mapping.b = vk::ComponentSwizzle::eIdentity;
            component_mapping.a = vk::ComponentSwizzle::eIdentity;
            image_view_info.components = component_mapping;

            vk::ImageSubresourceRange subresource_range{};
            subresource_range.aspectMask = vk::ImageAspectFlagBits::eColor;
            subresource_range.baseMipLevel = 0;
            subresource_range.levelCount = 1;
            subresource_range.baseArrayLayer = 0;
            subresource_range.layerCount = 1;
            image_view_info.subresourceRange = subresource_range;

            swapchainImageViews.emplace_back(
                    vulkanEnginePtr->GetDevicePtr()->createImageView(image_view_info));
            println(std::cout, "--------Image-View-Created--------");
        }
    }

    void VulkanGraphics::DestroySwapchainImages() const {
        for (const auto &image_view: swapchainImageViews) {
            vulkanEnginePtr->GetDevicePtr()->destroyImageView(image_view);
            println(std::cout, "-------Image-View-Destroyed-------");
        }
    }

} // namespace Graphics