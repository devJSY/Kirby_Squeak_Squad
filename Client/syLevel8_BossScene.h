#pragma once
#include "syScene.h"
#include "syDefaultKirby.h"

namespace sy
{
	class Level8_BossScene : public Scene
	{
	public:
		Level8_BossScene();
		virtual ~Level8_BossScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class DarkNebula*	mDarkNebula;
		class BackGround*	mPixelBG;
		float				mDuration;
	};
}
