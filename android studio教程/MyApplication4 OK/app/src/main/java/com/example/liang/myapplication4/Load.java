package com.example.liang.myapplication4;

/**
 * Created by liang on 2016/6/2.
 */
public class Load {
    static { //载入名为“lb”的C++库
        System.loadLibrary("lib");
    }
    public native int addInt(int a, int b); //调用库里的方法“addInt”，这是计算a和b两个整数相加
}
