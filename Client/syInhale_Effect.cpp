#include "syInhale_Effect.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syTime.h"
#include "syDefaultKirby.h"
#include "syIce.h"

namespace sy
{
	Inhale_Effect::Inhale_Effect(GameObject* owner)
		: Effects(owner)
		, mDir(eDirection::RIGHT)
	{
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();
		GetComponent<Transform>()->SetDirection(mDir);
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
			
		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(63.f, 30.f));

		if (mDir == eDirection::RIGHT)
			col->SetOffset(Vector2(31.5f, 0.f));
		else
			col->SetOffset(Vector2(-31.5f, 0.f));

	}

	Inhale_Effect::~Inhale_Effect()
	{

	}

	void Inhale_Effect::Initialize()
	{
		Effects::Initialize();
	}

	void Inhale_Effect::Update()
	{
		GetComponent<Transform>()->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		DefaultKirby* player = dynamic_cast<DefaultKirby*>(GetOwner());

		// Inhale 이외의 상태에선 삭제
		if (!(player->GetKirbyState() == eDefaultKirbyState::Inhale_1 || player->GetKirbyState() == eDefaultKirbyState::Inhale_2))
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void Inhale_Effect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Inhale_Effect::OnCollisionEnter(Collider* other)
	{
	}

	void Inhale_Effect::OnCollisionStay(Collider* other)
	{
		DefaultKirby* player = dynamic_cast<DefaultKirby*>(GetOwner());

		if (player == nullptr)
			return;

		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (enemy == nullptr)
			return;

		// ice 타입이면 무시
		Ice* ice = dynamic_cast<Ice*>(other->GetOwner());
		if (ice != nullptr)
			return;

		// 피격 애니메이션 설정
		enemy->TakeHit(0, Vector2::Zero);

		Transform* PlayerTransform = player->GetComponent<Transform>();
		Transform* EnemyTransform = enemy->GetComponent<Transform>();

		Vector2 vecDir = PlayerTransform->GetPosition() - EnemyTransform->GetPosition();
		float Len = vecDir.Length();

		// 특정 거리 이내에 근접하면 삭제
		if (Len < 10.f)
		{
			player->SetInhaleTrig(true);
			Destroy(other->GetOwner());
			Destroy(this);
		}
		else
		{
			vecDir.Normalize();
			vecDir *= 200.f * Time::DeltaTime();
			vecDir += EnemyTransform->GetPosition();
			EnemyTransform->SetPosition(vecDir);
		}
	}

	void Inhale_Effect::OnCollisionExit(Collider* other)
	{
	}
}
