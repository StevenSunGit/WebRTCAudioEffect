#include <iostream>
#include <memory>
#include <cassert>
#include "webrtc_vad.hpp"
#include <jni.h>
//#include "com_feifei_webrtcaudioeffect_jni_AudioEffect.h"

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_VoiceActivityDetectionUtils_vadCreate(JNIEnv *env, jobject thiz) {
    VadInst* vad = WebRtcVad_Create();
    return (jlong)vad;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_VoiceActivityDetectionUtils_vadInit(JNIEnv *env, jobject thiz, jlong vadID) {
    return WebRtcVad_Init((VadInst*)vadID);
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_VoiceActivityDetectionUtils_vadSetMode(JNIEnv *env, jobject thiz, jlong vadID, jint mode) {
    return WebRtcVad_set_mode((VadInst*)vadID, mode);
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_VoiceActivityDetectionUtils_vadProcess(JNIEnv *env, jobject thiz, jlong vadID, jint sampleRate, jshortArray buffer) {
    auto pArray = env->GetShortArrayElements(buffer, nullptr);
    auto size = env->GetArrayLength(buffer);
    return WebRtcVad_Process((VadInst*)vadID, 16000, pArray, size);
}

extern "C" JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_VoiceActivityDetectionUtils_vadFree(JNIEnv *env, jobject thiz, jlong vadID) {
    WebRtcVad_Free((VadInst*)vadID);
}