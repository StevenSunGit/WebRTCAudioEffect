package com.feifei.webrtcaudioeffect.AudioEffect;

public class RNNoiseUtils {
    static {
        System.loadLibrary("rnnoise");
    }

    public static int get20msBufferSize(int frequency){
        return 40 * frequency / 1000;
    }

    public native long rnnoiseCreate();
    public native int rnnoiseProcessFrame(long sts, short[] buffers, int size);
    public native void rnnoiseDestroy(long sts);
}
