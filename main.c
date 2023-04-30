//TODO: Do create_function
//TODO: Do create_struct
//TODO: Do create_typedef

//TODO: Test get_total_lines
//TODO: Test get_file_stats

#include "_rstypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define BUFFER_SIZE 1024

typedef struct
{
    u32 line;
    u32 character;
}position;
typedef struct
{
    u32 lines;
    u32 *chars;
}file_stats;
struct file
{
	file_stats* stats;
	string file_name;
}

void insert_text(string, position, string);
void delete_text(string, position, position);
void append_text(string, string);
void create_function(string, string, string*, string*, u8);
void create_struct(string, string, string*, string*);

u32 get_total_lines(string);
u32 get_total_chars(string);
file_stats get_file_stats(string);
void print_file_stats(file_stats);
void free_file_stats(file_stats);
void print_pos(position);
u32 count_text(string, string);
u32 count_text_except(string, string, string);
position find_text(string, string, u8);
position find_text_except(string, string, string, u8);
u8 char_in_line(string, char, u32);
u32 get_chars_in_line(string, u32);

u8 char_in_string(string, char);
string concatenate_array_strings(string*, u8);

int main()
{
    const string main_file = "main.txt";
    const string c_file = "void_structs.c";
    position pos = find_text(main_file, "89", 3);
    print_pos(pos);
    return 727;
}

void insert_text(string file_name, position pos, string text)
{
    string buffer = malloc(BUFFER_SIZE);
    u32 i;
    char character;

    FILE* file_pointer = fopen(file_name, "r");
    FILE* fp_temp = fopen("temp.txt", "w");

    for(i = 0; i < pos.line; i++)
        if(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
            fprintf(fp_temp, buffer);
        else
            break;

    fgets(buffer, BUFFER_SIZE, file_pointer);
    for(i = 0; i < pos.character; i++)
        if(buffer[i] == '\n')
            break;
        else
            fputc(buffer[i], fp_temp);
    
    fprintf(fp_temp, text);
    fprintf(fp_temp, buffer + i);

    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
        fprintf(fp_temp, buffer);

    free(buffer);
    fclose(file_pointer);
    fclose(fp_temp);

    remove(file_name);
    rename("temp.txt", file_name);
}
void delete_text(string file_name, position start, position end)
{
    assert(start.line <= end.line);
    if(start.line == end.line)
        assert(start.character <= end.character);

    string buffer = malloc(BUFFER_SIZE);
    u32 i;

    FILE* file_pointer = fopen(file_name, "r");
    FILE* fp_temp = fopen("temp.txt", "w");

    for(i = 0; i < start.line; i++)
        if(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
            fprintf(fp_temp, buffer);
        else
            break;

    fgets(buffer, BUFFER_SIZE, file_pointer);
    for(i = 0; i < start.character; i++)
        if(buffer[i] == '\n')
            break;
        else
            fputc(buffer[i], fp_temp);

    if(start.line != end.line)
        fprintf(fp_temp, "\n");

    for(i = start.line; i < end.line; i++) 
        fgets(buffer, BUFFER_SIZE, file_pointer);

    for(i = end.character; i < strlen(buffer); i++)
        fputc(buffer[i], fp_temp);

    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
        fprintf(fp_temp, buffer);
    
    free(buffer);
    fclose(file_pointer);
    fclose(fp_temp);

    remove(file_name);
    rename("temp.txt", file_name);
}
void append_text(string file_name, string text)
{
    FILE* file_pointer = fopen(file_name, "a");
    fprintf(file_pointer, text);
    fclose(file_pointer);
}
void create_function(string file_name, string function_name, string* var_types, string* var_name, u8 size)
{

}
void create_struct(string file_name, string struct_name, string* var_types, string* var_names)
{

}

u32 get_total_lines(string file_name)
{
    u32 result = 0;
    string buffer = malloc(BUFFER_SIZE);
    FILE* file_pointer = fopen(file_name, "r");

    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
        result++;
    
    free(buffer);
    fclose(file_pointer);
    return result;
}
u32 get_total_chars(string file_name)
{
    string buffer = malloc(BUFFER_SIZE);
    FILE* file_pointer = fopen(file_name, "r");
    u32 total = 0;

    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
        total += strlen(buffer);
    
    free(buffer);
    fclose(file_pointer);
    return total;
}
file_stats get_file_stats(string file_name)
{
    file_stats result;
    result.lines = get_total_lines(file_name);
    result.chars = malloc(sizeof(*result.chars) * result.lines);
    
    string buffer = malloc(BUFFER_SIZE);
    FILE* file_pointer = fopen(file_name, "r");

    for(u32 i = 0; i < result.lines; i++)
        result.chars[i] = strlen(buffer);

    free(buffer);
    fclose(file_pointer);
    return result;
}
void print_file_stats(file_stats stats)
{
    printf(".lines: %u\n\n", stats.lines);
    for(u32 i = 0; i < stats.lines; i++)
        printf("result[%u].chars: %u\n", i, stats.chars[i]);
}
void free_file_stats(file_stats stats)
{
    free(stats.chars);
}
void print_pos(position pos)
{
    printf(".line: %u\n.character: %u\n", pos.line, pos.character);
}
u32 count_text(string file_name, string text)
{
    u32 result = 0;
    string buffer = malloc(BUFFER_SIZE);
    FILE* file_pointer = fopen(file_name, "r");
    
    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
        if(strstr(buffer, text) != NULL)
            result++;
    
    free(buffer);
    fclose(file_pointer);
    return result;
}
u32 count_text_except(string file_name, string text, string exception)
{
    string buffer = malloc(BUFFER_SIZE);
    FILE* file_pointer = fopen(file_name, "r");
    u32 result = 0;
    
    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
        if((strstr(buffer, text) != NULL) && (strstr(buffer, exception) == NULL))
            result++;

    free(buffer);
    fclose(file_pointer);
    return result;
}
position find_text(string file_name, string text, u8 instance)
{
    position result = {.line = 0, .character = 0};
    if(instance == 0)
        return result;
    u8 current_instance = 0;
    string buffer = malloc(BUFFER_SIZE);
    FILE* file_pointer = fopen(file_name, "r");
    
    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
    {
        if(strstr(buffer, text) != NULL)
            current_instance++;
        result.line++;
        if(current_instance == instance)
            break;
    }

    result.character = strstr(buffer, text) - buffer;
    free(buffer);
    fclose(file_pointer);
    assert(current_instance == instance);
    return result;
}
position find_text_except(string file_name, string text, string exception, u8 instance)
{
    position result = {.line = 0, .character = 0};
    if(instance == 0)
        return result;
    u8 current_instance = 0;
    string buffer = malloc(BUFFER_SIZE);
    FILE* file_pointer = fopen(file_name, "r");
    
    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
    {
        if((strstr(buffer, text) != NULL) && (strstr(buffer, exception) == NULL))
            current_instance++;
        if(current_instance == instance)
            break;
        result.line++;
    }
    
    result.character = strstr(buffer, text) - buffer;
    free(buffer);
    fclose(file_pointer);
    assert(current_instance == instance);
    return result;
}
u8 char_in_line(string file_name, char character, u32 line)
{
    string buffer = malloc(BUFFER_SIZE);
    u32 current_line = 0;
    FILE* file_pointer = fopen(file_name, "r");
    
    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
        if(current_line == line)
            break;
        else
            current_line++;

    u8 result = char_in_string(buffer, character);
    free(buffer);
    fclose(file_pointer);
    return result;
}
u32 get_chars_in_line(string file_name, u32 line)
{
    string buffer = malloc(BUFFER_SIZE);
    FILE* file_pointer = fopen(file_name, "r");
    u32 current_line = 0;

    while(fgets(buffer, BUFFER_SIZE, file_pointer) != NULL)
        if(current_line == line)
            break;
        else
            current_line++;

    u32 result = strlen(buffer);
    free(buffer);
    fclose(file_pointer);
    assert(current_line == line);
    return result;
}

u8 char_in_string(string str, char c)
{
    u16 i;
    for(i = 0; str[i] != '\0'; i++)
        if(str[i] == c)
            return 1;
    return 0;
}
string concatenate_array_strings(string* strings, u8 array_size)
{
    u8 current_string;
    u64 total_size = 0;

    for(current_string = 0; current_string < array_size; current_string++)
    total_size += strlen(strings[current_string]);

    string output = malloc(total_size + 1);
    output[0] = '\0';

    for(current_string = 0; current_string < array_size; current_string++)
    strcat(output, strings[current_string]);

    output[total_size] = '\0';
    return output;
}
