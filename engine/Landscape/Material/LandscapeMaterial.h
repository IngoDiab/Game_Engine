#pragma once

#include "engine/Materials/Material.h"

#include <string>
using namespace std;

class LandscapeMaterial : public Material
{

public:
    LandscapeMaterial();
    LandscapeMaterial(const string& _vertexShader, const string& _fragShader);

public:
    virtual void Initialize() override;
};