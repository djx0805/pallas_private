#pragma once
#include "Export.h"
#include "..\PallasCore\Renderer.h"
#include "VulkanSDK\1.0.33.0\Include\vulkan\vk_platform.h"
#include "VulkanSDK\1.0.33.0\Include\vulkan\vulkan.h"

namespace pallas
{
	class PALLASVKRENDERSYSTEM_API VKRenderer : public Renderer
	{
	public:
		void Render(RenderStage* prs) override;
		bool Init();
	private:
		bool createVKInstance();
		bool getVKPhysicalDevice();
		bool createLogicDevice();
	private:
		pallas::ref_ptr<pallas::RenderStage> mRenderStage;
		//
		VkInstance mVKInstance = VK_NULL_HANDLE;
		std::vector<VkLayerProperties> mInstanceLayerProperties;
		VkPhysicalDevice mGPU = VK_NULL_HANDLE;
		std::vector<VkLayerProperties> mGPULayerProperties;
		std::vector<VkQueueFamilyProperties> mGPUQueueFamilyProperties;
		VkPhysicalDeviceMemoryProperties mGPUMemoryProperties;
		VkPhysicalDeviceFeatures mGPUFeatures;
		VkDevice mLogicDevice = VK_NULL_HANDLE;
	};
}