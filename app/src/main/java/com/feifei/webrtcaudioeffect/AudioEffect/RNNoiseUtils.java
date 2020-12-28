package com.feifei.webrtcaudioeffect.AudioEffect;

public class RNNoiseUtils {
    static {
        System.loadLibrary("rnnoise");
    }

    public static int get20msBufferSize(int frequency, int audioFramet){
        return 10 * frequency / 1000 * audioFramet / 8;
    }

    public native long rnnoiseCreate();
    public native int rnnoiseProcessFrame(long sts, short[] buffers, int size);
    public native void rnnoiseDestroy(long sts);
}
