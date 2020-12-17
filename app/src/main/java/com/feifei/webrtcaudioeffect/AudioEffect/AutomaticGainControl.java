package com.feifei.webrtcaudioeffect.AudioEffect;

public class AutomaticGainControl {
    public native long agcCreate();
    public native int agcSetConfig();
    public native int agcInit();
    public native int agcProcess();
    public native void agcFree();
}
