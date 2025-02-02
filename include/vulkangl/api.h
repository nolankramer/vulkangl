
#ifndef VULKANGL_EXPORT_H
#define VULKANGL_EXPORT_H

#ifdef VULKANGL_STATIC_DEFINE
#  define VULKANGL_EXPORT
#  define VULKANGL_NO_EXPORT
#else
#  ifndef VULKANGL_EXPORT
#    ifdef vulkangl_EXPORTS
        /* We are building this library */
#      define VULKANGL_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define VULKANGL_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef VULKANGL_NO_EXPORT
#    define VULKANGL_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef VULKANGL_DEPRECATED
#  define VULKANGL_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef VULKANGL_DEPRECATED_EXPORT
#  define VULKANGL_DEPRECATED_EXPORT VULKANGL_EXPORT VULKANGL_DEPRECATED
#endif

#ifndef VULKANGL_DEPRECATED_NO_EXPORT
#  define VULKANGL_DEPRECATED_NO_EXPORT VULKANGL_NO_EXPORT VULKANGL_DEPRECATED
#endif

/* NOLINTNEXTLINE(readability-avoid-unconditional-preprocessor-if) */
#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VULKANGL_NO_DEPRECATED
#    define VULKANGL_NO_DEPRECATED
#  endif
#endif

#endif /* VULKANGL_EXPORT_H */
