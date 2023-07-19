#pragma once
#include "syScene.h"

namespace sy
{
	class LevelSelectScene : public Scene
	{
	public:
		LevelSelectScene();
		virtual ~LevelSelectScene();

		virtual void Initialize();
		virtual void Update();
		virtual void Render(HDC hdc);

		virtual void Enter() override;
		virtual void Exit() override;
		
	private:
		class Inventory* mInventory;
		class AbilityUI* mAbilityUI;
		class HPbarUI* mHPbarUI;
		class LifeUI* mLifeUI;
	};
}
