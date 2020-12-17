#include "com_feifei_webrtcaudioeffect_jni_AudioEffect.h"
#include "echo_cancellation.h"

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecCreate(JNIEnv *env, jobject thiz) {
    void* aecID = webrtc::WebRtcAec_Create();
    return (jlong)aecID;
}

extern "C" JNIEXPORT int JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecInit(JNIEnv *env, jobject thiz, jint aecID, jint sampleRate) {
    return webrtc::WebRtcAec_Init((webrtc::AecCore*)aecID, sampleRate, sampleRate);
}

extern "C" JNIEXPORT int JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecProcess(JNIEnv *env, jobject thiz) {
    return 0;
}

extern "C" JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecFree(JNIEnv *env, jobject thiz, jlong aecID) {
    webrtc::WebRtcAec_Free((webrtc::AecCore*)aecID);
}
