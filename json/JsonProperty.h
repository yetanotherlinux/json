#ifndef JSON_JSON_PROPERTY_H
#define JSON_JSON_PROPERTY_H

#include "json/JsonNode.h"

#include <memory>
#include "json/JsonString.h"

namespace json {
    class JsonProperty : public JsonNode {

    private:
        const std::string _name;
        std::shared_ptr<JsonNode> _value;

    public:
        JsonProperty(std::string name, std::shared_ptr<JsonNode> value);

        std::string GetName() const;

        std::shared_ptr<JsonNode> GetValue() const;

        void SetValue(const std::shared_ptr<JsonNode> &value);
    };
}

#endif
