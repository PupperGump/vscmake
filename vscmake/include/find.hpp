#pragma once
#pragma warning(push, 4)
#include <vscmake.hpp>

class FileClass
{
public:
	std::string current_directory = ".";
	dirent* dp;
	DIR* dirptr;

	FileClass();
	~FileClass();

	bool enter_directory(std::string dir);
	std::string dir();
	std::string dir(const std::string& path);
	std::string getdir() { return current_directory; }
	void escape_directory();

	bool check_dir(std::string item);

	inline std::string find_file(const std::string& filename, const std::string& extension, const std::string searchdir = ".", const int depth = 1);

	bool get_real_path(std::string dir);

};

//std::string find_file(std::string filename, const std::string extension = ".", const std::string searchdir = ".", const int depth = 1, const bool is_caller = 1);