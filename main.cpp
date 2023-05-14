#include <vscmake.hpp>

int test(const int x = 10);

inline int test(const int x)
{
	if (x <= 1)
		return x;
	return test(x-1);
}

int main()
{
	using namespace std::chrono_literals;
	using namespace std::chrono;
	// CMakeLists
	std::fstream cml;

	// Create CMakeLists in solution directory

	// This is relative to soure files, I need to search for the solution file
	//cml.open(

	// Search for .sln file in working directory, if not found keep moving up


	FileClass fc;
	//fc.enter_directory("build");
	//std::cout << fc.dir() << "path: " << fc.current_directory << "\n";
	//fc.enter_directory("build/debug");
	//std::cout << fc.dir() << "path: " << fc.current_directory << "\n";
	//fc.dirptr = opendir("build");
	//closedir(fc.dirptr);
	//fc.dirptr = opendir("build\\debug");
	//closedir(fc.dirptr);
	//std::cout << test(100) << "\n";
	//return 0;
	std::cout << fc.dir() << "\n";
	std::string filename = "uwu", extension = ".";

	auto begin = system_clock::now();
	std::cout << "Path: " << fc.find_file(filename, extension, "C:/Users/User") << "\n";
	auto end = system_clock::now();

	std::cout << "Time: " << (float)duration_cast<milliseconds>(end - begin).count() / 1000.f;

	
	return 0;
}