#include "syTexture.h"
#include "syApplication.h"
#include "syResourceManager.h"
#include "syCamera.h"
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

	Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
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

			// GDIplus 로 Gdiplus::Image 객체를 생성
			mImage = Gdiplus::Image::FromFile(path.c_str());			
			
			if (mImage == nullptr || mImage->GetLastStatus() != Gdiplus::Status::Ok)
				return E_FAIL;

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}

		return S_OK;
	}

	void Texture::Render(HDC hdc
		, Vector2 pos
		, Vector2 size
		, Vector2 LeftTop
		, Vector2 RightBottom
		, bool AffectedCamera
		, Vector2 scale
		, float Alpha
		, COLORREF rgb
		, float rotate)
	{
		// Animation or SpriteRenderer 에서 호출됨
		if (mBitmap == nullptr && mImage == nullptr)
			return;

		if (AffectedCamera)
			pos = Camera::CalculatePosition(pos);

		if (mType == eTextureType::Bmp)
		{
			TransparentBlt(hdc, (int)(pos.x - (size.x * scale.x / 2.0f))
				, (int)(pos.y - (size.y * scale.y / 2.0f))
				, int(size.x * scale.x)
				, int(size.y * scale.y)
				, mHdc
				, int(LeftTop.x), int(LeftTop.y), int(RightBottom.x), int(RightBottom.y)
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
			func.SourceConstantAlpha = alpha; // 0 ~ 255

			AlphaBlend(hdc, (int)(pos.x - (size.x * scale.x / 2.0f))
				, (int)(pos.y - (size.y * scale.y / 2.0f))
				, int(size.x * scale.x)
				, int(size.y * scale.y)
				, mHdc
				, int(LeftTop.x), int(LeftTop.y)
				, int(RightBottom.x), int(RightBottom.y)
				, func);
		}
		else if (mType == eTextureType::Png)
		{
			//// 내가 원하는 픽셀을 투명화 시킬떄
			Gdiplus::ImageAttributes imageAtt = {};
			//// 투명화 시킬 픽셀 색 범위
			imageAtt.SetColorKey(Gdiplus::Color(100, 100, 100)
				, Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);

			// 회전적용 
			graphics.TranslateTransform((float)pos.x, (float)pos.y);	// 회전시킬 기준위치 지정
			graphics.RotateTransform(rotate);
			graphics.TranslateTransform(-(float)pos.x, -(float)pos.y);	// 회전시킬 기준위치 복구

			graphics.DrawImage(mImage
				, Gdiplus::Rect
				(
					(int)(pos.x - (size.x * scale.x / 2.0f))
					, (int)(pos.y - (size.y * scale.y / 2.0f))
					, (int)(size.x * scale.x)
					, (int)(size.y * scale.y)
				)
				, INT(LeftTop.x), INT(LeftTop.y)
				, INT(RightBottom.x), INT(RightBottom.y)
				, Gdiplus::UnitPixel
				, nullptr);
		}
	}
}