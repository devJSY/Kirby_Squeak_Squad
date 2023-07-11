#pragma once
#include "syResource.h"

namespace sy
{
	using namespace enums;
	class Texture : public Resource
	{
	public:
		Texture();
		virtual ~Texture();

		virtual HRESULT Load(const std::wstring& path) override;

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }
		eTextureType GetType() { return mType; }
		Gdiplus::Image* GetImage() { return mImage; }

	private:
		eTextureType mType;	// Ȯ���� Ÿ��
		Gdiplus::Image* mImage;		// png ��ü

		HBITMAP mBitmap;	// ���ҽ� ��Ʈ��
		HDC mHdc;			// ���ҽ� ��Ʈ���� dc
		UINT mWidth;		// ���ҽ� ����
		UINT mHeight;		// ���ҽ� ����
	};
}
