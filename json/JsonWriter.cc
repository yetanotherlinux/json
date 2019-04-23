#include "JsonWriter.h"

#include "json/JsonArray.h"
#include "json/JsonException.h"
#include "json/JsonObject.h"
#include "json/JsonProperty.h"
#include "json/JsonString.h"

namespace json {

    JsonWriter::JsonWriter(std::ostream *stream) :
            _stream(stream) {
    }

    void JsonWriter::Write(const Json &json) {
        Write(_stream, json.GetRoot());
    }

    void JsonWriter::Write(std::ostream *stream, const std::shared_ptr<JsonNode> &node) {
        if (std::shared_ptr<JsonString> string{std::dynamic_pointer_cast<JsonString>(node)}) {
            Write(stream, string);
        } else if (std::shared_ptr<JsonProperty> property{std::dynamic_pointer_cast<JsonProperty>(node)}) {
            Write(stream, property);
        } else if (std::shared_ptr<JsonObject> object{std::dynamic_pointer_cast<JsonObject>(node)}) {
            Write(stream, object);
        } else if (std::shared_ptr<JsonArray> array{std::dynamic_pointer_cast<JsonArray>(node)}) {
            Write(stream, array);
        } else {
            throw JsonException("Unexpected json node");
        }
    }

    void JsonWriter::Write(std::ostream *stream, const std::shared_ptr<JsonString> &node) {
        std::string value{node->GetValue()};
        stream->put('"');
        stream->write(value.c_str(), value.size());
        stream->put('"');
    }

    void JsonWriter::Write(std::ostream *stream, const std::shared_ptr<JsonProperty> &node) {
        Write(stream, std::make_shared<JsonString>(node->GetName()));
        stream->put(':');
        Write(stream, node->GetValue());
    }

    void JsonWriter::Write(std::ostream *stream, const std::shared_ptr<JsonObject> &node) {
        stream->put('{');
        bool delimiter{};
        for (const std::shared_ptr<JsonProperty> &property : node->GetProperties()) {
            if (delimiter) {
                stream->put(',');
            } else {
                delimiter = true;
            }
            Write(stream, property);
        }
        stream->put('}');
    }

    void JsonWriter::Write(std::ostream *stream, const std::shared_ptr<JsonArray> &node) {
        stream->put('[');
        bool delimiter{};
        for (const auto &item : node->GetItems()) {
            if (delimiter) {
                stream->put(',');
            } else {
                delimiter = true;
            }
            Write(stream, item);
        }
        stream->put(']');
    }
}
