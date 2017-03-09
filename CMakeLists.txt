project(apriori)
cmake_minimum_required(VERSION 3.0.0)
include_directories("src/")
set(
	SRC 
	"main.cpp"
	"src/apriori.cpp"
)
add_executable(${PROJECT_NAME} ${SRC})
file(COPY "entrada" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
