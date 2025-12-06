#include <iostream>
#include <vector>
#include "img_lib.h"

int main()
{
    img_lib_init();

    void* api = nullptr;
    if (get_api(&api)) {
        std::cerr << "API init failed
";
        return 1;
    }

    FILE* f = fopen("sample.jpg","rb");
    if (!f) return 1;

    fseek(f,0,SEEK_END);
    size_t len = ftell(f);
    fseek(f,0,SEEK_SET);

    std::vector<unsigned char> buf(len);
    fread(buf.data(),1,len,f);
    fclose(f);

    Result r;
    get_image_info(api, buf.data(), len, {}, r);

    for (auto &p : r.classification_map)
        std::cout << p.first << ": " << p.second << "%
";

    std::cout << "OCR: " << r.text_extracted << "\n";

    free_api(api);
    img_lib_deinit();
}
