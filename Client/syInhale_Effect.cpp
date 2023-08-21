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
#include "syDaroach_Bomb.h"
#include "syDaroach_TimeBomb.h"
#include "syDaroach_Star.h"
#include "syDarkNebula_Star.h"

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
		if (mTarget != nullptr)
		{
			Destroy(mTarget);
		}
	}

	void Inhale_Effect::Initialize()
	{
		Effects::Initialize();
	}

	void Inhale_Effect::Update()
	{
		// Collider �� �浹�� ��ü�� �÷��̾�� ���� ����� ��ü�� Ÿ������ ����
		SetTarget();

		// �÷��̾� ��ġ���󰡵��� ����
		Player* player = dynamic_cast<Player*>(GetOwner());		

		GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());

		// Target ���� ������Ʈ
		TargetUpdate();				

		DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());

		// defaultKirby �� �ƴϸ� ����
		if (defaultKirby == nullptr)
		{
			Destroy(this);
		}
		else
		{
			// Inhale �̿��� ���¿��� ����
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
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		Star_Effect* star = dynamic_cast<Star_Effect*>(other->GetOwner());
		Daroach_Bomb* daroachbomb = dynamic_cast<Daroach_Bomb*>(other->GetOwner());
		Daroach_TimeBomb* daroachTimebomb = dynamic_cast<Daroach_TimeBomb*>(other->GetOwner());
		Daroach_Star* daroachStar = dynamic_cast<Daroach_Star*>(other->GetOwner());
		DarkNebula_Star* darkNebulaStar = dynamic_cast<DarkNebula_Star*>(other->GetOwner());

		// Ư�� ������Ʈ�� ��� �ν�
		if (abilityStar == nullptr
			&& abilityItem == nullptr
			&& enemy == nullptr
			&& star == nullptr
			&& daroachbomb == nullptr
			&& daroachTimebomb == nullptr
			&& daroachStar == nullptr
			&& darkNebulaStar == nullptr)
			return;

		// ����ó�� 
		// ����� ������Ʈ�� Enemy�ΰ��
		if (enemy != nullptr)
		{
			if (enemy->IsDeadState() || enemy->GetCurHP() <= 0.f)
			{
				return;
			}
		}
		
		if (daroachbomb != nullptr)
		{
			if (daroachbomb->GetDaroachBombState() != eDaroachBombState::Idle)
				return;
		}

		if (daroachTimebomb != nullptr)
		{
			if (daroachTimebomb->GetDaroachTimeBombState() != eDaroachTimeBombState::Idle)
				return;
		}			

		mInhaledObject.push_back(other->GetOwner());
	}

	void Inhale_Effect::SetTarget()
	{
		// Dead������ ������Ʈ�� mInhaledObject���� �����Ѵ�
		for (std::vector<GameObject*>::iterator iter = mInhaledObject.begin()
			; iter != mInhaledObject.end()
			; )
		{
			if ((*iter)->GetGameObjectState() == GameObject::eGameObjectState::Dead)
			{
				GameObject* obj = *iter;
				iter = mInhaledObject.erase(iter);
			}
			else
			{
				iter++;
			}
		}


		Player* player = dynamic_cast<Player*>(GetOwner());
		if (player == nullptr)
			return;

		// ��ó�� ������ ���� �ѹ��� Ÿ�� ����
		if (mTarget != nullptr)
			return;

		// ��� �켱���� 0��° AbilityStar
		for (GameObject* obj : mInhaledObject)
		{
			if (obj == nullptr)
				continue;

			Transform* PlayerTransform = player->GetComponent<Transform>();

			AbilityStar* abilityStar = dynamic_cast<AbilityStar*>(obj);

			// abilityStar�� �ƴϸ� ������������
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

				// Player���� �Ÿ��� ���� obj �� Ÿ������ ����
				if (ObjLen < TargetLen)
				{
					mTarget = abilityStar;
				}
			}
		}

		// AbilityStar�� ã�Ҵٸ� ����
		if (mTarget != nullptr)
			return;


		// ��� �켱���� 1��° AbilityItem
		for (GameObject* obj : mInhaledObject)
		{
			if (obj == nullptr)
				continue;

			Transform* PlayerTransform = player->GetComponent<Transform>();

			AbilityItem* abilityItem = dynamic_cast<AbilityItem*>(obj);

			// AbilityItem�� �ƴϸ� ������������
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

				// Player���� �Ÿ��� ���� obj �� Ÿ������ ����
				if (ObjLen < TargetLen)
				{
					mTarget = abilityItem;
				}
			}
		}

		// AbilityItem�� ã�Ҵٸ� ����
		if (mTarget != nullptr)
			return;

		// ��� �켱���� 2��° Effects
		for (GameObject* obj : mInhaledObject)
		{
			if (obj == nullptr)
				continue;

			Transform* PlayerTransform = player->GetComponent<Transform>();

			// Ư��������Ʈ�� �ν�, Dead ���´� ������������
			Star_Effect* star = dynamic_cast<Star_Effect*>(obj);
			Daroach_Bomb* daroachbomb = dynamic_cast<Daroach_Bomb*>(obj);
			Daroach_TimeBomb* daroachTimebomb = dynamic_cast<Daroach_TimeBomb*>(obj);
			Daroach_Star* daroachStar = dynamic_cast<Daroach_Star*>(obj);
			DarkNebula_Star* darkNebulaStar = dynamic_cast<DarkNebula_Star*>(obj);

			// owner ����
			Effects* owner = nullptr;
			if (star != nullptr)
				owner = star;
			else if (daroachbomb != nullptr)
				owner = daroachbomb;
			else if (daroachTimebomb != nullptr)
				owner = daroachTimebomb;
			else if (daroachStar != nullptr)
				owner = daroachStar;
			else if (darkNebulaStar != nullptr)
				owner = darkNebulaStar;

			if (owner == nullptr || owner->GetGameObjectState() == eGameObjectState::Dead)
				continue;

			if (mTarget == nullptr)
			{
				mTarget = owner;
			}
			else
			{
				Transform* TargetTransform = mTarget->GetComponent<Transform>();
				Transform* objTransform = obj->GetComponent<Transform>();

				float TargetLen = (PlayerTransform->GetPosition() - TargetTransform->GetPosition()).Length();
				float ObjLen = (PlayerTransform->GetPosition() - objTransform->GetPosition()).Length();

				// Player���� �Ÿ��� ���� obj �� Ÿ������ ����
				if (ObjLen < TargetLen)
				{
					mTarget = star;
				}
			}
		}

		// Star_Effect�� ã�Ҵٸ� ����
		if (mTarget != nullptr)
			return;

		// ��� �켱���� 3��° Enemy
		for (GameObject* obj : mInhaledObject)
		{
			if (obj == nullptr)
				continue;

			Transform* PlayerTransform = player->GetComponent<Transform>();

			// Enemy�� �ƴϸ� ������������, Dead ���´� ������������
			Enemy* enemy = dynamic_cast<Enemy*>(obj);
			if (enemy == nullptr
				|| enemy->GetGameObjectState() == eGameObjectState::Dead
				|| enemy->GetCurHP() <= 0.f)
				continue;

			// IceEnemy�� ������������
			Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(obj);
			if (IceEnemy != nullptr)
				continue;

			// BossEnemy�� ������������
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

				// Player���� �Ÿ��� ���� obj �� Ÿ������ ����
				if (ObjLen < TargetLen)
				{
					mTarget = enemy;
				}
			}
		}	

		// Enemy�� ã�Ҵٸ� ����
		if (mTarget != nullptr)
			return;
	}

	void Inhale_Effect::TargetUpdate()
	{
		// Target �� Inhaled ���� ȣ��
		if (mTarget == nullptr || mTarget->GetGameObjectState() == eGameObjectState::Dead)
			return;

		Player* player = dynamic_cast<Player*>(GetOwner());
		DefaultKirby* defaultKirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());

		// defaultKirby �� �ƴϸ� ����
		if (defaultKirby == nullptr)
			return;

		Transform* PlayerTransform = player->GetComponent<Transform>();
		Transform* TargetTransform = mTarget->GetComponent<Transform>();

		Vector2 vecDir = PlayerTransform->GetPosition() - TargetTransform->GetPosition();
		float Len = vecDir.Length();

		// Ư�� �Ÿ� �̳��� �����ϸ� ����
		if (Len < 10.f)
		{
			// Player�� ����� ��ü ���� ����

			AbilityStar* abilityStar = dynamic_cast<AbilityStar*>(mTarget);
			AbilityItem* abilityItem = dynamic_cast<AbilityItem*>(mTarget);

			Star_Effect* star = dynamic_cast<Star_Effect*>(mTarget);
			Daroach_Bomb* daroachbomb = dynamic_cast<Daroach_Bomb*>(mTarget);
			Daroach_TimeBomb* daroachTimebomb = dynamic_cast<Daroach_TimeBomb*>(mTarget);
			Daroach_Star* daroachStar = dynamic_cast<Daroach_Star*>(mTarget);
			DarkNebula_Star* darkNebulaStar = dynamic_cast<DarkNebula_Star*>(mTarget);

			Enemy* enemy = dynamic_cast<Enemy*>(mTarget);

			if (abilityStar != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(abilityStar->GetAbilityType(), sy::InhaledObjectType::AbilityStar);
			}
			else if (abilityItem != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(abilityItem->GetAbilityType(), sy::InhaledObjectType::AbilityItem);
			}
			else if (star != nullptr 
				|| daroachbomb != nullptr
				|| daroachTimebomb != nullptr
				|| daroachStar != nullptr
				|| darkNebulaStar != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(eAbilityType::Normal, sy::InhaledObjectType::Effects);
			}
			else if (enemy != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(enemy->GetAbilityType(), sy::InhaledObjectType::Monster);
			}	

			mbInhale = true;
			Destroy(mTarget);
			mTarget = nullptr;
			Destroy(this);		
		}
		else
		{
			AbilityStar* abilityStar = dynamic_cast<AbilityStar*>(mTarget);
			AbilityItem* abilityItem = dynamic_cast<AbilityItem*>(mTarget);
			Star_Effect* star = dynamic_cast<Star_Effect*>(mTarget);
			Daroach_Bomb* daroachbomb = dynamic_cast<Daroach_Bomb*>(mTarget);
			Daroach_TimeBomb* daroachTimebomb = dynamic_cast<Daroach_TimeBomb*>(mTarget);
			Daroach_Star* daroachStar = dynamic_cast<Daroach_Star*>(mTarget);
			DarkNebula_Star* darkNebulaStar = dynamic_cast<DarkNebula_Star*>(mTarget);
			Enemy* enemy = dynamic_cast<Enemy*>(mTarget);

			// Inhaled ���� ����
			if (abilityStar != nullptr)
			{
				abilityStar->TakeInhaled();
			}
			else if (abilityItem != nullptr)
			{
				abilityItem->TakeInhaled();
			}
			else if (star != nullptr)
			{
				star->TakeInhaled();
			}
			else if (daroachbomb != nullptr)
			{
				daroachbomb->TakeInhaled();
			}
			else if (daroachTimebomb != nullptr)
			{
				daroachTimebomb->TakeInhaled();
			}
			else if (daroachStar != nullptr)
			{
				daroachStar->TakeInhaled();
			}
			else if (darkNebulaStar != nullptr)
			{
				darkNebulaStar->TakeInhaled();
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
