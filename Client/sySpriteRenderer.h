#pragma once
#include "syComponent.h"
#include "syTexture.h"

namespace sy
{
	using namespace math;
    class SpriteRenderer : public Component
    {
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetTexture(Texture* tex) { mTex = tex; }
		void SetBmpRGB(BYTE r, BYTE g, BYTE b) { mBMPRGB = RGB(r, g, b); };
		void SetScale(Vector2 scale) { mScale = scale; }		

		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }

		void SetAffectedCamera(bool enable) { mbAffectedCamera = enable; }
		bool GetAffectedCamera() { return mbAffectedCamera; }

	private:
		Texture*	mTex;
		COLORREF	mBMPRGB;
		Vector2		mScale;
		float		mAlpha;
		bool		mbAffectedCamera;
    };
}
