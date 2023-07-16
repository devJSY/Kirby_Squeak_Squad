#pragma once
#include "syEnemy.h"

namespace sy
{
	class Brown : public Enemy
	{
	public:
		Brown();
		virtual ~Brown();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
	};
}
