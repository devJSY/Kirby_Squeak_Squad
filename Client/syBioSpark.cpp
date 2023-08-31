#include "syBioSpark.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syobject.h"
#include "syTransform.h"
#include "syInput.h"
#include "syRigidbody.h"
#include "syCollider.h"
#include "syTime.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"
#include "sySound.h"
#include "syBioSpark_Shuriken.h"
#include "syBioSpark_AttackArea.h"

namespace sy
{
	BioSpark::BioSpark()
		: Enemy(eAbilityType::Ninja)
		, mState(eBioSparkState::Hide)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::LEFT)
		, mStateChangeDelay(0.f)
	{
	}

	BioSpark::~BioSpark()
	{
	}

	void BioSpark::Initialize()
	{
		Texture* BioSpark_Tex = ResourceManager::Load<Texture>(L"BioSpark_Tex", L"..\\Resources\\Enemy\\BioSpark\\BioSpark.bmp");
		BioSpark_Tex->SetScale(Vector2(0.3f, 0.3f));

		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidBody = AddComponent<Rigidbody>();

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(3.f, 5.f);

		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Right_Idle", Vector2::Zero, Vector2(180.f, 180.f), Vector2(180.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Left_Idle", Vector2(0.f, 1440.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Right_ThrowShuriken", Vector2(0.f, 360.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 0.3f, 2);
		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Left_ThrowShuriken", Vector2(0.f, 1800.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 0.3f, 2);

		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Right_Hide", Vector2(0.f, 540.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Left_Hide", Vector2(0.f, 1980.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 1.f, 1, Animationoffset);

		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Right_Appear", Vector2(0.f, 720.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 0.1f, 3, Animationoffset);
		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Left_Appear", Vector2(0.f, 2160.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 0.1f, 3, Animationoffset);

		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Right_Hiding", Vector2(0.f, 900.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 0.1f, 4, Animationoffset);
		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Left_Hiding", Vector2(0.f, 2340.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 0.1f, 4, Animationoffset);

		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Right_Attack", Vector2(0.f, 1080.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 0.1f, 4);
		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Left_Attack", Vector2(0.f, 2520.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 0.1f, 4);

		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Right_Damage", Vector2(0.f, 1260.f), Vector2(180.f, 180.f), Vector2(180.f, 0.f), 0.1f, 2);
		mAnimator->CreateAnimation(BioSpark_Tex, L"BioSpark_Left_Damage", Vector2(0.f, 2700.f), Vector2(180.f, 173.f), Vector2(180.f, 0.f), 0.1f, 2);

		mAnimator->CreateAnimation(Monster_Death_Tex, L"BioSpark_Death", Vector2::Zero, Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);

		if(mDir == eDirection::RIGHT)
			mAnimator->PlayAnimation(L"BioSpark_Right_Hide", true);
		else
			mAnimator->PlayAnimation(L"BioSpark_Left_Hide", true);

		Enemy::Initialize();
	}

	void BioSpark::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// 픽셀충돌 체크
		if (mState != eBioSparkState::Inhaled)
		{
			CheckPixelCollision();
		}

		switch (mState)
		{
		case eBioSparkState::Idle:
			Idle();
			break;
		case eBioSparkState::ThrowShuriken:
			ThrowShuriken();
			break;
		case eBioSparkState::Hide:
			Hide();
			break;
		case eBioSparkState::Appear:
			Appear();
			break;
		case eBioSparkState::Hiding:
			Hiding();
			break;
		case eBioSparkState::Attack:
			Attack();
			break;
		case eBioSparkState::Damage:
			Damage();
			break;
		case eBioSparkState::Dead:
			Dead();
			break;
		case eBioSparkState::Inhaled:
			Inhaled();
			break;
		}		

		Enemy::Update();
	}

	void BioSpark::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void BioSpark::OnCollisionEnter(Collider* other)
	{
		if (mState == eBioSparkState::Dead
			|| mState == eBioSparkState::Inhaled)
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

	void BioSpark::OnCollisionStay(Collider* other)
	{
	}

	void BioSpark::OnCollisionExit(Collider* other)
	{
	}

	void BioSpark::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		Damaged(DamageAmount);

		// 이미 데미지 상태면 애니메이션, 피격 넉백 처리하지않음
		if (mState == eBioSparkState::Damage || mState == eBioSparkState::Dead)
			return;

		mState = eBioSparkState::Damage;

		if (HitDir != Vector2::Zero)
		{
			HitDir.Normalize();
			HitDir *= 30.f;
			mRigidBody->SetVelocity(HitDir);
		}

		if (HitDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"BioSpark_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"BioSpark_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void BioSpark::TakeInhaled(math::Vector2 InhaleDir)
	{
		if (mState == eBioSparkState::Dead)
			return;

		mState = eBioSparkState::Inhaled;

		if (InhaleDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"BioSpark_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"BioSpark_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void BioSpark::CheckPixelCollision()
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
		else if (CurSceneName == L"Level7_BossScene")
			PixelTex = ResourceManager::Find<Texture>(L"Meta_Knight_Pixel");
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
			|| CurSceneName == L"Meta_Knight_Pixel"
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
			pos.x += 1.f;
			mTransform->SetPosition(pos);
		}
		else if (LBColorOffsetX == RGB(0, 255, 0))
		{
			Vector2 pos = mTransform->GetPosition();
			pos.x += 3.f;
			mTransform->SetPosition(pos);

			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
		}
	}

	void BioSpark::Idle()
	{
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 3.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"BioSpark_Right_Hiding", false);
			else
				mAnimator->PlayAnimation(L"BioSpark_Left_Hiding", false);

			mState = eBioSparkState::Hiding;
			mStateChangeDelay = 0.f;
		}

		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 distance = PlayerPos - mTransform->GetPosition();
		float Len = distance.Length();
		if (fabs(distance.x) < 30.f
			&& fabs(distance.y) < 30.f
			&& mStateChangeDelay > 1.f)
		{
			if (PlayerPos.x > mTransform->GetPosition().x)
				mDir = eDirection::RIGHT;
			else
				mDir = eDirection::LEFT;

			mTransform->SetDirection(mDir);

			if (mDir == eDirection::RIGHT)			
				mAnimator->PlayAnimation(L"BioSpark_Right_Attack", false);			
			else
				mAnimator->PlayAnimation(L"BioSpark_Left_Attack", false);			

			BioSpark_AttackArea* AttackArea = new BioSpark_AttackArea(this);
			object::ActiveSceneAddGameObject(eLayerType::Effect, AttackArea);

			mState = eBioSparkState::Attack;
			mStateChangeDelay = 0.f;	
		}
	}

	void BioSpark::ThrowShuriken()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"BioSpark_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"BioSpark_Left_Idle", true);

			mState = eBioSparkState::Idle;
			mStateChangeDelay = 0.f;
		}
	}

	void BioSpark::Hide()
	{
		mStateChangeDelay += Time::DeltaTime();

		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		Vector2 distance = PlayerPos - mTransform->GetPosition();
		float Len = distance.Length();

		if (fabs(distance.x) < 100.f 
			&& fabs(distance.y) < 30.f
			&& mStateChangeDelay > 1.f)
		{
			if (PlayerPos.x > mTransform->GetPosition().x)
				mDir = eDirection::RIGHT;
			else
				mDir = eDirection::LEFT;

			mTransform->SetDirection(mDir);

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"BioSpark_Right_Appear", false);
			else
				mAnimator->PlayAnimation(L"BioSpark_Left_Appear", false);

			mState = eBioSparkState::Appear;
			mStateChangeDelay = 0.f;
		}
	}

	void BioSpark::Appear()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"BioSpark_Right_ThrowShuriken", false);
			else
				mAnimator->PlayAnimation(L"BioSpark_Left_ThrowShuriken", false);

			// 수리검 생성
			BioSpark_Shuriken* shurihen = new BioSpark_Shuriken(this);
			object::ActiveSceneAddGameObject(eLayerType::Effect, shurihen);

			mState = eBioSparkState::ThrowShuriken;
			mStateChangeDelay = 0.f;
		}
	}

	void BioSpark::Hiding()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"BioSpark_Right_Hide", true);
			else
				mAnimator->PlayAnimation(L"BioSpark_Left_Hide", true);

			mState = eBioSparkState::Hide;
			mStateChangeDelay = 0.f;
		}
	}

	void BioSpark::Attack()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"BioSpark_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"BioSpark_Left_Idle", true);
				
			mState = eBioSparkState::Idle;
			mStateChangeDelay = 0.f;
		}
	}

	void BioSpark::Damage()
	{
		mStateChangeDelay += Time::DeltaTime();

		if (mAnimator->IsActiveAnimationComplete() && mStateChangeDelay > 1.f)
		{
			mStateChangeDelay = 0.f;

			if (GetCurHP() <= 0.f)
			{
				mAnimator->PlayAnimation(L"BioSpark_Death", false);
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
				mState = eBioSparkState::Dead;
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"BioSpark_Right_Idle", true);
				else
					mAnimator->PlayAnimation(L"BioSpark_Left_Idle", true);

				mRigidBody->SetVelocity(Vector2(0.f, 0.f));

				mState = eBioSparkState::Idle;
			}
		}
	}

	void BioSpark::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void BioSpark::Inhaled()
	{
		mRigidBody->SetGround(true);

		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"BioSpark_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"BioSpark_Left_Idle", true);

			mRigidBody->SetVelocity(Vector2(0.f, 0.f));

			mState = eBioSparkState::Idle;
		}
	}
}