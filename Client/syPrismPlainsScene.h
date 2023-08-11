#pragma once
#include "syScene.h"

namespace sy
{
	class PrismPlainsScene : public Scene
	{
	public:
		PrismPlainsScene();
		virtual ~PrismPlainsScene();

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
		void Stage1();
		void StageBoss();

	private:
		eLevelType mLevelType;
		class Level_BG* mlevelBG;

		bool mbActiveUI[7];					
		class UI* ExitUI;
		class StepUI* mStepUI[7];
		class StarUI* mStarUI[7];
		class NumberUI* mNumberUI[7];

		std::vector<class DotUI*> mDots[7];
		eStageState mCurStageState;

		float mEnterTime;
		class Zoom_Effect* mZoom;
		bool mbSceneChange;
	};
}
