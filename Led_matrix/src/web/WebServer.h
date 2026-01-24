#ifndef WEB_SERVER_H        // Защита от повторного включения
#define WEB_SERVER_H

// Подключаем необходимые библиотеки
#include <ESP8266WebServer.h> // Веб-сервер для ESP8266
#include "config.h"          // Наши конфигурации

// ============ ОБЪЯВЛЕНИЕ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ ============
// Объявляем веб-сервер как extern - он определен в WebServer.cpp
extern ESP8266WebServer server;

// ============ ФУНКЦИИ ВЕБ-СЕРВЕРА ============

// Инициализация веб-сервера
void initWebServer();

// Обработка клиентских запросов (вызывается в loop())
void handleWebClient();

#endif // Конец WEB_SERVER_H