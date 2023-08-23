#pragma once
#include "syScene.h"
#include "syDefaultKirby.h"

namespace sy
{
	class BackGround;

	class Level7_BossScene : public Scene
	{
	public:
		Level7_BossScene();
		virtual ~Level7_BossScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		BackGround*			mBackGround;
		BackGround*			mPixelBG;
		class PortalUI*		mPortalUI;
		float				mBgSpeed;
		float				mDuration;
		bool				mbBGChange;
	};
}
