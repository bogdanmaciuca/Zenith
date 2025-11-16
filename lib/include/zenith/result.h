#pragma once
#include <string>
#include <variant>

struct Error {
    std::string message;
    Error(std::string message) : message(message) {}
};

template<typename T = void>
class Result {
public:
    Result(const T& value) { std::get<0>(m_variant) = value; }
    Result(const Error& error) { std::get<1>(m_variant) = error.message; }
    operator bool() const {
        return m_variant.index() == 0;
    }
    T Value() const {
        return std::get<0>(m_variant);
    }
    struct Error Error() const {
        return (struct Error)(std::get<1>(m_variant));
    }
    std::string ErrorStr() const {
        return std::get<1>(m_variant);
    }
private:
    std::variant<T, std::string> m_variant;
};

template<>
class Result<void> {
public:
    Result(const Error& error) : m_error(error.message), m_is_error(true) {}
    Result(bool success) : m_error(""), m_is_error(!success) {}
    operator bool() const {
        return !m_is_error;
    }
    std::string Error() const {
        return m_error;
    }
private:
    std::string m_error;
    bool m_is_error;
};

