#include "syBioSpark_Shuriken.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syPlayer.h"
#include "syResourceManager.h"
#include "sySound.h"
#include "syBioSpark.h"
#include "syTime.h"
#include "syAnimator.h"

namespace sy
{
	BioSpark_Shuriken::BioSpark_Shuriken(BioSpark* owner)
		: Effects(owner)
		, mDir()
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mDuration(0.f)
	{
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		// 텍스쳐 로드
		Texture* BioSpark_Shuriken_Tex = ResourceManager::Load<Texture>(L"BioSpark_Shuriken_Tex", L"..\\Resources\\Enemy\\BioSpark\\BioSpark_shuriken.bmp");
		BioSpark_Shuriken_Tex->SetScale(Vector2(0.5f, 0.5f));
	
		mAnimator = GetComponent<Animator>();

		mAnimator->CreateAnimation(BioSpark_Shuriken_Tex, L"BioSpark_Shuriken_Right", Vector2::Zero, Vector2(60.f, 60.f), Vector2(60.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(BioSpark_Shuriken_Tex, L"BioSpark_Shuriken_Left", Vector2(0.f, 60.f), Vector2(60.f, 60.f), Vector2(60.f, 0.f), 1.f, 1);

		if(mDir == eDirection::RIGHT)
			mAnimator->PlayAnimation(L"BioSpark_Shuriken_Right", true);
		else
			mAnimator->PlayAnimation(L"BioSpark_Shuriken_Left", true);

		Collider* col = AddComponent<Collider>();
		col->SetPosition(mTransform->GetPosition());
		col->SetSize(Vector2(30.f, 15.f));

		ResourceManager::Load<Sound>(L"NinjaKirby_ShurikenSound", L"..\\Resources\\Sound\\Effect\\NinjaStar.wav")->Play(false);
	}

	BioSpark_Shuriken::~BioSpark_Shuriken()
	{
	}

	void BioSpark_Shuriken::Initialize()
	{
		Effects::Initialize();
	}

	void BioSpark_Shuriken::Update()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 5.f)
		{
			Destroy(this);
		}

		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();
		if (mDir == eDirection::RIGHT)
			pos.x += 300.f * Time::DeltaTime();
		else
			pos.x -= 300.f * Time::DeltaTime();
		mTransform->SetPosition(pos);

		Effects::Update();
	}

	void BioSpark_Shuriken::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void BioSpark_Shuriken::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
		Destroy(this);
	}
}