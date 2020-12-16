#include <jni.h>
#include <android/log.h>
#include "com_feifei_webrtcnoisesuppression_jni_NoiseSuppressionEngine.h"
#include "noise_suppression.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef nullptr
#define nullptr 0
#endif

/* 日志输出 */
#define LOG_TAG "jni_NoiseSuppressionNative"
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcnoisesuppression_NoiseSuppressionEngine_NoiseSuppressionUtils_nsCreate(JNIEnv *env, jobject thiz) {
    return (long) WebRtcNs_Create();
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcnoisesuppression_NoiseSuppressionEngine_NoiseSuppressionUtils_nsInit(JNIEnv *env, jobject thiz, jlong nsHandler, jint frequency) {
    NsHandle *handler = (NsHandle *) nsHandler;
    if (handler == nullptr) {
        return -3;
    }
    return WebRtcNs_Init(handler, frequency);
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcnoisesuppression_NoiseSuppressionEngine_NoiseSuppressionUtils_nsSetPolicy(JNIEnv *env,jobject thiz, jlong nsHandler, jint mode) {
    NsHandle *handle = (NsHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    return WebRtcNs_set_policy(handle, mode);
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcnoisesuppression_NoiseSuppressionEngine_NoiseSuppressionUtils_nsProcess(JNIEnv *env, jobject thiz, jlong nsHandler, jshortArray spframe, jint num_bands, jshortArray outframe) {
    NsHandle *handle = (NsHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    jshort *cspframe = env->GetShortArrayElements(spframe, nullptr);
    jshort *coutframe = env->GetShortArrayElements(outframe, nullptr);

    WebRtcNs_Analyze(handle, &cspframe[0]);
    WebRtcNs_Process(handle, &cspframe, num_bands, &coutframe);

    env->ReleaseShortArrayElements(spframe, cspframe, 0);
    env->ReleaseShortArrayElements(outframe, coutframe, 0);
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcnoisesuppression_NoiseSuppressionEngine_NoiseSuppressionUtils_nsFree(JNIEnv *env, jobject thiz, jlong nsHandler) {
    NsHandle *handle = (NsHandle *) nsHandler;
    if (handle == nullptr) {
        return -3;
    }
    WebRtcNs_Free(handle);
    return 0;
}