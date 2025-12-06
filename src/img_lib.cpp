#include "../include/img_lib.h"
#include "internal.h"
#include <filesystem>

extern "C" {

void run_yolo(ApiContext*,const void*,size_t,ClassificationMap&);
void run_ocr(ApiContext*,const void*,size_t,std::string&);

int img_lib_init(){ return 0; }
int img_lib_deinit(){ return 0; }

int list_classification_options(const char* folder, Result &res)
{
    res.classification_map.clear();
    for (auto &f : std::filesystem::directory_iterator(folder))
        res.classification_map[f.path().stem().string()] = 0;
    return 0;
}

int get_image_info(IMG_API_HANDLE a,
                   const void* buf,
                   size_t len,
                   const std::list<std::string>& hint,
                   Result &res)
{
    ApiContext* ctx = (ApiContext*) a;

    run_yolo(ctx, buf, len, res.classification_map);
    run_ocr(ctx, buf, len, res.text_extracted);

    if (!hint.empty()) {
        ClassificationMap filtered;
        for (auto &h : hint)
            if (res.classification_map.count(h))
                filtered[h] = res.classification_map[h];
        res.classification_map = filtered;
    }

    return 0;
}

}
