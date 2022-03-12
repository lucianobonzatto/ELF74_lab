/******************************
 * @file printMacros.cpp
 * @brief lab1 embarcados
 * @date 03/10/2022
 * @author Hadryan Salles
 *         Luciano Bonzatto
 ******************************/

#include <iostream>

extern "C" void printMacros();

void printMacros() {
    std::cout << "__cplusplus: " << __cplusplus << '\n';
    std::cout << "__DATE__: " << __DATE__ << '\n';
    std::cout << "__TIME__: " << __TIME__ << '\n';
    std::cout << "__FILE__: " << __FILE__ << '\n';
    std::cout << "__LINE__: " << __LINE__ << '\n';
    std::cout << "__STDC__: " << __STDC__ << '\n';
    std::cout << "__ARM_ARCH: " << __ARM_ARCH << '\n';
    std::cout << "__ARM_ARCH_ISA_THUMB: " << __ARM_ARCH_ISA_THUMB << '\n';
    std::cout << "__ARM_SIZEOF_MINIMAL_ENUM: " << __ARM_SIZEOF_MINIMAL_ENUM << '\n';
    std::cout << "__ARM_SIZEOF_WCHAR_T: " << __ARM_SIZEOF_WCHAR_T << '\n';

    float var;
    std::cout << "x = ";
    std:: cin >> var;

    float var2 = 1.3f;
    var = var + var2;
    std::cout << "x + 1.3f = " << var << '\n';

    // the instructions used to sum floats was: vadd.f32 s15, s16, s15
}
