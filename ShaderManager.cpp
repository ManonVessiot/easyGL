#include "ShaderManager.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

namespace easyGL
{
    ShaderManager* ShaderManager::m_Instance = nullptr;

    ShaderProgramSource ShaderManager::ParseShader(const std::string& filepath) const{
        std::ifstream stream(filepath);

        enum class ShaderType{
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };
        
        std::string line;
        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;
        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos){
                if (line.find("vertex") != std::string::npos){
                    type = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos){
                    type = ShaderType::FRAGMENT;
                }
            }
            else if ((int)type != -1)
            {                
                ss[(int)type] << line << "\n";
            }        
        }
        return {ss[0].str(), ss[1].str()};
    }

    Shader* ShaderManager::GetSaher(std::string filepath){
        if (m_Shaders.find(filepath) == m_Shaders.end())
        {
            ShaderProgramSource source = ParseShader(filepath);
            m_Shaders[filepath] = new Shader(source.VertexSource, source.FragmentSource);
        }
        return m_Shaders[filepath];
    }

} // namespace easyGL