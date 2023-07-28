#include "main.h"

int print_char_handler(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_string_handler(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_percent_handler(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_int_handler(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_binary_handler(va_list args, char buffer[], int flags, int width, int precision, int size);

int my_printf(const char *format, ...)
{
    if (format == NULL)
        return -1;

    va_list args;
    va_start(args, format);

    char buffer[BUFF_SIZE];
    int printed_chars = 0;

    for (int i = 0; format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[printed_chars++] = format[i];
        }
        else
        {
            i++;

            int flags = get_flags(format, &i);
            int width = get_width(format, &i, args);
            int precision = get_precision(format, &i, args);
            int size = get_size(format, &i);

            int chars_printed = 0;

            switch (format[i])
            {
                case 'c':
                    chars_printed = print_char_handler(args, buffer + printed_chars, flags, width, precision, size);
                    break;
                case 's':
                    chars_printed = print_string_handler(args, buffer + printed_chars, flags, width, precision, size);
                    break;
                case '%':
                    chars_printed = print_percent_handler(args, buffer + printed_chars, flags, width, precision, size);
                    break;
                case 'd':
                    chars_printed = print_int_handler(args, buffer + printed_chars, flags, width, precision, size);
                    break;
                case 'b':
                    chars_printed = print_binary_handler(args, buffer + printed_chars, flags, width, precision, size);
                    break;
                default:
                    buffer[printed_chars++] = '%';
                    i--;
            }

            if (chars_printed == -1)
            {
                va_end(args);
                return -1;
            }

            printed_chars += chars_printed;
        }
    }

    buffer[printed_chars] = '\0';
    va_end(args);

    write(1, buffer, printed_chars);
    return printed_chars;
}
