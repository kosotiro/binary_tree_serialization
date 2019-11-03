# Define an executable
add_executable(serialize_app
    src/serialize_process.c
)

target_include_directories(serialize_app
  PUBLIC
        ${MAINFOLDER}/binary_tree/include
        ${MAINFOLDER}/serialize/include
)

# Define the libraries this project depends upon
target_link_libraries(serialize_app
    serdeserbtree)
