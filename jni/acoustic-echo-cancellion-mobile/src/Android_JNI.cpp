#include <android/log.h>
#include "com_feifei_webrtcaudioeffect_jni_AudioEffect.h"

/* 日志输出 */
#define LOG_TAG "jni_NoiseSuppressionNative"
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmCreate(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmInit(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmSetConfig(JNIEnv *env,jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmProcess(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmFree(JNIEnv *env, jobject thiz) {
    ;
}