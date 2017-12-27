//
// Created by xiang on 2017/12/24.
//

#ifndef OPERATINGSYSTEM_LOCKTEST_H
#define OPERATINGSYSTEM_LOCKTEST_H

#include <iostream>
#define PROCESS_NUM 3

using namespace std;

int resourceAvaliable = 10;         //��ǰ��ʣ����Դ��
int resourceNeed[] = {0, 0, 0};     //��Ҫ����Դ��
int resourceAlloation[] = {0, 0, 0};//�ѷ������Դ��
int safeSeuence[PROCESS_NUM] ;      //��ȫ����
bool isFinish[PROCESS_NUM] = {false, false, false}; //�Ƿ���ɵı��

/**
 * ��ԴԤ����
 * @param process ���̺�
 * @param resource ��Դ��
 */
void preAlloc(int process, int resource);

/**
 * �����䲻��ȫʱ�ص���ȫ״̬
 * @param process ���̺�
 * @param resource ��Դ��
 */
void roolBack(int process, int resource);

/**
 * �������Ƿ�ȫ
 * @return �����Ƿ�ȫ
 */
bool isSafe();

/**
 * ������Դ
 * @param process ���̺�
 * @param request �������Դ��
 * @return �Ƿ�����ɹ�
 */
bool request(int process, int request);

//Ԥ����
void preAlloc(int process, int resource) {
    resourceAvaliable -= resource;

    resourceAlloation[process] += resource;

    resourceNeed[process] -= resource;
}

//�����䲻��ȫʱ���ص���ȫ״̬
void rollBack(int process, int resource) {

    resourceAvaliable += resource;

    resourceAlloation[process] -= resource;

    resourceNeed[process] += resource;

}

//�������Ƿ�ȫ
bool isSafe() {
    int work = resourceAvaliable;
    bool  finish[PROCESS_NUM];
    for (int i=0 ;i<PROCESS_NUM; i++) {     //��ȡ���̵�״̬
        finish[i] = isFinish[i];
    }
    int j = 0;
    for (int i=0; i<PROCESS_NUM; i++) {
        if (!finish[i]) {
            if (resourceNeed[i] <= work) {      //��ǰ���̰�ȫ
                work += resourceAlloation[i];       //���ս���
                finish[i] = true;               //������������
                safeSeuence[j++] = i;   //���°�ȫ����
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

//������Դ
bool request(int process, int request) {
    if (request <= resourceNeed[process]) {
        if (request <= resourceAvaliable) {
            preAlloc(process, request);
            if (resourceNeed[process] == 0) {               //���������
                isFinish[process] = true;
                resourceAvaliable += resourceAlloation[process];
            }
            if (isSafe())
                return true;
            else {
                rollBack(process, request);
                cout<<"����ʧ�ܣ����ܻ��������"<<endl;
            }
        } else {
            cout<<"����ʧ��,ʣ����Դ����"<<endl;
        }
    } else {
        cout<<"����ʧ�ܣ��������Դ�����������Դ"<<endl;
    }
    return false;
}

void doLock() {
    cout<<"������߳���Ҫ����Դ����:"<<endl;
    for (int i=0 ;i<PROCESS_NUM; i++) {
        cin>>resourceNeed[i];
    }
    int loopNum = 30;
    int process, resource;
    while (loopNum--) {
        cout<<"��ǰʣ����Դ��"<<resourceAvaliable<<endl;
        cout<<"���̺� "<<"��ǰ���� "<<"��Ҫ "<<"�Ƿ����"<<endl;
        for (int i=0 ;i< PROCESS_NUM; i++) {
            cout<<i<<'\t'<<resourceAlloation[i]<<'\t'<<resourceNeed[i]<<'\t'<<isFinish[i]<<'\t'<<endl;
        }
        cout<<endl;
        cout<<"������̺ź�������ڴ�:"<<endl;
        cin>>process>>resource;
        cout<<endl;
        request(process, resource);
        cout<<"��ǰ��ȫ����:" ;
        for (int i : safeSeuence) {
            cout<< i << ' ';
        }
        cout<<endl;
        cout<<"---------------------------------------------------------------"<<endl<<endl;
    }
}



#endif //OPERATINGSYSTEM_LOCKTEST_H
