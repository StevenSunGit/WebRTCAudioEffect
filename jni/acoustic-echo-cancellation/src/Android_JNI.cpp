#include "com_feifei_webrtcaudioeffect_jni_AudioEffect.h"
#include "echo_cancellation.h"
#include <android/log.h>
#include <string.h>

/* 日志输出 */
#define LOG_TAG "jni_NoiseSuppressionNative"
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecCreate(JNIEnv *env, jobject thiz) {
    void* aecID = webrtc::WebRtcAec_Create();
    return (jlong)aecID;
}

extern "C" JNIEXPORT int JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecInit(JNIEnv *env, jobject thiz, jint aecID, jint sampleRate) {
    return webrtc::WebRtcAec_Init((webrtc::AecCore*)aecID, sampleRate, sampleRate);
}

extern "C" JNIEXPORT int JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecSetConfig(JNIEnv *env, jobject thiz, jint aecID, jint mode) {
    webrtc::AecConfig aecConfig;
    aecConfig.metricsMode = mode;
    aecConfig.skewMode = webrtc::kAecTrue;
    aecConfig.metricsMode = webrtc::kAecTrue;

    int status = webrtc::WebRtcAec_set_config((void*)aecID, aecConfig);
    if (status != 0) {
        ALOGE("WebRtcAecm_set_config fail\n");
        webrtc::WebRtcAec_Free((void*)aecID);
        return -1;
    }
    return status;
}

extern "C" JNIEXPORT int JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecProcess(JNIEnv *env, jobject thiz, jlong aecID, jfloatArray nearInput, jfloatArray farInput, jfloatArray output) {
    int16_t msInSndCardBuf = 40;
    jfloat *nearBuffer = env->GetFloatArrayElements(nearInput, nullptr);
    jfloat *farBuffer = env->GetFloatArrayElements(farInput, nullptr);
    jfloat *outputBuffer = env->GetFloatArrayElements(output, nullptr);

    int retFar = webrtc::WebRtcAec_BufferFarend((void*)aecID, farBuffer, 160);
    if(retFar != 0){
        ALOGE("WebRtcAec_BufferFarend() failed.\n");
        webrtc::WebRtcAec_Free((void*)aecID);
        return -1;
    }

    int ret = webrtc::WebRtcAec_Process((void*)aecID, (const float* const*)nearBuffer, 1, (float* const* )outputBuffer, 160, msInSndCardBuf, 0);
    if (ret != 0) {
        ALOGE("failed in WebRtcAecm_Process\n");
        webrtc::WebRtcAec_Free((void*)aecID);
        return -1;
    }

    memcpy(nearBuffer, outputBuffer, 160 * sizeof(int16_t));

    env->ReleaseFloatArrayElements(nearInput, nearBuffer, 0);
    env->ReleaseFloatArrayElements(farInput, farBuffer, 0);
    env->ReleaseFloatArrayElements(output, outputBuffer, 0);

    return 0;
}

extern "C" JNIEXPORT void JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_AcousticEchoCancellationUtils_aecFree(JNIEnv *env, jobject thiz, jlong aecID) {
    webrtc::WebRtcAec_Free((webrtc::AecCore*)aecID);
}
