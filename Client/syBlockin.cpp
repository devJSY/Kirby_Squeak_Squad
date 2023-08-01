#include "syBlockin.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syRigidbody.h"
#include "syCollider.h"
#include "sySceneManager.h"
#include "syScene.h"
#include "syTime.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"


namespace sy
{
	Blockin::Blockin()
		: Enemy(eAbilityType::Normal)
		, mState(eBlockinState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDirDuration(0.f)
		, mDir(eDirection::RIGHT)
	{
	}

	Blockin::~Blockin()
	{
	}

	void Blockin::Initialize()
	{
		Texture* Enemies_Right = ResourceManager::Load<Texture>(L"Enemies_Right_Tex", L"..\\Resources\\Enemy\\Enemies_Right.bmp");
		Texture* Enemies_Left = ResourceManager::Load<Texture>(L"Enemies_Left_Tex", L"..\\Resources\\Enemy\\Enemies_Left.bmp");
		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidBody = AddComponent<Rigidbody>();

		mAnimator->CreateAnimation(Enemies_Right, L"BlockEnemy_Right_Idle", Vector2(1.f, 611.f), Vector2(16.f, 16.f), Vector2(16.f, 0.f), 1.f, 1);
		
		mAnimator->CreateAnimation(Enemies_Right, L"BlockEnemy_Right_Appear", Vector2(0.f, 611.f), Vector2(18.f, 16.f), Vector2(18.f, 0.f), 0.12f, 6);
		mAnimator->CreateAnimation(Enemies_Left, L"BlockEnemy_Left_Appear", Vector2(464.f, 611.f), Vector2(18.f, 16.f), Vector2(-18.f, 0.f), 0.12f, 6);
		
		mAnimator->CreateAnimation(Enemies_Right, L"BlockEnemy_Right_Walk", Vector2(110.f, 616.f), Vector2(23.f, 35.f), Vector2(23.f, 0.f), 0.12f, 7, Vector2(0.f, -10.f));
		mAnimator->CreateAnimation(Enemies_Left, L"BlockEnemy_Left_Walk", Vector2(349.f, 616.f), Vector2(23.f, 35.f), Vector2(-23.f, 0.f), 0.12f, 7, Vector2(0.f, -10.f));
		
		mAnimator->CreateAnimation(Enemies_Right, L"BlockEnemy_Right_Damage", Vector2(26.f, 653.f), Vector2(21.f, 20.f), Vector2(21.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Enemies_Left, L"BlockEnemy_Left_Damage", Vector2(435.f, 653.f), Vector2(21.f, 20.f), Vector2(-21.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(Monster_Death_Tex, L"BlockEnemy_Death", Vector2(0.f, 0.f), Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);
		
		mAnimator->PlayAnimation(L"BlockEnemy_Right_Idle", true);

		Enemy::Initialize();
	}

	void Blockin::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// 픽셀충돌 체크
		CheckPixelCollision();

		switch (mState)
		{
		case eBlockinState::Idle:
			Idle();
			break;
		case eBlockinState::Appear:
			Appear();
			break;
		case eBlockinState::Walk:
			Walk();
			break;
		case eBlockinState::Damage:
			Damage();
			break;
		case eBlockinState::Dead:
			Dead();
			break;
		default:
			break;
		}

		Enemy::Update();
	}

	void Blockin::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void Blockin::OnCollisionEnter(Collider* other)
	{
		if (mState == eBlockinState::Dead)
			return;

		// Inhale 상태에선 무시
		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(other->GetOwner());
		if (kirby != nullptr)
		{
			if (kirby->GetKirbyState() == eDefaultKirbyState::Inhale_1 || kirby->GetKirbyState() == eDefaultKirbyState::Inhale_2)
				return;
		}

		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 몬스터 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Blockin::OnCollisionStay(Collider* other)
	{
	}

	void Blockin::OnCollisionExit(Collider* other)
	{
	}

	void Blockin::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		// 이미 데미지 상태면 처리하지않음
		if (mState == eBlockinState::Damage || mState == eBlockinState::Dead)
			return;

		Damaged(DamageAmount);
		mState = eBlockinState::Damage;

		if (HitDir != Vector2::Zero)
		{
			HitDir.Normalize();
			HitDir *= 30.f;
			mRigidBody->SetVelocity(HitDir);
		}

		if (HitDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"BlockEnemy_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"BlockEnemy_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void Blockin::CheckPixelCollision()
	{
		// Stage타입에따라 픽셀텍스쳐 변경하기
		Texture* PixelTex = ResourceManager::Find<Texture>(L"Stage1_Pixel");

		if (PixelTex == nullptr)
			return;

		// Offset 픽셀 좌상단위치 설정
		Vector2 offset = Vector2::Zero;

		std::wstring CurSceneName = SceneManager::GetActiveScene()->GetName();

		if (CurSceneName == L"Stage1Scene")
		{
			offset = Vector2::Zero;
		}
		else if (CurSceneName == L"Stage2Scene")
		{
			offset = Vector2(0, 347.f);
		}
		else if (CurSceneName == L"Stage3Scene")
		{
			offset = Vector2(0, 679.f);
		}
		else if (CurSceneName == L"Stage4Scene")
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
		if (LBColor == RGB(0, 0, 255) || RBColor == RGB(0, 0, 255))
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
			|| RBColor == RGB(0, 0, 255) || RBColorOffsetY == RGB(0, 0, 255)))
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
				mAnimator->PlayAnimation(L"BlockEnemy_Left_Walk", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"BlockEnemy_Right_Walk", true);
			}

			mState = eBlockinState::Walk;
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
				mAnimator->PlayAnimation(L"BlockEnemy_Left_Walk", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"BlockEnemy_Right_Walk", true);
			}

			mState = eBlockinState::Walk;
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
			mDirDuration = 0.f;
		}
	}

	void Blockin::Idle()
	{
	}

	void Blockin::Appear()
	{
	}

	void Blockin::Walk()
	{
		// 좌우 이동
		Vector2 pos = mTransform->GetPosition();
		if (mDir == eDirection::RIGHT)
			pos.x += 30.f * Time::DeltaTime();
		else
			pos.x -= 30.f * Time::DeltaTime();
		mTransform->SetPosition(pos);

		mDirDuration += Time::DeltaTime();

		// 일정시간 이후 방향 변경
		if (mDirDuration > 3.f)
		{
			if (mDir == eDirection::RIGHT)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"BlockEnemy_Left_Walk", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"BlockEnemy_Right_Walk", true);
			}

			mDirDuration = 0.f;
		}
	}

	void Blockin::Damage()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (GetHP() <= 0.f)
			{
				mAnimator->PlayAnimation(L"BlockEnemy_Death", false);
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
				mState = eBlockinState::Dead;
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"BlockEnemy_Right_Walk", true);
				else
					mAnimator->PlayAnimation(L"BlockEnemy_Left_Walk", true);

				mRigidBody->SetVelocity(Vector2(0.f, 0.f));

				mState = eBlockinState::Walk;
			}
		}
	}

	void Blockin::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}		
	}
}