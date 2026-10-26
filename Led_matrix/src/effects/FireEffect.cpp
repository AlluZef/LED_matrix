#include "FireEffect.h"    // Подключаем заголовок класса
#include "utils/MatrixUtils.h" // Утилиты для работы с матрицей

// ============ РЕАЛИЗАЦИЯ МЕТОДОВ КЛАССА FIRE_EFFECT ============

// Метод инициализации эффекта огня
void FireEffect::init() {
    // Инициализируем буферы нулями
    memset(matrixValue, 0, sizeof(matrixValue));
    
    // Генерируем первую строку огня
    generateLine();
    
    // Сбрасываем счетчик анимации
    pcnt = 0;
    prevTime = millis(); // Запоминаем текущее время
}

// Основной метод обновления (вызывается каждый цикл)
bool FireEffect::update() {
    // Вычисляем скорость обновления в зависимости от интенсивности
    int updateSpeed = map(effectIntensity, 1, 100, 50, 20);
    
    // Проверяем, пора ли обновлять кадр
    if (millis() - prevTime > (unsigned long)updateSpeed) {
        prevTime = millis(); // Обновляем время последнего кадра
        
        // Если достигли 100% интерполяции
        if (pcnt >= 100) {
            shiftUp();        // Сдвигаем огонь вверх
            generateLine();   // Генерируем новую нижнюю строку
            pcnt = 0;         // Сбрасываем счетчик
        }
        
        // Отрисовываем текущий кадр с учетом интерполяции
        drawFireFrame(pcnt);
        
        // Увеличиваем счетчик интерполяции
        pcnt += 30;
        return true;
    }
    return false;
}

// Установка интенсивности огня
void FireEffect::setIntensity(int intensity) {
    effectIntensity = constrain(intensity, 1, 100);
}

// Установка цвета огня
void FireEffect::setHue(int hue) {
    fireHue = constrain(hue, 0, 255);
}

// ============ ПРИВАТНЫЕ МЕТОДЫ ============

// Генерация новой нижней строки огня
void FireEffect::generateLine() {
    for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
        // Вычисляем минимальное и максимальное значение
        int minVal = 64 + map(effectIntensity, 1, 100, 0, 64);
        int maxVal = 128 + map(effectIntensity, 1, 100, 0, 127);
        
        // Генерируем случайное значение в заданном диапазоне
        line[x] = random(minVal, maxVal);
    }
}

// Сдвиг огня вверх по матрице
void FireEffect::shiftUp() {
    // Сдвигаем все строки вверх, начиная с предпоследней
    for (uint8_t y = 7; y > 0; y--) {
        for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
            matrixValue[y][x] = matrixValue[y - 1][x];
        }
    }

    // Копируем сгенерированную строку в самую нижнюю
    for (uint8_t x = 0; x < MATRIX_WIDTH; x++) {
        matrixValue[0][x] = line[x];
    }
}

// Получение цвета пикселя огня
CRGB FireEffect::getFireColor(int hueOffset, int value) {
    // Вычисляем итоговый оттенок с учетом смещения
    int hue = fireHue + hueOffset;
    if (hue < 0) hue += 255;
    if (hue > 255) hue -= 255;
    
    // Создаем цвет в формате HSV
    CRGB color = CHSV(hue, 255, value);
    
    // Корректируем яркость в зависимости от интенсивности
    int brightness = map(effectIntensity, 1, 100, 50, 255);
    color.nscale8(brightness);
    
    return color;
}

// Отрисовка кадра огня с интерполяцией
void FireEffect::drawFireFrame(int pcnt) {
    int nextv; // Значение для интерполяции

    // Отрисовываем нижние 8 строк (основное пламя)
    for (unsigned char y = 7; y > 0; y--) {
        for (unsigned char x = 0; x < MATRIX_WIDTH; x++) {
            // Линейная интерполяция между текущим и следующим значением
            nextv = (((100.0 - pcnt) * matrixValue[y][x] + 
                      pcnt * matrixValue[y - 1][x]) / 100.0) - 
                    pgm_read_byte(&(valueMask[y][x]));

            // Получаем смещение цвета из маски
            int hueOffset = pgm_read_byte(&(hueMask[y][x]));
            // Ограничиваем значение снизу
            int value = max(0, nextv);
            
            // Получаем цвет и устанавливаем пиксель
            CRGB color = getFireColor(hueOffset, value);
            setPixel(x, y, color); // Используем функцию из MatrixUtils
        }
    }

    // Отрисовываем верхние строки для эффекта тления/дыма
    for (unsigned char y = 8; y < MATRIX_HEIGHT; y++) {
        for (unsigned char x = 0; x < MATRIX_WIDTH; x++) {
            if (y == 8) {
                // Первая строка дыма - иногда появляется над пламенем
                if (random(0, 20 + map(effectIntensity, 1, 100, 0, 30)) == 0 && 
                    leds[getPixelIndex(x, y - 1)] != CRGB::Black) {
                    // Берем цвет из пикселя ниже и затемняем его
                    CRGB color = leds[getPixelIndex(x, y - 1)];
                    color.nscale8(100); // Уменьшаем яркость на 60%
                    setPixel(x, y, color);
                } else {
                    // Иначе черный пиксель
                    setPixel(x, y, CRGB::Black);
                }
            } else {
                // Последующие строки дыма - плавное затухание
                CRGB lowerColor = leds[getPixelIndex(x, y - 1)];
                if (lowerColor != CRGB::Black) {
                    CRGB color = lowerColor;
                    // Чем выше строка, тем больше затухание
                    int fade = 150 - (y - 8) * 15;
                    color.nscale8(constrain(fade, 20, 255));
                    setPixel(x, y, color);
                } else {
                    setPixel(x, y, CRGB::Black);
                }
            }
        }
    }

    // Отрисовываем самую нижнюю (первую) строку
    for (unsigned char x = 0; x < MATRIX_WIDTH; x++) {
        int hueOffset = pgm_read_byte(&(hueMask[0][x]));
        // Интерполяция для первой строки
        int value = ((100.0 - pcnt) * matrixValue[0][x] + pcnt * line[x]) / 100.0;
        
        CRGB color = getFireColor(hueOffset, value);
        setPixel(x, 0, color);
    }
}