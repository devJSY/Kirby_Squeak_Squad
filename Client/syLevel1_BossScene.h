#pragma once
#include "syScene.h"
#include "syDefaultKirby.h"

namespace sy
{
	class Level1_BossScene : public Scene
	{
	public:
		Level1_BossScene();
		virtual ~Level1_BossScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class KingDedede*	mKingDedede;
		class BackGround*	mPixelBG;
		class PortalUI* 	mPortalUI;
	};
}
