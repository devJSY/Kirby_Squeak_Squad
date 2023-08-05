#include "syInhale_Effect.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syEnemy.h"
#include "syTime.h"
#include "syDefaultKirby.h"
#include "syIce.h"
#include "syPlayer.h"

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
		// Collider �� �浹�� ��ü�� �÷��̾�� ���� ����� ��ü�� Ÿ������ ����
		SetTarget();

		// �÷��̾� ��ġ���󰡵��� ����
		DefaultKirby* player = dynamic_cast<DefaultKirby*>(GetOwner());		
		GetComponent<Transform>()->SetPosition(player->GetComponent<Transform>()->GetPosition());		

		// Target ���� ������Ʈ
		TargetUpdate();		

		// Inhale �̿��� ���¿��� ����
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

	void Inhale_Effect::SetTarget()
	{
		DefaultKirby* player = dynamic_cast<DefaultKirby*>(GetOwner());
		if (player == nullptr)
			return;

		// ��ó�� ������ ���� �ѹ��� Ÿ�� ����
		if (mTarget == nullptr)
			return;


		for (GameObject* obj : mInhaledObject)
		{
			if (obj == nullptr)
				continue;

			Transform* PlayerTransform = player->GetComponent<Transform>();

			Enemy* enemy = dynamic_cast<Enemy*>(obj);

			// Enemy�� �ƴϸ� ������������
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

				// Player���� �Ÿ��� ���� obj �� Ÿ������ ����
				if (ObjLen < TargetLen)
				{
					mTarget = enemy;
				}
			}
		}		
	}

	void Inhale_Effect::TargetUpdate()
	{
		// Target �� Inhaled ���� ȣ��
		if (mTarget == nullptr)
			return;

		DefaultKirby* player = dynamic_cast<DefaultKirby*>(GetOwner());

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
		}
		else
		{
			Enemy* enemy = dynamic_cast<Enemy*>(mTarget);

			// Enemy ���� Block ���� üũ
			if (enemy != nullptr)
			{
				// Enemy ��� Inhaled ���� ����
				enemy->TakeInhaled(vecDir);
			}

			vecDir.Normalize();
			vecDir *= 300.f * Time::DeltaTime();
			vecDir += TargetTransform->GetPosition();
			TargetTransform->SetPosition(vecDir);
		}		
	}
}
