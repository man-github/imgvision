#include "internal.h"
#include <new>

extern "C" {

int get_api(void **api)
{
    if (!api) return 1;

    ApiContext* ctx = new(std::nothrow) ApiContext();
    if (!ctx) return 1;

    ctx->tess = new tesseract::TessBaseAPI();
    if (ctx->tess->Init(NULL, "eng")) return 1;

    ctx->yolo = load_network((char*)"models/yolov3.cfg",
                             (char*)"models/yolov3.weights",
                             0);

    ctx->labels = get_labels((char*)"models/coco.names");
    ctx->label_count = 80;

    *api = ctx;
    return 0;
}

int free_api(IMG_API_HANDLE api)
{
    if (!api) return -1;

    ApiContext* ctx = (ApiContext*) api;

    ctx->tess->End();
    delete ctx->tess;

    free_network(ctx->yolo);

    delete ctx;
    return 0;
}

}
