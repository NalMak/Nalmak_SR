#include "DeviceManager.h"


USING(Nalmak)
IMPLEMENT_SINGLETON(DeviceManager)

DeviceManager::DeviceManager()
{
}
DeviceManager::~DeviceManager()
{
	Release();
}
HRESULT DeviceManager::Initialize(UINT _wincx, UINT _wincy, HWND _handle, bool _windowMode)
{
	m_msQualityLev = 0;
	m_behaviourFlag = 0;
	m_displayMode = _windowMode;

	Check_SDKVersion();
	CheckMultiSample();

	D3DPRESENT_PARAMETERS desc;
	ZeroMemory(&desc, sizeof(D3DPRESENT_PARAMETERS));

	m_hwnd = _handle;
	CreateSwapChain(&desc,_wincx,_wincy,_handle);
	CreateDevice(&desc,_handle);

	return S_OK;
}


void DeviceManager::Check_SDKVersion()
{
	// 1. ���� ���� ��ġ(�׷��� ī��)�� ����� üũ.
	// ���� �����ϰ� �ִ� ����� �����ϴ� ���������� SDK ����
	// Direct3D9 ��ü�� ���ʷ� �Ҵ� �Ǿ���ϴ� ��ü�̸�, ���� �������� �Ҵ������Ѵ�.
	// �ش� ��ü�� ���� �������̽� IDirect3D9 ���� �ϵ����� ���õǾ� �ش� �ϵ������ ������ �����Ѵ�.
	m_SDK = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9 Caps;								// Capability �ɷ�, ���� 
												// IDirect3D9 ��ü�� ���� �ϵ������ ������ �����Ѵ�.
	ZeroMemory(&Caps, sizeof(D3DCAPS9));

	// ���ڷ� ���޵Ǵ� ������ġ(�׷��� ī��)�� ���� ������ �˻��Ѵ�. 
	// �ټ��� �ϵ��� ����Ǿ� ���� �ÿ��� IDirect3D9::GetAdapterCount �� ���� ����� �ϵ��� �˻��Ѵ�.
	// D3DDEVTYPE_HAL HAL(Hardware Abstraction Layer) �ϵ���� �߻� ����
	// �پ��� ������ �ϵ���� ���ۻ簡 OS �� �ϰ������� ������ �� �ֵ��� ����ȭ �س��� �������̽�.
	ThrowIfFailed(m_SDK->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &Caps));



	if (Caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)				// �ϵ����� ��ĺ�ȯ�� �������� ������ �� �ִ°� �˻��Ѵ�.
		m_behaviourFlag |= D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;		// ������ ��� �ϵ����� ���������� �����Ѵ�.
	else
		m_behaviourFlag |= D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_MULTITHREADED;		// �Ұ����� ��� ����Ʈ����� ���������� �����Ѵ�.
}

void DeviceManager::CheckMultiSample()
{
	ThrowIfFailed(m_SDK->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_A8R8G8B8, true, D3DMULTISAMPLE_NONE, &m_msQualityLev));
}

void DeviceManager::CreateSwapChain(D3DPRESENT_PARAMETERS* _desc, UINT _wincx, UINT _wincy, HWND _handle)
{
	_desc->BackBufferCount = 1;									// ������ BackBuffer�� ��.					
	_desc->BackBufferWidth = _wincx;								// ������ BackBuffer�� ����.
	_desc->BackBufferHeight = _wincy;							// ������ BackBuffer�� ����(���� ���� ��). D3DFMT_
	_desc->BackBufferFormat = D3DFMT_A8R8G8B8;					// ������ BackBuffer�� ��.

	_desc->MultiSampleType = D3DMULTISAMPLE_NONE;				// MSAA �� ���� ��Ƽ���ø� Ÿ��. D3DMULTISAMPLE_
	_desc->MultiSampleQuality = m_msQualityLev - 1;				// MS ���� ���� ����  0 ~ IDirect3D9::CheckMultiSampleType�� ����� - 1 �� ����Ѵ�.

	_desc->SwapEffect = D3DSWAPEFFECT_DISCARD;					// Present ȣ�� ��Ŀ� ���� ������ �ο��Ѵ�.
	_desc->hDeviceWindow = _handle;								// ��� Ŭ���̾�Ʈ ������ �ڵ�.
	_desc->Windowed = m_displayMode;							// ������ â��� ���� ���� true �� �� â���.
	_desc->EnableAutoDepthStencil = true;						// ����, ���ٽ� ���� ��뿩��. 2D ������ �ʿ������, 3D ������ �ʼ���.
	_desc->AutoDepthStencilFormat = D3DFMT_D24S8;				// ���� ���ٽ� ���� ����.	D3DFMT_
	_desc->Flags = false;										// Present ���� ������ ��� ����.

	_desc->FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ��üȭ�� ����� �� ȭ�� �ֻ���.
	_desc->PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE; // Present ȣ�� �� �߻��� ���� ����.
																	//_desc->PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// Present ȣ�� �� �߻��� ���� ����.
}

void DeviceManager::CreateDevice(D3DPRESENT_PARAMETERS* _desc, HWND _handle)
{
	ThrowIfFailed(m_SDK->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _handle, m_behaviourFlag, _desc, &m_device));
}




void DeviceManager::Release()
{
	SAFE_RELEASE(m_device);
	SAFE_RELEASE(m_SDK);
}


