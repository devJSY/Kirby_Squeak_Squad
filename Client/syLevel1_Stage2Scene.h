#pragma once
#include "syScene.h"
#include "syDefaultKirby.h"

namespace sy
{
	class Level1_Stage2Scene : public Scene
	{
	public:
		Level1_Stage2Scene();
		virtual ~Level1_Stage2Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class BackGround* mPixelBG;
	};
}
