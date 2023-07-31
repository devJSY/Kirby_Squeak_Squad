#include "syNormal_Skill.h"

namespace sy
{
	Normal_Skill::Normal_Skill(GameObject* owner)
		: Effects(owner)
	{
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
		Effects::Update();
	}

	void Normal_Skill::Render(HDC hdc)
	{
		Effects::Render(hdc);
	}

	void Normal_Skill::OnCollisionEnter(Collider* other)
	{
	}

	void Normal_Skill::OnCollisionStay(Collider* other)
	{
	}

	void Normal_Skill::OnCollisionExit(Collider* other)
	{
	}
}