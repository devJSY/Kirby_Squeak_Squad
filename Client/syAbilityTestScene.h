#pragma once
#include "syScene.h"

namespace sy
{
	class AbilityTestScene : public Scene
	{
	public:
		AbilityTestScene();
		virtual ~AbilityTestScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;

	private:
		class BackGround* mPixelBG;

	};
}
