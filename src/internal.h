#pragma once

#include <string>
#include <vector>
#include <list>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <darknet/yolo_v2_class.hpp>

#include "../include/img_lib.h"

// -----------------------------------------------------------
// API Context (per-thread)
// -----------------------------------------------------------
struct ApiContext {
    Detector* yolo;                   // YOLO detector instance
    tesseract::TessBaseAPI* ocr;      // OCR engine
    float yolo_thresh;                // Detection threshold
    std::vector<std::string> labels;  // Class labels
};

// -----------------------------------------------------------
// Global detector + labels + OCR mode
// -----------------------------------------------------------
extern Detector* g_detector;
extern std::vector<std::string> g_labels;
extern int g_ocr_mode;

// -----------------------------------------------------------
// Utility helpers
// -----------------------------------------------------------
std::vector<std::string> load_labels(const char* names_file);

// -----------------------------------------------------------
// Backend modules
// -----------------------------------------------------------
void run_yolo(ApiContext*, const void*, size_t, ClassificationMap&);
void run_ocr(ApiContext*, const void*, size_t, std::string&);
