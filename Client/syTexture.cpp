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
		// 생성할 이미지가 이미 만들어져있는 리소스인지 확인
		Texture* image = ResourceManager::Find<Texture>(name);
		if (image != nullptr)
			return image;

		// 인자로 들어온 크기로 텍스쳐 생성
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

		// 생성한 텍스쳐를 ResourceManager에 넣어서 관리
		image->SetName(name);
		ResourceManager::Insert<Texture>(name, image);

		// 인자로 들어온 색으로 채움
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

			// 인자로 들어온 경로로 부터 이미지파일을 Load 한다
			mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0
				, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

			if (mBitmap == nullptr)
				return E_FAIL;

			// 받아온 mBitmap의 정보를 info 에 저장
			BITMAP info = {};
			GetObject(mBitmap, sizeof(BITMAP), &info);

			// 32bit 비트맵 파일인경우 AlphaBmp 타입으로 설정한다
			if (info.bmBitsPixel == 32)
				mType = eTextureType::AlphaBmp;

			mWidth = info.bmWidth;
			mHeight = info.bmHeight;

			HDC mainDC = Application::GetHdc();
			mHdc = CreateCompatibleDC(mainDC); // mainDC로부터 새로운 DC생성하여 멤버변수로 저장

			// 비트맵과 DC를 연결
			HBITMAP deafultBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
			DeleteObject(deafultBitmap);
		}
		else if (ext == L"png")
		{
			mType = eTextureType::Png;

			ULONG_PTR ptrGdi;                        //Gdi+사용을 위한 포인터객체
			Gdiplus::GdiplusStartupInput inputGdi;         //gdi+입력값객체
			Gdiplus::GdiplusStartup(&ptrGdi, &inputGdi, 0);   //시작


			// image.png 파일을 이용하여 Texture 객체를 생성합니다.
			mImage = Gdiplus::Image::FromFile(path.c_str());

			//파일로부터 비트맵받기
			m_pBitGdi = Gdiplus::Bitmap::FromFile(path.c_str());

			//비트맵정보를 HBITMAP m_hBit에 복사
			m_pBitGdi->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &mBitmap);

			HDC mainDC = Application::GetHdc();
			mHdc = ::CreateCompatibleDC(mainDC);

			// 비트맵과 DC 연결
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
		// Animation or SpriteRenderer 에서 호출됨
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

			////// 내가 원하는 픽셀을 투명화 시킬떄
			//Gdiplus::ImageAttributes imageAtt = {};
			////// 투명화 시킬 픽셀 색 범위
			//imageAtt.SetColorKey(Gdiplus::Color(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb))
			//	, Gdiplus::Color(GetRValue(rgb), GetGValue(rgb), GetBValue(rgb)));

			//Gdiplus::Graphics graphics(hdc);

			//// 회전적용 
			//graphics.TranslateTransform((float)pos.x, (float)pos.y);	// 회전시킬 기준위치 지정
			//graphics.RotateTransform(rotate);
			//graphics.TranslateTransform(-(float)pos.x, -(float)pos.y);	// 회전시킬 기준위치 복구

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