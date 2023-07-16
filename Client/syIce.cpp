#include "syIce.h"

namespace sy
{
	Ice::Ice()
		: Enemy(eAbilityType::Ice)
	{
	}

	Ice::~Ice()
	{
	}

	void Ice::Initialize()
	{
		Enemy::Initialize();
	}

	void Ice::Update()
	{
		Enemy::Update();
	}

	void Ice::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
}