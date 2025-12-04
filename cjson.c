#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *text;
} json_t;

// ---------------------------------------------------------
//  FIND KEY
// ---------------------------------------------------------
static char* find_key(const char *json, const char *key) {
    static char out[256];
    out[0] = 0;

    char pattern[256];
    sprintf(pattern, "\"%s\"", key);

    char *pos = strstr(json, pattern);
    if (!pos) return NULL;

    pos = strchr(pos + strlen(pattern), ':');
    if (!pos) return NULL;

    pos++;
    while (*pos==' '||*pos=='\n'||*pos=='\t') pos++;

    return pos;
}

// ---------------------------------------------------------
//  STRING GET
// ---------------------------------------------------------
char* json_get_string(const char *json, const char *key) {
    static char value[256];
    value[0] = 0;

    char *pos = find_key(json, key);
    if (!pos || *pos != '"') return NULL;

    pos++;
    char *end = strchr(pos, '"');
    if (!end) return NULL;

    int len = end - pos;
    strncpy(value, pos, len);
    value[len] = 0;

    return value;
}

// ---------------------------------------------------------
//  INT GET
// ---------------------------------------------------------
int json_get_int(const char *json, const char *key) {
    char *pos = find_key(json, key);
    if (!pos) return 0;

    return atoi(pos);
}

// ---------------------------------------------------------
//  FLOAT GET
// ---------------------------------------------------------
double json_get_float(const char *json, const char *key) {
    char *pos = find_key(json, key);
    if (!pos) return 0.0;

    return atof(pos);
}

// ---------------------------------------------------------
//  BOOL GET
// ---------------------------------------------------------
int json_get_bool(const char *json, const char *key) {
    char *pos = find_key(json, key);
    if (!pos) return 0;

    if (strncmp(pos, "true", 4) == 0) return 1;
    if (strncmp(pos, "false", 5) == 0) return 0;

    return 0;
}

// ---------------------------------------------------------
//  RAW VALUE GET (no parsing)
// ---------------------------------------------------------
char* json_get_raw(const char *json, const char *key) {
    static char raw[256];
    raw[0] = 0;

    char *pos = find_key(json, key);
    if (!pos) return NULL;

    int i = 0;
    while (*pos && *pos != ',' && *pos != '}' && i < 255) {
        raw[i++] = *pos++;
    }
    raw[i] = 0;

    return raw;
}

// ---------------------------------------------------------
//  SIMPLE ARRAY STRING GET
//  for arrays: "names": ["a","b","c"]
// ---------------------------------------------------------
char* json_get_array_string(const char *json, const char *key, int index) {
    static char value[256];
    value[0] = 0;

    char *pos = find_key(json, key);
    if (!pos) return NULL;

    pos = strchr(pos, '[');
    if (!pos) return NULL;

    pos++; // skip [

    for (int i = 0; i < index; i++) {
        pos = strchr(pos, ',');
        if (!pos) return NULL;
        pos++;
    }

    while (*pos == ' ' || *pos == '"' ) pos++;

    char *end = strchr(pos, '"');
    if (!end) return NULL;

    int len = end - pos;
    strncpy(value, pos, len);
    value[len] = 0;

    return value;
}

// ---------------------------------------------------------
//  GET NESTED OBJECT: returns "{ ... }" text
// ---------------------------------------------------------
char* json_get_object(const char *json, const char *key) {
    static char obj[512];
    obj[0] = 0;

    char *pos = find_key(json, key);
    if (!pos || *pos != '{') return NULL;

    int braces = 0;
    int i = 0;

    do {
        char c = *pos++;
        obj[i++] = c;

        if (c == '{') braces++;
        if (c == '}') braces--;
    }
    while (braces > 0 && i < 511);

    obj[i] = 0;
    return obj;
}

// ---------------------------------------------------------
//  READ JSON FILE
// ---------------------------------------------------------
json_t read_json(const char *filename) {
    json_t j = {0};

    FILE *f = fopen(filename, "r");
    if (!f) return j;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    j.text = malloc(size + 1);
    fread(j.text, 1, size, f);
    j.text[size] = 0;

    fclose(f);
    return j;
}

// ---------------------------------------------------------
//  SAVE JSON FILE
// ---------------------------------------------------------
void save_json(const char *filename, json_t j) {
    if (!j.text) return;

    FILE *f = fopen(filename, "w");
    if (!f) return;

    fputs(j.text, f);
    fclose(f);
}

// ---------------------------------------------------------
//  FREE JSON
// ---------------------------------------------------------
void free_json(json_t j) {
    if (j.text) free(j.text);
}
