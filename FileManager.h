#pragma once
#include "Singleton.h"

class FileManager :
	public Singleton<FileManager>
{
public:
	list<std::pair<int, string>> listScoreData;
public:
	FileManager();
	virtual ~FileManager();

	void GetFileData(const string& path);
	void SetFileData(const string& path);

	void InsertData(const string& initial, int score);

	inline void Clear() {
		listScoreData.clear();
	}

	list<std::pair<int, string>>& GetList() { return listScoreData; }

public:
	static bool DataSort(const std::pair<int, string>& prev, const std::pair<int, string>& next);
};

#define FILEMGR FileManager::GetInstance()