#include <vulkangl/api.h>

#include <vulkan/vulkan.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

void VULKANGL_EXPORT loadOpenGLExtensions();
void VULKANGL_EXPORT importToOpenGL(GLuint &texture, GLuint &memoryObject, GLuint &glSemaphore, VkDevice device, VkDeviceMemory memory, VkSemaphore semaphore, int width, int height);
void VULKANGL_EXPORT cleanup(VkDevice device, VkImage image, VkDeviceMemory memory, VkSemaphore semaphore);
