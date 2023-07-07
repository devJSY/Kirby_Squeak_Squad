#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syGameObject.h"

namespace sy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mPenRGB(RGB(0,0,0)) // default Black
		, mBrushRGB(RGB(0,0,0)) // default Black
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
	 
		HPEN hNewPen = CreatePen(PS_SOLID, 1, mPenRGB); // ���ο� �� ����
		HPEN hOldPen = (HPEN)SelectObject(hdc, hNewPen); // ������ ������ ����

		HBRUSH hNewBrush = CreateSolidBrush(mBrushRGB); // ���ο� �귯�� ����
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush); // ������ �귯���� ����

		Ellipse(hdc, int(pos.x - 50), int(pos.y - 50)
			, int(pos.x + 50), int(pos.y + 50));


		SelectObject(hdc, hOldPen); // ������ ����ϴ���(Newpen)�� ������  
		DeleteObject(hNewPen);

		SelectObject(hdc, hOldBrush); // ������ ����ϴ���(Newpen)�� ������  
		DeleteObject(hNewBrush);
	}
}