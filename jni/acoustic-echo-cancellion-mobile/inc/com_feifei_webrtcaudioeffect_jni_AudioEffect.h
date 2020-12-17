#ifndef WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H
#define WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmCreate(JNIEnv *env, jobject thiz);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmInit(JNIEnv *env, jobject thiz, jlong aecmID, jint sampleRate);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmSetConfig(JNIEnv *env,jobject thiz, jlong aecmID, jint mode);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmProcess(JNIEnv *env, jobject thiz, jlong aecmID, jshortArray nearInput, jshortArray farInput, jshortArray output);

JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellerMobileUtils_aecmFree(JNIEnv *env, jobject thiz, jlong aecmID);

#ifdef __cplusplus
}
#endif

#endif //WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H