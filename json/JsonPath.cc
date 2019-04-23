#include "JsonPath.h"

#include <sstream>
#include "json/JsonArray.h"
#include "json/JsonException.h"
#include "json/JsonObject.h"

namespace json {

    JsonPath::JsonPath(std::string expression) :
            _expression(std::move(expression)) {
    }

    std::vector<std::shared_ptr<JsonNode>> JsonPath::ApplyTo(const Json &json) {
        std::istringstream stream{_expression};
        std::vector<std::shared_ptr<JsonNode>> result{Process(json, {}, stream)};
        if (!stream.eof()) {
            throw JsonException("Invalid path '" + std::string(_expression) + "'");
        }
        return result;
    }

    std::vector<std::shared_ptr<JsonNode>> JsonPath::Process(
            const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream) {
        switch (stream.peek()) {
            case '$':
                stream.get();
                return Process(json, {json.GetRoot()}, stream);
            case '.':
                return ProcessObject(json, context, stream);
            case '[':
                return ProcessArray(json, context, stream);
            case '?':
                return ProcessFilter(json, context, stream);
            case '(':
                return ProcessScope(json, context, stream);
            case '=':
                return ProcessCompare(json, context, stream);
            default:
                return context;
        }
    }

    std::vector<std::shared_ptr<JsonNode>> JsonPath::ProcessObject(
            const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream) {
        Expect('.', stream);
        std::string name{GetWord(stream)};
        std::vector<std::shared_ptr<JsonNode>> nodes{};
        for (const std::shared_ptr<JsonNode> &node : context) {
            if (std::shared_ptr<JsonObject> object{std::dynamic_pointer_cast<JsonObject>(node)}) {
                if (std::shared_ptr<JsonNode> value{object->FindProperty(name)}) {
                    nodes.push_back(value);
                }
            }
        }
        return Process(json, nodes, stream);
    }

    std::vector<std::shared_ptr<JsonNode>> JsonPath::ProcessArray(
            const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream) {
        Expect('[', stream);

        Expect('*', stream);
        uint64_t begin{};
        uint64_t count{context.size()};

        std::vector<std::shared_ptr<JsonNode>> nodes{};
        for (const std::shared_ptr<JsonNode> &node : context) {
            if (std::shared_ptr<JsonArray> array{std::static_pointer_cast<JsonArray>(node)}) {
                if (begin) {
                    --begin;
                    continue;
                }
                if (!count)
                    break;
                --count;
                for (const std::shared_ptr<JsonNode> &child : array->GetItems())
                    nodes.push_back(child);
            }
        }
        Expect(']', stream);
        return Process(json, nodes, stream);
    }

    std::vector<std::shared_ptr<JsonNode>> JsonPath::ProcessFilter(
            const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream) {
        Expect('?', stream);
        bool isPositive{true};
        if (stream.peek() == '!') {
            stream.get();
            isPositive = false;
        }
        std::istringstream::pos_type position{stream.tellg()};
        std::vector<std::shared_ptr<JsonNode>> nodes{};
        for (const std::shared_ptr<JsonNode> &node : context) {
            stream.seekg(position);
            if (isPositive ^ Process(json, {node}, stream).empty()) {
                nodes.push_back(node);
            }
        }
        return Process(json, nodes, stream);
    }

    std::vector<std::shared_ptr<JsonNode>> JsonPath::ProcessCompare(
            const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream) {
        Expect('=', stream);
        Expect('"', stream);
        std::string value{GetWord(stream)};
        std::vector<std::shared_ptr<JsonNode>> nodes{};
        for (const std::shared_ptr<JsonNode> &node : context) {
            if (std::shared_ptr<JsonString> string{std::dynamic_pointer_cast<JsonString>(node)};
                    string->GetValue() == value)
                nodes.push_back(node);
        }
        Expect('"', stream);
        return Process(json, nodes, stream);
    }

    std::vector<std::shared_ptr<JsonNode>> JsonPath::ProcessScope(
            const Json &json, const std::vector<std::shared_ptr<JsonNode>> &context, std::istringstream &stream) {
        Expect('(', stream);
        std::vector<std::shared_ptr<JsonNode>> nodes{Process(json, context, stream)};
        Expect(')', stream);
        return nodes;
    }

    std::string JsonPath::GetWord(std::istringstream &stream) {
        std::string word{};
        while (std::isalpha(stream.peek())) {
            word += static_cast<char>(stream.get());
        }
        return word;
    }

    void JsonPath::Expect(char c, std::istringstream &stream) {
        if (stream.eof() || stream.get() != c) {
            std::string message{"'"};
            message += c;
            message += "' expected but '";
            if (stream.eof()) {
                message += "EOF";
            } else {
                message += static_cast<char>(stream.unget().peek());
            }
            message += "'";
            throw JsonException(message);
        }
    }
}
