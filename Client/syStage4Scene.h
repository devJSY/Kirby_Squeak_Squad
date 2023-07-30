#pragma once
#include "syScene.h"
#include "syDefaultKirby.h"

namespace sy
{
	class Stage4Scene : public Scene
	{
	public:
		Stage4Scene();
		virtual ~Stage4Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class BackGround* mPixelBG;
	};
}
