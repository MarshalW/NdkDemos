package com.demos.ndk;

public class HelloWorld {
	public native String sayHello(String name);

	public native int[] drawImage(int[] image, int width, int height);

	static {
		System.loadLibrary("HelloWorld");
	}
}
