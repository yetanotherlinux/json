#ifndef JSON_JSON_H
#define JSON_JSON_H

#include <memory>
#include "json/JsonNode.h"

namespace json {
    class Json {

    private:
        std::shared_ptr<JsonNode> _root;

    public:
        Json(const std::shared_ptr<JsonNode> &root = nullptr);

        std::shared_ptr<JsonNode> GetRoot() const;
    };
}

#endif
