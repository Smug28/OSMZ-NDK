//
// Created by smug2 on 09.04.2017.
//

#ifndef OSMZ_NDK_BITMAP_UTILS_H
#define OSMZ_NDK_BITMAP_UTILS_H

#include "utils.h"
#include <android/bitmap.h>
#include "Color4.h"

void transformGrayscale(uint32_t* imgp, int width, int height){
    // TODO: 1) Grayscale
    int x, y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            imgp[y * width + x] = Color4(imgp[y * width + x]).getGrayscale();
        }
    }
}

void transformInverse(uint32_t* imgp, int width, int height){
    // TODO: 2) Inverze (B = 255 - B, G = 255 - G, R = 255 - R)
    int x, y;
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            imgp[y * width + x] = Color4(imgp[y * width + x]).getInverse();
        }
    }
}

void transformBlur(uint32_t* imgp, int width, int height){
    // TODO: 3) Blur matice 3x3, samé 1, konvoluce
    uint32_t* original_img = new uint32_t[width * height];
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < (width * height); i++)
            original_img[i] = imgp[i];

        float matrix[] = {
                1.f, 4.f, 6.f, 4.f, 1.f,
                4.f, 16.f, 24.f, 16.f, 4.f,
                6.f, 24.f, 36.f, 24.f, 6.f,
                4.f, 16.f, 24.f, 16.f, 4.f,
                1.f, 4.f, 6.f, 4.f, 1.f
        };
        int x, y;
        for (y = 2; y < height - 2; y++) {
            for (x = 2; x < width - 2; x++) {
                float sumR = 0, sumG = 0, sumB = 0;
                for (int i = -2; i <= 2; i++) {
                    for (int j = -2; j <= 2; j++) {
                        Color4 pixel = Color4(original_img[(y + i) * width + (x + j)]);

                        sumR += (((float) pixel.getR()) * matrix[(i + 2) * 5 + (j + 2)]) / 255.f;
                        sumG += (((float) pixel.getG()) * matrix[(i + 2) * 5 + (j + 2)]) / 255.f;
                        sumB += (((float) pixel.getB()) * matrix[(i + 2) * 5 + (j + 2)]) / 255.f;
                    }
                }
                imgp[y * width + x] = Color4((uint32_t) sumR, (uint32_t) sumG, (uint32_t) sumB, 255).getColor();
            }
        }
    }
    delete[] original_img;
}

void imageTransform(JNIEnv* env, jobject img, void (*transform)(uint32_t*, int, int)){
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

    transform(imgp, width, height);
    AndroidBitmap_unlockPixels(env, img);
}

#endif //OSMZ_NDK_BITMAP_UTILS_H
