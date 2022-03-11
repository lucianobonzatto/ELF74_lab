/*
 * printMacros.cpp
 *
 *  Created on: 10 de mar de 2022
 *      Author: lucia
 */
#include<iostream>

extern "C" void printMacros();

void printMacros(){
    std::cout << "macros:" << std::endl;
    std::cout << "\t cplusplus: " << __cplusplus << std::endl;
    std::cout << "\t DATE: " << __DATE__ << std::endl;
    std::cout << "\t TIme: " << __TIME__ << std::endl;
    std::cout << "\t FILE: " << __FILE__ << std::endl;
    std::cout << "\t LINE: " << __LINE__ << std::endl;
    std::cout << "\t STDC: " << __STDC__ << std::endl;
    std::cout << "\t ARM_ARCH: " << __ARM_ARCH << std::endl;
    std::cout << "\t ARM_ARCH_ISA_THUMB: " << __ARM_ARCH_ISA_THUMB << std::endl;
    std::cout << "\t ARM_SIZEOF_MINIMAL_ENUM: " << __ARM_SIZEOF_MINIMAL_ENUM << std::endl;
    std::cout << "\t ARM_SIZEOF_WCHAR_T: " << __ARM_SIZEOF_WCHAR_T << std::endl;

    float var;
    std::cout << "escreva um float: ";
    std:: cin >> var;

    var = var + (float)2.9;
    std::cout << "valor somado: " << var << std::endl;
    // what assembly instruction was used for this add? why?
}
