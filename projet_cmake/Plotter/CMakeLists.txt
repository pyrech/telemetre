PROJECT(PlotterProject)

#=============================================
SET(PROJECT_NAME Plotter)
#===================================================================================================
# For Qt4 usage 

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR})
LINK_DIRECTORIES (${QT_LIBRARIES})
ADD_DEFINITIONS(${QT_DEFINITIONS})
#C++ Project Include
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include) 
#===================================================================================================
# console suppression for windows based applications
IF(WIN32)
LINK_LIBRARIES(${QT_QTMAIN_LIBRARY})
#ADD_DEFINITIONS (-DQT_DLL)
ENDIF (WIN32)
#===================================================================================================
#Project libraries
LINK_DIRECTORIES (${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/lib)
#===================================================================================================
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin)
#===================================================================================================
SET(PROJECT_SOURCES 
#project source
${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/src/main.cpp
${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/src/Plotter.cpp

#project headers
${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include/Plotter.h
) 
# MOCing process 
SET(PROJECT_MOC_CLASSES 
${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include/Plotter.h
)
QT4_WRAP_CPP(PROJECT_MOC_SOURCES  ${PROJECT_MOC_CLASSES})
SOURCE_GROUP(moc FILES ${PROJECT_MOC_SOURCES}) 
#===================================================================================================
# Compilation and installation

IF(WIN32)
ADD_EXECUTABLE(PlotterProject WIN32  ${PROJECT_SOURCES} ${PROJECT_MOC_SOURCES})
TARGET_LINK_LIBRARIES(PlotterProject 
${QT_LIBRARIES} odbc32 odbccp32
)
ENDIF (WIN32)

IF (UNIX)
ADD_EXECUTABLE(PlotterProject WIN32  ${PROJECT_SOURCES} ${PROJECT_MOC_SOURCES})
TARGET_LINK_LIBRARIES(PlotterProject 
${QT_LIBRARIES}
)
ENDIF (UNIX)

#===================================================================================================
SET_TARGET_PROPERTIES(PlotterProject PROPERTIES DEBUG_POSTFIX "_d" )
INSTALL(TARGETS PlotterProject RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/bin )