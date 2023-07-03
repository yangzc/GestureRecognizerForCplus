#!bin/sh
project="/Users/yangzc/devsoft/project/cplus/GestureRecognizer"

function copyHeader() {
	for file in `ls $1`; do
		if [ -d $1"/"$file ]
		then
			copyHeader $1"/"$file
		fi
	done
	cp $1/*.h $project/android-armv7/include/recognizer/
}


rm -rf android-armv7
mkdir android-armv7
cd android-armv7
mkdir $project/android-armv7/include
mkdir $project/android-armv7/include/recognizer

cmake -DCMAKE_TOOLCHAIN_FILE=/Users/yangzc/devsoft/MDK/ndk-bundle/build/cmake/android.toolchain.cmake  \
    -DANDROID_ABI="armeabi-v7a" -DANDROID_ARM_NEON=ON \
    -DANDROID_PLATFORM=android-14 ../GestureRecognizer
make -j4

echo $project
copyHeader $project/GestureRecognizer/bitmap
copyHeader $project/GestureRecognizer/json
copyHeader $project/GestureRecognizer/recognizer

cp -r $project/ncnn-android-lib/ncnn/ ./include/ncnn