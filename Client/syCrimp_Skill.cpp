#include "syCrimp_Skill.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTime.h"
#include "syPlayer.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syCrimp.h"

namespace sy
{
	CrimpSkill::CrimpSkill(Crimp* owner)
		: Effects(owner)
		, mTransform(nullptr)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		rigidbody->SetGround(false);
		rigidbody->SetVelocity(Vector2(200.f, 0.f));

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(10.f, 10.f));

		Texture* tex = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(tex, L"Flower_Skill", Vector2(109.f, 2959.f), Vector2(8.f, 8.f), Vector2(8.f, 0.f), 1.f, 1);
		animator->PlayAnimation(L"Flower_Skill", true);
	}

	CrimpSkill::~CrimpSkill()
	{
	}

	void CrimpSkill::Initialize()
	{
		Effects::Initialize();
	}

	void CrimpSkill::Update()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 3.f)
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void CrimpSkill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
	void CrimpSkill::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		player->TakeHit(10, Dir);
	}
}