#pragma once
#include "syScene.h"

namespace sy
{
	class IntroScene : public Scene
	{
	public:
		IntroScene();
		virtual ~IntroScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

	private:
		class Video*	mVideo;
	};
}
