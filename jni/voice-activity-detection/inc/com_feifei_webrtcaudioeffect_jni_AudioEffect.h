#ifndef WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H
#define WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_VoiceActivityDetectionUtils_vadCreate(JNIEnv *env, jobject thiz);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_VoiceActivityDetectionUtils_vadInit(JNIEnv *env, jobject thiz, jlong vadID);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_VoiceActivityDetectionUtils_vadSetMode(JNIEnv *env, jobject thiz, jlong vadID, jint mode);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_VoiceActivityDetectionUtils_vadProcess(JNIEnv *env, jobject thiz, jlong vadID, jint sampleRate, jshortArray buffer);

JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_VoiceActivityDetectionUtils_vadFree(JNIEnv *env, jobject thiz, jlong vadID)

#ifdef __cplusplus
}
#endif