#include "_rstypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define i8_INDICE 0
#define i16_INDICE 1
#define i32_INDICE 2
#define i64_INDICE 3
#define u8_INDICE 4
#define u16_INDICE 5
#define u32_INDICE 6
#define u64_INDICE 7
#define f32_INDICE 8
#define f64_INDICE 9
#define char_INDICE 10

struct c_array
{
    void *array;
    u32 size;
    u32 max;
    u8 type;
};
typedef struct c_array* array;

int main()
{
    
    return 727;
}
