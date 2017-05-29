package com.jiangdg.jnilearning;

import java.util.Random;
import java.util.UUID;

/**(1) C/C++、Java之间交互
 *  (2) C/C++访问Java父类问题  
 *  (3) 中文乱码问题
 *  (4) 数组
 *  @author Created by jiangdongguo on 2017-5-24上午9:26:10
 *  @csdn博客 http://blog.csdn.net/andrexpert
 */
public class JNIUitls {
	public String key = "jiangdongguo";
	public static int count = 99;
	// 一个父类的引用指向子类的对象
	public Fruit fruitInfo = new Bananas();
	
	// Java->C，调用本地方法
	public static native String getStringFromC();
	
	// Java->C，调用本地方法
	public  native String getString2FromC(String str);
	
	//Java->C，中文乱码问题
	public native void getChineseFromC1(String chineseStr);
	
	//Java->C，C/C++传递中文到Java乱码
	public native String getChineseFromC2();
	
	// C->Java，访问Java属性，返回修改之后的属性内容
	public native String accessJavaField();
	
	// C->Java，访问Java静态属性
	public native void accessJavaStaticField();
	
	// C->Java，访问Java方法
	public native void accessJavaMethod();
	
	// C->Java，访问Java静态方法
	public native void accessJavaStaticMethod();
	
	//C->Java，访问Java父类对象的方法
	public native void accessJavaFatherMethod();
	
	// C->Java，返回一个数组给Java
	public native int[] getByteArrayFromC();
	
	//C->Java，C/C++对传入的数组进行排序后返回
	public native int[] getSortedArray(int[] arr);
	
	// 产生一个随机数
	public int genRandomInt(int max){
		return new Random().nextInt(max);
	}
	
	// 产生一个UUID字符串
	public static String getUUID(){
		return UUID.randomUUID().toString();
	}
	
	// 静态加载共享库
	static {
		System.loadLibrary("JniLearning");
	}
}
