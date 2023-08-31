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

namespace sy
{
	BioSpark::BioSpark()
		: Enemy(eAbilityType::Ninja)
		, mState(eBioSparkState::Hide)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mRigidBody(nullptr)
		, mDir(eDirection::RIGHT)
		, mStateChangeDelay(0.f)
	{
	}

	BioSpark::~BioSpark()
	{
	}

	void BioSpark::Initialize()
	{

		Enemy::Initialize();
	}

	void BioSpark::Update()
	{
		// ���� ����
		mDir = mTransform->GetDirection();

		// �ȼ��浹 üũ
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

		// Inhale ���¿��� ����
		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());
		if (kirby != nullptr)
		{
			if (kirby->GetKirbyState() == eDefaultKirbyState::Inhale_1 || kirby->GetKirbyState() == eDefaultKirbyState::Inhale_2)
				return;
		}

		// ���� �� Ŀ�� ����
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

		// �̹� ������ ���¸� �ִϸ��̼�, �ǰ� �˹� ó����������
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

		// StageŸ�Կ����� �ȼ��ؽ��� �����ϱ�
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

		// Offset �ȼ� �»����ġ ����
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

		// �ٴ� ó��
		if (LBColor == RGB(0, 0, 255) || RBColor == RGB(0, 0, 255)
			|| LBColor == RGB(255, 0, 0) || RBColor == RGB(255, 0, 0))
		{
			// �̵�
			Vector2 pos = mTransform->GetPosition();
			pos.y -= 1.f;
			mTransform->SetPosition(pos);
			mRigidBody->SetGround(true);
		}

		COLORREF LBColorOffsetY = PixelTex->GetTexturePixel((int)LB.x, int(LB.y + 1));
		COLORREF RBColorOffsetY = PixelTex->GetTexturePixel((int)RB.x, int(RB.y + 1));

		// �ٴ� ~ �ٴ� + 1�ȼ� ������ �ƴҰ�� Ground false ó��
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
			// �̵�
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
			// �̵�
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
	}

	void BioSpark::ThrowShuriken()
	{
	}

	void BioSpark::Hide()
	{
	}

	void BioSpark::Appear()
	{
	}

	void BioSpark::Hiding()
	{
	}

	void BioSpark::Attack()
	{
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