//
// Created by vitaliy on 5/24/21.
//

#include "helloWorld.h"
#include <cstdio>
#include <ctime>

#include <iostream>
#include <fstream>


using namespace std;



string HelloWorld::getHelloWorld() {
    string hString2(hstr); // Строка из константы класса
    string hString( " ======================================================  GDAL  -  This Hello World String"); // Строка - создание
    return hString ;
}



void testHelloWorld(){
    HelloWorld testHW;
    cout << "testHelloWorld(): " << testHW.getHelloWorld();
};

