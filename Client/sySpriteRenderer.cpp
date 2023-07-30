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
		, mCameraSpeedRatio(Vector2::One)
		, mSize(Vector2::Zero)
		, mLeftTop(Vector2::Zero)
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
		assert(mTex); // mTex�� nullptr �̸� ����

		GameObject* gameObj = GetOwner();
		Transform* tr = gameObj->GetComponent<Transform>();

		// �⺻�� ����
		if (mSize == Vector2::Zero)
		{
			mSize = Vector2(mTex->GetWidth(), mTex->GetHeight());
		}

		if (mbRenderTrig)
		{
			mTex->Render(hdc
				, GetOwner()->GetComponent<Transform>()->GetPosition()
				, mSize
				, mLeftTop
				, mSize
				, mbAffectedCamera
				, mCameraSpeedRatio
				, tr->GetScale()
				, mAlpha
				, mBMPRGB
				, tr->GetRotation());
		}
	}
}