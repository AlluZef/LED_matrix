#include "WebServer.h"      // Подключаем наш заголовочный файл
#include <ESP8266WiFi.h>    // Для Wi-Fi подключения
#include "web/html_page.h"
#include "utils/NTPClient.h"

// ============ ОПРЕДЕЛЕНИЕ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ ============
ESP8266WebServer server(80); // Создаем веб-сервер на порту 80

// ============ ОБРАБОТЧИКИ ВЕБ-ЗАПРОСОВ ============

// Главная страница - отображение HTML интерфейса
void handleRoot() {
    server.send(200, "text/html", MAIN_page);  // MAIN_page определен в html_page.h
}

// Обработчик для установки настроек
void handleSet() {
    // Получаем и обрабатываем параметры из запроса
    
    // Эффект (огонь, время, выключено)
    if (server.hasArg("effect")) {
        currentEffect = server.arg("effect");
        Serial.println("Установлен эффект: " + currentEffect);
    }
    
    // Яркость огня (1-100)
    if (server.hasArg("fireBrightness")) {
        effectIntensity = server.arg("fireBrightness").toInt();
        effectIntensity = constrain(effectIntensity, 1, 100);
        Serial.println("Яркость огня: " + String(effectIntensity));
    }
    
    // Цвет огня (0-255)
    if (server.hasArg("fireHue")) {
        fireHue = server.arg("fireHue").toInt();
        fireHue = constrain(fireHue, 0, 255);
        Serial.println("Цвет огня: " + String(fireHue));
    }
    
    // Яркость времени (0-100%, преобразуем в 0-255)
    if (server.hasArg("timeBrightness")) {
        int tempBrightness = server.arg("timeBrightness").toInt();
        tempBrightness = constrain(tempBrightness, 0, 100);
        timeBrightness = map(tempBrightness, 0, 100, 0, 255);
        Serial.println("Яркость времени: " + String(timeBrightness));
    }
    
    // Цвет времени (0-255)
    if (server.hasArg("timeHue")) {
        timeHue = server.arg("timeHue").toInt();
        timeHue = constrain(timeHue, 0, 255);
        Serial.println("Цвет времени: " + String(timeHue));
    }
    
    // Перенаправляем на главную страницу
    server.sendHeader("Location", "/");
    server.send(303); // Код 303 See Other
}

// Обработчик для обновления времени
void handleUpdateTime() {
    updateTime(); // Вызываем функцию обновления времени
    server.send(200, "text/plain", "Время обновлено");
}

// ============ ОСНОВНЫЕ ФУНКЦИИ ВЕБ-СЕРВЕРА ============

// Инициализация веб-сервера
void initWebServer() {
    // Настраиваем маршруты (URL пути) и их обработчики
    server.on("/", handleRoot);           // Главная страница
    server.on("/set", handleSet);         // Установка настроек
    server.on("/updatetime", handleUpdateTime); // Обновление времени
    
    // Запускаем сервер
    server.begin();
    Serial.println("HTTP сервер запущен на порту 80");
    Serial.println("IP адрес: " + WiFi.localIP().toString());
}

// Обработка клиентских запросов (вызывается в loop())
void handleWebClient() {
    server.handleClient(); // Обрабатываем входящие запросы
}