#pragma once

#include "Test.hpp"
#include "Logger.hpp"
#include "imgui/imgui.h"


namespace test
{

    
    class ClearColor : public Test
    {

        private: 
        
            float m_ClearColor[4];


        public:

            ClearColor() : m_ClearColor{ 0.2f, 0.3f, 0.8f, 1.0f } {}

            ~ClearColor() {}


            void OnUpdate(float deltaTime) {}


            void OnRender() override 
            {
                GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
                GLCall(glClear(GL_COLOR_BUFFER_BIT));
            }


            void OnImGuiRender() override 
            {
                ImGui::ColorEdit4("Clear Color", m_ClearColor);
            }


    }; // class ClearColor


} // namespace test