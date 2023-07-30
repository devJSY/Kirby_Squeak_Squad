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

		float GetAlpha() { return mAlpha; }
		void SetAlpha(float alpha) { mAlpha = alpha; }

		void SetAffectedCamera(bool enable) { mbAffectedCamera = enable; }
		bool GetAffectedCamera() { return mbAffectedCamera; }

		void SetRenderTrig(bool Trig) { mbRenderTrig = Trig; }
		bool GetRenderTrig() { return mbRenderTrig; }

		void SetCameraSpeedRatio(Vector2 ratio) { mCameraSpeedRatio = ratio; }

		void SetRednerLeftTop(Vector2 lt) { mLeftTop = lt; }
		void SetRenderSize(Vector2 size) { mSize = size; }

	private:
		Texture*	mTex;
		COLORREF	mBMPRGB;
		float		mAlpha;
		bool		mbAffectedCamera;
		bool		mbRenderTrig;
		Vector2		mCameraSpeedRatio;
		Vector2     mSize;
		Vector2		mLeftTop;
    };
}
