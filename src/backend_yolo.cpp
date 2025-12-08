#include "internal.h"
#include <opencv2/opencv.hpp>

extern "C" {
#include <darknet/darknet.h>

// Provided by darknet (not in header)
image mat_to_image_cv(cv::Mat* mat);
}

// Convert darknet C image → C++ wrapper image_t
static image_t convert_image(const image& im)
{
    image_t out;
    out.h = im.h;
    out.w = im.w;
    out.c = im.c;

    size_t sz = im.h * im.w * im.c;
    out.data = (float*)malloc(sz * sizeof(float));
    memcpy(out.data, im.data, sz * sizeof(float));

    return out;
}

void run_yolo(ApiContext* ctx,
              const void* buf,
              size_t len,
              ClassificationMap &out)
{
    if (!ctx || !ctx->yolo)
        return;

    // Decode image
    cv::Mat cv_img = cv::imdecode(
        cv::Mat(1, len, CV_8UC1, (void*)buf),
        cv::IMREAD_COLOR);

    if (cv_img.empty()) {
        fprintf(stderr, "YOLO: decode failed\n");
        return;
    }

    // Convert cv::Mat → darknet::image
    image dn_img = mat_to_image_cv(&cv_img);

    // Convert to C++ wrapper image_t
    image_t cpp_img = convert_image(dn_img);

    // Run YOLO detection
    float thresh = ctx->yolo_thresh;
    std::vector<bbox_t> det = ctx->yolo->detect(cpp_img, thresh);

    // Clean up raw buffers
    free_image(dn_img);
    free(cpp_img.data);

    // Push results
    for (auto &d : det) {
        std::string label = ctx->labels[d.obj_id];
        int conf = (int)(d.prob * 100);

        if (out.count(label))
            out[label] = std::max(out[label], conf);
        else
            out[label] = conf;
    }
}
