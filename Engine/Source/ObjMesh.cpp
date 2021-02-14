#include "..\Include\ObjMesh.h"
#include <fstream>

ObjMesh::ObjMesh()
{
}

ObjMesh::~ObjMesh()
{
}

void ObjMesh::Initialize(wstring _fp)
{
	m_filePath = _fp;
	if (L"" == m_filePath)
	{
		assert(0 && L"Please, Insert to FilePath");
		return;
	}

	CreateVertexBuffer();
	CreateIndexBuffer();

}

void ObjMesh::CreateVertexBuffer()
{

	vector<float> vertex;
	vector<float> uv;
	vector<float> vn;



	{
#pragma region VERTEX POS IMPORT

		ifstream file;
		file.open(m_filePath);
		string str;
		

		// v ã��

		while (!file.eof())
		{
			getline(file, str);
			if ('v' == str[0]) // T�� ���ΰ������� �����
				break;
		}

		while ('v' == str[0]) // ù��° ���ڿ��� v�϶�
		{
			int iIndex = 0;

			while (true)
			{
				while (' ' == str[iIndex])
				{
					// �����̸� �پ� �ѱ��
					++iIndex;
				}
				iIndex += 3; // 0��° �ε�������
																	//for . x ��ġ
				int XMin = iIndex, XMax = iIndex;				// ���ڿ� �ε��� ��ġ
				while (' ' != str[iIndex])
				{
					++iIndex;
					XMax = iIndex; // ���� ���ڿ� ����
				}
				double x = atof(str.substr(XMin, XMax - XMin).c_str()); // ����ġ�� ������ �����ϸ� ?�ڷ������� �� �ϳ��� ��ȯ

				while (' ' == str[iIndex])						    //for. Y��ġ
				{
					++iIndex;
				}
				int YMin = iIndex, YMax = iIndex;
				while (str[iIndex] != ' ') {
					++iIndex;
					YMax = iIndex;
				}
				double y = atof(str.substr(YMin, YMax - YMin).c_str());

				while (' ' == str[iIndex])						    //for. Z��ġ
				{
					++iIndex;
				}
				int  ZMin = iIndex, ZMax = iIndex;
				while (' ' != str[iIndex]) {
					size_t a = str.length();
					if (str.length() <= iIndex)
						break;

					iIndex++;
					ZMax = iIndex;

				}
				double z = atof(str.substr(ZMin, ZMax - ZMin).c_str());

				// �����а� Ż��, 
				vertex.emplace_back((float)x);
				vertex.emplace_back((float)y);
				vertex.emplace_back((float)z);

				break;

			}
			getline(file, str);

		}
		file.close();
#pragma endregion
	}

	{
#pragma region UV IMPORT
	
	ifstream file;
	file.open(m_filePath);
	string str;

	// v ã��

	while (!file.eof())
	{
		getline(file, str);
		if ('v' == str[0] && 't' == str[1])
			break;
			
	}

	while ('t' == str[1]) // ù��° ���ڿ��� v�϶�
	{
		int iIndex = 0;

		while (true)
		{
			while (' ' == str[iIndex])
			{
				// �����̸� �پ� �ѱ��
				++iIndex;
			}
			iIndex += 3; // 0��° �ε�������
						 //for . x ��ġ
			int XMin = iIndex, XMax = iIndex;				// ���ڿ� �ε��� ��ġ
			while (' ' != str[iIndex])
			{
				++iIndex;
				XMax = iIndex; // ���� ���ڿ� ����
			}
			double x = atof(str.substr(XMin, XMax - XMin).c_str()); // ����ġ�� ������ �����ϸ� ?�ڷ������� �� �ϳ��� ��ȯ

			while (' ' == str[iIndex])						    //for. Y��ġ
			{
				++iIndex;
			}
			int YMin = iIndex, YMax = iIndex;
			while (str[iIndex] != ' ') {
				++iIndex;
				YMax = iIndex;
			}
			double y = atof(str.substr(YMin, YMax - YMin).c_str());

			while (' ' == str[iIndex])						    //for. Z��ġ
			{
				++iIndex;
			}
			int  ZMin = iIndex, ZMax = iIndex;
			while (' ' != str[iIndex]) {
				size_t a = str.length();
				if (str.length() <= iIndex)
					break;

				iIndex++;
				ZMax = iIndex;

			}
			double z = atof(str.substr(ZMin, ZMax - ZMin).c_str());

			// �����а� Ż��, 
			Vector3 vec3 = D3DXVECTOR3((float)x, (float)y, (float)z);
			uv.emplace_back((float)x);
			uv.emplace_back((float)y);
			uv.emplace_back((float)z);
			break;

		}
		getline(file, str);
		
	}
	file.close();
#pragma endregion
	}

	{
#pragma region VN IMPORT
		ifstream file;
		file.open(m_filePath);
		string str;

		// v ã��

		while (!file.eof())
		{
			getline(file, str);
			if ('v' == str[0] && 'n' == str[1])
				break;

		}

		while ('n' == str[1]) // ù��° ���ڿ��� v�϶�
		{
			int iIndex = 0;

			while (true)
			{
				while (' ' == str[iIndex])
				{
					// �����̸� �پ� �ѱ��
					++iIndex;
				}
				iIndex += 3; // 0��° �ε�������
							 //for . x ��ġ
				int XMin = iIndex, XMax = iIndex;				// ���ڿ� �ε��� ��ġ
				while (' ' != str[iIndex])
				{
					++iIndex;
					XMax = iIndex; // ���� ���ڿ� ����
				}
				double x = atof(str.substr(XMin, XMax - XMin).c_str()); // ����ġ�� ������ �����ϸ� ?�ڷ������� �� �ϳ��� ��ȯ

				while (' ' == str[iIndex])						    //for. Y��ġ
				{
					++iIndex;
				}
				int YMin = iIndex, YMax = iIndex;
				while (str[iIndex] != ' ') {
					++iIndex;
					YMax = iIndex;
				}
				double y = atof(str.substr(YMin, YMax - YMin).c_str());

				while (' ' == str[iIndex])						    //for. Z��ġ
				{
					++iIndex;
				}
				int  ZMin = iIndex, ZMax = iIndex;
				while (' ' != str[iIndex]) {
					size_t a = str.length();
					if (str.length() <= iIndex)
						break;

					iIndex++;
					ZMax = iIndex;

				}
				double z = atof(str.substr(ZMin, ZMax - ZMin).c_str());

				// �����а� Ż��, 
				D3DXVECTOR3 vec3 = D3DXVECTOR3((float)x, (float)y, (float)z);
				vn.emplace_back((float)x);
				vn.emplace_back((float)y);
				vn.emplace_back((float)z);
				break;

			}
			getline(file, str);

		}
		file.close();

#pragma endregion
	}




	ThrowIfFailed(m_device->CreateVertexBuffer(
		sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV) * (UINT)vertex.size(),
		0, // ��ƼŬ�̳� ���� �ɼ� ����
		NULL, //D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0),
		D3DPOOL_MANAGED,
		&m_vBuffer,
		nullptr
	));
	
	INPUT_LAYOUT_POSITION_NORMAL_UV* vertices = nullptr;
	m_vBuffer->Lock(0, 0, (void**)&vertices, 0);
	
	
	size_t size = vertex.size() / 3;
	for (size_t i = 0; i < size; ++i)
	{
		vertices[i].position.x = (vertex[i * 3]);
		vertices[i].position.y = (vertex[i * 3 + 1]);
		vertices[i].position.z = (vertex[i * 3 + 2]);
	}
	
	size = uv.size() / 3;
	for (size_t i = 0; i <size; ++i)
	{
		vertices[i].uv.x = (uv[i * 3]);
		vertices[i].uv.y = (uv[i * 3 + 1]);
	}
	size = vn.size() / 3;
	for (int i = 0; i < size; ++i)
	{
		vertices[i].normal.x = (vn[i * 3]);
		vertices[i].normal.y = (vn[i * 3 + 1]);
		vertices[i].normal.z = (vn[i * 3 + 2]);
	}
	

	m_vBuffer->Unlock();
	SetVertexCount((UINT)vertex.size());
	vertex.clear();
	uv.clear();
	vn.clear();

	D3DXComputeBoundingSphere(&vertices[0].position, (DWORD)vertex.size(), sizeof(INPUT_LAYOUT_POSITION_NORMAL_UV), &m_boundingSphereCenter, &m_boundingSphereRadius);


}

void ObjMesh::CreateIndexBuffer()
{
	/*f 1 / 1 / 1 2 / 2 / 1 3 / 3 / 1
		f 4 / 4 / 1 3 / 3 / 1 2 / 2 / 1*/
	vector<float> faces;
	ifstream file;
	file.open(m_filePath);

	string str;
	while (!file.eof())
	{
		getline(file, str);
		if (str[0] == 'f') {
			break;
		}
	}

	while ('f' == str[0])
	{
		int iIndex = 0;
		while (true)
		{
			// 1. ���࿡ 'f' �ڿ� ������ ����������� ����ó�� 
			while (' ' == str[iIndex])
				++iIndex;
			

			iIndex += 2; // �о�ߵ� �ε��� ��ġ

			int XMin = iIndex, XMax = iIndex;				// ���ڿ� �ε��� ��ġ
			while ('/' != str[iIndex])
			{
				++iIndex;
				XMax = iIndex; // ���� ���ڿ� ����
			}
			int IndexPos_0 = atoi(str.substr(XMin, XMax - XMin).c_str());


			while (' ' != str[iIndex])
				++iIndex;
			int YMin = iIndex, YMax = iIndex;				// ���ڿ� �ε��� ��ġ
			while ('/' != str[iIndex])
			{
				++iIndex;
				YMax = iIndex; // ���� ���ڿ� ����
			}
			int IndexPos_1 = atoi(str.substr(YMin, YMax - YMin).c_str());


			while (' ' != str[iIndex])
				++iIndex;
			int ZMin = iIndex, ZMax = iIndex;				// ���ڿ� �ε��� ��ġ
			while ('/' != str[iIndex])
			{
				++iIndex;
				ZMax = iIndex; // ���� ���ڿ� ����
			}
			int IndexPos_2 = atoi(str.substr(ZMin, ZMax - ZMin).c_str());

			//Vector3 face = Vector3((float)IndexPos_0, (float)IndexPos_1, (float)IndexPos_2);
			// �߰� : 
			faces.emplace_back((float)IndexPos_0);
			faces.emplace_back((float)IndexPos_1);
			faces.emplace_back((float)IndexPos_2);

			break;
		}
		getline(file, str);
	}

	file.close();


	ThrowIfFailed(m_device->CreateIndexBuffer(
		sizeof(short) * (UINT)(faces.size()),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_iBuffer,
		nullptr));

	short* test = nullptr;
	m_iBuffer->Lock(0, 0, (void**)&test, 0);

	for (size_t i = 0; i < faces.size(); ++i)
	{
		if (i >= faces.size())
			break;
	
		test[i] = (short)faces[i] - 1;

		
	}
	m_iBuffer->Unlock();
	SetFigureCount((UINT)faces.size());
	faces.clear();

}


