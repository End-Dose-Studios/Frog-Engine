#include <iostream>

#include "FrogEngine.h"
#include "GraphicsEngine.h"

namespace FrogEngine::Graphics {
    vk::RenderPass *GraphicsEngine::createRenderPass() {
        vk::RenderPass *render_pass = &renderPasses.emplace_back();

        vk::AttachmentDescription color_attachment_description{};
        color_attachment_description.format = swapchainSurfaceFormat.format;
        color_attachment_description.samples = vk::SampleCountFlagBits::e1;
        color_attachment_description.loadOp = vk::AttachmentLoadOp::eClear;
        color_attachment_description.storeOp = vk::AttachmentStoreOp::eStore;
        color_attachment_description.stencilLoadOp = vk::AttachmentLoadOp::eDontCare;
        color_attachment_description.stencilStoreOp = vk::AttachmentStoreOp::eDontCare;
        color_attachment_description.initialLayout = vk::ImageLayout::eUndefined;
        color_attachment_description.finalLayout = vk::ImageLayout::ePresentSrcKHR;

        vk::AttachmentReference color_attachment_reference{};
        color_attachment_reference.attachment = 0;
        color_attachment_reference.layout = vk::ImageLayout::eColorAttachmentOptimal;

        vk::SubpassDescription subpass_description{};
        subpass_description.pipelineBindPoint = vk::PipelineBindPoint::eGraphics;
        subpass_description.colorAttachmentCount = 1;
        subpass_description.pColorAttachments = &color_attachment_reference;

        vk::RenderPassCreateInfo render_pass_info{};
        render_pass_info.attachmentCount = 1;
        render_pass_info.pAttachments = &color_attachment_description;
        render_pass_info.subpassCount = 1;
        render_pass_info.pSubpasses = &subpass_description;

        *render_pass = frogEnginePtr->vulkan.vkDevice.createRenderPass(render_pass_info);

        std::println(std::cout, "--------Render-Pass-Created-------");

        return render_pass;
    }

    void GraphicsEngine::destroyRenderPass(const vk::RenderPass *render_pass) const {
        frogEnginePtr->vulkan.vkDevice.destroyRenderPass(*render_pass);

        std::println(std::cout, "-------Render-Pass-Destroyed------");
    }
}
