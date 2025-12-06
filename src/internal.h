#pragma once
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

extern "C" {
#include <darknet.h>
}

struct ApiContext {
    tesseract::TessBaseAPI* tess;
    network* yolo;
    char** labels;
    int label_count;
};
