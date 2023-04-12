#include "SkyboxMaterial.h"
#include "engine/Skyboxes/ShaderHandler/SkyboxShaderHandler.h"
#include <iostream>
using namespace std;

SkyboxMaterial::SkyboxMaterial(){}

SkyboxMaterial::SkyboxMaterial(const string& _vertexShader, const string& _fragShader)
{
    mShaderHandler = new SkyboxShaderHandler(_vertexShader, _fragShader);
    mShaderHandler->Initialize();
    mShader = mShaderHandler;
}

void SkyboxMaterial::UseMaterial(const int _typeTexture, const mat4& _model, const mat4& _view, const mat4& _proj)
{
    glm::mat4 _viewSkybox = glm::mat4(glm::mat3(_view)); 
    BaseMaterial::UseMaterial(_typeTexture, _model, _viewSkybox, _proj);

    mShaderHandler->SendTexture(_typeTexture, 0, mCubemap, mShaderHandler->GetCubemapHandler());
}

void SkyboxMaterial::ChangeSkyboxTextures(const string _path, const string _format)
{
    if(_path == "" || _format == "") return;
    vector<string> _texturesCubemapPaths
    {
        _path + "right" + _format,
        _path + "left" + _format,
        _path + "top" + _format,
        _path + "bottom" + _format,
        _path + "front" + _format,
        _path + "back" + _format,
    };
    LoadCubemapTexture(_texturesCubemapPaths);
}

void SkyboxMaterial::LoadCubemapTexture(const vector<string>& _texturePaths)
{
    DeleteTexture(mCubemap);
    mCubemap = loadTextureCubeMap2DFromFilePath(_texturePaths);
}