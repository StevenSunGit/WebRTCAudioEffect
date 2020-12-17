#ifndef WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H
#define WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcCreate(JNIEnv *env, jobject thiz);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcInit(JNIEnv *env, jobject thiz, jlong agcID, jint agcMode, jint sampleRate);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcSetConfig(JNIEnv *env, jobject thiz, jlong agcID, jint gaindB, jint leveldB);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcProcess(JNIEnv *env, jobject thiz, jlong agcID, jshortArray inputBuffer, int numbands, int sampleRate ,jshortArray outBuffer);

JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AutomaticGainControl_agcFree(JNIEnv *env, jobject thiz, jlong agcID);

#ifdef __cplusplus
}
#endif

#endif //WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H