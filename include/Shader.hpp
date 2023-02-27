/// @file Shader.hpp

#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "Logger.hpp"
#include "glm/glm.hpp"


struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};


/// @brief Shader class
class Shader
{

    private: 

        unsigned int m_RendererID;
        std::unordered_map<std::string, int> m_UniformLocationCache;

    
    public:


        /// @brief Constructor
        /// @param filepath Path to the shader file
        Shader(const std::string& filepath)
        {
            ShaderProgramSource source = ParseShader(filepath);
            m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
        }


        /// @brief Destructor
        ~Shader()
        {
            GLCall(glDeleteProgram(m_RendererID));
        }


        /// @brief Bind the shader
        void Bind() const
        {
            GLCall(glUseProgram(m_RendererID));
        }


        /// @brief Unbind the shader
        void Unbind() const
        {
            GLCall(glUseProgram(0));
        }


        void SetUniform1i(const std::string& name, int value)
        {
            GLCall(glUniform1i(GetUniformLocation(name), value));
        }


        void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
        {
            GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
        }


        void SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
        {
            GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
        }

    private: 

        ShaderProgramSource ParseShader(const std::string& filepath)
        {

            enum class ShaderType
            {
                NONE = -1, VERTEX = 0, FRAGMENT = 1
            };

            std::ifstream stream(filepath);

            std::string line;
            std::stringstream ss[2];
            ShaderType type = ShaderType::NONE;

            while (getline(stream, line))
            {
            
                if (line.find("#shader") != std::string::npos)
                {
                    if (line.find("vertex") != std::string::npos)
                        type = ShaderType::VERTEX;
                    else if (line.find("fragment") != std::string::npos)
                        type = ShaderType::FRAGMENT;
                }
                else
                {
                    ss[(int)type] << line << '\n';
                }

            }

            return { ss[0].str(), ss[1].str() };

        }


        unsigned int CompileShader(unsigned int type, const std::string& source) 
        {
            unsigned int id = glCreateShader(type);
            const char* src = source.c_str();
            glShaderSource(id, 1, &src, nullptr);
            glCompileShader(id);

            int result;
            glGetShaderiv(id, GL_COMPILE_STATUS, &result);
            if (result == GL_FALSE)
            {
                int length;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                char* message = (char*)alloca(length * sizeof(char));
                glGetShaderInfoLog(id, length, &length, message);
                std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
                std::cout << message << std::endl;
                glDeleteShader(id);
                return 0;
            }

            return id;

        }


        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) 
        {
            unsigned int program = glCreateProgram();
            unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
            unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

            glAttachShader(program, vs);
            glAttachShader(program, fs);
            glLinkProgram(program);
            glValidateProgram(program);

            glDeleteShader(vs);
            glDeleteShader(fs);

            return program;
        }


        int GetUniformLocation(const std::string& name)
        {
            if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
                return m_UniformLocationCache[name];

            GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
            if (location == -1)
                std::cerr << "Warning: uniform '" << name << "' doesn't exist!";

            m_UniformLocationCache[name] = location; 
            return location; 
        }
        

}; // class Shader