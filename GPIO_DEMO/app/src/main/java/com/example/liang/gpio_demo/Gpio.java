/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.example.liang.gpio_demo;

/**
 * Class that provides access to some of the gpio management functions.
 *
 * {@hide}
 */
public class Gpio
{

    // can't instantiate this class
	static {
		System.loadLibrary("gpio_jni");

	}

    public native int Set_GPIO(char name,int number,int val);
    public native int Get_GPIO(char name,int number,int val);

}

