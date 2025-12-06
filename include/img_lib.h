#pragma once
#include <string>
#include <map>
#include <list>
typedef std::map<std::string,int> ClassificationMap;
class Result{public:ClassificationMap classification_map;std::string text_extracted;};
typedef void* IMG_API_HANDLE;
int img_lib_init();
int img_lib_deinit();
int list_classification_options(const char*, Result&);
int get_api(void **api);
int free_api(IMG_API_HANDLE api);
int get_image_info(IMG_API_HANDLE api,const void* buf,size_t len,const std::list<std::string>& hint,Result& result);
