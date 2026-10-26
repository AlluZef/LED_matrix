#ifndef CLAUDE_EFFECT_H     // Защита от повторного включения
#define CLAUDE_EFFECT_H

// Подключаем необходимые библиотеки
#include <FastLED.h>        // Для работы со светодиодами
#include "config.h"         // Наши конфигурации

// ============ КЛАСС ДЛЯ ЭФФЕКТА "АВАТАР CLAUDE" ============
// Краб Claude 16x10 внизу матрицы, над головой 6 строк для значков
class ClaudeEffect {
public:
    // ===== ПУБЛИЧНЫЕ МЕТОДЫ (интерфейс класса) =====

    // Инициализация эффекта
    void init();

    // Основной метод обновления (вызывается в loop())
    // Возвращает true, если был отрисован новый кадр
    bool update();

private:
    // ===== ТИПЫ =====

    // Эмоции аватара (после каждой эмоции возвращаемся в NEUTRAL)
    enum Emotion {
        NEUTRAL,      // Спокойствие с морганием
        LOOK,         // Оглядывается по сторонам
        HAPPY,        // Радуется и подпрыгивает
        DANCE,        // Танцует: руки и ноги по очереди
        WAVE,         // Машет рукой
        SURPRISED,    // Удивление со знаком "!"
        LOVE,         // Сердечко над головой
        SLEEPY,       // Спит, над головой "z"
        EMOTION_COUNT // Количество эмоций
    };

    // Форма глаз
    enum EyeShape {
        EYES_OPEN,    // Обычные глаза 1x2
        EYES_CLOSED,  // Закрытые глаза (линия)
        EYES_HAPPY,   // Довольные глаза "^"
        EYES_WIDE     // Широко открытые глаза 2x2
    };

    // ===== ПРИВАТНЫЕ ПЕРЕМЕННЫЕ (внутреннее состояние) =====
    Emotion emotion = NEUTRAL;          // Текущая эмоция
    unsigned long emotionStart = 0;     // Время начала эмоции
    unsigned long emotionDuration = 0;  // Длительность эмоции (мс)
    unsigned long nextBlink = 0;        // Время следующего моргания
    unsigned long prevTime = 0;         // Время последнего кадра

    // ===== ПРИВАТНЫЕ МЕТОДЫ (внутренняя логика) =====

    // Установка эмоции и ее длительности
    void setEmotion(Emotion e);

    // Выбор следующей эмоции
    void chooseNextEmotion();

    // Отрисовка кадра для текущей эмоции
    void drawFrame(unsigned long now);

    // Отрисовка тела краба (top - верхняя строка спрайта)
    void drawBody(int top, bool leftArmUp, bool rightArmUp, uint8_t legPhase, CRGB color);

    // Отрисовка глаз (dx - смещение взгляда по горизонтали)
    void drawEyes(int top, EyeShape shape, int dx);

    // Отрисовка значка шириной до 8 пикселей из PROGMEM
    void drawIcon(const uint8_t* rows, int height, int left, int top, CRGB color);

    // Установка пикселя в системе координат (0,0 - левый верхний угол)
    void setPixelTop(int x, int y, CRGB color);
};

#endif // Конец CLAUDE_EFFECT_H
