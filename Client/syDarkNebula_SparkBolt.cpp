#include "syDarkNebula_SparkBolt.h"
#include "syDarkNebula.h"
#include "syTime.h"
#include "syTransform.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syCollider.h"
#include "syAnimator.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"

namespace sy
{
	DarkNebula_SparkBolt::DarkNebula_SparkBolt(DarkNebula* owner, eCornerDirection dir)
		: Effects(owner)
		, mDir(dir)
		, mTransform(nullptr)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		AddComponent<Collider>()->SetSize(Vector2(50.f, 42.f));

		// 애니메이션 생성
		Animator* animator = GetComponent<Animator>();
		Texture* DarkNebula_Spark_Bolt_Tex = ResourceManager::Load<Texture>(L"DarkNebula_Spark_Bolt_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_Spark_Bolt.bmp");

		animator->CreateAnimation(DarkNebula_Spark_Bolt_Tex, L"DarkNebula_SparkBolt_RightTop", Vector2::Zero, Vector2(50.f, 42.f), Vector2(50.f, 0.f), 0.05f, 3);
		animator->CreateAnimation(DarkNebula_Spark_Bolt_Tex, L"DarkNebula_SparkBolt_LeftTop", Vector2(0.f, 42.f), Vector2(50.f, 42.f), Vector2(50.f, 0.f), 0.05f, 3);
		animator->CreateAnimation(DarkNebula_Spark_Bolt_Tex, L"DarkNebula_SparkBolt_RightBottom", Vector2(0.f, 84.f), Vector2(50.f, 42.f), Vector2(50.f, 0.f), 0.05f, 3);
		animator->CreateAnimation(DarkNebula_Spark_Bolt_Tex, L"DarkNebula_SparkBolt_LeftBottom", Vector2(0.f, 126.f), Vector2(50.f, 42.f), Vector2(50.f, 0.f), 0.05f, 3);

		if(mDir == eCornerDirection::RightTop)
			animator->PlayAnimation(L"DarkNebula_SparkBolt_RightTop", true);
		else if (mDir == eCornerDirection::LeftTop)
			animator->PlayAnimation(L"DarkNebula_SparkBolt_LeftTop", true);
		else if (mDir == eCornerDirection::RightBottom)
			animator->PlayAnimation(L"DarkNebula_SparkBolt_RightBottom", true);
		else if (mDir == eCornerDirection::LeftBottom)
			animator->PlayAnimation(L"DarkNebula_SparkBolt_LeftBottom", true);
	}

	DarkNebula_SparkBolt::~DarkNebula_SparkBolt()
	{
	}

	void DarkNebula_SparkBolt::Initialize()
	{
		Effects::Initialize();
	}

	void DarkNebula_SparkBolt::Update()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 2.f)
		{
			Destroy(this);
		}

		// 이동
		Vector2 Dir = Vector2::Zero;

		if (mDir == eCornerDirection::RightTop)
			Dir = Vector2(2.f, -1.f);
		else if (mDir == eCornerDirection::LeftTop)
			Dir = Vector2(-2.f, -1.f);
		else if (mDir == eCornerDirection::RightBottom)
			Dir = Vector2(2.f, 1.f);
		else if (mDir == eCornerDirection::LeftBottom)
			Dir = Vector2(-2.f, 1.f);

		Dir.Normalize();

		Vector2 pos = mTransform->GetPosition();
		pos += Dir * 100.f * Time::DeltaTime();
		mTransform->SetPosition(pos);

		Effects::Update();
	}

	void DarkNebula_SparkBolt::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void DarkNebula_SparkBolt::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// Damage 상태에선 무시
		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
		if (kirby != nullptr && kirby->IsDamagedState())
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}
}