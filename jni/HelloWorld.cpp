/*
 * HelloWorld.cpp
 *
 *  Created on: 2013年7月29日
 *      Author: marshal
 */
#include <jni.h>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "com_demos_ndk_HelloWorld.h"

using namespace std;
using namespace cv;

string jstring2str(JNIEnv* env, jstring jstr) {
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("UTF8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes",
			"(Ljava/lang/String;)[B");
	jbyteArray barr = (jbyteArray) env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0) {
		rtn = (char*) malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	string stemp(rtn);
	free(rtn);
	return stemp;
}

jstring str2jstring(JNIEnv* env, const char* pat) {
	jclass strClass = (env)->FindClass("java/lang/String");
	jmethodID ctorID = (env)->GetMethodID(strClass, "<init>",
			"([BLjava/lang/String;)V");
	jbyteArray bytes = (env)->NewByteArray(strlen(pat));
	(env)->SetByteArrayRegion(bytes, 0, strlen(pat), (jbyte*) pat);
	jstring encoding = (env)->NewStringUTF("UTF8");
	return (jstring) (env)->NewObject(strClass, ctorID, bytes, encoding);
}

IplImage * change4channelTo3InIplImage(IplImage * src) {
	if (src->nChannels != 4) {
		return NULL;
	}

	IplImage * destImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
	for (int row = 0; row < src->height; row++) {
		for (int col = 0; col < src->width; col++) {
			CvScalar s = cvGet2D(src, row, col);
			cvSet2D(destImg, row, col, s);
		}
	}

	return destImg;
}

JNIEXPORT jstring JNICALL Java_com_demos_ndk_HelloWorld_sayHello(JNIEnv *env,
		jobject thiz, jstring name) {
	string c = jstring2str(env, name);
	string s = "你好，" + c + "！";
	return str2jstring(env, s.c_str());
}

JNIEXPORT jintArray JNICALL Java_com_demos_ndk_HelloWorld_drawImage(JNIEnv *env,
		jobject thiz, jintArray image, jint width, jint height) {

	jint *cbuf;
	cbuf = env->GetIntArrayElements(image, false);

	Mat myimg(height, width, CV_8UC4, (unsigned char*) cbuf);
	IplImage img = IplImage(myimg);

	IplImage* image3channel = change4channelTo3InIplImage(&img);
	IplImage* pCannyImage = cvCreateImage(cvGetSize(image3channel),
	IPL_DEPTH_8U, 1);

	cvCanny(image3channel, pCannyImage, 50, 150, 3);

	int* outImage = new int[width * height];
	for (int i = 0; i < width * height; i++) {
		outImage[i] = (int) pCannyImage->imageData[i];
	}

	int size = width * height;
	jintArray result = env->NewIntArray(size);
	env->SetIntArrayRegion(result, 0, size, outImage);
	env->ReleaseIntArrayElements(image, cbuf, 0);
	return result;
}
