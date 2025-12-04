# CJson – Tiny JSON Parser in Pure C

CJson is a minimal, zero-dependency JSON reader designed for small C projects, embedded systems, and anyone who just wants to pull values out of a JSON file without bringing in a giant library.

This project provides:
- Simple key/value extraction  
- Integer, float, boolean, and string getters  
- Array string lookup  
- Nested object extraction  
- File-based JSON loading and saving  

Perfect for lightweight projects, toy languages, interpreters, and system utilities.

---

## 🔧 Features

- `json_get_string(json, key)`
- `json_get_int(json, key)`
- `json_get_float(json, key)`
- `json_get_bool(json, key)`
- `json_get_raw(json, key)`
- `json_get_array_string(json, key, index)`
- `json_get_object(json, key)`

Plus file utilities:
- `read_json("file.json")`
- `save_json("file.json", json)`
- `free_json(json)`

---

## 📄 Example

```c
#include <stdio.h>
#include "cjson.h"

int main() {
    json_t data = read_json("data.json");

    printf("Name: %s\n", json_get_string(data.text, "name"));
    printf("Age: %d\n", json_get_int(data.text, "age"));
    printf("Dev: %d\n", json_get_bool(data.text, "dev"));

    char *lang = json_get_array_string(data.text, "languages", 0);
    printf("First language: %s\n", lang);

    free_json(data);
}
```

## 📁 File Structure
CJson/  
│── examples/  
│     ├── data.json  
│     ├── test.c  
│  
│── cjson.c  
│── cjson.h  
│── README.md  
└── LICENSE  

## ⚠️ Limitations

This is not a full JSON parser.
It assumes clean JSON, no escaping, no deep validation, and no weird formatting.

Works perfectly for:

config files

small interpreters

game data

simple embedded projects

learning JSON parsing

## 📝 License

MIT License — free to use, modify, and ship.

## 👤 Author

Made by ISD NightNova
Project: CJson, a micro JSON reader for C.
