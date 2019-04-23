#include "JsonException.h"

namespace json {

    JsonException::JsonException(std::string message) :
            _message(std::move(message)) {

    }

    const char *JsonException::what() const noexcept {
        return _message.c_str();
    }
}
