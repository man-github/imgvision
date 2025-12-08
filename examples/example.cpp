#include <iostream>
#include <cstdio>
#include <vector>
#include "img_lib.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: example <imagefile>" << std::endl;
        return 1;
    }

    const char* filename = argv[1];

    FILE* f = fopen(filename, "rb");
    if (!f) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return 1;
    }

    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    fseek(f, 0, SEEK_SET);

    std::vector<unsigned char> buf(size);

    // We ignore fread() return, but suppress compiler warning:
    size_t read_bytes = fread(buf.data(), 1, size, f);
    (void)read_bytes;

    fclose(f);

    // Initialize API (fix: pass address of pointer)
    void* api = nullptr;
    if (get_api(&api) != 0) {     // <<<< FIXED
        std::cerr << "get_api() failed" << std::endl;
        return 1;
    }

    Result result;

    std::list<std::string> hint;  // no classification hint

    if (get_image_info(api, buf.data(), size, hint, result) != 0) {
        std::cerr << "get_image_info() failed" << std::endl;
        free_api(api);
        return 1;
    }

    free_api(api);

    std::cout << "--- OCR TEXT ---\n";
    std::cout << result.text_extracted << "\n\n";

    std::cout << "--- CLASSIFICATIONS ---\n";
    for (auto &p : result.classification_map) {
        std::cout << p.first << " : " << p.second << std::endl;
    }

    return 0;
}
