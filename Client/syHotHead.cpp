#include "syHotHead.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syHotHead_Fire.h"
#include "syobject.h"
#include "syTransform.h"
#include "syInput.h"

namespace sy
{
	HotHead::HotHead()
		: Enemy(eAbilityType::Fire)
	{
	}

	HotHead::~HotHead()
	{
	}

	void HotHead::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left", L"..\\Resources\\Enemy\\Enemies_Left.bmp");

		mAnimator->CreateAnimation(Enemies_Right, L"HotHead_Right_Walk", Vector2(0.f, 3260.f), Vector2(22.f, 21.f), Vector2(22.f, 0.f), 0.18f, 8);
		mAnimator->CreateAnimation(Enemies_Left, L"HotHead_Left_Walk", Vector2(460.f, 3260.f), Vector2(22.f, 21.f), Vector2(-22.f, 0.f), 0.18f, 8);

		mAnimator->CreateAnimation(Enemies_Right, L"HotHead_Right_Death", Vector2(0.f, 3350.f), Vector2(23.f, 21.f), Vector2(23.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Enemies_Left, L"HotHead_Left_Death", Vector2(459.f, 3350.f), Vector2(23.f, 21.f), Vector2(-23.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(Enemies_Right, L"HotHead_Right_Attack", Vector2(8.f, 3284.f), Vector2(24.f, 21.f), Vector2(24.f, 0.f), 0.2f, 3);
		mAnimator->CreateAnimation(Enemies_Left, L"HotHead_Left_Attack", Vector2(450.f, 3284.f), Vector2(24.f, 21.f), Vector2(-24.f, 0.f), 0.2f, 3);

		mAnimator->PlayAnimation(L"HotHead_Right_Walk", true);

		Enemy::Initialize();
	}

	void HotHead::Update()
	{
		Enemy::Update();

		// 특정 조건일때 스킬 생성
		if (Input::GetKeyDown(eKeyCode::MOUSE_LBTN))
		{
			Transform* tr = GetComponent<Transform>();
			// 현재 HotHead 위치 기준 더해준 위치로 생성
			Vector2 pos = tr->GetPosition();
			pos += Vector2(10.f, 0.f);
			HotHead_Fire* skill = object::Instantiate<HotHead_Fire>(eLayerType::Effect);
			skill->GetComponent<Transform>()->SetPosition(pos);
			skill->SetOwner(this);
		}
	}

	void HotHead::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
}