#pragma once
#include "syScene.h"

namespace sy
{
    class CushyCloudScene : public Scene
    {
	public:
		CushyCloudScene();
		virtual ~CushyCloudScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

	private:
		eLevelType mLevelType;

		eStageState mCurStageState;
    };
}
