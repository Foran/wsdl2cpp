#include "path.h"

#include <vector>

#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#include <libgen.h>
#endif

Path::Path()
{

}

Path::Path(const string &source)
{
	*this = source;
}

Path::Path(const Path &source)
{
	*this = source;
}

Path::Path(const Path &&source) : mPath(std::move(source.mPath))
{
}

Path::~Path()
{

}

Path &Path::operator=(const string &source)
{
	mPath = source;

	return *this;
}

Path &Path::operator=(const Path &source)
{
	*this = source.mPath;

	return *this;
}

Path &Path::operator=(const Path &&source)
{
	mPath = std::move(source.mPath);

	return *this;
}

bool Path::operator==(const string &source)
{
	return mPath == source;
}

bool Path::operator==(const Path &source)
{
	return mPath == source.mPath;
}

string Path::get_Raw() const
{
	return mPath;
}

string Path::CurrentDirectory()
{
	string retval = "";
	char path[FILENAME_MAX];

	if (GetCurrentDir(path, sizeof(path)) > 0) {
		retval = path;
#ifdef _WIN32
		retval += '\\';
#else
		retval += '/';
#endif
	}

	return retval;
}

string Path::get_Absolute(const string &path)
{
	string retval = path;

	if (!Path::is_Absolute(retval)) {
		retval = Path::CurrentDirectory() + retval;
	}

	return retval;
}

string Path::get_Absolute() const
{
	return Path::get_Absolute(mPath);
}

string Path::get_BaseFilename(const string &path)
{
	string retval = Path::get_Absolute(path);

	size_t pos = retval.find_last_of("/\\");
	retval = retval.substr(pos + 1);

	return retval;
}

string Path::get_BaseFilename() const
{
	return Path::get_BaseFilename(mPath);
}

string Path::get_BasePath(const string &path)
{
	string retval = Path::get_Absolute(path);

	size_t pos = retval.find_last_of("/\\");
	retval = retval.substr(0, pos + 1);

	return retval;
}

string Path::get_BasePath() const
{
	return Path::get_BasePath(mPath);
}

string Path::get_UNC(const string &path)
{
	string retval = path;

	if (!Path::is_UNC(retval)) {
		if (Path::is_Absolute(retval)) {
			retval = "file://" + Path::get_Absolute(retval);
		}
		else if (Path::is_Relative(retval)) {
			retval = Path::ResolveRelative(Path::CurrentDirectory(), retval).get_UNC();
		}
	}

	return retval;
}

string Path::get_UNC() const
{
	return Path::get_UNC(mPath);
}

string Path::get_Protocol() const
{
	string retval = get_UNC();

	return retval.substr(0, retval.find_first_of(":"));
}

Path Path::ResolveRelative(const string &source, const string &relative)
{
	Path path(source);
	string temp = path.get_UNC();
	temp = temp.substr(path.get_Protocol().length() + 3);
	vector<string> parts;
	while (temp.length() > 0) {
		size_t t = temp.find_first_of('/');
		if (t == string::npos) {
			parts.push_back(temp);
			temp = "";
		}
		else {
			parts.push_back(temp.substr(0, t));
			temp = temp.substr(t + 1);
		}
	}
	string retval = relative;
	while (retval.find_first_of("../") == 0) {
		parts.pop_back();
		retval = retval.substr(3);
	}
	for (int i = parts.size() - 1; i >= 0; i--) {
		retval = parts[i] + "/" + retval;
	}
	return retval;
}

Path Path::ResolveRelative(const string &relative) const
{
	return Path::ResolveRelative(mPath, relative);
}

bool Path::is_Relative(const string &relative)
{
	bool retval = false;

	if (!Path::is_Absolute(relative)) {
		retval = true;
	}

	return retval;
}

bool Path::is_UNC(const string &path)
{
	bool retval = false;

	if (path.c_str()[0] !=
#ifdef _WIN32
		'\\'
#else
		'/'
#endif
		&&
		path.c_str()[0] != '.' &&
		path.c_str()[1] != '.' &&
		path.c_str()[3] !=
#ifdef _WIN32
		'\\'
#else
		'/'
#endif
		&&		path.find_first_of("://") != string::npos) {
		retval = true;
}

	return retval;
}

bool Path::is_UNC() const
{
	return Path::is_UNC(mPath);
}

bool Path::is_Absolute(const string &path)
{
	bool retval = Path::is_UNC(path);
	if (!retval) {
#ifdef _WIN32
		if (isalpha(path.c_str()[0]) && path.c_str()[1] == ':' && path.c_str()[2] == '\\') {
			retval = true;
		}
		else if(path.c_str()[0] == '\\' && path.c_str()[1] == '\\') {
			retval = true;
		}
#else
		if (path.c_str()[0] == '/') {
			retval = true;
		}
#endif
	}
	return retval;
}

bool Path::is_Absolute() const
{
	return Path::is_Absolute(mPath);
}
