cmake_minimum_required(VERSION 2.8)

project(ihm)
SET(PROJECT_NAME ihm)

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR})
LINK_DIRECTORIES (${QT_LIBRARIES})
ADD_DEFINITIONS(${QT_DEFINITIONS})

include_directories(include)
#link_directories(include)

#include_directories(${CMAKE_SOURCE_DIR}/../qextserialport/src)
#link_directories(${CMAKE_SOURCE_DIR}/../qextserialport/src)

include_directories(${CMAKE_SOURCE_DIR}/../Plotter/include)
link_directories(${CMAKE_SOURCE_DIR}/../Plotter/include)



#${CMAKE_SOURCE_DIR}/../Plotter/src/Plotter.cpp


# MOCing process 
SET(PROJECT_MOC_CLASSES 
${CMAKE_SOURCE_DIR}/include/Plotter.h
${CMAKE_SOURCE_DIR}/include/MainWindow.h
)
QT4_WRAP_CPP(PROJECT_MOC_SOURCES  ${PROJECT_MOC_CLASSES})
SOURCE_GROUP(moc FILES ${PROJECT_MOC_SOURCES}) 


add_executable(
${PROJECT_NAME}
${CMAKE_SOURCE_DIR}/src/main.cpp
${CMAKE_SOURCE_DIR}/src/MainWindow.cpp
${CMAKE_SOURCE_DIR}/include/MainWindow.h
${CMAKE_SOURCE_DIR}/src/Plotter.cpp
${CMAKE_SOURCE_DIR}/include/Plotter.h
${PROJECT_MOC_SOURCES}
)


target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin/)
