#include "syHotHead.h"

namespace sy
{
	HotHead::HotHead()
		: Enemy(eAbilityType::Fire)
	{
	}

	HotHead::~HotHead()
	{
	}

	void HotHead::Initialize()
	{
		Enemy::Initialize();
	}

	void HotHead::Update()
	{
		Enemy::Update();
	}

	void HotHead::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
}