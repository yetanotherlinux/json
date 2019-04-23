#include <iostream>
#include <sstream>
#include "json/JsonPath.h"
#include "json/JsonReader.h"
#include "json/JsonWriter.h"

using namespace json;

int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        return -1;
    }

    std::string expression{argv[1]};

    Json json{};
    if (argc == 2) {
        json = JsonReader(&std::cin).Read();
    } else {
        std::istringstream stream{argv[2]};
        json = JsonReader(&stream).Read();
    }

    JsonPath jsonPath{expression};
    std::vector<std::shared_ptr<JsonNode>> nodes{jsonPath.ApplyTo(json)};
    for (const std::shared_ptr<JsonNode> &node : nodes) {
        JsonWriter(&std::cout).Write(node);
        std::cout << std::endl;
    }
    return 0;
}
