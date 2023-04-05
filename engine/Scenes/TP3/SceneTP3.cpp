#include "SceneTP3.h"
#include "engine/Character/Character.h"
#include "engine/Landscape/Landscape/Landscape.h"
#include "engine/Skyboxes/Skybox/Skybox.h"
#include "engine/Inputs/InputManager/InputManager.h"
#include "engine/Camera/EditorCamera/EditorCamera.h"
#include "engine/Engine/Engine.h"

void SceneTP3::LoadScene()
{
    Skybox* _skybox = Skybox::Instance();
    _skybox->ChangeSkybox("Textures/Skybox/Base/", ".jpg");

    mCharacter = CreateCharacter();
    mLandscape = CreateLandscape();

    InitEditorCamera();
    BindCharacterInput();
    BindLandscapeInput();

    mCharacter->ClipToLandscape(mLandscape);
}

Character* SceneTP3::CreateCharacter()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Character* _character = _objectManager->Create<Character>(vec3(0,100,0));
    return _character;
}

Landscape* SceneTP3::CreateLandscape()
{
    ObjectManager* _objectManager = ObjectManager::Instance();
    Landscape* _landscape = _objectManager->Create<Landscape>();
    _landscape->ChangeResolution(2,2);
    _landscape->ApplyHeightmap("Textures/Heightmaps/height_test.png",100);
    return _landscape;
}

void SceneTP3::InitEditorCamera() const
{
   EditorCamera::Instance()->SetPosition(vec3(0,100,0));
}

void SceneTP3::BindCharacterInput()
{
    InputManager* _inputManager = InputManager::Instance();
    _inputManager->BindAxis({{GLFW_KEY_UP,GLFW_KEY_DOWN}}, mCharacter, (void* (Object::*)(float))&Character::MoveForwardBackward);
    _inputManager->BindAxis({{GLFW_KEY_RIGHT,GLFW_KEY_LEFT}}, mCharacter, (void* (Object::*)(float))&Character::MoveLateral);
}

void SceneTP3::BindLandscapeInput() const
{
    InputManager* _inputManager = InputManager::Instance();
    _inputManager->BindKey(GLFW_KEY_KP_ADD , ACTION_TYPE::HOLD, mLandscape, (void* (Object::*)(bool))&Landscape::IncreaseResolution);
    _inputManager->BindKey(GLFW_KEY_KP_SUBTRACT, ACTION_TYPE::HOLD, mLandscape, (void* (Object::*)(bool))&Landscape::DecreaseResolution);
}