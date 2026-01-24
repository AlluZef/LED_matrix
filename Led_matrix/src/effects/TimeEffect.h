#ifndef TIME_EFFECT_H       // Защита от повторного включения
#define TIME_EFFECT_H

// Подключаем необходимые библиотеки
#include <FastLED.h>        // Для работы со светодиодами
#include <TimeLib.h>        // Для работы со временем
#include "config.h"         // Наши конфигурации

// ============ КЛАСС ДЛЯ ЭФФЕКТА ВРЕМЕНИ ============
class TimeEffect {
public:
    // ===== ПУБЛИЧНЫЕ МЕТОДЫ (интерфейс класса) =====
    
    // Основной метод обновления (вызывается в loop())
    void update();
    
    // Отрисовка текущего времени на матрице
    void drawTime();
    
    // Установка цвета отображения времени (0-255 в формате HSV)
    void setHue(int hue);
    
    // Установка яркости отображения времени (0-255)
    void setBrightness(int brightness);
    
private:
    // ===== ПРИВАТНЫЕ ПЕРЕМЕННЫЕ =====
    unsigned long lastUpdate = 0; // Время последнего обновления
    
    // ===== ПРИВАТНЫЕ МЕТОДЫ (внутренняя логика) =====
    
    // Установка пикселя в системе координат (0,0 - левый нижний угол)
    void setPixelLB(int x, int y, CRGB color);
    
    // Отрисовка цифры размером 3x7 пикселей
    void drawDigit3x7(int startX, int startY, int digit, CRGB color);
};

#endif // Конец TIME_EFFECT_H