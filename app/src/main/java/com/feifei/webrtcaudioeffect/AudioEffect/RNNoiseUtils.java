package com.feifei.webrtcaudioeffect.AudioEffect;

public class RNNoiseUtils {
    static {
        System.loadLibrary("rnnoise");
    }

    public static int get10msBufferSizeInFloat(int frequency){
        return 10 * frequency / 1000;
    }

    public native long rnnoiseCreate();
    public native int rnnoiseProcessFrame(long sts, float[] outPutBuffers, float[] inputBuffer);
    public native void rnnoiseDestroy(long sts);
}
