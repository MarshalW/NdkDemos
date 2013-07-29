package com.demos.ndk;

import android.os.Bundle;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	protected void onResume() {
		super.onResume();
		Log.d("ndkdemos", new HelloWorld().sayHello("王五"));

		int[] image = new HelloWorld().drawImage(new int[] { 1, 2, 3, 4 }, 100,
				100);
		Log.d("ndkdemos", "image.length: " + image.length);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
