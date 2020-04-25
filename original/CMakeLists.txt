project(original)

add_library(predicates predicates.c)

target_include_directories(predicates
	PUBLIC .
)

install(TARGETS predicates DESTINATION lib)
install(FILES predicates.h DESTINATION include)

