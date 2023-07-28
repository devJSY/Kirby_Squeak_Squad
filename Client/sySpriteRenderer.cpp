#include "sySpriteRenderer.h"
#include "syTransform.h"
#include "syGameObject.h"
#include "syApplication.h"
#include "syCamera.h"

namespace sy
{
	SpriteRenderer::SpriteRenderer()
		: Component(eComponentType::SpriteRenderer)
		, mTex(nullptr)
		, mBMPRGB(RGB(255, 0, 255)) // default Magenta
		, mAlpha(1.0f)
		, mbAffectedCamera(true)
		, mbRenderTrig(true)
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
		assert(mTex); // mTex이 nullptr 이면 에러

		GameObject* gameObj = GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		if (mbRenderTrig)
		{
			mTex->Render(hdc
				, GetOwner()->GetComponent<Transform>()->GetPosition()
				, Vector2(mTex->GetWidth(), mTex->GetHeight())
				, Vector2::Zero
				, Vector2(mTex->GetWidth(), mTex->GetHeight())
				, mbAffectedCamera
				, tr->GetScale()
				, mAlpha
				, mBMPRGB
				, tr->GetRotation());
		}
	}
}