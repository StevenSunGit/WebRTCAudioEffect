#include <android/log.h>
#include "com_feifei_webrtcaudioeffect_jni_AudioEffect.h"
#include "echo_control_mobile.h"
#include <string.h>
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
    return status;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmProcess(JNIEnv *env, jobject thiz, jlong aecmID, jshortArray nearInput, jshortArray farInput, jshortArray output) {
    int16_t msInSndCardBuf = 40;

    jshort *nearBuffer = env->GetShortArrayElements(nearInput, nullptr);
    jshort *farBuffer = env->GetShortArrayElements(farInput, nullptr);
    jshort *outputBuffer = env->GetShortArrayElements(output, nullptr);

    int retFar = WebRtcAecm_BufferFarend((void*)aecmID, farBuffer, 160);
    if(retFar != 0){
        ALOGE("WebRtcAecm_BufferFarend() failed.\n");
    }

    int nRet = WebRtcAecm_Process((void*)aecmID, nearBuffer, NULL, outputBuffer, 160, msInSndCardBuf);
    if (nRet != 0) {
        ALOGE("failed in WebRtcAecm_Process\n");
        WebRtcAecm_Free((void*)aecmID);
        return -1;
    }

    memcpy(nearBuffer, outputBuffer, 160 * sizeof(int16_t));

    env->ReleaseShortArrayElements(nearInput, nearBuffer, 0);
    env->ReleaseShortArrayElements(farInput, farBuffer, 0);
    env->ReleaseShortArrayElements(output, outputBuffer, 0);

    return 0;
}

extern "C" JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmFree(JNIEnv *env, jobject thiz, jlong aecmID) {
    WebRtcAecm_Free((void*)aecmID);
}