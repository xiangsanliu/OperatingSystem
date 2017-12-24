//
// Created by xiang on 2017/12/12.
// 存储管理
//

#ifndef OPERATINGSYSTEM_STORAGE_MANAGE_H
#define OPERATINGSYSTEM_STORAGE_MANAGE_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

#define MAX_LOOP 999

using namespace std;

typedef struct {
    int start_index;
    int size;
}Memory;

typedef struct {
    int flag;
    int memory;
    int start_index;
}Process;

vector<Memory> memoryList;
vector<Process> processList;
int n;

void printProcess();
void printMemory();

bool sortByStartIndex(Memory m1, Memory m2){
    return m1.size < m2.size;
}

//首次适应算法
void assign_ff(Process *process) {

    for (unsigned int i=0 ; i < memoryList.size(); i++ ) {
        if (process->memory == memoryList.at(i).size) {         //如果刚好等于当前空间
            process->start_index = memoryList.at(i).start_index;
            process->flag = 1;
            memoryList.erase(memoryList.cbegin()+i);            //从空间队列中删除
            return;
        } else if (process->memory < memoryList.at(i).size) {
            process->start_index = memoryList.at(i).start_index;    //如果当前空间大于所需空间
            memoryList.at(i).start_index += process->memory;
            process->flag = 1;
            memoryList.at(i).size -= process->memory;
            return;
        }
    }
    cout<<"分配失败"<<endl<<endl;
}

//回收
void recycle(Process process) {
    Memory memory{};
    memory.start_index = process.start_index;
    memory.size = process.memory;
    memoryList.push_back(memory);
    sort(memoryList.begin(), memoryList.end(), sortByStartIndex);   //根据分区起始位置排序
    int size = 0;
    for (unsigned int i=0 ;i<memoryList.size()-1; i++) {            //整理内存
        if (memoryList.at(i).start_index+memoryList.at(i).size == memoryList.at(i+1).start_index) {
            memoryList.at(i).size += memoryList.at(i+1).size;
            memoryList.erase(memoryList.cbegin()+i+1);
        }
    }
    cout<<"回收成功"<<endl<<endl;
}


void domain() {
    Memory first{
            0, 1024
    };
    memoryList.push_back(first);
    cout<<"请输入程序的个数：";
    cin>>n;
    cout<<"请输入各程序所需的内存空间：";
    for (int i=0 ;i<n; i++) {
        Process process{};
        process.flag = 0;
        process.start_index = -1;
        cin>> process.memory;
        processList.push_back(process);
    }
    printProcess();
    printMemory();

    for (int i=0; i<MAX_LOOP; i++) {
        cout<<"选择序号：";
        unsigned int index;
        cin>>index;
        if (processList.at(index).flag==0) {
            assign_ff(& processList.at(index));     //使用首次适应算法
            printProcess();
            printMemory();
        } else {
            recycle(processList.at(index));
            printProcess();
            printMemory();
        }
    }

}

//最佳适应算法
void assign_bf(Process *process) {
    int di = 65535;
    unsigned int index = 0;
    for (unsigned int i=0; i< memoryList.size(); i++) {
        if (memoryList.at(i).size - process->memory < di) {
            di = memoryList.at(i).size - process->memory;
            index = i;
        }
    }
    if (di == 0) {
        process->start_index = memoryList.at(index).start_index;
        process->flag = 1;
        memoryList.erase(memoryList.cbegin()+index);
    } else if (di > 0) {
        process->start_index = memoryList.at(index).start_index;
        memoryList.at(index).start_index += process->memory;
        process->flag = 1;
        memoryList.at(index).size -= process->memory;
    } else {
        cout<<"分配失败"<<endl;
    }
}

void printProcess() {
    cout<<"编号   "<<"\t"<<"进程需要的空间   "<<"\t"<<"进程分配状态    "<<"\t"<<"空间起始位置    "<<endl;
    for (unsigned int i=0 ; i < processList.size(); i++ ) {
        cout<<i<<"\t"<<processList.at(i).memory<<"\t"<<processList.at(i).flag<<"\t"<<processList.at(i).start_index<<endl;
    }
    cout<<endl;

}

void printMemory() {
    cout<<"空间起始位置"<<"\t"<<"空间大小"<<endl;
    for (auto &item: memoryList) {
        cout<<item.start_index<<"\t"<<item.size<<endl;
    }
    cout<<endl;
}


#endif //OPERATINGSYSTEM_STORAGE_MANAGE_H
