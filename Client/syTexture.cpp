#include "syTexture.h"
#include "syApplication.h"
#include "syResourceManager.h"

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

			// GDIplus �� Gdiplus::Image ��ü�� ����
			mImage = Gdiplus::Image::FromFile(path.c_str());

			if (mImage == nullptr)
				return E_FAIL;

			mWidth = mImage->GetWidth();
			mHeight = mImage->GetHeight();
		}

		return S_OK;
	}
}