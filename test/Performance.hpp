#pragma once

#include "Test.hpp"
#include "Logger.hpp"
#include "imgui/imgui.h"


namespace test
{

    
    class Performance : public Test
    {

        public:

            Performance() {}

            ~Performance() {}


            void OnUpdate(float deltaTime) {}


            void OnRender() {}


            void OnImGuiRender() override 
            {
                ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            }


    }; // class Performance


} // namespace test