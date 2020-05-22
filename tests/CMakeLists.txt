project(cppredicate-tests)

add_executable(PredicatesBenchmarks main.cpp original.cpp)
target_link_libraries(PredicatesBenchmarks PUBLIC predicates)
add_test(NAME PredicatesBenchmarks COMMAND PredicatesBenchmarks)

add_executable(SupportTests
	main.cpp
	circle2d.cpp
	plane3d.cpp
	point2d.cpp
	point3d.cpp
	ray2d.cpp
	sphere.cpp
)
target_link_libraries(SupportTests PRIVATE libcppredicates)
add_test(NAME SupportTests COMMAND SupportTests)

add_executable(CppredicatesTests
	main.cpp
	cppredicates.cpp
)
target_link_libraries(CppredicatesTests PRIVATE libcppredicates)
add_test(NAME CppredicatesTests COMMAND CppredicatesTests)
