#pragma once
#include "syScene.h"

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
		class Video* mVideo;

	};
}

