#include <vulkangl/api.h>

#include <vulkan/vulkan.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

namespace vulkangl
{

// Loads the necessary OpenGL Extensions to share memory between Vulkan and OpenGL
void VULKANGL_EXPORT loadOpenGLExtensions();

// Imports a texture to OpenGL. The memory is shared between OpenGL and Vulkan. The texture must already exist in Vulkan.
// The semaphore synchronizes memory access between the two APIs.
void VULKANGL_EXPORT importToOpenGL(GLuint &texture,
                                    GLuint &memoryObject,
                                    GLuint &glSemaphore,
                                    VkDevice device,
                                    VkDeviceMemory memory,
                                    VkSemaphore semaphore,
                                    int width, int height);

// Utility function to help draw the texture to a quad that covers the entire surface.
void VULKANGL_EXPORT glDraw();

}
