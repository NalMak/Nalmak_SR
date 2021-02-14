#include "..\Include\Terrain.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "Plane.h"
#include "Camera.h"
int Terrain::m_terrainID = 0;


Terrain::Terrain(Desc * _desc)
{
	m_isChangeData = false;

	m_width = _desc->width;
	m_depth = _desc->depth;
	m_interval = _desc->interval;
	m_brushPower = _desc->brushPower;
	m_brushRadius = _desc->brushRadius;
	if (!_desc->mtrl)
		m_material = ResourceManager::GetInstance()->GetResource<Material>(_desc->mtrlName);
	else
		m_material = _desc->mtrl;

	Plane * viBuffer = new Plane(m_width, m_depth, m_interval);
	viBuffer->Initialize();
	m_viBuffer = viBuffer;
	ResourceManager::GetInstance()->AddResource<VIBuffer>(L"terrainData" + to_wstring(m_terrainID), viBuffer);
	++m_terrainID;

	m_vertexInfo = new INPUT_LAYOUT_POSITION_NORMAL_UV[(_desc->width + 1) * (_desc->depth + 1)];

	for (int row = 0; row < m_depth + 1; ++row)
	{
		for (int col = 0; col < m_width + 1; ++col)
		{
			int index = row * (m_depth + 1) + col;
			m_vertexInfo[index].position = Vector3(m_interval * col, 0.f, m_interval * row);
			m_vertexInfo[index].uv = Vector2(m_interval * col, m_interval * row);
			m_vertexInfo[index].normal = Vector3(0.f, 0.f, 0.f);
		}
	}
}

Terrain::~Terrain()
{
}

void Terrain::Initialize()
{
	m_mainCam = RenderManager::GetInstance()->GetMainCamera();

	
}

void Terrain::Update()
{
	DEBUG_LOG(L"[ o , p ] Brush Size", m_brushRadius);
	DEBUG_LOG(L"[ k , l ] Brush Power", m_brushPower);

	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_LEFT_MOUSE))
	{
		DEBUG_LOG(L"Click", L"Left Mouse");
		Matrix worldMat = m_transform->GetWorldMatrix();
		Vector3 point = m_mainCam->GetTransform()->GetWorldPosition();
		Vector3 dir = m_mainCam->GetCamToMouseWorldDirection();

		for (int i = 0; i < m_depth; ++i)
		{
			for (int j = 0; j < m_width; ++j)
			{
				Vector3 v0;
				Vector3 v1;
				Vector3 v2;
				D3DXVec3TransformCoord(&v0, &m_vertexInfo[(m_depth + 1) * i + j].position, &worldMat);
				D3DXVec3TransformCoord(&v1, &m_vertexInfo[(m_depth + 1) * i + j + 1].position, &worldMat);
				D3DXVec3TransformCoord(&v2, &m_vertexInfo[(m_depth + 1) * (i + 1) + j + 1].position, &worldMat);
				Vector3 intersectPoint;
				if (Nalmak_Math::IsIntersectTriangle(point,dir,v0,v1,v2,&intersectPoint))
				{
					m_isChangeData = true;
					DEBUG_LOG(L"depth",i);
					DEBUG_LOG(L"width",j);
				}
				else
				{
					D3DXVec3TransformCoord(&v0, &m_vertexInfo[(m_depth + 1) * i + j + 1].position, &worldMat);
					D3DXVec3TransformCoord(&v1, &m_vertexInfo[(m_depth + 1) * (i + 1) + j].position, &worldMat);
					D3DXVec3TransformCoord(&v2, &m_vertexInfo[(m_depth + 1) * (i + 1) + j + 1].position, &worldMat);
					if (Nalmak_Math::IsIntersectTriangle(point, dir, v0, v1, v2, &intersectPoint))
					{
						m_isChangeData = true;
						DEBUG_LOG(L"depth", i);
						DEBUG_LOG(L"width", j);
					}
				}
				if (m_isChangeData)
				{
					float yOffset = m_brushPower * TimeManager::GetInstance()->GetdeltaTime();

					int radius = (int)m_brushRadius + 1;
					for (int k = -radius; k <= radius; ++k)
					{
						for (int l = -radius; l <= radius; ++l)
						{
							int xOffset = (int)intersectPoint.x + l;
							int zOffset = (int)intersectPoint.z + k;
							float distance = Nalmak_Math::Distance(Vector3((float)xOffset, 0.f, (float)zOffset), Vector3(intersectPoint.x, 0, intersectPoint.z));

							if (distance < m_brushRadius)
							{
								float ratio =  (m_brushRadius - distance) / m_brushRadius; // 0 -> �����ڸ� 1 -> ���
								float addHeight = sin(PI_DIV2 * ratio) * yOffset;
								m_vertexInfo[(m_depth + 1) * zOffset + xOffset].position.y += addHeight;
							}
						}
					}
					return;
				}
			}
		}
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_O))
	{
		m_brushRadius -= TimeManager::GetInstance()->GetdeltaTime();
		if (m_brushRadius < 0)
			m_brushRadius = 0;
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_P))
	{
		m_brushRadius += TimeManager::GetInstance()->GetdeltaTime();
	}
	if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_K))
	{
		m_brushPower -= TimeManager::GetInstance()->GetdeltaTime();
		if (m_brushPower < 0)
			m_brushPower = 0;
	}
	else if (InputManager::GetInstance()->GetKeyPress(KEY_STATE_L))
	{
		m_brushPower += TimeManager::GetInstance()->GetdeltaTime();
	
	}


}

void Terrain::LateUpdate()
{
	if (m_isChangeData)
	{
		((Plane*)m_viBuffer)->UpdateInstanceBuffer(m_vertexInfo, (m_depth + 1) * (m_width + 1));
		m_isChangeData = false;
	}
}

void Terrain::Release()
{
	SAFE_DELETE_ARR(m_vertexInfo);
}

void Terrain::Render()
{
	Shader* currentShader = m_material->GetShader();
	assert("Current Shader is nullptr! " && currentShader);

	currentShader->SetMatrix("g_world", GetTransform()->GetWorldMatrix());

	currentShader->CommitChanges();				   // BeginPass ȣ��� �ݵ�� �׸��� ���� ȣ��
												   ////////////////////////////////////////////////////////////////////////////////////
												   // DrawPrimitive (index ��� x)
												   // Type, �̹��� �̿�� �ε���, �ּ� ��������, ȣ��� ���ؽ� ��, �ε��� ���۳����� �б� ������ �ε���, �׸��� ���� ��
	ThrowIfFailed(m_device->DrawIndexedPrimitive(currentShader->GetPrimitiveType(), 0, 0, m_viBuffer->GetVertexCount(), 0, m_viBuffer->GetFigureCount()));
}

void Terrain::BindingStreamSource()
{
	ThrowIfFailed(m_device->SetStreamSource(0, m_viBuffer->GetVertexBuffer(), 0, m_material->GetShader()->GetInputLayoutSize()));
	ThrowIfFailed(m_device->SetIndices(m_viBuffer->GetIndexBuffer()));
}

float Terrain::GetHeight(const Vector3 & _pos)
{
	if (_pos.x < 0 || _pos.x > m_width * m_interval)
		return 0;

	if(_pos.y < 0 || _pos.y > m_depth * m_interval)
		return 0;

	int widthIndex = (int)(_pos.x / m_interval);
	int depthIndex = (int)(_pos.z / m_interval);


	Vector3 xzPos = Vector3(_pos.x, 0, _pos.z);

	float distance1 = Nalmak_Math::Distance(xzPos, Vector3(widthIndex * m_interval, 0, depthIndex * m_interval));
	float distance2 = Nalmak_Math::Distance(xzPos, Vector3((widthIndex + 1) * m_interval, 0, (depthIndex + 1)* m_interval));


	D3DXPLANE plane;
	Vector3 v0;
	Vector3 v1;
	Vector3 v2;

	if (distance1 < distance2)
	{
		v0 = m_vertexInfo[(m_depth + 1) * depthIndex + widthIndex].position;
		v1 = m_vertexInfo[(m_depth + 1) * depthIndex + (widthIndex + 1)].position;
		v2 = m_vertexInfo[(m_depth + 1) * (depthIndex + 1) + widthIndex].position;

		D3DXPlaneFromPoints(&plane, &v0, &v1, &v2);
	}
	else
	{
		v0 = m_vertexInfo[(m_depth + 1) * (depthIndex + 1)+ (widthIndex + 1)].position;
		v1 = m_vertexInfo[(m_depth + 1) * depthIndex + widthIndex + 1].position;
		v2 = m_vertexInfo[(m_depth + 1) * (depthIndex + 1) + widthIndex].position;

		D3DXPlaneFromPoints(&plane, &v0, &v1, &v2);
	}
	// ax + by + cz + d = 0;
	if (plane.b == 0)
	{
		return 0;
	}
	float height = (-plane.a * _pos.x - plane.c * _pos.z - plane.d) / plane.b;
	return height;
}
