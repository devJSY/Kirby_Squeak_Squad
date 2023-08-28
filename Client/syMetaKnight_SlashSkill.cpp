#include "syMetaKnight_SlashSkill.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syMetaKnight.h"
#include "syPlayer.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTime.h"

namespace sy
{
	MetaKnight_SlashSkill::MetaKnight_SlashSkill(MetaKnight* owner, Vector2 MoveDir)
		: Effects(owner)
		, mTransform(nullptr)
		, mMoveDir(MoveDir)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		AddComponent<Collider>()->SetSize(Vector2(42.f, 73.5f));

		// 텍스쳐 로드
		Texture* MetaKnight_SlashSkill_Right_Tex = ResourceManager::Load<Texture>(L"MetaKnight_SlashSkill_Right_Tex", L"..\\Resources\\Enemy\\Boss\\MetaKnight\\MetaKnight_SlashSkill_Right.bmp");
		Texture* MetaKnight_SlashSkill_Left_Tex = ResourceManager::Load<Texture>(L"MetaKnight_SlashSkill_Left_Tex", L"..\\Resources\\Enemy\\Boss\\MetaKnight\\MetaKnight_SlashSkill_Left.bmp");

		MetaKnight_SlashSkill_Right_Tex->SetScale(Vector2(0.35f, 0.35f));
		MetaKnight_SlashSkill_Left_Tex->SetScale(Vector2(0.35f, 0.35f));

		Animator* animator = GetComponent<Animator>();

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, 0.f);
		animator->CreateAnimation(MetaKnight_SlashSkill_Right_Tex, L"MetaKnight_SlashSkill_Right", Vector2::Zero, Vector2(120.f, 210.f), Vector2(120.f, 0.f), 0.1f, 4, Animationoffset);
		animator->CreateAnimation(MetaKnight_SlashSkill_Left_Tex, L"MetaKnight_SlashSkill_Left", Vector2::Zero, Vector2(120.f, 210.f), Vector2(120.f, 0.f), 0.1f, 4, Animationoffset);

		if (owner->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
			animator->PlayAnimation(L"MetaKnight_SlashSkill_Right", true);
		else
			animator->PlayAnimation(L"MetaKnight_SlashSkill_Left", true);
	}

	MetaKnight_SlashSkill::~MetaKnight_SlashSkill()
	{
	}

	void MetaKnight_SlashSkill::Initialize()
	{
		Effects::Initialize();
	}

	void MetaKnight_SlashSkill::Update()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 5.f)
		{
			Destroy(this);
		}

		Vector2 pos = mTransform->GetPosition();
		mMoveDir.Normalize();
		pos += mMoveDir * 150.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
		
		Effects::Update();
	}

	void MetaKnight_SlashSkill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void MetaKnight_SlashSkill::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void MetaKnight_SlashSkill::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}