#pragma once
#include "syScene.h"

namespace sy
{
	class StageScene : public Scene
	{
	public:
		StageScene();
		virtual ~StageScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

	private:

	};
}
