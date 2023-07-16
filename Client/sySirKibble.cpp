#include "sySirKibble.h"

namespace sy
{
	SirKibble::SirKibble()
		: Enemy(eAbilityType::Cutter)
	{
	}

	SirKibble::~SirKibble()
	{
	}

	void SirKibble::Initialize()
	{
		Enemy::Initialize();
	}

	void SirKibble::Update()
	{
		Enemy::Update();
	}

	void SirKibble::Render(HDC hdc)
	{
		Enemy::Render(hdc);
	}
}