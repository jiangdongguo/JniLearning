package com.jiangdg.jnilearning;

import android.util.Log;

/** 香蕉是水果的子类
 *
 * @author Created by jiangdongguo on 2017-5-26上午9:44:56
 */
public class Bananas extends Fruit {

	@Override
	protected void printEatInfo() {
		Log.d(TAG, "香蕉是水果的一种，所以是可以吃的...");
	}
}
