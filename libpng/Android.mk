LOCAL_PATH:= $(call my-dir)
 
include $(CLEAR_VARS)
 
LOCAL_MODULE := libpng
LOCAL_SRC_FILES := lib/libpng16.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
 
include $(PREBUILT_STATIC_LIBRARY)
