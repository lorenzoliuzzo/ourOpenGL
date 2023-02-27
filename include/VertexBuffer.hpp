#pragma once

#include <vector>
#include "Logger.hpp"


struct VertexBufferElement
{

    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }

        ASSERT(false);
        return 0;
    }

};


struct VertexBufferLayout 
{

    private:
    
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;

    public:

        VertexBufferLayout() : m_Stride(0) {}

        void Push(unsigned int type, unsigned int count)
        {
            if (type == GL_UNSIGNED_BYTE)
                m_Elements.push_back({ type, count, GL_TRUE });
            else
                m_Elements.push_back({ type, count, GL_FALSE });

            m_Stride += count * VertexBufferElement::GetSizeOfType(type);

        }

        inline const std::vector<VertexBufferElement>& GetElements() const noexcept { return m_Elements; }
        
        inline unsigned int GetStride() const noexcept { return m_Stride; }


}; 


class VertexBuffer
{

    private:

        unsigned int m_RendererID; // ID of the buffer

    public:

        VertexBuffer(const void* data, unsigned int size) noexcept {

            GLCall(glGenBuffers(1, &m_RendererID));
            GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
            GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));

        }

        ~VertexBuffer() {

            GLCall(glDeleteBuffers(1, &m_RendererID));

        }

        void Bind() const noexcept {

            GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));

        }

        void Unbind() const noexcept {

            GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
            
        }

        
};