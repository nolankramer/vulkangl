#include <vulkangl/api.h>

#include <vulkan/vulkan.h>
#include <GL/glew.h>
#include <iostream>
#include <vector>

// Helper macro for error checking
#define VK_CHECK(result) \
    if (result != VK_SUCCESS) { \
        std::cerr << "Vulkan error at " << __FILE__ << ":" << __LINE__ << std::endl; \
        exit(EXIT_FAILURE); \
    }

#ifndef PFNGLGENMEMORYOBJECTSEXTPROC
typedef void (GLAPIENTRY *  PFNGLGENMEMORYOBJECTSEXTPROC) (GLsizei n, GLuint *memoryObjects);
#endif

#ifndef PFNGLIMPORTMEMORYFDEXTPROC
typedef void (GLAPIENTRY *  PFNGLIMPORTMEMORYFDEXTPROC) (GLuint memory, GLuint64 size, GLenum handleType, GLint fd);
#endif

#ifndef PFNGLTEXSTORAGEMEM2DEXTPROC
typedef void (GLAPIENTRY *  PFNGLTEXSTORAGEMEM2DEXTPROC) (GLenum target, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLuint memory, GLuint64 offset);
#endif

#ifndef PFNGLGENSEMAPHORESEXTPROC
typedef void (GLAPIENTRY *  PFNGLGENSEMAPHORESEXTPROC) (GLsizei n, GLuint *semaphores);
#endif

#ifndef PFNGLIMPORTSEMAPHOREFDEXTPROC
typedef void (GLAPIENTRY *  PFNGLIMPORTSEMAPHOREFDEXTPROC) (GLuint semaphore, GLenum handleType, GLint fd);
#endif

// Declare function pointers
PFNGLGENMEMORYOBJECTSEXTPROC glGenMemoryObjectsEXT = nullptr;
PFNGLIMPORTMEMORYFDEXTPROC glImportMemoryFdEXT = nullptr;
PFNGLTEXSTORAGEMEM2DEXTPROC glTexStorageMem2DEXT = nullptr;
PFNGLGENSEMAPHORESEXTPROC glGenSemaphoresEXT = nullptr;
PFNGLIMPORTSEMAPHOREFDEXTPROC glImportSemaphoreFdEXT = nullptr;

void loadOpenGLExtensions();
void importToOpenGL(GLuint &texture, GLuint &memoryObject, GLuint &glSemaphore, VkDevice device, VkDeviceMemory memory, VkSemaphore semaphore, int width, int height);
void cleanup(VkDevice device, VkImage image, VkDeviceMemory memory, VkSemaphore semaphore);
