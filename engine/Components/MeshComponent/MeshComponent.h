#pragma once

#include "engine/Components/Component/Component.h"
#include "engine/Utils/Interfaces/IRenderable.h"
#include "engine/Meshs/Mesh/Mesh.h"
#include "engine/Materials/Material.h"

class Camera;

class MeshComponent : public Component, public IRenderable
{
protected:
    Mesh* mMesh = nullptr;
    map<double, Mesh*> mLODS = map<double, Mesh*>();
    Material* mMaterial = nullptr;
    bool mCanBeRendered = true;
public:
    virtual Mesh* GetMesh() override {return mMesh;}
    void SetMesh(Mesh* const _mesh) {mMesh = _mesh;}

    virtual BaseMaterial* GetRendererMaterial() override {return (BaseMaterial*)mMaterial;}
    Material* GetMaterial() {return mMaterial;}
    void SetMaterial(Material* const _material) {mMaterial = _material;}

    virtual bool CanBeRendered() const override {return mCanBeRendered;}
    void SetCanBeRendered(const bool _canBeRendered) {mCanBeRendered = _canBeRendered;}

public:
    virtual ~MeshComponent();

public:
    virtual void ChangeMeshByDistance(Camera* _renderingCamera, float _threshold) override;
    virtual void Render(Camera* _renderingCamera) override;
    virtual void CleanRessources() override;

public:
    template<typename T>
    T* CreateMesh();

    template<typename T>
    T* CreateMesh(const string& _meshPath);

    template<typename T>
    T* AddLOD(double _distanceLOD, int _vertexDim1, int _vertexDim2);

    template<typename T>
    T* CreateMaterial();

    template<typename T>
    T* CreateMaterial(const string& _vertexShader, const string& _fragShader);
};

template<typename T>
T* MeshComponent::CreateMesh()
{
    T* _meshCreated = new T();
    Mesh* _mesh = dynamic_cast<Mesh*>(_mesh);
    if(!_mesh) return nullptr;
    if(mMesh) delete mMesh;
    mMesh = _meshCreated;

    for(pair<double,Mesh*> _pair : mLODS)
    {
        delete _pair.second;
    }
    mLODS.clear();

    mLODS[0] = _meshCreated;
    return _meshCreated;
}

template<typename T>
T* MeshComponent::CreateMesh(const string& _meshPath)
{
    T* _meshCreated = new T(_meshPath);
    Mesh* _mesh = dynamic_cast<Mesh*>(_mesh);
    if(!_mesh) return nullptr;
    if(mMesh) delete mMesh;
    mMesh = _meshCreated;

    for(pair<double,Mesh*> _pair : mLODS)
    {
        delete _pair.second;
    }
    mLODS.clear();

    mLODS[0] = _meshCreated;
    return _meshCreated;
}

template<typename T>
T* MeshComponent::AddLOD(double _distanceLOD, int _vertexDim1, int _vertexDim2)
{
    T* _meshCreated = new T(_vertexDim1, _vertexDim2);
    Mesh* _mesh = dynamic_cast<Mesh*>(_mesh);
    if(!_mesh) return nullptr;
    mLODS[_distanceLOD] = _meshCreated;
    return _meshCreated;
}

template<typename T>
T* MeshComponent::CreateMaterial()
{
    T* _materialCreated = new T();
    BaseMaterial* _material = dynamic_cast<BaseMaterial*>(_materialCreated);
    if(!_material) return nullptr;
    if(mMaterial) delete mMaterial;
    mMaterial = _materialCreated;
    return _materialCreated;
}

template<typename T>
T* MeshComponent::CreateMaterial(const string& _vertexShader, const string& _fragShader)
{
    T* _materialCreated = new T(_vertexShader, _fragShader);
    BaseMaterial* _material = dynamic_cast<BaseMaterial*>(_materialCreated);
    if(!_material) return nullptr;
    if(mMaterial) delete mMaterial;
    mMaterial = _materialCreated;
    return _materialCreated;
}