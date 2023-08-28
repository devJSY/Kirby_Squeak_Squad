#pragma once
#include "syScene.h"

namespace sy
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
		AbilityTest,
	};

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
		void SetClearActiveUI(eLevelState type);
		eLevelState GetCurLevelState() const { return mCurLevelState; }

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
		void AbilityTest();
		
	private:
		eLevelType					mLevelType;
		class Level_BG*				mlevelBG;		
		bool						mbActiveUI[10];
		class PlacardUI*			mPlacardUI[10];
		class StarUI*				mStarUI[10];
		class NumberUI*				mNumberUI[10];
		std::vector<class DotUI*>	mDots[10]; 
		eLevelState					mCurLevelState;
		float						mEnterTime;
		class Zoom_Effect*			mZoom;
		bool						mbSceneChange;
	};
}
