cmake_minimum_required(VERSION 2.8)

PROJECT( ImageSegmentationQualityEvaluator )

# Set up ITK
FIND_PACKAGE(ITK REQUIRED)
INCLUDE(${ITK_USE_FILE})

set(Boost_USE_STATIC_LIBS    ON)
set(Boost_USE_MULTITHREADED  ON)
set(Boost_USE_STATIC_RUNTIME ON)
find_package(Boost COMPONENTS system filesystem regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

FIND_PACKAGE(YamlCpp REQUIRED)
INCLUDE_DIRECTORIES(${YAML_CPP_INCLUDE_DIRS})

IF (USE_ITK_FILE)
	INCLUDE(${USE_ITK_FILE})
ENDIF(USE_ITK_FILE)

LINK_DIRECTORIES(${ITK_LIBRARY_PATH})

ADD_EXECUTABLE(HausdorffDistanceComputer HausdorffDistanceComputer.cxx)
TARGET_LINK_LIBRARIES(HausdorffDistanceComputer ${ITK_LIBRARIES} ${YAML_CPP_LIBRARIES} ${Boost_LIBRARIES})

add_executable(LabelOverlapComputer LabelOverlapComputer.cxx)
target_link_libraries(LabelOverlapComputer ${ITK_LIBRARIES} ${YAML_CPP_LIBRARIES} ${Boost_LIBRARIES})
