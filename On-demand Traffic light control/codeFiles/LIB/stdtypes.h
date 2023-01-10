#ifndef STDTYPES_H
#define STDTYPES_H


#define NULL ((void *)0)

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned int uint32;
typedef unsigned long long uint64;


typedef char sint8;
typedef short int sint16;
typedef int sint32;
typedef long long sint64;

typedef float sfloat32 ;


typedef enum
{
    ERROR,
    SUCESS,

} StdReturn_t;

#endif