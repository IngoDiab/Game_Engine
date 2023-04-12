#include "BaseMaterial.h"
#include "engine/ShaderHandlers/BaseShaderHandler/BaseShaderHandler.h"

void BaseMaterial::DeleteTexture(unsigned int& _texture)
{
    if(!glIsTexture(_texture)) return;
    glDeleteTextures(1, &_texture);
}

void BaseMaterial::UseMaterial(const int _typeTexture, const mat4& _model, const mat4& _view, const mat4& _proj)
{
    mShader->SendMVP(_model, _view, _proj);
}

void BaseMaterial::LoadTexture(unsigned int& _textureSlot, const string& _texturePath)
{
    DeleteTexture(_textureSlot);
    _textureSlot = loadTexture2DFromFilePath(_texturePath);
}