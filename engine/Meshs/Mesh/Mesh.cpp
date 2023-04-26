#include "Mesh.h"

#include <assimp/Importer.hpp> 
#include <assimp/postprocess.h> 

#define GL_ARRAY_BUFFER 0x8892
#define GL_ELEMENT_ARRAY_BUFFER 0x8893
#define GL_FLOAT 0x1406
#define GL_TRIANGLES 0x0004

Mesh::Mesh()
{

}

Mesh::Mesh(const string& _pathMesh)
{
    LoadMeshAssimp(_pathMesh);
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

vector<Mesh*> Mesh::CreateMeshLoaded(const aiScene* _aiScene, const aiNode* _node, const aiMatrix4x4& _parentTransformation)
{
    unsigned int* _meshesInNode =_node->mMeshes;
    unsigned int _nbMeshesInNode =_node->mNumMeshes;
    vector<Mesh*> _meshes = vector<Mesh*>();
    aiMatrix4x4 _localTransformationASSIMP = _node->mTransformation * _parentTransformation;
    mat4 _localTransformationGLM = ASSIMP_To_GLM(_localTransformationASSIMP);

    for(unsigned int i = 0; i<_nbMeshesInNode; ++i)
    {
        Mesh* _mesh = new Mesh();
        _mesh->ClearMeshBuffers();

        aiMesh* _loadedMesh = _aiScene->mMeshes[_meshesInNode[i]];

        unsigned int _nbVertices = _loadedMesh->mNumVertices;
        for(unsigned int i = 0; i<_nbVertices; ++i)
        {
            aiVector3D _position = _loadedMesh->mVertices[i];
            vec4 _positionV4 = _localTransformationGLM * vec4(_position.x,_position.y,_position.z,1);
            _mesh->mPositions.push_back(vec3(_positionV4.x,_positionV4.y,_positionV4.z));

            aiVector3D _uv = _loadedMesh->mTextureCoords[0][i];
            _mesh->mUVs.push_back(vec2(_uv.x,_uv.y));

            aiVector3D _normal = _loadedMesh->mNormals[i];
            _mesh->mNormales.push_back(vec3(_normal.x,_normal.y,_normal.z));
        }

        unsigned int _nbTriangles = _loadedMesh->mNumFaces;
        for(unsigned int i = 0; i<_nbTriangles; ++i)
        {
            aiFace _triangle = _loadedMesh->mFaces[i];
            for (unsigned int j = 0; j < 3; j++) {
                _mesh->mIndices.push_back(_triangle.mIndices[j]);
            }
        }

        _mesh->RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_POSITION);
        _mesh->RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_UVS);
        _mesh->RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_NORMALE);
        _mesh->RefreshVBOData(VERTEX_ATTRIBUTE::VERTEX_INDICES);

        _meshes.push_back(_mesh);
    }
    
    aiNode** _nodeChildren = _node->mChildren;
    unsigned int _nbNodeChildren = _node->mNumChildren;
    for(unsigned int i = 0; i<_nbNodeChildren; ++i)
    {
        vector<Mesh*> _childrenMeshes = CreateMeshLoaded(_aiScene, _nodeChildren[i], _localTransformationASSIMP);
        _meshes.insert(_meshes.end(), _childrenMeshes.begin(), _childrenMeshes.end());
    }

    return _meshes;
}

//Issue if pathMesh is more than one mesh (merge all meshs in one)
vector<Mesh*> Mesh::LoadMeshAssimp(const string& _pathMesh)
{
    vector<Mesh*> _meshs = vector<Mesh*>();

    Assimp::Importer _importer;
    const aiScene* _aiScene = _importer.ReadFile(_pathMesh.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
    if(!_aiScene || !_aiScene->HasMeshes()) return _meshs;

    _meshs = CreateMeshLoaded(_aiScene, _aiScene->mRootNode, aiMatrix4x4());
    
    return _meshs;
}