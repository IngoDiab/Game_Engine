#include "Collider.h"

void Collider::ChangeMeshByDistance(Camera* _renderingCamera, float _threshold)
{

}

void Collider::OnCollide(CollisionData _data)
{
    if(!mCollisionCallback) return;
    mCollisionCallback(_data);
}

void Collider::OnTrigger(CollisionData _data)
{
    if(!mTriggerCallback) return;
    mTriggerCallback(_data);
}