#pragma once

#include "Test.hpp"
#include "imgui/imgui.h"


namespace test
{

    
    class ButtonCounter : public Test
    {
        
        private: 
        
            int counter = 0;
            

        public:

            ButtonCounter() {}

            ~ButtonCounter() {}


            void OnUpdate(float deltaTime) {}


            void OnRender() {}


            void OnImGuiRender() override 
            {
                if (ImGui::Button("Button"))
                    counter++;

                ImGui::SameLine();
                ImGui::Text("counter = %d", counter);
            }


    }; // class ButtonCounter


} // namespace test