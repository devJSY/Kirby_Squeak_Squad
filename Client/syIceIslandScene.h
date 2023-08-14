#pragma once
#include "syScene.h"

namespace sy
{
    class IceIslandScene : public Scene
    {
	public:
		IceIslandScene();
		virtual ~IceIslandScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

		void SetActiveUI(eStageState type);
		void SetClearActiveUI(eStageState type);

	private:
		void CreateDot();
		void CreateStageUI();

		void StageExit();
		void Boss();

	private:
		eLevelType mLevelType;
		class Level_BG* mlevelBG;

		bool mbActiveUI[1];
		class UI* ExitUI;
		class StepUI* mStepUI[1];
		class StarUI* mStarUI[1];
		class NumberUI* mNumberUI[1];

		std::vector<class DotUI*> mDots[1];
		eStageState mCurStageState;

		float mEnterTime;
		class Zoom_Effect* mZoom;
		bool mbSceneChange;
    };
}

