#include <jni.h>
#include <string>
#include <android/bitmap.h>
#include <android/log.h>

#define  LOG_TAG    "LibBitmap"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_kru13_bitmaptest_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_kru13_bitmaptest_MainActivity_bitmapChange( JNIEnv* env, jobject  obj, jobject img)
{
    AndroidBitmapInfo  info;
    void*              pixels;
    int                ret;
    static int         init;

    if ((ret = AndroidBitmap_getInfo(env, img, &info)) < 0) {
        LOGE("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }

    if ((ret = AndroidBitmap_lockPixels(env, img, &pixels)) < 0) {
        LOGE("AndroidBitmap_lockPixels() failed ! error=%d", ret);
    }


    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("Bitmap format is not RGBA_8888 !");
        return;
    }


    uint32_t**  raw_data = (uint32_t**)pixels;

    int height = info.height;
    int width = info.width;


    LOGI("start");
    LOGI("info height: %d", info.height);
    LOGI("info width : %d", info.width);

    uint32_t* imgp = (uint32_t*)pixels;
    int x,y;

    // TODO: 1) Grayscale
    for ( y = 0; y < info.height; y++)
        for ( x = 0; x < info.width; x++) {
            // imgp[y*info.width+x] = 0xFF00FF00; // ABGR
            uint32_t b = imgp[y*info.width+x] & 0x00FF0000;
            uint32_t g = imgp[y*info.width+x] & 0x0000FF00;
            uint32_t r = imgp[y*info.width+x] & 0x000000FF;
            uint32_t jas = (uint32_t)((float) (r + g + b)/3.f);
            uint32_t finalColor = 0;
            finalColor = (jas & 0x000000FF) | ((jas & 0x000000FF) << 8) | ((jas & 0x000000FF) << 16);
            finalColor |= 0xFF000000;
            imgp[y*info.width+x] = finalColor;
        }

    // TODO: 2) Inverze (B = 255 - B, G = 255 - G, R = 255 - R)
    // TODO: 3) Blur matice 3x3, samé 1, konvoluce

    AndroidBitmap_unlockPixels(env, img);

}
