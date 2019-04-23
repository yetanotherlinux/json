#ifndef JSON_JSON_EXCEPTION_H
#define JSON_JSON_EXCEPTION_H

#include <string>

namespace json {
    class JsonException : public std::exception {

    private:
        const std::string _message;

    public:
        explicit JsonException(std::string message);

        const char *what() const noexcept override;
    };
}

#endif
