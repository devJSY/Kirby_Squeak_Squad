#include "sySirKibble_Skill.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "sySirKibble.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "sySound.h"
#include "syTime.h"
#include "syRigidbody.h"

namespace sy
{
	SirKibble_Skill::SirKibble_Skill(SirKibble* owner)
		: Effects(owner)
		, mDir()
		, mTransform(nullptr)
		, mRigidbody(nullptr)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();
		mDir = owner->GetComponent<Transform>()->GetDirection();
		Vector2 vec = owner->GetComponent<Transform>()->GetPosition();
		if (mDir == eDirection::RIGHT)
			vec.x += 20.f;
		else
			vec.x -= 20.f;
		mTransform->SetPosition(vec);

		// Collider
		AddComponent<Collider>()->SetSize(Vector2(20.f, 20.f));

		// Rigidbody
		mRigidbody = AddComponent<Rigidbody>();
		if (mDir == eDirection::RIGHT)
			mRigidbody->SetVelocity(Vector2(200.f, 0.f));
		else
			mRigidbody->SetVelocity(Vector2(-200.f, 0.f));

		mRigidbody->SetFloat(true);

		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemies_Right.bmp");

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(Enemies_Right, L"SirKibble_Skill", Vector2(179.f, 2640.f), Vector2(23.f, 16.f), Vector2(23.f, 0.f), 0.05f, 4);
		animator->PlayAnimation(L"SirKibble_Skill", true);

		ResourceManager::Load<Sound>(L"CutterKirby_Skill_HitSound", L"..\\Resources\\Sound\\Effect\\CutterSkill.wav");
		ResourceManager::Load<Sound>(L"CutterKirby_Skill_Sound", L"..\\Resources\\Sound\\Effect\\CutterSkill2.wav")->Play(true);
	}

	SirKibble_Skill::~SirKibble_Skill()
	{
		ResourceManager::Find<Sound>(L"CutterKirby_Skill_Sound")->Stop(true);
	}

	void SirKibble_Skill::Initialize()
	{
		Effects::Initialize();
	}

	void SirKibble_Skill::Update()
	{
		mDuration += Time::DeltaTime();

		// 일정시간뒤 자동삭제
		if (mDuration > 10.f)
		{
			ResourceManager::Find<Sound>(L"CutterKirby_Skill_Sound")->Stop(true);
			ResourceManager::Find<Sound>(L"CutterKirby_Skill_HitSound")->Play(false);
			Destroy(this);
		}

		// 이동
		if (mDir == eDirection::RIGHT)
			mRigidbody->AddForce(Vector2(-250.f, 0.f));
		else
			mRigidbody->AddForce(Vector2(250.f, 0.f));

		Effects::Update();
	}

	void SirKibble_Skill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void SirKibble_Skill::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());

		// DefaultKirby가 Damage 상태면 적용하지않음
		if (kirby != nullptr && kirby->IsDamagedState())
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		player->TakeHit(10, Dir);
	}
}