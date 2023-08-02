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
		, mInhaledObject()
		, mTarget(nullptr)
		, mbInhale(false)
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
		if (player == nullptr)
			return;


		// 맨처음 영역에 들어온 한번만 타겟 설정
		if (mTarget == nullptr)
		{
			for (GameObject* obj : mInhaledObject)
			{
				if (obj == nullptr)
					continue;

				Transform* PlayerTransform = player->GetComponent<Transform>();

				Enemy* enemy = dynamic_cast<Enemy*>(obj);

				// Enemy가 아니면 적용하지않음
				if (enemy == nullptr)
					continue;

				if (mTarget == nullptr)
				{
					mTarget = enemy;
				}
				else
				{
					Transform* TargetTransform = mTarget->GetComponent<Transform>();
					Transform* objTransform = obj->GetComponent<Transform>();

					float TargetLen = (PlayerTransform->GetPosition() - TargetTransform->GetPosition()).Length();
					float ObjLen = (PlayerTransform->GetPosition() - objTransform->GetPosition()).Length();

					// Player와의 거리가 작은 obj 를 타겟으로 설정
					if (ObjLen < TargetLen)
					{
						mTarget = enemy;
					}
				}
			}


			// Block 클래스 탐색
			//if (mTarget == nullptr)
			//{
			//	
			//}
		}		


		// Target 의 Inhaled 상태 호출
		if (mTarget != nullptr)
		{
			Enemy* enemy = dynamic_cast<Enemy*>(mTarget);

			if (enemy == nullptr)
				return;

			// ice 타입이면 무시
			Ice* ice = dynamic_cast<Ice*>(mTarget);
			if (ice != nullptr)
				return;

			Transform* PlayerTransform = player->GetComponent<Transform>();
			Transform* EnemyTransform = enemy->GetComponent<Transform>();

			Vector2 vecDir = PlayerTransform->GetPosition() - EnemyTransform->GetPosition();
			float Len = vecDir.Length();

			// 특정 거리 이내에 근접하면 삭제
			if (Len < 10.f)
			{
				mbInhale = true;
				Destroy(mTarget);
				Destroy(this);
			}
			else
			{
				// Enemy 상태 설정
				enemy->TakeInhaled(vecDir);

				vecDir.Normalize();
				vecDir *= 300.f * Time::DeltaTime();
				vecDir += EnemyTransform->GetPosition();
				EnemyTransform->SetPosition(vecDir);
			}
		}

		// Inhale 이외의 상태에선 삭제
		if (mTarget == nullptr && !(player->GetKirbyState() == eDefaultKirbyState::Inhale_1 || player->GetKirbyState() == eDefaultKirbyState::Inhale_2))
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
		DefaultKirby* player = dynamic_cast<DefaultKirby*>(other->GetOwner());
		if (player != nullptr)
			return;

		if (other->GetOwner()->GetGameObjectState() == eGameObjectState::Dead)
			return;

		mInhaledObject.push_back(other->GetOwner());
	}

	void Inhale_Effect::OnCollisionStay(Collider* other)
	{
		
	}

	void Inhale_Effect::OnCollisionExit(Collider* other)
	{
	}
}
