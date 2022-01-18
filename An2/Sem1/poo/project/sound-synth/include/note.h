#pragma once
#include <instruments.h>

template <class T>
class note;

template <class T>
std::ostream &operator<<(std::ostream &os, const note<T> &n);
template <class T>
class note
{
public:
    bool active;
    int id;
    T on;
    T off;
    friend std::ostream &operator<<<>(std::ostream &os, const note<T> &n);

    ~note();
    note(int id = 0, T on = 0.0, T off = 0.0, bool active = false);
};