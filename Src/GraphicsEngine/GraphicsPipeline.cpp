#include <GraphicsEngine.h>
#include <iostream>

#include "FrogEngine.h"

namespace FrogEngine::Graphics {
    GraphicsPipeline *GraphicsEngine::createGraphicsPipeline(FrogAsset vert, FrogAsset frag,
                                                             const vk::RenderPass *render_pass) {
        GraphicsPipeline *graphics_pipeline = &graphicPipelines.emplace_back();

        if (vert == nullptr || frag == nullptr)
            throw std::runtime_error("Vertex and fragment shaders missing.");

        vk::PipelineShaderStageCreateInfo vertex_shader_info = {};
        vertex_shader_info.stage = vk::ShaderStageFlagBits::eVertex;
        vertex_shader_info.module = *static_cast<const vk::ShaderModule *>(vert);
        vertex_shader_info.pName = "main";

        vk::PipelineShaderStageCreateInfo fragment_shader_info = {};
        fragment_shader_info.stage = vk::ShaderStageFlagBits::eFragment;
        fragment_shader_info.module = *static_cast<const vk::ShaderModule *>(frag);
        fragment_shader_info.pName = "main";

        std::vector<vk::PipelineShaderStageCreateInfo> const shader_stages = {vertex_shader_info,
                                                                              fragment_shader_info};

        const std::vector<vk::DynamicState> dynamic_states = {vk::DynamicState::eViewport,
                                                              vk::DynamicState::eScissor};

        vk::PipelineDynamicStateCreateInfo dynamic_state_info{};
        dynamic_state_info.dynamicStateCount = static_cast<uint32_t>(dynamic_states.size());
        dynamic_state_info.pDynamicStates = dynamic_states.data();

        vk::PipelineVertexInputStateCreateInfo vertex_input_info = {};
        vertex_input_info.vertexBindingDescriptionCount = 0;
        vertex_input_info.pVertexBindingDescriptions = nullptr;
        vertex_input_info.vertexAttributeDescriptionCount = 0;
        vertex_input_info.pVertexAttributeDescriptions = nullptr;

        vk::PipelineInputAssemblyStateCreateInfo input_assembly_info = {};
        input_assembly_info.topology = vk::PrimitiveTopology::eTriangleList;
        input_assembly_info.primitiveRestartEnable = vk::False;

        vk::Viewport viewport{};
        viewport.x = 0.0F;
        viewport.y = 0.0F;
        viewport.width = static_cast<float>(swapchainExtent.width);
        viewport.height = static_cast<float>(swapchainExtent.height);
        viewport.minDepth = 0.0F;
        viewport.maxDepth = 1.0F;

        vk::Rect2D scissor{};
        scissor.offset = vk::Offset2D{0, 0};
        scissor.extent = swapchainExtent;

        vk::PipelineViewportStateCreateInfo viewport_state_info = {};
        viewport_state_info.viewportCount = 1;
        viewport_state_info.pViewports = &viewport;
        viewport_state_info.scissorCount = 1;
        viewport_state_info.pScissors = &scissor;

        vk::PipelineRasterizationStateCreateInfo rasterizer_info = {};
        rasterizer_info.depthClampEnable = VK_FALSE;
        rasterizer_info.rasterizerDiscardEnable = vk::False;
        rasterizer_info.polygonMode = vk::PolygonMode::eFill;
        rasterizer_info.lineWidth = 1.0F;
        rasterizer_info.cullMode = vk::CullModeFlagBits::eBack;
        rasterizer_info.frontFace = vk::FrontFace::eClockwise;
        rasterizer_info.depthBiasEnable = vk::False;
        rasterizer_info.depthBiasConstantFactor = 0.0F;
        rasterizer_info.depthBiasClamp = 0.0F;
        rasterizer_info.depthBiasSlopeFactor = 0.0F;

        vk::PipelineMultisampleStateCreateInfo multisample_info = {};
        multisample_info.sampleShadingEnable = vk::False;
        multisample_info.rasterizationSamples = vk::SampleCountFlagBits::e1;
        multisample_info.minSampleShading = 1.0F;
        multisample_info.pSampleMask = nullptr;
        multisample_info.alphaToCoverageEnable = vk::False;
        multisample_info.alphaToOneEnable = vk::False;

        vk::PipelineColorBlendAttachmentState color_blend_attachment = {};
        color_blend_attachment.colorWriteMask =
                vk::ColorComponentFlagBits::eR | vk::ColorComponentFlagBits::eG |
                vk::ColorComponentFlagBits::eB | vk::ColorComponentFlagBits::eA;
        color_blend_attachment.blendEnable = vk::False;
        color_blend_attachment.srcColorBlendFactor = vk::BlendFactor::eOne;
        color_blend_attachment.dstColorBlendFactor = vk::BlendFactor::eZero;
        color_blend_attachment.colorBlendOp = vk::BlendOp::eAdd;
        color_blend_attachment.srcAlphaBlendFactor = vk::BlendFactor::eOne;
        color_blend_attachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
        color_blend_attachment.alphaBlendOp = vk::BlendOp::eAdd;
        color_blend_attachment.blendEnable = VK_TRUE;
        color_blend_attachment.srcColorBlendFactor = vk::BlendFactor::eSrcAlpha;
        color_blend_attachment.dstColorBlendFactor = vk::BlendFactor::eOneMinusSrcAlpha;
        color_blend_attachment.colorBlendOp = vk::BlendOp::eAdd;
        color_blend_attachment.srcAlphaBlendFactor = vk::BlendFactor::eOne;
        color_blend_attachment.dstAlphaBlendFactor = vk::BlendFactor::eZero;
        color_blend_attachment.alphaBlendOp = vk::BlendOp::eAdd;

        vk::PipelineColorBlendStateCreateInfo color_blending_info = {};
        color_blending_info.logicOpEnable = vk::False;
        color_blending_info.logicOp = vk::LogicOp::eCopy;
        color_blending_info.attachmentCount = 1;
        color_blending_info.pAttachments = &color_blend_attachment;
        color_blending_info.blendConstants[0] = 0.0F;
        color_blending_info.blendConstants[1] = 0.0F;
        color_blending_info.blendConstants[2] = 0.0F;
        color_blending_info.blendConstants[3] = 0.0F;

        vk::PipelineLayoutCreateInfo pipeline_layout_info = {};
        pipeline_layout_info.setLayoutCount = 0;
        pipeline_layout_info.pSetLayouts = nullptr;
        pipeline_layout_info.pushConstantRangeCount = 0;
        pipeline_layout_info.pPushConstantRanges = nullptr;

        graphics_pipeline->pipelineLayout =
                frogEnginePtr->vulkan.vkDevice.createPipelineLayout(pipeline_layout_info);

        vk::GraphicsPipelineCreateInfo graphics_pipeline_info{};
        graphics_pipeline_info.stageCount = 2;
        graphics_pipeline_info.pStages = shader_stages.data();
        graphics_pipeline_info.pVertexInputState = &vertex_input_info;
        graphics_pipeline_info.pInputAssemblyState = &input_assembly_info;
        graphics_pipeline_info.pViewportState = &viewport_state_info;
        graphics_pipeline_info.pRasterizationState = &rasterizer_info;
        graphics_pipeline_info.pMultisampleState = &multisample_info;
        graphics_pipeline_info.pDepthStencilState = nullptr;
        graphics_pipeline_info.pColorBlendState = &color_blending_info;
        graphics_pipeline_info.pDynamicState = &dynamic_state_info;
        graphics_pipeline_info.layout = graphics_pipeline->pipelineLayout;
        graphics_pipeline_info.renderPass = *render_pass;
        graphics_pipeline_info.subpass = 0;
        graphics_pipeline_info.basePipelineHandle = nullptr;
        graphics_pipeline_info.basePipelineIndex = -1;

        graphics_pipeline->pipeline =
                frogEnginePtr->vulkan.vkDevice
                        .createGraphicsPipelines(nullptr, graphics_pipeline_info)
                        .value[0];

        std::println(std::cout, "--------Pipeline(s)-Created-------");

        return graphics_pipeline;
    }

    void GraphicsEngine::destroyGraphicsPipeline(const GraphicsPipeline *graphics_pipeline) const {
        frogEnginePtr->vulkan.vkDevice.destroyPipeline(graphics_pipeline->pipeline);
        frogEnginePtr->vulkan.vkDevice.destroyPipelineLayout(graphics_pipeline->pipelineLayout);

        std::println(std::cout, "-------Pipeline(s)-Destroyed------");

        graphics_pipeline = nullptr;
    }

}