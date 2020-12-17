#ifndef WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H
#define WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_NoiseSuppressionUtils_nsCreate(JNIEnv *env, jobject thiz);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_NoiseSuppressionUtils_nsInit(JNIEnv *env, jobject thiz, jlong nsHandler, jint frequency);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_NoiseSuppressionUtils_nsSetPolicy(JNIEnv *env,jobject thiz, jlong ns_handler, jint mode);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_NoiseSuppressionUtils_nsProcess(JNIEnv *env, jobject thiz, jlong nsHandler, jshortArray spframe, jint num_bands, jshortArray outframe);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_NoiseSuppressionUtils_nsFree(JNIEnv *env, jobject thiz, jlong nsHandler);

#ifdef __cplusplus
}
#endif

#endif //WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H