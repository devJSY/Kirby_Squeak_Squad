#pragma once
#include "syScene.h"

namespace sy
{
	class Inventory;
	class AbilityUI;
	class HPbarUI;
	class LifeUI;

	class SceneManager
	{
	private:
		// 객체 생성 차단
		SceneManager();
		~SceneManager() {};

	public:
		static void Release();
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);

		template <typename T>
		static T* CreateScene(const std::wstring& name)
		{
			T* Scene = new T();
			Scene->SetName(name);
			mScenes.insert(std::make_pair(name, Scene));
			mActiveScene = Scene;

			return Scene;
		}

		static Scene* LoadScene(const std::wstring& name);
		static Scene* GetActiveScene() { return mActiveScene; }
		static Scene* GetScene(const std::wstring& name);

	private:
		static void UIInitialize();


	private:
		// 트리 자료구조
		// Key Value 구조로 이루어져 있다
		// Key는 데이터를 검색하는 용도
		// Value 는 실제 저장할 데이터
		static std::map<std::wstring, Scene*> mScenes;
		static Scene* mActiveScene;

		// UI 객체는 게임에 1개만 존재하기때문에 SceneManager에서 관리
		static Inventory* mInventory;
		static AbilityUI* mAbilityUI;
		static HPbarUI* mHPbarUI;
		static LifeUI* mLifeUI;
	};
}
