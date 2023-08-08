#include "syBreath_Effect.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syTime.h"
#include "syEnemy.h"
#include "syPlayer.h"

namespace sy
{
	Breath_Effect::Breath_Effect(Player* owner)
		: Effects(owner)
		, mDir(eDirection::RIGHT)
		, mColOffset(0.f)
	{
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();

		Texture* Breath_Effect_Left_tex = ResourceManager::Load<Texture>(L"Breath_Effect_Left", L"..\\Resources\\Effect\\BreathEffect_Left.bmp");
		Texture* Breath_Effect_Right_tex = ResourceManager::Load<Texture>(L"Breath_Effect_Right", L"..\\Resources\\Effect\\BreathEffect_Right.bmp");

		Transform* tr = GetComponent<Transform>();
		Vector2 vec = owner->GetComponent<Transform>()->GetPosition();
		tr->SetPosition(vec);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(25.f, 25.f));

		Animator* animator = GetComponent<Animator>();

		Vector2 LeftOffset = Vector2(-50.f, 0.f);
		Vector2 RightOffset = Vector2(50.f, 0.f);

		animator->CreateAnimation(Breath_Effect_Left_tex, L"Breath_Effect_Left", Vector2(500.f, 0.f), Vector2(100.f, 25.f), Vector2(-100.f, 0.f), 0.05f, 6, LeftOffset);
		animator->CreateAnimation(Breath_Effect_Right_tex, L"Breath_Effect_Right", Vector2(0.f, 0.f), Vector2(100.f, 25.f), Vector2(100.f, 0.f), 0.05f, 6, RightOffset);

		
		// 방향 설정
		if (mDir == eDirection::RIGHT)
			animator->PlayAnimation(L"Breath_Effect_Right", false);
		else
			animator->PlayAnimation(L"Breath_Effect_Left", false);

	}

	Breath_Effect::~Breath_Effect()
	{
	}

	void Breath_Effect::Initialize()
	{
		Effects::Initialize();
	}

	void Breath_Effect::Update()
	{
		// Collider 이동
		mColOffset += Time::DeltaTime();

		Collider* col = GetComponent<Collider>();
		if (mDir == eDirection::RIGHT)
			col->SetOffset(Vector2(mColOffset * 200.f, 0.f));
		else
			col->SetOffset(Vector2(mColOffset * -200.f, 0.f));


		Animator* animator = GetComponent<Animator>();
		if (animator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void Breath_Effect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Breath_Effect::OnCollisionEnter(Collider* other)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		
		if (enemy == nullptr)
			return;

		Player* player = dynamic_cast<Player*>(GetOwner());

		if (player == nullptr)
			return;
		
		// 스킬 → 몬스터 방향
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);

		Destroy(this);
	}
}