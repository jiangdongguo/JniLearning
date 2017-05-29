package com.jiangdg.jnilearning;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
	private TextView mTvResult;
	private JNIUitls mJNIUtil;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		mTvResult = (TextView) findViewById(R.id.tv_result);
		mJNIUtil = new JNIUitls();
	}

	public void onGetStringFromCClick(View view) {
		mTvResult.setText(JNIUitls.getStringFromC());
	}

	public void onGetString2FromCClick(View view) {
		mTvResult.setText(mJNIUtil.getString2FromC("Hello，你好！"));
	}

	public void onAccessJavaFieldClick(View view) {
		StringBuilder mBinder = new StringBuilder();
		mBinder.append("原始key = " + mJNIUtil.key);
		mBinder.append("\n");
		mBinder.append("accessJavaField修改后返回值：" + mJNIUtil.accessJavaField());
		mBinder.append("\n");
		mBinder.append("修改后key =  " + mJNIUtil.key);
		mTvResult.setText(mBinder.toString());
	}

	public void onAccessJavaStaticFieldClick(View view) {
		StringBuilder mBinder = new StringBuilder();
		mBinder.append("原始count = " + JNIUitls.count);
		mBinder.append("\n");

		mJNIUtil.accessJavaStaticField();

		mBinder.append("\n");
		mBinder.append("修改后count=" + JNIUitls.count);
		mTvResult.setText(mBinder.toString());
	}

	public void onAccessJavaMethodClick(View view) {
		showToast("onAccessJavaMethodClick");
		mJNIUtil.accessJavaMethod();
	}

	public void onAccessJavaStaticMethodClick(View view) {
		showToast("onAccessJavaStaticMethodClick");
		mJNIUtil.accessJavaStaticMethod();
	}

	public void onAccessJavaFatherMethodClick(View view) {
		Log.d("laojiang", "* Java调用printEatInfo：");
		Fruit eatInfo = mJNIUtil.fruitInfo;
		eatInfo.printEatInfo();
		Log.d("laojiang", "* C/C++调用printEatInfo：");

		mJNIUtil.accessJavaFatherMethod();
	}

	public void onGetChineseFromC1Click(View view) {
		mJNIUtil.getChineseFromC1("蒋");
	}

	public void onGetByteArrayFromCClick(View view) {
		int[] result = mJNIUtil.getByteArrayFromC();
		StringBuilder mBuilder = new StringBuilder();
		for(int i = 0;i<result.length;i++){
			mBuilder.append(String.valueOf(result[i]));
			mBuilder.append(",");
		}
		mTvResult.setText(mBuilder.toString());
	}

	public void onGetSortedArrayClick(View view) {
		int[] array = {11,45,2,90,89,22,100};
		int[] sortArray = mJNIUtil.getSortedArray(array);
		StringBuilder mBuilder = new StringBuilder();
		mBuilder.append("待排序：11,45,2,90,89,22,100");
		mBuilder.append("\n");
		mBuilder.append("已排序：");
		for(int i = 0;i<sortArray.length;i++){
			mBuilder.append(String.valueOf(sortArray[i]));
			mBuilder.append(",");
		}
		mTvResult.setText(mBuilder.toString());
	}

	public void onGetChineseFromC2Click(View view) {
		Toast.makeText(MainActivity.this, mJNIUtil.getChineseFromC2(),
				Toast.LENGTH_SHORT).show();
	}

	private void showToast(String msg) {
		Toast.makeText(MainActivity.this, msg, Toast.LENGTH_SHORT).show();
	}
}
