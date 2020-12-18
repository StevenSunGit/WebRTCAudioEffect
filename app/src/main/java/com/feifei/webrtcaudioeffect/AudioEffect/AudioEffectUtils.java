package com.feifei.webrtcaudioeffect.AudioEffect;

public class AudioEffectUtils {
    public static int get10msBufferSizeInByte(int frequency, int channels){
        return 10 * frequency / 1000 * channels;
    }
}
