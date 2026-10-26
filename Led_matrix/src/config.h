#ifndef CONFIG_H          // Защита от повторного включения
#define CONFIG_H

// Подключаем необходимые библиотеки
#include <Arduino.h>      // Основная библиотека Arduino

// ============ КОНФИГУРАЦИЯ МАТРИЦЫ ============
#define LED_PIN 4         // Пин подключения ленты/матрицы (D2 на Wemos D1)
#define MATRIX_WIDTH 16   // Ширина матрицы в пикселях
#define MATRIX_HEIGHT 16  // Высота матрицы в пикселях
#define NUM_LEDS (MATRIX_WIDTH * MATRIX_HEIGHT) // Общее количество светодиодов
#define LED_VOLTS 5       // Напряжение питания матрицы (В)
#define LED_MAX_MA 2000   // Максимальный ток блока питания (мА)

// ============ КОНФИГУРАЦИЯ WI-FI ============
extern const char* ssid;
extern const char* password;

// ============ НАСТРОЙКИ NTP (СИНХРОНИЗАЦИЯ ВРЕМЕНИ) ============
extern const char* ntpServerName; // Сервер времени
extern int timeZone;          // Часовой пояс (Москва UTC+3)
extern unsigned int localPort;   // Порт для NTP клиента

// ============ ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ ЭФФЕКТОВ ============
// Объявляем переменные как extern - их реализация будет в config.cpp
extern String currentEffect;    // Текущий выбранный эффект ("fire", "time", "off")
extern int effectIntensity;     // Интенсивность эффекта огня (1-100)
extern int fireHue;             // Цвет огня (0-255 в формате HSV)
extern int timeHue;             // Цвет времени (0-255)
extern int timeBrightness;      // Яркость отображения времени (0-255)

// ============ КОНСТАНТЫ ДЛЯ ЭФФЕКТА ОГНЯ ============
// Маска для формы пламени (хранится в памяти программ)
extern const unsigned char valueMask[8][16] PROGMEM;
// Маска для оттенков пламени
extern const unsigned char hueMask[8][16] PROGMEM;

#endif // Конец CONFIG_H