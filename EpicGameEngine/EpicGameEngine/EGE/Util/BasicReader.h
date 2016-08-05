#pragma once

#include <fstream>
#include <filesystem>
namespace EGE{namespace Util{
	class BasicReader
	{
	public:
		static std::vector<uint8_t>  ReadData(std::string filename);
		static uintmax_t FileSize(std::string filename);
	};
}}

