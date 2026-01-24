// Автоматически сгенерированный файл из HTML
// Не редактировать вручную!

#ifndef HTML_PAGE_H
#define HTML_PAGE_H

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Матрица 16×16</title>
    <style>
        body { 
            font-family: Arial, sans-serif; 
            margin: 20px; 
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
        }
        .container { 
            max-width: 600px; 
            background: white; 
            padding: 30px; 
            border-radius: 15px; 
            box-shadow: 0 10px 30px rgba(0,0,0,0.2);
        }
        h1 { 
            color: #333; 
            text-align: center;
            margin-bottom: 30px;
            padding-bottom: 15px;
            border-bottom: 3px solid #ff5722;
        }
        .control { 
            margin: 20px 0; 
            padding: 15px;
            background: #f8f9fa;
            border-radius: 8px;
        }
        label { 
            display: block; 
            margin-bottom: 8px; 
            font-weight: bold;
            color: #555;
        }
        select, input[type="range"] { 
            width: 100%; 
            padding: 10px;
            margin: 5px 0;
            border: 1px solid #ddd;
            border-radius: 6px;
            font-size: 16px;
        }
        input[type="range"] { 
            height: 10px;
            -webkit-appearance: none;
            border: none;
            padding: 0;
        }
        /* Серые ползунки */
        .gray-slider {
            background: linear-gradient(to right, #e0e0e0, #b0b0b0);
        }
        input[type="range"]::-webkit-slider-thumb {
            -webkit-appearance: none;
            width: 24px;
            height: 24px;
            background: #666;
            border: 2px solid #444;
            border-radius: 50%;
            cursor: pointer;
            box-shadow: 0 2px 5px rgba(0,0,0,0.2);
        }
        .value-display { 
            display: inline-block; 
            width: 40px; 
            text-align: center;
            font-weight: bold; 
            color: #333;
            font-size: 1.2em;
            margin-left: 10px;
        }
        .color-preview {
            width: 40px;
            height: 40px;
            border-radius: 50%;
            display: inline-block;
            margin-left: 15px;
            vertical-align: middle;
            border: 2px solid #ddd;
            box-shadow: 0 2px 5px rgba(0,0,0,0.1);
            transition: background 0.3s;
        }
        .button-group {
            display: flex;
            gap: 10px;
            margin-top: 10px;
        }
        button { 
            flex: 1;
            padding: 12px;
            border: none;
            border-radius: 6px;
            cursor: pointer;
            font-size: 16px;
            font-weight: bold;
            transition: all 0.3s;
        }
        #applyBtn {
            background: linear-gradient(to right, #4CAF50, #2E7D32);
            color: white;
        }
        #applyBtn:hover {
            transform: translateY(-2px);
            box-shadow: 0 5px 15px rgba(76, 175, 80, 0.4);
        }
        #updateTimeBtn {
            background: linear-gradient(to right, #2196F3, #0D47A1);
            color: white;
        }
        #updateTimeBtn:hover {
            background: linear-gradient(to right, #1E88E5, #0D47A1);
        }
        #offBtn {
            background: linear-gradient(to right, #f44336, #c62828);
            color: white;
        }
        #offBtn:hover {
            background: linear-gradient(to right, #e53935, #b71c1c);
        }
        .status {
            margin-top: 20px;
            padding: 15px;
            border-radius: 8px;
            text-align: center;
            font-weight: bold;
            transition: all 0.3s;
        }
        .status.ready {
            background: #e8f5e9;
            color: #2e7d32;
        }
        .status.error {
            background: #ffebee;
            color: #c62828;
        }
        .status.info {
            background: #e3f2fd;
            color: #1565c0;
        }
        .info {
            font-size: 14px;
            color: #666;
            margin-top: 5px;
            text-align: center;
        }
        .mode-indicator {
            text-align: center;
            font-size: 18px;
            font-weight: bold;
            margin: 10px 0;
            padding: 10px;
            border-radius: 6px;
            background: #f0f0f0;
        }
        .fire-indicator {
            color: #ff5722;
            border-left: 4px solid #ff5722;
        }
        .time-indicator {
            color: #2196F3;
            border-left: 4px solid #2196F3;
        }
        .off-indicator {
            color: #666;
            border-left: 4px solid #666;
        }
        .color-wheel {
            width: 120px;
            height: 120px;
            border-radius: 50%;
            margin: 15px auto;
            cursor: pointer;
            border: 3px solid #ddd;
            background: conic-gradient(
                from 90deg,
                #ff0000, #ff8000, #ffff00, #80ff00,
                #00ff00, #00ff80, #00ffff, #0080ff,
                #0000ff, #8000ff, #ff00ff, #ff0080, #ff0000
            );
            position: relative;
        }
        .color-wheel::after {
            content: '';
            position: absolute;
            width: 20px;
            height: 20px;
            background: white;
            border: 2px solid #333;
            border-radius: 50%;
            top: 50%;
            left: 50%;
            transform: translate(-50%, -50%);
        }
        .color-wheel-indicator {
            position: absolute;
            width: 30px;
            height: 30px;
            background: white;
            border: 3px solid #333;
            border-radius: 50%;
            transform: translate(-50%, -50%);
            pointer-events: none;
            box-shadow: 0 0 5px rgba(0,0,0,0.5);
        }
    </style>
</head>
<body>
    <div class="container">
        <h1>Матрица 16×16</h1>
        
        <div class="control">
            <label>Режим:</label>
            <select name="effect" id="effect">
                <option value="fire">🔥 Огонь</option>
                <option value="time">🕒 Время</option>
                <option value="off">⚫ Выключено</option>
            </select>
        </div>
        
        <div id="fireSettings" class="control">
            <div class="mode-indicator fire-indicator">Режим: Огонь</div>
            
            <label>Яркость огня: <span id="fireBrightnessValue" class="value-display">50</span>%</label>
            <input type="range" name="fireBrightness" id="fireBrightness" class="gray-slider" min="1" max="100" value="50">
            
            <label>Цвет огня:</label>
            <div class="color-wheel" id="fireColorWheel">
                <div class="color-wheel-indicator" id="fireColorIndicator"></div>
            </div>
            <input type="hidden" name="fireHue" id="fireHue" value="5">
        </div>
        
        <div id="timeSettings" class="control" style="display: none;">
            <div class="mode-indicator time-indicator">Режим: Время</div>
            
            <label>Яркость времени: <span id="timeBrightnessValue" class="value-display">78</span>%</label>
            <input type="range" name="timeBrightness" id="timeBrightness" class="gray-slider" min="0" max="100" value="78">
            
            <label>Цвет времени:</label>
            <div class="color-wheel" id="timeColorWheel">
                <div class="color-wheel-indicator" id="timeColorIndicator"></div>
            </div>
            <input type="hidden" name="timeHue" id="timeHue" value="200">
        </div>
        
        <div class="button-group">
            <button id="applyBtn">Применить</button>
            <button id="updateTimeBtn">Обновить время</button>
            <button id="offBtn">Выключить</button>
        </div>
        
        <div class="status ready" id="status">Готов к работе</div>
    </div>
    
    <script>
        // Глобальные переменные для цветовых кругов
        let fireColorWheel = null;
        let timeColorWheel = null;
        let fireColorIndicator = null;
        let timeColorIndicator = null;
        let fireHueInput = null;
        let timeHueInput = null;
        
        // Функция для получения цвета из цветового круга
        function getHueFromWheel(event, wheel, indicator, hueInput) {
            const rect = wheel.getBoundingClientRect();
            const x = event.clientX - rect.left;
            const y = event.clientY - rect.top;
            
            const centerX = rect.width / 2;
            const centerY = rect.height / 2;
            
            const deltaX = x - centerX;
            const deltaY = y - centerY;
            
            // Вычисляем угол
            let angle = Math.atan2(deltaY, deltaX) * 180 / Math.PI;
            if (angle < 0) angle += 360;
            
            // Преобразуем угол в hue (0-255)
            let hue = Math.round(angle * 255 / 360);
            
            // Ограничиваем радиус
            const radius = Math.sqrt(deltaX * deltaX + deltaY * deltaY);
            const maxRadius = Math.min(centerX, centerY) - 15;
            
            if (radius > maxRadius) {
                // За пределами круга - перемещаем к границе
                const scale = maxRadius / radius;
                const limitedX = centerX + deltaX * scale;
                const limitedY = centerY + deltaY * scale;
                
                indicator.style.left = limitedX + 'px';
                indicator.style.top = limitedY + 'px';
            } else {
                indicator.style.left = x + 'px';
                indicator.style.top = y + 'px';
            }
            
            hueInput.value = hue;
            updateColorIndicator(indicator, hue);
            
            return hue;
        }
        
        // Функция обновления индикатора цвета
        function updateColorIndicator(indicator, hue) {
            const hsl = `hsl(${Math.round(hue * 360 / 255)}, 100%, 50%)`;
            indicator.style.background = hsl;
        }
        
        // Функция установки позиции индикатора на цветовом круге
        function setIndicatorPosition(wheel, indicator, hue) {
            const angle = hue * 360 / 255;
            const radians = angle * Math.PI / 180;
            const radius = Math.min(wheel.offsetWidth, wheel.offsetHeight) / 2 - 20;
            
            const centerX = wheel.offsetWidth / 2;
            const centerY = wheel.offsetHeight / 2;
            
            const x = centerX + radius * Math.cos(radians);
            const y = centerY + radius * Math.sin(radians);
            
            indicator.style.left = x + 'px';
            indicator.style.top = y + 'px';
            updateColorIndicator(indicator, hue);
        }
        
        // Инициализация цветовых кругов
        function initColorWheels() {
            fireColorWheel = document.getElementById('fireColorWheel');
            timeColorWheel = document.getElementById('timeColorWheel');
            fireColorIndicator = document.getElementById('fireColorIndicator');
            timeColorIndicator = document.getElementById('timeColorIndicator');
            fireHueInput = document.getElementById('fireHue');
            timeHueInput = document.getElementById('timeHue');
            
            // Устанавливаем начальные позиции
            setIndicatorPosition(fireColorWheel, fireColorIndicator, parseInt(fireHueInput.value) || 5);
            setIndicatorPosition(timeColorWheel, timeColorIndicator, parseInt(timeHueInput.value) || 200);
            
            // Обработчики для круга огня
            let isFireDragging = false;
            fireColorWheel.addEventListener('mousedown', (e) => {
                isFireDragging = true;
                getHueFromWheel(e, fireColorWheel, fireColorIndicator, fireHueInput);
            });
            
            fireColorWheel.addEventListener('mousemove', (e) => {
                if (isFireDragging) {
                    getHueFromWheel(e, fireColorWheel, fireColorIndicator, fireHueInput);
                }
            });
            
            fireColorWheel.addEventListener('mouseup', () => {
                isFireDragging = false;
                // Автоматически применяем, если выбран режим огня
                if (document.getElementById('effect').value === 'fire') {
                    applySettings();
                }
            });
            
            fireColorWheel.addEventListener('mouseleave', () => {
                isFireDragging = false;
            });
            
            // Обработчики для круга времени
            let isTimeDragging = false;
            timeColorWheel.addEventListener('mousedown', (e) => {
                isTimeDragging = true;
                getHueFromWheel(e, timeColorWheel, timeColorIndicator, timeHueInput);
            });
            
            timeColorWheel.addEventListener('mousemove', (e) => {
                if (isTimeDragging) {
                    getHueFromWheel(e, timeColorWheel, timeColorIndicator, timeHueInput);
                }
            });
            
            timeColorWheel.addEventListener('mouseup', () => {
                isTimeDragging = false;
                // Автоматически применяем, если выбран режим времени
                if (document.getElementById('effect').value === 'time') {
                    applySettings();
                }
            });
            
            timeColorWheel.addEventListener('mouseleave', () => {
                isTimeDragging = false;
            });
            
            // Поддержка сенсорных устройств
            fireColorWheel.addEventListener('touchstart', (e) => {
                e.preventDefault();
                isFireDragging = true;
                getHueFromWheel(e.touches[0], fireColorWheel, fireColorIndicator, fireHueInput);
            });
            
            fireColorWheel.addEventListener('touchmove', (e) => {
                e.preventDefault();
                if (isFireDragging) {
                    getHueFromWheel(e.touches[0], fireColorWheel, fireColorIndicator, fireHueInput);
                }
            });
            
            fireColorWheel.addEventListener('touchend', () => {
                isFireDragging = false;
                if (document.getElementById('effect').value === 'fire') {
                    applySettings();
                }
            });
            
            timeColorWheel.addEventListener('touchstart', (e) => {
                e.preventDefault();
                isTimeDragging = true;
                getHueFromWheel(e.touches[0], timeColorWheel, timeColorIndicator, timeHueInput);
            });
            
            timeColorWheel.addEventListener('touchmove', (e) => {
                e.preventDefault();
                if (isTimeDragging) {
                    getHueFromWheel(e.touches[0], timeColorWheel, timeColorIndicator, timeHueInput);
                }
            });
            
            timeColorWheel.addEventListener('touchend', () => {
                isTimeDragging = false;
                if (document.getElementById('effect').value === 'time') {
                    applySettings();
                }
            });
        }
        
        // Обновление значения ползунков
        document.getElementById('fireBrightness').addEventListener('input', function() {
            document.getElementById('fireBrightnessValue').textContent = this.value;
        });
        
        document.getElementById('timeBrightness').addEventListener('input', function() {
            document.getElementById('timeBrightnessValue').textContent = this.value;
        });
        
        // Показ/скрытие настроек в зависимости от режима
        document.getElementById('effect').addEventListener('change', function() {
            const effect = this.value;
            const fireSettings = document.getElementById('fireSettings');
            const timeSettings = document.getElementById('timeSettings');
            const status = document.getElementById('status');
            
            if (effect === 'fire') {
                fireSettings.style.display = 'block';
                timeSettings.style.display = 'none';
                status.textContent = 'Режим огня';
                status.className = 'status info';
            } else if (effect === 'time') {
                fireSettings.style.display = 'none';
                timeSettings.style.display = 'block';
                status.textContent = 'Режим времени';
                status.className = 'status info';
            } else {
                fireSettings.style.display = 'none';
                timeSettings.style.display = 'none';
                status.textContent = 'Матрица выключена';
                status.className = 'status ready';
            }
        });
        
        // Функция отправки настроек
        function applySettings() {
            const effect = document.getElementById('effect').value;
            const fireBrightness = document.getElementById('fireBrightness').value;
            const fireHue = document.getElementById('fireHue').value;
            const timeBrightness = document.getElementById('timeBrightness').value;
            const timeHue = document.getElementById('timeHue').value;
            
            const status = document.getElementById('status');
            status.textContent = 'Отправка настроек...';
            status.className = 'status info';
            
            const params = new URLSearchParams({
                effect: effect,
                fireBrightness: fireBrightness,
                fireHue: fireHue,
                timeBrightness: timeBrightness,
                timeHue: timeHue
            });
            
            fetch('/set?' + params.toString())
                .then(response => {
                    if (response.ok) {
                        status.textContent = effect === 'off' ? 'Матрица выключена' : 'Настройки применены!';
                        status.className = 'status ready';
                        
                        // Сохраняем в localStorage
                        localStorage.setItem('matrixSettings', JSON.stringify({
                            effect: effect,
                            fireBrightness: fireBrightness,
                            fireHue: fireHue,
                            timeBrightness: timeBrightness,
                            timeHue: timeHue
                        }));
                        
                        setTimeout(() => {
                            status.textContent = 'Готов к работе';
                        }, 2000);
                    } else {
                        throw new Error('Ошибка сервера');
                    }
                })
                .catch(error => {
                    status.textContent = 'Ошибка подключения';
                    status.className = 'status error';
                });
        }
        
        // Обработчики кнопок
        document.getElementById('applyBtn').addEventListener('click', applySettings);
        
        document.getElementById('updateTimeBtn').addEventListener('click', function() {
            const status = document.getElementById('status');
            status.textContent = 'Обновление времени...';
            status.className = 'status info';
            
            fetch('/updatetime')
                .then(response => {
                    if (response.ok) {
                        status.textContent = 'Время обновлено!';
                        status.className = 'status ready';
                        
                        setTimeout(() => {
                            status.textContent = 'Готов к работе';
                        }, 2000);
                    } else {
                        throw new Error('Ошибка обновления времени');
                    }
                })
                .catch(error => {
                    status.textContent = 'Ошибка обновления времени';
                    status.className = 'status error';
                });
        });
        
        document.getElementById('offBtn').addEventListener('click', function() {
            document.getElementById('effect').value = 'off';
            document.getElementById('effect').dispatchEvent(new Event('change'));
            applySettings();
        });
        
        // Восстановление настроек из localStorage
        function restoreSettings() {
            const saved = localStorage.getItem('matrixSettings');
            if (saved) {
                try {
                    const settings = JSON.parse(saved);
                    document.getElementById('effect').value = settings.effect || 'fire';
                    document.getElementById('fireBrightness').value = settings.fireBrightness || 50;
                    document.getElementById('fireBrightnessValue').textContent = settings.fireBrightness || 50;
                    document.getElementById('fireHue').value = settings.fireHue || 5;
                    document.getElementById('timeBrightness').value = settings.timeBrightness || 78;
                    document.getElementById('timeBrightnessValue').textContent = settings.timeBrightness || 78;
                    document.getElementById('timeHue').value = settings.timeHue || 200;
                } catch(e) {
                    console.log('Не удалось загрузить настройки');
                }
            }
        }
        
        // Инициализация при загрузке
        window.addEventListener('load', function() {
            restoreSettings();
            initColorWheels();
            
            // Триггерим начальное состояние
            document.getElementById('effect').dispatchEvent(new Event('change'));
            
            // Проверка соединения
            fetch('/')
                .then(() => {
                    console.log('Подключено к матрице');
                })
                .catch(() => {
                    document.getElementById('status').textContent = 'Нет подключения к матрице';
                    document.getElementById('status').className = 'status error';
                });
        });
    </script>
</body>
</html>
)=====";

#endif // HTML_PAGE_H
