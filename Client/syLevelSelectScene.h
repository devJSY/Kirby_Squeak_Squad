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

		void SetActiveUI(eLevelType type);

	private:
		void CreateDot();
		void CreateLevelUI();		
		
	private:
		eLevelType mType;
		class Level_BG* mlevelBG;		

		bool mbActiveUI[9];
		class PlacardUI* mPlacardUI[9];
		class StarUI* mStarUI[9];
		class NumberUI* mNumberUI[9];

		std::vector<DotUI*> mDots[9]; 
	};
}
