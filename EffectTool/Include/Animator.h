#pragma once
#include "Component.h"
class MeshRenderer;


// Mesh Renderer�� ������쿡�� �۵�!
// Mehs Renderer�� material�� ������ 0�� Texture�� �ִϸ��̼� �����ش�
// sprite�� ������� �ؽ����� 0������ ������ �ε��������� �����̴�
// Resource �����ȿ� xxxx_0, xxxx_1 �� ���� �ؽ��ĸ� �����ϸ� xxxx��� �̸����� ��������Ʈ�� ������ش�
class NALMAK_DLL Animator :
	public Component
{
public:
	struct Desc
	{
		UINT maxIndex = 0;
		UINT startIndex = 0;
		float interval = 0.05f;
		float timer = 0;
		wstring spriteName = L"default";


		bool isNormal = false;
		bool loop = true;
	};
public:
	Animator(Desc* _desc);
	~Animator();
private:
	// Component��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Release() override;
private:
	size_t m_maxIndex;
	size_t m_currentIndex = 0;;
	float m_interval = 0.1f;
	float m_timer = 0;
	bool m_isNormal = false;
	bool m_loop = true;
	wstring m_animName;
	Texture* m_spriteDiffuseData;
	Texture* m_spriteNormalData;
	bool m_isPlay;
	bool m_isSleep;

public:
	void Play(wstring _spriteName);
	void Stop();
	void Resume();
	void SetInterval(float _interval) { m_interval = _interval; }
	bool IsPlay() { return m_isPlay; }
	void SetLoop(bool _loop) { m_loop = _loop; }
	wstring GetAnimationName()const { return m_animName; }
	LPDIRECT3DTEXTURE9 GetDiffuseSprite();
	LPDIRECT3DTEXTURE9 GetNormalSprite();
	size_t GetAnimationIndex() { return m_currentIndex; }

private:
	TimeManager* m_time;
};

