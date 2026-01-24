#!/usr/bin/env python3
# Файл: HTMLConverter.py
# Скрипт для конвертации HTML файла в C++ строку для PROGMEM

import sys

def convert_html_to_cpp(input_file, output_file):
    """
    Конвертирует HTML файл в C++ строку для использования в PROGMEM
    """
    try:
        # Читаем HTML файл
        with open(input_file, 'r', encoding='utf-8') as f:
            html_content = f.read()
        
        # Экранируем кавычки и обратные слеши
        escaped_content = html_content.replace('\\', '\\\\').replace('"', '\\"')
        
        # Разбиваем на строки для удобочитаемости (не более 100 символов)
        lines = []
        current_line = ''
        
        for char in escaped_content:
            current_line += char
            if len(current_line) >= 100 and char in ' ;>}\n':
                lines.append(current_line)
                current_line = ''
        
        if current_line:
            lines.append(current_line)
        
        # Формируем C++ код
        cpp_code = '// Автоматически сгенерированный файл из HTML\n'
        cpp_code += '// Не редактировать вручную!\n\n'
        cpp_code += '#ifndef HTML_PAGE_H\n'
        cpp_code += '#define HTML_PAGE_H\n\n'
        cpp_code += 'const char MAIN_page[] PROGMEM = R"=====(\n'
        cpp_code += html_content
        cpp_code += '\n)=====";\n\n'
        cpp_code += '#endif // HTML_PAGE_H\n'
        
        # Записываем результат
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(cpp_code)
        
        print(f"✅ Успешно сконвертирован {input_file} в {output_file}")
        print(f"   Размер HTML: {len(html_content)} символов")
        
    except FileNotFoundError:
        print(f"❌ Ошибка: Файл {input_file} не найден")
    except Exception as e:
        print(f"❌ Ошибка при конвертации: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Использование: python HTMLConverter.py input.html output.h")
        print("Пример: python HTMLConverter.py web/index.html src/web/html_page.h")
    else:
        convert_html_to_cpp(sys.argv[1], sys.argv[2])