package com.demos.ndk;

import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.widget.ImageView;

public class MainActivity extends Activity {

	private ImageView imageView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		imageView = (ImageView) findViewById(R.id.imageView);
	}

	@Override
	protected void onResume() {
		super.onResume();
		Log.d("ndkdemos", new HelloWorld().sayHello("王五"));

		Bitmap img = ((BitmapDrawable) getResources().getDrawable(R.raw.f1))
				.getBitmap();
		int w = img.getWidth(), h = img.getHeight();
		int[] pix = new int[w * h];
		img.getPixels(pix, 0, w, 0, 0, w, h);
		int[] resultInt = new HelloWorld().drawImage(pix, w, h);
		Bitmap resultImg = Bitmap.createBitmap(w, h, Config.RGB_565);
		resultImg.setPixels(resultInt, 0, w, 0, 0, w, h);

		imageView.setImageBitmap(resultImg);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
