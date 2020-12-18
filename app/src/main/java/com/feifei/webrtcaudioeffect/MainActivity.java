package com.feifei.webrtcaudioeffect;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.feifei.webrtcaudioeffect.AudioEffect.AcousticEchoCancellationUtils;
import com.feifei.webrtcaudioeffect.AudioEffect.AcousticEchoCancellerMobileUtils;
import com.feifei.webrtcaudioeffect.AudioEffect.AudioEffectUtils;
import com.feifei.webrtcaudioeffect.AudioEffect.AutomaticGainControl;
import com.feifei.webrtcaudioeffect.AudioEffect.NoiseSuppressionUtils;
import com.feifei.webrtcaudioeffect.AudioEffect.VoiceActivityDetectionUtils;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    private static String TAG = "AudioEffect";

    private final int GrantCode = 1;
    private Button nsFileTest, vadFileTest, agcFileTest, aecFileTest, aecmFileTest;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        requestPermissions();
    }

    private void requestPermissions(){
        List<String> permissionList = new ArrayList<>();

        if (checkSelfPermission(Manifest.permission.READ_EXTERNAL_STORAGE)!= PackageManager.PERMISSION_GRANTED){
            permissionList.add(Manifest.permission.READ_EXTERNAL_STORAGE);
        }
        if (checkSelfPermission(Manifest.permission.WRITE_EXTERNAL_STORAGE)!= PackageManager.PERMISSION_GRANTED){
            permissionList.add(Manifest.permission.WRITE_EXTERNAL_STORAGE);
        }
        if (checkSelfPermission(Manifest.permission.RECORD_AUDIO)!= PackageManager.PERMISSION_GRANTED){
            permissionList.add(Manifest.permission.RECORD_AUDIO);
        }

        if (!permissionList.isEmpty()){
            String[] permissions = permissionList.toArray(new String[permissionList.size()]);
            requestPermissions(permissions, GrantCode);
        }else {
            grantPermission();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        switch (requestCode){
            case GrantCode :
                if (grantResults.length > 0){
                    for (int result : grantResults){
                        if (result!=PackageManager.PERMISSION_GRANTED){
                            Log.d(TAG, "必须同意所有权限！");
                            return;
                        }
                    }
                }
                grantPermission();
        }
    }

    private void grantPermission(){
        nsFileTest = (Button)findViewById(R.id.nsFileTest);
        nsFileTest.setOnClickListener(this);

        vadFileTest = (Button)findViewById(R.id.vadFileTest);
        vadFileTest.setOnClickListener(this);

        agcFileTest = (Button)findViewById(R.id.agcFileTest);
        agcFileTest.setOnClickListener(this);

        aecFileTest = (Button)findViewById(R.id.aecFileTest);
        aecFileTest.setOnClickListener(this);

        aecmFileTest = (Button)findViewById(R.id.aecmFileTest);
        aecmFileTest.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        String root = getExternalFilesDir("").getAbsolutePath();
        switch (v.getId()){
            /* 测试噪声抑制对音频文件的效果 */
            case R.id.nsFileTest:
                ExecutorService nsFileTest = Executors.newSingleThreadExecutor();
                nsFileTest.execute(()->{
                    try {
                        /* 消噪前文件夹 */
                        File inFiles = new File(root + File.separator + "inFiles");
                        /* 消噪后文件夹 */
                        File outFiles = new File(root + File.separator + "outFiles");

                        /* 配置NoiseSuppressionUtils */
                        NoiseSuppressionUtils noiseSuppressionUtils = new NoiseSuppressionUtils();
                        long nsId = noiseSuppressionUtils.nsCreate();
                        noiseSuppressionUtils.nsInit(nsId, 16000);
                        noiseSuppressionUtils.nsSetPolicy(nsId, 2);

                        int nsMinBufferSize = AudioEffectUtils.get10msBufferSizeInByte(16000, 2);

                        short[] inputShort = new short[nsMinBufferSize/2];
                        short[] outputShort = new short[nsMinBufferSize/2];

                        for (File inFile : inFiles.listFiles()){
                            InputStream inputStream = new FileInputStream(inFile);
                            OutputStream outputStream = new FileOutputStream(outFiles.getAbsolutePath() + File.separator + inFile.getName());

                            byte inputByte[] = new byte[nsMinBufferSize];
                            byte outputByte[] = new byte[nsMinBufferSize];
                            int ret = 0;
                            while ((ret = inputStream.read(inputByte)) > 0){
                                /*字节转化*/
                                ByteBuffer.wrap(inputByte).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().get(inputShort);

                                /*送入模型*/
                                noiseSuppressionUtils.nsProcess(nsId, inputShort, 1, outputShort);

                                /* 保存消噪效果 */
                                ByteBuffer.wrap(outputByte).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().put(outputShort);
                                outputStream.write(outputByte);
                                outputStream.flush();
                            }

                            inputStream.close();
                            outputStream.close();
                        }

                        noiseSuppressionUtils.nsFree(nsId);
                        Log.d(TAG, "ns file test finish");
                    }catch (IOException e) {
                        e.printStackTrace();
                    }
                });
                break;
            case R.id.vadFileTest:
                ExecutorService vadFileTest = Executors.newSingleThreadExecutor();
                vadFileTest.execute(()->{
                    try {
                        File inFiles = new File(root + File.separator + "inFiles");
                        VoiceActivityDetectionUtils voiceActivityDetectionUtils = new VoiceActivityDetectionUtils();
                        long vadId = voiceActivityDetectionUtils.vadCreate();
                        voiceActivityDetectionUtils.vadInit(vadId);
                        voiceActivityDetectionUtils.vadSetMode(vadId, 3);
                        int vadMinBufferSize = AudioEffectUtils.get10msBufferSizeInByte(16000, 2);
                        short[] inputShort = new short[vadMinBufferSize/2];

                        for (File inFile : inFiles.listFiles()){
                            InputStream inputStream = new FileInputStream(inFile);

                            byte inputByte[] = new byte[vadMinBufferSize];
                            int ret = 0;
                            while ((ret = inputStream.read(inputByte)) > 0){
                                ByteBuffer.wrap(inputByte).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().get(inputShort);
                                int result = voiceActivityDetectionUtils.vadProcess(vadId, 16000, inputShort);
                                Log.d(TAG, "result: " + result);
                            }
                            inputStream.close();
                        }
                        voiceActivityDetectionUtils.vadFree(vadId);
                        Log.d(TAG, "vad file test finish");

                    }catch (IOException e){
                        e.printStackTrace();
                    }
                });
                break;
            case R.id.agcFileTest:
                ExecutorService agcFileTest = Executors.newSingleThreadExecutor();
                agcFileTest.execute(()->{
                    try {
                        File inFiles = new File(root + File.separator + "inFiles");
                        File outFiles = new File(root + File.separator + "outFiles");

                        AutomaticGainControl automaticGainControl = new AutomaticGainControl();
                        long agcID = automaticGainControl.agcCreate();
                        automaticGainControl.agcInit(agcID, 2, 16000);
                        automaticGainControl.agcSetConfig(agcID, 9, 3);

                        int agcMinBufferSize = AudioEffectUtils.get10msBufferSizeInByte(16000, 2);

                        short[] inputShort = new short[agcMinBufferSize/2];
                        short[] outputShort = new short[agcMinBufferSize/2];

                        for (File inFile : inFiles.listFiles()){
                            InputStream inputStream = new FileInputStream(inFile);
                            OutputStream outputStream = new FileOutputStream(outFiles.getAbsolutePath() + File.separator + inFile.getName());

                            byte inputByte[] = new byte[agcMinBufferSize];
                            byte outputByte[] = new byte[agcMinBufferSize];

                            int ret = 0;
                            while ((ret = inputStream.read(inputByte)) > 0){
                                ByteBuffer.wrap(inputByte).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().get(inputShort);

                                int result = automaticGainControl.agcProcess(agcID, inputShort, 1, 16000, outputShort);
                                Log.d(TAG, "result: " + result);

                                /* 保存处理后文件 */
                                ByteBuffer.wrap(outputByte).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().put(outputShort);
                                outputStream.write(outputByte);
                                outputStream.flush();
                            }
                            inputStream.close();
                            outputStream.close();
                        }

                        automaticGainControl.agcFree(agcID);

                    }catch (IOException e){
                        e.printStackTrace();
                    }
                });
                break;
            case R.id.aecFileTest:
                ExecutorService aecFileTest = Executors.newSingleThreadExecutor();
                aecFileTest.execute(()->{
                    try {
                        File inFiles = new File(root + File.separator + "inFiles");
                        File outFiles = new File(root + File.separator + "outFiles");

                        AcousticEchoCancellationUtils acousticEchoCancellationUtils = new AcousticEchoCancellationUtils();
                        long aecID = acousticEchoCancellationUtils.aecCreate();
                        acousticEchoCancellationUtils.aecInit(aecID, 16000);
                        acousticEchoCancellationUtils.aecSetConfig(aecID, 1);

                        int aecMinBufferSize = AudioEffectUtils.get10msBufferSizeInByte(16000, 2);
                        float[] inputFloat = new float[aecMinBufferSize/4];
                        float[] outputFloat = new float[aecMinBufferSize/4];

                        for (File inFile : inFiles.listFiles()){
                            InputStream inputStream = new FileInputStream(inFile);
                            OutputStream outputStream = new FileOutputStream(outFiles.getAbsolutePath() + File.separator + inFile.getName());

                            byte inputByte[] = new byte[aecMinBufferSize];
                            byte outputByte[] = new byte[aecMinBufferSize];

                            int ret = 0;
                            while ((ret = inputStream.read(inputByte)) > 0){
                                ByteBuffer.wrap(inputByte).order(ByteOrder.LITTLE_ENDIAN).asFloatBuffer().get(inputFloat);

                                int result = acousticEchoCancellationUtils.aecProcess(aecID, inputFloat, inputFloat, outputFloat);
                                Log.d(TAG, "result: " + result);

                                ByteBuffer.wrap(outputByte).order(ByteOrder.LITTLE_ENDIAN).asFloatBuffer().put(outputFloat);
                                outputStream.write(outputByte);
                                outputStream.flush();
                            }

                            inputStream.close();
                            outputStream.close();
                        }

                        acousticEchoCancellationUtils.aecFree(aecID);

                    }catch (IOException e){
                        e.printStackTrace();
                    }
                });
                break;
            case R.id.aecmFileTest:
                ExecutorService aecmFileTest = Executors.newSingleThreadExecutor();
                aecmFileTest.execute(()->{
                    try {
                        File inFiles = new File(root + File.separator + "inFiles");
                        File outFiles = new File(root + File.separator + "outFiles");

                        AcousticEchoCancellerMobileUtils acousticEchoCancellerMobileUtils = new AcousticEchoCancellerMobileUtils();
                        long aecmID = acousticEchoCancellerMobileUtils.aecmCreate();
                        acousticEchoCancellerMobileUtils.aecmInit(aecmID, 16000);
                        acousticEchoCancellerMobileUtils.aecmSetConfig(aecmID, 2);
                        int aecmMinBufferSize = AudioEffectUtils.get10msBufferSizeInByte(16000, 2);
                        short[] inputShort = new short[aecmMinBufferSize/2];
                        short[] outputShort = new short[aecmMinBufferSize/2];
                        for (File inFile : inFiles.listFiles()){
                            InputStream inputStream = new FileInputStream(inFile);
                            OutputStream outputStream = new FileOutputStream(outFiles.getAbsolutePath() + File.separator + inFile.getName());

                            byte inputByte[] = new byte[aecmMinBufferSize];
                            byte outputByte[] = new byte[aecmMinBufferSize];
                            int ret = 0;
                            while ((ret = inputStream.read(inputByte)) > 0){
                                ByteBuffer.wrap(inputByte).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().get(inputShort);

                                int result = acousticEchoCancellerMobileUtils.aecmProcess(aecmID, inputShort, inputShort, outputShort);
                                Log.d(TAG, "result: " + result);

                                ByteBuffer.wrap(outputByte).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().put(outputShort);
                                outputStream.write(outputByte);
                                outputStream.flush();
                            }
                            inputStream.close();
                            outputStream.close();
                        }

                        acousticEchoCancellerMobileUtils.aecmFree(aecmID);
                    }catch (IOException e){
                        e.printStackTrace();
                    }
                });
                break;
            default:
                break;
        }
    }
}