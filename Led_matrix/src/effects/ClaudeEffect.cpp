#include "ClaudeEffect.h"   // Подключаем заголовок класса
#include "utils/MatrixUtils.h" // Утилиты для работы с матрицей

// ============ КОНСТАНТЫ ЭФФЕКТА ============
#define CLAUDE_FRAME_MS 50      // Интервал между кадрами (мс), ~20 кадров/с
#define CLAUDE_SPRITE_TOP 6     // Верхняя строка спрайта (спрайт прижат к низу)
#define CLAUDE_SPRITE_HEIGHT 10 // Высота спрайта

// Цвета
static const CRGB BODY_COLOR = CRGB(217, 119, 87); // Фирменный оранжевый Claude #D97757
static const CRGB Z_COLOR = CRGB(120, 160, 255);   // Буква "z" во сне
static const CRGB EXCL_COLOR = CRGB(255, 200, 0);  // Знак "!"
static const CRGB HEART_COLOR = CRGB(255, 40, 60); // Сердечко

// Спрайт краба 16x10: одна строка = 16 бит, старший бит - левый пиксель (x = 0)
static const uint16_t CLAUDE_SPRITE[CLAUDE_SPRITE_HEIGHT] PROGMEM = {
    0x3FFC, // ..############..
    0x3FFC, // ..############..
    0x3FFC, // ..############..  (строки 2-3 - глаза)
    0x3FFC, // ..############..
    0xFFFF, // ################  (строки 4-5 - руки)
    0xFFFF, // ################
    0x3FFC, // ..############..
    0x3FFC, // ..############..
    0x1428, // ...#.#....#.#...  (строки 8-9 - ноги)
    0x1428  // ...#.#....#.#...
};

// Маски рук и ног
#define ARM_LEFT  0xC000 // Столбцы 0-1
#define ARM_RIGHT 0x0003 // Столбцы 14-15
#define LEGS_A    0x1020 // Ноги в столбцах 3 и 10
#define LEGS_B    0x0408 // Ноги в столбцах 5 и 12

// Значки шириной до 8 пикселей: одна строка = 8 бит, старший бит - левый пиксель
static const uint8_t ICON_HEART[5] PROGMEM = {0x66, 0xFF, 0x7E, 0x3C, 0x18};
static const uint8_t ICON_EXCL[5] PROGMEM = {0xC0, 0xC0, 0xC0, 0x00, 0xC0};
static const uint8_t ICON_Z[3] PROGMEM = {0xE0, 0x40, 0xE0};

// ============ РЕАЛИЗАЦИЯ МЕТОДОВ КЛАССА CLAUDE_EFFECT ============

// Метод инициализации эффекта
void ClaudeEffect::init() {
    setEmotion(NEUTRAL);
    nextBlink = millis() + 2000; // Первое моргание через 2 секунды
    prevTime = 0;
}

// Основной метод обновления (вызывается каждый цикл)
bool ClaudeEffect::update() {
    unsigned long now = millis();

    // Проверяем, пора ли рисовать новый кадр
    if (now - prevTime < CLAUDE_FRAME_MS) {
        return false;
    }
    prevTime = now;

    // Эмоция закончилась - выбираем следующую
    if (now - emotionStart >= emotionDuration) {
        chooseNextEmotion();
    }

    drawFrame(now);
    return true;
}

// ============ ПРИВАТНЫЕ МЕТОДЫ ============

// Установка эмоции и ее длительности
void ClaudeEffect::setEmotion(Emotion e) {
    emotion = e;
    emotionStart = millis();

    switch (emotion) {
        case NEUTRAL:   emotionDuration = random(4000, 8000); break;
        case LOOK:      emotionDuration = 2800; break; // Один цикл: влево - центр - вправо - центр
        case HAPPY:     emotionDuration = 2000; break;
        case DANCE:     emotionDuration = 3600; break;
        case WAVE:      emotionDuration = 2400; break;
        case SURPRISED: emotionDuration = 1500; break;
        case LOVE:      emotionDuration = 3000; break;
        case SLEEPY:    emotionDuration = 8000; break;
        default:        emotionDuration = 3000; break;
    }
}

// Выбор следующей эмоции: между эмоциями всегда возвращаемся в NEUTRAL
void ClaudeEffect::chooseNextEmotion() {
    if (emotion != NEUTRAL) {
        setEmotion(NEUTRAL);
    } else {
        setEmotion((Emotion)random(NEUTRAL + 1, EMOTION_COUNT));
    }
}

// Отрисовка кадра для текущей эмоции
void ClaudeEffect::drawFrame(unsigned long now) {
    unsigned long t = now - emotionStart; // Время с начала эмоции

    // Параметры кадра по умолчанию
    int top = CLAUDE_SPRITE_TOP; // Верхняя строка спрайта (меньше - выше)
    bool leftArmUp = false;
    bool rightArmUp = false;
    uint8_t legPhase = 0;        // 0 - все ноги на месте, 1/2 - поднята пара ног
    EyeShape eyes = EYES_OPEN;
    int lookDx = 0;              // Смещение взгляда
    uint8_t level = 255;         // Яркость тела

    // Моргание: глаза закрыты 150 мс, затем следующее через 2-5 секунд
    bool blinking = now >= nextBlink;
    if (now >= nextBlink + 150) {
        nextBlink = now + random(2000, 5000);
    }

    FastLED.clear();

    switch (emotion) {
        case LOOK: {
            // Фазы по 700 мс: влево, центр, вправо, центр
            int phase = (t / 700) % 4;
            if (phase == 0) lookDx = -1;
            if (phase == 2) lookDx = 1;
            break;
        }

        case HAPPY:
            eyes = EYES_HAPPY;
            if ((t / 250) % 2) top--; // Подпрыгивание
            break;

        case DANCE: {
            // Руки и ноги по очереди каждые 300 мс, подпрыгивание каждые 150 мс
            int beat = (t / 300) % 2;
            leftArmUp = (beat == 0);
            rightArmUp = (beat == 1);
            legPhase = beat + 1;
            eyes = EYES_HAPPY;
            if ((t / 150) % 2) top--;
            break;
        }

        case WAVE:
            rightArmUp = (t / 300) % 2;
            break;

        case SURPRISED:
            eyes = EYES_WIDE;
            if (t < 200) top--; // Вздрагивание в начале
            if ((t / 250) % 2 == 0) {
                drawIcon(ICON_EXCL, 5, 7, 0, EXCL_COLOR);
            }
            break;

        case LOVE: {
            eyes = EYES_HAPPY;
            // Пульсация сердечка, период ~0.8 с
            CRGB heart = HEART_COLOR;
            heart.nscale8(120 + scale8(sin8(t / 3), 135));
            drawIcon(ICON_HEART, 5, 4, 0, heart);
            break;
        }

        case SLEEPY:
            eyes = EYES_CLOSED;
            // Дыхание: яркость тела плавно меняется, период ~3 с
            level = 140 + scale8(sin8(t / 12), 115);
            // Две буквы "z" поднимаются вверх со сдвигом в половину периода
            for (int i = 0; i < 2; i++) {
                int ph = (t + i * 1000) % 2000;
                CRGB z = Z_COLOR;
                z.nscale8(255 - ph * 200 / 2000);
                drawIcon(ICON_Z, 3, 10 + ph * 3 / 2000, 3 - ph * 4 / 2000, z);
            }
            break;

        default: // NEUTRAL
            break;
    }

    // Моргаем только открытыми глазами
    if (eyes == EYES_OPEN && blinking) {
        eyes = EYES_CLOSED;
    }

    CRGB body = BODY_COLOR;
    body.nscale8(level);

    drawBody(top, leftArmUp, rightArmUp, legPhase, body);
    drawEyes(top, eyes, lookDx);
}

// Отрисовка тела краба
void ClaudeEffect::drawBody(int top, bool leftArmUp, bool rightArmUp, uint8_t legPhase, CRGB color) {
    for (int row = 0; row < CLAUDE_SPRITE_HEIGHT; row++) {
        uint16_t mask = pgm_read_word(&CLAUDE_SPRITE[row]);

        // Поднятая рука переезжает со строк 4-5 на строки 2-3
        if (row == 4 || row == 5) {
            if (leftArmUp) mask &= ~ARM_LEFT;
            if (rightArmUp) mask &= ~ARM_RIGHT;
        }
        if (row == 2 || row == 3) {
            if (leftArmUp) mask |= ARM_LEFT;
            if (rightArmUp) mask |= ARM_RIGHT;
        }

        // Поднятая нога становится короче на 1 пиксель
        if (row == 9) {
            if (legPhase == 1) mask &= ~LEGS_A;
            if (legPhase == 2) mask &= ~LEGS_B;
        }

        for (int x = 0; x < MATRIX_WIDTH; x++) {
            if (mask & (0x8000 >> x)) {
                setPixelTop(x, top + row, color);
            }
        }
    }
}

// Отрисовка глаз (черные пиксели поверх тела)
void ClaudeEffect::drawEyes(int top, EyeShape shape, int dx) {
    int y = top + 2; // Глаза в строках 2-3 спрайта

    switch (shape) {
        case EYES_OPEN:
            setPixelTop(4 + dx, y, CRGB::Black);
            setPixelTop(4 + dx, y + 1, CRGB::Black);
            setPixelTop(11 + dx, y, CRGB::Black);
            setPixelTop(11 + dx, y + 1, CRGB::Black);
            break;

        case EYES_CLOSED:
            setPixelTop(3, y + 1, CRGB::Black);
            setPixelTop(4, y + 1, CRGB::Black);
            setPixelTop(11, y + 1, CRGB::Black);
            setPixelTop(12, y + 1, CRGB::Black);
            break;

        case EYES_HAPPY:
            // Глаза в форме "^"
            setPixelTop(3, y + 1, CRGB::Black);
            setPixelTop(4, y, CRGB::Black);
            setPixelTop(5, y + 1, CRGB::Black);
            setPixelTop(10, y + 1, CRGB::Black);
            setPixelTop(11, y, CRGB::Black);
            setPixelTop(12, y + 1, CRGB::Black);
            break;

        case EYES_WIDE:
            for (int i = 0; i < 2; i++) {
                setPixelTop(3, y + i, CRGB::Black);
                setPixelTop(4, y + i, CRGB::Black);
                setPixelTop(11, y + i, CRGB::Black);
                setPixelTop(12, y + i, CRGB::Black);
            }
            break;
    }
}

// Отрисовка значка шириной до 8 пикселей из PROGMEM
void ClaudeEffect::drawIcon(const uint8_t* rows, int height, int left, int top, CRGB color) {
    for (int row = 0; row < height; row++) {
        uint8_t bits = pgm_read_byte(&rows[row]);
        for (int col = 0; col < 8; col++) {
            if (bits & (0x80 >> col)) {
                setPixelTop(left + col, top + row, color);
            }
        }
    }
}

// Установка пикселя в системе координат (0,0 - левый верхний угол)
void ClaudeEffect::setPixelTop(int x, int y, CRGB color) {
    // В setPixel() y = 0 - нижняя строка (так рисуется основание огня)
    setPixel(x, MATRIX_HEIGHT - 1 - y, color);
}
