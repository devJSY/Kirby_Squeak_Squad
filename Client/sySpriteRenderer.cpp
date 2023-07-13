#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syGameObject.h"
#include "syApplication.h"
#include "syCamera.h"

namespace sy
{
	SpriteRenderer::SpriteRenderer()
		: mbAffectCamera(true)
		, Component(eComponentType::SpriteRenderer)
		, mTex(nullptr)
		, mBMPRGB(RGB(0, 0, 0)) // default Black
		, mScale(Vector2::One)
		, mAlpha(1.0f)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		assert(tr); // tr�� nullptr �̸� ����
		Vector2 pos = tr->GetPosition();		

		if (mbAffectCamera)
			pos = Camera::CalculatePosition(pos);

		assert(mTex); // mTex�� nullptr �̸� ����

		if (mTex->GetType() == eTextureType::Bmp)
		{
			TransparentBlt(hdc											// �Ű� �׷��� dc
				, int(pos.x - ((mTex->GetWidth() * mScale.x) / 2.0f))	// hdc �� ���� ���� ��ġ
				, int(pos.y - ((mTex->GetHeight() * mScale.y) / 2.0f))	// ������ �߾����� ����
				, int(mTex->GetWidth() * mScale.x)
				, int(mTex->GetHeight() * mScale.y)						// hdc �� ���� ���� ��ġ ���� ������ �׸��� ����	
				, mTex->GetHdc()										// �̹����� ������ hdc
				, 0, 0													// �̹��� ������
				, mTex->GetWidth(), mTex->GetHeight()					// �ڸ� �̹��� ������
				, mBMPRGB);			
		}
		else if (mTex->GetType() == eTextureType::AlphaBmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			// 0.0f ~ 1.0f -> 0 ~ 255
			int alpha = (int)(mAlpha * 255.0f);
			if (alpha <= 0)
				alpha = 0;
			func.SourceConstantAlpha = alpha; // 0 ~ 255

			AlphaBlend(hdc												// �Ű� �׷��� dc
				, int(pos.x - ((mTex->GetWidth() * mScale.x) / 2.0f))	// hdc �� ���� ���� ��ġ
				, int(pos.y - ((mTex->GetHeight() * mScale.y) / 2.0f))	// ������ �߾����� ����
				, int(mTex->GetWidth() * mScale.x)
				, int(mTex->GetHeight() * mScale.y)						// hdc �� ���� ���� ��ġ ���� ������ �׸��� ����	
				, mTex->GetHdc()										// �̹����� ������ hdc
				, 0, 0													// �̹��� ������
				, mTex->GetWidth(), mTex->GetHeight()					// �ڸ� �̹��� ������
				, func);
		}
		else if (mTex->GetType() == eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTex->GetImage()
				, (int)(pos.x - ((mTex->GetWidth() * mScale.x) / 2.0f))
				, (int)(pos.y - ((mTex->GetHeight() * mScale.y) / 2.0f))
				, (int)(mTex->GetWidth() * mScale.x)
				, (int)(mTex->GetHeight() * mScale.y));


			//// ���� ���ϴ� �ȼ��� ����ȭ ��ų��
			//Gdiplus::ImageAttributes imageAtt = {};

			//// ����ȭ ��ų �ȼ� �� ����
			//imageAtt.SetColorKey(Gdiplus::Color(100,100,100)
			//	, Gdiplus::Color(255,255,255));

			//Gdiplus::Graphics graphics(hdc);
			//graphics.DrawImage(mTexture->GetImage()
			//	, Gdiplus::Rect
			//	(
			//		(int)(pos.x - (mTexture->GetWidth() * mScale.x / 2.0f))
			//		, (int)(pos.y - (mTexture->GetHeight() * mScale.y / 2.0f))
			//		, (int)(mTexture->GetWidth() * mScale.x)
			//		, (int)(mTexture->GetHeight() * mScale.y)
			//	)
			//	, 0, 0, mTexture->GetWidth(), mTexture->GetHeight()
			//	, Gdiplus::UnitPixel
			//	, &imageAtt);
		}
	}
}