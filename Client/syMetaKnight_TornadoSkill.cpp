#include "syMetaKnight_TornadoSkill.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syMetaKnight.h"
#include "syPlayer.h"
#include "syTime.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"

namespace sy
{
	MetaKnight_TornadoSkill::MetaKnight_TornadoSkill(MetaKnight* owner)
		: Effects(owner)
		, mState(eMetaKnight_TornadoSkillState::Active)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mDir()
		, mDuration(0.f)
		, mbActive(true)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(Vector2(GetOwner()->GetComponent<Transform>()->GetPosition().x, 96.f));

		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();
		mTransform->SetDirection(mDir);
		AddComponent<Collider>()->SetSize(Vector2(63.f, 157.5f));
		
		Texture* MetaKnight_Tornado_Tex = ResourceManager::Load<Texture>(L"MetaKnight_Tornado_Tex", L"..\\Resources\\Enemy\\Boss\\MetaKnight\\MetaKnight_Tornado.bmp");

		MetaKnight_Tornado_Tex->SetScale(Vector2(0.35f, 0.35f));

		mAnimator = GetComponent<Animator>();

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, 0.f);
		mAnimator->CreateAnimation(MetaKnight_Tornado_Tex, L"MetaKnight_Tornado_Active", Vector2::Zero, Vector2(180.f, 450.f), Vector2(180.f, 0.f), 0.1f, 9, Animationoffset);
		mAnimator->CreateAnimation(MetaKnight_Tornado_Tex, L"MetaKnight_Tornado_Dead", Vector2(1620.f,0.f), Vector2(180.f, 450.f), Vector2(180.f, 0.f), 0.1f, 5, Animationoffset);

		mAnimator->PlayAnimation(L"MetaKnight_Tornado_Active", true);
	}

	MetaKnight_TornadoSkill::~MetaKnight_TornadoSkill()
	{
	}

	void MetaKnight_TornadoSkill::Initialize()
	{
		Effects::Initialize();
	}

	void MetaKnight_TornadoSkill::Update()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 5.f && mbActive)
		{
			mAnimator->PlayAnimation(L"MetaKnight_Tornado_Dead", false);
			mbActive = false;
		}

		if (!mbActive)
		{
			if (mAnimator->IsActiveAnimationComplete())
			{
				Destroy(this);
			}
		}

		Vector2 pos = mTransform->GetPosition();
		if(mDir == eDirection::RIGHT)
			pos.x += 100.f * Time::DeltaTime();
		else
			pos.x -= 100.f * Time::DeltaTime();
		mTransform->SetPosition(pos);

		Effects::Update();
	}

	void MetaKnight_TornadoSkill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void MetaKnight_TornadoSkill::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void MetaKnight_TornadoSkill::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}