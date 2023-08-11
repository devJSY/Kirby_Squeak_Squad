#pragma once
#include "syScene.h"
#include "syDefaultKirby.h"

namespace sy
{
	class Level1_Stage4Scene : public Scene
	{
	public:
		Level1_Stage4Scene();
		virtual ~Level1_Stage4Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class BackGround* mPixelBG;
	};
}
