#pragma once
#include "syScene.h"

namespace sy
{
    class SecretSeaScene : public Scene
    {
	public:
		SecretSeaScene();
		virtual ~SecretSeaScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

	private:
		eLevelType mType;

    };
}
