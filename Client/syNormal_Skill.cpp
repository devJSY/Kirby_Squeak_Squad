#include "syNormal_Skill.h"
#include "syTexture.h"
#include "syTransform.h"
#include "syResourceManager.h"
#include "syAnimator.h"
#include "syCollider.h"
#include "sySceneManager.h"
#include "syTime.h"
#include "syEnemy.h"

namespace sy
{
	Normal_Skill::Normal_Skill(GameObject* owner)
		: Effects(owner)
		, mAnimator(nullptr)
		, mTransform(nullptr)
		, mDir(eDirection::RIGHT)
		, mbDestroy(false)
	{
		mDir = GetOwner()->GetComponent<Transform>()->GetDirection();

		mTransform = GetComponent<Transform>();

		Texture* Normal_Skill_tex = ResourceManager::Load<Texture>(L"Normal_Skill", L"..\\Resources\\Effect\\Normal_Skill.bmp");
		Texture* Normal_Skill_Destory_tex = ResourceManager::Load<Texture>(L"Normal_Skill_Destory", L"..\\Resources\\Effect\\Normal_Skill_Destory.bmp");

		Transform* tr = GetComponent<Transform>();
		Vector2 vec = owner->GetComponent<Transform>()->GetPosition();
		tr->SetPosition(vec);

		Collider* col = AddComponent<Collider>();
		col->SetSize(Vector2(24.f, 24.f));

		mAnimator = GetComponent<Animator>();

		mAnimator->CreateAnimation(Normal_Skill_tex, L"Normal_Skill", Vector2(72.f, 0.f), Vector2(24.f, 24.f), Vector2(-24.f, 0.f), 0.03f, 4);
		mAnimator->CreateAnimation(Normal_Skill_Destory_tex, L"Normal_Skill_Destory", Vector2(0.f, 0.f), Vector2(40.22f, 42.f), Vector2(42.f, 0.f), 0.03f, 9);

		mAnimator->PlayAnimation(L"Normal_Skill", true);
	}

	Normal_Skill::~Normal_Skill()
	{
	}

	void Normal_Skill::Initialize()
	{
		Effects::Initialize();
	}

	void Normal_Skill::Update()
	{
		if (mbDestroy)
		{
			if (mAnimator->IsActiveAnimationComplete())
			{
				Destroy(this);
			}
		}
		else
		{
			CheckPixelCollision();

			Vector2 pos = mTransform->GetPosition();
			if (mDir == eDirection::RIGHT)
				pos.x += 200.f * Time::DeltaTime();
			else
				pos.x -= 200.f * Time::DeltaTime();
			mTransform->SetPosition(pos);
		}

		Effects::Update();
	}

	void Normal_Skill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Normal_Skill::OnCollisionEnter(Collider* other)
	{
		Enemy* enemy = dynamic_cast<Enemy*>(other->GetOwner());

		if (enemy == nullptr)
			return;

		Vector2 Dir = Vector2::Zero;

		if (mDir == eDirection::RIGHT)
			Dir = Vector2(1.f, 0);
		else
			Dir = Vector2(-1.f, 0);

		enemy->TakeHit(50, Dir);

		mbDestroy = true;
		mAnimator->PlayAnimation(L"Normal_Skill_Destory");
	}

	void Normal_Skill::OnCollisionStay(Collider* other)
	{
	}

	void Normal_Skill::OnCollisionExit(Collider* other)
	{
	}

	void Normal_Skill::CheckPixelCollision()
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

		if (LTColor == RGB(0, 255, 0) || LTColor == RGB(255, 0, 0)
			|| RTColor == RGB(0, 255, 0) || RTColor == RGB(255, 0, 0)
			|| LBColor == RGB(0, 255, 0) || LBColor == RGB(255, 0, 0)
			|| RBColor == RGB(0, 255, 0) || RBColor == RGB(255, 0, 0))
		{
			mbDestroy = true;
			mAnimator->PlayAnimation(L"Normal_Skill_Destory");
		}
	}
}