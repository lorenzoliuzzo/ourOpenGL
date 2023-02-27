#pragma once

#include "Test.hpp"
#include "ClearColor.hpp"

#include "imgui/imgui.h"

#include "Logger.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Renderer.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <memory>


namespace test
{

    
    class Texture2D : public Test
    {

        private: 

            std::unique_ptr<VertexArray> m_VertexArray;
            std::unique_ptr<VertexBuffer> m_VertexBuffer;
            std::unique_ptr<IndexBuffer> m_IndexBuffer;
            std::unique_ptr<Shader> m_Shader;
            std::unique_ptr<Texture> m_Texture;
        
            glm::mat4 m_Proj, m_View; 
            glm::vec3 translation = glm::vec3(200.0f, 200.0f, 0.0f);


        public:

            Texture2D() : 
            
                m_Proj(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
                m_View(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))

            {

                float positions[] = {
                    -50.0f, -50.0f, 0.0f, 0.0f,
                    50.0f, -50.0f, 1.0f, 0.0f,
                    50.0f,  50.0f, 1.0f, 1.0f,
                    -50.0f,  50.0f, 0.0f, 1.0f
                };

                unsigned int indices[] = {
                    0, 1, 2,
                    2, 3, 0
                };

                GLCall(glEnable(GL_BLEND)); 
                GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


                m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));

                VertexBufferLayout layout;

                layout.Push(GL_FLOAT, 2);
                layout.Push(GL_FLOAT, 2);

                m_VertexArray = std::make_unique<VertexArray>();
                m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

                m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

                m_Shader = std::make_unique<Shader>("res/shaders/basic.shader"); 
                m_shader->Bind();

                m_Texture = std::make_unique<Texture>("res/textures/black_hole.png");
                m_Texture->Bind();
                m_Shader->SetUniform1i("u_Texture", 0);

                m_VertexArray->Unbind();
                vb.Unbind();
                m_IndexBuffer->Unbind();
                m_Shader->Unbind();

            }

            ~Texture2D() {}


            void OnUpdate(float deltaTime) {}


            void OnRender() override 
            {
                GLCall(glTexture2D(0.0f, 0.0f, 0.0f, 1.0f));
                GLCall(glClear(GL_COLOR_BUFFER_BIT));

                Renderer renderer;
                m_Texture->Bind();
    
                {
                    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation);
                    glm::mat4 mvp = m_Proj * m_View * model;
                    m_Shader->Bind();
                    m_Shader->SetUniform4f("u_Color", f, 0.3f, 0.8f, 1.0f);
                    m_Shader->SetUniformMat4f("u_MVP", mvp);
                    renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
                }
                {
                    glm::mat4 model = glm::translate(glm::mat4(1.0f), translation + glm::vec3(200.0f, 0.0f, 0.0f));
                    glm::mat4 mvp = m_Proj * m_View * model;
                    m_Shader->Bind();
                    m_Shader->SetUniformMat4f("u_MVP", mvp);
                    renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
                }
            }


            void OnImGuiRender() {}

    }; // class Texture2D


} // namespace test