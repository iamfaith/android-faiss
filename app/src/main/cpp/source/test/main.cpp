
#include <string>

#include <cmath>
#include <cstdio>
#include <cstdlib>

#include <sys/time.h>

#include "IndexIVFPQ.h"
#include "IndexFlat.h"
#include "index_io.h"

#include "../log.h"
#define FEATURE_COUNT 256
int main() {

    LOGD("hello");

    std::string result = "0";
    faiss::IndexFlatL2 *index;
    std::string name_faiss = "1.index";

    index = new faiss::IndexFlatL2(FEATURE_COUNT);
    float data[FEATURE_COUNT];//random data
    for (int i = 0; i < FEATURE_COUNT; i++) {
        data[i] = 0.0001f * i + 0.00001f;
    }
    LOGI("index->add。。。");
    for (int i = 0; i < (50000); i++) {

        index->add(1, data);
        //Problems may occur in 32-bit
        printf("SIZE= %ld\n", index->ntotal * index->d);
    }
    LOGI("index->add over");


    LOGI("save...");
    //please apply for sdcard permission before writing
    faiss::write_index(index, name_faiss.c_str());
    LOGI("save ");
    delete index;

    LOGI("read ... ");
    faiss::Index *tmp = faiss::read_index(name_faiss.c_str(), faiss::IO_FLAG_MMAP);
    LOGI("read ok");
    //null point check
    index = (faiss::IndexFlatL2 *) tmp;

    LOGI("index->d=%d", index->d);


    float read[FEATURE_COUNT] = {0};
    index->reconstruct(index->ntotal - 1, read);

    for (int i = 0; i < FEATURE_COUNT; i++) {
        printf("read[%d] %f %f\n", i, data[i], read[i]);
    }

    float data2[FEATURE_COUNT];//random data
    for (int i = 0; i < FEATURE_COUNT; i++) {
        data2[i] = 0.0001f * FEATURE_COUNT * 2 + 0.00002f;
    }
    const int64_t destCount = 3;
    int64_t *listIndex = (int64_t *) malloc(sizeof(int64_t) * destCount);
    float *listScore = (float *) malloc(sizeof(float) * destCount);
    LOGI("index->search。。。");
    index->search(1, data2, destCount, listScore, listIndex);
    LOGI("index->search");
    for (int i = 0; i < destCount; i++) {
        printf("index->search[%lld]=%f\n", listIndex[i], listScore[i]);
    }
    free(listIndex);
    free(listScore);

    LOGI("read");
    result = std::to_string(index->ntotal);


    LOGI(result.c_str());
    return 0;
}