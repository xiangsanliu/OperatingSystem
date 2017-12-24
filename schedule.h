//
// Created by xiang on 2017/12/24.
//

#ifndef OPERATINGSYSTEM_SCHEDULE_H
#define OPERATINGSYSTEM_SCHEDULE_H

#include <cstdio>
#include <cstdlib>

#define RUN 1000
#define READY 1001
#define FINISH 1002

typedef struct PCBDefine{
    char name[20];      //进程标识符
    int pri;            //优先级
    int timeNeeded;             //进程所需的时间片数
    int timeOccupied;           //占用的CPU时间数
    short processStstus;        //进程状态
    struct PCBDefine *next;       //
}PCB;

PCB * currentProcess;       //当前进程
PCB * readyHead;            //准备队列队首
PCB * finishHead;           //完成队列队首

void insertIntoReady(PCB * pcb) {
    PCB * index = readyHead;
    while (index->next) {
        if (pcb->pri >= index->next->pri) {
            pcb->next = index->next->next;
            index->next = pcb;
            return;
        }
        index = index->next;
    }
    index->next = pcb;
}

void printReady() {
    PCB * index = readyHead;
    while (index->next) {
        printf("xiangjianjian1");
        printf("%s\n", index->next->name);
    }
}

void initProcesss() {
    int n;
    printf("Input process number:");
    scanf("%d", &n);
    printf("Input process name, priority, timeNeeded:\n");
    readyHead =(PCB *) malloc(sizeof(PCB));
    readyHead->next = NULL;
    for (int i=0; i<n; i++) {
        PCB * pcb = (PCB * ) malloc(sizeof(PCB));
        scanf("%s", &pcb->name);
        scanf("%d", & pcb->pri);
        scanf("%d", & pcb->timeNeeded);
        printf("xiangjianjian");
//        insertIntoReady(pcb);
    }
    printReady();
}


#endif //OPERATINGSYSTEM_SCHEDULE_H
