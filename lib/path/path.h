/******************************************************************************
 * Project: wsdl2cpp
 * File: lib/path/path.h
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef LIB_PATH_PATH_H_
#define LIB_PATH_PATH_H_

#include <string>

namespace wsdl2cpp {
namespace lib {
namespace path {

class Path {
 public:
    Path();
    explicit Path(const ::std::string &source);
    Path(const Path &source);
    ~Path();

    Path &operator=(const ::std::string &source);
    Path &operator=(const Path &source);
    bool operator==(const ::std::string &source);
    bool operator==(const Path &source);

    ::std::string get_Raw() const;
    ::std::string get_Absolute() const;
    static ::std::string get_Absolute(const ::std::string &path);
    ::std::string get_BaseFilename() const;
    static ::std::string get_BaseFilename(const ::std::string &path);
    ::std::string get_BasePath() const;
    static ::std::string get_BasePath(const ::std::string &path);
    ::std::string get_UNC() const;
    static ::std::string get_UNC(const ::std::string &path);
    Path ResolveRelative(const ::std::string &relative) const;
    static Path ResolveRelative(const ::std::string &source,
                                const ::std::string &relative);
    bool is_UNC() const;
    static bool is_UNC(const ::std::string &path);
    bool is_Absolute() const;
    static bool is_Absolute(const ::std::string &path);
    static bool is_Relative(const ::std::string &relative);
    static ::std::string CurrentDirectory();
    ::std::string get_Protocol() const;

 private:
    ::std::string mPath;
};

}  // namespace path
}  // namespace lib
}  // namespace wsdl2cpp

#endif  // LIB_PATH_PATH_H_
