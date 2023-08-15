#include "syInhale_Effect.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syTime.h"
#include "syDefaultKirby.h"
#include "syIce_Enemy.h"
#include "syPlayer.h"
#include "syAbilityItem.h"
#include "syAbilityStar.h"
#include "syStar_Effect.h"
#include "syBossEnemy.h"

namespace sy
{
	Inhale_Effect::Inhale_Effect(Player* owner)
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
		// Collider 에 충돌한 객체중 플레이어와 제일 가까운 객체를 타겟으로 설정
		SetTarget();

		// 플레이어 위치따라가도록 갱신
		Player* player = dynamic_cast<Player*>(GetOwner());		

		GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());

		// Target 상태 업데이트
		TargetUpdate();				

		DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());

		// defaultKirby 가 아니면 삭제
		if (defaultKirby == nullptr)
		{
			Destroy(this);
		}
		else
		{
			// Inhale 이외의 상태에선 삭제
			if (mTarget == nullptr && !(defaultKirby->GetKirbyState() == eDefaultKirbyState::Inhale_1 || defaultKirby->GetKirbyState() == eDefaultKirbyState::Inhale_2))
			{
				Destroy(this);
			}
		}

		Effects::Update();
	}

	void Inhale_Effect::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Inhale_Effect::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
			return;

		if (other->GetOwner()->GetGameObjectState() == eGameObjectState::Dead)
			return;

		AbilityStar* abilityStar = dynamic_cast<AbilityStar*>(other->GetOwner());
		AbilityItem* abilityItem = dynamic_cast<AbilityItem*>(other->GetOwner());
		Star_Effect* star = dynamic_cast<Star_Effect*>(other->GetOwner());
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		// 특정 오브젝트만 흡수 인식
		if (abilityStar == nullptr
			&& abilityItem == nullptr
			&& star == nullptr
			&& enemy == nullptr)
			return;

		// 흡수한 오브젝트가 Enemy인경우 Dead상태인지 체크
		if (enemy != nullptr && enemy->IsDeadState())
			return;

		mInhaledObject.push_back(other->GetOwner());
	}

	void Inhale_Effect::SetTarget()
	{
		Player* player = dynamic_cast<Player*>(GetOwner());
		if (player == nullptr)
			return;

		// 맨처음 영역에 들어온 한번만 타겟 설정
		if (mTarget != nullptr)
			return;

		// 흡수 우선순위 0번째 AbilityStar
		for (GameObject* obj : mInhaledObject)
		{
			if (obj == nullptr)
				continue;

			Transform* PlayerTransform = player->GetComponent<Transform>();

			AbilityStar* abilityStar = dynamic_cast<AbilityStar*>(obj);

			// abilityStar이 아니면 적용하지않음
			if (abilityStar == nullptr)
				continue;

			if (mTarget == nullptr)
			{
				mTarget = abilityStar;
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
					mTarget = abilityStar;
				}
			}
		}

		// AbilityStar를 찾았다면 리턴
		if (mTarget != nullptr)
			return;


		// 흡수 우선순위 1번째 AbilityItem
		for (GameObject* obj : mInhaledObject)
		{
			if (obj == nullptr)
				continue;

			Transform* PlayerTransform = player->GetComponent<Transform>();

			AbilityItem* abilityItem = dynamic_cast<AbilityItem*>(obj);

			// AbilityItem이 아니면 적용하지않음
			if (abilityItem == nullptr)
				continue;

			if (mTarget == nullptr)
			{
				mTarget = abilityItem;
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
					mTarget = abilityItem;
				}
			}
		}

		// AbilityItem을 찾았다면 리턴
		if (mTarget != nullptr)
			return;

		// 흡수 우선순위 2번째 Star_Effect
		for (GameObject* obj : mInhaledObject)
		{
			if (obj == nullptr)
				continue;

			Transform* PlayerTransform = player->GetComponent<Transform>();

			// Star_Effect 가 아니면 적용하지않음, Dead 상태는 적용하지않음
			Star_Effect* star = dynamic_cast<Star_Effect*>(obj);
			if (star == nullptr
				|| star->GetStarState() == eStarState::Dead)
				continue;

			if (mTarget == nullptr)
			{
				mTarget = star;
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
					mTarget = star;
				}
			}
		}

		// Star_Effect를 찾았다면 리턴
		if (mTarget != nullptr)
			return;

		// 흡수 우선순위 3번째 Enemy
		for (GameObject* obj : mInhaledObject)
		{
			if (obj == nullptr)
				continue;

			Transform* PlayerTransform = player->GetComponent<Transform>();

			// Enemy가 아니면 적용하지않음, Dead 상태는 적용하지않음
			Enemy* enemy = dynamic_cast<Enemy*>(obj);
			if (enemy == nullptr
				|| enemy->GetGameObjectState() == eGameObjectState::Dead
				|| enemy->GetCurHP() <= 0.f)
				continue;

			// IceEnemy는 적용하지않음
			Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(obj);
			if (IceEnemy != nullptr)
				continue;

			// BossEnemy는 적용하지않음
			BossEnemy* bossEnemy = dynamic_cast<BossEnemy*>(obj);
			if (bossEnemy != nullptr)
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

		// Enemy를 찾았다면 리턴
		if (mTarget != nullptr)
			return;
	}

	void Inhale_Effect::TargetUpdate()
	{
		// Target 의 Inhaled 상태 호출
		if (mTarget == nullptr || mTarget->GetGameObjectState() == eGameObjectState::Dead)
			return;

		Player* player = dynamic_cast<Player*>(GetOwner());
		DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());

		// defaultKirby 가 아니면 리턴
		if (defaultKirby == nullptr)
			return;

		Transform* PlayerTransform = player->GetComponent<Transform>();
		Transform* TargetTransform = mTarget->GetComponent<Transform>();

		Vector2 vecDir = PlayerTransform->GetPosition() - TargetTransform->GetPosition();
		float Len = vecDir.Length();

		// 특정 거리 이내에 근접하면 삭제
		if (Len < 10.f)
		{
			mbInhale = true;
			Destroy(mTarget);
			Destroy(this);

			// Player에 흡수한 객체 정보 셋팅

			AbilityStar* abilityStar = dynamic_cast<AbilityStar*>(mTarget);
			AbilityItem* abilityItem = dynamic_cast<AbilityItem*>(mTarget);
			Star_Effect* star = dynamic_cast<Star_Effect*>(mTarget);
			Enemy* enemy = dynamic_cast<Enemy*>(mTarget);

			if (abilityStar != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(abilityStar->GetAbilityType(), sy::InhaledObjectType::AbilityStar);
			}
			else if (abilityItem != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(abilityItem->GetAbilityType(), sy::InhaledObjectType::AbilityItem);
			}
			else if (star != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(eAbilityType::Normal, sy::InhaledObjectType::Star_Effect);
			}
			else if (enemy != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(enemy->GetAbilityType(), sy::InhaledObjectType::Monster);
			}	
		}
		else
		{
			AbilityStar* abilityStar = dynamic_cast<AbilityStar*>(mTarget);
			AbilityItem* abilityItem = dynamic_cast<AbilityItem*>(mTarget);
			Enemy* enemy = dynamic_cast<Enemy*>(mTarget);

			// Inhaled 상태 설정
			if (abilityStar != nullptr)
			{
				abilityStar->TakeInhaled();
			}
			else if (abilityItem != nullptr)
			{
				abilityItem->TakeInhaled();
			}
			else if (enemy != nullptr)
			{
				enemy->TakeInhaled(vecDir);
			}

			vecDir.Normalize();
			vecDir *= 300.f * Time::DeltaTime();
			vecDir += TargetTransform->GetPosition();
			TargetTransform->SetPosition(vecDir);
		}		
	}
}
