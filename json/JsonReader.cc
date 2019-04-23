#include "JsonReader.h"

#include <sstream>
#include "json/JsonException.h"

namespace json {

    JsonReader::JsonReader(std::istream *stream) :
            _stream(stream) {
    }

    Json JsonReader::Read() {
        std::shared_ptr<JsonNode> root{ReadNext(_stream)};
        SkipWhitespace(_stream);
        if (root && !(_stream->eof())) {
            throw JsonException("EOF expected at " + std::to_string(_stream->tellg()));
        }
        return Json{root};
    }

    std::shared_ptr<JsonNode> JsonReader::ReadNext(std::istream *stream) {
        SkipWhitespace(stream);
        switch (stream->peek()) {
            case '"':
                return ReadString(stream);
            case '{':
                return ReadObject(stream);
            case '[':
                return ReadArray(stream);
            default:
                std::string message{"'"};
                message += static_cast<char>(stream->peek());
                message += "' not expected at ";
                message += std::to_string(stream->tellg());
                throw JsonException(message);
        }
    }

    std::shared_ptr<JsonString> JsonReader::ReadString(std::istream *stream) {
        Expect(stream, '"');

        bool isEscaped{};
        std::ostringstream buffer;
        while (isEscaped || stream->peek() != '"') {
            if (stream->eof()) {
                throw JsonException("EOF not expected");
            }
            int32_t s{stream->get()};
            if (s == '\\' && !isEscaped) {
                isEscaped = true;
            } else {
                isEscaped = false;
                buffer << static_cast<char>(s);
            }
        }
        Expect(stream, '"');
        return std::make_shared<JsonString>(buffer.str());
    }

    std::shared_ptr<JsonProperty> JsonReader::ReadProperty(std::istream *stream) {
        SkipWhitespace(stream);
        std::shared_ptr<JsonString> name{ReadString(stream)};
        SkipWhitespace(stream);
        Expect(stream, ':');
        std::shared_ptr<JsonNode> value{ReadNext(stream)};
        return std::make_shared<JsonProperty>(name->GetValue(), value);
    }

    std::shared_ptr<JsonObject> JsonReader::ReadObject(std::istream *stream) {
        std::vector<std::shared_ptr<JsonProperty>> properties{};
        ForEach(stream, '{', '}', [&properties](std::istream *s) {
            properties.push_back(ReadProperty(s));
        });
        return std::make_shared<JsonObject>(properties);
    }

    std::shared_ptr<JsonArray> JsonReader::ReadArray(std::istream *stream) {
        std::vector<std::shared_ptr<JsonNode>> items{};
        ForEach(stream, '[', ']', [&items](std::istream *s) {
            items.push_back(ReadNext(s));
        });
        return std::make_shared<JsonArray>(items);
    }

    void JsonReader::ForEach(
            std::istream *stream, char begin, char end, const std::function<void(std::istream *)> &callback) {
        Expect(stream, begin);
        SkipWhitespace(stream);
        if (stream->peek() != end) {
            do {
                callback(stream);
                SkipWhitespace(stream);
            } while (stream->peek() == ',' && stream->get());
        }
        Expect(stream, end);
    }

    void JsonReader::SkipWhitespace(std::istream *stream) {
        while (std::isspace(stream->peek())) {
            stream->get();
        }
    }

    void JsonReader::Expect(std::istream *stream, char c) {
        if (stream->eof() || stream->get() != c) {
            std::string message{"'"};
            message += c;
            message += "' expected but '";
            if (stream->eof()) {
                message += "EOF";
            } else {
                message += static_cast<char>(stream->unget().peek());
            }
            message += "'";
            throw JsonException(message);
        }
    }
}
