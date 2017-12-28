//
// Created by xiang on 2017/12/12.
// �洢����
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

//�״���Ӧ�㷨
void assign_ff(Process *process) {

    for (unsigned int i=0 ; i < memoryList.size(); i++ ) {
        if (process->memory == memoryList.at(i).size) {         //����պõ��ڵ�ǰ�ռ�
            process->start_index = memoryList.at(i).start_index;
            process->flag = 1;
            memoryList.erase(memoryList.cbegin()+i);            //�ӿռ������ɾ��
            return;
        } else if (process->memory < memoryList.at(i).size) {
            process->start_index = memoryList.at(i).start_index;    //�����ǰ�ռ��������ռ�
            memoryList.at(i).start_index += process->memory;
            process->flag = 1;
            memoryList.at(i).size -= process->memory;
            return;
        }
    }
    cout<<"����ʧ��"<<endl<<endl;
}

//����
void recycle(Process process) {
    Memory memory{};
    memory.start_index = process.start_index;
    memory.size = process.memory;
    memoryList.push_back(memory);
    sort(memoryList.begin(), memoryList.end(), sortByStartIndex);   //���ݷ�����ʼλ������
    int size = 0;
    for (unsigned int i=0 ;i<memoryList.size()-1; i++) {            //�����ڴ�
        if (memoryList.at(i).start_index+memoryList.at(i).size == memoryList.at(i+1).start_index) {
            memoryList.at(i).size += memoryList.at(i+1).size;
            memoryList.erase(memoryList.cbegin()+i+1);
        }
    }
    cout<<"���ճɹ�"<<endl<<endl;
}

//�����Ӧ�㷨
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
        cout<<"����ʧ��"<<endl;
    }
}

void domain() {
    Memory first{
            0, 1024
    };
    memoryList.push_back(first);
    cout<<"���������ĸ�����";
    cin>>n;
    cout<<"�����������������ڴ�ռ䣺";
    for (int i=0 ;i<n; i++) {
        Process process{};
        process.flag = 0;
        process.start_index = -1;
        cin>> process.memory;
        processList.push_back(process);
    }
    printProcess();
    printMemory();
    cout<<"ѡ����,�״���Ӧ�㷨call 1�������Ӧ�㷨call2:"<<endl;
    int fun;
    cin>>fun;

    for (int i=0; i<MAX_LOOP; i++) {
        cout<<"ѡ����ţ�";
        unsigned int index;
        cin>>index;
        if (processList.at(index).flag==0) {
            if (fun==1) {
                assign_ff(&processList.at(index));     //ʹ���״���Ӧ�㷨
            } else if (fun==2) {
                assign_bf(&processList.at(index));      //ʹ�������Ӧ�㷨
            } else {
                return;
            }

            printProcess();     //��ӡ�������
            printMemory();      //��ӡ�洢�ռ����
        } else {
            recycle(processList.at(index));
            printProcess();     //��ӡ������Ϣ
            printMemory();      //��ӡ�洢�ռ���Ϣ
        }
    }

}

void printProcess() {
    cout<<"������Ҫ�Ŀռ�"<<'\t'<<"���̷���״̬"<<'\t'<<"�ռ���ʼλ��"<<endl;
    for (auto & item:processList) {
        cout<<item.memory<<'\t'<<item.flag<<'\t'<<item.start_index<<endl;
    }
    cout<<endl;

}

void printMemory() {
    cout<<"�ռ���ʼλ��"<<"\t"<<"�ռ��С"<<endl;
    for (auto &item: memoryList) {
        cout<<item.start_index<<"\t"<<item.size<<endl;
    }
    cout<<endl;
}


#endif //OPERATINGSYSTEM_STORAGE_MANAGE_H
