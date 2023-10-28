#pragma once

#include <string>
#include <filesystem>

namespace Treble
{
	std::filesystem::path getExecutableDir();
	std::string fileToString(const std::string &filePath);
}
