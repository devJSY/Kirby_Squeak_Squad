#pragma once
#include "syScene.h"

namespace sy
{
	class OpeningScene : public Scene
	{
	public:
		OpeningScene();
		virtual ~OpeningScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class Video* mVideo;
		float		mPassedTime;
		bool		mbSoundPlay;

	};
}

