#ifndef WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H
#define WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecCreate(JNIEnv *env, jobject thiz);

JNIEXPORT int JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecInit(JNIEnv *env, jobject thiz, jint aecID, jint sampleRate);

JNIEXPORT int JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecSetConfig(JNIEnv *env, jobject thiz, jint aecID, jint sampleRate);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecProcess(JNIEnv *env, jobject thiz);

JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecFree(JNIEnv *env, jobject thiz, jlong aecID);

#ifdef __cplusplus
}
#endif

#endif //WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H
