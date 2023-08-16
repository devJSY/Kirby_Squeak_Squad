#include "syAbilityStar.h"
#include "syTransform.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syCollider.h"
#include "syTime.h"
#include "syAnimator.h"
#include "syPlayer.h"
#include "syRigidbody.h"
#include "sySceneManager.h"

namespace sy
{
	AbilityStar::AbilityStar(class Player* owner, eAbilityType type)
		: mOwner(owner)
		, mState(eAbilityStarState::Move)
		, mType(type)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mCollider(nullptr)
		, mRigidBody(nullptr)
		, mDuration(0.f)
		, mInhaled(false)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(mOwner->GetComponent<Transform>()->GetPosition());

		// 플레이어와 반대방향으로 생성
		if(mOwner->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
			mTransform->SetDirection(eDirection::LEFT);
		else
			mTransform->SetDirection(eDirection::RIGHT);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(20.f, 20.f));

		Texture* Portal_StarTex = ResourceManager::Load<Texture>(L"Portal_Star", L"..\\Resources\\UI\\Portal_Star.bmp");
		Texture* Monster_Death_Tex = ResourceManager::Load<Texture>(L"Monster_Death_Tex", L"..\\Resources\\Effect\\Monster_Death.bmp");

		mAnimator = AddComponent<Animator>();
		mAnimator->CreateAnimation(Portal_StarTex, L"Portal_Star", Vector2::Zero, Vector2(50.f, 30.f), Vector2(50.f, 0.f), 0.07f, 12);
		mAnimator->CreateAnimation(Monster_Death_Tex, L"AbilityStar_Death", Vector2(0.f, 0.f), Vector2(102.f, 102.f), Vector2(102.f, 0.f), 0.05f, 14);
				
		mAnimator->PlayAnimation(L"Portal_Star", true);

		mRigidBody = AddComponent<Rigidbody>();
		mRigidBody->SetVelocity(Vector2(0.f, -200.f));
	}

	AbilityStar::~AbilityStar()
	{
	}

	void AbilityStar::Initialize()
	{
		GameObject::Initialize();
	}

	void AbilityStar::Update()
	{
		// Inhaled 상태에선 중력적용 X
		if (mInhaled)
			mRigidBody->SetGround(true);

		mDuration += Time::DeltaTime();

		// 픽셀충돌 체크
		if(!mInhaled)
			CheckPixelCollision();

		switch (mState)
		{
		case eAbilityStarState::Move:
			Move();
			break;
		case eAbilityStarState::Dead:
			Dead();
			break;
		default:
			break;
		}

		GameObject::Update();
	}

	void AbilityStar::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void AbilityStar::CheckPixelCollision()
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
		Vector2 ColSize = mCollider->GetSize();

		Vector2 Left = Vector2(ColPos.x - (ColSize.x / 2.f), ColPos.y);
		Vector2 Right = Vector2(ColPos.x + (ColSize.x / 2.f), ColPos.y);
		Vector2 Top = Vector2(ColPos.x, ColPos.y - (ColSize.y / 2.f));
		Vector2 Bottom = Vector2(ColPos.x, ColPos.y + (ColSize.y / 2.f));

		Left += offset;
		Right += offset;
		Top += offset;
		Bottom += offset;

		COLORREF LeftColor = PixelTex->GetTexturePixel((int)Left.x, (int)Left.y);
		COLORREF RightColor = PixelTex->GetTexturePixel((int)Right.x, (int)Right.y);
		COLORREF TopColor = PixelTex->GetTexturePixel((int)Top.x, (int)Top.y);
		COLORREF BottomColor = PixelTex->GetTexturePixel((int)Bottom.x, (int)Bottom.y);

		// 상단 처리		
		if (TopColor == RGB(0, 255, 0))
		{
			Vector2 pos = mTransform->GetPosition();
			pos.y += 1.f;
			mTransform->SetPosition(pos);
		}

		// 바닥 처리 Y축 방향 변경
		if (BottomColor == RGB(0, 0, 255) || BottomColor == RGB(255, 0, 0))
		{
			mRigidBody->SetVelocity(Vector2(0.f, -200.f));
		}

		// 좌측 처리 방향 변경
		if (LeftColor == RGB(0, 255, 0))
		{
			if (mTransform->GetDirection() == eDirection::RIGHT)
				mTransform->SetDirection(eDirection::LEFT);
			else
				mTransform->SetDirection(eDirection::RIGHT);
		}

		// 우측 처리 방향 변경
		if (RightColor == RGB(0, 255, 0))
		{
			if (mTransform->GetDirection() == eDirection::RIGHT)
				mTransform->SetDirection(eDirection::LEFT);
			else
				mTransform->SetDirection(eDirection::RIGHT);
		}
	}

	void AbilityStar::Move()
	{
		if (mDuration > 5.f)
		{
			mState = eAbilityStarState::Dead;
			mAnimator->PlayAnimation(L"AbilityStar_Death", false);
		}

		Vector2 pos = mTransform->GetPosition();
		if (mTransform->GetDirection() == eDirection::RIGHT)
			pos.x += 50.f * Time::DeltaTime();
		else
			pos.x -= 50.f * Time::DeltaTime();
		mTransform->SetPosition(pos);
	}

	void AbilityStar::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}