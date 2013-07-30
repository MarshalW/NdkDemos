LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

OPENCV_LIB_TYPE:=STATIC
include /opt/OpenCV-2.4.6-android-sdk/sdk/native/jni/OpenCV.mk

LOCAL_MODULE    := FeatureDetect 
LOCAL_SRC_FILES := FeatureDetect.cpp

APP_STL:=stlport_static

include $(BUILD_SHARED_LIBRARY)