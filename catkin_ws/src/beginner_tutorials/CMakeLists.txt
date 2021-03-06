cmake_minimum_required(VERSION 2.8.3)
project(beginner_tutorials)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

 add_message_files(
   FILES
   Num.msg
 )


 add_service_files(
   FILES
   AddTwoInts.srv
)

 generate_messages(
   DEPENDENCIES
   std_msgs
 )

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES beginner_tutorials
#  CATKIN_DEPENDS roscpp rospy std_msgs
#  DEPENDS system_lib
)


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)


file(GLOB helloworld_SRC
    "src/thrift_gen/*.h"
    "src/thrift_gen/*.cpp"
)


add_executable(talker ${helloworld_SRC} src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES} thrift)
add_dependencies(talker beginner_tutorials_generate_messages_cpp)

add_executable(listener ${helloworld_SRC} src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES} thrift)
add_dependencies(listener beginner_tutorials_generate_messages_cpp)

add_executable(add_two_ints_server src/add_two_ints_server.cpp)
target_link_libraries(add_two_ints_server ${catkin_LIBRARIES})
add_dependencies(add_two_ints_server beginner_tutorials_gencpp)
 
add_executable(add_two_ints_client src/add_two_ints_client.cpp)
target_link_libraries(add_two_ints_client ${catkin_LIBRARIES})
add_dependencies(add_two_ints_client beginner_tutorials_gencpp)
