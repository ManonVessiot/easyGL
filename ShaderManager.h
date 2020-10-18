#pragma once

#include <unordered_map>

#include "Shader.h"

namespace easyGL
{
    struct ShaderProgramSource
    {
        std::string VertexSource;
        std::string FragmentSource;
    };

    class ShaderManager
    {
        private:
            static ShaderManager* m_Instance;

            ShaderManager(){ }
            ~ShaderManager(){
                if (m_Instance){
                    delete m_Instance;
                }
                for(std::unordered_map<std::string, Shader*>::iterator i = m_Shaders.begin(); i!=m_Shaders.end(); ++i) {
                    delete i->second;
                }
            }

            std::unordered_map<std::string, Shader*> m_Shaders;

            ShaderProgramSource ParseShader(const std::string& filepath) const;
            
        public:
            static ShaderManager* Instance()
            {
                if (!m_Instance){
                    m_Instance = new ShaderManager();
                }
                return m_Instance;
            }

            Shader* GetSaher(std::string filepath);
            
    };
    
} // namespace easyGL
