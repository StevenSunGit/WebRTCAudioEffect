#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include "inc/com_feifei_webrtcaudioeffect_jni_AudioEffect.h.h"
#include <jni.h>
#ifndef nullptr
#define nullptr 0
#endif

#ifndef MIN
#define  MIN(A, B)        ((A) < (B) ? (A) : (B))
#endif

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcCreate(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcSetConfig(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcInit(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcProcess(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcFree(JNIEnv *env, jobject thiz) {
    return 0;
}