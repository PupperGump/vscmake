#pragma once
#pragma warning(push, 4)
#include <vscmake.hpp>

int test(const int x = 10);

class FileClass
{
public:
	std::string current_directory = ".";
	dirent* dp;
	DIR* dirptr;

	FileClass();
	~FileClass();

	inline bool enter_directory(std::string dir);
	inline std::string dir();
	inline std::string dir(const std::string& path);
	inline std::string getdir() { return current_directory; }
	inline void escape_directory();

	inline bool check_dir(std::string item);

	std::string find_file(const std::string& filename, const std::string& extension, const std::string searchdir = ".", const int depth = 1);

	inline bool get_real_path(std::string dir);
};

//std::string find_file(std::string filename, const std::string extension = ".", const std::string searchdir = ".", const int depth = 1, const bool is_caller = 1);