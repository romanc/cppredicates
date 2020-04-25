project(cppredicate-tests)

add_executable(PredicatesBenchmarks main.cpp original.cpp)
target_link_libraries(PredicatesBenchmarks PUBLIC predicates)
add_test(NAME PredicatesBenchmarks COMMAND PredicatesBenchmarks)

