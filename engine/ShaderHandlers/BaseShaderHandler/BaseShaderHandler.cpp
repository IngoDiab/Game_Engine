#include "BaseShaderHandler.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <common/shader.hpp>
#include "engine/ShaderHandlers/ShaderManager/ShaderManager.h"

BaseShaderHandler::BaseShaderHandler(const string& _vertexShader, const string& _fragShader)
{
    mShaderHandler = ShaderManager::Instance()->LoadShader(ShaderInfo(_vertexShader, _fragShader));
}

void BaseShaderHandler::Initialize()
{
    mModelHandler = glGetUniformLocation(mShaderHandler, "model");
    mViewHandler = glGetUniformLocation(mShaderHandler, "view");
    mProjectionHandler = glGetUniformLocation(mShaderHandler, "projection");
}

void BaseShaderHandler::SendMVP(const mat4& _model, const mat4& _view, const mat4& _proj)
{
    glUniformMatrix4fv(mModelHandler, 1, GL_FALSE, &_model[0][0]);
    glUniformMatrix4fv(mViewHandler, 1, GL_FALSE, &_view[0][0]);
    glUniformMatrix4fv(mProjectionHandler, 1, GL_FALSE, &_proj[0][0]);
}

void BaseShaderHandler::SendTexture(int _typeTexture, int _offsetSlot, unsigned int _texture, int _handler)
{
    if(_handler == -1 || _texture == 0)return;
    glActiveTexture(GL_TEXTURE0 + _offsetSlot);
    glBindTexture(_typeTexture, _texture);
    glUniform1i(_handler, _offsetSlot);
}

void BaseShaderHandler::GetTextureLocation(int& _slotTexture, const string& _nameLocation)
{
    _slotTexture = glGetUniformLocation(mShaderHandler, _nameLocation.c_str());
}

void BaseShaderHandler::GetUniformLocation(int& _slotUniform, const string& _nameLocation)
{
    _slotUniform = glGetUniformLocation(mShaderHandler, _nameLocation.c_str());
}

void BaseShaderHandler::SendFloat(float _value, int _handler)
{
    if(_handler == -1) return;
    glUniform1f(_handler, _value);
}

void BaseShaderHandler::SendInt(int _value, int _handler)
{
    if(_handler == -1) return;
    glUniform1i(_handler, _value);
}

void BaseShaderHandler::SendVec3(vec3 _value, int _handler)
{
    if(_handler == -1) return;
    glUniform3fv(_handler, 1, value_ptr(_value));
}