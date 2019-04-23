#ifndef JSON_JSON_WRITER_H
#define JSON_JSON_WRITER_H

#include <ostream>
#include "json/Json.h"
#include "json/JsonArray.h"
#include "json/JsonObject.h"
#include "json/JsonProperty.h"
#include "json/JsonString.h"

namespace json {
    class JsonWriter {

    private:
        std::ostream *const _stream;

    public:
        JsonWriter(std::ostream *stream);

        void Write(const Json &json);

    private:
        static void Write(std::ostream *stream, const std::shared_ptr<JsonNode> &node);

        static void Write(std::ostream *stream, const std::shared_ptr<JsonString> &node);

        static void Write(std::ostream *stream, const std::shared_ptr<JsonProperty> &node);

        static void Write(std::ostream *stream, const std::shared_ptr<JsonObject> &node);

        static void Write(std::ostream *stream, const std::shared_ptr<JsonArray> &node);

    };
}

#endif
