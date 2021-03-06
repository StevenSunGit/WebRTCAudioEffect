package com.feifei.webrtcaudioeffect.AudioEffect;

public class AcousticEchoCancellerMobileUtils {
    static {
        System.loadLibrary("acoustic-echo-cancellion-mobile");
    }

    public static int get10msBufferSizeInByte(int frequency){
        return 10 * frequency / 1000 * 16 / 8;
    }

    public native long aecmCreate();
    public native int aecmInit(long aecmID, int sampleRate);
    /* mode 0,1,2(default),3 */
    public native int aecmSetConfig(long aecmID, int mode);
    public native int aecmProcess(long aecmID, short[] nearInput, short[] farInput, short[] output);
    public native void aecmFree(long aecmID);
}
