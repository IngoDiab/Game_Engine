#include "LandscapeShaderHandler.h"
#include <GL/glew.h>

LandscapeShaderHandler::LandscapeShaderHandler(const string& _vertexShader, const string& _fragShader) : ShaderHandler(_vertexShader,_fragShader)
{

}

void LandscapeShaderHandler::Initialize()
{
    ShaderHandler::Initialize();
    GetTextureLocation(0, "mHeightmap");
    GetTextureLocation(1, "mGrassTex");
    GetTextureLocation(2, "mRockTex");
    GetTextureLocation(3, "mSnowrockTex");

    GetNumericalLocation("mHeightGrassRock");
    GetNumericalLocation("mHeightRockSnow");
    GetNumericalLocation("mTransitionThreshold");
    GetNumericalLocation("mTiling");
    GetNumericalLocation("mMaxHeight");
}
