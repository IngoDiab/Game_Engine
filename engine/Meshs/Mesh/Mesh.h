#pragma once

#include <vector>
#include <string>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

#include <assimp/scene.h>

#include "engine/Buffers/VBO/VBO.h"

enum class VERTEX_ATTRIBUTE
{
    VERTEX_POSITION = 0,
    VERTEX_UVS = 1,
    VERTEX_NORMALE = 2,
    VERTEX_INDICES = 3
};

struct Triangle
{
    vector<unsigned int> mIndices = vector<unsigned int>(3);

    Triangle(const vector<unsigned int>& _indices) : mIndices(_indices){}
    Triangle(const unsigned int _indice0, const unsigned int _indice1, const unsigned int _indice2)
    {
        mIndices[0] = _indice0;
        mIndices[1] = _indice1;
        mIndices[2] = _indice2;
    }

    unsigned int operator[](const int _index) { return mIndices[_index]; }
};

class Mesh
{
protected:
    vector<vec3> mPositions = vector<vec3>();
    VBO mPositionVBO = VBO(GL_ARRAY_BUFFER);

    vector<vec2> mUVs = vector<vec2>();
    VBO mUVsVBO = VBO(GL_ARRAY_BUFFER);

    vector<vec3> mNormales = vector<vec3>();
    VBO mNormalVBO = VBO(GL_ARRAY_BUFFER);

    vector<unsigned short> mIndices = vector<unsigned short>();
    VBO mIndicesVBO = VBO(GL_ELEMENT_ARRAY_BUFFER);

    std::vector<Triangle> mTriangles;

public:
    vector<vec3> GetPositionsVertices() const {return mPositions;}
    void SetPositionsVertices(const vector<vec3>& _positions) {mPositions = _positions; RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);}

public:
    Mesh();
    Mesh(const string& _pathMesh);
    virtual ~Mesh();
    Mesh(const vector<vec3>& _positions, const vector<vec2>& _uvs, const vector<unsigned short>& _indices, const std::vector<Triangle>& _triangles);

protected:
    void RefreshVBOData(const VERTEX_ATTRIBUTE _vbo);

    void ClearMeshBuffers();
    virtual void CreateVerticesPositions();
    virtual void CreateVerticesUVs();
    virtual void CreateIndices();
    virtual void CreateVerticesNormales();

public:
    void DrawMesh();

private:
    static vector<Mesh*> CreateMeshLoaded(const aiScene* _aiScene, const aiNode* _node, const aiMatrix4x4& _parentTransformation);
public:
    static vector<Mesh*> LoadMeshAssimp(const string& _pathMesh);


////ASSIMP->GLM////
mat4 static ASSIMP_To_GLM(const aiMatrix4x4& _matrix)
{
    return glm::mat4(
        (double)_matrix.a1, (double)_matrix.b1, (double)_matrix.c1, (double)_matrix.d1,
        (double)_matrix.a2, (double)_matrix.b2, (double)_matrix.c2, (double)_matrix.d2,
        (double)_matrix.a3, (double)_matrix.b3, (double)_matrix.c3, (double)_matrix.d3,
        (double)_matrix.a4, (double)_matrix.b4, (double)_matrix.c4, (double)_matrix.d4
    );
}
};