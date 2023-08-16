#include "syDaroach_Energe.h"
#include "syDaroach.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syPlayer.h"
#include "syCollider.h"
#include "sySound.h"

namespace sy
{
	Daroach_Energe::Daroach_Energe(Daroach* owner)
		: Effects(owner)
		, mDir(eDirection::RIGHT)
		, mTransform(nullptr)
	{
		mTransform = GetComponent<Transform>();
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();
		mTransform->SetDirection(mDir);
		Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		pos.y += 9.f;
		if (mDir == eDirection::RIGHT)
			pos.x += 158.f;
		else
			pos.x -= 158.f;
		mTransform->SetPosition(pos);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(250.f, 16.f));

		Texture* Daroach_Left_Energe_Tex = ResourceManager::Load<Texture>(L"Daroach_Left_Energe_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Left_Energe.bmp");
		Texture* Daroach_Right_Energe_Tex = ResourceManager::Load<Texture>(L"Daroach_Right_Energe_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Right_Energe.bmp");

		Animator* animator = AddComponent<Animator>();

		animator->CreateAnimation(Daroach_Left_Energe_Tex, L"Daroach_Left_Energe", Vector2::Zero, Vector2(250.f, 16.f), Vector2(250.f, 0.f), 0.05f, 4);
		animator->CreateAnimation(Daroach_Right_Energe_Tex, L"Daroach_Right_Energe", Vector2::Zero, Vector2(250.f, 16.f), Vector2(250.f, 0.f), 0.05f, 4);

		if (mDir == eDirection::RIGHT)
			animator->PlayAnimation(L"Daroach_Right_Energe", true);
		else
			animator->PlayAnimation(L"Daroach_Left_Energe", true);
	
		// Sound Load
		ResourceManager::Load<Sound>(L"Daroach_IceSkill", L"..\\Resources\\Sound\\Effect\\Daroach\\IceSkill.wav")->Play(true);	
	}

	Daroach_Energe::~Daroach_Energe()
	{
		ResourceManager::Find<Sound>(L"Daroach_IceSkill")->Stop(true);
	}

	void Daroach_Energe::Initialize()
	{
		Effects::Initialize();
	}

	void Daroach_Energe::Update()
	{
		Daroach* owner = dynamic_cast<Daroach*>(GetOwner());

		if (owner == nullptr)
		{
			Destroy(this);
		}

		mDir = owner->GetComponent<Transform>()->GetDirection();
		mTransform->SetDirection(mDir);
		Vector2 pos = owner->GetComponent<Transform>()->GetPosition();
		pos.y += 9.f;
		if (mDir == eDirection::RIGHT)
			pos.x += 158.f;
		else
			pos.x -= 158.f;
		mTransform->SetPosition(pos);


		if (owner->GetDaroachState() != eDaroachState::WandAttack)
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void Daroach_Energe::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Daroach_Energe::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());

		// DefaultKirby가 Damage 상태면 적용하지않음
		if (kirby != nullptr && kirby->IsDamagedState())
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}