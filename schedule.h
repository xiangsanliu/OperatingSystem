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
    char name[20];      //���̱�ʶ��
    int pri;            //���ȼ�
    int timeNeeded;             //���������ʱ��Ƭ��
    int timeOccupied;           //ռ�õ�CPUʱ����
    short processStstus;        //����״̬
}PCB;
vector<PCB> readyList;      //��������
vector<PCB> finishList;     //��ɶ���

/**
 * ��ʼ������
 */
void initProcess();

/**
 * �����������
 * @param pcb ���̿��ƿ�
 */
void insertIntoReady(PCB pcb);

/**
 * ������ɶ���
 * @param pcb ���̿��ƿ�
 */
void insertIntoFinish(PCB pcb);

/**
 * ��ӡ��������
 */
void printReady();

/**
 * ��ӡ��ɶ���
 */
void printFinish();

/**
 * ִ�н���
 * @param processIndex ���̺�
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
    readyList.at(processIndex).processStstus = RUN;    //������������
    readyList.at(processIndex).pri -= 3;               //�������ȼ� -3
    readyList.at(processIndex).timeNeeded --;          //��������ʱ��Ƭ -1
    if (readyList.at(processIndex).timeNeeded == 0) {  //���̽���
        readyList.at(processIndex).processStstus = FINISH;
        insertIntoFinish(readyList.at(processIndex));  //������ɶ���
        readyList.erase(readyList.cbegin() + processIndex); //�Ӿ�������ɾ��
        return;
    }
    readyList.at(processIndex).processStstus = READY; //�������²����������
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
    cout<<"������\t"<<"�������ȼ�\t"<<"����ʱ��"<<endl;
    for (auto & pcb: readyList) {
        cout<<pcb.name<<'\t'<<pcb.pri<<'\t'<<pcb.timeNeeded<<'\t'<<endl;
    }
    cout<<endl;
}

void printFinish() {
    cout<<endl;
    cout<<"�����������:"<<endl;
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
