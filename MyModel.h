#pragma once

#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"

#include <vector>
#include <iostream>



class MyModel
{
public:
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
        float TexID;

        Vertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords, float texID)
            :Position(position), Normal(normal), TexCoords(texCoords), TexID(texID)
        {
        }
    };

    MyModel();
    ~MyModel();

    void SetTranslation(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void Translate(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    void SetRotationEuler(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void RotateEuler(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    void SetRotationQuaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void RotateQuaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f);

    Vertex* GetVertexData();
    unsigned int * GetIndicesData();

    void AddVertex(Vertex& vertex);
    void AddVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords, float texID);

    void AddTriangle(unsigned int indice1, unsigned int indice2, unsigned int indice3);

    unsigned int GetVertexCount(){ return m_Vertices.size();}
    unsigned int GetTriangleCount(){ return m_Tiangles.size() / 3.0f;}

private:
    glm::vec3 m_Translation;
    glm::quat m_Rotation;
    glm::vec3 m_Scale;

    std::vector<Vertex> m_Vertices;
    std::vector<Vertex> m_FinalVertices;
    std::vector<unsigned int> m_Tiangles;
};
