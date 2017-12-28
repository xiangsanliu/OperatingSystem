//
// Created by xiang on 2017/12/28.
//

#ifndef OPERATINGSYSTEM_STORAGE_MANAGE_SUB_H
#define OPERATINGSYSTEM_STORAGE_MANAGE_SUB_H

#include <iostream>
using namespace std;

#define STORAGE_NUM 3

int storage[STORAGE_NUM] = {-1,-1,-1};
int time[STORAGE_NUM] = {0, 0, 0};

int getTransIndex();

int storageSize() {
    int size = 0;
    for (int i : storage) {
        if (i >=0) {
            size++;
        }
    }
    return size;
}

bool isInStorage(int seq) {
    for (int i: storage) {
        if (i==seq)
            return true;
    }
    return false;
}

void trans(int seq, int timeNow) {
    int index = getTransIndex();
    storage[index] = seq;
    time[index] = timeNow;
}

bool isFull() {
    return storageSize() == STORAGE_NUM;
}

int getTransIndex() {
    int index = 0;

    if (!isFull()) {
        for (int s: storage) {
            if (s != -1) {
                index++;
            }
        }
        return index;
    }

    int old = 9999;
    for (int i=0 ;i<STORAGE_NUM; i++) {
        if (time[i]<old) {
            index = i;
            old = time[i];
        }
    }
    return index;
}

void printStorage() {
    cout<<storage[0]<<' '<<storage[1]<<' '<<storage[2]<<endl;
}

void doTrans() {
    int seqList[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int time = 0;
    for (int seq : seqList) {
        if (!isInStorage(seq)) {
            trans(seq, time);
            time++;
            printStorage();
        }
    }
}


#endif //OPERATINGSYSTEM_STORAGE_MANAGE_SUB_H
