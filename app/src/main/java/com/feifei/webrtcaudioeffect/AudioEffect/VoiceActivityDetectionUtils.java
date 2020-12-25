package com.feifei.webrtcaudioeffect.AudioEffect;

public class VoiceActivityDetectionUtils {
    static {
        System.loadLibrary("voice-activity-detection");
    }

    public static int get10msBufferSizeInByte(int frequency){
        return 10 * frequency / 1000 * 16 / 8;
    }

    public native long vadCreate();
    public native int vadInit(long vadID);
    public native int vadSetMode(long vadID, int mode);

    /*vad活动判断：
     1 语音活跃
     0 语音不活跃
     -1 错误
     */
    public native int vadProcess(long vadID, int sampleRate, short[] buffer);
    public native void vadFree(long vadID);
}
