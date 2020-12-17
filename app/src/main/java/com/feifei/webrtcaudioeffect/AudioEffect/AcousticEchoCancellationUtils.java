package com.feifei.webrtcaudioeffect.AudioEffect;

public class AcousticEchoCancellationUtils {
    static {
        System.loadLibrary("acoustic-echo-cancellation");
    }

    public native long aecCreate();
    public native int aecProcess();
    public native void aecFree();
}
