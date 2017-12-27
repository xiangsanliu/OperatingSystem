#ifndef OPERATIONSYSTEM_LOCK_H
#define OPERATIONSYSTEM_LOCK_H

//
// Created by xiang on 2017/11/21.
// 死锁
//


#include <cstdio>

#define PROCESS_NUM 5

typedef struct {
    int a;          //a资源
    int b;          //b资源
    int c;          //c资源
}Resource;

Resource max[PROCESS_NUM] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
};

Resource allocation[PROCESS_NUM] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
};

Resource need[PROCESS_NUM] = {
        {7, 4, 3},
        {1, 2, 2},
        {6, 0, 0},
        {0, 1, 1},
        {4, 3, 1}
};

Resource avaliable = {3, 3, 2};
int safeSequence[5];

//预分配
void preAlloc(int process, Resource resource) {

    avaliable.a -= resource.a;
    avaliable.b -= resource.b;
    avaliable.c -= resource.c;

    allocation[process].a += resource.a;
    allocation[process].b += resource.b;
    allocation[process].c += resource.c;

    need[process].a -= resource.a;
    need[process].b -= resource.b;
    need[process].c -= resource.c;

}

//若分配后进入不安全状态，收回资源
void rollBack(int process, Resource resource) {
    avaliable.a += resource.a;
    avaliable.b += resource.b;
    avaliable.c += resource.c;

    allocation[process].a -= resource.a;
    allocation[process].b -= resource.b;
    allocation[process].c -= resource.c;

    need[process].a += resource.a;
    need[process].b += resource.b;
    need[process].c += resource.c;

}

//检查是否安全
bool isSafe() {
    Resource work = avaliable;
    bool finish[PROCESS_NUM] = {false, false, false, false, false};
    int i, j=0;
    for (i=0; i<PROCESS_NUM; i++) {
        if (finish[i] == false) {
            if (need[i].a<= work.a && need[i].b <= work.b && need[i].c <= work.c) {
                work.a += allocation[i].a;
                work.b += allocation[i].b;
                work.c += allocation[i].c;
                finish[i] = true;
                safeSequence[j++] = i;
                i = -1;
            }
        }
    }

    for (i=0; i<PROCESS_NUM; i++) {
        if (finish[i] == false)
            return false;
    }
    return true;
}

//申请资源
bool request(int process, Resource request) {
    if (request.a<=need[process].a && request.b<=need[process].b && request.c<=need[process].c) {
        if (request.a<=avaliable.a && request.b<=avaliable.b && request.c<=avaliable.c) {
            preAlloc(process, request);
            if (isSafe())
                return true;
            else {
                rollBack(process, request);
                printf("分配失败，分配后可能会出现死锁");
            }
        } else {
            printf("申请失败，剩余资源不足");
        }
    } else {
        printf("分配失败，申请的资源大于所需的资源");
    }
    return false;
}


void lock() {
    if (isSafe()) {
        for (int i=0; i<PROCESS_NUM; i++) {
            printf("%d", safeSequence[i]);
        }
    }
}

#endif //OPERATIONSYSTEM_LOCK_H
