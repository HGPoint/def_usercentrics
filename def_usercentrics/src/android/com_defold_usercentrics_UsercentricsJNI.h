#include <jni.h>
/* Header for class com_defold_usercentrics_UsercentricsJNI */

#ifndef COM_DEFOLD_USERCENTRICS_USERCENTRICSJNI_H
#define COM_DEFOLD_USERCENTRICS_USERCENTRICSJNI_H
#ifdef __cplusplus
extern "C" {
#endif
	/*
	* Class:     com_defold_usercentrics_UsercentricsJNI
	* Method:    jniAddToQueue_first_arg
	* Signature: (ILjava/lang/String;I)V
	*/
	JNIEXPORT void JNICALL Java_com_defold_usercentrics_UsercentricsJNI_jniAddToQueue
		(JNIEnv *, jclass, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif
