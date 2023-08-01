#pragma once
#include "syUI.h"

namespace sy
{
	class Texture;
	class EnemyHPbarUI : public UI
	{
	public:
		EnemyHPbarUI();
		virtual ~EnemyHPbarUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Texture* mBarTex;
		Texture* mHPTex;

		bool mbRenderTrig;
	};

}