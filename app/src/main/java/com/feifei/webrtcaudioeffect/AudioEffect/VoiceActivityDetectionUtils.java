package com.feifei.webrtcaudioeffect.AudioEffect;

public class VoiceActivityDetectionUtils {
    static {
        System.loadLibrary("voice-activity-detection");
    }

    public native long vadCreate();
    public native int vadInit(long vadID);
    public native int vadSetMode(long vadID, int mode);
    public native int vadProcess(long vadID, int sampleRate, short[] buffer);
    public native void vadFree(long vadID);
}
