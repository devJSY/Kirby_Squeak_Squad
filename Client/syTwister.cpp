#include "syTwister.h"
#include "syAnimator.h"
#include "syTexture.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syResourceManager.h"
#include "syRigidbody.h"
#include "sySceneManager.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"
#include "syTime.h"
#include "sySound.h"

namespace sy
{
	Twister::Twister()
		: Enemy(eAbilityType::Tornado)
		, mState(eTwisterState::Idle)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
		, mAttackDelay(0.f)
		, mStateChangeDelay(0.f)
	{
	}

	Twister::~Twister()
	{

	}
	void Twister::Initialize()
	{
		Texture* Twister_Right_Tex = ResourceManager::Load<Texture>(L"Twister_Right_Tex", L"..\\Resources\\Enemy\\Twister\\Twister_Right.bmp");
		Texture* Twister_Left_Tex = ResourceManager::Load<Texture>(L"Twister_Left_Tex", L"..\\Resources\\Enemy\\Twister\\Twister_Left.bmp");
		Twister_Right_Tex->SetType(eTextureType::Bmp);
		Twister_Left_Tex->SetType(eTextureType::Bmp);

		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");

		mAnimator = GetComponent<Animator>();
		mTransform = GetComponent<Transform>();
		mRigidBody = AddComponent<Rigidbody>();

		// 애니메이션 생성
		Vector2 Animationoffset = Vector2(0.f, 10.f);

		mAnimator->CreateAnimation(Twister_Right_Tex, L"Twister_Right_Idle", Vector2::Zero, Vector2(128.f, 128.f), Vector2(128.f, 0.f), 0.1f, 10, Animationoffset);
		mAnimator->CreateAnimation(Twister_Left_Tex, L"Twister_Left_Idle", Vector2::Zero, Vector2(128.f, 128.f), Vector2(128.f, 0.f), 0.1f, 10, Animationoffset);

		mAnimator->CreateAnimation(Twister_Right_Tex, L"Twister_Right_Skill", Vector2(0.f, 256.f), Vector2(128.f, 128.f), Vector2(128.f, 0.f), 0.1f, 3, Animationoffset);
		mAnimator->CreateAnimation(Twister_Left_Tex, L"Twister_Left_Skill", Vector2(0.f, 256.f), Vector2(128.f, 128.f), Vector2(128.f, 0.f), 0.1f, 3, Animationoffset);

		mAnimator->CreateAnimation(Twister_Right_Tex, L"Twister_Right_Damage", Vector2(384.f, 256.f), Vector2(128.f, 128.f), Vector2(128.f, 0.f), 0.2f, 2, Animationoffset);
		mAnimator->CreateAnimation(Twister_Left_Tex, L"Twister_Left_Damage", Vector2(384.f, 256.f), Vector2(128.f, 128.f), Vector2(128.f, 0.f), 0.2f, 2, Animationoffset);

		mAnimator->CreateAnimation(Monster_Death_Tex, L"Twister_Death", Vector2::Zero, Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);

		mAnimator->PlayAnimation(L"Twister_Right_Idle", true);

		ResourceManager::Load<Sound>(L"TornadoSkill_Sound", L"..\\Resources\\Sound\\Effect\\TornadoSkill.wav");


		Enemy::Initialize();
	}

	void Twister::Update()
	{
		// 방향 설정
		mDir = mTransform->GetDirection();

		// 픽셀충돌 체크
		if (mState != eTwisterState::Inhaled)
		{
			CheckPixelCollision();
		}

		switch (mState)
		{
		case eTwisterState::Idle:
			Idle();
			break;
		case eTwisterState::Skill:
			Skill();
			break;
		case eTwisterState::Damage:
			Damage();
			break;
		case eTwisterState::Dead:
			Dead();
			break;
		case eTwisterState::Inhaled:
			Inhaled();
			break;
		}

		Enemy::Update();
	}

	void Twister::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}

	void Twister::OnCollisionEnter(Collider* other)
	{
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

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Twister::OnCollisionStay(Collider* other)
	{
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

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Twister::TakeHit(int DamageAmount, math::Vector2 HitDir)
	{
		Damaged(DamageAmount);

		// 이미 데미지 상태면 애니메이션, 피격 넉백 처리하지않음
		if (mState == eTwisterState::Damage || mState == eTwisterState::Dead)
			return;

		mState = eTwisterState::Damage;
		mStateChangeDelay = 0.f;
		mRigidBody->SetFloat(false);

		if (HitDir != Vector2::Zero)
		{
			HitDir.Normalize();
			HitDir *= 30.f;
			mRigidBody->SetVelocity(HitDir);
		}

		if (HitDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"Twister_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"Twister_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void Twister::TakeInhaled(math::Vector2 InhaleDir)
	{
		if (mState == eTwisterState::Dead)
			return;

		mState = eTwisterState::Inhaled;

		if (InhaleDir.x < 0.f)
		{
			mAnimator->PlayAnimation(L"Twister_Right_Damage", false);
			mTransform->SetDirection(eDirection::RIGHT);
		}
		else
		{
			mAnimator->PlayAnimation(L"Twister_Left_Damage", false);
			mTransform->SetDirection(eDirection::LEFT);
		}
	}

	void Twister::CheckPixelCollision()
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
				mAnimator->PlayAnimation(L"Twister_Left_Skill", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"Twister_Right_Skill", true);
			}

			mState = eTwisterState::Skill;
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

			if (mDir == eDirection::RIGHT)
			{
				mTransform->SetDirection(eDirection::LEFT);
				mAnimator->PlayAnimation(L"Twister_Left_Skill", true);
			}
			else
			{
				mTransform->SetDirection(eDirection::RIGHT);
				mAnimator->PlayAnimation(L"Twister_Right_Skill", true);
			}

			mState = eTwisterState::Skill;
			mRigidBody->SetVelocity(Vector2(0.f, 0.f));
		}
	}

	void Twister::Idle()
	{
		mAttackDelay += Time::DeltaTime();

		// 플레이어 방향을 바라보도록 설정
		Vector2 PlayerPos = SceneManager::GetPlayer()->GetComponent<Transform>()->GetPosition();
		mSkillDir = PlayerPos - mTransform->GetPosition();
		float Len = mSkillDir.Length();

		// Skill
		if (Len < 100.f && mAttackDelay > 1.f)
		{
			if (PlayerPos.x > mTransform->GetPosition().x)
				mDir = eDirection::RIGHT;
			else
				mDir = eDirection::LEFT;

			mTransform->SetDirection(mDir);

			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Twister_Right_Skill", true);
			else
				mAnimator->PlayAnimation(L"Twister_Left_Skill", true);

			mState = eTwisterState::Skill;
			mAttackDelay = 0.f;
			mRigidBody->SetFloat(true);
			ResourceManager::Find<Sound>(L"TornadoSkill_Sound")->Play(false);
		}
	}

	void Twister::Skill()
	{
		mStateChangeDelay += Time::DeltaTime();

		if (mStateChangeDelay > 2.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Twister_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"Twister_Left_Idle", true);

			mState = eTwisterState::Idle;
			mStateChangeDelay = 0.f;
			mRigidBody->SetFloat(false);
		}

		Vector2 pos = mTransform->GetPosition();
		mSkillDir.Normalize();
		pos += mSkillDir * 100.f * Time::DeltaTime();
		mTransform->SetPosition(pos);	
	}

	void Twister::Damage()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			if (GetCurHP() <= 0.f)
			{
				mAnimator->PlayAnimation(L"HotHead_Death", false);
				mRigidBody->SetVelocity(Vector2(0.f, 0.f));
				mState = eTwisterState::Dead;
			}
			else
			{
				if (mDir == eDirection::RIGHT)
					mAnimator->PlayAnimation(L"Twister_Right_Idle", true);
				else
					mAnimator->PlayAnimation(L"Twisterd_Left_Idle", true);

				mRigidBody->SetVelocity(Vector2(0.f, 0.f));

				mState = eTwisterState::Idle;
			}
		}
	}

	void Twister::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}

	void Twister::Inhaled()
	{
		mRigidBody->SetGround(true);

		if (mAnimator->IsActiveAnimationComplete())
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Twister_Right_Idle", true);
			else
				mAnimator->PlayAnimation(L"Twisterd_Left_Idle", true);

			mRigidBody->SetVelocity(Vector2(0.f, 0.f));

			mState = eTwisterState::Idle;
		}
	}
}