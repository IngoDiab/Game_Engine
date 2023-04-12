#include "MeshComponent.h"

#include <limits>
#include <iostream>
using namespace std;

#include "engine/Meshs/Mesh/Mesh.h"
#include "engine/Materials/Material.h"
#include "engine/ShaderHandlers/ShaderHandler/ShaderHandler.h"
#include "engine/Camera/Camera/Camera.h"

MeshComponent::~MeshComponent()
{
    CleanRessources();
}

void MeshComponent::ChangeMeshByDistance(Camera* _renderingCamera, float _threshold)
{
    double _distanceCamera = length(_renderingCamera->GetWorldPosition()-mTransform.GetTransformData()->mWorldPosition);
    for(pair<double,Mesh*> _pair : mLODS)
    {
        double _distanceRequired = _pair.first;
        if(_distanceRequired+_threshold >= _distanceCamera) return;
        mMesh = _pair.second;
    }
}

void MeshComponent::Render(Camera* _renderingCamera)
{
    //Calculate MVP
    const mat4& _modelMatrix = mTransform.GetModelMatrix();
    const mat4& _viewMatrix = _renderingCamera->GetViewMatrix();
    const mat4& _projMatrix = _renderingCamera->GetProjectionMatrix();

    //Use Material
    glUseProgram(mMaterial->GetShader()->GetShaderHandler());
    mMaterial->UseMaterial(GL_TEXTURE_2D, _modelMatrix, _viewMatrix, _projMatrix);

    //Draw
    ChangeMeshByDistance(_renderingCamera, 25);
    mMesh->DrawMesh();
}

void MeshComponent::CleanRessources()
{
    delete mMesh;
    delete mMaterial;
}