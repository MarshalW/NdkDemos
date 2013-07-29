LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := HelloWorld 
LOCAL_SRC_FILES := HelloWorld.cpp

APP_STL:=stlport_static

include $(BUILD_SHARED_LIBRARY)