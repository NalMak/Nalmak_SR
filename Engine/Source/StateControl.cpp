#include "..\Include\StateControl.h"

#include "IState.h"


StateControl::StateControl(Desc * _desc)
{
}

StateControl::~StateControl()
{
	Release();
}

void StateControl::Initialize()
{
	assert("Please Set Init State" && m_state);

	for (auto state : m_stateList)
		state.second->Initialize();

	m_state->EnterState();

}

void StateControl::Update()
{
	assert("State is nullptr" && m_state);
	m_state->UpdateState();

}

void StateControl::LateUpdate()
{
}

void StateControl::Release()
{
	for (auto& state : m_stateList)
	{
		SAFE_DELETE(state.second);
	}
	m_stateList.clear();

}

void StateControl::InitState(wstring _stateName)
{
	if (m_stateList.end() == m_stateList.find(_stateName))
		assert("Can't find state that name" && 0);

	m_state = m_stateList[_stateName];

}

void StateControl::SetState(wstring _stateName)
{
	if (m_stateList.end() == m_stateList.find(_stateName))
		assert("Can't find state that name" && 0);

	assert("Current State is nullptr! Please call InitState func" && m_state);

	m_state->ExitState();

	m_state = m_stateList[_stateName];

	m_state->EnterState();
}

bool StateControl::CompareState(wstring _stateName)
{
	assert("Current state is nullptr" && m_state);

	if (m_stateList.find(_stateName) == m_stateList.end())
		return false;

	if (m_stateList[_stateName] == m_state)
		return true;

	return false;
}

void StateControl::SetInteger(wstring _key, int _value)
{
	m_blackBoardInteger[_key] = _value;
}

void StateControl::SetFloat(wstring _key, float _value)
{
	m_blackBoardFloat[_key] = _value;
}

void StateControl::SetVector3(wstring _key, const Vector3 & _value)
{
	m_blackBoardVector3[_key] = _value;
}



int StateControl::GetInteger(wstring _key)
{
	if (m_blackBoardInteger.find(_key) == m_blackBoardInteger.end())
	{
		assert(L"Can't find integer data has that key!" && 0);
	}

	return m_blackBoardInteger[_key];
}

float StateControl::GetFloat(wstring _key)
{
	if (m_blackBoardFloat.find(_key) == m_blackBoardFloat.end())
	{
		assert(L"Can't find integer data has that key!" && 0);
	}

	return m_blackBoardFloat[_key];
}

const Vector3 & StateControl::GetVector3(wstring _key)
{
	if (m_blackBoardVector3.find(_key) == m_blackBoardVector3.end())
	{
		assert(L"Can't find integer data has that key!" && 0);
	}

	return m_blackBoardVector3[_key];
}

