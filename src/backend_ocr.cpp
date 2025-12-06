#include "internal.h"
#include <opencv2/opencv.hpp>

void run_ocr(ApiContext* ctx,
             const void* buf,
             size_t len,
             std::string &out)
{
    std::vector<unsigned char> data((unsigned char*)buf,
                                    (unsigned char*)buf + len);

    PIX* pix = pixReadMem(data.data(), len);
    if (!pix) { out = ""; return; }

    ctx->tess->SetImage(pix);
    char* text = ctx->tess->GetUTF8Text();

    out = text ? text : "";
    delete[] text;

    pixDestroy(&pix);
}
