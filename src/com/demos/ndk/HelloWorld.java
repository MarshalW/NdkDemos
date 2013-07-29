package com.demos.ndk;

public class HelloWorld {
	public native String sayHello(String name);
	
	static{
		System.loadLibrary("HelloWorld");
	}
}
