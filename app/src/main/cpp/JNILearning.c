/** C++本地方法实现
 * @author Created by jiangdongguo on 2017-5-24 9:26:10
 * @csdn博客 http://blog.csdn.net/andrexpert
 */
#include <jni.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <android/log.h>
//#include <iconv.h>

#define LOG_TAG "laojiang"
// 不带格式日志
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,"%s",__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,"%s",__VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,"%s",__VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,"%s",__VA_ARGS__)
// 带格式日志
#define LOG_I(format,...) __android_log_print(ANDROID_LOG_INFO,LOG_TAG,format,__VA_ARGS__)
#define LOG_D(format,...) __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,format,__VA_ARGS__)
#define LOG_W(format,...) __android_log_print(ANDROID_LOG_WARN,LOG_TAG,format,__VA_ARGS__)
#define LOG_E(format,...) __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,format, __VA_ARGS__)
// 声明函数
char* jstringTostring(JNIEnv* env, jstring jstr);
int compare(const void *a,const void *b);

/**
 *  Java访问本地函数，返回一个字符串
 * */
JNIEXPORT jstring JNICALL Java_com_jiangdg_jnilearning_JNIUitls_getStringFromC
        (JNIEnv *env, jclass jobj){
    return (*env)->NewStringUTF(env,"My Name is jiangdongguo--2017");
}

/**
 *  Java访问本地函数，返回一个拼接字符串
 * */
JNIEXPORT jstring JNICALL Java_com_jiangdg_jnilearning_JNIUitls_getString2FromC
        (JNIEnv *env, jobject jobj, jstring j_str){
    // jstring转char *
    char* c_str = jstringTostring(env,j_str);
    // 拼接字符串
    strcat(c_str," 广州");
    LOG_D("c_str = %s",c_str);
    // char * 转string
    jstring j_temp = (*env)->NewStringUTF(env,(const char*)c_str);
    return j_temp;
}

/**
 *  C/C++层访问Java对象的属性
 * */
JNIEXPORT jstring JNICALL Java_com_jiangdg_jnilearning_JNIUitls_accessJavaField
        (JNIEnv *env, jobject jobj){
    // 得到Java类JNIUtils.class
    jclass jniutil_cls = (*env)->GetObjectClass(env,jobj);
    // 得到java对象的key属性ID
    jfieldID key_fid = (*env)->GetFieldID(env,jniutil_cls,"key","Ljava/lang/String;");
    // 得到Java对象Key属性的值
    jstring key = (jstring)(*env)->GetObjectField(env,jobj,key_fid);
    // 拼接一个新的c字符串
    const char * c_key = (*env)->GetStringUTFChars(env,key,JNI_FALSE);
    char  c_temp[100] = "Hello,";
    strcat(c_temp,c_key);
    // 修改key属性的值
    jstring j_temp = (*env)->NewStringUTF(env,c_temp);
    (*env)->SetObjectField(env,jobj,key_fid,j_temp);
    return j_temp;
}

/**
 *  C/C++层访问Java类的静态属性
 * */
JNIEXPORT void JNICALL Java_com_jiangdg_jnilearning_JNIUitls_accessJavaStaticField
        (JNIEnv *env, jobject jobj){
    jclass ju_cls = (*env)->GetObjectClass(env,jobj);
    // 得到JNIUtils类静态属性count的ID
    jfieldID count_fid = (*env)->GetStaticFieldID(env,ju_cls,"count","I");
    // 得到count属性的值
    jint count = (*env)->GetStaticIntField(env,ju_cls,count_fid);
    // 修改count属性的值
    jint new_count = count+1;
    (*env)->SetStaticIntField(env,ju_cls,count_fid,new_count);
}

/**
 *  C/C++层访问Java对象的方法
 * */
JNIEXPORT void JNICALL Java_com_jiangdg_jnilearning_JNIUitls_accessJavaMethod
        (JNIEnv *env, jobject jobj){
    jclass cls = (*env)->GetObjectClass(env,jobj);
    // 得到JNIUtils类对象genRandomInt方法的ID
    jmethodID mid = (*env)->GetMethodID(env,cls,"genRandomInt","(I)I");
    // 调用genRandomInt方法
    jint random = (*env)->CallIntMethod(env,jobj,mid,200);
    LOG_I("genRandomInt() = %d",random);
}

/**
 * C/C++层访问Java类的静态方法
 * */
JNIEXPORT void JNICALL Java_com_jiangdg_jnilearning_JNIUitls_accessJavaStaticMethod
        (JNIEnv *env, jobject jobj){
    jclass ju_cls = (*env)->GetObjectClass(env,jobj);
    // 得到JNIUtils类getUUID静态方法ID
    jmethodID mid = (*env)->GetStaticMethodID(env,ju_cls,"getUUID","()Ljava/lang/String;");
    // 调用getUUID方法
    jstring UUID = (jstring)(*env)->CallStaticObjectMethod(env,ju_cls,mid);
    LOG_I("getUUID() = %s",(*env)->GetStringUTFChars(env,UUID,JNI_FALSE));
}

/**
 * C/C++访问Java的父类方法
 * */
JNIEXPORT void JNICALL Java_com_jiangdg_jnilearning_JNIUitls_accessJavaFatherMethod
        (JNIEnv *env, jobject jobj){
    jclass cls = (*env)->GetObjectClass(env,jobj);
    // 得到JNIUtils对象fruitInfo属性对象的ID
    jfieldID fid =  (*env)->GetFieldID(env,cls,"fruitInfo","Lcom/jiangdg/jnilearning/Fruit;");
    // 得到fruitInfo属性对象
    jobject fruit_jobj = (*env)->GetObjectField(env,jobj,fid);
    // 得到父类Fruit
    jclass fruit_cls = (*env)->FindClass(env,"com/jiangdg/jnilearning/Fruit");
    // 得到父类的printEatInfo方法，调用该方法
    jmethodID fruit_mid = (*env)->GetMethodID(env,fruit_cls,"printEatInfo","()V");
    (*env)->CallNonvirtualVoidMethod(env,fruit_jobj,fruit_cls,fruit_mid);
}

JNIEXPORT void JNICALL Java_com_jiangdg_jnilearning_JNIUitls_getChineseFromC1
        (JNIEnv *env, jobject jobj, jstring j_str){
    unsigned char qm, wm;					// 区码、位码
    unsigned int i,offset = 0;					// 偏移量
    FILE *fp = NULL;
    //----------------------------------------------------------------------------
    // 得到UTF-8格式的字节数组数据
    const char* c_str_utf8 = (*env)->GetStringUTFChars(env,j_str,JNI_FALSE);
//    // 使用iconv库将UTF-8转换为GB2312
//	iconv_t cd = iconv_open ("gbk","utf-8");
//	if(cd == (iconv_t)-1){
//		LOG_E("打开iconv库失败，error = %d",errno);
//		return;
//	}
//	// 转换汉字编码格式
//	char* c_str_gbk = (char *)malloc(32);
//	unsigned int len = 32;
//	char *temp = (char *)malloc(32);
//	strcpy(temp,c_str_utf8);
//	iconv (cd, &temp,&len, &c_str_gbk, &len);
//	iconv_close (cd);
    //----------------------------------------------------------------------------
    // 从字库中查找
    // 打开HZK16字库文件，提取"蒋"字模，汉字占两个字节，取其区位号
    if ((fp = fopen("/storage/emulated/0/HZK16c", "rb")) == NULL) {
        LOGE("打开HZK16字库文件失败，请查看文件是否存在");
        return;
    }
    // 计算<蒋>在字库中的偏移量
    qm = *c_str_utf8 - 0xa0;
    wm = *(c_str_utf8+1) - 0xa0;
    offset = (94*(qm-1)+(wm-1))*32;
    LOG_D("区位=%d--->码位=%d--->偏移量=%d",qm,wm,offset);
    // 开辟一段内存空间，根据偏移量在字库中定位，提取汉字字模
    char *table = (char *)malloc(32);
    fseek(fp, offset, SEEK_SET);
    fread(table,1,32,fp);
    // 打印序列
    LOGD("提取<蒋>字模数据：");
    for(i=0;i<32;i++){
        LOG_I("%#x,",table[i]);
    }
    fclose(fp);
    fp = NULL;
}

JNIEXPORT jstring JNICALL Java_com_jiangdg_jnilearning_JNIUitls_getChineseFromC2
        (JNIEnv *env, jobject jobj){
    // (1) 得到String(byte[] data,String charset)构造方法ID
    jclass str_cls = (*env)->FindClass(env,"java/lang/String");
    jmethodID construct_mid = (*env)->GetMethodID(env,str_cls,"<init>","([BLjava/lang/String;)V");
    // (2) 得到编码为GB2312 字符数组
    const char* c_str = "Hello，中国！";
    jbyteArray bArray = (*env)->NewByteArray(env,strlen(c_str));
    (*env)->SetByteArrayRegion(env,bArray,0,strlen(c_str),(const signed char *)c_str);
    // (3) 指定构造String编码 UTF-8
    jstring j_charset = (*env)->NewStringUTF(env,"UTF-8");
    // 将GB2312编码的字符串转换为UTF-8，返回给Java
    jstring result = (jstring)(*env)->NewObject(env,str_cls,construct_mid,bArray,j_charset);
    return result;
}

JNIEXPORT jintArray JNICALL Java_com_jiangdg_jnilearning_JNIUitls_getByteArrayFromC(
        JNIEnv *env, jobject jobj) {
    jsize i,len = 10;
    // 创建一个jintArray
    jintArray j_arr = (*env)->NewIntArray(env,len);
    // jnitArray转jint *(即c/c++)
    jint* c_arr = (*env)->GetIntArrayElements(env,j_arr,JNI_FALSE);
    // 写入数据
    for(i=0;i<len;i++){
        *(c_arr + i) = i;
    }
    // 同步到Java层
    (*env)->ReleaseIntArrayElements(env,j_arr,c_arr,JNI_COMMIT);
    return j_arr;
}

JNIEXPORT jintArray JNICALL Java_com_jiangdg_jnilearning_JNIUitls_getSortedArray(
        JNIEnv *env, jobject jobj, jintArray j_arr) {
    // jintArray转jint *
    jint* c_arr = (*env)->GetIntArrayElements(env,j_arr,JNI_FALSE);
    // 得到数组的长度
    jsize arrLen = (*env)->GetArrayLength(env,j_arr);
    // 排序
    qsort(c_arr,arrLen,sizeof(jint),compare);
    // 同步数据到Java层
    (*env)->ReleaseIntArrayElements(env,j_arr,c_arr,JNI_COMMIT);
    return j_arr;
}

int compare(const void *a,const void *b){
    return *(int *)a - *(int *)b;
}

char* jstringTostring(JNIEnv* env, jstring j_str) {
    char* c_str = NULL;
    jclass clsstring = (*env)->FindClass(env,"java/lang/String");
    jstring strencode = (*env)->NewStringUTF(env,"utf-8");
    jmethodID mid = (*env)->GetMethodID(env,clsstring, "getBytes","(Ljava/lang/String;)[B");
    jbyteArray byteArr = (jbyteArray)(*env)->CallObjectMethod(env,j_str, mid,strencode);
    jsize arrLen = (*env)->GetArrayLength(env,byteArr);
    jbyte* ba = (*env)->GetByteArrayElements(env,byteArr, JNI_FALSE);
    if (arrLen > 0) {
        c_str = (char*) malloc(arrLen + 1);
        memcpy(c_str, ba, arrLen);
        c_str[arrLen] = 0;
    }
    (*env)->ReleaseByteArrayElements(env,byteArr, ba, 0);
    return c_str;
}





