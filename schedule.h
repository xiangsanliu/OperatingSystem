//
// Created by xiang on 2017/12/24.
//

#ifndef OPERATINGSYSTEM_SCHEDULE_H
#define OPERATINGSYSTEM_SCHEDULE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

#define RUN 1000
#define READY 1001
#define FINISH 1002

typedef struct PCBDefine{
    char name[20];      //进程标识符
    int pri;            //优先级
    int timeNeeded;             //进程所需的时间片数
    int timeOccupied;           //占用的CPU时间数
    short processStstus;        //进程状态
}PCB;
vector<PCB> readyList;      //就绪队列
vector<PCB> finishList;     //完成队列

/**
 * 初始化进程
 */
void initProcess();

/**
 * 插入就绪队列
 * @param pcb 进程控制块
 */
void insertIntoReady(PCB pcb);

/**
 * 出入完成队列
 * @param pcb 进程控制块
 */
void insertIntoFinish(PCB pcb);

/**
 * 打印就绪队列
 */
void printReady();

/**
 * 打印完成队列
 */
void printFinish();

/**
 * 执行进程
 * @param processIndex 进程号
 */
void execute(unsigned int processIndex);

bool sortByPriority(PCB p1, PCB p2);
void sortReadyList();


void doSchedule() {
    initProcess();
    while(!readyList.empty()) {
        execute(0);
        printReady();
    }
    printFinish();
}

void sortReadyList() {
    sort(readyList.begin(), readyList.end(), sortByPriority);
}

void execute(unsigned int processIndex)  {
    readyList.at(processIndex).processStstus = RUN;    //进程正在运行
    readyList.at(processIndex).pri -= 3;               //进程优先级 -3
    readyList.at(processIndex).timeNeeded --;          //进程所需时间片 -1
    if (readyList.at(processIndex).timeNeeded == 0) {  //进程结束
        readyList.at(processIndex).processStstus = FINISH;
        insertIntoFinish(readyList.at(processIndex));  //进入完成队列
        readyList.erase(readyList.cbegin() + processIndex); //从就绪队列删除
        return;
    }
    readyList.at(processIndex).processStstus = READY; //进程重新插入就绪队列
    sortReadyList();
}

void insertIntoReady(PCB pcb) {
    readyList.push_back(pcb);
    sortReadyList();
}

void insertIntoFinish(PCB pcb) {
    finishList.push_back(pcb);
}

void printReady() {
    cout<<"进程名\t"<<"进程优先级\t"<<"所需时间"<<endl;
    for (auto & pcb: readyList) {
        cout<<pcb.name<<'\t'<<pcb.pri<<'\t'<<pcb.timeNeeded<<'\t'<<endl;
    }
    cout<<endl;
}

void printFinish() {
    cout<<endl;
    cout<<"进程完成序列:"<<endl;
    for (auto & pcb: finishList) {
        cout<<pcb.name<<endl;
    }
}

bool sortByPriority(PCB p1, PCB p2) {
    return p1.pri > p2.pri;
}

void initProcess() {
    int n;
    cout<<"Input process number:";
    cin>>n;
    for (int i=0; i<n; i++) {
        cout<<"Input process name, priority, timeNeeded:(num "<<i<< "):\t";
        PCB pcb{};
        cin>>pcb.name;
        cin>>pcb.pri;
        cin>>pcb.timeNeeded;
        pcb.processStstus = READY;
        insertIntoReady(pcb);
    }
    printReady();
}


#endif //OPERATINGSYSTEM_SCHEDULE_H
