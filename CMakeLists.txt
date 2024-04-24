cmake_minimum_required(VERSION 3.5)
project(roscpp_tcp_client)

add_compile_options(-std=c++14)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  nlohmann_json
)

find_package(Boost 1.65.1 COMPONENTS serialization REQUIRED)

catkin_package(
  #INCLUDE_DIRS include
  #LIBRARIES ${PROJECT_NAME}
  #CATKIN_DEPENDS roscpp std_msgs 
  #DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(roscpp_tcp_talker src/roscpp_tcp_talker.cpp )
target_link_libraries(roscpp_tcp_talker
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)