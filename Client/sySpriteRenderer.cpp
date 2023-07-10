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
		assert(tr); // tr이 nullptr 이면 에러
		Vector2 pos = tr->GetPosition();


		assert(mImage); // mImage이 nullptr 이면 에러
		TransparentBlt(hdc								// 옮겨 그려질 dc
			, (int)pos.x, (int)pos.y					// hdc 의 렌더 시작 위치
			, mImage->GetWidth(), mImage->GetHeight()	// hdc 의 렌더 시작 위치 부터 어디까지 그릴것 인지	
			, mImage->GetHdc()							// 이미지를 가져올 hdc
			, 0, 0										// 이미지 시작점
			, mImage->GetWidth(), mImage->GetHeight()	// 자를 이미지 사이즈
			, mBMPRGB);									// 이미지에서 삭제할 색상
	}
}