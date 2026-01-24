#ifndef NTP_CLIENT_H        // Защита от повторного включения
#define NTP_CLIENT_H

// Подключаем необходимые библиотеки
#include <WiFiUdp.h>        // Для UDP соединения с NTP сервером
#include <TimeLib.h>        // Для работы со временем
#include "config.h"         // Наши конфигурации

// ============ ОБЪЯВЛЕНИЕ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ ============
// Объявляем UDP клиент как extern - он определен в NTPClient.cpp
extern WiFiUDP udp;

// ============ ФУНКЦИИ NTP КЛИЕНТА ============

// Инициализация NTP клиента
void initNTP();

// Обновление времени с NTP сервера
void updateTime();

// Получение времени с NTP сервера (внутренняя функция)
time_t getNtpTime();

#endif // Конец NTP_CLIENT_H