cmake_minimum_required(VERSION 3.20)
project(ImGui)

set(CMAKE_CXX_STANDARD 20)

set(FILES 
    imgui.cpp
    imgui.h
    imgui_demo.cpp
    imgui_draw.cpp
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
    imconfig.h
    imstb_rectpack.h
    imstb_textedit.h
    imstb_truetype.h
    imgui_impl_glfw.cpp
    imgui_impl_glfw.h
    imgui_impl_opengl3.cpp
    imgui_impl_opengl3.h
)

add_library(ImGui STATIC ${FILES})

install(
    TARGETS ImGui 
    LIBRARY DESTINATION lib
    RESOURCE DESTINATION include
)