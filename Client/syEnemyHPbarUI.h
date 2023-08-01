#pragma once
#include "syUI.h"

namespace sy
{
	class Texture;
	class EnemyHPbarUI : public UI
	{
	public:
		EnemyHPbarUI(class Enemy* owner);
		virtual ~EnemyHPbarUI();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetRenderTrig(bool trig) { mbRenderTrig = trig; }

	private:
		Enemy*		mOwner;
		Texture*	mBarTex;
		Texture*	mHPTex;

		float		mRenderHP;
		bool		mbRenderTrig;
	};

}