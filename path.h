#ifndef __PATH_H__
#define __PATH_H__

#include <string>

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#include <libgen.h>
#endif

using namespace std;

class Path
{
public:
	Path();
	Path(const string &source);
	Path(const Path &source);
	Path(const Path &&source);
	~Path();

	Path &operator=(const string &source);
	Path &operator=(const Path &source);
	Path &operator=(const Path &&source);
	bool operator==(const string &source);
	bool operator==(const Path &source);

	string get_Raw() const;
	string get_Absolute() const;
	static string get_Absolute(const string &path);
	string get_BaseFilename() const;
	static string get_BaseFilename(const string &path);
	string get_UNC() const;
	static string get_UNC(const string &path);
	Path ResolveRelative(const string &relative) const;
	static Path ResolveRelative(const string &source, const string &relative);
	bool is_UNC() const;
	static bool is_UNC(const string &path);
	bool is_Absolute() const;
	static bool is_Absolute(const string &path);
	static string CurrentDirectory();
protected:
private:
	string mPath;
};

#endif