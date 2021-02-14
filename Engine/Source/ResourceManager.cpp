#include "..\Include\ResourceManager.h"
#include "Quad.h"
#include "Triangle.h"
#include "LineVI.h"
#include "QuadNoneNormal.h"
#include "Box.h"
#include "Sphere.h"
#include "Plane.h"
#include "ObjMesh.h"
USING(Nalmak)
IMPLEMENT_SINGLETON(ResourceManager)
ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
	Release();
}

HRESULT ResourceManager::Initialize(const wstring& _path)
{
	m_directoryPath = _path;
	LoadMeshes<ObjMesh>(L"obj");
	LoadResources<Shader>(L"fx");
	LoadTextures(L"png");

	return S_OK;
}

HRESULT ResourceManager::Release()
{
	for (auto& resources : m_resoucreContainers)
	{
		for (auto& resource : resources.second)
		{
			SAFE_DELETE(resource.second);
		}
		resources.second.clear();
	}
	m_resoucreContainers.clear();
	return S_OK;
}

void ResourceManager::SetShaderInfo(const wstring& _shaderName, D3DPRIMITIVETYPE _primitive, D3DVERTEXELEMENT9 * _decl, UINT _inputLayoutSize)
{
	Shader* shader = GetResource<Shader>(_shaderName);
	shader->SetInputLayout(_primitive, _decl, _inputLayoutSize);
}



void ResourceManager::CreateDefaultResource()
{
	CreateDefaultMesh();
	CreateDefaultShader();
	CreateDefaultRenderTarget();

	LoadResources<RenderTarget>(L"rtd");
	LoadResources<Material>(L"mtrl");
}

void ResourceManager::CreateDefaultRenderTarget()
{
	RenderTarget* renderTarget = new RenderTarget(1920, 1080, D3DFORMAT::D3DFMT_A8R8G8B8, D3DCOLOR_RGBA(0, 0, 0, 255));
	m_resoucreContainers[typeid(RenderTarget).name()][L"mainCamera"] = renderTarget;
}

void ResourceManager::CreateDefaultMesh()
{
	{
		VIBuffer* mesh = new Quad();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"quad"] = mesh;
	}
	{
		VIBuffer* mesh = new Triangle();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"triangle"] = mesh;
	}
	{
		VIBuffer* mesh = new LineVI();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"line"] = mesh;
	}
	{
		VIBuffer* mesh = new QuadNoneNormal();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"quadNoneNormal"] = mesh;
	}
	{
		VIBuffer* mesh = new Box();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"box"] = mesh;
	}
	{
		VIBuffer* mesh = new Sphere();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"sphere"] = mesh;
	}
	{
		VIBuffer* mesh = new Plane();
		assert("Fail to Create Mesh!" && mesh);
		mesh->OnInitialize();
		m_resoucreContainers[typeid(VIBuffer).name()][L"plane"] = mesh;
	}

}

void ResourceManager::CreateDefaultShader()
{
	{
		D3DVERTEXELEMENT9 decl[] =
		{
			{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0,12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,  0 },
			{ 0,24,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
			D3DDECL_END()
		};
		SetShaderInfo(L"default", D3DPT_TRIANGLELIST, decl, sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV));
	}
	/*{
	D3DVERTEXELEMENT9 decl[] =
	{
	{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
	{ 0,12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
	D3DDECL_END()
	};
	SetShaderInfo(L"cubeMap", D3DPT_TRIANGLELIST, decl, sizeof(INPUT_LAYOUT_POSITION_UV));
	}*/

	{
		D3DVERTEXELEMENT9 decl[] =
		{
			{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			D3DDECL_END()
		};
		SetShaderInfo(L"line",
			D3DPT_LINELIST,
			decl,
			sizeof(INPUT_LAYOUT_POSITION));
	}

	{
		D3DVERTEXELEMENT9 decl[] =
		{
			{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0,12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
			D3DDECL_END()
		};
		SetShaderInfo(L"noneNormal",
			D3DPT_TRIANGLELIST,
			decl,
			sizeof(INPUT_LAYOUT_POSITION_UV));
	}

	{
		D3DVERTEXELEMENT9 decl[] =
		{
			{ 0,0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0 },
			{ 0,12,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,0 },
			{ 1,0,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1 },
			{ 1,16,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2 },
			{ 1,32,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3 },
			{ 1,48,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4 },
			{ 1,64,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 5 },
			D3DDECL_END()
		};
		SetShaderInfo(L"particle", D3DPT_TRIANGLELIST, decl, sizeof(INPUT_LAYOUT_PARTICLE));
	}
}






void ResourceManager::UpdateMaterial()
{

	list<wstring> filePaths;
	FileIO::SearchingDir(&filePaths, m_directoryPath.c_str(), L"mtrl");

	for (auto& file : filePaths)
	{
		wstring filePath = file;
		wstring fileName = filePath.substr(filePath.find_last_of(L"/") + 1);
		size_t targetNum = fileName.find_last_of(L".");
		fileName = fileName.substr(0, targetNum);

		if (m_resoucreContainers[typeid(Material).name()][fileName])
		{
			Material material;
			material.Initialize(filePath);
			Material* existingMtrl = (Material*)m_resoucreContainers[typeid(Material).name()][fileName];
			*existingMtrl = material;
			existingMtrl->m_name = fileName;
		}
		else
		{
			Material* resource = new Material();

			assert("Fail to Create Resource!" && resource);
			resource->Initialize(filePath);
			m_resoucreContainers[typeid(Material).name()][fileName] = resource;
			((IResource*)resource)->m_name = fileName;
		}


	}
}

void ResourceManager::LoadTextures(const TCHAR * _extention)
{

	list<wstring> filePaths;
	FileIO::SearchingDir(&filePaths, m_directoryPath.c_str(), _extention);

	for (auto& file : filePaths)
	{
		wstring filePath = file;
		wstring fileName = filePath.substr(filePath.find_last_of(L"/") + 1);
		size_t targetNum = fileName.find_last_of(L".");
		fileName = fileName.substr(0, targetNum);



		targetNum = fileName.find_last_of(L"_");
		if (targetNum != -1)
		{
			wstring fileIndex = fileName.substr(targetNum + 1, fileName.length());

			int texIndex = 0;
			if (Nalmak_String::IsDigitString(&texIndex, fileIndex))
			{
				fileName = fileName.substr(0, targetNum);

				Texture* tex = (Texture*)m_resoucreContainers[typeid(Texture).name()][fileName];
				if (!tex)
				{
					tex = new Texture;
					m_resoucreContainers[typeid(Texture).name()][fileName] = tex;
				}
				tex->Initialize(filePath.c_str());

			}
			else
			{
				if (m_resoucreContainers[typeid(Texture).name()][fileName])
				{
					MessageBox(NULL, (L"Resource is already exist! " + filePath).c_str(), NULL, MB_OK);
				}
				Texture* tex = new Texture();
				assert("Fail to Create Resource!" && tex);
				tex->Initialize(filePath.c_str());
				m_resoucreContainers[typeid(Texture).name()][fileName] = tex;
			}
		}
		else
		{
			if (m_resoucreContainers[typeid(Texture).name()][fileName])
			{
				MessageBox(NULL, (L"Resource is already exist! " + filePath).c_str(), NULL, MB_OK);
			}
			Texture* tex = new Texture();
			assert("Fail to Create Resource!" && tex);
			tex->Initialize(filePath.c_str());
			m_resoucreContainers[typeid(Texture).name()][fileName] = tex;
		}


	}
}

