cmake_minimum_required(VERSION 3.8)
project(Q002)

if(DEFINED ONLINE_JUDGE_MODE AND ONLINE_JUDGE_MODE STREQUAL ON)
	foreach(i RANGE 1 5)
	add_executable("${PROJECT_NAME}_Case${i}"
		"${CMAKE_CURRENT_SOURCE_DIR}/entrypoint.cpp"
		"${CMAKE_CURRENT_SOURCE_DIR}/circuit.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/test.h"
		"${CMAKE_CURRENT_SOURCE_DIR}/online_judge/case${i}.h")
	target_include_directories("${PROJECT_NAME}_Case${i}" PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
	target_include_directories("${PROJECT_NAME}_Case${i}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/online_judge")
	target_compile_definitions("${PROJECT_NAME}_Case${i}" PRIVATE "ONLINE_JUDGE=1")
	target_compile_definitions("${PROJECT_NAME}_Case${i}" PRIVATE "CASE=\"case${i}.h\"")
	endforeach()
else()

add_executable(${PROJECT_NAME}
	"${CMAKE_CURRENT_SOURCE_DIR}/entrypoint.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/circuit.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/case.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/test.h"
)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
endif()