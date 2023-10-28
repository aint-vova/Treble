#include "resources/file.h"

#include <cassert>
#include <filesystem>
#include <cwchar>
#include <Windows.h>

namespace Treble
{
	std::filesystem::path getExecutableDir()
	{
		wchar_t buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, sizeof(buffer));
		return std::filesystem::path(buffer).parent_path();
	}

	std::string fileToString(const std::string& filePath)
	{
		auto fp = std::fopen((getExecutableDir().string() + '\\' + filePath).c_str(), "rb");

		if (fp == nullptr)
		{
			return {};
		}

		std::fseek(fp, 0u, SEEK_END);
		const auto size = std::ftell(fp);
		std::fseek(fp, 0u, SEEK_SET);

		std::string s;
		s.resize(size);

		const auto read = std::fread(&s[0], 1u, size, fp);
		std::fclose(fp);

		assert(read == size);

		return s;
	}
}