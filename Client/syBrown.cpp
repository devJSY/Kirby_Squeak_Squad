#include "syBrown.h"

namespace sy
{
	Brown::Brown()
		: Enemy(eAbilityType::None)
	{
	}

	Brown::~Brown()
	{
	}

	void Brown::Initialize()
	{
		Enemy::Initialize();
	}

	void Brown::Update()
	{
		Enemy::Update();
	}

	void Brown::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
}