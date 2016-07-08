//
// Created by liang on 2016/7/7.
//

#include"com_example_liang_gpio_demo_Gpio.h"

#include<stdio.h>
#include<string.h>
#include<unistd.h>

#include"Logger.h"

JNIEXPORT jint JNICALL Java_com_example_liang_gpio_1demo_Gpio_Init_1GPIO
        (JNIEnv *env, jobject obj, jstring name, jint val){
        char buf[128];
        const char *str=env->GetStringUTFChars(name,0);
        printf("%s\n",str);
        LOGD("Com::start - open device %s faild\n", str);
}
JNIEXPORT jint JNICALL Java_com_example_liang_gpio_1demo_Gpio_Set_1GPIO
        (JNIEnv *env, jobject obj, jstring name, jint number, jint val){

}
JNIEXPORT jint JNICALL Java_com_example_liang_gpio_1demo_Gpio_Get_1GPIO
        (JNIEnv *env, jobject, jstring name, jint number, jint val){

}