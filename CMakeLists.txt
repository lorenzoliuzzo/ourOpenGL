cmake_minimum_required(VERSION 3.20)
project(myApp)

find_package(PkgConfig REQUIRED)

find_package(X11 REQUIRED)
if(NOT X11_FOUND)
    message("ERROR: x11 not found")
endif(NOT X11_FOUND)

find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)

find_package(glfw3 3.3 REQUIRED)
if (NOT GLFW_FOUND)
    message("ERROR: GLFW not found")
endif(NOT GLFW_FOUND)

pkg_search_module(GLFW REQUIRED glfw3)

find_package(glm REQUIRED)
if(NOT GLM_FOUND)
    message("ERROR: GLM not found")
endif(NOT GLM_FOUND)


include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${X11_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/ext)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/test)


add_executable(myApp src/Application.cpp)

target_link_libraries(
    myApp 
        PUBLIC
            ${GLFW_STATIC_LIBRARIES}  
            ${OPENGL_gl_LIBRARY}
            ${GL_LIBRARY}
            ${OPENGL_glu_LIBRARY}
            GLEW m dl Xinerama Xrandr Xi Xcursor pthread
            /usr/lib/x86_64-linux-gnu/libX11.so
            /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1
            ${X11_LIBRARIES}
            glm::glm
            ImGui
)


add_executable(ClearColor src/ClearColor.cpp)

target_link_libraries(
    ClearColor 
        PUBLIC
            ${GLFW_STATIC_LIBRARIES}  
            ${OPENGL_gl_LIBRARY}
            ${GL_LIBRARY}
            ${OPENGL_glu_LIBRARY}
            GLEW m dl Xinerama Xrandr Xi Xcursor pthread
            /usr/lib/x86_64-linux-gnu/libX11.so
            /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1
            ${X11_LIBRARIES}
            glm::glm
            ImGui
)

add_executable(Menu src/Menu.cpp)

target_link_libraries(
    Menu 
        PUBLIC
            ${GLFW_STATIC_LIBRARIES}  
            ${OPENGL_gl_LIBRARY}
            ${GL_LIBRARY}
            ${OPENGL_glu_LIBRARY}
            GLEW m dl Xinerama Xrandr Xi Xcursor pthread
            /usr/lib/x86_64-linux-gnu/libX11.so
            /usr/lib/x86_64-linux-gnu/libXxf86vm.so.1
            ${X11_LIBRARIES}
            glm::glm
            ImGui
)