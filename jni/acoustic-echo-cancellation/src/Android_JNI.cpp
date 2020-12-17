#include "com_android_aec_util_WebRtcUtil.h"
#include <stdint.h>
#include <time.h>
#include <pthread.h>
#include <android/log.h>
#include <string.h>
#include <audio_aec.h>

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecCreate(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT int JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecProcess(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecFree(JNIEnv *env, jobject thiz) {
    ;
}
