#pragma once
#include <string>

struct Error {
    std::string message;
    Error(std::string message) : message(message) {}
};

template<typename T>
class Result {
public:
    Result(const T& value) : m_value(value), m_error(false) {}
    Result(const Error& error) : m_error_message(error.message), m_error(true) {}
private:
    union {
        T m_value;
        std::string m_error_message;
    };
    bool m_error;
};

