package com.feifei.webrtcaudioeffect.AudioEffect;

public class AcousticEchoCancellerMobileUtils {
    public native long aecmCreate();
    public native int aecmInit();
    public native int aecmSetConfig();
    public native int aecmProcess();
    public native void aecmFree();
}
