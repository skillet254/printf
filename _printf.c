#include "main.h"

#define BUFF_SIZE 1024

void add_to_buffer(char buffer[], char ch, int *buff_ind);
void print_buffer(char buffer[], int *buff_ind);

int my_printf(const char *format, ...)
{
    if (format == NULL)
        return -1;

    va_list args;
    va_start(args, format);

    char buffer[BUFF_SIZE];
    int printed_chars = 0, buff_ind = 0;
    int flags, width, precision, size, printed;

    for (int i = 0; format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            add_to_buffer(buffer, format[i], &buff_ind);
            printed_chars++;
        }
        else
        {
            print_buffer(buffer, &buff_ind);

            flags = get_flags(format, &i);
            width = get_width(format, &i, args);
            precision = get_precision(format, &i, args);
            size = get_size(format, &i);

            i++;

            printed = handle_print(format, &i, args, buffer, flags, width, precision, size);

            if (printed == -1)
            {
                va_end(args);
                return -1;
            }

            printed_chars += printed;
        }
    }

    print_buffer(buffer, &buff_ind);
    va_end(args);

    return printed_chars;
}

void add_to_buffer(char buffer[], char ch, int *buff_ind)
{
    buffer[(*buff_ind)++] = ch;
    if (*buff_ind == BUFF_SIZE)
        print_buffer(buffer, buff_ind);
}

void print_buffer(char buffer[], int *buff_ind)
{
    if (*buff_ind > 0)
    {
        write(1, buffer, *buff_ind);
        *buff_ind = 0;
    }
}
