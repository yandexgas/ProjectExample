//
// Created by dex_y on 12.09.2023.
//

#ifndef LESSONS_GETNUMBER_H
#define LESSONS_GETNUMBER_H
#include <iostream>
#include <limits>

namespace Utils {
    template<class T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T number;
        while (true) {
            std::cin >> number;
            if (std::cin.eof())
                throw std::runtime_error("It is EOF, sorry\n");
            else if (std::cin.bad())
                throw std::runtime_error("BAD!\n");
            else if (std::cin.fail() || number < min || number > max) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            } else return number;
        }
    }
}
#endif //LESSONS_GETNUMBER_H
