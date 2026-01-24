#ifndef FIRE_EFFECT_H      // Защита от повторного включения
#define FIRE_EFFECT_H

// Подключаем необходимые библиотеки
#include <FastLED.h>       // Для работы со светодиодами
#include "config.h"        // Наши конфигурации

// ============ КЛАСС ДЛЯ ЭФФЕКТА ОГНЯ ============
class FireEffect {
public:
    // ===== ПУБЛИЧНЫЕ МЕТОДЫ (интерфейс класса) =====
    
    // Инициализация эффекта огня
    void init();
    
    // Основной метод обновления (вызывается в loop())
    void update();
    
    // Установка интенсивности огня (1-100)
    void setIntensity(int intensity);
    
    // Установка цвета огня (0-255 в формате HSV)
    void setHue(int hue);
    
private:
    // ===== ПРИВАТНЫЕ ПЕРЕМЕННЫЕ (внутреннее состояние) =====
    
    // Буферы для эффекта огня
    unsigned char matrixValue[8][16];  // Текущие значения пикселей
    unsigned char line[MATRIX_WIDTH];  // Генерируемая нижняя строка
    int pcnt = 0;                       // Счетчик для плавности анимации
    
    unsigned long prevTime = 0;         // Время последнего обновления
    
    // ===== ПРИВАТНЫЕ МЕТОДЫ (внутренняя логика) =====
    
    // Генерация новой нижней строки огня
    void generateLine();
    
    // Сдвиг огня вверх по матрице
    void shiftUp();
    
    // Отрисовка кадра огня с учетом плавности
    void drawFireFrame(int pcnt);
    
    // Получение цвета пикселя огня
    CRGB getFireColor(int hueOffset, int value);
};

#endif // Конец FIRE_EFFECT_H