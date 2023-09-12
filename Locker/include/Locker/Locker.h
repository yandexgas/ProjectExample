//
// Created by dex_y on 12.09.2023.
//

#ifndef LESSONS_LOCKER_H
#define LESSONS_LOCKER_H
#include <cmath>

class Locker {
private:
    static const std::size_t MAX_KEY = 1e10;

    const std::size_t key_;

    bool closed_;

public:
    explicit Locker (std::size_t key, bool close = false);

    Locker& close();

    bool isOpen() const;

    bool open(std::size_t key);
};
#endif //LESSONS_LOCKER_H
