cmake_minimum_required(VERSION 2.8)

project(ihm)
SET(PROJECT_NAME ihm)
SET(NIDAQ_INCLUDE_DIR "C:\\Program Files (x86)\\National Instruments\\NI-DAQ\\DAQmx ANSI C Dev")

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
INCLUDE_DIRECTORIES(
${QT_INCLUDE_DIR}
"C:\\Program Files (x86)\\National Instruments\\NI-DAQ\\DAQmx ANSI C Dev\\include"
)
LINK_DIRECTORIES (
${QT_LIBRARIES}
"C:\\Program Files (x86)\\National Instruments\\NI-DAQ\\DAQmx ANSI C Dev\\msvc"
)
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
${CMAKE_SOURCE_DIR}/include/Acquisitor.h
)
QT4_WRAP_CPP(PROJECT_MOC_SOURCES  ${PROJECT_MOC_CLASSES})
SOURCE_GROUP(moc FILES ${PROJECT_MOC_SOURCES}) 


add_executable(
${PROJECT_NAME}
${CMAKE_SOURCE_DIR}/src/main.cpp
${CMAKE_SOURCE_DIR}/src/MainWindow.cpp
${CMAKE_SOURCE_DIR}/include/MainWindow.h
${CMAKE_SOURCE_DIR}/src/Calculator.cpp
${CMAKE_SOURCE_DIR}/include/Calculator.h
${CMAKE_SOURCE_DIR}/src/Acquisitor.cpp
${CMAKE_SOURCE_DIR}/include/Acquisitor.h
${CMAKE_SOURCE_DIR}/src/Plotter.cpp
${CMAKE_SOURCE_DIR}/include/Plotter.h
${PROJECT_MOC_SOURCES}
)


IF (WIN32)
target_link_libraries(
${PROJECT_NAME}
${QT_LIBRARIES}
NIDAQmx
)
ENDIF (WIN32)

IF (UNIX)
target_link_libraries(
${PROJECT_NAME}
${QT_LIBRARIES}
)
ENDIF (UNIX)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/bin/)
