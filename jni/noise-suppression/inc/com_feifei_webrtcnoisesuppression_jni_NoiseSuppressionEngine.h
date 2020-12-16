#include <jni.h>
#ifndef WEBRTC_NS_COM_EXAMPLE_WEBRTC_NS_NOISESUPPRESSION_H
#define WEBRTC_NS_COM_EXAMPLE_WEBRTC_NS_NOISESUPPRESSION_H

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jlong JNICALL Java_com_feifei_webrtcnoisesuppression_NoiseSuppressionEngine_NoiseSuppressionUtils_nsCreate(JNIEnv *env, jobject thiz);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcnoisesuppression_NoiseSuppressionEngine_NoiseSuppressionUtils_nsInit(JNIEnv *env, jobject thiz, jlong nsHandler, jint frequency);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcnoisesuppression_NoiseSuppressionEngine_NoiseSuppressionUtils_nsSetPolicy(JNIEnv *env,jobject thiz, jlong ns_handler, jint mode);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcnoisesuppression_NoiseSuppressionEngine_NoiseSuppressionUtils_nsProcess(JNIEnv *env, jobject thiz, jlong nsHandler, jshortArray spframe, jint num_bands, jshortArray outframe);

JNIEXPORT jint JNICALL Java_com_feifei_webrtcnoisesuppression_NoiseSuppressionEngine_NoiseSuppressionUtils_nsFree(JNIEnv *env, jobject thiz, jlong nsHandler);

#ifdef __cplusplus
}
#endif

#endif