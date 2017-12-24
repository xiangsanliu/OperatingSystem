//
// Created by xiang on 2017/12/24.
//

#ifndef OPERATINGSYSTEM_LOCKTEST_H
#define OPERATINGSYSTEM_LOCKTEST_H

#include <iostream>
#define PROCESS_NUM 3

using namespace std;

int resourceAvaliable = 10;         //当前总剩余资源数
int resourceNeed[] = {0, 0, 0};     //需要的资源数
int resourceAlloation[] = {0, 0, 0};//已分配的资源数

//预分配
void preAlloc(int process, int resource);

//检查分配是否安全
bool isSafe() {
    int work = resourceAvaliable;
    bool finish[PROCESS_NUM] = {false, false, false};
    for (int i=0; i<PROCESS_NUM; i++) {
        if (!finish[i]) {
        }
    }
}

void doLock() {
    cout<<"输入各进程需要的资源总数："<<endl;
    for (int i = 0; i<PROCESS_NUM ; i ++) {
        cin>>resourceNeed[i];
    }
}



#endif //OPERATINGSYSTEM_LOCKTEST_H
