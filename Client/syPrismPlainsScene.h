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

	private:
		void CreateDot();
		void CreateStageUI();

		void StageExit();
		void Stage1();
		void Stage2();
		void Stage3();
		void Stage4();
		void Stage5();
		void Ex();
		void StageBoss();

	private:
		eLevelType mType;
		class Level_BG* mlevelBG;

		bool mbActiveUI[8];					// 0번 ExitUI 1 ~ 7번 그외 UI
		class UI* ExitUI;
		class StepUI* mStepUI[7];
		class StarUI* mStarUI[7];
		class NumberUI* mNumberUI[7];

		std::vector<class DotUI*> mDots[7];
		eStageState eCurStageState;
	};
}
