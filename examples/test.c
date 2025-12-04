#include <stdio.h>
#include "cjson.h"

int main() {
    json_t j = read_json("data.json");

    printf("name = %s\n", json_get_string(j.text, "name"));
    printf("age  = %d\n", json_get_int(j.text, "age"));

    free_json(j);
}
