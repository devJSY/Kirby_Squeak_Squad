#pragma once
#include "syScene.h"

namespace sy
{
	enum class eLevelState;

	class TunnelScene : public Scene
	{
	public:
		TunnelScene();
		virtual ~TunnelScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

		void SetPrevSceneName(const std::wstring& name) { mPrevSceneName = name; }

	private:
		class Tunnel_BG*	mBackGround;
		eLevelState			mCurLevelState;
		float				mPassedTime;

		std::wstring		mPrevSceneName;
	};
}


