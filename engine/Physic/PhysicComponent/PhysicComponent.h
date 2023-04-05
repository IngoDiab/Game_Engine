#pragma once

#include "engine/Components/Component/Component.h"

class Collider;
class Landscape;

class PhysicComponent : public Component
{
    Collider* mCollider = nullptr;
    vec3 mVelocity = vec3(0);
    float mMass = 0;

    Landscape* mClipToLandscape = nullptr;
    float mOffsetClip = 10;

public:
    void ClipObject(Landscape* const _landscape){mClipToLandscape = _landscape;}

public :
    void ApplyClip();
};