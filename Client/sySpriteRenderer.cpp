#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syGameObject.h"
#include "syApplication.h"

namespace sy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mTex(nullptr)
		, mBMPRGB(RGB(0, 0, 0)) // default Black
		, mScale(Vector2::One)
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

		assert(mTex); // mTex�� nullptr �̸� ����

		if (mTex->GetType() == eTextureType::Bmp)
		{
			TransparentBlt(hdc								// �Ű� �׷��� dc
				, (int)pos.x, (int)pos.y					// hdc �� ���� ���� ��ġ
				, int(mTex->GetWidth() * mScale.x)
				, int(mTex->GetHeight() * mScale.y)			// hdc �� ���� ���� ��ġ ���� ������ �׸��� ����	
				, mTex->GetHdc()							// �̹����� ������ hdc
				, 0, 0										// �̹��� ������
				, mTex->GetWidth(), mTex->GetHeight()		// �ڸ� �̹��� ������
				, mBMPRGB);									// �̹������� ������ ����
		}
		else if (mTex->GetType() == eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTex->GetImage(), (int)pos.x, (int)pos.y
				, (int)(mTex->GetWidth() * mScale.x)
				, (int)(mTex->GetHeight() * mScale.y));
		}
	}
}