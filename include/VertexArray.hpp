#pragma once 

#include "VertexBuffer.hpp"


class VertexArray 
{

    private:

        unsigned int m_RendererID; // ID of the buffer

    public:

        VertexArray() noexcept {

            GLCall(glGenVertexArrays(1, &m_RendererID));
            GLCall(glBindVertexArray(m_RendererID));

        }

        ~VertexArray() {

            GLCall(glDeleteVertexArrays(1, &m_RendererID));

        }

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const noexcept {

            Bind(); 
            vb.Bind();
            const auto& elements = layout.GetElements();
            unsigned int offset = 0;
            for (unsigned int i = 0; i < elements.size(); i++)
            {
                const auto& element = elements[i];
                GLCall(glEnableVertexAttribArray(i));
                GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
                offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
            }

        }

        void Bind() const noexcept {

            GLCall(glBindVertexArray(m_RendererID));

        }

        void Unbind() const noexcept {

            GLCall(glBindVertexArray(0));

        }


}; 