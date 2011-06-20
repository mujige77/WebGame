#!/bin/bash
echo

echo "########### TESTS #############"
echo "Use the following variables when debugging this script; note that they may change on recursions"
echo "BUILD_DIR = $BUILD_DIR"
echo "BUILD_ROOT = $BUILD_ROOT"
echo "CONFIGURATION_BUILD_DIR = $CONFIGURATION_BUILD_DIR"
echo "BUILT_PRODUCTS_DIR = $BUILT_PRODUCTS_DIR"
echo "CONFIGURATION_TEMP_DIR = $CONFIGURATION_TEMP_DIR"
echo "TARGET_BUILD_DIR = $TARGET_BUILD_DIR"
echo "PROJECT_NAME = $PROJECT_NAME"
echo "TARGET_NAME = $TARGET_NAME"
echo "TARGET_NAME = ${EXECUTABLE_NAME}"

SDK_FOLDER="../../../../SDK"
if [ ! -d $SDK_FOLDER ]
then
	mkdir $SDK_FOLDER
fi

SDK_INCLUDE=$SDK_FOLDER"/include"
if [ ! -d $SDK_INCLUDE ]
then
	mkdir $SDK_INCLUDE
fi

SOURCE="cocos2d-x/cocos2dx"
find "$SOURCE" -name "*.h" | cpio -admvp "$SDK_INCLUDE"

#for tval in `find "$SOURCE" -name "*.h"`
#do
#cp -r "$tval" "$SDK_INCLUDE"
#done

SDK_BIN=$SDK_FOLDER"/bin"
if [ ! -d $SDK_BIN ]
then
mkdir $SDK_BIN
fi

SDK_BIN=$SDK_FOLDER"/bin/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME"
if [ ! -d $SDK_BIN ]
then
mkdir $SDK_BIN
fi

cp "$TARGET_BUILD_DIR/$EXECUTABLE_NAME" "$SDK_BIN"

exit 0