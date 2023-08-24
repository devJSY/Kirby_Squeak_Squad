#include "syDarkNebula_FireBall.h"
#include "syDarkNebula.h"
#include "syTransform.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"
#include "syTime.h"
#include "sySceneManager.h"
#include "syDarkNebula_Fire.h"
#include "syObject.h"
#include "sySound.h"

namespace sy
{
	DarkNebula_FireBall::DarkNebula_FireBall(DarkNebula* owner)
		: Effects(owner)
		, mState(eDarkNebulaFireBallState::FireBall)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mCollider(nullptr)
		, mDuration(0.f)
		, mGroundPos(Vector2::Zero)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		mCollider = AddComponent<Collider>();
		mCollider->SetColliderType(eColliderType::Sphere);
		mCollider->SetRadius(20.f);
		mCollider->SetPosition(mTransform->GetPosition());

		// 애니메이션 생성
		mAnimator = GetComponent<Animator>();
		Texture* DarkNebula_FireBall_Tex = ResourceManager::Load<Texture>(L"DarkNebula_FireBall_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_FireBall.bmp");
		Texture* DarkNebula_FireBall_Exploded_Tex = ResourceManager::Load<Texture>(L"DarkNebula_FireBall_Exploded_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_FireBall_Exploded.bmp");

		mAnimator->CreateAnimation(DarkNebula_FireBall_Tex, L"DarkNebula_FireBall", Vector2::Zero, Vector2(42.f, 42.f), Vector2(42.f, 0.f), 0.05f, 4);
		mAnimator->CreateAnimation(DarkNebula_FireBall_Exploded_Tex, L"DarkNebula_FireBall_Exploded", Vector2::Zero, Vector2(105.f, 160.f), Vector2(105.f, 0.f), 0.05f, 4);

		mAnimator->PlayAnimation(L"DarkNebula_FireBall", true);

		mbActive[0] = mbActive[1] = mbActive[2] = mbActive[3] = mbActive[4] = true;

		// Sound Load
		ResourceManager::Load<Sound>(L"DarkNebula_FireSound", L"..\\Resources\\Sound\\Effect\\DarkNebula\\DarkNebula_Fire.wav");
	}

	DarkNebula_FireBall::~DarkNebula_FireBall()
	{
		ResourceManager::Find<Sound>(L"DarkNebula_FireSound")->Stop(true);
	}

	void DarkNebula_FireBall::Initialize()
	{
		Effects::Initialize();
	}

	void DarkNebula_FireBall::Update()
	{
		if (mState == eDarkNebulaFireBallState::FireBall)
			CheckPixelCollision();

		switch (mState)
		{
		case eDarkNebulaFireBallState::FireBall:
			FireBall();
			break;
		case eDarkNebulaFireBallState::Exploded:
			Exploded();
			break;
		default:
			break;
		}

		Effects::Update();
	}

	void DarkNebula_FireBall::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void DarkNebula_FireBall::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void DarkNebula_FireBall::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (player == nullptr)
			return;

		// 스킬 → 커비 방향
		Vector2 Dir = player->GetComponent<Transform>()->GetPosition() - GetComponent<Transform>()->GetPosition();

		player->TakeHit(10, Dir);
	}

	void DarkNebula_FireBall::CheckPixelCollision()
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

		Vector2 ColPos = mCollider->GetPosition();
		ColPos += offset;

		COLORREF ColPosColor = PixelTex->GetTexturePixel((int)ColPos.x, (int)ColPos.y);

		// 바닥 처리
		if (ColPosColor == RGB(0, 0, 255))
		{
			mState = eDarkNebulaFireBallState::Exploded;
			mCollider->SetColliderType(eColliderType::Box);
			mCollider->SetSize(Vector2(105.f, 160.f));
			mAnimator->PlayAnimation(L"DarkNebula_FireBall_Exploded", true);
			ResourceManager::Find<Sound>(L"DarkNebula_FireSound")->Play(false);
			
			Vector2 pos = mTransform->GetPosition();
			mGroundPos = pos;
			pos.y -= 80.f;
			mTransform->SetPosition(pos);
		}
	}

	void DarkNebula_FireBall::FireBall()
	{
		Vector2 pos = mTransform->GetPosition();
		pos.y += 50.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void DarkNebula_FireBall::Exploded()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 3.f)
		{
			Destroy(this);
		}
	
		if (mbActive[0])
		{
			DarkNebula* owner = dynamic_cast<DarkNebula*>(GetOwner());
			if (owner != nullptr)
			{
				DarkNebula_Fire* fire1 = new DarkNebula_Fire(owner, Vector2(mGroundPos.x + 61.5f, mGroundPos.y));
				object::ActiveSceneAddGameObject(eLayerType::Effect, fire1);

				DarkNebula_Fire* fire2 = new DarkNebula_Fire(owner, Vector2(mGroundPos.x - 61.5f, mGroundPos.y));
				object::ActiveSceneAddGameObject(eLayerType::Effect, fire2);
			}

			mbActive[0] = false;
		}
		else if (mDuration >= 0.2f && mbActive[1])
		{
			DarkNebula* owner = dynamic_cast<DarkNebula*>(GetOwner());
			if (owner != nullptr)
			{
				DarkNebula_Fire* fire1 = new DarkNebula_Fire(owner, Vector2(mGroundPos.x + 79.5f, mGroundPos.y));
				object::ActiveSceneAddGameObject(eLayerType::Effect, fire1);

				DarkNebula_Fire* fire2 = new DarkNebula_Fire(owner, Vector2(mGroundPos.x - 79.5f, mGroundPos.y));
				object::ActiveSceneAddGameObject(eLayerType::Effect, fire2);
			}

			mbActive[1] = false;
		}
		else if (mDuration >= 0.4f && mbActive[2])
		{
			DarkNebula* owner = dynamic_cast<DarkNebula*>(GetOwner());
			if (owner != nullptr)
			{
				DarkNebula_Fire* fire1 = new DarkNebula_Fire(owner, Vector2(mGroundPos.x + 97.5f, mGroundPos.y));
				object::ActiveSceneAddGameObject(eLayerType::Effect, fire1);

				DarkNebula_Fire* fire2 = new DarkNebula_Fire(owner, Vector2(mGroundPos.x - 97.5f, mGroundPos.y));
				object::ActiveSceneAddGameObject(eLayerType::Effect, fire2);
			}

			mbActive[2] = false;
		}
		else if (mDuration >= 0.6f && mbActive[3])
		{
			DarkNebula* owner = dynamic_cast<DarkNebula*>(GetOwner());
			if (owner != nullptr)
			{
				DarkNebula_Fire* fire1 = new DarkNebula_Fire(owner, Vector2(mGroundPos.x + 115.5f, mGroundPos.y));
				object::ActiveSceneAddGameObject(eLayerType::Effect, fire1);

				DarkNebula_Fire* fire2 = new DarkNebula_Fire(owner, Vector2(mGroundPos.x - 115.5f, mGroundPos.y));
				object::ActiveSceneAddGameObject(eLayerType::Effect, fire2);
			}

			mbActive[3] = false;
		}
		else if (mDuration >= 0.8f && mbActive[4])
		{
			DarkNebula* owner = dynamic_cast<DarkNebula*>(GetOwner());
			if (owner != nullptr)
			{
				DarkNebula_Fire* fire1 = new DarkNebula_Fire(owner, Vector2(mGroundPos.x + 133.5f, mGroundPos.y));
				object::ActiveSceneAddGameObject(eLayerType::Effect, fire1);

				DarkNebula_Fire* fire2 = new DarkNebula_Fire(owner, Vector2(mGroundPos.x - 133.5f, mGroundPos.y));
				object::ActiveSceneAddGameObject(eLayerType::Effect, fire2);
			}

			mbActive[4] = false;
		}
	}
}