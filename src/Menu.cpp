#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "Logger.hpp"
#include "Renderer.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Menu.hpp"
#include "ClearColor.hpp"
#include "ButtonCounter.hpp"
#include "Performance.hpp"


int main(void)
{
    
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(960, 540, "Hello OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cerr << "Error! Cannot initialize GLEW" << std::endl;

    GLCall(glEnable(GL_BLEND)); 
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    Renderer renderer;

    IMGUI_CHECKVERSION(); 
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    std::shared_ptr<test::Test> current_test;
    std::shared_ptr<test::TestMenu> test_menu = std::make_shared<test::TestMenu>(current_test);
    current_test = test_menu;

    test_menu->RegisterTest<test::ClearColor>("Clear Color");
    test_menu->RegisterTest<test::ButtonCounter>("Button-Counter");
    test_menu->RegisterTest<test::Performance>("Performance");


    while (!glfwWindowShouldClose(window))
    {

        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (current_test)
        {
            current_test->OnUpdate(0.0f);
            current_test->OnRender();
            ImGui::Begin("Test");

            if (current_test != test_menu && ImGui::Button("<-")) 
                current_test = test_menu;

            current_test->OnImGuiRender();
            ImGui::End();
        }
         
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    return 0;
    
}