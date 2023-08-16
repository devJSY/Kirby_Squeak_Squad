#include "syDaroach_Bomb.h"
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

namespace sy
{
	Daroach_Bomb::Daroach_Bomb(Daroach* owner)
		: Effects(owner)
		, mState(eDaroachBombState::Idle)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mCollider(nullptr)
		, mRigidBody(nullptr)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();
		mAnimator = GetComponent<Animator>();
		mCollider = AddComponent<Collider>();
		mRigidBody = AddComponent<Rigidbody>();
		mRigidBody->SetMass(1.5f);
		
		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		mCollider->SetSize(Vector2(19.f,19.f));

		if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
			mRigidBody->SetVelocity(Vector2(100.f, 0.f));
		else
			mRigidBody->SetVelocity(Vector2(-100.f, 0.f));
		
		// 애니메이션 생성
		Texture* Daroach_Bomb_Tex = ResourceManager::Load<Texture>(L"Daroach_Bomb_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Bomb.bmp");
		Texture* Daroach_Bomb_Fire_Tex = ResourceManager::Load<Texture>(L"Daroach_Bomb_Fire_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Bomb_Fire.bmp");

		mAnimator->CreateAnimation(Daroach_Bomb_Tex, L"Daroach_Bomb", Vector2::Zero, Vector2(19.f, 19.f), Vector2(19.f, 0.f), 0.1f, 3);
		mAnimator->CreateAnimation(Daroach_Bomb_Fire_Tex, L"Daroach_Bomb_Fire", Vector2::Zero, Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.1f, 8);

		mAnimator->PlayAnimation(L"Daroach_Bomb", true);
	}

	Daroach_Bomb::~Daroach_Bomb()
	{
	}

	void Daroach_Bomb::Initialize()
	{
		Effects::Initialize();
	}

	void Daroach_Bomb::Update()
	{
		// Idle 상태에서만 픽셀충돌 적용
		if(mState == eDaroachBombState::Idle)
			CheckPixelCollision();

		switch (mState)
		{
		case eDaroachBombState::Idle:
			Idle();
			break;
		case eDaroachBombState::Fire:
			Fire();
			break;
		default:
			break;
		}

		Effects::Update();
	}

	void Daroach_Bomb::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Daroach_Bomb::OnCollisionEnter(Collider* other)
	{
		// Fire 상태에서만 적용
		if (mState != eDaroachBombState::Fire)
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

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Daroach_Bomb::OnCollisionStay(Collider* other)
	{
		// Fire 상태에서만 적용
		if (mState != eDaroachBombState::Fire)
			return;

		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		DefaultKirby* kirby = dynamic_cast<DefaultKirby*>(player->GetActiveKirby());

		// DefaultKirby가 Damage 상태면 적용하지않음
		if (kirby != nullptr && kirby->IsDamagedState())
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Daroach_Bomb::CheckPixelCollision()
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
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 3.f;
			mTransform->SetPosition(pos);

			Vector2 vel = mRigidBody->GetVelocity();
			if(vel.x > 0.f)
				vel.x *= -1;
			mRigidBody->SetVelocity(vel);
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

			Vector2 vel = mRigidBody->GetVelocity();
			if (vel.x < 0.f)
				vel.x *= -1;
			mRigidBody->SetVelocity(vel);
		}
	}

	void Daroach_Bomb::Idle()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 1.f)
		{
			mAnimator->PlayAnimation(L"Daroach_Bomb_Fire", false);
			mRigidBody->SetGround(true);
			mCollider->SetSize(Vector2(50.f, 50.f));
			mState = eDaroachBombState::Fire;
			mDuration = 0.f;
		}
	}

	void Daroach_Bomb::Fire()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}	
	}
}