#ifndef JSON_JSON_PATH_H
#define JSON_JSON_PATH_H

#include <memory>
#include <string>
#include <vector>
#include "json/Json.h"

namespace json {
    class JsonPath {

    private:
        const std::string _expression;

    public:
        JsonPath(std::string expression);

        std::vector<std::shared_ptr<JsonNode>> ApplyTo(const Json &json);

    private:
        static std::vector<std::shared_ptr<JsonNode>> Process(
                const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream);

        static std::vector<std::shared_ptr<JsonNode>> ProcessObject(
                const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream);

        static std::vector<std::shared_ptr<JsonNode>> ProcessArray(
                const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream);

        static std::vector<std::shared_ptr<JsonNode>> ProcessFilter(
                const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream);

        static std::vector<std::shared_ptr<JsonNode>> ProcessCompare(
                const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream);

        static std::vector<std::shared_ptr<JsonNode>> ProcessScope(
                const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream);

        static std::string GetWord(std::istringstream &stream);

        static void Expect(char c, std::istringstream &stream);
    };
}

#endif
