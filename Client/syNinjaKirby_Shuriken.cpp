#include "syNinjaKirby_Shuriken.h"
#include "syPlayer.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "sySound.h"
#include "sySoundManager.h"
#include "syAnimator.h"
#include "syTransform.h"
#include "syTime.h"
#include "syCollider.h"
#include "sySceneManager.h"
#include "syEnemy.h"

namespace sy
{
	NinjaKirby_Shuriken::NinjaKirby_Shuriken(Player* owner)
		: Effects(owner)
		, mState(eShurikenState::Move)
		, mDir()
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mCollider(nullptr)
		, mStuckTarget(nullptr)
		, mStuckOffset(Vector2::Zero)
		, mDuration(0.f)
	{
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(GetOwner()->GetComponent<Transform>()->GetPosition());

		// 텍스쳐 로드
		Texture* Ninja_Shuriken_Tex = ResourceManager::Load<Texture>(L"Ninja_Shuriken_Tex", L"..\\Resources\\Effect\\Ninja_Shuriken.bmp");
		Texture* Ninja_Shuriken_Stuck_Tex = ResourceManager::Load<Texture>(L"Ninja_Shuriken_Stuck_Tex", L"..\\Resources\\Effect\\Ninja_Shuriken_Stuck.bmp");
		Texture* Destroy_Tex = ResourceManager::Load<Texture>(L"Destroy_Tex", L"..\\Resources\\Effect\\Block_Destroy.bmp");

		mAnimator = GetComponent<Animator>();


		mAnimator->CreateAnimation(Ninja_Shuriken_Tex, L"Ninja_Shuriken", Vector2(0.f, 0.f), Vector2(23.f, 16.f), Vector2(23.f, 0.f), 0.01f, 4);
		mAnimator->CreateAnimation(Ninja_Shuriken_Stuck_Tex, L"Ninja_Shuriken_Stuck_Right", Vector2(0.f, 0.f), Vector2(14.f, 21.f), Vector2(14.f, 0.f), 1.f, 1);
		mAnimator->CreateAnimation(Ninja_Shuriken_Stuck_Tex, L"Ninja_Shuriken_Stuck_Left", Vector2(14.f, 0.f), Vector2(14.f, 21.f), Vector2(-14.f, 0.f), 1.f, 1);

		mAnimator->CreateAnimation(Ninja_Shuriken_Stuck_Tex, L"Ninja_Shuriken_Stuck_Right_Blink", Vector2(0.f, 0.f), Vector2(14.f, 21.f), Vector2(0.f, 21.f), 0.05f, 2);
		mAnimator->CreateAnimation(Ninja_Shuriken_Stuck_Tex, L"Ninja_Shuriken_Stuck_Left_Blink", Vector2(14.f, 0.f), Vector2(14.f, 21.f), Vector2(0.f, 21.f), 0.05f, 2);

		mAnimator->CreateAnimation(Destroy_Tex, L"Destroy_Animation", Vector2(0.f, 0.f), Vector2(16.f, 16.f), Vector2(16.f, 0.f), 0.05f, 5);

		mAnimator->PlayAnimation(L"Ninja_Shuriken", true);

		ResourceManager::Load<Sound>(L"NinjaKirby_ShurikenSound", L"..\\Resources\\Sound\\Effect\\NinjaStar.wav")->Play(false);

		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Vector2(23.f, 16.f));
	}

	NinjaKirby_Shuriken::~NinjaKirby_Shuriken()
	{
	}

	void NinjaKirby_Shuriken::Initialize()
	{
		Effects::Initialize();
	}

	void NinjaKirby_Shuriken::Update()
	{
		// 픽셀충돌 체크
		CheckPixelCollision();

		if (mStuckTarget != nullptr && mStuckTarget->GetGameObjectState() == eGameObjectState::Dead)
		{
			mAnimator->PlayAnimation(L"Destroy_Animation", false);
			mState = eShurikenState::Dead;
		}

		switch (mState)
		{
		case eShurikenState::Move:
			Move();
			break;
		case eShurikenState::Stuck:
			Stuck();
			break;
		case eShurikenState::Blink:
			Blink();
			break;
		case eShurikenState::Dead:
			Dead();
			break;
		default:
			break;
		}


		Effects::Update();
	}

	void NinjaKirby_Shuriken::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void NinjaKirby_Shuriken::OnCollisionEnter(Collider* other)
	{
		// 플레이어와 충돌무시
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (player != nullptr)
			return;

		if (mDir == eDirection::RIGHT)
		{
			Vector2 pos = mTransform->GetPosition();
			pos.x += 5.f;
			mTransform->SetPosition(pos);

			mAnimator->PlayAnimation(L"Ninja_Shuriken_Stuck_Right", true);
			mState = eShurikenState::Stuck;
			mDuration = 0.f;
		}
		else
		{
			Vector2 pos = mTransform->GetPosition();
			pos.x -= 5.f;
			mTransform->SetPosition(pos);

			mAnimator->PlayAnimation(L"Ninja_Shuriken_Stuck_Left", true);
			mState = eShurikenState::Stuck;
			mDuration = 0.f;
		}


		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());
		Vector2 Dir = other->GetOwner()->GetComponent<Transform>()->GetPosition() - mTransform->GetPosition();
		mStuckOffset = Dir;

		SceneManager::GetPlayer()->SetHitEnemy(enemy);
		enemy->TakeHit(50, Dir);
		enemy->SetHPBarUIRenderTrig(true);
	
		mStuckTarget = enemy;
	}

	void NinjaKirby_Shuriken::CheckPixelCollision()
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

		Vector2 ColPos = mCollider->GetPosition();
		Vector2 ColSize = mCollider->GetSize();

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

		if (mState == eShurikenState::Move)
		{
			if (RBColor == RGB(0, 255, 0) || RTColor == RGB(0, 255, 0))
			{
				Vector2 pos = mTransform->GetPosition();
				pos.x += 5.f;
				mTransform->SetPosition(pos);

				mAnimator->PlayAnimation(L"Ninja_Shuriken_Stuck_Right", true);
				mState = eShurikenState::Stuck;
				mDuration = 0.f;
			}

			if (LBColor == RGB(0, 255, 0) || LTColor == RGB(0, 255, 0))
			{
				Vector2 pos = mTransform->GetPosition();
				pos.x -= 5.f;
				mTransform->SetPosition(pos);

				mAnimator->PlayAnimation(L"Ninja_Shuriken_Stuck_Left", true);
				mState = eShurikenState::Stuck;
				mDuration = 0.f;
			}
		}

	}

	void NinjaKirby_Shuriken::Move()
	{
		// 상하 이동
		Vector2 pos = mTransform->GetPosition();
		if (mDir == eDirection::RIGHT)
			pos.x += 300.f * Time::DeltaTime();
		else 
			pos.x -= 300.f * Time::DeltaTime();
		mTransform->SetPosition(pos);


		mDuration += Time::DeltaTime();
		if (mDuration > 5.f)
		{
			mAnimator->PlayAnimation(L"Destroy_Animation", false);
			mState = eShurikenState::Dead;
			mDuration = 0.f;
		}
	}
	void NinjaKirby_Shuriken::Stuck()
	{
		if (mStuckTarget != nullptr)
		{
			Vector2 pos = mStuckTarget->GetComponent<Transform>()->GetPosition();
			pos -= mStuckOffset;
			mTransform->SetPosition(pos);
		}

		mDuration += Time::DeltaTime();
		if (mDuration > 3.f)
		{
			if (mDir == eDirection::RIGHT)
				mAnimator->PlayAnimation(L"Ninja_Shuriken_Stuck_Right_Blink", true);
			else
				mAnimator->PlayAnimation(L"Ninja_Shuriken_Stuck_Left_Blink", true);

			mState = eShurikenState::Blink;
			mDuration = 0.f;
		}
	}

	void NinjaKirby_Shuriken::Blink()
	{
		if (mStuckTarget != nullptr)
		{
			Vector2 pos = mStuckTarget->GetComponent<Transform>()->GetPosition();
			pos -= mStuckOffset;
			mTransform->SetPosition(pos);
		}

		mDuration += Time::DeltaTime();
		if (mDuration > 2.f)
		{
			mAnimator->PlayAnimation(L"Destroy_Animation", false);
			mState = eShurikenState::Dead;
			mDuration = 0.f;
		}
	}

	void NinjaKirby_Shuriken::Dead()
	{
		if (mAnimator->IsActiveAnimationComplete())
		{
			Destroy(this);
		}
	}
}