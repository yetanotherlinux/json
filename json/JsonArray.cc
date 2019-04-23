#include "JsonArray.h"

namespace json {

    JsonArray::JsonArray(std::vector<std::shared_ptr<JsonNode>> items) :
            _items(std::move(items)) {
    }

    std::vector<std::shared_ptr<JsonNode>> JsonArray::GetItems() const {
        return _items;
    }
}
