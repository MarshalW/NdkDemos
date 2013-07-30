package com.demos.ndk;

import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.util.Log;

public class FeatureDetect {

	public Bitmap markMatchImage(Bitmap originImg, Bitmap targetImg) {
		int[] originImgPixels = {}, targetImgPixels = {};
		int originW = 0, originH = 0, targetW = 0, targetH = 0;

		originW = originImg.getWidth();
		originH = originImg.getHeight();
		originImgPixels = new int[originW * originH];
		originImg
				.getPixels(originImgPixels, 0, originW, 0, 0, originW, originH);

		targetW = targetImg.getWidth();
		targetH = targetImg.getHeight();
		targetImgPixels = new int[targetW * targetH];
		targetImg
				.getPixels(targetImgPixels, 0, targetW, 0, 0, targetW, targetH);

		long now=System.currentTimeMillis();
		int[] resultInt = nativeMarkImage(originImgPixels, originW, originH,
				targetImgPixels, targetW, targetH);
		Log.d("ndkdemos","time: "+(System.currentTimeMillis()-now)+"ms");

		Bitmap markedImage = Bitmap.createBitmap(targetW, targetH,
				Config.RGB_565);
		markedImage.setPixels(resultInt, 0, targetW, 0, 0, targetW, targetH);
		return markedImage;

	}

	private native int[] nativeMarkImage(int[] img1, int w1, int h1,
			int[] img2, int w2, int h2);

	static {
		System.loadLibrary("FeatureDetect");
	}
}
