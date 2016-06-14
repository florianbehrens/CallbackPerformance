project(CallbackPerformance)
cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS signals signals2)

add_definitions(-std=c++14)

add_executable(
    ${PROJECT_NAME}
    func.cpp
    func.hpp
    main.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    ${Boost_SIGNALS_LIBRARY}
    ${Boost_SIGNALS2_LIBRARY}
)
