#pragma once

#define MAX_INPUT 1024

typedef struct {
    int x;
    int y;
} cursor;

void curnl(cursor *cur, int by);
