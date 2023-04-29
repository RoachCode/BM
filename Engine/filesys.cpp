#pragma once
#include <filesystem>

const std::string getLocalPath() {
	std::string localPath = std::filesystem::current_path().string();
	std::replace(localPath.begin(), localPath.end(), '\\', '/');
	return localPath;
}