#pragma once
#include "syScene.h"

namespace sy
{
    enum class eDanceSceneType
    {
        BossClear,
        NormalClear,
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

        void SetType(eDanceSceneType type) { mType = type; }
        void SetNextSceneName(const std::wstring& name) { mNextSceneName = name; }

    private:
        eDanceSceneType     mType;
        std::wstring        mNextSceneName;
        class Video*        mVideo;
        float		        mPassedTime;
        bool		        mbSoundPlay;
        bool			    mbSceneChange;
    };
}

