//
// Created by vitaliy on 5/24/21.
//

#include "HelloWorldImpl.h"
#include <cstdio>
#include <ctime>

#include <iostream>
#include <fstream>


using namespace std;




string HelloWorldImpl::getHelloWorld() {
    string hString2(hstr); // Строка из константы класса
    string hString( " ======================================================  GDAL  -  This Hello World String"); // Строка - создание
    return hString2 ;
}



void testHelloWorld(){
    HelloWorldImpl testHW;
    cout << "testHelloWorld(): " << testHW.getHelloWorld();
};

/** Используем "умный" указатель */
std::shared_ptr<dgn::panorama::HelloWorld> dgn::panorama::HelloWorld::create(){
   return std::shared_ptr<dgn::panorama::HelloWorld>(new HelloWorldImpl() );
}

