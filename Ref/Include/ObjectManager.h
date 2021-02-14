#pragma once

#ifndef __OBJECTMANAGER_H__
#define __OBJECTMANAGER_H__

#include "GameObject.h"
#include "Nalmak_Include.h"

// ������Ʈ ��� (����, ������Ʈ )
// ������Ʈ ����Ʈ�� Ŭ���̾�Ʈ���� ���� �±׸�ŭ �����ϸ�, ��� ������Ʈ��
// ������Ʈ�� ����Ѵ�. 
// ���� �� ������ ��û������, �� ������Ʈ ó���κп��� ó���� �Ѵ�
// -> �߰�����  GameObject�� INSTANTIATE�� ������û�� �ص� m_newGameObjectList�� ����
//    ���� ������ ó���κп�  m_gameObjectLists�� ���簡 �Ͼ��

BEGIN(Nalmak)
class ObjectManager
{
	DECLARE_SINGLETON(ObjectManager)
private:
	ObjectManager();
	~ObjectManager();
private:
	list<GameObject*> m_newGameObjectList;
	vector<list<GameObject*>> m_gameObjectLists;
public:
	void Initialize(_OBJECT_TAG _ObjectTag);
	void Update();
	void LateUpdate();
	void PreRender();
	void PostRender();
	void Release();
	void ReleaseScene();

	void DeleteList(_OBJECT_TAG _tag);
	void AddObject(GameObject* _obj);
	void ChangeTag(_OBJECT_TAG _tag, GameObject* _obj);
public:
	const list<GameObject*>& GetObjectList(_OBJECT_TAG _tag);
	GameObject* Find(const wstring& _name);
	GameObject* Find(_OBJECT_TAG _tag, const wstring& _name);
	GameObject* FindFirstObjectbyTag(_OBJECT_TAG _tag);

public:
	void MergeObjectList();

};
END
#endif

