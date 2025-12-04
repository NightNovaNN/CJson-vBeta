#ifndef CJSON_H
#define CJSON_H

typedef struct {
    char *text;
} json_t;

// reading / writing
json_t read_json(const char *filename);
void save_json(const char *filename, json_t j);
void free_json(json_t j);

// getters
char* json_get_string(const char *json, const char *key);
int   json_get_int(const char *json, const char *key);
double json_get_float(const char *json, const char *key);
int   json_get_bool(const char *json, const char *key);
char* json_get_raw(const char *json, const char *key);

// arrays + nested objects
char* json_get_array_string(const char *json, const char *key, int index);
char* json_get_object(const char *json, const char *key);

#endif
