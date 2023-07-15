#pragma once
#include "syScene.h"
#include "syVideo.h"

namespace sy
{
	class TitleScene : public Scene
	{
	public:
		TitleScene();
		virtual ~TitleScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		Video* mVideo;

	};
}

