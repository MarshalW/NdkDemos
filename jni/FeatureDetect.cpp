/*
 * HelloWorld.cpp
 *
 *  Created on: 2013年7月29日
 *      Author: marshal
 */
#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "com_demos_ndk_FeatureDetect.h"

using namespace std;
using namespace cv;

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "ndkdemos", __VA_ARGS__))

JNIEXPORT jintArray JNICALL Java_com_demos_ndk_FeatureDetect_nativeMarkImage(
		JNIEnv *env, jobject thiz, jintArray image0, jint width0, jint height0,
		jintArray image, jint width, jint height) {
	jint *cbuf0;
	cbuf0 = env->GetIntArrayElements(image0, false);
	Mat img0(height0, width0, CV_8UC4, (unsigned char*) cbuf0);

	jint *cbuf;
	cbuf = env->GetIntArrayElements(image, false);
	Mat img(height, width, CV_8UC4, (unsigned char*) cbuf);

	Ptr<flann::IndexParams> indexParams = new flann::KDTreeIndexParams();
	Ptr<flann::SearchParams> searchParams = new flann::SearchParams();

	indexParams->setAlgorithm(cvflann::FLANN_INDEX_LSH);
	indexParams->setInt("table_number", 6);
	indexParams->setInt("key_size", 12);
	indexParams->setInt("multi_probe_level", 1);
	searchParams->setAlgorithm(cvflann::FLANN_INDEX_LSH);

	FlannBasedMatcher matcher(indexParams, searchParams);

	OrbFeatureDetector detector(1000);
	OrbDescriptorExtractor extractor(1000);

	vector<KeyPoint> keyPoints0;
	Mat descriptor0;
	detector.detect(img0, keyPoints0, descriptor0);
	extractor.compute(img0, keyPoints0, descriptor0);

	vector<vector<DMatch> > matches;

	vector<Mat> descriptors;
	descriptors.push_back(descriptor0);
	matcher.add(descriptors);

	clock_t now = clock();

	vector<KeyPoint> keyPoints;
	Mat descriptor;
	detector.detect(img, keyPoints, descriptor);
	extractor.compute(img, keyPoints, descriptor);

	matcher.knnMatch(descriptor, matches, 2);

	stringstream strm;
	strm << "ORB+FLANN耗时（毫秒）：" << (clock() - now) / 1000;

	LOGI(strm.str().c_str());

	int size = width * height;
	jintArray result = env->NewIntArray(size);
	env->SetIntArrayRegion(result, 0, size, cbuf);

	env->ReleaseIntArrayElements(image, cbuf, 0);

	return result;
}
