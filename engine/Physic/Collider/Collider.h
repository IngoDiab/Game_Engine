#pragma once

#include <functional> 
using namespace std;

#include "engine/Components/Component/Component.h"
#include "engine/Utils/Interfaces/IRenderable.h"
#include "engine/Physic/CollisionData/CollisionData.h"


class Collider : public Component, public IRenderable
{
protected:
    bool mCanBeRendered = true;
    bool mIsTrigger = false;

    function<void(CollisionData)> mCollisionCallback = nullptr;
    function<void(CollisionData)> mTriggerCallback = nullptr;

public:
    virtual bool CanBeRendered() const override {return mCanBeRendered;}
    bool IsTrigger() const {return mIsTrigger;}
    virtual vec3 GetCenterInWorld() const {return vec3(0);}

    void SetTrigger(const bool _isTrigger) {mIsTrigger = _isTrigger;}
    void SetOnCollideCallback(function<void(CollisionData)> _callback) {if(_callback == nullptr);mCollisionCallback = _callback;}
    void SetOnTriggerCallback(function<void(CollisionData)> _callback) {mTriggerCallback = _callback;}

    void ClearOnCollide() {mCollisionCallback = nullptr;}
    void ClearOnTrigger() {mTriggerCallback = nullptr;}

public:
    virtual void ChangeMeshByDistance(Camera* _renderingCamera, float _threshold) override;

public:
    void OnCollide(CollisionData _data);
    void OnTrigger(CollisionData _data);
};