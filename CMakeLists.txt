cmake_minimum_required(VERSION 3.20)
project(Ray_Tracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(Ray_Tracer vec3.cpp vec3.hpp surface.cpp surface.hpp ray.cpp ray.hpp hittable.hpp sphere.cpp sphere.hpp hittable_list.cpp hittable_list.hpp utilities.hpp camera.cpp camera.hpp material.hpp moving_sphere.hpp moving_sphere.cpp main_week2.cpp aabb.cpp aabb.hpp bvh.cpp bvh.hpp texture.hpp perlin.cpp perlin.hpp rtw_stb_image.hpp aarect.cpp aarect.hpp box.cpp box.hpp hittable.cpp constant_medium.hpp constant_medium.cpp)

target_include_directories(Ray_Tracer PRIVATE external)
#target_link_directories(Ray_Tracer PRIVATE "external/SDL2/lib")
#target_link_libraries(Ray_Tracer PRIVATE -Wall -lmingw32 SDL2main SDL2)
