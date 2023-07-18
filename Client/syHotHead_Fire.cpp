#include "syHotHead_Fire.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"

namespace sy
{
	HotHead_Fire::HotHead_Fire()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemy\\Enemies_Left.bmp");

		Animator* animator = GetAnimator();

		animator->CreateAnimation(Enemies_Right, L"HotHead_Fire_Right", Vector2(22.f, 3308.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.08f, 3);
		animator->CreateAnimation(Enemies_Left, L"HotHead_Fire_Left", Vector2(460.f, 3308.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.08f, 3);
		
		animator->PlayAnimation(L"HotHead_Fire_Right", true);
	}

	HotHead_Fire::~HotHead_Fire()
	{
	}

	void HotHead_Fire::Initialize()
	{
		Effects::Initialize();
	}

	void HotHead_Fire::Update()
	{
		Effects::Update();
	}

	void HotHead_Fire::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}