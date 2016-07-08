//
// Created by liang on 2016/7/7.
//

#include"com_example_liang_gpio_demo_Gpio.h"

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include"Logger.h"


#include "A20-gpio.hpp"

#include <assert.h>
#include <iostream>


using namespace A20;

#define GPIO_DEVICE_NAME "/sys/class/gpio_sw/"

JNIEXPORT jint JNICALL Java_com_example_liang_gpio_1demo_Gpio_Init_1GPIO
        (JNIEnv *env, jobject obj, jstring name, jint val){
      /*  char buf[128];
        strcpy(buf,GPIO_DEVICE_NAME);
        const char *str=env->GetStringUTFChars(name,0);
        strcat(buf,str);
        strcat(buf,"/cfg");
        LOGD("buf is %s \n", buf);
        int gpio_fd=open(buf,O_RDWR);
        if(gpio_fd<=0){
                LOGD("open gpio device %s faild\n", buf);
                return 0;
        }
        char tmp[20];
        if(val==1){
                LOGD("gpio init is %s\n", "out");
                strcpy(tmp,"1");
        }else{
                LOGD("gpio init is %s\n", "in");
                strcpy(tmp,"0");
        }

        if(write(gpio_fd ,tmp,sizeof(tmp) - 1)<=0){
                LOGD("write gpio_fd is %s\n", "error");
        }
        LOGD("tmp is %s \n", tmp);
        printf("%s\n",str);
        LOGD("Com::start - open device %s faild\n", str);
        close(gpio_fd);*/

        GPIO_input *test;
        GPIO_input *test2;

        GPIO::init();
        test  = GPIO::get_input(261);
        test2 = GPIO::get_input(261);
        assert(test==test2);

        std::cout << "GPIO 261 reads (no pull-resistor): " << test->get() << std::endl;

        GPIO::free(261);
        test = GPIO::get_input(261, PULL_UP);

        std::cout << "GPIO 261 reads (pulled UP): " << test->get() << std::endl;

        GPIO::free(261);
        test = GPIO::get_input(261, PULL_DOWN);

        std::cout << "GPIO 261 reads (pulled DOWN): " << test->get() << std::endl;

        GPIO::free(261);
        GPIO::set_periphery_mode(261);

        std::cout << "GPIO 261 now in periphery mode" << std::endl;

        GPIO_output *test_out;

        GPIO::free(261);
        test_out = GPIO::get_output(261);

        test_out->set(true);
        std::cout << "GPIO 261 is now enabled as output and producing '1' (wait 5s)." << std::endl;

        sleep(5);

        test_out->set(false);
        std::cout << "GPIO 261 is now enabled as output and producing '0' (wait 5s)." << std::endl;

        sleep(5);
        GPIO::free(261);

        return 1;
}
JNIEXPORT jint JNICALL Java_com_example_liang_gpio_1demo_Gpio_Set_1GPIO
        (JNIEnv *env, jobject obj, jstring name, jint number, jint val){
        char buf[128];
        // strcat(buf,GPIO_DEVICE_NAME);
        strcpy(buf,GPIO_DEVICE_NAME);
        const char *str=env->GetStringUTFChars(name,0);
        // strcpy(buf,str);
        strcat(buf,str);
        strcat(buf,"/data");
        LOGD("buf is %s \n", buf);
        FILE *gpio_fd;
        gpio_fd = fopen(buf, "rb+");
        if(gpio_fd==NULL){
                LOGD("open gpio device %s faild\n", buf);
                return 0;
        }
        char tmp[20];
        if(val==1){
                LOGD("gpio set is %s\n", "1");
                strcpy(tmp,"1");
        }else{
                LOGD("gpio set is %s\n", "0");
                strcpy(tmp,"0");
        }

        fwrite(tmp, sizeof(char), sizeof(tmp) - 1, gpio_fd);

        LOGD("tmp is %s \n", tmp);
        printf("%s\n",str);
        LOGD("Com::start - open device %s faild\n", str);
        fclose(gpio_fd);
        return 1;
}
JNIEXPORT jint JNICALL Java_com_example_liang_gpio_1demo_Gpio_Get_1GPIO
        (JNIEnv *env, jobject, jstring name, jint number, jint val){
        char buf[128];
        int re=0;
        strcpy(buf,GPIO_DEVICE_NAME);
       // strcat(buf,GPIO_DEVICE_NAME);
        const char *str=env->GetStringUTFChars(name,0);
       // strcpy(buf,str);
        strcat(buf,str);
        strcat(buf,"/data");
        LOGD("buf is %s \n", buf);
        FILE *gpio_fd=fopen(buf,"r");
        if(gpio_fd==NULL){
            LOGD("open gpio device %s faild\n", buf);
            return -1;
        }
        char tmp[20];
        fread(tmp, sizeof(char), sizeof(tmp) - 1, gpio_fd);
        LOGD("tmp is %s \n", tmp);
        printf("%s\n",str);
       /* if(strcmp(str,"0")==0){
                re=0;
                LOGD("strstr %d\n",0);
        }else{
                re=1;
                LOGD("strstr %d\n",1);
        }*/
        re=atoi(tmp);
        LOGD("strstr %d\n",re);

        fclose(gpio_fd);
        return re;
}