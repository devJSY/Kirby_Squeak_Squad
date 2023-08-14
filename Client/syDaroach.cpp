#include "syDaroach.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syCollider.h"
#include "sySound.h"

namespace sy
{
	Daroach::Daroach(eAbilityType type)
		: Enemy(type)
		, mState(eDaroachState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mCollider(nullptr)
		, mDir(eDirection::LEFT)
		, mStateChangeDelay(0.f)
	{
	}

	Daroach::~Daroach()
	{
	}

	void Daroach::Initialize()
	{
		// 체력 설정
		SetHP(500);

		// 텍스쳐 로드
		Texture* Daroach_Right_Tex = ResourceManager::Load<Texture>(L"KingDedede_Right_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Right.bmp");
		Texture* Daroach_Left_Tex = ResourceManager::Load<Texture>(L"KingDedede_Left_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Left.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidBody = AddComponent<Rigidbody>();
		mCollider = GetComponent<Collider>();
		mCollider->SetSize(Vector2(40.f, 40.f));
		//mCollider->SetOffset(Vector2(0.f, 0.f));


			// 애니메이션 생성
		std::vector<Vector2> Daroach_StarAttack_offset = { Vector2(0.f,5.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,0.f), Vector2(0.f,21.f), Vector2(0.f,26.f), Vector2(0.f, 26.f) };

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_Idle", Vector2(8.f, 15.f), Vector2(55.f, 56.f), Vector2(55.f, 0.f), 0.15f, 4);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_Idle", Vector2(757.f, 15.f), Vector2(55.f, 56.f), Vector2(-55.f, 0.f), 0.15f, 4);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_Prepare", Vector2(236.f, 86.f), Vector2(51.f, 55.f), Vector2(51.f, 0.f), 0.15f, 2);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_Prepare", Vector2(533.f, 86.f), Vector2(51.f, 55.f), Vector2(-51.f, 0.f), 0.15f, 2);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_WandUp", Vector2(4.f, 229.f), Vector2(89.f, 86.f), Vector2(89.f, 0.f), 0.1f, 3);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_WandUp", Vector2(727.f, 229.f), Vector2(89.f, 86.f), Vector2(-89.f, 0.f), 0.1f, 3);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_WandCharge", Vector2(289.f, 231.f), Vector2(55.f, 83.f), Vector2(55.f, 0.f), 0.2f, 2);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_WandCharge", Vector2(476.f, 231.f), Vector2(55.f, 83.f), Vector2(-55.f, 0.f), 0.2f, 2);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_WandAttack", Vector2(444.f, 257.f), Vector2(64.f, 53.f), Vector2(64.f, 0.f), 0.2f, 2);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_WandAttack", Vector2(312.f, 257.f), Vector2(64.f, 53.f), Vector2(-64.f, 0.f), 0.2f, 2);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_BombAttack", Vector2(486.f, 88.f), Vector2(70.f, 55.f), Vector2(70.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_BombAttack", Vector2(264.f, 88.f), Vector2(70.f, 55.f), Vector2(-70.f, 0.f), 0.1f, 4);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_Teleport", Vector2(273.f, 3.f), Vector2(60.f, 70.f), Vector2(60.f, 0.f), 0.1f, 3);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_Teleport", Vector2(487.f, 3.f), Vector2(60.f, 70.f), Vector2(-60.f, 0.f), 0.1f, 3);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_TeleportEnd", Vector2(393.f, 3.f), Vector2(60.f, 70.f), Vector2(-60.f, 0.f), 0.1f, 3);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_TeleportEnd", Vector2(367.f, 3.f), Vector2(60.f, 70.f), Vector2(60.f, 0.f), 0.1f, 3);

		mAnimator->CreateAnimation_Offset(Daroach_Right_Tex, L"Daroach_Right_StarAttack", Vector2(1.f, 381.f), Vector2(100.f, 89.f), Vector2(100.f, 0.f), 0.1f, 8, Daroach_StarAttack_offset);
		mAnimator->CreateAnimation_Offset(Daroach_Left_Tex, L"Daroach_Left_StarAttack", Vector2(719.f, 381.f), Vector2(100.f, 89.f), Vector2(-100.f, 0.f), 0.1f, 8, Daroach_StarAttack_offset);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_Death", Vector2(170.f, 152.f), Vector2(71.f, 56.f), Vector2(71.f, 0.f), 2.5f, 1);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_Death", Vector2(579.f, 152.f), Vector2(71.f, 56.f), Vector2(-71.f, 0.f), 2.5f, 1);

		mAnimator->CreateAnimation(Daroach_Right_Tex, L"Daroach_Right_End", Vector2(252.f, 159.f), Vector2(61.f, 44.f), Vector2(61.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Daroach_Left_Tex, L"Daroach_Left_End", Vector2(507.f, 159.f), Vector2(61.f, 44.f), Vector2(-61.f, 0.f), 1.f, 1);

		mAnimator->SetAffectedCamera(true);
		mAnimator->PlayAnimation(L"Daroach_Right_Idle", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"Daroach_Teleport", L"..\\Resources\\Sound\\Effect\\Daroach\\Teleport.wav");


		Enemy::Initialize();
	}

	void Daroach::Update()
	{
		Enemy::Update();
	}

	void Daroach::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void Daroach::OnCollisionEnter(Collider* other)
	{
	}

	void Daroach::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
	}

	void Daroach::CheckPixelCollision()
	{
	}

	void Daroach::AddStarEffect(eDirection dir)
	{
	}

	void Daroach::Idle()
	{
	}

	void Daroach::Prepare()
	{
	}

	void Daroach::WandUp()
	{
	}

	void Daroach::WandCharge()
	{
	}

	void Daroach::WandAttack()
	{
	}

	void Daroach::BoomAttack()
	{
	}

	void Daroach::Teleport()
	{
	}

	void Daroach::TeleportEnd()
	{
	}

	void Daroach::StarAttack()
	{
	}

	void Daroach::Damage()
	{
	}

	void Daroach::Dead()
	{
	}
}