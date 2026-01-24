#include "NTPClient.h"      // Подключаем наш заголовочный файл

// ============ ОПРЕДЕЛЕНИЕ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ ============
WiFiUDP udp; // Создаем объект UDP клиента

// ============ КОНСТАНТЫ ДЛЯ NTP ============
const int NTP_PACKET_SIZE = 48; // Размер NTP пакета
byte packetBuffer[NTP_PACKET_SIZE]; // Буфер для NTP пакета

// ============ РЕАЛИЗАЦИЯ ФУНКЦИЙ NTP КЛИЕНТА ============

// Инициализация NTP клиента
void initNTP() {
    udp.begin(localPort); // Начинаем слушать на указанном порту
    Serial.println("NTP клиент инициализирован на порту " + String(localPort));
}

// Отправка NTP запроса на сервер
void sendNTPpacket(const char* address) {
    // Очищаем буфер пакета
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    
    // Заполняем заголовок NTP пакета
    packetBuffer[0] = 0b11100011; // LI=3, Version=4, Mode=3 (клиент)
    packetBuffer[1] = 0;          // Stratum (уровень)
    packetBuffer[2] = 6;          // Polling Interval (интервал опроса)
    packetBuffer[3] = 0xEC;       // Peer Clock Precision (точность)
    
    // 8 bytes нулевого корня дисперсии
    packetBuffer[12] = 49;  // NTP код
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;
    
    // Отправляем пакет на NTP сервер (порт 123)
    udp.beginPacket(address, 123);
    udp.write(packetBuffer, NTP_PACKET_SIZE);
    udp.endPacket();
}

// Получение времени с NTP сервера
time_t getNtpTime() {
    // Очищаем буфер входящих пакетов
    while (udp.parsePacket() > 0);
    
    // Отправляем запрос на NTP сервер
    sendNTPpacket(ntpServerName);
    
    uint32_t beginWait = millis(); // Запоминаем время начала ожидания
    
    // Ждем ответа до 1.5 секунд
    while (millis() - beginWait < 1500) {
        int size = udp.parsePacket(); // Проверяем пришедшие пакеты
        
        if (size >= NTP_PACKET_SIZE) {
            // Читаем пакет в буфер
            udp.read(packetBuffer, NTP_PACKET_SIZE);
            
            // Извлекаем время из пакета (байты 40-43)
            unsigned long secsSince1900;
            secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
            secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
            secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
            secsSince1900 |= (unsigned long)packetBuffer[43];
            
            // Конвертируем время из секунд с 1900 в Unix время (секунды с 1970)
            // 2208988800 = секунд между 1900 и 1970
            // timeZone * SECS_PER_HOUR = поправка на часовой пояс
            return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
        }
        delay(10); // Небольшая задержка перед следующей проверкой
    }
    
    return 0; // Возвращаем 0 при ошибке
}

// Обновление времени с NTP сервера
void updateTime() {
    time_t newTime = getNtpTime(); // Получаем время с сервера
    
    if (newTime) {
        setTime(newTime); // Устанавливаем системное время
        Serial.println("Время успешно получено от NTP сервера");
    } else {
        Serial.println("Ошибка: не удалось получить время от NTP сервера");
    }
}