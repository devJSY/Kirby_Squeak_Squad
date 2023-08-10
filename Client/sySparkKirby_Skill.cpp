#include "sySparkKirby_Skill.h"
#include "syPlayer.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syAnimator.h"
#include "sySparkKirby.h"
#include "syObject.h"
#include "syIce_Enemy.h"
#include "sySoundManager.h"
#include "sySound.h"

namespace sy
{
	SparkKirby_Skill::SparkKirby_Skill(Player* owner)
		: Effects(owner)
		, mDir()
	{
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();

		// 텍스쳐 로드
		Texture* SparkKirby_Right = ResourceManager::Load<Texture>(L"SparkKirby_Right_Tex", L"..\\Resources\\Kirby\\SparkKirby\\SparkKirby_Right.bmp");
		Texture* SparkKirby_Left = ResourceManager::Load<Texture>(L"SparkKirby_Left_Tex", L"..\\Resources\\Kirby\\SparkKirby\\SparkKirby_Left.bmp");

		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(owner->GetComponent<Transform>()->GetPosition());

		Collider* col = AddComponent<Collider>();
		col->SetColliderType(eColliderType::Sphere);
		col->SetRadius(30.f);

		Animator* animator = GetComponent<Animator>();

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, 10.f);
		animator->CreateAnimation(SparkKirby_Right, L"Spark_Right_Skill", Vector2(0.f, 3584.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.03f, 4, Animationoffset);
		animator->CreateAnimation(SparkKirby_Left, L"Spark_Left_Skill", Vector2(0.f, 3584.f), Vector2(256.f, 256.f), Vector2(256.f, 0.f), 0.03f, 4, Animationoffset);

		// 방향 설정
		if (mDir == eDirection::RIGHT)
			animator->PlayAnimation(L"Spark_Right_Skill", true);
		else
			animator->PlayAnimation(L"Spark_Left_Skill", true);

		ResourceManager::Load<Sound>(L"SparkSound", L"..\\Resources\\Sound\\Effect\\Spark.wav")->Play(true);
		ResourceManager::Load<Sound>(L"Spark2Sound", L"..\\Resources\\Sound\\Effect\\Spark_2.wav");
	}

	SparkKirby_Skill::~SparkKirby_Skill()
	{
	}

	void SparkKirby_Skill::Initialize()
	{
		Effects::Initialize();
	}

	void SparkKirby_Skill::Update()
	{
		// 플레이어 위치따라가도록 갱신
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		// SparkKirby 가 아니면 삭제
		Player* player = dynamic_cast<Player*>(GetOwner());
		SparkKirby* sparkKirby = dynamic_cast<SparkKirby*>(player->GetActiveKirby());

		if (sparkKirby == nullptr || sparkKirby->GetKirbyState() != eSparkKirbyState::Skill)
		{
			Destroy(this);
			ResourceManager::Find<Sound>(L"SparkSound")->Stop(true);
		}

		Effects::Update();
	}

	void SparkKirby_Skill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void SparkKirby_Skill::OnCollisionEnter(Collider* other)
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
		if (enemy == nullptr)
			return;

		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();

		SceneManager::GetPlayer()->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}

	void SparkKirby_Skill::OnCollisionStay(Collider* other)
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
		if (enemy == nullptr)
			return;

		// Stay상태에서 Damage 상태면 적용하지않음
		if (enemy->IsDamagedState())
			return;

		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		SceneManager::GetPlayer()->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	}
}