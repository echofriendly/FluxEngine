#include "FluxEngine.h"
#include "FreeCamera.h"
#include "Camera.h"
#include "SceneGraph/Transform.h"
#include "Audio/AudioListener.h"
#include "Rendering/Core/Graphics.h"
#include "Input/InputEngine.h"

FreeCamera::FreeCamera(Context* pContext) :
	SceneNode(pContext)
{
	m_pInput = pContext->GetSubsystem<InputEngine>();
	m_pGraphics = pContext->GetSubsystem<Graphics>();
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::OnSceneSet(Scene* pScene)
{
	SceneNode::OnSceneSet(pScene);

	AudioListener* pAudioListener = new AudioListener(m_pContext);
	AddComponent(pAudioListener);
	m_pCamera = new Camera(m_pContext, m_pInput, m_pGraphics);
	AddComponent(m_pCamera);
}

void FreeCamera::Update()
{
	SceneNode::Update();

	if(m_UseMouseAndKeyboard)
		KeyboardMouse();
}

void FreeCamera::KeyboardMouse()
{
	float dt = GameTimer::DeltaTime();

	//Moving
	Vector3 moveDirection(0, 0, 0);
	moveDirection.x += m_pInput->IsKeyboardKeyDown(SDLK_a) ? -1 : 0;
	moveDirection.x += m_pInput->IsKeyboardKeyDown(SDLK_d) ? 1 : 0;
	moveDirection.z += m_pInput->IsKeyboardKeyDown(SDLK_s) ? -1 : 0;
	moveDirection.z += m_pInput->IsKeyboardKeyDown(SDLK_w) ? 1 : 0;
	moveDirection.y += m_pInput->IsKeyboardKeyDown(SDLK_q) ? -1 : 0;
	moveDirection.y += m_pInput->IsKeyboardKeyDown(SDLK_e) ? 1 : 0;

	float moveSpeed = m_MoveSpeed;
	if (m_pInput->IsKeyboardKeyDown(SDLK_LSHIFT))
		moveSpeed *= m_ShiftMultiplier;
	moveDirection *= dt * moveSpeed;

	if(moveDirection != Vector3())
		GetTransform()->Translate(moveDirection, Space::SELF);

	//Rotation
	if ( m_pInput->IsMouseButtonDown(SDL_BUTTON_RIGHT))
	{
		Vector2 mouseMove =  m_pInput->GetMouseMovement();
		if (mouseMove != Vector2())
		{
			GetTransform()->Rotate(mouseMove.y * dt * m_RotationSpeed, 0.0f, 0.0f, Space::SELF);
			GetTransform()->Rotate(0.0f, mouseMove.x * dt * m_RotationSpeed, 0.0f, Space::WORLD);
		}
	}
}