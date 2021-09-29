#ifndef RAY_TRACER_RTW_STB_IMAGE_HPP
#define RAY_TRACER_RTW_STB_IMAGE_HPP

// Disable pedantic warnings for this external library.
#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
#pragma warning (push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION

#include "external/stb_image.h"
#include "external/stb_image_write.h"

// Restore warning levels.
#ifdef _MSC_VER
// Microsoft Visual C++ Compiler
#pragma warning (pop)
#endif

#endif


// TODO: refactor stb_image usages to go through this header file and implement textures 6.1