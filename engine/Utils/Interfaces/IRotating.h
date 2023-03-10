#pragma once

class IRotating
{
protected:
    float mRotationSpeed = 10;
    bool mCanRotate = false;

public:
    float GetRotationSpeed() const {return mRotationSpeed;}
    void SetRotationSpeed(const float _speed){mRotationSpeed = _speed;}

    bool CanMove() const {return mCanRotate;}
    void SetCanRotate(const bool _canRotate) {mCanRotate = _canRotate;}

public:
    virtual void RotateLocalAxisX(const float _rotation) = 0;
    virtual void RotateLocalAxisY(const float _rotation) = 0;
    virtual void RotateLocalAxisZ(const float _rotation) = 0;
};