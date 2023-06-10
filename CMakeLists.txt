cmake_minimum_required(VERSION 3.25)
project(jakdojade)

set(CMAKE_CXX_STANDARD 17)

add_executable(jakdojade main.cpp engine.cpp engine.cpp custom_string.h bfs_point.h custom_queue.h linked_list.h linked_list_node.h adjacency_list.h custom_unordered_map.h key_value.h custom_priority_queue.h)
