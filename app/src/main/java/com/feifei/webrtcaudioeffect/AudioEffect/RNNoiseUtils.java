package com.feifei.webrtcaudioeffect.AudioEffect;

/*
 RNNoise仅支持采样率48000Hz， 量化位数32bit
 */

public class RNNoiseUtils {
    static {
        System.loadLibrary("rnnoise");
    }

    public static int getMinBufferSize(){
        return 10 * 48000 / 1000 * 32 / 8;
    }

    public native long rnnoiseCreate();
    public native int rnnoiseProcessFrame(long sts, float[] buffers);
    public native void rnnoiseDestroy(long sts);
}
