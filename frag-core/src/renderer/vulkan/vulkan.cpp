#include"Renderer/vulkan/internal_object_type.h"
#include"Utils/StringUtil.h"
#include <limits>
#include"Exception/InvalidArgumentException.h"
#include "Exception/RuntimeExecption.h"

using namespace fragcore;

uint32_t findMemoryType(fragcore::VulkanCore* vulkanCore, uint32_t typeFilter, VkMemoryPropertyFlags properties){


	for (uint32_t i = 0; i < vulkanCore->memProperties.memoryTypeCount; i++) {
		if ((typeFilter & (1 << i)) && (vulkanCore->memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}
}

void createBuffer(VulkanCore* vulkanCore, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
	VkResult result;

	/**/
	VkBufferCreateInfo bufferInfo = {};
	bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferInfo.size = size;
	bufferInfo.usage = usage;
	bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	/**/
	if (vkCreateBuffer(vulkanCore->device, &bufferInfo, NULL, &buffer) != VK_SUCCESS) {
		throw RuntimeException("failed to create buffer!");
	}

	VkMemoryRequirements memRequirements;
	vkGetBufferMemoryRequirements(vulkanCore->device, buffer, &memRequirements);

	/**/
	VkMemoryAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memRequirements.size;
	allocInfo.memoryTypeIndex = findMemoryType(vulkanCore, memRequirements.memoryTypeBits, properties);

	/**/
	if (vkAllocateMemory(vulkanCore->device, &allocInfo, NULL, &bufferMemory) != VK_SUCCESS) {
		throw RuntimeException("failed to allocate buffer memory!");
	}

	/**/
	vkBindBufferMemory(vulkanCore->device, buffer, bufferMemory, 0);
}

VkImageView createImageView(VulkanCore *vulkanCore, VkImage image, VkFormat format) {

	/**/
	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VkImageView imageView;
	if (vkCreateImageView(vulkanCore->device, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
		throw RuntimeException("failed to create texture image view!");
	}

	return imageView;
}

VkShaderModule createShaderModule(VkDevice device, const char* pdata, size_t size){

    VkResult result;
    VkShaderModule module;

    /**/
    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.pCode = (const uint32_t *) pdata;
    createInfo.codeSize = size;

    /**/
    result = vkCreateShaderModule(device, &createInfo, NULL, &module);
    if (result != VK_SUCCESS)
        throw RuntimeException(fvformatf("Failed to create shader module - %d", result));

    return module;
}


bool isDeviceSuitable(VkPhysicalDevice device){
	VkPhysicalDeviceProperties deviceProperties;
	VkPhysicalDeviceFeatures deviceFeatures;
    VkQueueFamilyProperties a;

	/*  */
	vkGetPhysicalDeviceProperties(device, &deviceProperties);
	vkGetPhysicalDeviceFeatures(device, &deviceFeatures);
//	vkGetPhysicalDeviceMemoryProperties()
//	vkGetPhysicalDeviceQueueFamilyProperties()
  //  vkGetPhysicalDeviceQueueFamilyProperties(vulkancore->gpu, &vulkancore->queue_count, NULL);
	/*  Check if device is good enough as a GPU candidates.  */




	/*  */
	printf("%s", deviceProperties.deviceName);
	return (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU || deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU || deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU) &&
	       deviceFeatures.geometryShader;
}

void selectDevices(std::vector<VkPhysicalDevice*>& devices, std::vector<VkPhysicalDevice*>& selectDevices){

    /*  Check for matching. */
    //VK_KHR_device_group_creation
    //VK_KHR_device_group_creation

}

VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
    if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
        return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
    }

    for (const auto& availableFormat : availableFormats) {
        if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
            return availableFormat;
        }
    }

    return availableFormats[0];
}

VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
    VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

    for (const auto& availablePresentMode : availablePresentModes) {
        if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return availablePresentMode;
        } else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
            bestMode = availablePresentMode;
        }
    }

    return bestMode;
}

VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities) {
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        return capabilities.currentExtent;
    } else {
        //TODO determine what
        VkExtent2D actualExtent = {800, 600};

        actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
        actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

        return actualExtent;
    }
}


struct QueueFamilyIndices {
	//std::optional<uint32_t> graphicsFamily;

	bool isComplete() {
		//return graphicsFamily.has_value();
	}
};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
	QueueFamilyIndices indices;

	return indices;
}





//TODO move to the helper file.
unsigned int getTextureFormat(TextureDesc::Format format) {
	switch (format) {
		case TextureDesc::eRGB:
			return VK_FORMAT_R8G8B8_UNORM;
		case TextureDesc::eRGBA:
			return VK_FORMAT_R8G8B8A8_UNORM;
		case TextureDesc::eBGR:
			return VK_FORMAT_B8G8R8_UNORM;
		case TextureDesc::eBGRA:
			return VK_FORMAT_B8G8R8A8_UNORM;
		case TextureDesc::eSRGB:
			return VK_FORMAT_B8G8R8_SRGB;
		case TextureDesc::eSRGBA:
			return VK_FORMAT_B8G8R8A8_UNORM;
		case TextureDesc::eSingleColor:
			return VK_FORMAT_R8_UNORM;
		case TextureDesc::eDepth:
			return VK_FORMAT_R8_UNORM;
		case TextureDesc::eStencil:
			return VK_FORMAT_R8_UNORM;
		case TextureDesc::eDepthStencil:
			return VK_FORMAT_R8G8_UNORM;
		default:
			throw InvalidArgumentException("Invalid texture fvformatf.");
	}
}

unsigned int getTextureTarget(TextureDesc::Target target) {
	switch(target){
		case TextureDesc::eTexture1D:
			return VK_IMAGE_TYPE_1D;
		case TextureDesc::eTexture2D:
			return VK_IMAGE_TYPE_2D;
		case TextureDesc::eTexture3D:
			return VK_IMAGE_TYPE_3D;
		case TextureDesc::eCubeMap:
		default:
			throw InvalidArgumentException("Invalid Texture target");
	}
}

unsigned int getTextureType(TextureDesc::Type type) {

}


unsigned int getBufferType(BufferDesc::BufferType type) {
	switch(type){
		case BufferDesc::eArray:
			return VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		case BufferDesc::eElementArray:
			return VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
		case BufferDesc::eUniform:
			return VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		case BufferDesc::eShaderStorage:
			return VK_BUFFER_USAGE_STORAGE_BUFFER_BIT;
		case BufferDesc::ePixelUnpack:
			return VK_BUFFER_USAGE_TRANSFER_DST_BIT;
		case BufferDesc::ePixelPack:
			return VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
		default:
			assert(0);
	}
}

unsigned int getBufferHint(BufferDesc::BufferHint hint) {
	return 0;
}

unsigned int getPrimitive(GeometryDesc::Primitive primitive) {
	switch (primitive) {
		case GeometryDesc::ePoint:
			return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		case GeometryDesc::eLines:
			return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
		case GeometryDesc::eTriangles:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		case GeometryDesc::eTriangleStrips:
			return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
		default:
			return -1;
	}

}

unsigned int  getAttributeDataType(GeometryDesc::AttributeType type) {
	return 0;
}

unsigned int getState(unsigned int state) {
	return 0;
}