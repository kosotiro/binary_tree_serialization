# Define an executable
add_executable(test_btree
    src/test_btree.c
)

target_include_directories(test_btree
  PUBLIC
    ${MAINFOLDER}/mybtree/include
)

# Define the libraries this project depends upon
target_link_libraries(test_btree
    mybtree)
