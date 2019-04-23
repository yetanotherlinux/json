add_executable(jpath
        main)
target_link_libraries(jpath json)

install(TARGETS jpath DESTINATION bin)
