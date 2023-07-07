#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syGameObject.h"

namespace sy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mPenRGB(RGB(0,0,0)) // default Black
		, mBrushRGB(RGB(0,0,0)) // default Black
		, mRenderType(eRenderType::Rectangle)
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
		assert(tr); // tr이 nullptr 이면 에러
		Vector2 pos = tr->GetPosition();
	 
		HPEN hNewPen = CreatePen(PS_SOLID, 1, mPenRGB); // 새로운 펜 생성
		HPEN hOldPen = (HPEN)SelectObject(hdc, hNewPen); // 생성한 펜으로 설정

		HBRUSH hNewBrush = CreateSolidBrush(mBrushRGB); // 새로운 브러쉬 생성
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hNewBrush); // 생성한 브러쉬로 설정


		if (mRenderType == eRenderType::Rectangle)
		{
			Rectangle(hdc, int(pos.x - 50), int(pos.y - 50)
				, int(pos.x + 50), int(pos.y + 50));
		}
		else if (mRenderType == eRenderType::Ellipse)
		{
			Ellipse(hdc, int(pos.x - 50), int(pos.y - 50)
				, int(pos.x + 50), int(pos.y + 50));
		}		


		SelectObject(hdc, hOldPen); // 기존에 사용하던것(Newpen)을 리턴함  
		DeleteObject(hNewPen);

		SelectObject(hdc, hOldBrush); // 기존에 사용하던것(Newpen)을 리턴함  
		DeleteObject(hNewBrush);
	}
}