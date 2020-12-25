package com.feifei.webrtcaudioeffect.AudioEffect;

public class RNNoiseUtils {
    static {
        System.loadLibrary("rnnoise");
    }

    public static int get30msBufferSizeInFloat(int frequency){
        return 30 * frequency / 1000;
    }

    public native long rnnoiseCreate();
    public native int rnnoiseProcessFrame(long sts, short[] buffers, int size);
    public native void rnnoiseDestroy(long sts);
}
