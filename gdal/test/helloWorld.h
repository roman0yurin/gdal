//
// Created by vitaliy on 5/24/21.
//

#ifndef ALTIUS_NATIVE_HELLOWORLD_H
#define ALTIUS_NATIVE_HELLOWORLD_H

#include <string>
//#include <stdio.h>


using namespace std;

void testHelloWorld();

class HelloWorld {

public:

    const char *hstr = "GDAL  -  This Hello World String";

    string getHelloWorld();
};


#endif //ALTIUS_NATIVE_HELLOWORLD_H
