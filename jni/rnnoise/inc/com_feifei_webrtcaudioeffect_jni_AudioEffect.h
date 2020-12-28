#ifndef WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H
#define WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <android/log.h>
/* 日志输出 */
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE,"sunyunfei", __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG,"sunyunfei",__VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO,"sunyunfei", __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN,"sunyunfei", __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR,"sunyunfei",__VA_ARGS__)

JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_RNNoiseUtils_rnnoiseCreate(JNIEnv *env, jobject thiz);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_RNNoiseUtils_rnnoiseProcessFrame(JNIEnv *env,jobject thiz, jlong sts, jfloatArray buffers);

JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_RNNoiseUtils_rnnoiseDestroy(JNIEnv *env,jobject thiz, jlong sts);

#ifdef __cplusplus
}
#endif

#endif //WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H
