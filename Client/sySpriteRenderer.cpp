#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syGameObject.h"

namespace sy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
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

		Ellipse(hdc, int(100 + pos.x), int(100 + pos.y)
			, int(200 + pos.x), int(200 + pos.y));
	}
}