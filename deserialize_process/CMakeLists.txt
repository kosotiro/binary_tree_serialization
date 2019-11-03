# Define an executable
add_executable(deserialize_app
    src/deserialize_process.c
)

target_include_directories(deserialize_app
 PUBLIC
        ${MAINFOLDER}/binary_tree/include
        ${MAINFOLDER}/serialize/include
)

# Define the libraries this project depends upon
target_link_libraries(deserialize_app
    serdeserbtree)
