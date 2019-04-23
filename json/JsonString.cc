#include "JsonString.h"

namespace json {

    JsonString::JsonString(std::string value) :
            _value(std::move(value)) {
    }

    std::string JsonString::GetValue() const {
        return _value;
    }
}