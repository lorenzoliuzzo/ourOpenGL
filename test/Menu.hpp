#pragma once 


#include "Test.hpp"
#include "Logger.hpp"
#include "imgui/imgui.h"
#include <functional>
#include <memory>
#include <vector>
#include <string>


namespace test
{


    class TestMenu : public Test
    {

        private:

            std::shared_ptr<Test>& m_CurrentTest;
            std::vector<std::pair<std::string, std::function<std::shared_ptr<Test>()>>> m_Tests;


        public:

            TestMenu(std::shared_ptr<Test>& currentTestPointer) : m_CurrentTest(currentTestPointer) {}

            virtual void OnUpdate(float deltaTime) override {}

            virtual void OnRender() {}

            virtual void OnImGuiRender() override 
            {
                for (auto& test : m_Tests)
                    if (ImGui::Button(test.first.c_str()))
                        m_CurrentTest = test.second();
            }


            template <typename T>
            void RegisterTest(const std::string& name)
            {
                m_Tests.push_back(std::make_pair(name, []() { return std::make_shared<T>(); }));
            }


    }; // class TestMenu


} // namespace Test