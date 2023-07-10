#pragma once
#include "syResource.h"

namespace sy
{
	class Image : public Resource
	{
	public:
		Image();
		virtual ~Image();

		virtual HRESULT Load(const std::wstring& path) override;

		UINT GetWidth() { return mWidth; }
		UINT GetHeight() { return mHeight; }
		HDC GetHdc() { return mHdc; }

	private:
		HBITMAP mBitmap;	// ���ҽ� ��Ʈ��
		HDC mHdc;			// ���ҽ� ��Ʈ���� dc
		UINT mWidth;		// ���ҽ� ����
		UINT mHeight;		// ���ҽ� ����
	};
}
