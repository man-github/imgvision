#include "internal.h"

extern "C" int list_classification_options(const char* folder, Result &result)
{
    for (auto &s : g_labels)
        result.classification_map[s] = 0;
    return 0;
}

extern "C" int get_image_info(void* api,
                              const void* buf,
                              size_t len,
                              const std::list<std::string>& hint,
                              Result &result)
{
    ApiContext* ctx = (ApiContext*)api;
    if (!ctx) return -1;

    run_yolo(ctx, buf, len, result.classification_map);
    run_ocr(ctx, buf, len, result.text_extracted);

    return 0;
}
