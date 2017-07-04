/******************************************************************************
 * Project: wsdl2cpp
 * File: main.cpp
 * Author: Ben M. Ward <ben.ward@gmail.com>
 * Copyright 2012-2017 Ben M. Ward
 *****************************************************************************/
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <vector>

#include "gflags/gflags.h"
#include "lib/path/path.h"
#include "lib/typegenerator/typegenerator.h"
#include "lib/wsdl/wsdl.h"

::std::vector<::std::string> Filenames;

bool ParseCmdLine(int argc, char **argv) {
    bool retval = true;
    gflags::SetUsageMessage(::std::string("Usage: ") + argv[0] +
                                          " [options] filename "
                                          "[filename [filename ...]]");
    gflags::SetVersionString("0.0.1a");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    for (int i = 1; retval && i < argc; i++) {
        Filenames.push_back(::wsdl2cpp::lib::path::Path::get_UNC(argv[i]));
    }
    if (Filenames.size() <= 0) gflags::ShowUsageWithFlags(argv[0]);
    return retval;
}

int main(int argc, char **argv) {
    int retval = 0;

    if (ParseCmdLine(argc, argv)) {
        for (::std::string filename : Filenames) {
            ::std::cout << "Loading " << filename << "..." << ::std::endl;
            ::wsdl2cpp::lib::wsdl::WSDL wsdl(filename);
            for (::std::string portTypeName : wsdl.get_PortTypeNames()) {
                ::std::cout << "Generating codegen/"
                            << wsdl.get_PortType(portTypeName).get_Name()
                            << ".h ..." << ::std::endl;
                for (::std::string operationName :
                     wsdl.get_PortType(portTypeName).get_OperationNames()) {
                    ::std::cout << "Generating Operation " << operationName
                                << ::std::endl;
                    ::std::string inputMessageName =
                      wsdl.get_PortType(portTypeName)
                          .get_Operation(operationName)
                          .get_InputMessageName();
                    ::std::string outputMessageName =
                      wsdl.get_PortType(portTypeName)
                          .get_Operation(operationName)
                          .get_OutputMessageName();
                    if (inputMessageName.length() > 0) {
                        for (::std::string partName :
                             wsdl.get_Message(inputMessageName)
                                 .get_PartNames()) {
                            ::std::cout << "Generating Input Message Part "
                                        << partName << ::std::endl;
                            ::std::string elementName =
                              wsdl.get_Message(inputMessageName)
                                  .get_Part(partName)
                                  .get_Element();
                            wsdl.get_Type(elementName);
                        }
                    }
                    if (outputMessageName.length() > 0) {
                        for (::std::string partName :
                             wsdl.get_Message(outputMessageName)
                                 .get_PartNames()) {
                            ::std::cout << "Generating Output Message Part "
                                        << partName << ::std::endl;
                            ::std::string elementName =
                              wsdl.get_Message(outputMessageName)
                                  .get_Part(partName)
                                  .get_Element();
                            ::std::cout << "Generating codegen/" +
                                           wsdl.get_Type(elementName).get_Name()
                                        << ".h ..." << ::std::endl;
                            ::wsdl2cpp::lib::typegenerator::TypeGenerator
                                generator("codegen", wsdl.get_Type(elementName)
                                                         .get_Prefix());
                            generator.Generate(wsdl.get_Type(elementName));
                        }
                    }
                }
            }
        }
    }

    return retval;
}
