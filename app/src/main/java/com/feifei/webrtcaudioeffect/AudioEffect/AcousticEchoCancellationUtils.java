package com.feifei.webrtcaudioeffect.AudioEffect;

public class AcousticEchoCancellationUtils {
    static {
        System.loadLibrary("acoustic-echo-cancellation");
    }

    public static int get10msBufferSizeInByte(int frequency){
        return 10 * frequency / 1000 * 16 / 8;
    }

    public native long aecCreate();
    public native int aecInit(long aecID, int sampleRate);
    /* mode: kAecNlpConservative = 0, kAecNlpModerate = 1(default), kAecNlpAggressive = 2 */
    public native int aecSetConfig(long aecID, int mode);
    public native int aecProcess(long aecID, float[] nearInput, float[] farInput, float[] output);
    public native void aecFree(long aecID);
}
