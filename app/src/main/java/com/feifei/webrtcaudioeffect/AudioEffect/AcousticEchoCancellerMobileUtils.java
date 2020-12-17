package com.feifei.webrtcaudioeffect.AudioEffect;

public class AcousticEchoCancellerMobileUtils {
    static {
        System.loadLibrary("acoustic-echo-cancellion-mobile");
    }

    public native long aecmCreate();
    public native int aecmInit();
    public native int aecmSetConfig();
    public native int aecmProcess();
    public native void aecmFree();
}
