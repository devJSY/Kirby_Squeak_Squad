#pragma once
#include "syScene.h"
#include "syDefaultKirby.h"

namespace sy
{
	class Stage1Scene : public Scene
	{
	public:
		Stage1Scene();
		virtual ~Stage1Scene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class BackGround* mPixelBG;
	};
}
