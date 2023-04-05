#pragma once

#include <vector>
using namespace std;

#include "engine/Utils/Singleton/Singleton.h"

class PhysicComponent;

class PhysicManager final : public Singleton<PhysicManager>
{
    vector<PhysicComponent*> mPhysicComponents = vector<PhysicComponent*>();

public:
    void AddPhysicComponent(PhysicComponent* _physicComponent);
    void DeletePhysicComponents();

public:
    void UpdatePhysic();
    void ClipPhysicComponents();
};