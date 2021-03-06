cmake_minimum_required(VERSION 2.6)

project(OPENCV_Intro)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})

# copy image files into build folder as the input files
file(GLOB_RECURSE IMAGE_FILES "*.jpg" "*.png" "*.avi" "*.yaml")
# install(FILES ${IMAGE_FILES} DESTINATION ${CMAKE_BINARY_DIR}) # need to launch INSTALL target
file(COPY ${IMAGE_FILES} DESTINATION ${CMAKE_BINARY_DIR})

function(add_sub_directory_executables folder)
  message("Processing folder: " ${folder})
  file(GLOB ALL_SUB RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/${folder} ${folder}/*)
  SET(dirlist "")
  foreach(sub ${ALL_SUB})
    if (IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${folder}/${sub})  # absolute path
      message("add executable: " ${sub})
      LIST(APPEND dirlist ${sub})
      file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/${folder}/${sub}/*.cpp")
      # message(${SOURCE_FILES})
      add_executable(${sub} ${SOURCE_FILES})
      target_link_libraries(${sub} ${OpenCV_LIBS})
    endif()
  endforeach()
  set_property(TARGET ${dirlist} PROPERTY FOLDER ${folder})
endfunction()

# add_subdirectory(chapter2)  # use the above function instead of the sub cmake file
add_sub_directory_executables(chapter2)
add_sub_directory_executables(chapter3)
add_sub_directory_executables(chapter4)
add_sub_directory_executables(chapter5)
add_sub_directory_executables(chapter6)
add_sub_directory_executables(chapter7)
add_sub_directory_executables(chapter8)
add_sub_directory_executables(chapter9)
add_sub_directory_executables(chapter10)
add_sub_directory_executables(others)
