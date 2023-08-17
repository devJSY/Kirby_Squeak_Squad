#include "syDaroach_Star.h"
#include "syDaroach.h"
#include "syResourceManager.h"
#include "syTexture.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syRigidbody.h"
#include "syAnimator.h"
#include "syTime.h"
#include "syPlayer.h"
#include "sySceneManager.h"

namespace sy
{
	Daroach_Star::Daroach_Star(Daroach* owner, Vector2 Dir)
		: Effects(owner)
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

		Vector2 pos = GetOwner()->GetComponent<Transform>()->GetPosition();

		if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
		{
			pos.x += 31.f;
			pos.y -= 12.f;
		}
		else
		{
			pos.x -= 31.f;
			pos.y -= 12.f;
		}

		mTransform->SetPosition(pos);
		mCollider->SetColliderType(eColliderType::Sphere);
		mCollider->SetRadius(15.f);
		mCollider->SetPosition(pos);

		Dir.Normalize();
		Dir *= 200.f;
		mRigidBody->SetVelocity(Dir);
		mRigidBody->SetFriction(0.f);
		mRigidBody->SetFloat(true);

		// 애니메이션 생성
		Texture* Daroach_Star_Tex = ResourceManager::Load<Texture>(L"Daroach_Star_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Star.bmp");
		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");
		
		mAnimator->CreateAnimation(Daroach_Star_Tex, L"Daroach_Star", Vector2::Zero, Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.05f, 8);
		mAnimator->CreateAnimation(Monster_Death_Tex, L"Daroach_Star_Death", Vector2(0.f, 0.f), Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);
		mAnimator->PlayAnimation(L"Daroach_Star", true);
	}

	Daroach_Star::~Daroach_Star()
	{
	}

	void Daroach_Star::Initialize()
	{
		Effects::Initialize();
	}

	void Daroach_Star::Update()
	{
		CheckPixelCollision();

		mDuration += Time::DeltaTime();

		if (mDuration > 3.f)
		{
			mAnimator->PlayAnimation(L"Daroach_Star_Death", false);
			mDuration = 0.f;
		}

		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}


		Effects::Update();
	}

	void Daroach_Star::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Daroach_Star::OnCollisionEnter(Collider* other)
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

			// DefaultKirby가 Damage 상태면 적용하지않음
			if (kirby->IsDamagedState())
				return;
		}

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void Daroach_Star::CheckPixelCollision()
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

		Vector2 ColPos = mCollider->GetPosition();
		float ColRadius = mCollider->GetRadius();

		Vector2 LEFT = Vector2(ColPos.x - ColRadius, ColPos.y);
		Vector2 RIGHT = Vector2(ColPos.x + ColRadius, ColPos.y);
		Vector2 TOP = Vector2(ColPos.x, ColPos.y - ColRadius);
		Vector2 BOTTOM = Vector2(ColPos.x, ColPos.y + ColRadius);

		LEFT += offset;
		RIGHT += offset;
		TOP += offset;
		BOTTOM += offset;

		COLORREF LEFTColor = PixelTex->GetTexturePixel((int)LEFT.x, (int)LEFT.y);
		COLORREF RIGHTColor = PixelTex->GetTexturePixel((int)RIGHT.x, (int)RIGHT.y);
		COLORREF TOPColor = PixelTex->GetTexturePixel((int)TOP.x, (int)TOP.y);
		COLORREF BOTTOMColor = PixelTex->GetTexturePixel((int)BOTTOM.x, (int)BOTTOM.y);

		// 상단 처리
		if (TOPColor == RGB(0, 255, 0))
		{
			Vector2 vel = mRigidBody->GetVelocity();
			if (vel.y < 0.f)
				vel.y *= -1.f;
			mRigidBody->SetVelocity(vel);
		}

		// 바닥 처리
		if (BOTTOMColor == RGB(0, 0, 255))
		{
			Vector2 vel = mRigidBody->GetVelocity();
			if (vel.y > 0.f)
				vel.y *= -1.f;
			mRigidBody->SetVelocity(vel);
		}

		// Right Stop Check
		if (RIGHTColor == RGB(0, 255, 0))
		{
			Vector2 vel = mRigidBody->GetVelocity();
			if (vel.x > 0.f)
				vel.x *= -1.f;
			mRigidBody->SetVelocity(vel);
		}

		// Left Stop Check
		if (LEFTColor == RGB(0, 255, 0))
		{
			Vector2 vel = mRigidBody->GetVelocity();
			if (vel.x < 0.f)
				vel.x *= -1.f;
			mRigidBody->SetVelocity(vel);
		}
	}
}