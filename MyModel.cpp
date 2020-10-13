#include "MyModel.h"

#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
//#include "glm/gtx/string_cast.hpp"


MyModel::MyModel()
    :m_GlobalTranslation(0.0f, 0.0f, 0.0f), m_GlobalRotation(1.0f, 0.0f, 0.0f, 0.0f), m_GlobalScale(1.0f, 1.0f, 1.0f),
     m_LocalTranslation(0.0f, 0.0f, 0.0f), m_LocalRotation(1.0f, 0.0f, 0.0f, 0.0f), m_LocalScale(1.0f, 1.0f, 1.0f)
{
}

MyModel::~MyModel()
{
}

void MyModel::SetScale(float x, float y, float z, Landmark landmark)
{
    if (landmark == GLOBAL){
        m_GlobalScale = glm::vec3(x, y, z); 
    }
    else if (landmark == LOCAL){
        m_LocalScale = glm::vec3(x, y, z);        
    }
}
void MyModel::Scale(float x, float y, float z, Landmark landmark)
{
    if (landmark == GLOBAL){
        m_GlobalScale += glm::vec3(x, y, z); 
    }
    else if (landmark == LOCAL){
        m_LocalScale += glm::vec3(x, y, z);      
    }
}

void MyModel::SetTranslation(float x, float y, float z, Landmark landmark)
{
    if (landmark == GLOBAL){
        m_GlobalTranslation = glm::vec3(x, y, z); 
    }
    else if (landmark == LOCAL){
        m_LocalTranslation = glm::vec3(x, y, z);        
    }
}
void MyModel::Translate(float x, float y, float z, Landmark landmark)
{
    if (landmark == GLOBAL){
        m_GlobalTranslation += glm::vec3(x, y, z); 
    }
    else if (landmark == LOCAL){
        m_LocalTranslation += glm::vec3(x, y, z);      
    }
}

void MyModel::SetRotationEuler(float x, float y, float z, Landmark landmark)
{
    glm::quat quatX(cos(glm::radians(x) / 2), sin(glm::radians(x) / 2), 0, 0);
    glm::quat quatY(cos(glm::radians(y) / 2), 0, sin(glm::radians(y) / 2), 0);
    glm::quat quatZ(cos(glm::radians(z) / 2), 0, 0, sin(glm::radians(z) / 2));

    if (landmark == GLOBAL){
        m_GlobalRotation = quatX * quatY * quatZ; 
    }
    else if (landmark == LOCAL){
        m_LocalRotation = quatX * quatY * quatZ;      
    }
}
void MyModel::RotateEuler(float x, float y, float z, Landmark landmark)
{
    glm::quat quatX(cos(glm::radians(x) / 2), sin(glm::radians(x) / 2), 0, 0);
    glm::quat quatY(cos(glm::radians(y) / 2), sin(glm::radians(y) / 2), 0, 0);
    glm::quat quatZ(cos(glm::radians(z) / 2), sin(glm::radians(z) / 2), 0, 0);

    if (landmark == GLOBAL){
        m_GlobalRotation = m_GlobalRotation * quatX * quatY * quatZ; 
    }
    else if (landmark == LOCAL){
        m_LocalRotation = m_LocalRotation * quatX * quatY * quatZ;      
    }
}

void MyModel::SetRotationQuaternion(float w, float x, float y, float z, Landmark landmark)
{
    if (landmark == GLOBAL){
        m_GlobalRotation = glm::quat(w, x, y, z);
    }
    else if (landmark == LOCAL){
        m_LocalRotation = glm::quat(w, x, y, z);
    }
}
void MyModel::RotateQuaternion(float w, float x, float y, float z, Landmark landmark)
{
    if (landmark == GLOBAL){
        m_GlobalRotation = m_GlobalRotation * glm::quat(w, x, y, z);
    }
    else if (landmark == LOCAL){
        m_LocalRotation = m_LocalRotation * glm::quat(w, x, y, z);
    }
}

MyModel::Vertex* MyModel::GetVertexData()
{
    m_FinalVertices.clear();
    for (Vertex vert : m_Vertices) m_FinalVertices.push_back(vert);

    glm::mat4 scaleGMat = glm::scale(glm::mat4(1.0f), m_GlobalScale);
    glm::mat4 scaleLMat = glm::scale(glm::mat4(1.0f), m_LocalScale);

    glm::vec3 eulerG = glm::eulerAngles(m_GlobalRotation);
    glm::mat4 rotationGMat = glm::eulerAngleXYZ(eulerG.x, eulerG.y, eulerG.z);
    glm::vec3 eulerL = glm::eulerAngles(m_LocalRotation);
    glm::mat4 rotationLMat = glm::eulerAngleXYZ(eulerL.x, eulerL.y, eulerL.z);

    glm::mat4 translationGMat = glm::translate(glm::mat4(1.0f), m_GlobalTranslation);
    glm::mat4 translationLMat = glm::translate(glm::mat4(1.0f), m_LocalTranslation);

    for (Vertex &vert : m_FinalVertices){
        vert.Position = scaleLMat * glm::vec4(vert.Position, 1.0f);
        vert.Position = translationLMat * glm::vec4(vert.Position, 1.0f);
        vert.Position = rotationLMat * glm::vec4(vert.Position, 1.0f);
        vert.Position = translationGMat * glm::vec4(vert.Position, 1.0f);
        vert.Position = scaleGMat * glm::vec4(vert.Position, 1.0f);
        vert.Position = rotationGMat * glm::vec4(vert.Position, 1.0f);

        vert.Normal = rotationLMat * rotationGMat * glm::vec4(vert.Normal, 1.0f);
    }

    return m_FinalVertices.data();
}
unsigned int * MyModel::GetIndicesData()
{
    return m_Tiangles.data();
}

void MyModel::AddVertex(Vertex& vertex)
{
    m_Vertices.push_back(vertex);
}
void MyModel::AddVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords, float texID)
{
    m_Vertices.push_back(Vertex(position, normal, texCoords, texID));
}

void MyModel::AddTriangle(unsigned int indice1, unsigned int indice2, unsigned int indice3)
{
    m_Tiangles.push_back(indice1);
    m_Tiangles.push_back(indice2);
    m_Tiangles.push_back(indice3);
}