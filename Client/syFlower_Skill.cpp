#include "syFlower_Skill.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"

namespace sy
{
	FlowerSkill::FlowerSkill()
	{
		Texture* tex = ResourceManager::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemy\\Enemies_Right.bmp");

		mAnimator->CreateAnimation(tex, L"Flower_Skill", Vector2(109.f, 2959.f), Vector2(8.f, 8.f), Vector2(8.f, 0.f), 1.f, 1);
		mAnimator->PlayAnimation(L"Flower_Skill", true);
	}

	FlowerSkill::~FlowerSkill()
	{
	}

	void FlowerSkill::Initialize()
	{
		Effects::Initialize();
	}

	void FlowerSkill::Update()
	{
		Effects::Update();
	}

	void FlowerSkill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}