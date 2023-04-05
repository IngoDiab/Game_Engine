#pragma once

#include "engine/Materials/Material.h"

#include <string>
using namespace std;

#define LANDSCAPE_VERTEX "Landscape/Shader/Landscape_vertex.glsl"
#define LANDSCAPE_FRAG "Landscape/Shader/Landscape_frag.glsl"

class LandscapeMaterial : public Material
{
    float mHeightGrassRock = 50;
    float mHeightRockSnow = 80;
    float mTransitionThreshold = 10;
    int mTiling = 20;
    int mMaxHeight = 1;

public:
    void SetHeightmap(const string& _map, const float _maxHeight){LoadTexture(0, _map); mMaxHeight=_maxHeight;}

public:
    LandscapeMaterial();
    LandscapeMaterial(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;
    virtual void UseMaterial(const int _typeTexture, const mat4& _model, const mat4& _view, const mat4& _proj) override;
};