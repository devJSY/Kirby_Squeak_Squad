#pragma once
#include "syScene.h"

namespace sy
{
	class PrismPlainsScene : public Scene
	{
	public:
		PrismPlainsScene();
		virtual ~PrismPlainsScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

	private:
		eLevelType mType;
		class Level_BG* mlevelBG;

	};
}
