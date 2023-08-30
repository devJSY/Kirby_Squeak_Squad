#include "syHeavyKnight.h"
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
	HeavyKnight::HeavyKnight()
		: Enemy(eAbilityType::Sword)
		, mState(eHeavyKnightState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
		, mDirDuration(0.f)
		, mAttackDelay(0.f)
		, mStateChangeDelay(0.f)
		, mSlashCount(2)
	{
	}

	HeavyKnight::~HeavyKnight()
	{
	}

	void HeavyKnight::Initialize()
	{
		Texture* HeavyKnight_Tex = ResourceManager::Load<Texture>(L"HeavyKnight_Tex", L"..\\Resources\\Enemy\\HeavyKnight\\HeavyKnight.bmp");
		HeavyKnight_Tex->SetScale(Vector2(0.4f, 0.4f));

		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidBody = AddComponent<Rigidbody>();
		GetComponent<Collider>()->SetSize(Vector2(30.f, 30.f));
		SetHP(200);

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, 0.f);

		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Right_Idle", Vector2::Zero, Vector2(240.f, 240.f), Vector2(240.f, 0.f), 1.f, 1, Animationoffset);
		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Left_Idle", Vector2(0.f, 1200.f), Vector2(240.f, 240.f), Vector2(240.f, 0.f), 1.f, 1, Animationoffset);

		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Right_Walk", Vector2::Zero, Vector2(240.f, 240.f), Vector2(240.f, 0.f), 0.1f, 8, Animationoffset);
		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Left_Walk", Vector2(0.f, 1200.f), Vector2(240.f, 240.f), Vector2(240.f, 0.f), 0.1f, 8, Animationoffset);

		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Right_SlashReady", Vector2(0.f, 240.f), Vector2(240.f, 240.f), Vector2(240.f, 0.f), 0.1f, 2, Animationoffset);
		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Left_SlashReady", Vector2(0.f, 1440.f), Vector2(240.f, 240.f), Vector2(240.f, 0.f), 0.1f, 2, Animationoffset);

		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Right_Slash1", Vector2(0.f, 480.f), Vector2(240.f, 240.f), Vector2(240.f, 0.f), 0.08f, 9, Animationoffset);
		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Left_Slash1", Vector2(0.f, 1680.f), Vector2(240.f, 240.f), Vector2(240.f, 0.f), 0.08f, 9, Animationoffset);

		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Right_Slash2", Vector2(0.f, 720.f), Vector2(240.f, 240.f), Vector2(240.f, 0.f), 0.08f, 6, Animationoffset);
		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Left_Slash2", Vector2(0.f, 1920.f), Vector2(240.f, 240.f), Vector2(240.f, 0.f), 0.08f, 6, Animationoffset);

		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Right_Damage", Vector2(0.f, 960.f), Vector2(240.f, 240.f), Vector2(240.f, 0.f), 0.1f, 2, Animationoffset);
		mAnimator->CreateAnimation(HeavyKnight_Tex, L"HeavyKnight_Left_Damage", Vector2(0.f, 2160.f), Vector2(240.f, 240.f), Vector2(240.f, 0.f), 0.1f, 2, Animationoffset);
		
		mAnimator->CreateAnimation(Monster_Death_Tex, L"HeavyKnight_Death", Vector2::Zero, Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);

		mAnimator->PlayAnimation(L"HeavyKnight_Right_Idle", true);


		Enemy::Initialize();
	}

	void HeavyKnight::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// 픽셀충돌 체크
		if (mState != eHeavyKnightState::Inhaled)
		{
			CheckPixelCollision();
		}

		switch (mState)
		{
		case eHeavyKnightState::Idle:
			Idle();
			break;
		case eHeavyKnightState::Walk:
			Walk();
			break;
		case eHeavyKnightState::SlashReady:
			SlashReady();
			break;
		case eHeavyKnightState::Slash:
			Slash();
			break;
		case eHeavyKnightState::Damage:
			Damage();
			break;
		case eHeavyKnightState::Dead:
			Dead();
			break;
		case eHeavyKnightState::Inhaled:
			Inhaled();
			break;
		}

		Enemy::Update();
	}

	void HeavyKnight::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void HeavyKnight::OnCollisionEnter(Collider* other)
	{
		if (mState == eHeavyKnightState::Dead
			|| mState == eHeavyKnightState::Inhaled)
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

	void HeavyKnight::OnCollisionStay(Collider* other)
	{
	}

	void HeavyKnight::OnCollisionExit(Collider* other)
	{
	}

	void HeavyKnight::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		Damaged(DamageAmount);

		// 이미 데미지 상태면 애니메이션, 피격 넉백 처리하지않음
		if (mState == eHeavyKnightState::Damage || mState == eHeavyKnightState::Dead)
			return;

		mState = eHeavyKnightState::Damage;

		if (HitDir != Vector2::Zero)
		{
			HitDir.Normalize();
			HitDir *= 30.f;
			mRigidBody->SetVelocity(HitDir);
		}

		if (HitDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"HeavyKnight_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"HeavyKnight_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void HeavyKnight::TakeInhaled(math::Vector2 InhaleDir)
	{
		if (mState == eHeavyKnightState::Dead)
			return;

		mState = eHeavyKnightState::Inhaled;

		if (InhaleDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"HeavyKnight_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"HeavyKnight_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void HeavyKnight::CheckPixelCollision()
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

			if (mDir == eDirection::RIGHT)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"HeavyKnight_Left_Walk", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"HeavyKnight_Right_Walk", true);
			}

			mState = eHeavyKnightState::Walk;
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
				mAnimator->PlayAnimation(L"HeavyKnight_Left_Walk", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"HeavyKnight_Right_Walk", true);
			}

			mState = eHeavyKnightState::Walk;
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mDirDuration = 0.f;
		}
	}

	void HeavyKnight::Idle()
	{
		mStateChangeDelay += Time::DeltaTime();
		mAttackDelay += Time::DeltaTime();

		if (mStateChangeDelay > 1.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"HeavyKnight_Right_Walk", true);
			else
				mAnimator->PlayAnimation(L"HeavyKnight_Left_Walk", true);

			mState = eHeavyKnightState::Walk;
			mStateChangeDelay = 0.f;
		}

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

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"HeavyKnight_Right_SlashReady", false);
			else
				mAnimator->PlayAnimation(L"HeavyKnight_Left_SlashReady", false);

			mState = eHeavyKnightState::SlashReady;
			mAttackDelay = 0.f;
			mStateChangeDelay = 0.f;
		}
	}

	void HeavyKnight::Walk()
	{
		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();
		if (mDir == eDirection::RIGHT)
			pos.x += 30.f * Time::DeltaTime();
		else
			pos.x -= 30.f * Time::DeltaTime();
		mTransform->SetPosition(pos);

		mDirDuration += Time::DeltaTime();
		mAttackDelay += Time::DeltaTime();
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 5.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"HeavyKnight_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"HeavyKnight_Left_Idle", true);

			mState = eHeavyKnightState::Idle;
			mStateChangeDelay = 0.f;
		}

		// 일정시간 이후 방향 변경
		if (mDirDuration > 3.f)
		{
			if (mDir == eDirection::RIGHT)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"HeavyKnight_Left_Walk", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"HeavyKnight_Right_Walk", true);
			}

			mDirDuration = 0.f;
		}

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

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"HeavyKnight_Right_SlashReady", false);
			else
				mAnimator->PlayAnimation(L"HeavyKnight_Left_SlashReady", false);

			mState = eHeavyKnightState::SlashReady;
			mAttackDelay = 0.f;
			mStateChangeDelay = 0.f;
		}
	}

	void HeavyKnight::SlashReady()
	{
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 1.f)
		{
			Vector2 vel = mRigidBody->GetVelocity();

			if (mDir == eDirection::RIGHT)
			{
				vel.x += 50.f;
				mAnimator->PlayAnimation(L"HeavyKnight_Right_Slash1", false);
			}
			else
			{
				vel.x -= 50.f;
				mAnimator->PlayAnimation(L"HeavyKnight_Left_Slash1", false);
			}

			mState = eHeavyKnightState::Slash;
			--mSlashCount;
			mStateChangeDelay = 0.f;
			mRigidBody->SetVelocity(vel);
		}
	}

	void HeavyKnight::Slash()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mSlashCount == 0)
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"HeavyKnight_Right_Idle", true);
				else
					mAnimator->PlayAnimation(L"HeavyKnight_Left_Idle", true);

				mSlashCount = 2;

				mState = eHeavyKnightState::Idle;
			}
			else
			{
				if (mSlashCount == 1)
				{
					Vector2 vel = mRigidBody->GetVelocity();

					if (mDir == eDirection::RIGHT)
					{
						vel.x += 50.f;
						mAnimator->PlayAnimation(L"HeavyKnight_Right_Slash2", false);
					}
					else
					{
						vel.x -= 50.f;
						mAnimator->PlayAnimation(L"HeavyKnight_Left_Slash2", false);
					}

					--mSlashCount;
					mRigidBody->SetVelocity(vel);
				}
			}
		}
	}

	void HeavyKnight::Damage()
	{
		mStateChangeDelay += Time::DeltaTime();

		if (mAnimator->IsActiveAnimationComplete() && mStateChangeDelay > 1.f)
		{
			mStateChangeDelay = 0.f;

			if (GetCurHP() <= 0.f)
			{
				mAnimator->PlayAnimation(L"HeavyKnight_Death", false);
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
				mState = eHeavyKnightState::Dead;
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"HeavyKnight_Right_Idle", true);
				else
					mAnimator->PlayAnimation(L"HeavyKnight_Left_Idle", true);

				mRigidBody->SetVelocity(Vector2(0.f, 0.f));

				mState = eHeavyKnightState::Idle;
			}
		}
	}

	void HeavyKnight::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void HeavyKnight::Inhaled()
	{
		mRigidBody->SetGround(true);

		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"HeavyKnight_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"HeavyKnight_Left_Idle", true);

			mRigidBody->SetVelocity(Vector2(0.f, 0.f));

			mState = eHeavyKnightState::Idle;
		}
	}
}