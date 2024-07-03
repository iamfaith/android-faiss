# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)
# Set the project name
project (main)

add_definitions(-w)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}   -s  -O3 -DSkip_f2c_Undefs -DNO_LONG_LONG -DNO_BLAS_WRAP")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s  -O3 -DSkip_f2c_Undefs -DNO_LONG_LONG -DNO_BLAS_WRAP")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fopenmp -Doff64_t=__off64_t")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3")

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
# 设置native目录
#set(NATIVE_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp)
set(NATIVE_DIR ${CMAKE_SOURCE_DIR})

#set(clapack_dir ${NATIVE_DIR}/lapack)
# set(LIBS_DIR ${NATIVE_DIR}/libs)

set(EXTRA_DIR ${NATIVE_DIR}/../extra)

set(FAISS_DIR ${NATIVE_DIR}/../faiss)
add_definitions(-D ANDROID_BIT64)

message(STATUS ${FAISS_DIR})
# if ((${ANDROID_ABI} STREQUAL "arm64-v8a") OR (${ANDROID_ABI} STREQUAL "x86_64"))

# else ()
#     set(FAISS_DIR ${NATIVE_DIR}/faiss_32)
#     add_definitions(-D ANDROID_BIT32)
# endif ()


FILE(GLOB EXTRA_FILES
        ${EXTRA_DIR}/clapack/SRC/*.c
        ${EXTRA_DIR}/clapack/SRC/*.cpp
        )
FILE(GLOB FAISS_FILES
        ${FAISS_DIR}/*.cpp
        #add faiss source more
        #${FAISS_DIR}/impl/*.cpp
        #${FAISS_DIR}/utils/*.cpp
        )

include_directories(${FAISS_DIR})

add_library( # Sets the name of the library.
        faiss
        SHARED
        #STATIC
        ${EXTRA_FILES}
        ${FAISS_FILES}
        )

# Add an executable
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries( ${PROJECT_NAME}
    PRIVATE 
    faiss
)


find_package(OpenMP)
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fopenmp")
if (OPENMP_FOUND)
# target_compile_options(${PROJECT_NAME} PRIVATE ${OpenMP_C_FLAGS})
message(STATUS "OPENMP = ${OPENMP}[add openmp C Flag] [${OpenMP_C_FLAGS}]")
target_link_libraries(faiss PRIVATE OpenMP::OpenMP_C)
elseif(OpenMP_CXX_FOUND)
target_compile_options(faiss PRIVATE ${OpenMP_CXX_FLAGS})
message(STATUS "OPENMP = ${OPENMP}[add openmp CXX Flag] ${OpenMP_CXX_FLAGS}")
target_link_libraries(faiss PUBLIC OpenMP::OpenMP_CXX)
else()
message("OpenMP not found")
endif()
# target_link_libraries( # Specifies the target library.
#         faiss
#         omp
#         # Links the target library to the log library
#         # included in the NDK.
#         )