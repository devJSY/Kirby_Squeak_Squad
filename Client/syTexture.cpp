#include "syTexture.h"
#include "syApplication.h"
#include "syResourceManager.h"
#include "syCamera.h"
#include "syTime.h"

namespace sy
{
	Texture::Texture()
		: mType(eTextureType::None)
		, mImage(nullptr) 
		, mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{
	}

	Texture::~Texture()
	{
		//delete mImage;
		//mImage = nullptr;

		//DeleteObject(mBitmap);
		//mBitmap = NULL;
	}

	Texture* Texture::Create(const std::wstring& name, UINT width, UINT height, COLORREF rgb)
	{
		// ������ �̹����� �̹� ��������ִ� ���ҽ����� Ȯ��
		Texture* image = ResourceManager::Find<Texture>(name);
		if (image != nullptr)
			return image;

		// ���ڷ� ���� ũ��� �ؽ��� ����
		image = new Texture();
		image->SetWidth(width);
		image->SetHeight(height);

		HDC hdc = Application::GetHdc();
		HBITMAP bitmap = CreateCompatibleBitmap(hdc, width, height);
		image->SetHBitmap(bitmap);

		HDC bitmapHdc = CreateCompatibleDC(hdc);
		image->SetHdc(bitmapHdc);

		HBITMAP defaultBitmap = (HBITMAP)SelectObject(bitmapHdc, bitmap);
		DeleteObject(defaultBitmap);

		// ������ �ؽ��ĸ� ResourceManager�� �־ ����
		image->SetName(name);
		ResourceManager::Insert<Texture>(name, image);

		// ���ڷ� ���� ������ ä��
		HBRUSH brush = CreateSolidBrush(rgb);
		HBRUSH oldBrush = (HBRUSH)SelectObject(image->GetHdc(), brush);
		Rectangle(image->GetHdc(), -1, -1, image->mWidth + 1, image->mHeight + 1);
		SelectObject(image->GetHdc(), oldBrush);
		DeleteObject(oldBrush);

		return image;
	}

	HRESULT Texture::Load(const std::wstring& path)
	{
		std::wstring ext
			= path.substr(path.find_last_of(L".") + 1);

		if (ext == L"bmp")
		{
			mType = eTextureType::Bmp;

			// ���ڷ� ���� ��η� ���� �̹��������� Load �Ѵ�
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
				, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr)
				return E_FAIL;

			// �޾ƿ� mBitmap�� ������ info �� ����
			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			// 32bit ��Ʈ�� �����ΰ�� AlphaBmp Ÿ������ �����Ѵ�
			if (info.bmBitsPixel == 32)
				mType = eTextureType::AlphaBmp;

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = Application::GetHdc();
			mHdc = CreateCompatibleDC(mainDC); // mainDC�κ��� ���ο� DC�����Ͽ� ��������� ����

			// ��Ʈ�ʰ� DC�� ����
			HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(deafultBitmap);
		}
		else if (ext == L"png")
		{
			mType = eTextureType::Png;

			ULONG_PTR ptrGdi;                        //Gdi+����� ���� �����Ͱ�ü
			Gdiplus::GdiplusStartupInput inputGdi;         //gdi+�Է°���ü
			Gdiplus::GdiplusStartup(&ptrGdi, &inputGdi, 0);   //����


			// image.png ������ �̿��Ͽ� Texture ��ü�� �����մϴ�.
			mImage = Gdiplus::Image::FromFile(path.c_str());

			//���Ϸκ��� ��Ʈ�ʹޱ�
			m_pBitGdi = Gdiplus::Bitmap::FromFile(path.c_str());

			//��Ʈ�������� HBITMAP m_hBit�� ����
			m_pBitGdi->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &mBitmap);

			HDC mainDC = Application::GetHdc();
			mHdc = ::CreateCompatibleDC(mainDC);

			// ��Ʈ�ʰ� DC ����
			HBITMAP hPrevBit = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(hPrevBit);

			assert(mImage);

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}

		return S_OK;
	}

	void Texture::Render(HDC hdc
		, Vector2 pos
		, Vector2 size
		, Vector2 TexLeftTop
		, Vector2 TexSize
		, bool AffectedCamera
		, Vector2 CameraSpeedRatio
		, Vector2 scale
		, float Alpha
		, COLORREF rgb
		, float rotate
		, bool blink)
	{
		// Animation or SpriteRenderer ���� ȣ���
		if (mBitmap == nullptr && mImage == nullptr)
			return;

		if (AffectedCamera)
			pos = Camera::CalculatePosition(pos, CameraSpeedRatio);

		if (mType == eTextureType::Bmp)
		{
			TransparentBlt(hdc, (int)(pos.x - (size.x * scale.x / 2.0f))
				, (int)(pos.y - (size.y * scale.y / 2.0f))
				, int(size.x * scale.x)
				, int(size.y * scale.y)
				, mHdc
				, int(TexLeftTop.x), int(TexLeftTop.y), int(TexSize.x), int(TexSize.y)
				, rgb);
		}
		else if (mType == eTextureType::AlphaBmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			// 0.0f ~ 1.0f -> 0 ~ 255
			int alpha = (int)(Alpha * 255.0f);

			if (alpha <= 0)
				alpha = 0;

			static float blinkTime = 0.f;
			static float blinkalpha = 0.f;

			if (blink)
			{
				blinkTime += Time::DeltaTime();
				if (blinkTime > 0.1)
				{
					if (blinkalpha == 100) blinkalpha = 255;
					else blinkalpha = 100;
					blinkTime = 0;
				}

				alpha = (int)blinkalpha;
			}

			func.SourceConstantAlpha = alpha; // 0 ~ 255

			AlphaBlend(hdc, (int)(pos.x - (size.x * scale.x / 2.0f))
				, (int)(pos.y - (size.y * scale.y / 2.0f))
				, int(size.x * scale.x)
				, int(size.y * scale.y)
				, mHdc
				, int(TexLeftTop.x), int(TexLeftTop.y)
				, int(TexSize.x), int(TexSize.y)
				, func);
		}
		else if (mType == eTextureType::Png)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;

			GdiAlphaBlend(hdc, (int)(pos.x - (size.x * scale.x / 2.0f))
				, (int)(pos.y - (size.y * scale.y / 2.0f))
				, int(size.x * scale.x)
				, int(size.y * scale.y)
				, mHdc
				, int(TexLeftTop.x), int(TexLeftTop.y)
				, int(TexSize.x), int(TexSize.y)
				, func);

			////// ���� ���ϴ� �ȼ��� ����ȭ ��ų��
			//Gdiplus::ImageAttributes imageAtt = {};
			////// ����ȭ ��ų �ȼ� �� ����
			//imageAtt.SetColorKey(Gdiplus::Color(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb))
			//	, Gdiplus::Color(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)));

			//Gdiplus::Graphics graphics(hdc);

			//// ȸ������ 
			//graphics.TranslateTransform((float)pos.x, (float)pos.y);	// ȸ����ų ������ġ ����
			//graphics.RotateTransform(rotate);
			//graphics.TranslateTransform(-(float)pos.x, -(float)pos.y);	// ȸ����ų ������ġ ����

			//graphics.DrawImage(mImage
			//	, Gdiplus::Rect
			//	(
			//		(int)(pos.x - (size.x * scale.x / 2.0f))
			//		, (int)(pos.y - (size.y * scale.y / 2.0f))
			//		, (int)(size.x * scale.x)
			//		, (int)(size.y * scale.y)
			//	)
			//	, INT(TexLeftTop.x), INT(TexLeftTop.y)
			//	, INT(TexSize.x), INT(TexSize.y)
			//	, Gdiplus::UnitPixel
			//	, &imageAtt);
		}
	}
}