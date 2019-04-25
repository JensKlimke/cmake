//
// Created by klimke on 25.04.2019.
//

#include <iostream>
#include <two/lib.h>
#include <one/lib.h>

bool two() {

    one();
    std::cout << "TWO" << std::endl;

    return false;

}