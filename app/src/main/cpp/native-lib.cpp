#include <string>
#include "bitmap-utils.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_example_kru13_bitmaptest_MainActivity_bitmapBlur(JNIEnv *env, jobject instance, jobject img) {
    imageTransform(env, img, transformBlur);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_kru13_bitmaptest_MainActivity_bitmapInverse(JNIEnv *env, jobject instance, jobject img) {
    imageTransform(env, img, transformInverse);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_kru13_bitmaptest_MainActivity_bitmapGrayscale(JNIEnv *env, jobject instance, jobject img) {
    imageTransform(env, img, transformGrayscale);
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_kru13_bitmaptest_MainActivity_stringFromJNI(JNIEnv* env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

