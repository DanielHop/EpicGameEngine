#pragma once

#include <fstream>
#include <filesystem>
namespace EGE{namespace Util{
	class BasicReader
	{
	public:
		static std::vector<uint8_t>  ReadData(const std::string filename);
		static uintmax_t FileSize(const std::string filename);
	};
}}

