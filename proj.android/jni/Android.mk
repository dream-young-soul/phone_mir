LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/HelloWorldScene.cpp \
				   ../../Classes/Common/Grobal2.cpp \
				   ../../Classes/Common/IconvString.cpp \
				   ../../Classes/Common/VDImageDatas.cpp \
				   ../../Classes/Common/ZipUnit.cpp \
				   ../../Classes/Common/SoundUtil.cpp \
				   ../../Classes/Net/EnDecode.cpp \
				   ../../Classes/Net/NetClient.cpp \
				   ../../Classes/Net/NetRecvMsg.cpp \
				   ../../Classes/Net/NetSendMsg.cpp \
				   ../../Classes/Net/TcpSocket.cpp \
				   ../../Classes/UI/UIManager.cpp \
				   ../../Classes/UI/UIBase.cpp \
				   ../../Classes/UI/NpcDialog.cpp \
				   ../../Classes/UI/JoyStick.cpp \
				   ../../Classes/UI/BaseDialog.cpp \
				   ../../Classes/UI/MyStatePan.cpp \
				   ../../Classes/UI/ShortcutsDialog.cpp \
				   ../../Classes/UI/RoleStateDialog.cpp \
				   ../../Classes/UI/BagDialog.cpp \
				   ../../Classes/UI/HitDialog.cpp \
				   ../../Classes/UI/MagicDialog.cpp \
				   ../../Classes/UI/MapMiniTitle.cpp \
				   ../../Classes/UI/MiniTaskPan.cpp \
				   ../../Classes/UI/JoyVirtualKey.cpp \
				   ../../Classes/Actor.cpp \
				   ../../Classes/FileStream.cpp \
				   ../../Classes/FrmMain.cpp \
				   ../../Classes/GameStruct.cpp \
				   ../../Classes/MapUnit.cpp \
				   ../../Classes/MShare.cpp \
				   ../../Classes/PlayScene.cpp \
				   ../../Classes/VD_Share.cpp \
				   ../../Classes/VDImage.cpp \
				   ../../Classes/MagicEff.cpp \
				   ../../Classes/BaseConfig.cpp \
				   ../../Classes/clEvent.cpp \
				   ../../Classes/DScreen.cpp \
				   ../../Classes/PathHelper.cpp \
				   ../../Classes/GuaJiHelper.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../cocos2d/iconv/include \
					$(LOCAL_PATH)/../../cocos2d/iconv/libcharset  \
					$(LOCAL_PATH)/../../cocos2d/iconv/lib  \
					$(LOCAL_PATH)/../../cocos2d/iconv/libcharset/include  \
					$(LOCAL_PATH)/../../cocos2d/iconv/srclib  \
					$(LOCAL_PATH)/../../cocos2d/iconv

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += libiconv
# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,iconv)
# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
