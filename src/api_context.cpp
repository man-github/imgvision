#include "internal.h"
#include <fstream>
#include <iostream>

/*
 * Global shared objects — used by all API contexts
 */
Detector* g_detector = nullptr;
std::vector<std::string> g_labels;
int g_ocr_mode = 0;

/*
 * Load .names file
 */
std::vector<std::string> load_labels(const char* names_file) {
    std::vector<std::string> out;
    std::ifstream f(names_file);
    std::string line;

    while (std::getline(f, line)) {
        if (!line.empty())
            out.push_back(line);
    }
    return out;
}

/*
 * Initialize library: YOLO + label list + OCR mode
 */
extern "C"
int img_lib_init(const char* cfg_file,
                 const char* weights_file,
                 const char* names_file,
                 int ocr_engine_mode)
{
    if (!cfg_file || !weights_file || !names_file)
        return -1;

    try {
        g_detector = new Detector(cfg_file, weights_file);
    }
    catch (...) {
        std::cerr << "ERROR: Failed to load YOLO detector" << std::endl;
        return -2;
    }

    g_labels = load_labels(names_file);
    g_ocr_mode = ocr_engine_mode;

    return 0;
}

/*
 * De-initialize global state
 */
extern "C"
int img_lib_deinit()
{
    if (g_detector) {
        delete g_detector;
        g_detector = nullptr;
    }
    g_labels.clear();

    return 0;
}

/*
 * Allocate per-thread API context
 */
extern "C"
int get_api(void** api)
{
    if (!g_detector)
        return -1;

    ApiContext* ctx = new ApiContext();
    ctx->yolo = g_detector;
    ctx->labels = g_labels;

    // Create Tesseract instance
    ctx->ocr = new tesseract::TessBaseAPI();

    tesseract::OcrEngineMode mode;

    if (g_ocr_mode == OCR_LEGACY_ONLY)
        mode = tesseract::OEM_TESSERACT_ONLY;
    else if (g_ocr_mode == OCR_LSTM_AND_LEGACY)
        mode = tesseract::OEM_TESSERACT_LSTM_COMBINED;
    else
        mode = tesseract::OEM_LSTM_ONLY;

    // Init OCR engine
    if (ctx->ocr->Init(NULL, "eng", mode) != 0) {
        delete ctx->ocr;
        delete ctx;
        return -2;
    }

    *api = ctx;
    return 0;
}

/*
 * Free per-thread API context
 */
extern "C"
int free_api(void* api)
{
    ApiContext* ctx = (ApiContext*)api;

    if (!ctx)
        return 0;

    if (ctx->ocr)
        delete ctx->ocr;

    delete ctx;
    return 0;
}


