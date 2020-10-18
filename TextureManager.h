#pragma once

#include <vector>
#include <unordered_map>

#include "Texture.h"

namespace easyGL
{
    class TextureManager
    {
        private:
            static TextureManager* m_Instance;

            TextureManager(){ }
            ~TextureManager(){
                if (m_Instance){
                    delete m_Instance;
                }
                for ( auto it = m_Textures.begin(); it != m_Textures.end(); ++it ) {
                    delete it->second;
                }
            }

            std::unordered_map<std::string, Texture*> m_Textures;
            
        public:
            static TextureManager* Instance()
            {
                if (!m_Instance){
                    m_Instance = new TextureManager();
                }
                return m_Instance;
            }

            Texture* CreateTexture(std::string textureFileName);
            
    };
    
} // namespace easyGL
