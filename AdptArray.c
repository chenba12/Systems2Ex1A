#include <stdio.h>
#include <malloc.h>
#include "AdptArray.h"
//I based my code around what I wrote in the previous course's Exam moed A 
typedef struct AdptArray_ {
    int arrSize;
    PElement *pElementArray;
    COPY_FUNC copyFunc;
    DEL_FUNC delFunc;
    PRINT_FUNC printFunc;
} AdptArray, *pAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc, DEL_FUNC delFunc, PRINT_FUNC printFunc) {
    if(copyFunc==NULL || delFunc==NULL || printFunc==NULL) return NULL;
    pAdptArray adptArray = (PAdptArray) malloc(sizeof(struct AdptArray_));
    if (adptArray == NULL) {
        return NULL;
    }
    adptArray->arrSize = 0;
    PElement *array = (PElement *) calloc((adptArray->arrSize), sizeof(PElement));
    if (array == NULL) {
        return NULL;
    }
    adptArray->pElementArray = array;
    adptArray->copyFunc = copyFunc;
    adptArray->delFunc = delFunc;
    adptArray->printFunc = printFunc;
    return adptArray;
}

void DeleteAdptArray(PAdptArray adptArray) {
    if (adptArray == NULL || adptArray->pElementArray == NULL) return;
    for (int i = 0; i < adptArray->arrSize; i++) {
        if (adptArray->pElementArray[i] != NULL) {
            adptArray->delFunc(adptArray->pElementArray[i]);
        }
    }
    free(adptArray->pElementArray);
    free(adptArray);
}

Result SetAdptArrayAt(PAdptArray adptArray, int index, PElement element) {
    if (element == NULL || adptArray == NULL) return FAIL;
    if (adptArray->arrSize <= index) {
        PElement *arr = (PElement *) calloc((index + 1), sizeof(PElement));
        if (arr == NULL) {
            return FAIL;
        }
        for (int i = 0; i < index + 1; i++) {
            if (i < adptArray->arrSize && adptArray->pElementArray[i] != NULL) {
                arr[i] = adptArray->pElementArray[i];
            } else {
                arr[i] = NULL;
            }
        }
        free(adptArray->pElementArray);
        adptArray->pElementArray = arr;
        adptArray->arrSize = index + 1;
    }
    PElement pElement = adptArray->copyFunc(element);
    if (adptArray->pElementArray[index] != NULL) {
        adptArray->delFunc(adptArray->pElementArray[index]);
    }
    adptArray->pElementArray[index] = pElement;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray adptArray, int index) {
    if (adptArray == NULL || index > adptArray->arrSize) return NULL;
    if (adptArray->pElementArray[index] == NULL) return NULL;
    PElement pElement = adptArray->copyFunc(adptArray->pElementArray[index]);
    return pElement;
}

int GetAdptArraySize(PAdptArray adptArray) {
    if (adptArray == NULL || adptArray->pElementArray == NULL) return -1;
    return adptArray->arrSize;
}

void PrintDB(PAdptArray adptArray) {
    if (adptArray == NULL) return;
    for (int i = 0; i < adptArray->arrSize; i++) {
        if (adptArray->pElementArray[i] != NULL) {
            adptArray->printFunc(adptArray->pElementArray[i]);
        }
    }
}
