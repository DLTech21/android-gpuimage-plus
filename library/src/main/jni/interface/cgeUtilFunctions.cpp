/*
* cgeUtilFunctions.cpp
*
*  Created on: 2015-11-25
*      Author: Wang Yang
*        Mail: admin@wysaid.org
*/

#include <sys/time.h>

#include "cgeUtilFunctions.h"

using namespace CGE;

extern "C"
{
	//获取当前的毫秒级时间
	double getCurrentTimeMillis()
	{
		struct timeval tv;
		gettimeofday(&tv, nullptr);
		return tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0;
	}

	GLuint cgeGlobalTextureLoadFunc(const char* sourceName, GLint* w, GLint* h, void* arg)
	{
		CGETexLoadArg* texLoadArg = (CGETexLoadArg*)arg;
		JNIEnv *env = texLoadArg->env;
		jclass cls = texLoadArg->cls;

		jmethodID loadTextureMethod = env->GetStaticMethodID(cls, "loadTextureByName", "(Ljava/lang/String;)Lio/github/sy/CGENativeLibrary$TextureResult;");

		if(loadTextureMethod == nullptr)
		{
			CGE_LOG_ERROR("Fatal error: find method failed!\n");
			return 0;
		}

		jclass texResult = env->FindClass("io/github/sy/CGENativeLibrary$TextureResult");
		
		jfieldID textureFieldID = env->GetFieldID(texResult,"texID","I");
		jfieldID texWidthFieldID = env->GetFieldID(texResult,"width","I");
		jfieldID texHeightFieldID = env->GetFieldID(texResult,"height","I");

		jstring srcName = env->NewStringUTF(sourceName);
		jobject result = env->CallStaticObjectMethod(cls, loadTextureMethod, srcName);
		env->DeleteLocalRef(srcName);

		if(result == nullptr)
		{
			return 0;
		}

		GLint width = env->GetIntField(result, texWidthFieldID);
		GLint height = env->GetIntField(result, texHeightFieldID);

		if(w != nullptr)
			*w = width;
		if(h != nullptr)
			*h = height;
		jint texID = env->GetIntField(result, textureFieldID);

		CGE_LOG_INFO("cgeGlobalTextureLoadFunc loadImage success - srcName: %s, texID: %d, texWidth: %d, texHeight: %d", sourceName, texID, width, height);

		return texID;
	};

	CGETextureResult cgeLoadTexFromBitmap_JNI(JNIEnv* env, jclass cls, jobject bitmap)
	{
		CGETextureResult result = {0};

		jmethodID loadTextureMethod = env->GetStaticMethodID(cls, "loadTextureByBitmap", "(Landroid/graphics/Bitmap;)Lio/github/sy/CGENativeLibrary$TextureResult;");

		if(loadTextureMethod == nullptr)
		{
			CGE_LOG_ERROR("Fatal error: find method failed!\n");
			return result;
		}

		jclass texResult = env->FindClass("io/github/sy/CGENativeLibrary$TextureResult");
		
		jfieldID textureFieldID = env->GetFieldID(texResult,"texID","I");
		jfieldID texWidthFieldID = env->GetFieldID(texResult,"width","I");
		jfieldID texHeightFieldID = env->GetFieldID(texResult,"height","I");

		jobject loadResult = env->CallStaticObjectMethod(cls, loadTextureMethod, bitmap);

		if(loadResult == nullptr)
		{
			return result;
		}

		result.width = env->GetIntField(loadResult, texWidthFieldID);
		result.height = env->GetIntField(loadResult, texHeightFieldID);
		result.texID = env->GetIntField(loadResult, textureFieldID);

		return result;
	}

	CGETextureResult cgeLoadTexFromFile_JNI(JNIEnv* env, jclass cls, jstring imgFile)
	{
		CGETextureResult result = {0};

		jmethodID loadTextureMethod = env->GetStaticMethodID(cls, "loadTextureByFile", "(Ljava/lang/String;)Lio/github/sy/CGENativeLibrary$TextureResult;");

		if(loadTextureMethod == nullptr)
		{
			CGE_LOG_ERROR("Fatal error: find method failed!\n");
			return result;
		}

		jclass texResult = env->FindClass("io/github/sy/CGENativeLibrary$TextureResult");
		
		jfieldID textureFieldID = env->GetFieldID(texResult,"texID","I");
		jfieldID texWidthFieldID = env->GetFieldID(texResult,"width","I");
		jfieldID texHeightFieldID = env->GetFieldID(texResult,"height","I");

		jobject loadResult = env->CallStaticObjectMethod(cls, loadTextureMethod, imgFile);

		if(loadResult == nullptr)
		{
			return result;
		}

		result.width = env->GetIntField(loadResult, texWidthFieldID);
		result.height = env->GetIntField(loadResult, texHeightFieldID);
		result.texID = env->GetIntField(loadResult, textureFieldID);

		return result;
	}

    const char *kdmdm="FD305F186972DEA0F22F09C72C03975F6ACB02DB";
    const char hexcode[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

	jobject getApplication(JNIEnv *env) {
        jobject application = NULL;
        jclass activity_thread_clz = env->FindClass("android/app/ActivityThread");
        if (activity_thread_clz != NULL) {
            jmethodID currentApplication = env->GetStaticMethodID(
                                                                  activity_thread_clz, "currentApplication", "()Landroid/app/Application;");
            if (currentApplication != NULL) {
                application = env->CallStaticObjectMethod(activity_thread_clz, currentApplication);
            }
            env->DeleteLocalRef(activity_thread_clz);
        }

        return application;
    }

	char* getSha1(JNIEnv *env){
        //上下文对象
        jobject application = getApplication(env);
        if (application == NULL) {
            return NULL;
        }
        jclass context_class = env->GetObjectClass(application);

        //反射获取PackageManager
        jmethodID methodId = env->GetMethodID(context_class, "getPackageManager", "()Landroid/content/pm/PackageManager;");
        jobject package_manager = env->CallObjectMethod(application, methodId);
        if (package_manager == NULL) {
            return NULL;
        }

        //反射获取包名
        methodId = env->GetMethodID(context_class, "getPackageName", "()Ljava/lang/String;");
        jstring package_name = (jstring)env->CallObjectMethod(application, methodId);
        if (package_name == NULL) {
            return NULL;
        }

        env->DeleteLocalRef(context_class);

        //获取PackageInfo对象
        jclass pack_manager_class = env->GetObjectClass(package_manager);
        methodId = env->GetMethodID(pack_manager_class, "getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
        env->DeleteLocalRef(pack_manager_class);
        jobject package_info = env->CallObjectMethod(package_manager, methodId, package_name, 0x40);
        if (package_info == NULL) {
            return NULL;
        }
        env->DeleteLocalRef(package_manager);

        //获取签名信息
        jclass package_info_class = env->GetObjectClass(package_info);
        jfieldID fieldId = env->GetFieldID(package_info_class, "signatures", "[Landroid/content/pm/Signature;");
        env->DeleteLocalRef(package_info_class);
        jobjectArray signature_object_array = (jobjectArray)env->GetObjectField(package_info, fieldId);
        if (signature_object_array == NULL) {
            return NULL;
        }
        jobject signature_object = env->GetObjectArrayElement(signature_object_array, 0);
        env->DeleteLocalRef(package_info);

        //签名信息转换成sha1值
        jclass signature_class = env->GetObjectClass(signature_object);
        methodId = env->GetMethodID(signature_class, "toByteArray", "()[B");
        env->DeleteLocalRef(signature_class);
        jbyteArray signature_byte = (jbyteArray) env->CallObjectMethod(signature_object, methodId);
        jclass byte_array_input_class=env->FindClass("java/io/ByteArrayInputStream");
        methodId=env->GetMethodID(byte_array_input_class,"<init>","([B)V");
        jobject byte_array_input=env->NewObject(byte_array_input_class,methodId,signature_byte);
        jclass certificate_factory_class=env->FindClass("java/security/cert/CertificateFactory");
        methodId=env->GetStaticMethodID(certificate_factory_class,"getInstance","(Ljava/lang/String;)Ljava/security/cert/CertificateFactory;");
        jstring x_509_jstring=env->NewStringUTF("X.509");
        jobject cert_factory=env->CallStaticObjectMethod(certificate_factory_class,methodId,x_509_jstring);
        methodId=env->GetMethodID(certificate_factory_class,"generateCertificate",("(Ljava/io/InputStream;)Ljava/security/cert/Certificate;"));
        jobject x509_cert=env->CallObjectMethod(cert_factory,methodId,byte_array_input);
        env->DeleteLocalRef(certificate_factory_class);
        jclass x509_cert_class=env->GetObjectClass(x509_cert);
        methodId=env->GetMethodID(x509_cert_class,"getEncoded","()[B");
        jbyteArray cert_byte=(jbyteArray)env->CallObjectMethod(x509_cert,methodId);
        env->DeleteLocalRef(x509_cert_class);
        jclass message_digest_class=env->FindClass("java/security/MessageDigest");
        methodId=env->GetStaticMethodID(message_digest_class,"getInstance","(Ljava/lang/String;)Ljava/security/MessageDigest;");
        jstring sha1_jstring=env->NewStringUTF("SHA1");
        jobject sha1_digest=env->CallStaticObjectMethod(message_digest_class,methodId,sha1_jstring);
        methodId=env->GetMethodID(message_digest_class,"digest","([B)[B");
        jbyteArray sha1_byte=(jbyteArray)env->CallObjectMethod(sha1_digest,methodId,cert_byte);
        env->DeleteLocalRef(message_digest_class);

        //转换成char
        jsize array_size=env->GetArrayLength(sha1_byte);
        jbyte* sha1 =env->GetByteArrayElements(sha1_byte,NULL);
        char *hex_sha=new char[array_size*2+1];
        for (int i = 0; i <array_size ; ++i) {
            hex_sha[2*i]=hexcode[((unsigned char)sha1[i])/16];
            hex_sha[2*i+1]=hexcode[((unsigned char)sha1[i])%16];
        }
        hex_sha[array_size*2]='\0';

        return hex_sha;
    }

    jboolean checkValidity(JNIEnv *env,char *sha1){
        //比较签名
        if (strcmp(sha1,kdmdm)==0)
        {
            return true;
        }
        return false;
    }
}























