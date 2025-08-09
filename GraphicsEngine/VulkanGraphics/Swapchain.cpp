#include <iostream>

#include <GLFW/glfw3.h>

#include "../../EngineCore/VulkanEngine/VulkanEngine.h"
#include "VulkanGraphics.h"

namespace {
    Graphics::Vulkan::SwapchainDetails getSwapChainDetails(const vk::PhysicalDevice *device,
                                                           const vk::SurfaceKHR *surface) {

        Graphics::Vulkan::SwapchainDetails swapchainDetails;

        swapchainDetails.capabilities = device->getSurfaceCapabilitiesKHR(*surface);
        swapchainDetails.formats = device->getSurfaceFormatsKHR(*surface);
        swapchainDetails.presentModes = device->getSurfacePresentModesKHR(*surface);

        if (swapchainDetails.formats.empty() || swapchainDetails.presentModes.empty()) {
            throw std::runtime_error(
                    "Impressive work. You encountered an error though impossible.");
        }

        return swapchainDetails;
    }

    vk::SurfaceFormatKHR getFormat(const Graphics::Vulkan::SwapchainDetails *details) {
        vk::SurfaceFormatKHR surface_format = details->formats[0];

        for (const auto &format: details->formats) {
            if (format.format == vk::Format::eB8G8R8A8Srgb &&
                format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear) {
                surface_format = format;
            }
        }

        return surface_format;
    }

    vk::PresentModeKHR getPresent(const Graphics::Vulkan::SwapchainDetails *swap_chain_details) {
        auto surface_present_mode = vk::PresentModeKHR::eFifo;

        for (const auto &present_mode: swap_chain_details->presentModes) {
            if (present_mode == vk::PresentModeKHR::eMailbox) {
                surface_present_mode = vk::PresentModeKHR::eMailbox;
            }
        }

        return surface_present_mode;
    }

    vk::Extent2D getExtent(const Graphics::Vulkan::SwapchainDetails *swap_chain_details,
                           GLFWwindow *window) {
        vk::Extent2D extent;
        if (swap_chain_details->capabilities.currentExtent.width !=
            std::numeric_limits<uint32_t>::max()) {
            extent = swap_chain_details->capabilities.currentExtent;
        }
        else {
            int width{};
            int height{};
            glfwGetWindowSize(window, &width, &height);

            vk::Extent2D actual_extent = {static_cast<uint32_t>(width),
                                          static_cast<uint32_t>(height)};

            actual_extent.width = std::clamp(actual_extent.width,
                                             swap_chain_details->capabilities.minImageExtent.width,
                                             swap_chain_details->capabilities.maxImageExtent.width);
            actual_extent.height = std::clamp(
                    actual_extent.height, swap_chain_details->capabilities.minImageExtent.height,
                    swap_chain_details->capabilities.maxImageExtent.height);

            extent = actual_extent;
        }
        std::println(std::cout, "Chosen Extent Size: ({}, {})", extent.width, extent.height);

        return extent;
    }

    uint32_t getImageCount(const Graphics::Vulkan::SwapchainDetails *swap_chain_details) {
        uint32_t image_count = swap_chain_details->capabilities.minImageCount + 1;
        if (swap_chain_details->capabilities.maxImageCount > 0 &&
            image_count > swap_chain_details->capabilities.maxImageCount) {
            image_count = swap_chain_details->capabilities.maxImageCount;
        }
        std::println(std ::cout, "Chosen Image Count: {}", image_count);

        return image_count;
    }
} // namespace

namespace Graphics::Vulkan {
    void Graphics::CreateSwapchain() {
        swapchainDetails = getSwapChainDetails(vulkanEnginePtr->GetPhysicalDevicePtr(),
                                               vulkanEnginePtr->GetSurfacePtr());

        swapchainSurfaceFormat = getFormat(&swapchainDetails).format;
        swapchainPresentMode = getPresent(&swapchainDetails);
        swapchainExtent = getExtent(&swapchainDetails, windowPtr);

        vk::SwapchainCreateInfoKHR swapchain_info{};
        swapchain_info.surface = *vulkanEnginePtr->GetSurfacePtr();
        swapchain_info.minImageCount = getImageCount(&swapchainDetails);
        swapchain_info.imageFormat = swapchainSurfaceFormat.format;
        swapchain_info.imageColorSpace = swapchainSurfaceFormat.colorSpace;
        swapchain_info.imageExtent = swapchainExtent;
        swapchain_info.imageArrayLayers = 1;
        swapchain_info.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;

        const EngineCore::Vulkan::QueueFamilyIndices *queue_indices =
                vulkanEnginePtr->GetQueueFamilyIndicesPtr();

        const std::array<uint32_t, 2> queue_family_indices = {queue_indices->graphicsFamily,
                                                              queue_indices->presentFamily};
        if (queue_indices->graphicsFamily != queue_indices->presentFamily) {
            swapchain_info.imageSharingMode = vk::SharingMode::eConcurrent;
            swapchain_info.queueFamilyIndexCount = queue_family_indices.size();
            swapchain_info.pQueueFamilyIndices = queue_family_indices.data();
        }
        else {
            swapchain_info.imageSharingMode = vk::SharingMode::eExclusive;
            swapchain_info.queueFamilyIndexCount = 0;
            swapchain_info.pQueueFamilyIndices = nullptr;
        }
        swapchain_info.preTransform = swapchainDetails.capabilities.currentTransform;
        swapchain_info.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
        swapchain_info.presentMode = swapchainPresentMode;
        swapchain_info.clipped = vk::True;
        swapchain_info.oldSwapchain = nullptr;

        vkSwapchain = vulkanEnginePtr->GetDevicePtr()->createSwapchainKHR(swapchain_info);
        println(std::cout, "---------Swapchain-Created--------");
    }

    void Graphics::DestroySwapChain() const {
        vulkanEnginePtr->GetDevicePtr()->destroySwapchainKHR(vkSwapchain);
        println(std::cout, "-------Swapchain-Destroyed--------");
    }

} // namespace Graphics::Vulkan