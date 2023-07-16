#pragma once
#include "syEnemy.h"

namespace sy
{
	class BlockEnemy : public Enemy
	{
	public:
		BlockEnemy();
		virtual ~BlockEnemy();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:
	};
}
