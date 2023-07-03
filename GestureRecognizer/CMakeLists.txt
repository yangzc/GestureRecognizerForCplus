# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

#添加子目录
option(ANDROID "isAndroid" ON)
add_library( # Sets the name of the library.
             register

             # Sets the library as a shared library.
             STATIC

             # Provides a relative path to your source file(s).
             json/json_reader.cpp
             json/json_value.cpp
             json/json_writer.cpp

             bitmap/bitmap_image.hpp

             recognizer/common_type.cpp
             recognizer/recognizer.cpp
             recognizer/gesture_utils.cpp
             recognizer/utils.cpp
             recognizer/gesture.cpp
             recognizer/polyline.cpp
             recognizer/classification/classification.cpp
             recognizer/classification/gesture_classification.cpp
             recognizer/classification/ncnn_classification.cpp
             recognizer/reducer/reducer.cpp
             recognizer/reducer/douglaspeukcer_reducer.cpp
             recognizer/reducer/distance_reducer.cpp
             recognizer/matcher/matcher.cpp
             recognizer/matcher/distance_matcher.cpp
             recognizer/template/template_manager.cpp
             recognizer/rule/pair_rule.cpp
             recognizer/rule/gesture_pair_rule.cpp
             recognizer/rule/ncnn_pair_rule.cpp
             recognizer/template/parser/template_parser.cpp
             recognizer/template/parser/template_parser_json.cpp
             recognizer/reducer/vector_reducer.cpp
             recognizer/matcher/vector_matcher.cpp
             )

# Specifies a path to native header files
include_directories(/)
include_directories(json/)
include_directories(bitmap/)
include_directories(recognizer/)
include_directories(recognizer/classification/)
include_directories(recognizer/reducer/)
include_directories(recognizer/matcher/)
include_directories(recognizer/template/)
include_directories(recognizer/rule/)
include_directories(recognizer/template/parser/)
include_directories(recognizer/template/reducer/)


target_include_directories(register PRIVATE ${CMAKE_SOURCE_DIR}/ncnn)

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

find_library( # Sets the name of the path variable.
              z-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              z )

set(LIB_NCNN_DIR /Users/yangzc/devsoft/project/cplus/GestureRecognizer/ncnn-android-lib)
add_library(ncnn STATIC IMPORTED)
set_target_properties(ncnn PROPERTIES IMPORTED_LOCATION ${LIB_NCNN_DIR}/${ANDROID_ABI}/libncnn.a)
include_directories(${LIB_NCNN_DIR}/)


# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

add_definitions(-DANDROID)
target_link_libraries( # Specifies the target library.
               register
               ${ncnn}
               # Links the target library to the log library
               # included in the NDK.
               ${z-lib}
               ${log-lib} )

