#include "Character.h"
#include "engine/Engine/Engine.h"
#include "engine/Meshs/Sphere/Sphere.h"
#include "engine/Planets/Material/PlanetMaterial.h"
#include "engine/Components/MeshComponent/MeshComponent.h"
#include "engine/Physic/PhysicComponent/PhysicComponent.h"

Character::Character()
{
    mMeshComponent = AddComponent<MeshComponent>(vec3(0), vec3(0), vec3(5));
    mMeshComponent->CreateMesh<Sphere>();
    mMeshComponent->AddLOD<Sphere>(100, 10,10);
    mMeshComponent->AddLOD<Sphere>(200, 4,4);
    mMeshComponent->CreateMaterial<PlanetMaterial>();

    mPhysicComponent = AddComponent<PhysicComponent>();
}

void Character::MoveLateral(const float _move)
{
    if(!mCanMove) return;
    const vec3 _currentPos = mTransform.GetPosition();
    mTransform.SetPosition(_currentPos+mTransform.GetRightVector()*_move*mMovementSpeed*Engine::Instance()->DeltaTime());
}

void Character::MoveForwardBackward(const float _move)
{
    if(!mCanMove) return;
    const vec3 _currentPos = mTransform.GetPosition();
    mTransform.SetPosition(_currentPos+mTransform.GetForwardVector()*_move*mMovementSpeed*Engine::Instance()->DeltaTime());
}

void Character::MoveUpDown(const float _move)
{

}
    
void Character::RotateLocalAxisX(float _rotation)
{

}

void Character::RotateLocalAxisY(float _rotation)
{

}

void Character::RotateLocalAxisZ(float _rotation)
{

}

void Character::ClipToLandscape(Landscape* const _landscape)
{
    if(!mPhysicComponent) return;
    mPhysicComponent->ClipObject(_landscape);
}