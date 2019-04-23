#ifndef JSON_JSON_ARRAY_H
#define JSON_JSON_ARRAY_H

#include <memory>
#include <vector>
#include "json/JsonNode.h"

namespace json {
    class JsonArray : public JsonNode {

    private:
        const std::vector<std::shared_ptr<JsonNode>> _items;

    public:
        JsonArray(std::vector<std::shared_ptr<JsonNode>> items);

        std::vector<std::shared_ptr<JsonNode>> GetItems() const;
    };
}

#endif
