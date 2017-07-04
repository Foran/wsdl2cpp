/******************************************************************************
 * Project: wsdl2cpp
 * File: wsdl2cpp_client.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#ifndef WSDL2CPP_CLIENT_H_
#define WSDL2CPP_CLIENT_H_

#include <string>

namespace WSDL2CPP {
template <class T> class Serializable {
 public:
    static T Serialize(const std::string &source) {
        return T::_Serialize(source);
    }
    static std::string Deserialize(const T &source) {
        return source.Deserialize();
    }

 protected:
    virtual std::string Deserialize() const = 0;
};

}  // namespace WSDL2CPP

#endif  // WSDL2CPP_CLIENT_H_
