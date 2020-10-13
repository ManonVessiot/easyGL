#include "MyModel.h"

#include "glm/gtx/euler_angles.hpp"
#include "glm/gtx/quaternion.hpp"
//#include "glm/gtx/string_cast.hpp"


MyModel::MyModel()
    :m_Translation(0.0f, 0.0f, 0.0f), m_Rotation(1.0f, 0.0f, 0.0f, 0.0f), m_Scale(1.0f, 1.0f, 1.0f)
{
}

MyModel::~MyModel()
{
}

void MyModel::SetScale(float x, float y, float z)
{
    m_Scale = glm::vec3(x, y, z); 
}
void MyModel::Scale(float x, float y, float z)
{
    m_Scale += glm::vec3(x, y, z); 
}

void MyModel::SetTranslation(float x, float y, float z)
{
    m_Translation = glm::vec3(x, y, z); 
}
void MyModel::Translate(float x, float y, float z)
{
    m_Translation += glm::vec3(x, y, z); 
}

void MyModel::SetRotationEuler(float x, float y, float z)
{
    glm::quat quatX(cos(glm::radians(x) / 2), sin(glm::radians(x) / 2), 0, 0);
    glm::quat quatY(cos(glm::radians(y) / 2), 0, sin(glm::radians(y) / 2), 0);
    glm::quat quatZ(cos(glm::radians(z) / 2), 0, 0, sin(glm::radians(z) / 2));

    m_Rotation = quatX * quatY * quatZ; 
}
void MyModel::RotateEuler(float x, float y, float z)
{
    glm::quat quatX(cos(glm::radians(x) / 2), sin(glm::radians(x) / 2), 0, 0);
    glm::quat quatY(cos(glm::radians(y) / 2), sin(glm::radians(y) / 2), 0, 0);
    glm::quat quatZ(cos(glm::radians(z) / 2), sin(glm::radians(z) / 2), 0, 0);

    m_Rotation = m_Rotation * quatX * quatY * quatZ;
}

void MyModel::SetRotationQuaternion(float w, float x, float y, float z)
{
    m_Rotation = glm::quat(w, x, y, z);
}
void MyModel::RotateQuaternion(float w, float x, float y, float z)
{
    m_Rotation = m_Rotation * glm::quat(w, x, y, z);
}

MyModel::Vertex* MyModel::GetVertexData()
{
    m_FinalVertices.clear();
    for (Vertex vert : m_Vertices) m_FinalVertices.push_back(vert);

    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), m_Scale);

    glm::vec3 eulerG = glm::eulerAngles(m_Rotation);
    glm::mat4 rotationMat = glm::eulerAngleXYZ(eulerG.x, eulerG.y, eulerG.z);

    glm::mat4 translationMat = glm::translate(glm::mat4(1.0f), m_Translation);

    glm::mat4 transform = translationMat * rotationMat * scaleMat;
    for (Vertex &vert : m_FinalVertices){
        vert.Position = transform * glm::vec4(vert.Position, 1.0f);
        vert.Normal = rotationMat * glm::vec4(vert.Normal, 1.0f);
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