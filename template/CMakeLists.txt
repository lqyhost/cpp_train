
ADD_LIBRARY(man man.cpp)

add_executable(test test.cpp)
add_executable(main1 main.cpp)
add_executable(p4 project4.cpp)
add_executable(p5 p5.cpp)
add_executable(p6 p6.cpp)
add_executable(p7 p7.cpp)
TARGET_LINK_LIBRARIES(main1 man)

add_executable(fdb_test fdb_test.cpp)
add_executable(test1 test1.cpp)