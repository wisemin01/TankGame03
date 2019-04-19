#include "DXUT.h"
#include "FileManager.h"

#include <fstream>

FileManager::FileManager()
{

}


FileManager::~FileManager()
{

}

void FileManager::GetFileData(const string & path)
{
	ifstream file;
	file.open(path, ios::in);

	while (file && !file.eof())
	{
		std::pair<int, string> temp;
		file >> temp.first >> temp.second;

		if (temp.first != 0)
			listScoreData.push_back(temp);
	}

	file.close();
}

void FileManager::SetFileData(const string & path)
{
	ofstream file;
	file.open(path, ios::out | ios::trunc);

	listScoreData.sort([&](const pair<int, string>& prev, const pair<int, string>& next)->bool
		{
			return prev.first > next.first;
		});

	constexpr int set_count = 3;
	int i = 0;

	for (auto iter : listScoreData)
	{
		file << iter.first << " " << iter.second << endl;

		if (++i >= set_count)
			break;
	}
	file.close();

	Clear();
}

void FileManager::InsertData(const string & initial, int score)
{
	listScoreData.push_back(make_pair(score, initial));
}

bool FileManager::DataSort(const std::pair<int, string>& prev, const std::pair<int, string>& next)
{
	return prev.first > next.first;
}
