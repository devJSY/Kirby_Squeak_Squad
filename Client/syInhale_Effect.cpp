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

		mInhaledObject.push_back(other->GetOwner());
	}

	void Inhale_Effect::SetTarget()
	{
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


		// ��� �켱���� 2��° Enemy
		for (GameObject* obj : mInhaledObject)
		{
			if (obj == nullptr)
				continue;

			Transform* PlayerTransform = player->GetComponent<Transform>();

			// Enemy�� �ƴϸ� ������������
			Enemy* enemy = dynamic_cast<Enemy*>(obj);
			if (enemy == nullptr)
				continue;

			// IceEnemy�� ������������
			Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(obj);
			if (IceEnemy != nullptr)
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
			mbInhale = true;
			Destroy(mTarget);
			Destroy(this);

			// Player�� ����� ��ü ���� ����

			AbilityStar* abilityStar = dynamic_cast<AbilityStar*>(mTarget);
			AbilityItem* abilityItem = dynamic_cast<AbilityItem*>(mTarget);
			Enemy* enemy = dynamic_cast<Enemy*>(mTarget);

			if (abilityStar != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(abilityStar->GetAbilityType(), sy::InhaledObjectType::AbilityStar);
			}
			else if (abilityItem != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(abilityItem->GetAbilityType(), sy::InhaledObjectType::AbilityItem);
			}
			else if (enemy != nullptr)
			{
				defaultKirby->SetInhaledObjectInfo(enemy->GetAbilityType(), sy::InhaledObjectType::Monster);
			}	
		}
		else
		{
			Enemy* enemy = dynamic_cast<Enemy*>(mTarget);
			AbilityItem* abilityItem = dynamic_cast<AbilityItem*>(mTarget);

			// Enemy ���� Block ���� üũ
			if (enemy != nullptr)
			{
				// Enemy ��� Inhaled ���� ����
				enemy->TakeInhaled(vecDir);
			}
			else if (abilityItem != nullptr)
			{
				abilityItem->TakeInhaled();
			}

			vecDir.Normalize();
			vecDir *= 300.f * Time::DeltaTime();
			vecDir += TargetTransform->GetPosition();
			TargetTransform->SetPosition(vecDir);
		}		
	}
}
