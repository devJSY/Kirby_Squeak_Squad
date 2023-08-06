#include "syIceKirby_Skill.h"
#include "syPlayer.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syAnimator.h"
#include "syIceKirby.h"
#include "syIce_Enemy.h"
#include "syObject.h"

namespace sy
{
	IceKirby_Skill::IceKirby_Skill(Player* owner)
		: Effects(owner)
		, mDir()
	{
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();


		Texture* Ice_Skill_Left_tex = ResourceManager::Load<Texture>(L"Ice_Skill_Left", L"..\\Resources\\Effect\\Ice_Skill_Left.bmp");
		Texture* Ice_Skill_Right_tex = ResourceManager::Load<Texture>(L"Ice_Skill_Right", L"..\\Resources\\Effect\\Ice_Skill_Right.bmp");

		Transform* tr = GetComponent<Transform>();
		Vector2 vec = owner->GetComponent<Transform>()->GetPosition();

		if (mDir == eDirection::RIGHT)
			vec.x += 28.f;
		else
			vec.x -= 18.f;

		tr->SetPosition(vec);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(60.f, 40.f));

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(Ice_Skill_Left_tex, L"Ice_Skill_Left", Vector2(0.f, 0.f), Vector2(110.f, 50.f), Vector2(110.f, 0.f), 0.02f, 12);
		animator->CreateAnimation(Ice_Skill_Right_tex, L"Ice_Skill_Right", Vector2(120.f, 0.f), Vector2(110.f, 50.f), Vector2(110.f, 0.f), 0.03f, 12);

		// ���� ����
		if (mDir == eDirection::RIGHT)
			animator->PlayAnimation(L"Ice_Skill_Right", true);
		else
			animator->PlayAnimation(L"Ice_Skill_Left", true);
	}

	IceKirby_Skill::~IceKirby_Skill()
	{
	}

	void IceKirby_Skill::Initialize()
	{
		Effects::Initialize();
	}

	void IceKirby_Skill::Update()
	{
		// �÷��̾� ��ġ���󰡵��� ����
		Transform* tr = GetComponent<Transform>();
		Vector2 vec = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (mDir == eDirection::RIGHT)
			vec.x += 28.f;
		else
			vec.x -= 18.f;
		tr->SetPosition(vec);


		// IceKirby �� �ƴϸ� ����
		Player* player = dynamic_cast<Player*>(GetOwner());
		IceKirby* iceKirby = dynamic_cast<IceKirby*>(player->GetActiveKirby());
		
		if (iceKirby == nullptr || iceKirby->GetKirbyState() != eIceKirbyState::Skill)
		{
			Destroy(this);
		}

		Effects::Update();
	}

	void IceKirby_Skill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void IceKirby_Skill::OnCollisionEnter(Collider* other)
	{
		// Plyaer�� ����
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
			return;

		// Ice_Enemy �� ����
		Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(other->GetOwner());
		if (IceEnemy != nullptr)
			return;

		// Dead���´� ����
		if (other->GetOwner()->GetGameObjectState() == eGameObjectState::Dead)
			return;

		IceEnemy = new Ice_Enemy(eIceEnemyType::Small);
		object::ActiveSceneAddGameObject(eLayerType::Enemy, IceEnemy);
		IceEnemy->GetComponent<Transform>()->SetPosition(other->GetOwner()->GetComponent<Transform>()->GetPosition());

		Destroy(other->GetOwner());
	}

	void IceKirby_Skill::OnCollisionStay(Collider* other)
	{
	}

	void IceKirby_Skill::OnCollisionExit(Collider* other)
	{
	}
}