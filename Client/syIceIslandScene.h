#pragma once
#include "syScene.h"

namespace sy
{
    class IceIslandScene : public Scene
    {
	public:
		IceIslandScene();
		virtual ~IceIslandScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

	private:
    };
}

