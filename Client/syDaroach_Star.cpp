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
	Daroach_Star::Daroach_Star(Daroach* owner)
		: Effects(owner)
		, mTransform(nullptr)
		, mAnimator(nullptr)
		, mCollider(nullptr)
		, mRigidBody(nullptr)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();
		mAnimator = GetComponent<Animator>();
		mCollider = GetComponent<Collider>();
		mRigidBody = GetComponent<Rigidbody>();

		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());
		mCollider->SetSize(Vector2(50.f, 50.f));

		if (GetOwner()->GetComponent<Transform>()->GetDirection() == eDirection::RIGHT)
			mRigidBody->SetVelocity(Vector2(100.f, 0.f));
		else
			mRigidBody->SetVelocity(Vector2(-100.f, 0.f));

		mRigidBody->SetFloat(true);

		// 애니메이션 생성
		Texture* Daroach_Star_Tex = ResourceManager::Load<Texture>(L"Daroach_Star_Tex", L"..\\Resources\\Enemy\\Boss\\Daroach\\Daroach_Star.bmp");
		mAnimator->CreateAnimation(Daroach_Star_Tex, L"Daroach_Star", Vector2::Zero, Vector2(50.f, 50.f), Vector2(50.f, 0.f), 0.1f, 8);
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
		mDuration += Time::DeltaTime();

		if (mDuration > 5.f)
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
		else
			PixelTex = ResourceManager::Find<Texture>(L"Stage1_Pixel");

		if (PixelTex == nullptr)
			return;

		// Offset 픽셀 좌상단위치 설정
		Vector2 offset = Vector2::Zero;

		if (CurSceneName == L"AbilityTestScene"
			|| CurSceneName == L"King_Dedede_Stage_Pixel"
			|| CurSceneName == L"Daroach_Pixel"
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
			if (vel.x > 0.f)
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
}