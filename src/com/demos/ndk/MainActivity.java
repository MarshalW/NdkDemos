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
	
	private FeatureDetect detect;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		imageView = (ImageView) findViewById(R.id.imageView);
		
		detect=new FeatureDetect();
	}

	@Override
	protected void onResume() {
		super.onResume();

		Bitmap originImage = ((BitmapDrawable) getResources().getDrawable(R.raw.f1))
				.getBitmap();
		Bitmap targetImage = ((BitmapDrawable) getResources().getDrawable(R.raw.f13))
				.getBitmap();
		
		Bitmap markedImage=detect.markMatchImage(originImage, targetImage);
		imageView.setImageBitmap(markedImage);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
