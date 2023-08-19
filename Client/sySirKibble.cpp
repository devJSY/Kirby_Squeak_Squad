#include "sySirKibble.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "sySirKibble_Skill.h"
#include "syobject.h"
#include "syTransform.h"
#include "syInput.h"
#include "syCollider.h"
#include "syRigidbody.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"
#include "syTime.h"

namespace sy
{
	SirKibble::SirKibble()
		: Enemy(eAbilityType::Cutter)
		, mState(eSirKibbleState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
		, mAttackDelay(0.f)
	{
	}

	SirKibble::~SirKibble()
	{
	}

	void SirKibble::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemies_Left.bmp");

		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidBody = AddComponent<Rigidbody>();

		mAnimator->CreateAnimation(Enemies_Right, L"SirKibble_Right_Idle", Vector2(3.f, 2582.f), Vector2(23.f, 22.f), Vector2(23.f, 0.f), 0.12f, 5);
		mAnimator->CreateAnimation(Enemies_Left, L"SirKibble_Left_Idle", Vector2(456.f, 2582.f), Vector2(23.f, 22.f), Vector2(-23.f, 0.f), 0.2f, 3);

		mAnimator->CreateAnimation(Enemies_Right, L"SirKibble_Right_Attack", Vector2(2.f, 2632.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 0.2f, 6);
		mAnimator->CreateAnimation(Enemies_Left, L"SirKibble_Left_Attack", Vector2(456.f, 2632.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.2f, 6);

		mAnimator->CreateAnimation(Enemies_Right, L"SirKibble_Right_Jump", Vector2(3.f, 2582.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Enemies_Left, L"SirKibble_Left_Jump", Vector2(456.f, 2582.f), Vector2(24.f, 24.f), Vector2(24.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(Enemies_Right, L"SirKibble_Right_Damage", Vector2(29.f, 2663.f), Vector2(24.f, 20.f), Vector2(24.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Enemies_Left, L"SirKibble_Left_Damage", Vector2(429.f, 2663.f), Vector2(24.f, 20.f), Vector2(-24.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(Monster_Death_Tex, L"SirKibble_Death", Vector2(0.f, 0.f), Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);

		mAnimator->PlayAnimation(L"SirKibble_Right_Idle", true);

		Enemy::Initialize();
	}

	void SirKibble::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// 픽셀충돌 체크
		if (mState != eSirKibbleState::Inhaled)
		{
			CheckPixelCollision();
		}

		switch (mState)
		{
		case eSirKibbleState::Idle:
			Idle();
			break;
		case eSirKibbleState::Attack:
			Attack();
			break;
		case eSirKibbleState::Jump:
			Jump();
			break;
		case eSirKibbleState::Damage:
			Damage();
			break;
		case eSirKibbleState::Dead:
			Dead();
			break;
		case eSirKibbleState::Inhaled:
			Inhaled();
			break;
		default:
			break;
		}

		Enemy::Update();
	}

	void SirKibble::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void SirKibble::OnCollisionEnter(Collider* other)
	{
		if (mState == eSirKibbleState::Dead 
			|| mState == eSirKibbleState::Inhaled
			|| GetCurHP() <= 0.f)
			return;

		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player == nullptr)
			return;

		// Inhale 상태에선 무시
		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
		if (kirby != nullptr)
		{
			if (kirby->GetKirbyState() == eDefaultKirbyState::Inhale_1 || kirby->GetKirbyState() == eDefaultKirbyState::Inhale_2)
				return;

			// DefaultKirby가 Damage 상태면 적용하지않음
			if (kirby->IsDamagedState())
				return;
		}

		// 몬스터 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		player->TakeHit(10, Dir);
	}

	void SirKibble::OnCollisionStay(Collider* other)
	{
	}

	void SirKibble::OnCollisionExit(Collider* other)
	{
	}

	void SirKibble::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		Damaged(DamageAmount);

		// 이미 데미지 상태면 애니메이션, 피격 넉백 처리하지않음
		if (mState == eSirKibbleState::Damage || mState == eSirKibbleState::Dead)
			return;

		mState = eSirKibbleState::Damage;

		if (HitDir != Vector2::Zero)
		{
			HitDir.Normalize();
			HitDir *= 30.f;
			mRigidBody->SetVelocity(HitDir);
		}

		if (HitDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"SirKibble_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"SirKibble_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void SirKibble::TakeInhaled(math::Vector2 InhaleDir)
	{
		if (mState == eSirKibbleState::Dead)
			return;

		mState = eSirKibbleState::Inhaled;

		if (InhaleDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"SirKibble_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"SirKibble_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void SirKibble::CheckPixelCollision()
	{
		std::wstring CurSceneName = SceneManager::GetActiveScene()->GetName();

		Texture* PixelTex = nullptr;

		// Stage타입에따라 픽셀텍스쳐 변경하기
		if (CurSceneName == L"AbilityTestScene")
			PixelTex = ResourceManager::Find<Texture>(L"AbilityTest_Pixel");
		else if (CurSceneName == L"Level1_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"King_Dedede_Stage_Pixel");
		else if (CurSceneName == L"Level6_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"Daroach_Pixel");
		else if (CurSceneName == L"Level8_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"DarkNebula_Pixel");
		else
			PixelTex = ResourceManager::Find<Texture>(L"Stage1_Pixel");

		if (PixelTex == nullptr)
			return;

		// Offset 픽셀 좌상단위치 설정
		Vector2 offset = Vector2::Zero;

		if (CurSceneName == L"AbilityTestScene"
			|| CurSceneName == L"King_Dedede_Stage_Pixel"
			|| CurSceneName == L"Daroach_Pixel"
			|| CurSceneName == L"DarkNebula_Pixel"
			|| CurSceneName == L"Level1_Stage1Scene")
		{
			offset = Vector2::Zero;
		}
		else if (CurSceneName == L"Level1_Stage2Scene")
		{
			offset = Vector2(0, 347.f);
		}
		else if (CurSceneName == L"Level1_Stage3Scene")
		{
			offset = Vector2(0, 679.f);
		}
		else if (CurSceneName == L"Level1_Stage4Scene")
		{
			offset = Vector2(1603.f, 137.f);
		}

		Collider* col = GetComponent<Collider>();
		Vector2 ColPos = col->GetPosition();
		Vector2 ColSize = col->GetSize();

		Vector2 LT = Vector2(ColPos.x - (ColSize.x / 2.f), ColPos.y - (ColSize.y / 2.f));
		Vector2 RT = Vector2(ColPos.x + (ColSize.x / 2.f), ColPos.y - (ColSize.y / 2.f));
		Vector2 LB = Vector2(ColPos.x - (ColSize.x / 2.f), ColPos.y + (ColSize.y / 2.f));
		Vector2 RB = Vector2(ColPos.x + (ColSize.x / 2.f), ColPos.y + (ColSize.y / 2.f));

		LT += offset;
		RT += offset;
		LB += offset;
		RB += offset;

		COLORREF LTColor = PixelTex->GetTexturePixel((int)LT.x, (int)LT.y);
		COLORREF RTColor = PixelTex->GetTexturePixel((int)RT.x, (int)RT.y);
		COLORREF LBColor = PixelTex->GetTexturePixel((int)LB.x, (int)LB.y);
		COLORREF RBColor = PixelTex->GetTexturePixel((int)RB.x, (int)RB.y);


		// 바닥 처리
		if (LBColor == RGB(0, 0, 255) || RBColor == RGB(0, 0, 255)
			|| LBColor == RGB(255, 0, 0) || RBColor == RGB(255, 0, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.y -= 1.f;
			mTransform->SetPosition(pos);
			mRigidBody->SetGround(true);
		}

		COLORREF LBColorOffsetY = PixelTex->GetTexturePixel((int)LB.x, int(LB.y + 1));
		COLORREF RBColorOffsetY = PixelTex->GetTexturePixel((int)RB.x, int(RB.y + 1));

		// 바닥 ~ 바닥 + 1픽셀 범위가 아닐경우 Ground false 처리
		if (!(LBColor == RGB(0, 0, 255) || LBColorOffsetY == RGB(0, 0, 255)
			|| RBColor == RGB(0, 0, 255) || RBColorOffsetY == RGB(0, 0, 255)
			|| LBColor == RGB(255, 0, 0) || LBColorOffsetY == RGB(255, 0, 0)
			|| RBColor == RGB(255, 0, 0) || RBColorOffsetY == RGB(255, 0, 0)))
		{
			mRigidBody->SetGround(false);
		}


		// Right Stop Check
		COLORREF RBColorOffsetX = PixelTex->GetTexturePixel(int(RB.x + 1), (int)RB.y);

		if (RBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 1.f;
			mTransform->SetPosition(pos);
		}
		else if (RBColorOffsetX == RGB(0, 255, 0))
		{
			// 한 픽셀 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 3.f;
			mTransform->SetPosition(pos);

			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
		}

		// Left Stop Check
		COLORREF LBColorOffsetX = PixelTex->GetTexturePixel(int(LB.x - 1), (int)LB.y);

		if (LBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x += 3.f;
			mTransform->SetPosition(pos);
		}
		else if (LBColorOffsetX == RGB(0, 255, 0))
		{
			// 한 픽셀 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 1.f;
			mTransform->SetPosition(pos);

			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
		}
	}

	void SirKibble::Idle()
	{
		if (GetCurHP() <= 0.f)
		{
			mAnimator->PlayAnimation(L"SirKibble_Death", false);
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mState = eSirKibbleState::Dead;
		}

		mAttackDelay += Time::DeltaTime();

		// 특정 조건일때 스킬 생성
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 distance = PlayerPos - mTransform->GetPosition();
		float Len = distance.Length();

		if (Len < 100.f && mAttackDelay > 1.f)
		{
			if (PlayerPos.x > mTransform->GetPosition().x)
				mDir = eDirection::RIGHT;
			else
				mDir = eDirection::LEFT;

			mTransform->SetDirection(mDir);

			SirKibble_Skill* skill = new SirKibble_Skill(this);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Effect, skill);

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SirKibble_Right_Attack", false);
			else
				mAnimator->PlayAnimation(L"SirKibble_Left_Attack", false);

			mState = eSirKibbleState::Attack;
			mAttackDelay = 0.f;
		}
	}

	void SirKibble::Attack()
	{
		static float time = 0.f;

		time += Time::DeltaTime();

		if (GetCurHP() <= 0.f)
		{
			mAnimator->PlayAnimation(L"SirKibble_Death", false);
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mState = eSirKibbleState::Dead;
			time = 0.f;
		}	

		if (mAnimator->IsActiveAnimationComplete() && time > 2.f)
		{
			if (mDir == eDirection::RIGHT)
			{
				mAnimator->PlayAnimation(L"SirKibble_Right_Idle", true);
			}
			else
			{
				mAnimator->PlayAnimation(L"SirKibble_Left_Idle", true);
			}

			mState = eSirKibbleState::Idle;
			time = 0.f;
		}
	}

	void SirKibble::Jump()
	{
		if (GetCurHP() <= 0.f)
		{
			mAnimator->PlayAnimation(L"SirKibble_Death", false);
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mState = eSirKibbleState::Dead;
		}
	}

	void SirKibble::Damage()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (GetCurHP() <= 0.f)
			{
				mAnimator->PlayAnimation(L"SirKibble_Death", false);
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
				mState = eSirKibbleState::Dead;
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"SirKibble_Right_Idle", true);
				else
					mAnimator->PlayAnimation(L"SirKibble_Left_Idle", true);
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
				mState = eSirKibbleState::Idle;
			}
		}
	}

	void SirKibble::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void SirKibble::Inhaled()
	{
		mRigidBody->SetGround(true);

		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"SirKibble_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"SirKibble_Left_Idle", true);
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mState = eSirKibbleState::Idle;
		}
	}
}