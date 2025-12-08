#pragma once
#include <string>
#include <list>
#include <map>

#define ORDERED_MAP std::map
typedef ORDERED_MAP<std::string, int> ClassificationMap;

class Result {
public:
    ClassificationMap classification_map;   // <label, confidence>
    std::string text_extracted;
};

typedef void* IMG_API_HANDLE;

// OCR modes
enum OCRMode {
    OCR_LSTM_ONLY = 0,
    OCR_LEGACY_ONLY = 1,
    OCR_LSTM_AND_LEGACY = 2
};

#ifdef __cplusplus
extern "C" {
#endif

int img_lib_init(const char* cfg_file,
                 const char* weights_file,
                 const char* names_file,
                 int ocr_engine_mode);

int img_lib_deinit();

int list_classification_options(const char* folder, Result &result);

int get_api(void **api);

int free_api(void *api);

int get_image_info(void* api,
                   const void* buf,
                   size_t len,
                   const std::list<std::string> &hint,
                   Result &result);

#ifdef __cplusplus
}
#endif
