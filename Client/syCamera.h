#pragma once
#include "syGameObject.h"

namespace sy
{
	enum class CAM_EFFECT
	{
		FADE_IN,
		FADE_OUT,
		NONE,
	};

	struct tCamEffect
	{
		CAM_EFFECT	eEffect;
		float		fDuration;
		float		fCurTime;
		COLORREF	TexColor; 
	};


	using namespace math;

	// ī�޶�� �⺻������ ȭ���� ���߾ӿ� �������ϵ��� �ϰ� ���� ���κп� ���������� �̵��Ѱ���ŭ ����������
	class Camera
	{
	public:
		static void Initalize();
		static void Update();
		static void Render(HDC hdc);

		static Vector2 CalculatePosition(Vector2 pos, Vector2 CameraSpeedRatio = Vector2::One) { return pos - (mDistance / CameraSpeedRatio); }

		static GameObject* GetTarget() { return mTarget; }
		static void SetTarget(GameObject* target) { mTarget = target; }

		static void SetCameraLimit(Vector2 limit) { mCameraLimit = limit; }
		static Vector2 GetCameraLimit() { return mCameraLimit; }

	public:
		static void fadeIn(float _fDuration, COLORREF color)
		{
			tCamEffect ef = {};
			ef.eEffect = CAM_EFFECT::FADE_IN;
			ef.fDuration = _fDuration;
			ef.fCurTime = 0.f;
			ef.TexColor = color;

			m_listCamEffect.push_back(ef);
		}

		static void fadeOut(float _fDuration, COLORREF color)
		{
			tCamEffect ef = {};
			ef.eEffect = CAM_EFFECT::FADE_OUT;
			ef.fDuration = _fDuration;
			ef.fCurTime = 0.f;
			ef.TexColor = color;

			m_listCamEffect.push_back(ef);
		}

	private:
		static Vector2 mResolution;			// ȭ�� �ػ�
		static Vector2 mLookPosition;		// ī�޶� �ٶ󺸰� �ִ� ��ġ
		static Vector2 mDistance;			// ����� �������� �̵��� �Ÿ�
		static GameObject* mTarget;			// ī�޶� �ٶ󺸴� ���� ������Ʈ

		static Vector2 mCameraLimit;		// ī�޶� �̵����� ���� Stage�� ����� �־��ָ��

		static std::list<tCamEffect>  m_listCamEffect;	// ī�޶� ȿ�� �̺�Ʈ ����Ʈ
		static class Texture* mWhiteTex;				// ī�޶� ȿ���� �ؽ���
		static class Texture* mBlackTex;				// ī�޶� ȿ���� �ؽ���
	};
}


