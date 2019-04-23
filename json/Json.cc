#include "Json.h"

#include "json/JsonObject.h"

namespace json {

    Json::Json(const std::shared_ptr<JsonNode> &root) :
            _root(root == nullptr ? std::shared_ptr<JsonNode>(new JsonObject()) : root) {
    }

    std::shared_ptr<JsonNode> Json::GetRoot() const {
        return _root;
    }
}
