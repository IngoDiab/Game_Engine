#include "Mesh.h"

#include <assimp/Importer.hpp> 
#include <assimp/postprocess.h> 

#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_FLOAT 0x1406
#define GL_TRIANGLES 0x0004

Mesh::Mesh()
{
    //Fix ?
    mPositions = vector<vec3>();
    mPositionVBO = VBO(GL_ARRAY_BUFFER);

    mUVs = vector<vec2>();
    mUVsVBO = VBO(GL_ARRAY_BUFFER);

    mNormales = vector<vec3>();
    mNormalVBO = VBO(GL_ARRAY_BUFFER);

    mIndices = vector<unsigned short>();
    mIndicesVBO = VBO(GL_ELEMENT_ARRAY_BUFFER);
}

Mesh::Mesh(const string& _pathMesh)
{
    //Fix ?
    mPositions = vector<vec3>();
    mPositionVBO = VBO(GL_ARRAY_BUFFER);

    mUVs = vector<vec2>();
    mUVsVBO = VBO(GL_ARRAY_BUFFER);

    mNormales = vector<vec3>();
    mNormalVBO = VBO(GL_ARRAY_BUFFER);

    mIndices = vector<unsigned short>();
    mIndicesVBO = VBO(GL_ELEMENT_ARRAY_BUFFER);
    
    LoadMeshAssimp(_pathMesh);
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_UVS);
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_NORMALE);
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_INDICES);
}

Mesh::~Mesh()
{
    
}

Mesh::Mesh(const vector<vec3>& _positions, const vector<vec2>& _uvs, const vector<unsigned short>& _indices, const std::vector<Triangle>& _triangles) : mPositions(_positions), mUVs(_uvs), mIndices(_indices), mTriangles(_triangles)
{
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_UVS);
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_NORMALE);
    RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_INDICES);
}

void Mesh::RefreshVBOData(const VERTEX_ATTRIBUTE _vbo)
{
    switch (_vbo)
    {
    case VERTEX_ATTRIBUTE::VERTEX_POSITION:
        mPositionVBO.CopyDataToVBO(mPositions);
        break;

    case VERTEX_ATTRIBUTE::VERTEX_UVS:
        mUVsVBO.CopyDataToVBO(mUVs);
        break;

    case VERTEX_ATTRIBUTE::VERTEX_NORMALE:
        mNormalVBO.CopyDataToVBO(mNormales);

    case VERTEX_ATTRIBUTE::VERTEX_INDICES:
        mIndicesVBO.CopyDataToVBO(mIndices);
        break;
    
    default:
        break;
    }
}

void Mesh::ClearMeshBuffers()
{
    mPositions.clear();
    mUVs.clear();
    mNormales.clear();
    mIndices.clear();
}

void Mesh::CreateVerticesPositions()
{

}

void Mesh::CreateVerticesUVs()
{

}

void Mesh::CreateIndices()
{

}


void Mesh::CreateVerticesNormales()
{
    
}

void Mesh::DrawMesh()
{
    mPositionVBO.DrawVBO(0, 3, GL_FLOAT);
    mUVsVBO.DrawVBO(1, 2, GL_FLOAT);
    mNormalVBO.DrawVBO(2, 3, GL_FLOAT);
    mIndicesVBO.DrawVBOIndices(GL_TRIANGLES, mIndices.size());
}

void Mesh::CreateMeshLoaded(aiMesh* _loadedMesh)
{
    unsigned int _nbVertices = _loadedMesh->mNumVertices;
    for(unsigned int i = 0; i<_nbVertices; ++i)
    {
        aiVector3D _position = _loadedMesh->mVertices[i];
        mPositions.push_back(vec3(_position.x,_position.y,_position.z));

        aiVector3D _uv = _loadedMesh->mTextureCoords[0][i];
        mUVs.push_back(vec2(_uv.x,_uv.y));

        aiVector3D _normal = _loadedMesh->mNormals[i];
        mNormales.push_back(vec3(_normal.x,_normal.y,_normal.z));
    }

    unsigned int _nbTriangles = _loadedMesh->mNumFaces;
    for(unsigned int i = 0; i<_nbTriangles; ++i)
    {
        aiFace _triangle = _loadedMesh->mFaces[i];
		for (unsigned int j = 0; j < 3; j++) {
			mIndices.push_back(_triangle.mIndices[j]);
		}
    }
}

//Issue if pathMesh is more than one mesh (merge all meshs in one)
void Mesh::LoadMeshAssimp(const string& _pathMesh)
{
    Assimp::Importer _importer;
    const aiScene* _aiScene = _importer.ReadFile(_pathMesh.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
    if(!_aiScene || !_aiScene->HasMeshes()) return;

    ClearMeshBuffers();
    unsigned int _nbMeshs = _aiScene->mNumMeshes;
    for(unsigned int i = 0; i<_nbMeshs; ++i)
        CreateMeshLoaded(_aiScene->mMeshes[i]);
}