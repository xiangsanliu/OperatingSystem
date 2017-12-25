//
// Created by xiang on 2017/12/24.
//

#ifndef OPERATINGSYSTEM_LOCKTEST_H
#define OPERATINGSYSTEM_LOCKTEST_H

#include <iostream>
#define PROCESS_NUM 3

using namespace std;

int resourceAvaliable = 10;         //当前总剩余资源数
int resourceNeed[] = {7, 1, 3};     //需要的资源数
int resourceAlloation[] = {0, 2, 3};//已分配的资源数
int safeSeuence[PROCESS_NUM] ;

//预分配
void preAlloc(int process, int resource) {
    resourceAvaliable -= resource;

    resourceAlloation[process] += resource;

    resourceNeed[process] -= resource;
}

void rollBack(int process, int resource) {

    resourceAvaliable += resource;

    resourceAlloation[process] -= resource;

    resourceNeed[process] += resource;

}

//检查分配是否安全
bool isSafe() {
    int work = resourceAvaliable;
    bool finish[PROCESS_NUM] = {false, false, false};
    int j = 0;
    for (int i=0; i<PROCESS_NUM; i++) {
        if (!finish[i]) {
            if (resourceNeed[i] <= work) {
                work += resourceAlloation[i];
                finish[i] = true;
                safeSeuence[j++] = i;
                i = -1;
            }
        }
    }
    for (bool item : finish) {
        if (!item) {
            return false;
        }
    }
    return true;
}

bool request(int process, int request) {
    if (request <= resourceNeed[process]) {
        if (request <= resourceAvaliable) {
            preAlloc(process, request);
            if (isSafe())
                return true;
            else {
                rollBack(process, request);
                cout<<"分配失败，可能会出现死锁"<<endl;
            }
        } else {
            cout<<"申请失败,剩余资源不足"<<endl;
        }
    } else {
        cout<<"申请失败，申请的资源大于所需的资源"<<endl;
    }
    return false;
}

void doLock() {
    int loopNum = 30;
    int process, resource;
    while (loopNum--) {
        cout<<"输入线程号和申请的内存:"<<endl;
        cin>>process>>resource;
        request(process, resource);
        cout<<"当前安全序列:" ;
        for (int i=0; i<PROCESS_NUM; i++){
            cout<<safeSeuence[i]<< ' '<<endl;
        }
    }
}



#endif //OPERATINGSYSTEM_LOCKTEST_H
