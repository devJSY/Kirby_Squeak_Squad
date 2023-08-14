#pragma once
#include "syScene.h"
#include "syDefaultKirby.h"

namespace sy
{
	class Level6_BossScene : public Scene
	{
	public:
		Level6_BossScene();
		virtual ~Level6_BossScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class BackGround* mPixelBG;
		class PortalUI* mPortalUI;
	};
}
