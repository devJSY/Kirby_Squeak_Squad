#include "syHotHead_Fire.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTime.h"
#include "syTransform.h"
#include "syPlayer.h"
#include "syHotHead.h"
#include "syResourceManager.h"
#include "sySound.h"

namespace sy
{
	HotHead_Fire::HotHead_Fire(HotHead* owner)
		: Effects(owner)
		, mTransform(nullptr)
		, mDir()
	{
		mTransform = GetComponent<Transform>();
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();
		mTransform->SetDirection(mDir);

		Vector2 vec = owner->GetComponent<Transform>()->GetPosition();
		if (mDir == eDirection::RIGHT)
			vec.x += 20.f;
		else
			vec.x -= 20.f;
		mTransform->SetPosition(vec);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(20.f, 20.f));

		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemy\\Enemies_Left.bmp");

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(Enemies_Right, L"HotHead_Fire_Right", Vector2(22.f, 3308.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.08f, 3);
		animator->CreateAnimation(Enemies_Left, L"HotHead_Fire_Left", Vector2(460.f, 3308.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.08f, 3);
		
		animator->PlayAnimation(L"HotHead_Fire_Right", true);
		ResourceManager::Load<Sound>(L"FireSkill_Sound", L"..\\Resources\\Sound\\Effect\\FireSkill.wav")->Play(true);
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
		Vector2 vec = GetOwner()->GetComponent<Transform>()->GetPosition();
		if (mDir == eDirection::RIGHT)
			vec.x += 20.f;
		else
			vec.x -= 20.f;
		mTransform->SetPosition(vec);

		HotHead* hothead = dynamic_cast<HotHead*>(GetOwner());
		if (hothead == nullptr || hothead->GetHotHeadState() != eHotHeadState::Attack)
		{
			Destroy(this);
			ResourceManager::Find<Sound>(L"FireSkill_Sound")->Stop(true);
		}


		Effects::Update();
	}

	void HotHead_Fire::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void HotHead_Fire::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		player->TakeHit(10, Dir);
	}
}