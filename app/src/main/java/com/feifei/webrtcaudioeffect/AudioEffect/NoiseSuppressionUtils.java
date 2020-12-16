package com.feifei.webrtcaudioeffect.AudioEffect;

public class NoiseSuppressionUtils {
    /* 加载消噪库 */
    static {
        System.loadLibrary("webrtc-noise-suppression");
    }

    public static int getMinBufferSize(int frequency){
        return 10 * frequency / 1000;
    }

    public native long nsCreate();

    public native int nsInit(long nsHandler, int frequency);

    public native int nsSetPolicy(long nsHandler, int mode);

    public native int nsProcess(long nsHandler, short[] inputData, int num_bands, short[] outputData);

    public native int nsFree(long nsHandler);
}
