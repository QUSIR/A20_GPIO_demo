//
// Created by liang on 2016/6/2.
//

#include"com_example_liang_myapplication4_Load.h"

JNIEXPORT jint JNICALL Java_com_example_liang_myapplication4_Load_addInt
  (JNIEnv *, jobject, jint a, jint b){
      return a+b;
}