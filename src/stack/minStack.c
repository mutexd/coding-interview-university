typedef struct {
    int *data;
    int *minData;
    int minIndex;
    int topIndex;
    int cap;
} MinStack;

/** initialize your data structure here. */
MinStack* minStackCreate(int maxSize) {
    MinStack *s = malloc(sizeof(MinStack));
    if (s == NULL) {
        return NULL;
    }
    s->data = malloc(sizeof(int)*maxSize);
    if (s->data == NULL) {
        return NULL;
    }
    s->minData = malloc(sizeof(int)*maxSize);
    if (s->minData == NULL) {
        return NULL;
    }
    s->minIndex = -1;
    s->topIndex = -1;
    s->cap = maxSize;
    return s;
}

void minStackPush(MinStack* obj, int x) {
    if (obj->topIndex + 1 >= obj->cap) {
        // reallocate
        return;
    }
    obj->topIndex++;
    obj->data[obj->topIndex] = x;
    if (obj->minIndex == -1 || x <= obj->minData[obj->minIndex]) {
        obj->minIndex++;
        obj->minData[obj->minIndex] = x;
    }
}

void minStackPop(MinStack* obj) {
    if (obj->topIndex >= 0) {
        if (obj->data[obj->topIndex] == obj->minData[obj->minIndex]) {
            obj->minIndex--;
        }
        obj->topIndex--;
    }
}

int minStackTop(MinStack* obj) {
    if (obj->topIndex >= 0) {
        return obj->data[obj->topIndex];
    }
    return -1;
}

int minStackGetMin(MinStack* obj) {
    if (obj->minIndex >= 0) {
        return obj->minData[obj->minIndex];
    }
    return -1;
}

void minStackFree(MinStack* obj) {
    if (obj != NULL) {
        free(obj->data);
        free(obj->minData);
    }
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * struct MinStack* obj = minStackCreate(maxSize);
 * minStackPush(obj, x);
 * minStackPop(obj);
 * int param_3 = minStackTop(obj);
 * int param_4 = minStackGetMin(obj);
 * minStackFree(obj);
 */
