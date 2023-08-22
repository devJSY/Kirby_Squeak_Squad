#pragma once
#include "syScene.h"

namespace sy
{
    enum class eDanceSceneType
    {
        NormalClear,
        BossClear,
        End,
    };

    class DanceScene : public Scene
    {
	public:
        DanceScene();
		virtual ~DanceScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

    private:
        eDanceSceneType mType;

    };
}

