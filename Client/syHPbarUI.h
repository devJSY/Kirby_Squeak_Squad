#pragma once
#include "syUI.h"

namespace sy
{
	class Texture;
	class HPbarUI : public UI
	{
	public:
		HPbarUI();
		virtual ~HPbarUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

	private:
		Texture* mBarTex;
		Texture* mPinkTex;
		Texture* mRedTex;

		float	mDecreaseHP;
		float	mIncreaseHP;
		float	mHpBarDelay;
	};

}