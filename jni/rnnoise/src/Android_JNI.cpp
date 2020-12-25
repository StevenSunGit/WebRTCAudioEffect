#include "com_feifei_webrtcaudioeffect_jni_AudioEffect.h"
#include <stdio.h>
#include "rnnoise.h"
#include <stdlib.h>
#include <stdint.h>

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_RNNoiseUtils_rnnoiseCreate(JNIEnv *env, jobject thiz) {
    DenoiseState *sts = rnnoise_create();
    return (jlong)sts;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_RNNoiseUtils_rnnoiseProcessFrame(JNIEnv *env,jobject thiz, jlong sts, jshortArray buffers){
    jshort *buffer = env->GetShortArrayElements(buffers, nullptr);
    rnnoise_process_frame((DenoiseState *)sts, (float* )buffer, (float* )buffer);
    env->ReleaseShortArrayElements(buffers, buffer, 0);
    return 0;
}

extern "C" JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_RNNoiseUtils_rnnoiseDestroy(JNIEnv *env,jobject thiz, jlong sts){
    rnnoise_destroy((DenoiseState *)sts);
}