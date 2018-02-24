#pragma once
#include "FileSystem/FileSystem.h"


namespace Forge
{
	class WINFileSystem : public FileSystem
	{
		void GetAllFiles(std::vector<String>& files, String path);
	public:
		std::vector<String> GetFilesFromDirectory(String path) override;
	};
}