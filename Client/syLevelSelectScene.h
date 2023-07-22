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

		virtual void Enter() override;
		virtual void Exit() override;
		
	private:
		eLevelType mType;
		class Level_BG* mlevelBG;

		class PlacardUI* mPlacardUI[9];
		class StarUI* mStarUI[9];
		class NumberUI* mNumberUI[9];

	};
}
