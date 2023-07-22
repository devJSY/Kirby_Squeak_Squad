#pragma once
#include "syScene.h"
#include "syDefaultKirby.h"

namespace sy
{
	class StageScene : public Scene
	{
	public:
		StageScene();
		virtual ~StageScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:

	};
}
