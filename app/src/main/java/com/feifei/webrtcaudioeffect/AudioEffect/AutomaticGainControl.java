package com.feifei.webrtcaudioeffect.AudioEffect;

public class AutomaticGainControl {
    public native long agcCreate();
    /*agc模式：
      0 = kAgcModeUnchanged,
      1 = kAgcModeAdaptiveAnalog,
      2 = kAgcModeAdaptiveDigital,
      3 = kAgcModeFixedDigital
     */
    public native int agcInit(long agcID, int agcMode, int sampleRate);
    public native int agcSetConfig(long agcID, int gaindB, int leveldB);
    public native int agcProcess(long agcID, short[] inputBuffer, int numBands, int sampleRate ,short[] outputBuffer);
    public native void agcFree(long agcID);
}
