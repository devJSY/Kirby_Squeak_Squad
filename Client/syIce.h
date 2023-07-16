#pragma once
#include "syEnemy.h"

namespace sy
{
	class Ice : public Enemy
	{
	public:
		Ice();
		virtual ~Ice();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
	};
}
