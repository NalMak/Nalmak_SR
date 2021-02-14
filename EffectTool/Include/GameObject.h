#pragma once

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "Nalmak_Include.h"
#include "ICycle.h"
#include "Collision.h"

BEGIN(Nalmak)
USING(Nalmak)




class Component;
class Transform;

//#define MAKEPROTOTYPE GameObject::MakePrototype
#define INSTANTIATE GameObject::Instantiate
#define DESTROY GameObject::Destroy
typedef pair<string, Component*> ComponentData;

class NALMAK_DLL GameObject : public ICycle
{
	friend class ObjectManager;
	friend class PrototypeManager;

public:

private:
	explicit GameObject() = default;
	~GameObject() = default;

public:
	//static GameObject* MakePrototype(wstring _name);
	static GameObject* Instantiate(int _tag = 0, wstring _name = L"default");
	//static GameObject* Instantiate(GameObject* _prototype);
	//static GameObject* Instantiate(wstring _prototypeName);

	static void Destroy(GameObject* _obj);



	template <typename T>
	GameObject* AddComponent(typename T::Desc* _desc)
	{
		string name = typeid(T).name();

		Component* component = Component::Create<T>(_desc);
		assert(L"Fail to Create Componet!" && component);

		m_newComponents.emplace_back(pair<string, Component*>(name, component));
		component->SetGameObject(this);
		component->SetTransform(m_transform);
		return this;
	}

	template <typename T>
	GameObject* AddComponent()
	{
		string name = typeid(T).name();

		typename T::Desc desc;
		Component* component = Component::Create<T>(&desc);
		assert(L"Fail to Create Componet!" && component);

		m_newComponents.emplace_back(pair<string, Component*>(name, component));
		component->SetGameObject(this);
		component->SetTransform(m_transform);
		return this;
	}
private:
	void AddComponent(const pair<string, Component*>&  _component);
public:
	template <typename T>
	T* GetComponent()
	{
		for (auto& component : m_components)
		{
			if (component.first == typeid(T).name())
				return (T*)component.second;
		}
		for (auto& component : m_newComponents)
		{
			if (component.first == typeid(T).name())
				return (T*)component.second;
		}

		return nullptr;
	}

	template <typename T>
	void DeleteComponent()
	{
		string name = typeid(T).name();
		for (auto iter = m_components.begin(); iter != m_components.end(); ++iter)
		{
			if ((*iter).first == typeid(T).name())
			{
				(*iter).second->m_dead = true;
				return;
			}
		}
	}
private:
	void InitializeComponents();
private:
	void OnEnable() override;
	void OnDisable() override;
	void Initialize() override;
	void Update() override;
	void LateUpdate() override;
	void PreRender() override;
	void OnTriggerEnter(Collisions& _col) override;
	void OnTriggerStay(Collisions& _col) override;
	void OnTriggerExit(Collisions& _col) override;
	void Release() override;

private:
	vector<pair<string, Component*>> m_components;
	vector<pair<string, Component*>> m_newComponents;
private:
	Transform* m_transform = nullptr;

public:
	Transform* GetTransform() { assert(L"Isn't Exist Transform!" && m_transform);  return m_transform; }
private:
	bool m_active;
	bool m_dead;
	bool m_static;
	bool m_dontDestroy;
	wstring m_name;
	int m_tag;
	Collisions m_collisions;
	Collisions m_preCollisions;


public:
	void SetParents(Transform* _parents);
	void SetParents(GameObject* _parents);

	void SetDontDestroy(bool _dontDestroy);
	void SetStatic(bool _static) { m_static = _static; }
	void SetActive(bool _active);
	void SetName(wstring _name) { m_name = _name; }
	void SetTag(int _tag);
	bool IsActive() const { return m_active; }
	bool IsAlive() const { return !m_dead; }
	const wstring GetName() const { return m_name; }
	int GetTag() const { return m_tag; }
	bool IsStatic() const { return m_static; }
	GameObject* SetPosition(const Vector3& _pos);
	GameObject* SetPosition(float _x, float _y, float _z);
	GameObject* SetScale(const Vector3& _scale);
	GameObject* SetScale(float _x, float _y, float _z);
	GameObject* SetRotation(float _xAngle, float _yAngle, float _zAngle);

	void ResetCollision();

private:
	bool m_preCollisionState;
	bool m_curCollisionState;
public:
	void CollisionNotify(Collision _collision);
	void CollisionUpdate();
};
END
#endif // !__GAMEOBJECT_H__
