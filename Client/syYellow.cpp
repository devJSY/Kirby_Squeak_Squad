#include "syYellow.h"

namespace sy
{
	Yellow::Yellow()
		: Enemy(eAbilityType::None)
	{
	}

	Yellow::~Yellow()
	{
	}

	void Yellow::Initialize()
	{
		Enemy::Initialize();
	}

	void Yellow::Update()
	{
		Enemy::Update();
	}

	void Yellow::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
}