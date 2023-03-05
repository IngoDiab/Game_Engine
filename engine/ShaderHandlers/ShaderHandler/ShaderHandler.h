#pragma once
#include<string>
#include <vector>
using namespace std;

#include <glm/glm.hpp>
using namespace glm;

class ShaderHandler
{
protected:
    unsigned int mShaderHandler;
    unsigned int mModelHandler;
    unsigned int mViewHandler;
    unsigned int mProjectionHandler;

    vector<int> mTexturesHandlers = vector<int>(16);

public:
    ShaderHandler(const string& _vertexShader, const string& _fragShader);

public:
    unsigned int GetShaderHandler() const {return mShaderHandler;}

public:
    virtual void Initialize();

    virtual void SendMVP(const mat4& _model, const mat4& _view, const mat4& _proj);
    virtual void SendTexture(int _typeTexture, int _offsetSlot, int _texture);

    virtual void GetTextureLocation(const int _slotTexture, const string& _nameLocation);
};
