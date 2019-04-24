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
        auto property{FindPropertyInternal(name, false)};
        return property == _properties.end() ? nullptr : property->operator->()->GetValue();
    }

    std::shared_ptr<JsonNode> JsonObject::GetProperty(const std::string &name) const {
        return FindPropertyInternal(name, true)->operator->()->GetValue();
    }

    void JsonObject::AddProperty(const std::string &name, std::shared_ptr<JsonNode> value) {
        _properties.push_back(std::make_shared<JsonProperty>(name, value));
    }

    void JsonObject::SetProperty(const std::string &name, const std::shared_ptr<JsonNode> &value) {
        FindPropertyInternal(name, true)->operator->()->SetValue(value);
    }

    void JsonObject::RemoveProperty(const std::string &name) {
        _properties.erase(FindPropertyInternal(name, true));
    }

    std::vector<std::shared_ptr<JsonProperty>>::const_iterator JsonObject::FindPropertyInternal(
            const std::string &name, bool mustExists) const {
        auto i{_properties.begin()};
        while (i != _properties.end()) {
            if (i->operator->()->GetName() == name) {
                break;
            } else {
                ++i;
            }
        }
        if (mustExists && i == _properties.end()) {
            throw JsonException("Property '" + name + "' not exists");
        }
        return i;
    }
}