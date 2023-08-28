#include "syDaroach_TimeBomb.h"
#include "syDaroach.h"
#include "syTransform.h"
#include "syRigidbody.h"
#include "syAnimator.h"
#include "syResourceManager.h"
#include "sySceneManager.h"
#include "syCollider.h"
#include "syPlayer.h"
#include "syTime.h"
#include "syDefaultKirby.h"
#include "sySound.h"

namespace sy
{
	Daroach_TimeBomb::Daroach_TimeBomb(Daroach* owner)
		: Effects(owner)
		, mState(eDaroachTimeBombState::Idle)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mCollider(nullptr)
		, mRigidBody(nullptr)
		, mDuration(0.f)
		, mInhaled(false)
	{
		mTransform = GetComponent<Transform>();
		mAnimator = GetComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mRigidBody = AddComponent<Rigidbody>();
		mRigidBody->SetMass(1.5f);

		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		mCollider->SetSize(Vector2(32.f, 31.f));

		if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
			mRigidBody->SetVelocity(Vector2(100.f, 0.f));
		else
			mRigidBody->SetVelocity(Vector2(-100.f, 0.f));

		// �ִϸ��̼� ����
		Texture* Daroach_TimeBomb_Tex = ResourceManager::Load<Texture>(L"Daroach_TimeBomb_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_TimeBomb.bmp");
		Texture* Daroach_TimeBomb_Fire_Tex = ResourceManager::Load<Texture>(L"Daroach_TimeBomb_Fire_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_TimeBomb_Fire.bmp");
		Texture* Daroach_TimeBomb_FireEnd_Tex = ResourceManager::Load<Texture>(L"Daroach_TimeBomb_FireEnd_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_TimeBomb_FireEnd.bmp");

		mAnimator->CreateAnimation(Daroach_TimeBomb_Tex, L"Daroach_TimeBomb", Vector2::Zero, Vector2(32.f, 31.f), Vector2(32.f, 0.f), 0.05f, 4);
		mAnimator->CreateAnimation(Daroach_TimeBomb_Fire_Tex, L"Daroach_TimeBomb_Fire", Vector2::Zero, Vector2(45.f, 112.f), Vector2(45.f, 0.f), 0.05f, 3, Vector2(0.f, -40.f));
		mAnimator->CreateAnimation(Daroach_TimeBomb_FireEnd_Tex, L"Daroach_TimeBomb_FireEnd", Vector2::Zero, Vector2(58.f, 160.f), Vector2(58.f, 0.f), 0.05f, 4, Vector2(0.f, -64.f));

		mAnimator->PlayAnimation(L"Daroach_TimeBomb", true);

		// Sound Load
		ResourceManager::Load<Sound>(L"DaroachTimeBombSound", L"..\\Resources\\Sound\\Effect\\Daroach\\DaroachTimeBomb.wav");
	}

	Daroach_TimeBomb::~Daroach_TimeBomb()
	{
	}

	void Daroach_TimeBomb::Initialize()
	{
		Effects::Initialize();
	}

	void Daroach_TimeBomb::Update()
	{
		if (!mInhaled)
		{
			// Idle ���¿����� �ȼ��浹 ����
			if (mState == eDaroachTimeBombState::Idle)
				CheckPixelCollision();

			switch (mState)
			{
			case eDaroachTimeBombState::Idle:
				Idle();
				break;
			case eDaroachTimeBombState::Fire:
				Fire();
				break;
			case eDaroachTimeBombState::FireEnd:
				FireEnd();
				break;
			default:
				break;
			}
		}
		else
		{
			// �������
			mRigidBody->SetVelocity(Vector2::Zero);
		}

		Effects::Update();
	}

	void Daroach_TimeBomb::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Daroach_TimeBomb::OnCollisionEnter(Collider* other)
	{
		if (mState == eDaroachTimeBombState::Idle)
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

		// ��ų �� Ŀ�� ����
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Daroach_TimeBomb::OnCollisionStay(Collider* other)
	{
		if (mState == eDaroachTimeBombState::Idle)
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

		// ��ų �� Ŀ�� ����
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Daroach_TimeBomb::CheckPixelCollision()
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

			Vector2 vel = mRigidBody->GetVelocity();
			if (vel.x > 0.f)
				vel.x *= -1;
			mRigidBody->SetVelocity(vel);
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

			Vector2 vel = mRigidBody->GetVelocity();
			if (vel.x < 0.f)
				vel.x *= -1;
			mRigidBody->SetVelocity(vel);
		}
	}

	void Daroach_TimeBomb::Idle()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 3.f)
		{
			mAnimator->PlayAnimation(L"Daroach_TimeBomb_Fire", false);
			mRigidBody->SetGround(true);
			mCollider->SetSize(Vector2(45.f, 112.f));
			mCollider->SetOffset(Vector2(0.f, -40.f));
			mState = eDaroachTimeBombState::Fire;
			ResourceManager::Find<Sound>(L"DaroachTimeBombSound")->Play(false);
			mDuration = 0.f;
		}
	}

	void Daroach_TimeBomb::Fire()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			mAnimator->PlayAnimation(L"Daroach_TimeBomb_FireEnd", true);
			mCollider->SetSize(Vector2(58.f, 160.f));
			mCollider->SetOffset(Vector2(0.f, -64.f));
			mState = eDaroachTimeBombState::FireEnd;
			mDuration = 0.f;
		}
	}
	void Daroach_TimeBomb::FireEnd()
	{
		mDuration += Time::DeltaTime();
		if (mDuration > 3.f)
		{
			Destroy(this);
		}
	}
}