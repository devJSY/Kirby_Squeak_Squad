#pragma once
#include "syScene.h"

namespace sy
{
    class NatureNotchScene : public Scene
    {
	public:
		NatureNotchScene();
		virtual ~NatureNotchScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

	private:
		void CreateStageUI();

		void StageExit();

	private:
		eLevelType mLevelType;

		class UI* ExitUI;
		eStageState mCurStageState;

		float mEnterTime;
		class Zoom_Effect* mZoom;
    };
}

