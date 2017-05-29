package com.jiangdg.jnilearning;

import android.util.Log;

/** 水果父类
 *
 * @author Created by jiangdongguo on 2017-5-26上午9:44:43
 */
public class Fruit {
	protected static final String TAG = "laojiang";

	protected void printEatInfo(){
		Log.d(TAG, "水果都是可吃的...");
	}

}
