#pragma once
#include "syComponent.h"
#include "syImage.h"

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

		void SetImage(Image* image) { mImage = image; }
		void SetBmpRGB(BYTE r, BYTE g, BYTE b) { mBMPRGB = RGB(r, g, b); };
	
	private:
		Image*		mImage;
		COLORREF	mBMPRGB;
    };
}
