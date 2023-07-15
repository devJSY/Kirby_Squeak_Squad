#pragma once
#include "syScene.h"
#include "syVideo.h"

namespace sy
{
	class EndingScene : public Scene
	{
	public:
		EndingScene();
		virtual ~EndingScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		Video* mVideo;
	};
}
