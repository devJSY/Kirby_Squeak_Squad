#include "syZoom_Effect.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "sySceneManager.h"
#include "syPlayer.h"

namespace sy
{
	Zoom_Effect::Zoom_Effect(Player* owner)
		: Effects(owner)
	{
		Texture* tex = ResourceManager::Load<Texture>(L"Zoom", L"..\\Resources\\Effect\\Zoom.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(tex, L"ZoomAnimation", Vector2::Zero, Vector2(512.f, 384.f), Vector2(512.f, 0.f), 0.02f, 30);
		mAnimator->SetAffectedCamera(false);

		GetComponent<Transform>()->SetPosition(owner->GetComponent<Transform>()->GetPosition());

		mAnimator->PlayAnimation(L"ZoomAnimation", false);
	}

	Zoom_Effect::~Zoom_Effect()
	{
	}

	void Zoom_Effect::Initialize()
	{
		Effects::Initialize();
	}

	void Zoom_Effect::Update()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
			SceneManager::LoadScene(L"TunnelScene");
		}

		Effects::Update();
	}

	void Zoom_Effect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}