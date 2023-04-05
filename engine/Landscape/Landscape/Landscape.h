#pragma once
#include "engine/Objects/GameObject/GameObject.h"

#include <string>
using namespace std;

class LandscapeMesh;
class LandscapeMaterial;
class MeshComponent;

class Landscape : public GameObject
{
    MeshComponent* mMeshComponent = nullptr;
    LandscapeMesh* mMeshRef= nullptr;
    LandscapeMaterial* mMaterialRef = nullptr;

    unsigned char* mHeightmap = nullptr;
    int mWidthImage = 0;
	int mHeightImage = 0;
    float mMaxHeight = 1;

    bool mCanRotate = false;
    float mRotateSpeed = 1;


public:
    virtual void SetScale(const vec3& _scale) override {mTransform.GetTransformData()->mLocalScale = vec3(_scale.x, 1, _scale.z);}

    bool CanRotate() const {return mCanRotate;}
    void SetCanRotate(const bool _canRotate) {mCanRotate = _canRotate;}
    void ToggleRotation(const bool _toggle) {if(_toggle) mCanRotate = !mCanRotate;}

    float GetRotationSpeed() const {return mRotateSpeed;}
    void SetRotationSpeed(const float _speed) {mRotateSpeed = _speed;}
    void ChangeSpeed(const float _change) {if(mCanRotate) mRotateSpeed += _change;}

public:
    Landscape();

public:
    virtual void Update(const float _deltaTime) override;

public:
    void ApplyHeightmap(const string& _heightmapPath, const float _maxHeight);
    void ChangeResolution(const int _nbVertexWidth, const int _nbVertexLength);

    void IncreaseResolution(const bool _increase);
    void DecreaseResolution(const bool _decrease);
    
    bool InTriangle(vec3 _point, vec3 _v0, vec3 _v1, vec3 _v2, float& _u0, float& _u1, float& _u2);
    void GetProjectionOnPlane(vec3& _pointToProject);
    vec2 UV(const vec3& _posOnPlan, const vec3& _uVector, const vec3& _vVector);
    double TexelByUV(const vec2& _uv);

private:
    void RotateLandscape();
};