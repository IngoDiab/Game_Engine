#include "LandscapeMaterial.h"
#include "engine/Landscape/ShaderHandler/LandscapeShaderHandler.h"

LandscapeMaterial::LandscapeMaterial(){}

LandscapeMaterial::LandscapeMaterial(const string& _vertexShader, const string& _fragShader)
{
    LandscapeShaderHandler* _shaderHandler = new LandscapeShaderHandler(_vertexShader, _fragShader);
    _shaderHandler->Initialize();
    SetShader(_shaderHandler);
}

void LandscapeMaterial::Initialize()
{
    LoadTexture(0, "Textures/2D/grass.png");
    LoadTexture(1, "Textures/2D/rock.png");
    LoadTexture(2, "Textures/2D/snowrocks.png");
}