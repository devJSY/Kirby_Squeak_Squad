#include "syTexture.h"
#include "syApplication.h"

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
		delete mImage;
		mImage = nullptr;

		DeleteObject(mBitmap);
		mBitmap = NULL;
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

			if (mImage == nullptr)
				return E_FAIL;

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}

		return S_OK;
	}
}