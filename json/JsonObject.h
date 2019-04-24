#ifndef JSON_JSON_OBJECT_H
#define JSON_JSON_OBJECT_H

#include "json/JsonNode.h"

#include <vector>
#include <memory>
#include "json/JsonProperty.h"

namespace json {
    class JsonObject : public JsonNode {

    private:
        std::vector<std::shared_ptr<JsonProperty>> _properties;

    public:
        JsonObject(std::vector<std::shared_ptr<JsonProperty>> properties = {});

        std::vector<std::shared_ptr<JsonProperty>> GetProperties() const;

        std::shared_ptr<JsonNode> FindProperty(const std::string &name) const;

        std::shared_ptr<JsonNode> GetProperty(const std::string &name) const;

        void AddProperty(const std::string &name, std::shared_ptr<JsonNode> value);

        void SetProperty(const std::string &name, const std::shared_ptr<JsonNode> &value);

        void RemoveProperty(const std::string &name);

    private:
        std::vector<std::shared_ptr<JsonProperty>>::const_iterator FindPropertyInternal(
                const std::string &name, bool mustExists) const;
    };
}

#endif
