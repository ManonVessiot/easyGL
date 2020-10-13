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

    enum Landmark{
        LOCAL = 0,
        GLOBAL = 1
    };

    MyModel();
    ~MyModel();

    void SetTranslation(float x = 0.0f, float y = 0.0f, float z = 0.0f, Landmark landmark = GLOBAL);
    void Translate(float x = 0.0f, float y = 0.0f, float z = 0.0f, Landmark landmark = GLOBAL);

    void SetRotationEuler(float x = 0.0f, float y = 0.0f, float z = 0.0f, Landmark landmark = GLOBAL);
    void RotateEuler(float x = 0.0f, float y = 0.0f, float z = 0.0f, Landmark landmark = GLOBAL);

    void SetRotationQuaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f, Landmark landmark = GLOBAL);
    void RotateQuaternion(float w = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f, Landmark landmark = GLOBAL);

    Vertex* GetVertexData();
    unsigned int * GetIndicesData();

    void AddVertex(Vertex& vertex);
    void AddVertex(glm::vec3 position, glm::vec3 normal, glm::vec2 texCoords, float texID);

    void AddTriangle(unsigned int indice1, unsigned int indice2, unsigned int indice3);

    unsigned int GetVertexCount(){ return m_Vertices.size();}
    unsigned int GetTriangleCount(){ return m_Tiangles.size() / 3.0f;}

private:
    glm::vec3 m_LocalTranslation;
    glm::quat m_LocalRotation;
    glm::vec3 m_LocalScale;

    glm::vec3 m_GlobalTranslation;
    glm::quat m_GlobalRotation;
    glm::vec3 m_GlobalScale;

    std::vector<Vertex> m_Vertices;
    std::vector<Vertex> m_FinalVertices;
    std::vector<unsigned int> m_Tiangles;
};
