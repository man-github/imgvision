#include "internal.h"
#include <opencv2/opencv.hpp>

void run_yolo(ApiContext* ctx,
              const void* buf,
              size_t len,
              ClassificationMap &out)
{
    std::vector<unsigned char> data((unsigned char*)buf,
                                    (unsigned char*)buf + len);

    cv::Mat img = cv::imdecode(data, cv::IMREAD_COLOR);
    if (img.empty()) return;

    image im = mat_to_image(img);
    image sized = letterbox_image(im, ctx->yolo->w, ctx->yolo->h);

    float* preds = network_predict_image(ctx->yolo, sized);

    int nboxes = 0;
    detection* dets = get_network_boxes(ctx->yolo,
                                        img.cols,
                                        img.rows,
                                        0.5,
                                        0.5,
                                        0,
                                        1,
                                        &nboxes);

    do_nms_sort(dets, nboxes, ctx->label_count, 0.45);

    for (int i = 0; i < nboxes; i++) {
        for (int j = 0; j < ctx->label_count; j++) {
            float p = dets[i].prob[j];
            if (p > 0.25f) {
                out[ctx->labels[j]] = (int)(p * 100);
            }
        }
    }

    free_detections(dets, nboxes);
    free_image(im);
    free_image(sized);
}
