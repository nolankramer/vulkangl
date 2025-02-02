#include <vulkangl/vulkangl.h>

#include <GLFW/glfw3.h>

using namespace vulkangl;

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

void loadOpenGLExtensions() {
    if (!glewIsSupported("GL_EXT_memory_object") || !glewIsSupported("GL_EXT_semaphore")) {
        throw std::runtime_error("Required OpenGL extensions GL_EXT_memory_object or GL_EXT_semaphore are not supported.");
    }

    glGenMemoryObjectsEXT = (PFNGLGENMEMORYOBJECTSEXTPROC)glfwGetProcAddress("glGenMemoryObjectsEXT");
    glImportMemoryFdEXT = (PFNGLIMPORTMEMORYFDEXTPROC)glfwGetProcAddress("glImportMemoryFdEXT");
    glTexStorageMem2DEXT = (PFNGLTEXSTORAGEMEM2DEXTPROC)glfwGetProcAddress("glTexStorageMem2DEXT");
    glGenSemaphoresEXT = (PFNGLGENSEMAPHORESEXTPROC)glfwGetProcAddress("glGenSemaphoresEXT");
    glImportSemaphoreFdEXT = (PFNGLIMPORTSEMAPHOREFDEXTPROC)glfwGetProcAddress("glImportSemaphoreFdEXT");

    if (!glGenMemoryObjectsEXT || !glImportMemoryFdEXT || !glTexStorageMem2DEXT || !glGenSemaphoresEXT || !glImportSemaphoreFdEXT) {
        throw std::runtime_error("Failed to load required OpenGL extension functions.");
    }
}

void importToOpenGL(GLuint &texture,
                    GLuint &memoryObject,
                    GLuint &glSemaphore,
                    VkDevice device,
                    VkDeviceMemory memory,
                    VkSemaphore semaphore,
                    int width, int height) {
    // Obtain file descriptor from Vulkan memory
    int memoryFd;
    VkMemoryGetFdInfoKHR getFdInfo = {};
    getFdInfo.sType = VK_STRUCTURE_TYPE_MEMORY_GET_FD_INFO_KHR;
    getFdInfo.memory = memory;
    getFdInfo.handleType = VK_EXTERNAL_MEMORY_HANDLE_TYPE_OPAQUE_FD_BIT;

    auto vkGetMemoryFdKHR = (PFN_vkGetMemoryFdKHR)vkGetDeviceProcAddr(device, "vkGetMemoryFdKHR");
    VK_CHECK(vkGetMemoryFdKHR(device, &getFdInfo, &memoryFd));

    // Import Vulkan memory into OpenGL
    glGenMemoryObjectsEXT(1, &memoryObject);
    glImportMemoryFdEXT(memoryObject, width * height * 4, GL_HANDLE_TYPE_OPAQUE_FD_EXT, memoryFd);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexStorageMem2DEXT(GL_TEXTURE_2D, 1, GL_RGBA8, width, height, memoryObject, 0);

    // Import Vulkan semaphore into OpenGL
    int semaphoreFd;
    VkSemaphoreGetFdInfoKHR semaphoreFdInfo = {};
    semaphoreFdInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_GET_FD_INFO_KHR;
    semaphoreFdInfo.semaphore = semaphore;
    semaphoreFdInfo.handleType = VK_EXTERNAL_SEMAPHORE_HANDLE_TYPE_OPAQUE_FD_BIT;

    auto vkGetSemaphoreFdKHR = (PFN_vkGetSemaphoreFdKHR)vkGetDeviceProcAddr(device, "vkGetSemaphoreFdKHR");
    VK_CHECK(vkGetSemaphoreFdKHR(device, &semaphoreFdInfo, &semaphoreFd));

    glGenSemaphoresEXT(1, &glSemaphore);
    glImportSemaphoreFdEXT(glSemaphore, GL_HANDLE_TYPE_OPAQUE_FD_EXT, semaphoreFd);
}

void cleanup(VkDevice device, VkImage image, VkDeviceMemory memory, VkSemaphore semaphore) {
    vkDestroySemaphore(device, semaphore, nullptr);
    vkDestroyImage(device, image, nullptr);
    vkFreeMemory(device, memory, nullptr);
}

