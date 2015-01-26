LOCAL_PATH:= $(call my-dir)
 
include $(CLEAR_VARS)
 
LOCAL_MODULE := libgain

LOCAL_SRC_FILES :=  GainApp.cpp\
					Core.cpp\
					Base.cpp\
					Layer.cpp\
					EffectLayer.cpp\
					Menu.cpp\
					Button.cpp\
					Rect.cpp\
					ShaderTest.cpp\
					PixelCanvas.cpp\
					Bitmap.cpp\
					ImageBitmap.cpp\
					FboBitmap.cpp\
					Text.cpp\
					TouchInterface.cpp \
					EventListener.cpp \
					Logger.cpp \
					PerfomanceCounter.cpp \
					PerfCounterItem.cpp \
					Settings.cpp
					
LOCAL_C_INCLUDES := gain/freetype/include \
                    gain/freetype/include/freetype2 \
                    gain

LOCAL_LDLIBS    := -llog -lGLESv2 -landroid -lEGL -lz  

LOCAL_STATIC_LIBRARIES := freetype

include $(BUILD_SHARED_LIBRARY)
 
$(call import-add-path, gain ) 
$(call import-module , freetype )
 
