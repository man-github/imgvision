#include "internal.h"
#include <opencv2/opencv.hpp>

void run_ocr(ApiContext* ctx,
             const void* buf,
             size_t len,
             std::string &out)
{
    if (!ctx || !ctx->ocr)
        return;

    cv::Mat img = cv::imdecode(
        cv::Mat(1, len, CV_8UC1, (void*)buf),
        cv::IMREAD_COLOR);

    if (img.empty()) {
        fprintf(stderr, "OCR: decode failed\n");
        return;
    }

    ctx->ocr->SetImage(img.data, img.cols, img.rows, 3, img.step);

    char* txt = ctx->ocr->GetUTF8Text();
    if (txt) {
        out = txt;
        delete[] txt;
    }
}
