package org.wysaid.nativePort;

/**
 * Created by wangyang on 15/7/30.
 */
public class NativeLibraryLoader {

    public static void load() {
        System.loadLibrary("ijkffmpeg");
        System.loadLibrary("CGE");
        System.loadLibrary("CGEExt");
        CGEFFmpegNativeLibrary.avRegisterAll();
    }

}
