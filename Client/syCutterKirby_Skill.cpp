#include "syCutterKirby_Skill.h"
#include "syPlayer.h"
#include "syTexture.h"
#include "syResourceManager.h"
#include "syTransform.h"
#include "syCollider.h"
#include "syAnimator.h"
#include "syFireKirby.h"
#include "syObject.h"
#include "syIce_Enemy.h"

namespace sy
{
	CutterKirby_Skill::CutterKirby_Skill(Player* owner)
		: Effects(owner)
		, mDir()
	{
			// 플레이어 방향으로  Velocity 주고 반대반향으로 계속 Add Force
	}

	CutterKirby_Skill::~CutterKirby_Skill()
	{
	}

	void CutterKirby_Skill::Initialize()
	{
		Effects::Initialize();
	}

	void CutterKirby_Skill::Update()
	{

		Effects::Update();
	}

	void CutterKirby_Skill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void CutterKirby_Skill::OnCollisionEnter(Collider* other)
	{
	
	}

	void CutterKirby_Skill::OnCollisionStay(Collider* other)
	{
	}

	void CutterKirby_Skill::OnCollisionExit(Collider* other)
	{
	}
}