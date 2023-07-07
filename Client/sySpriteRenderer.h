#pragma once
#include "syComponent.h"


namespace sy
{
    class SpriteRenderer : public Component
    {
	public:
		SpriteRenderer();
		virtual ~SpriteRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void Render(HDC hdc) override;

		void SetPenRGB(BYTE r, BYTE g, BYTE b) { mPenRGB = RGB(r,g,b); };
		void SetBrushRGB(BYTE r, BYTE g, BYTE b) { mBrushRGB = RGB(r,g,b); };

    private:
		COLORREF mPenRGB;
		COLORREF mBrushRGB;
    };
}
