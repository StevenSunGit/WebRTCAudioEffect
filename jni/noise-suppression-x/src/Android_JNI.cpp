#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "signal_processing_library.h"
#include "noise_suppression_x.h"
#include "noise_suppression.h"
#include "gain_control.h"


#ifndef nullptr
#define nullptr 0
#endif

/* 日志输出 */
#define LOG_TAG "jni_NoiseSuppressionNative"
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG,__VA_ARGS__)
#define ALOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG,__VA_ARGS__)

extern "C" JNIEXPORT jlong JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_NoiseSuppressionXUtils_nsxCreate(JNIEnv *env, jobject thiz) {
    NsxInst_t* nsHandler =WebRtcNsx_Create();
    return (long)nsHandler;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_NoiseSuppressionXUtils_nsxInit(JNIEnv *env, jobject thiz, jlong nsHandler, jint frequency) {
    NsxInst_t *handler = (NsxInst_t *) nsHandler;
    if (handler == nullptr) {
        return -3;
    }
    return WebRtcNsx_Init(handler, frequency);
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_NoiseSuppressionXUtils_nsxSetPolicy(JNIEnv *env,jobject thiz, jlong nsHandler, jint mode) {
    NsxInst_t *handler = (NsxInst_t *) nsHandler;
    return WebRtcNsx_set_policy(handler, mode);
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_NoiseSuppressionXUtils_nsxProcess(JNIEnv *env, jobject thiz, jlong nsHandler, jshortArray spframe, jint numBands, jshortArray outframe) {
    NsxInst_t *handler = (NsxInst_t *) nsHandler;
    jshort *cspframe = env->GetShortArrayElements(spframe, nullptr);
    jshort *coutframe = env->GetShortArrayElements(outframe, nullptr);

    int  filter_state1[6], filter_state12[6];
    int  Synthesis_state1[6], Synthesis_state12[6];

    memset(filter_state1,0,sizeof(filter_state1));
    memset(filter_state12,0,sizeof(filter_state12));
    memset(Synthesis_state1,0,sizeof(Synthesis_state1));
    memset(Synthesis_state12,0,sizeof(Synthesis_state12));

    short shInL[160],shInH[160];
    short shOutL[160] = {0},shOutH[160] = {0};

    //首先需要使用滤波函数将音频数据分高低频，以高频和低频的方式传入降噪函数内部
    WebRtcSpl_AnalysisQMF(cspframe ,320, shInL, shInH,filter_state1,filter_state12);

    //将需要降噪的数据以高频和低频传入对应接口，同时需要注意返回数据也是分高频和低频
    int ret = WebRtcNsx_Process(handler ,shInL  ,shInH ,shOutL , shOutH);

    //如果降噪成功，则根据降噪后高频和低频数据传入滤波接口，然后用将返回的数据写入文件
    WebRtcSpl_SynthesisQMF(shOutL,shOutH,160,coutframe, Synthesis_state1,Synthesis_state12);

    env->ReleaseShortArrayElements(spframe, cspframe, 0);
    env->ReleaseShortArrayElements(outframe, coutframe, 0);
    return ret;
}

extern "C" JNIEXPORT jint JNICALL Java_com_feifei_webrtcaudioeffect_AudioEffect_NoiseSuppressionXUtils_nsxFree(JNIEnv *env, jobject thiz, jlong nsHandler) {
    NsxInst_t *handler = (NsxInst_t *) nsHandler;
    WebRtcNsx_Free(handler);
    return 0;
}