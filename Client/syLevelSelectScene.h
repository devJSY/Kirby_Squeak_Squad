#pragma once
#include "syScene.h"

namespace sy
{
	class LevelSelectScene : public Scene
	{
	public:
		LevelSelectScene();
		virtual ~LevelSelectScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);
		
	private:
	};
}
