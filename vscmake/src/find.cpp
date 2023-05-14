#include <find.hpp>

int depth_start = 0;
std::string last_path;

size_t strlen(const wchar_t* wc)
{
	size_t length = 0;

	while (wc[length++] != '\0');
	return length;
}


std::string wctostr(const wchar_t* wc)
{
	std::string str;
	for (int i = 0; i < strlen(wc); i++)
	{
		str.push_back(wc[i]);
	}
	return str;
}

int countstr(std::string str, char c)
{
	size_t count = 0;

	for (const auto i : str)
	{
		if (i == c)
		{
			count++;
		}
	}
	return count;
}

inline std::string getstr(std::string str, int index, char token = '\n')
{
	if (str.size() == 0 || str.find(token) == std::string::npos)
		return "";
	//if (index > countstr(str, token) )
	//{
	//	return "";
	//}
	//if (countstr(str, '\\') == 0)
	//{
	//	return "";
	//}

	//std::string ret = str;
	int last = 0, offset = 0;

	for (int i = 0; i <= index; i++)
	{
		if (i != 0)
			last = offset + 1;
		offset = str.find(token, last);
		//ret = str.substr(last, offset);
		//str.erase(0, str.find(token) + 1);
	}
	return str.substr(last, offset - last);

}

FileClass::FileClass()
{
	enter_directory(".");
}

FileClass::~FileClass()
{
	//closedir(dirptr);
}

inline bool FileClass::enter_directory(std::string directory)
{
	//std::cout << "Absolute path: " << current_directory << "\n";
	return get_real_path(directory);
		//std::cout << "error finding path\n";

	//if (current_directory.find('.') != std::string::npos)
	//{
	//	/*escape_directory();*/
	//	return;
	//}
	//dirptr = opendir(current_directory.c_str());
}

inline void FileClass::escape_directory()
{
	for (int i = current_directory.size() - 1; i >= 0; i--)
	{
		if (current_directory[i] == '\\' || current_directory[i] == '/')
		{
			//std::cout << current_directory << "\n";
			current_directory = current_directory.substr(0, i);
			//std::cout << current_directory << "\n";
			//closedir(dirptr);
			enter_directory(current_directory);
			return;
		}
	}
}

inline std::string FileClass::dir()
{

	dirptr = opendir(current_directory.c_str());
	if (dirptr == NULL)
	{
		closedir(dirptr);
		if (!get_real_path(current_directory))
		{
			escape_directory();
			return "";
		}
	}
	std::string str;
	while (dp = readdir(dirptr))
	{
		if (!(strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..")))
			continue;
		str += dp->d_name;
		//if (str.find('.') == std::string::npos)
		//{
		//	str += '\\';
		//}
		str += "\n";
	}
	closedir(dirptr);
	return str;
}

inline std::string FileClass::dir(const std::string& path)
{
	const std::string temp = current_directory;
	current_directory = path;
	const std::string str = dir();
	current_directory = temp;
	return str;
}

inline bool FileClass::check_dir(std::string item)
{
	// Each call to dir() results in dp being NULL
	enter_directory(current_directory);
	std::string str = dir();
	if (str.find(item) == std::string::npos)
		return 0;
	else
		return 1;
}

inline bool FileClass::get_real_path(std::string directory)
{
	// Relative paths should only be done when a period is found, either alone or accompanying a slash or backslash
	
	// To make things easier, I'm not giving any craps about unicode. Tough.
	bool ret = 0;
	//if (directory.find(':') == std::string::npos)
	if (directory.size() > 1 && directory[1] != ':')
	{
		char fullpath[MAX_PATH];
		
		LPCSTR relpath = (LPCSTR)directory.c_str();
		ret = GetFullPathNameA(relpath, MAX_PATH, fullpath, NULL);
		if (ret == 0)
			return 0;
		//current_directory.clear();

		std::cout << "Input: " << directory << "\n";

		current_directory = fullpath;

		size_t append = 0;

		// Relative paths (../) get appended, remove them
		if ((append = current_directory.find("\\.")) != std::string::npos)
		{
			current_directory.erase(append, 2);
		}
		// Forward slash for Linux, might work lol
		if ((append = current_directory.find("/.")) != std::string::npos)
		{
			current_directory.erase(append, 2);
		}
	}
	else
	{
		current_directory = directory;
	}

	// If it's a folder, do a slash, doesn't account for files without extensions
	if (current_directory.find('.') == std::string::npos)
	{
		current_directory += '\\';
	}

	return ret;
}

std::string FileClass::find_file(const std::string& filename, const std::string& extension, const std::string searchdir, const int depth)
{
	if (depth <= 2)
		std::cout << searchdir << "\n";
	enter_directory(searchdir);

	std::string path;
	const std::string curr = current_directory;

	const std::string d = dir(curr);
	const int count = countstr(d, '\n');
	
	for (int i = 0; i < count; i++)
	{
		path = getstr(d, i);
		if (path.find(filename) != std::string::npos)
			return curr + path;
		find_file(filename, extension, curr + path, depth + 1);
		escape_directory();
	}

	return "";
}

//std::string FileClass::find_file(const std::string filename, const std::string extension, const std::string searchdir, const int depth, const bool is_caller)
//{
//	enter_directory(searchdir);
//	std::cout << current_directory << "\n";
//	std::string path, curr = current_directory;
//	int count = countstr(dir(curr), '\n');
//	//vec.reserve(count);
//
//	for (int i = 0; i < count; i++)
//	{
//		path = getstr(dir(curr), i);
//		if (path.find(filename) != std::string::npos)
//			return curr + path;
//		find_file(filename, extension, curr + path);
//		escape_directory();
//	}
//
//	return "";
//}
