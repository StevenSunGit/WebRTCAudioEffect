#include "com_feifei_webrtcaudioeffect_jni_AudioEffect.h"
#include "agc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <android/log.h>

#ifndef nullptr
#define nullptr 0
#endif

/* 日志输出 */
#define LOG_TAG "jni_AutomaticGainControl"
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcCreate(JNIEnv *env, jobject thiz) {
    void *agcInst = WebRtcAgc_Create();
    return (jlong)agcInst;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcInit(JNIEnv *env, jobject thiz, jlong agcID, jint agcMode, jint sampleRate) {
    int minLevel = 0;
    int maxLevel = 255;
    int ret = WebRtcAgc_Init((void*)agcID, minLevel, maxLevel, agcMode, sampleRate);
    if (ret != 0){
        ALOGE("WebRtcAgc_Init fail\n");
        WebRtcAgc_Free((void*)agcID);
        return -1;
    }
    return ret;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcSetConfig(JNIEnv *env, jobject thiz, jlong agcID, jint gaindB, jint leveldB) {
    WebRtcAgcConfig agcConfig;
    agcConfig.compressionGaindB = gaindB; // default 9 dB
    agcConfig.limiterEnable = 1; // default kAgcTrue (on)
    agcConfig.targetLevelDbfs = leveldB; // default 3 (-3 dBOv)

    int status = WebRtcAgc_set_config((void*)agcID, agcConfig);
    if (status != 0) {
        printf("WebRtcAgc_set_config fail\n");
        WebRtcAgc_Free((void*)agcID);
        return -1;
    }
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcProcess(JNIEnv *env, jobject thiz, jlong agcID, jshortArray inputBuffer, int numbands, int sampleRate ,jshortArray outBuffer) {
    int inMicLevel, outMicLevel = -1;
    uint8_t saturationWarning = 1;                 //是否有溢出发生，增益放大以后的最大值超过了65536
    int16_t echo = 0;                                 //增益放大是否考虑回声影响

    jshort *inputData = env->GetShortArrayElements(inputBuffer, nullptr);
    jshort *outputData = env->GetShortArrayElements(outBuffer, nullptr);

    int ret = WebRtcAgc_Process((void*)agcID, (const int16_t *const *) &inputData, numbands, sampleRate,(int16_t *const *) &outputData, inMicLevel, &outMicLevel, echo, &saturationWarning);

    if (ret == 0) {
        env->ReleaseShortArrayElements(inputBuffer, inputData, 0);
        env->ReleaseShortArrayElements(outBuffer, outputData, 0);
    } else{
        printf("failed in WebRtcAgc_Process\n");
        WebRtcAgc_Free((void*)agcID);
    }
    return ret;
}

extern "C" JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcFree(JNIEnv *env, jobject thiz, jlong agcID) {
    WebRtcAgc_Free((void*)agcID);
}