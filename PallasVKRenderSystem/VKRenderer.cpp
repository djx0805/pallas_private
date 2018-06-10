#include "VKRenderer.h"
#include <iostream>

#include "..\PallasCore\RenderTarget.h"
#include "..\PallasCore\RenderWindow.h"

namespace pallas
{
	void VKRenderer::Render(RenderStage* prs)
	{
		mRenderStage = prs;
	}

	bool VKRenderer::Init() {
		if(!createVKInstance())
		    return false;
		if (!getVKPhysicalDevice())
			return false;
		if (!createLogicDevice())
			return false;
		if (dynamic_cast<pallas::RenderWindow*>(mRenderStage->GetRenderTarget()) != nullptr) {

		}
		else {

		}
	}


	VkBool32 __stdcall debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
		std::cout << "validation layer: " << msg << std::endl;
		return VK_FALSE;
	}
	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const    VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}
	bool VKRenderer::createVKInstance() {
		//create instance
		VkApplicationInfo application_info;
		application_info.sType = VkStructureType::VK_STRUCTURE_TYPE_APPLICATION_INFO;
		application_info.pNext = nullptr;
		application_info.pApplicationName = "VKRenderer";
		application_info.applicationVersion = 1;
		application_info.pEngineName = nullptr;
		application_info.engineVersion = 1;
		application_info.apiVersion = VK_MAKE_VERSION(1, 0, 0);
		//
		std::vector<const char*> extensions;
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
		extensions.push_back(VK_KHR_SURFACE_EXTENSION_NAME);
		extensions.push_back(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
		const std::vector<const char*> validationLayers = {
			"VK_LAYER_LUNARG_standard_validation",
			//"VK_LAYER_LUNARG_swapchain"
		};
		VkInstanceCreateInfo instance_create_info = {};
		instance_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instance_create_info.pNext = nullptr;
		instance_create_info.flags = 0;
		instance_create_info.pApplicationInfo = &application_info;
		instance_create_info.enabledLayerCount = validationLayers.size();
		instance_create_info.ppEnabledLayerNames = validationLayers.data();
		instance_create_info.enabledExtensionCount = extensions.size();
		instance_create_info.ppEnabledExtensionNames = extensions.data();
		//
		if (vkCreateInstance(&instance_create_info, nullptr, &mVKInstance) == VkResult::VK_SUCCESS) {
			VkDebugReportCallbackCreateInfoEXT createInfo = {};
			VkDebugReportCallbackEXT callback;
			createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
			createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
			createInfo.pfnCallback = debugCallback;//pUserData 也可以指定数据，类似userData
			if (CreateDebugReportCallbackEXT(mVKInstance, &createInfo, nullptr, &callback) != VK_SUCCESS) {
				vkDestroyInstance(mVKInstance, nullptr);
				std::cout << "create instance failed" << std::endl;
				return false;
			}
			//
			uint32_t numInstanceLayers;
			vkEnumerateInstanceLayerProperties(&numInstanceLayers, nullptr);
			if (numInstanceLayers != 0)
			{
				mInstanceLayerProperties.resize(numInstanceLayers);
				vkEnumerateInstanceLayerProperties(
					&numInstanceLayers,
					mInstanceLayerProperties.data());
			}
			return true;
		}
		//
		std::cout << "create instance failed" << std::endl;
		return false;
	}

	bool VKRenderer::getVKPhysicalDevice() {
		//enum physical device
		uint32_t physical_device_count = 0;
		vkEnumeratePhysicalDevices(mVKInstance, &physical_device_count, nullptr);
		std::vector<VkPhysicalDevice>physical_devices(physical_device_count);
		if (vkEnumeratePhysicalDevices(mVKInstance, &physical_device_count, physical_devices.data()) == VkResult::VK_SUCCESS) {
			for each (auto device in physical_devices)
			{
				VkPhysicalDeviceProperties properties;
				vkGetPhysicalDeviceProperties(device, &properties);
				std::cout << "device name : " << properties.deviceName << std::endl;
				std::cout << "device id : " << properties.deviceID << std::endl;
				std::cout << "device type : " << properties.deviceType << std::endl;
			}
		}
		mGPU = physical_devices[0];
		//enum queue family 
		uint32_t queue_family_count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(mGPU, &queue_family_count, nullptr);
		mGPUQueueFamilyProperties.resize(queue_family_count);
		vkGetPhysicalDeviceQueueFamilyProperties(mGPU, &queue_family_count, mGPUQueueFamilyProperties.data());
		for (auto itr = mGPUQueueFamilyProperties.begin(); itr != mGPUQueueFamilyProperties.end(); ++itr)
		{
			std::cout << itr->queueFlags << ";" << itr->queueCount << std::endl;
		}
		//get device features
		vkGetPhysicalDeviceFeatures(mGPU, &mGPUFeatures);
		vkGetPhysicalDeviceMemoryProperties(mGPU, &mGPUMemoryProperties);
		//
		uint32_t numLayers;
		vkEnumerateDeviceLayerProperties(mGPU, &numLayers, nullptr);
		if (numLayers != 0)
		{
			mInstanceLayerProperties.resize(numLayers);
			vkEnumerateDeviceLayerProperties(
				mGPU,
				&numLayers,
				mGPULayerProperties.data());
		}
		//
		return true;
	}

	bool VKRenderer::createLogicDevice() {
		//create logic device
		VkDeviceQueueCreateInfo queue_create_info[1];
		float priorities[1] = { 1.0f };
		memset(&queue_create_info[0], 0, sizeof(VkDeviceQueueCreateInfo));
		queue_create_info[0].sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queue_create_info[0].flags = 0;
		queue_create_info[0].pNext = NULL;
		queue_create_info[0].queueFamilyIndex = 0;
		queue_create_info[0].queueCount = 1;
		queue_create_info[0].pQueuePriorities = priorities;
		//
		std::vector<char*> enabledDeviceLayers;
		enabledDeviceLayers.push_back("VK_LAYER_LUNARG_standard_validation");
		std::vector<char*> enabledDeviceExtensions;
		enabledDeviceExtensions.push_back("VK_KHR_swapchain");
		VkDeviceCreateInfo device_create_info = {};
		device_create_info.sType = VkStructureType::VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		device_create_info.flags = 0;
		device_create_info.pEnabledFeatures = &mGPUFeatures;
		device_create_info.enabledLayerCount = enabledDeviceLayers.size();
		device_create_info.ppEnabledLayerNames = enabledDeviceLayers.data();
		device_create_info.enabledExtensionCount = enabledDeviceExtensions.size();
		device_create_info.ppEnabledExtensionNames = enabledDeviceExtensions.data();
		device_create_info.pQueueCreateInfos = queue_create_info;
		device_create_info.queueCreateInfoCount = 1;
		//
		if (vkCreateDevice(mGPU, &device_create_info, nullptr, &mLogicDevice) == VkResult::VK_SUCCESS)
		{

		}
		else {
			std::cout << "create logic device failed" << std::endl;
			return false;
		}
		//
		return true;
	}
}