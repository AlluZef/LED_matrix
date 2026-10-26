// Файл: main.cpp
// Главный файл программы с функциями setup() и loop()
// Объединяет все модули проекта

// ============ ПОДКЛЮЧЕНИЕ БИБЛИОТЕК И МОДУЛЕЙ ============

// Стандартные библиотеки Arduino
#include <Arduino.h>          // Основная библиотека Arduino
#include <ESP8266WiFi.h>      // Wi-Fi для ESP8266
#include <FastLED.h>          // Управление светодиодами
#include <TimeLib.h>          // Работа со временем

// Наши модули
#include "config.h"           // Конфигурации проекта
#include "effects/FireEffect.h" // Эффект огня
#include "effects/TimeEffect.h" // Эффект времени
#include "web/WebServer.h"    // Веб-сервер
#include "utils/NTPClient.h"  // NTP клиент
#include "utils/MatrixUtils.h" // Утилиты матрицы

// ============ ОБЪЯВЛЕНИЕ ГЛОБАЛЬНЫХ ОБЪЕКТОВ ============

// Массив светодиодов матрицы (определяется здесь, объявляется в MatrixUtils.h)
CRGB leds[NUM_LEDS];

// Объекты эффектов
FireEffect fireEffect;
TimeEffect timeEffect;

// ============ ФУНКЦИЯ SETUP() ============
// Выполняется один раз при старте микроконтроллера
void setup() {
    // Инициализация последовательного порта для отладки
    Serial.begin(115200);
    delay(100); // Короткая задержка для стабилизации
    Serial.println("\n\n=== Запуск матрицы 16x16 ===");
    
    // ===== ИНИЦИАЛИЗАЦИЯ СВЕТОДИОДОВ =====
    Serial.println("Инициализация светодиодов...");
    FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(255); // Максимальная яркость контроллера
    FastLED.setMaxPowerInVoltsAndMilliamps(LED_VOLTS, LED_MAX_MA); // Ограничение тока
    FastLED.clear();           // Очищаем матрицу
    FastLED.show();            // Применяем изменения
    Serial.println("Светодиоды инициализированы");
    
    // ===== ИНИЦИАЛИЗАЦИЯ ЭФФЕКТОВ =====
    Serial.println("Инициализация эффектов...");
    fireEffect.init(); // Инициализируем эффект огня
    Serial.println("Эффект огня готов");
    
    // ===== ПОДКЛЮЧЕНИЕ К WI-FI =====
    Serial.print("Подключение к Wi-Fi ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password); // Начинаем подключение
    
    // Ждем подключения
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    
    Serial.println("\n✅ Подключено к Wi-Fi!");
    Serial.print("📡 IP адрес: ");
    Serial.println(WiFi.localIP());
    
    // ===== ИНИЦИАЛИЗАЦИЯ NTP КЛИЕНТА =====
    Serial.println("Инициализация NTP клиента...");
    initNTP(); // Инициализируем NTP клиент
    
    // Устанавливаем провайдера времени и интервал синхронизации
    setSyncProvider(getNtpTime);
    setSyncInterval(3600); // Синхронизировать каждый час (3600 секунд)
    Serial.println("NTP клиент готов");
    
    // ===== ИНИЦИАЛИЗАЦИЯ ВЕБ-СЕРВЕРА =====
    Serial.println("Запуск веб-сервера...");
    initWebServer(); // Инициализируем веб-сервер
    Serial.println("✅ Веб-сервер запущен");
    
    // ===== ВСЕ СИСТЕМЫ ЗАПУЩЕНЫ =====
    Serial.println("\n=== Система готова к работе ===");
    Serial.println("Откройте браузер и перейдите по адресу:");
    Serial.println("http://" + WiFi.localIP().toString());
    Serial.println("================================\n");
}

// ============ ФУНКЦИЯ LOOP() ============
// Выполняется циклически после setup()
void loop() {
    // Обрабатываем веб-запросы (если есть)
    handleWebClient();
    
    // Выбираем и запускаем текущий эффект
    if (currentEffect == "fire") {
        // Режим огня
        // Отображаем изменения только если кадр обновился
        if (fireEffect.update()) {
            FastLED.show();
        }
    } 
    else if (currentEffect == "time") {
        // Режим времени
        timeEffect.update(); // Обновляем отображение времени
        // FastLED.show() вызывается внутри timeEffect.update()
    } 
    else if (currentEffect == "off") {
        // Выключенный режим
        FastLED.clear();     // Очищаем матрицу
        FastLED.show();      // Применяем очистку
        delay(50);           // Небольшая задержка для снижения нагрузки CPU
    }
    
    // Небольшая задержка для стабильности системы
    delay(1);
}