//
// Created by vitaliy on 5/24/21.
//

#ifndef ALTIUS_NATIVE_HELLOWORLDIMPL_H
#define ALTIUS_NATIVE_HELLOWORLDIMPL_H

#include <string>
//#include <stdio.h>


#include "HelloWorld.hpp"

using namespace std;


void testHelloWorld();

class HelloWorldImpl : public dgn::panorama::HelloWorld {

public:

    const char *hstr = "GDAL  -  Hello World - Constant of Class HelloWorldImpl";

    string getHelloWorld();
};


#endif //ALTIUS_NATIVE_HELLOWORLDIMPL_H
