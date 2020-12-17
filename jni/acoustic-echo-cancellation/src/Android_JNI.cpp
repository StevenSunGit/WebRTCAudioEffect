#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <android/log.h>
#include <string.h>
#include "audio_aec.h"

#include "com_feifei_webrtcaudioeffect_jni_AudioEffect.h"

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecCreate(JNIEnv *env, jobject thiz, jint sampleRate) {
    void* handle = audio_process_aec_create(sampleRate);
    return (jlong)handle;
}

extern "C" JNIEXPORT int JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecProcess(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecFree(JNIEnv *env, jobject thiz, jlong aecID) {
    audio_process_aec_free((void*)aecID);
}
