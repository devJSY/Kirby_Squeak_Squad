#include "syHotHead.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syHotHead_Fire.h"
#include "syobject.h"
#include "syTransform.h"
#include "syInput.h"
#include "syRigidbody.h"
#include "syCollider.h"
#include "syTime.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"


namespace sy
{
	HotHead::HotHead()
		: Enemy(eAbilityType::Fire)
		, mState(eHotHeadState::Walk)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDirDuration(0.f)
		, mDir(eDirection::RIGHT)
		, mAttackDelay(0.f)
	{
	}

	HotHead::~HotHead()
	{
	}

	void HotHead::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemy\\Enemies_Left.bmp");

		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");
		
		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidBody = AddComponent<Rigidbody>();

		mAnimator->CreateAnimation(Enemies_Right, L"HotHead_Right_Walk", Vector2(0.f, 3260.f), Vector2(22.f, 21.f), Vector2(22.f, 0.f), 0.18f, 8);
		mAnimator->CreateAnimation(Enemies_Left, L"HotHead_Left_Walk", Vector2(460.f, 3260.f), Vector2(22.f, 21.f), Vector2(-22.f, 0.f), 0.18f, 8);

		mAnimator->CreateAnimation(Enemies_Right, L"HotHead_Right_Damage", Vector2(0.f, 3350.f), Vector2(23.f, 21.f), Vector2(23.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Enemies_Left, L"HotHead_Left_Damage", Vector2(459.f, 3350.f), Vector2(23.f, 21.f), Vector2(-23.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(Enemies_Right, L"HotHead_Right_Attack", Vector2(8.f, 3284.f), Vector2(24.f, 21.f), Vector2(24.f, 0.f), 0.2f, 3);
		mAnimator->CreateAnimation(Enemies_Left, L"HotHead_Left_Attack", Vector2(450.f, 3284.f), Vector2(24.f, 21.f), Vector2(-24.f, 0.f), 0.2f, 3);

		mAnimator->CreateAnimation(Monster_Death_Tex, L"HotHead_Death", Vector2(0.f, 0.f), Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);

		mAnimator->PlayAnimation(L"HotHead_Right_Walk", true);

		Enemy::Initialize();
	}

	void HotHead::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// 픽셀충돌 체크
		if (mState != eHotHeadState::Inhaled)
		{
			CheckPixelCollision();
		}

		switch (mState)
		{
		case eHotHeadState::Walk:
			Walk();
			break;
		case eHotHeadState::Attack:
			Attack();
			break;
		case eHotHeadState::Damage:
			Damage();
			break;
		case eHotHeadState::Dead:
			Dead();
			break;
		case eHotHeadState::Inhaled:
			Inhaled();
			break;
		default:
			break;
		}

		Enemy::Update();
	}

	void HotHead::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void HotHead::OnCollisionEnter(Collider* other)
	{
		if (mState == eHotHeadState::Dead 
			|| mState == eHotHeadState::Inhaled 
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
		}

		// 몬스터 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		player->TakeHit(10, Dir);
	}

	void HotHead::OnCollisionStay(Collider* other)
	{
	}

	void HotHead::OnCollisionExit(Collider* other)
	{
	}

	void HotHead::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		Damaged(DamageAmount);

		// 이미 데미지 상태면 애니메이션, 피격 넉백 처리하지않음
		if (mState == eHotHeadState::Damage || mState == eHotHeadState::Dead)
			return;

		mState = eHotHeadState::Damage;

		if (HitDir != Vector2::Zero)
		{
			HitDir.Normalize();
			HitDir *= 30.f;
			mRigidBody->SetVelocity(HitDir);
		}

		if (HitDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"HotHead_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"HotHead_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void HotHead::TakeInhaled(math::Vector2 InhaleDir)
	{
		if (mState == eHotHeadState::Dead)
			return;

		mState = eHotHeadState::Inhaled;

		if (InhaleDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"HotHead_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"HotHead_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void HotHead::CheckPixelCollision()
	{
		std::wstring CurSceneName = SceneManager::GetActiveScene()->GetName();

		Texture* PixelTex = nullptr;

		// Stage타입에따라 픽셀텍스쳐 변경하기
		if (CurSceneName == L"AbilityTestScene")
			PixelTex = ResourceManager::Find<Texture>(L"AbilityTest_Pixel");
		else if (CurSceneName == L"Level1_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"King_Dedede_Stage_Pixel");
		else
			PixelTex = ResourceManager::Find<Texture>(L"Stage1_Pixel");

		if (PixelTex == nullptr)
			return;

		// Offset 픽셀 좌상단위치 설정
		Vector2 offset = Vector2::Zero;

		if (CurSceneName == L"AbilityTestScene"
			|| CurSceneName == L"King_Dedede_Stage_Pixel"
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
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 3.f;
			mTransform->SetPosition(pos);

			if (mDir == eDirection::RIGHT)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"HotHead_Left_Walk", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"HotHead_Right_Walk", true);
			}

			mState = eHotHeadState::Walk;
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mDirDuration = 0.f;
		}

		// Left Stop Check
		COLORREF LBColorOffsetX = PixelTex->GetTexturePixel(int(LB.x - 1), (int)LB.y);

		if (LBColor == RGB(0, 255, 0))
		{
			// 이동
			Vector2 pos = mTransform->GetPosition();
			pos.x += 1.f;
			mTransform->SetPosition(pos);
		}
		else if (LBColorOffsetX == RGB(0, 255, 0))
		{
			Vector2 pos = mTransform->GetPosition();
			pos.x += 3.f;
			mTransform->SetPosition(pos);

			if (mDir == eDirection::RIGHT)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"HotHead_Left_Walk", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"HotHead_Right_Walk", true);
			}

			mState = eHotHeadState::Walk;
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mDirDuration = 0.f;
		}
	}

	void HotHead::Walk()
	{
		if (GetCurHP() <= 0.f)
		{
			mAnimator->PlayAnimation(L"HotHead_Death", false);
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mState = eHotHeadState::Dead;
		}

		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();
		if (mDir == eDirection::RIGHT)
			pos.x += 30.f * Time::DeltaTime();
		else
			pos.x -= 30.f * Time::DeltaTime();
		mTransform->SetPosition(pos);

		mDirDuration += Time::DeltaTime();
		mAttackDelay += Time::DeltaTime();

		// 일정시간 이후 방향 변경
		if (mDirDuration > 3.f)
		{
			if (mDir == eDirection::RIGHT)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"HotHead_Left_Walk", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"HotHead_Right_Walk", true);
			}

			mDirDuration = 0.f;
		}



		// 특정 조건일때 스킬 생성
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 distance = PlayerPos - mTransform->GetPosition();
		float Len = distance.Length();
				
		if (Len < 50.f && mAttackDelay > 1.f)
		{
			if (PlayerPos.x > mTransform->GetPosition().x)
				mDir = eDirection::RIGHT;
			else 
				mDir = eDirection::LEFT;

			mTransform->SetDirection(mDir);

			HotHead_Fire* Fire = new HotHead_Fire(this);
			SceneManager::GetActiveScene()->AddGameObject(eLayerType::Effect, Fire);

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"HotHead_Right_Attack", false);
			else
				mAnimator->PlayAnimation(L"HotHead_Left_Attack", false);

			mState = eHotHeadState::Attack;
			mDirDuration = 0.f;
			mAttackDelay = 0.f;
		}
	}

	void HotHead::Attack()
	{
		static float time = 0.f;

		time += Time::DeltaTime();

		if (GetCurHP() <= 0.f)
		{
			mAnimator->PlayAnimation(L"HotHead_Death", false);
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mState = eHotHeadState::Dead;

			time = 0.f;
		}

		if (mAnimator->IsActiveAnimationComplete() && time > 2.f)
		{
			if (mDir == eDirection::RIGHT)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"HotHead_Left_Walk", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"HotHead_Right_Walk", true);
			}

			mState = eHotHeadState::Walk;
			time = 0.f;
		}
	}

	void HotHead::Damage()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (GetCurHP() <= 0.f)
			{
				mAnimator->PlayAnimation(L"HotHead_Death", false);
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
				mState = eHotHeadState::Dead;
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"HotHead_Right_Walk", true);
				else
					mAnimator->PlayAnimation(L"HotHead_Left_Walk", true);

				mRigidBody->SetVelocity(Vector2(0.f, 0.f));

				mState = eHotHeadState::Walk;
			}
		}
	}

	void HotHead::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void HotHead::Inhaled()
	{
		mRigidBody->SetGround(true);

		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"HotHead_Right_Walk", true);
			else
				mAnimator->PlayAnimation(L"HotHead_Left_Walk", true);

			mRigidBody->SetVelocity(Vector2(0.f, 0.f));

			mState = eHotHeadState::Walk;
		}
	}
}