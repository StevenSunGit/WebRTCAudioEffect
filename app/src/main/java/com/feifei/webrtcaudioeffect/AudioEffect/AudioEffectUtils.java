package com.feifei.webrtcaudioeffect.AudioEffect;

public class AudioEffectUtils {
    public static int get10msBufferSizeInByte(int frequency){
        return 10 * frequency / 1000 * 2;
    }
}
