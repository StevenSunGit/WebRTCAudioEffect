package com.feifei.webrtcaudioeffect.AudioEffect;

public class NoiseSuppressionXUtils {
    static {
        System.loadLibrary("noise-suppression-x");
    }

    public static int get20msBufferSizeInByte(int frequency, int audioFormat){
        return 20 * frequency / 1000 * audioFormat / 8;
    }

    public native long nsxCreate();

    public native int nsxInit(long nsHandler, int frequency);

    public native int nsxSetPolicy(long nsHandler, int mode);

    public native int nsxProcess(long nsHandler, short[] inputData, int num_bands, short[] outputData);

    public native int nsxFree(long nsHandler);
}
