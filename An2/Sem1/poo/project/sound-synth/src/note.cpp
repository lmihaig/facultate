#include <note.h>
#include <exceptions.h>

template <class T>
note<T>::note(int id, T on, T off, bool active) : id{id}, on{on}, off{off}, active{active}
{
    if (on < off)
        throw error_interval();
    if (id < 64 || id > 80)
        throw error_scale(id);
}

template <class T>
note<T>::~note()
{
}

template <class T>
std::ostream &operator<<(std::ostream &os, const note<T> &n)
{
    os << "Note ID: " << n.id;
    return os;
}

template class note<float>;
template class note<double>;

template std::ostream &operator<<<>(std::ostream &o, const note<float> &n);
template std::ostream &operator<<<>(std::ostream &o, const note<double> &n);