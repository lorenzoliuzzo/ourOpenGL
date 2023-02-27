#pragma once

#include "Logger.hpp"


class IndexBuffer
{

    private:

        unsigned int m_RendererID; // ID of the buffer
        unsigned int m_Count; // Number of indices

    public:

        IndexBuffer(const unsigned int* data, unsigned int count) noexcept : m_Count(count) {

            GLCall(glGenBuffers(1, &m_RendererID));
            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
            GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));

        }

        ~IndexBuffer() {

            GLCall(glDeleteBuffers(1, &m_RendererID));
            
        }

        void Bind() const noexcept {

            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));

        }

        void Unbind() const noexcept {

            GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
            
        }

        inline unsigned int GetCount() const noexcept { return m_Count; }


};