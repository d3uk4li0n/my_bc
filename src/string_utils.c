#include "../include/my_bc.h"

int my_strlen(char *string){
    int i=0;
    if(string == NULL) return -1;

    while(string[i] != '\0') i++;

    return i;
}

int my_strcmp(char *s1, char *s2){
    int i = 0;
    while((s1[i] != '\0') || (s2[i] != '\0')){
        if(s1[i] > s2[i]) return 1;
        if(s1[i] < s2[i]) return -1;
        i++;
    }
    return 0;
}

void my_itoa(char *str, int val){
    
    if (val == 0) //is zero
    {
        str[0] = '0';
        str[1] = '\0';
        return;
    }

    int strPos = 0;

    if (val < 0){
        val = -val;
        str[strPos++] = '-';
    }    

    //eg. 123 => store "321"
    char temp[DATA_SIZE];
    int tempPos = 0;
        
    while (val > 0){
        temp[tempPos++] = (char)('0' + (val % 10));
        val = val / 10;
    }

    for (int i = tempPos - 1; i >= 0; i--){
        str[strPos++] = temp[i];
    }    

    str[strPos] = '\0';
}

char *my_strncpy(char *dst, char *src, size_t n){
    size_t i;
    
    for(i=0; i<n && src[i] != '\0';i++)
        dst[i] = src[i];

    dst[i] = '\0';
    
    return dst;
}

char *my_strcpy(char *dst, char *src){    
   
    return my_strncpy(dst, src, my_strlen(src));
}

//convert string to integer, base 10
int my_atoi(char *string){

    int conv = 0;
    int sign = 1;

    if (*string == '-'){ // can be negative
        sign = -1;
        string++;
    }else if (*string == '+'){ // can contains +         
        string++;
    }

    while(*string != '\0'){
        conv = conv * 10 + (*string - '0');
        string++;
    }
    return conv * sign;
}