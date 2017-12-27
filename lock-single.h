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
int safeSeuence[PROCESS_NUM] ;      //安全序列
bool isFinish[PROCESS_NUM] = {false, false, false}; //是否完成的标记

/**
 * 资源预分配
 * @param process 进程号
 * @param resource 资源数
 */
void preAlloc(int process, int resource);

/**
 * 当分配不安全时回到安全状态
 * @param process 进程号
 * @param resource 资源数
 */
void roolBack(int process, int resource);

/**
 * 检查分配是否安全
 * @return 分配是否安全
 */
bool isSafe();

/**
 * 请求资源
 * @param process 进程号
 * @param request 请求的资源数
 * @return 是否请求成功
 */
bool request(int process, int request);

//预分配
void preAlloc(int process, int resource) {
    resourceAvaliable -= resource;

    resourceAlloation[process] += resource;

    resourceNeed[process] -= resource;
}

//当分配不安全时，回到安全状态
void rollBack(int process, int resource) {

    resourceAvaliable += resource;

    resourceAlloation[process] -= resource;

    resourceNeed[process] += resource;

}

//检查分配是否安全
bool isSafe() {
    int work = resourceAvaliable;
    bool  finish[PROCESS_NUM];
    for (int i=0 ;i<PROCESS_NUM; i++) {     //获取进程的状态
        finish[i] = isFinish[i];
    }
    int j = 0;
    for (int i=0; i<PROCESS_NUM; i++) {
        if (!finish[i]) {
            if (resourceNeed[i] <= work) {      //当前进程安全
                work += resourceAlloation[i];       //回收进程
                finish[i] = true;               //假设进程已完成
                safeSeuence[j++] = i;   //更新安全序列
                i = -1;
            }
        }
    }
    for (bool i : finish) {
        if (!i) {
            return false;
        }
    }
    return true;
}

//申请资源
bool request(int process, int request) {
    if (request <= resourceNeed[process]) {
        if (request <= resourceAvaliable) {
            preAlloc(process, request);
            if (resourceNeed[process] == 0) {               //进程完成了
                isFinish[process] = true;
                resourceAvaliable += resourceAlloation[process];
            }
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
    cout<<"输入各线程需要的资源总数:"<<endl;
    for (int i=0 ;i<PROCESS_NUM; i++) {
        cin>>resourceNeed[i];
    }
    int loopNum = 30;
    int process, resource;
    while (loopNum--) {
        cout<<"当前剩余资源："<<resourceAvaliable<<endl;
        cout<<"进程号 "<<"当前分配 "<<"需要 "<<"是否完成"<<endl;
        for (int i=0 ;i< PROCESS_NUM; i++) {
            cout<<i<<'\t'<<resourceAlloation[i]<<'\t'<<resourceNeed[i]<<'\t'<<isFinish[i]<<'\t'<<endl;
        }
        cout<<endl;
        cout<<"输入进程号和申请的内存:"<<endl;
        cin>>process>>resource;
        cout<<endl;
        request(process, resource);
        cout<<"当前安全序列:" ;
        for (int i : safeSeuence) {
            cout<< i << ' ';
        }
        cout<<endl;
        cout<<"---------------------------------------------------------------"<<endl<<endl;
    }
}



#endif //OPERATINGSYSTEM_LOCKTEST_H
