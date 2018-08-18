/*
* cgeFrameRendererWrapper.h
*
*  Created on: 2015-11-26
*      Author: Wang Yang
*        Mail: admin@wysaid.org
*/

#include <jni.h>
/* Header for class io_github_sy_CGEFrameRenderer */

#ifndef _Included_io_github_sy_CGEFrameRenderer
#define _Included_io_github_sy_CGEFrameRenderer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     io_github_sy_CGEFrameRenderer
 * Method:    nativeCreate
 * Signature: ()Ljava/nio/ByteBuffer;
 */
JNIEXPORT jlong JNICALL Java_io_github_sy_CGEFrameRenderer_nativeCreateRenderer
  (JNIEnv *, jobject);

/*
 * Class:     io_github_sy_CGEFrameRenderer
 * Method:    nativeInit
 * Signature: (Ljava/nio/ByteBuffer;IIII)Z
 */
JNIEXPORT jboolean JNICALL Java_io_github_sy_CGEFrameRenderer_nativeInit
  (JNIEnv *, jobject, jlong, jint, jint, jint, jint);

/*
 * Class:     io_github_sy_CGEFrameRenderer
 * Method:    nativeUpdate
 * Signature: (Ljava/nio/ByteBuffer;I)V
 */
JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeUpdate
  (JNIEnv *, jobject, jlong, jint, jfloatArray);

/*
 * Class:     io_github_sy_CGEFrameRenderer
 * Method:    nativeRender
 * Signature: (Ljava/nio/ByteBuffer;IIII)V
 */
JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeRender
  (JNIEnv *, jobject, jlong, jint, jint, jint, jint);

/*
 * Class:     io_github_sy_CGEFrameRenderer
 * Method:    nativeSetSrcRotation
 * Signature: (Ljava/nio/ByteBuffer;F)V
 */
JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetSrcRotation
  (JNIEnv *, jobject, jlong, jfloat);

/*
 * Class:     io_github_sy_CGEFrameRenderer
 * Method:    nativeSetSrcFlipScale
 * Signature: (Ljava/nio/ByteBuffer;FF)V
 */
JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetSrcFlipScale
  (JNIEnv *, jobject, jlong, jfloat, jfloat);

/*
 * Class:     io_github_sy_CGEFrameRenderer
 * Method:    nativeSetRenderRotation
 * Signature: (Ljava/nio/ByteBuffer;F)V
 */
JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetRenderRotation
  (JNIEnv *, jobject, jlong, jfloat);

/*
 * Class:     io_github_sy_CGEFrameRenderer
 * Method:    nativeSetRenderFlipScale
 * Signature: (Ljava/nio/ByteBuffer;FF)V
 */
JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetRenderFlipScale
  (JNIEnv *, jobject, jlong, jfloat, jfloat);

/*
 * Class:     io_github_sy_CGEFrameRenderer
 * Method:    nativeSetFilterWithConfig
 * Signature: (Ljava/nio/ByteBuffer;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetFilterWithConfig
  (JNIEnv *, jobject, jlong, jstring);

/*
 * Class:     io_github_sy_CGEFrameRenderer
 * Method:    nativeSetFilterIntensity
 * Signature: (Ljava/nio/ByteBuffer;F)V
 */
JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetFilterIntensity
  (JNIEnv *, jobject, jlong, jfloat);

JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSrcResize
  (JNIEnv *, jobject, jlong, jint, jint);

JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetMaskTexture
  (JNIEnv *, jobject, jlong, jint, jfloat);

JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetMaskTextureRatio
  (JNIEnv *, jobject, jlong, jfloat);

JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeRelease
  (JNIEnv *, jobject, jlong);

JNIEXPORT jint JNICALL Java_io_github_sy_CGEFrameRenderer_nativeQueryBufferTexture
  (JNIEnv *, jobject, jlong);

JNIEXPORT jint JNICALL Java_io_github_sy_CGEFrameRenderer_nativeQueryTargetTexture
  (JNIEnv *, jobject, jlong);


JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetMaskRotation
  (JNIEnv *, jobject, jlong, jfloat);

JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetMaskFlipScale
  (JNIEnv *, jobject, jlong, jfloat, jfloat);

 JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeRunProc
   (JNIEnv *, jobject, jlong);

/////////////////  Render Utils  /////////////////////////////

JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeDrawCache
  (JNIEnv *, jobject, jlong);

JNIEXPORT jlong JNICALL Java_io_github_sy_CGEFrameRenderer_nativeGetImageHandler
  (JNIEnv *, jobject, jlong);

JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeBindImageFBO
  (JNIEnv *, jobject, jlong);

JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSwapBufferFBO
  (JNIEnv *, jobject, jlong);

JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeProcessWithFilter
  (JNIEnv *, jobject, jlong, jlong);

////

JNIEXPORT void JNICALL Java_io_github_sy_CGEFrameRenderer_nativeSetFilterWithAddr
  (JNIEnv *, jobject, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif
