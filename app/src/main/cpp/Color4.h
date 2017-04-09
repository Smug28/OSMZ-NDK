//
// Created by smug2 on 09.04.2017.
//

#ifndef OSMZ_NDK_COLOR4_H
#define OSMZ_NDK_COLOR4_H

#include <stdint.h>

class Color4 {
private:
    uint32_t a;
    uint32_t b;
    uint32_t g;
    uint32_t r;

    inline uint32_t getColor(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha){
        uint32_t result = alpha << 32;
        result |= (blue << 16);
        result |= (green << 8);
        result |= red;
        return result;
    }
public:
    Color4(uint32_t abgr){
        a = (abgr & 0xFF000000) >> 32;
        b = (abgr & 0x00FF0000) >> 16;
        g = (abgr & 0x0000FF00) >> 8;
        r = abgr & 0x000000FF;
    }
    Color4(uint32_t red, uint32_t green, uint32_t blue, uint32_t alpha){
        a = alpha & 0xFF;
        b = blue & 0xFF;
        g = green & 0xFF;
        r = red & 0xFF;
    }
    inline uint32_t getR(){
        return r;
    }
    inline uint32_t getG(){
        return g;
    }
    inline uint32_t getB(){
        return b;
    }
    inline uint32_t getA(){
        return a;
    }
    inline uint32_t setR(uint32_t red){
        r = red & 0xFF;
    }
    inline uint32_t setG(uint32_t green){
        g = green & 0xFF;
    }
    inline uint32_t setB(uint32_t blue){
        b = blue & 0xFF;
    }
    inline uint32_t setA(uint32_t alpha){
        a = alpha & 0xFF;
    }
    inline uint32_t getColor(){
        return getColor(r, g, b, a);
    }
    inline uint32_t getGrayscale(){
        uint32_t y = 0;
        y = (uint32_t)(0.299f * (float) r + 0.587f * (float) g + 0.114f * (float) b);
        if (y > 0xFF)
            y = 0xFF;
        return getColor(y, y, y, a);
    }
    inline uint32_t getInverse(){
        return getColor(0xFF - r, 0xFF - g, 0xFF - b, 0xFF - a);
    }
};

#endif //OSMZ_NDK_COLOR4_H
