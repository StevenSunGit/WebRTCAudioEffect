#include <android/log.h>
#include "com_feifei_webrtcaudioeffect_jni_AudioEffect.h"
#include "echo_control_mobile.h"

/* 日志输出 */
#define LOG_TAG "jni_NoiseSuppressionNative"
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmCreate(JNIEnv *env, jobject thiz) {
    void *aecmInst = WebRtcAecm_Create();
    return (jlong)aecmInst;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmInit(JNIEnv *env, jobject thiz, jlong aecmID, jint sampleRate) {
    int status = WebRtcAecm_Init((void*)aecmID, sampleRate);//8000 or 16000 Sample rate
    if (status != 0) {
        ALOGE("WebRtcAecm_Init fail\n");
        WebRtcAecm_Free((void*)aecmID);
        return -1;
    }
    return status;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmSetConfig(JNIEnv *env,jobject thiz, jlong aecmID, jint mode) {
    AecmConfig config;
    config.cngMode = AecmTrue;
    config.echoMode = mode;
    int status = WebRtcAecm_set_config((void*)aecmID, config);
    if (status != 0) {
        ALOGE("WebRtcAecm_set_config fail\n");
        WebRtcAecm_Free((void*)aecmID);
        return -1;
    }
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmProcess(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmFree(JNIEnv *env, jobject thiz, jlong aecmID) {
    WebRtcAecm_Free((void*)aecmID);
}