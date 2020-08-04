#include<iostream>
using namespace std;

using Pfun=void(*)();

class Base {
public:
    Base() { A();
    };
    void test(){cout << "test" << endl;}
    virtual void A() {cout << "virtual Base::A" << endl;}
    void B() {cout << "Base::B" << endl;}
    virtual void C() {cout << "virtual Base::C" << endl;}
    virtual void D() {cout << "virtual Base::D" << endl;}
public:
    int a;
    int b;
};
class Derive:public Base {
public:
    Derive() { A(); };
    virtual void A() {cout << "virtual Der::A" << endl;}
    void derive_B() {cout << "virtual Der::B" << endl;}
    virtual void C() {cout << "virtual Der::C" << endl;}
    virtual void D() {cout << "virtual Der::D" << endl;}
};
typedef void(*Pfun)();

// ��int���ԣ���int����

void test1(){
    Base base_test;   //������������Base::A
    //Base* base_ptr;
    //�麯��ָ��һ������һ���������ʼ�ĵط�
    //cout<<sizeof(void *);//4
    //cout<< sizeof(int);//4
    int *address =(int*)(&base_test);
    //cout << "�����麯�����ַ" << (int*)&base_test<<endl;
    cout << "�����麯�����ַ" << address << endl;
    //����ȡ���麯����ĵ�ַ�������ַ���ŵ����麯��Ҳ���ǵ�һ���麯���ĵ�ַ��ȡ�������ַ��
    //cout << "�����麯�����һ�������ĵ�ַ" << (int*)*(int*)&base_test<<endl;
    cout << "�����麯�����һ�������ĵ�ַ" << (int*)(*address)<< endl;
    //��int*�Ļ����ϼ�1��ָ��ڶ����麯���ĵ�ַ
    cout << "�����麯����ڶ��������ĵ�ַ" << (((int*)(*address))+1) << endl;
    cout << "�����麯��������������ĵ�ַ" << ((int*)(*(address)) + 2) << endl;

    //����õ��麯���ĵ�ַ��ȡ�������ַ��ֵȻ�����ú���ָ��ָ������

    Pfun p1 = (Pfun)*((int*)(*address));           //����ָ��
    Pfun p2 = (Pfun)*(((int*)(*address)) + 1);
    Pfun p3 = (Pfun)*(((int*)(*(address)) + 2));
    p1();  //�����һ���麯��
    p2();  //����ڶ����麯��
    p3();  //����������麯��
}

void test2(){
    Derive derive_test;
    int * address2 = (int*)(&derive_test);
    cout << "�������麯�����ַ" << (int*)&derive_test << endl;
    cout << "�������麯�����һ�������ĵ�ַ" << (int*)*(int*)&derive_test << endl;
    cout << "�������麯����ڶ��������ĵ�ַ" << ((int*)(*address2)+1) << endl;
    cout << "�������麯����ڶ��������ĵ�ַ" << ((int*)(*address2) + 2) << endl;
    Pfun p4 = (Pfun)*((int*)(*address2));
    Pfun p5 = (Pfun)*(((int*)(*address2)) + 1);
    Pfun p6 = (Pfun)*(((int*)(*(address2)) + 2));
    p4();
    p5();
    p6();
}

int main() {
    test1();

    //**************  ������� *************
    test2();

    return 0;
}