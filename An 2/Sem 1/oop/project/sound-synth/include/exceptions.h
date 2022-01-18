#pragma once
#include <stdexcept>

class error : public std::runtime_error
{
public:
    explicit error(const std::string &arg);
};

class error_interval : public error
{
public:
    error_interval();
};

class error_scale : public error
{
public:
    explicit error_scale(const int id);
};