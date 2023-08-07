#include "syFireKirby_Skill.h"
#include "syPlayer.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syAnimator.h"
#include "syFireKirby.h"
#include "syObject.h"
#include "syIce_Enemy.h"
#include "sySoundManager.h"
#include "sySound.h"

namespace sy
{
	FireKirby_Skill::FireKirby_Skill(Player* owner)
		: Effects(owner)
		, mDir()
	{
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();

		Texture* Fire_Skill_Left_tex = ResourceManager::Load<Texture>(L"Fire_Skill_Left", L"..\\Resources\\Effect\\Fire_Skill_Left.bmp");
		Texture* Fire_Skill_Right_tex = ResourceManager::Load<Texture>(L"Fire_Skill_Right", L"..\\Resources\\Effect\\Fire_Skill_Right.bmp");

		Transform* tr = GetComponent<Transform>();
		Vector2 vec = owner->GetComponent<Transform>()->GetPosition();

		if (mDir == eDirection::RIGHT)
			vec.x += 48.f;
		else
			vec.x -= 48.f;

		tr->SetPosition(vec);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(60.f, 39.f));

		Animator* animator = GetComponent<Animator>();

		animator->CreateAnimation(Fire_Skill_Left_tex, L"Fire_Skill_Left", Vector2(0.f, 0.f), Vector2(68.f, 39.f), Vector2(68.f, 0.f), 0.03f, 13);
		animator->CreateAnimation(Fire_Skill_Right_tex, L"Fire_Skill_Right", Vector2(816.f, 0.f), Vector2(68.f, 39.f), Vector2(-68.f, 0.f), 0.03f, 13);

		// 방향 설정
		if (mDir == eDirection::RIGHT)
			animator->PlayAnimation(L"Fire_Skill_Right", true);
		else
			animator->PlayAnimation(L"Fire_Skill_Left", true);

		ResourceManager::Load<Sound>(L"FireSkill_Sound", L"..\\Resources\\Sound\\Effect\\FireSkill.wav")->Play(true);
	}

	FireKirby_Skill::~FireKirby_Skill()
	{
	}

	void FireKirby_Skill::Initialize()
	{
		Effects::Initialize();
	}

	void FireKirby_Skill::Update()
	{
		// 플레이어 위치따라가도록 갱신
		Transform* tr = GetComponent<Transform>();
		Vector2 vec = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (mDir == eDirection::RIGHT)
			vec.x += 48.f;
		else
			vec.x -= 48.f;

		tr->SetPosition(vec);


		// fireKirby 가 아니면 삭제
		Player* player = dynamic_cast<Player*>(GetOwner());
		FireKirby* fireKirby = dynamic_cast<FireKirby*>(player->GetActiveKirby());

		if (fireKirby == nullptr || fireKirby->GetKirbyState() != eFireKirbyState::Skill)
		{
			Destroy(this);
			ResourceManager::Find<Sound>(L"FireSkill_Sound")->Stop(true);
		}

		Effects::Update();
	}

	void FireKirby_Skill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void FireKirby_Skill::OnCollisionEnter(Collider* other)
	{
		// Plyaer는 무시
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
			return;

		// Ice_Enemy 는 무시
		Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(other->GetOwner());
		if (IceEnemy != nullptr)
			return;

		// Dead상태는 무시
		if (other->GetOwner()->GetGameObjectState() == eGameObjectState::Dead)
			return;

		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();

		SceneManager::GetPlayer()->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}

	void FireKirby_Skill::OnCollisionStay(Collider* other)
	{
		// Plyaer는 무시
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
			return;

		// Ice_Enemy 는 무시
		Ice_Enemy* IceEnemy = dynamic_cast<Ice_Enemy*>(other->GetOwner());
		if (IceEnemy != nullptr)
			return;

		// Dead, Damage상태는 무시
		if (other->GetOwner()->GetGameObjectState() == eGameObjectState::Dead)
			return;

		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		SceneManager::GetPlayer()->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}
}