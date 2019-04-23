#ifndef JSON_JSON_STRING_H
#define JSON_JSON_STRING_H

#include "json/JsonNode.h"

#include <string>

namespace json {
    class JsonString : public JsonNode {

    private:
        const std::string _value;

    public:
        JsonString(std::string value);

        std::string GetValue() const;
    };
}

#endif
