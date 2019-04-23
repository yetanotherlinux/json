add_library(json SHARED
        Json
        JsonArray
        JsonException
        JsonNode
        JsonObject
        JsonPath
        JsonProperty
        JsonReader
        JsonString
        JsonWriter)

install(TARGETS json DESTINATION lib)
install(FILES Json.h DESTINATION include/json)
install(FILES JsonArray.h DESTINATION include/json)
install(FILES JsonNode.h DESTINATION include/json)
install(FILES JsonObject.h DESTINATION include/json)
install(FILES JsonProperty.h DESTINATION include/json)
install(FILES JsonReader.h DESTINATION include/json)
install(FILES JsonString.h DESTINATION include/json)
install(FILES JsonWriter.h DESTINATION include/json)
