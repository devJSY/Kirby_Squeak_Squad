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
		// Animation or SpriteRenderer ���� ȣ���
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
			//// ���� ���ϴ� �ȼ��� ����ȭ ��ų��
			Gdiplus::ImageAttributes imageAtt = {};
			//// ����ȭ ��ų �ȼ� �� ����
			imageAtt.SetColorKey(Gdiplus::Color(100, 100, 100)
				, Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);

			// ȸ������ 
			graphics.TranslateTransform((float)pos.x, (float)pos.y);	// ȸ����ų ������ġ ����
			graphics.RotateTransform(rotate);
			graphics.TranslateTransform(-(float)pos.x, -(float)pos.y);	// ȸ����ų ������ġ ����

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