#pragma once
#include "syScene.h"

namespace sy
{
    class GambleGalaxyScene : public Scene
    {
	public:
		GambleGalaxyScene();
		virtual ~GambleGalaxyScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

	private:
		eLevelType mType;

    };
}

