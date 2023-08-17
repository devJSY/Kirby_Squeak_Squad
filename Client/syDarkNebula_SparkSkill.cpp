#include "syDarkNebula_SparkSkill.h"
#include "syDarkNebula.h"
#include "syTime.h"
#include "syTransform.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syCollider.h"
#include "syAnimator.h"
#include "syPlayer.h"
#include "syDefaultKirby.h"
#include "syDarkNebula_SparkSkill_Collider.h"
#include "syObject.h"

namespace sy
{
	DarkNebula_SparkSkill::DarkNebula_SparkSkill(DarkNebula* owner)
		: Effects(owner)
		, mTransform(nullptr)
		, mDuration(0.f)
	{
		mTransform = GetComponent<Transform>();
		mTransform->SetPosition(Vector2(128.f, 86.f));

		// Left
		mCollider[0] = new DarkNebula_SparkSkill_Collider(Vector2(20.f, 76.f), Vector2(20.f, 130.f));
		// Right
		mCollider[1] = new DarkNebula_SparkSkill_Collider(Vector2(240.f, 76.f), Vector2(20.f, 130.f));
		// Top
		mCollider[2] = new DarkNebula_SparkSkill_Collider(Vector2(128.f, 0.f), Vector2(210.f, 20.f));
		// Bottom
		mCollider[3] = new DarkNebula_SparkSkill_Collider(Vector2(128.f, 150.f), Vector2(210.f, 20.f));

		object::ActiveSceneAddGameObject(eLayerType::Effect, mCollider[0]);
		object::ActiveSceneAddGameObject(eLayerType::Effect, mCollider[1]);
		object::ActiveSceneAddGameObject(eLayerType::Effect, mCollider[2]);
		object::ActiveSceneAddGameObject(eLayerType::Effect, mCollider[3]);		

		// 局聪皋捞记 积己
		Animator* animator = GetComponent<Animator>();
		Texture* DarkNebula_SparkSkill_Tex = ResourceManager::Load<Texture>(L"DarkNebula_SparkSkill_Tex", L"..\\Resources\\Enemy\\Boss\\DarkNebula\\DarkNebula_SparkSkill.bmp");

		animator->CreateAnimation(DarkNebula_SparkSkill_Tex, L"DarkNebula_SparkSkill", Vector2::Zero, Vector2(256.f, 192.f), Vector2(256.f, 0.f), 0.05f, 3);

		animator->PlayAnimation(L"DarkNebula_SparkSkill", true);
	}

	DarkNebula_SparkSkill::~DarkNebula_SparkSkill()
	{
	}

	void DarkNebula_SparkSkill::Initialize()
	{
		Effects::Initialize();
	}

	void DarkNebula_SparkSkill::Update()
	{
		mDuration += Time::DeltaTime();

		if (mDuration > 2.f)
		{
			Destroy(this);
			Destroy(mCollider[0]);
			Destroy(mCollider[1]);
			Destroy(mCollider[2]);
			Destroy(mCollider[3]);
		}

		Effects::Update();
	}

	void DarkNebula_SparkSkill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}
}