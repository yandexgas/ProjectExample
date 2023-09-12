//
// Created by dex_y on 12.09.2023.
//

#include <stdexcept>

#include "Locker/Locker.h"

Locker::Locker(std::size_t key, bool close) : key_(key), closed_(close){
    if(key > MAX_KEY)
        throw std::invalid_argument("Too large key.");
}

Locker &Locker::close() {
    closed_ = true;
    return *this;
}

bool Locker::isOpen() const {
    return !closed_;
}

bool Locker::open(std::size_t key) {
    if(key == key_)
        closed_ = false;
    return !closed_;
}

