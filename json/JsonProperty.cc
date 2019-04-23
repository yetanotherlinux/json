#include "JsonProperty.h"

namespace json {

    JsonProperty::JsonProperty(std::string name, std::shared_ptr<JsonNode> value) :
            _name(std::move(name)),
            _value(std::move(value)) {
    }

    std::string JsonProperty::GetName() const {
        return _name;
    }

    std::shared_ptr<JsonNode> JsonProperty::GetValue() const {
        return _value;
    }

    void JsonProperty::SetValue(const std::shared_ptr<JsonNode> &value) {
        _value = value;
    }
}
