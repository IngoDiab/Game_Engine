#include "PhysicManager.h"

#include "engine/Physic/PhysicComponent/PhysicComponent.h"

void PhysicManager::AddPhysicComponent(PhysicComponent* _physicComponent)
{
    mPhysicComponents.push_back(_physicComponent);
}

void PhysicManager::DeletePhysicComponents()
{
    mPhysicComponents.clear();
}

void PhysicManager::UpdatePhysic()
{
    ClipPhysicComponents();
}

void PhysicManager::ClipPhysicComponents()
{
    for(PhysicComponent* _component : mPhysicComponents)
        _component->ApplyClip();
}