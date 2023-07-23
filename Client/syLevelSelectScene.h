#pragma once
#include "syScene.h"

namespace sy
{
	class LevelSelectScene : public Scene
	{

	enum class eLevelState
	{
		Level1,
		Level2,
		Level3,
		Level4,
		Level5,
		Level6,
		Level7,
		Level8,
	};

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

		void Level1();
		void Level2();
		void Level3();
		void Level4();
		void Level5();
		void Level6();
		void Level7();
		void Level8();
		
	private:
		eLevelType mType;
		class Level_BG* mlevelBG;		

		bool mbActiveUI[9];
		class PlacardUI* mPlacardUI[9];
		class StarUI* mStarUI[9];
		class NumberUI* mNumberUI[9];

		std::vector<DotUI*> mDots[9]; 

		eLevelState mCurLevel;
	};
}
