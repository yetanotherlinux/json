#ifndef JSON_JSON_READER_H
#define JSON_JSON_READER_H

#include <functional>
#include <istream>
#include "json/Json.h"
#include "json/JsonArray.h"
#include "json/JsonObject.h"
#include "json/JsonProperty.h"
#include "json/JsonString.h"

namespace json {
    class JsonReader {

    private:
        std::istream *const _stream;

    public:
        JsonReader(std::istream *stream);

        Json Read();

    private:
        static std::shared_ptr<JsonNode> ReadNext(std::istream *stream);

        static std::shared_ptr<JsonString> ReadString(std::istream *stream);

        static std::shared_ptr<JsonProperty> ReadProperty(std::istream *stream);

        static std::shared_ptr<JsonObject> ReadObject(std::istream *stream);

        static std::shared_ptr<JsonArray> ReadArray(std::istream *stream);

        static void ForEach(
                std::istream *stream, char begin, char end, const std::function<void(std::istream *)> &callback);

        static void SkipWhitespace(std::istream *stream);

        static void Expect(std::istream *stream, char c);
    };
}

#endif
