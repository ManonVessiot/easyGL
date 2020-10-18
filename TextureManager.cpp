#include "TextureManager.h"

namespace easyGL
{
    TextureManager* TextureManager::m_Instance = nullptr;

    Texture* TextureManager::CreateTexture(std::string textureFileName){
        if (m_Textures.find(textureFileName) == m_Textures.end()){
            m_Textures[textureFileName] = new Texture(textureFileName);
        }
        return m_Textures[textureFileName];
    }

} // namespace easyGL