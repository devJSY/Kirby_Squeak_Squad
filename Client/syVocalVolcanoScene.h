#pragma once
#include "syScene.h"

namespace sy
{
    class VocalVolcanoScene :
        public Scene
    {
	public:
		VocalVolcanoScene();
		virtual ~VocalVolcanoScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

	private:
    };
}
