#include "JsonObject.h"

#include "json/JsonException.h"

namespace json {

    JsonObject::JsonObject(std::vector<std::shared_ptr<JsonProperty>> properties) :
            _properties(std::move(properties)) {
    }

    std::vector<std::shared_ptr<JsonProperty>> JsonObject::GetProperties() const {
        return _properties;
    }

    std::shared_ptr<JsonNode> JsonObject::FindProperty(const std::string &name) const {
        for (const std::shared_ptr<JsonProperty> &property : _properties) {
            if (property->GetName() == name) {
                return property->GetValue();
            }
        }
        return nullptr;
    }

    void JsonObject::AddProperty(const std::string &name, std::shared_ptr<JsonNode> value) {
        _properties.push_back(std::make_shared<JsonProperty>(name, value));
    }

    void JsonObject::SetProperty(const std::string &name, const std::shared_ptr<JsonNode> &value) {
        for (const std::shared_ptr<JsonProperty> &property : _properties) {
            if (property->GetName() == name) {
                property->SetValue(value);
                return;
            }
        }
        throw JsonException("Property '" + name + "' not exists");
    }
}