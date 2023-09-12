//
// Created by dex_y on 12.09.2023.
//
#include <Locker/Locker.h>
#include <Utils/getNumber.h>

int main() {
    std::cout << ">> Insert key of locker: " << std::flush;
    size_t key = Utils::getNum<size_t>();

    Locker locker (key, true);
    std::cout << ">> Locker was created and locked." << std::endl;

    while (!locker.isOpen()) {
        try {
            std::cout << ">> Insert any key to try unlock: " << std::flush;
            size_t try_key = Utils::getNum<size_t>();
            locker.open(try_key);
        }
        catch (std::exception& e) {
            std::cout << e.what() << std::endl;
        }
    }

    std::cout << ">> Unlocked successfully!" << std::endl;
}