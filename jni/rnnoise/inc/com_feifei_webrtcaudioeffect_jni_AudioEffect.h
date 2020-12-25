#ifndef WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H
#define WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H

#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_RNNoiseUtils_rnnoiseCreate(JNIEnv *env, jobject thiz);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_RNNoiseUtils_rnnoiseProcessFrame(JNIEnv *env,jobject thiz, jlong sts, jfloatArray outputBuffers, jfloatArray inputBuffers);

JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_RNNoiseUtils_rnnoiseDestroy(JNIEnv *env,jobject thiz, jlong sts);

#ifdef __cplusplus
}
#endif

#endif //WEBRTCAUDIOEFFECT_COM_FEIFEI_WEBRTCAUDIOEFFECT_JNI_AUDIOEFFECT_H
