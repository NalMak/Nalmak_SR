#include "..\Include\FileIO.h"
#include <atlconv.h>

USING(Nalmak)

FileIO::FileIO()
{
}


FileIO::~FileIO()
{
}

int FileIO::IsFileOrDir(_wfinddata_t fd)
{
	if (fd.attrib & _A_SUBDIR)
		return 0; // ���丮�� 0 ��ȯ
	else
		return 1; // �׹��� ���� "�����ϴ� ����"�̱⿡ 1 ��ȯ
}

void FileIO::SearchingDir(std::list<std::wstring>* fdList, const TCHAR * _path, const TCHAR * _extention)
{
	wstring defaultPath = _path;
	wstring path = defaultPath + L"/*.*";
	wstring extention = _extention;
	int checkDirFile = 0;
	struct _wfinddata_t fd;
	intptr_t handle;


	//fd ����ü �ʱ�ȭ.
	if ((handle = _wfindfirst(path.c_str(), &fd)) == -1L)
	{
		//�����̳� ���丮�� ���� ���.
		cout << "No file in directory!" << endl;
		return;
	}
	do //���� Ž�� �ݺ� ����
	{
		//���� ��ü ���� Ȯ��(���� or ���丮)
		checkDirFile = IsFileOrDir(fd);
		if (checkDirFile == 0 && fd.name[0] != '.') {
			//���丮�� ���� ����
			//cout << "Dir  : " << _path << "/" << fd.name << endl;
			SearchingDir(fdList, (defaultPath + L"/" + fd.name).c_str(), extention.c_str());//����� ȣ��

		}
		else if (checkDirFile == 1 && fd.name[0] != '.') {
			//������ ���� ����
			//cout << "File : " << path << "/" << fd.name << endl;
			wstring fileName = fd.name;
			wstring fileFormat = fileName.substr(fileName.find_last_of(L".") + 1);

			if (fileFormat == _extention)
			{
				wstring temp = defaultPath + L"/" + fileName;

				fdList->emplace_back(temp.c_str());
			}
		}
	} while (_wfindnext(handle, &fd) == 0);
	_findclose(handle);
}
