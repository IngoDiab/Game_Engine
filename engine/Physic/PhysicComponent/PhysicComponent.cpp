#include "PhysicComponent.h"
#include "engine/Objects/GameObject/GameObject.h"
#include "engine/Landscape/Landscape/Landscape.h"
#include <iostream>
using namespace std;
void PhysicComponent::ApplyClip()
{
    if(!mClipToLandscape) return;
    vec3 _position = mOwner->GetTransformInstance()->GetTransformData()->mWorldPosition;
    mClipToLandscape->GetProjectionOnPlane(_position);
    // cout<<_position.x<<" "<<_position.y<<" "<<_position.z<<endl;
    mOwner->SetPosition(_position);
}