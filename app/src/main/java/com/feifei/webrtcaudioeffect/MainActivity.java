package com.feifei.webrtcaudioeffect;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.feifei.webrtcaudioeffect.AudioEffect.NoiseSuppressionUtils;

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
    private Button nsFileTest;

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
        nsFileTest=(Button)findViewById(R.id.nsFileTest);
        nsFileTest.setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
        String root = getExternalFilesDir("").getAbsolutePath();
        switch (v.getId()){
            /* 测试噪声抑制对音频文件的效果 */
            case R.id.nsFileTest:
                ExecutorService testFileThreadExecutor = Executors.newSingleThreadExecutor();
                testFileThreadExecutor.execute(()->{
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

                        int nsMinBufferSize = NoiseSuppressionUtils.get10msBufferSizeInByte(16000);

                        short[] inputData = new short[nsMinBufferSize/2];
                        short[] outputData = new short[nsMinBufferSize/2];

                        for (File inFile : inFiles.listFiles()){
                            InputStream inputStream = new FileInputStream(inFile);
                            OutputStream outputStream = new FileOutputStream(outFiles.getAbsolutePath() + File.separator + inFile.getName());

                            byte inputTemp[] = new byte[nsMinBufferSize];
                            byte outputTemp[] = new byte[nsMinBufferSize];
                            int ret = 0;
                            while ((ret = inputStream.read(inputTemp)) > 0){
                                /*字节转化*/
                                ByteBuffer.wrap(inputTemp).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().get(inputData);

                                /*送入模型*/
                                noiseSuppressionUtils.nsProcess(nsId, inputData, 1, outputData);

                                /* 保存消噪效果 */
                                ByteBuffer.wrap(outputTemp).order(ByteOrder.LITTLE_ENDIAN).asShortBuffer().put(outputData);
                                outputStream.write(outputTemp);
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

            default:
                break;
        }
    }
}