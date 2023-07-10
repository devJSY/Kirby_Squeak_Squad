#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syGameObject.h"

namespace sy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mImage(nullptr)
		, mBMPRGB(RGB(0, 0, 0)) // default Black
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


		assert(mImage); // mImage�� nullptr �̸� ����
		TransparentBlt(hdc								// �Ű� �׷��� dc
			, (int)pos.x, (int)pos.y					// hdc �� ���� ���� ��ġ
			, mImage->GetWidth(), mImage->GetHeight()	// hdc �� ���� ���� ��ġ ���� ������ �׸��� ����	
			, mImage->GetHdc()							// �̹����� ������ hdc
			, 0, 0										// �̹��� ������
			, mImage->GetWidth(), mImage->GetHeight()	// �ڸ� �̹��� ������
			, mBMPRGB);									// �̹������� ������ ����
	}
}