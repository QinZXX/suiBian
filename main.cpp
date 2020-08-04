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

// 用int可以，用int不行

void test1(){
    Base base_test;   //创建对象会输出Base::A
    //Base* base_ptr;
    //虚函数指针一般存放在一个类对象的最开始的地方
    //cout<<sizeof(void *);//4
    //cout<< sizeof(int);//4
    int *address =(int*)(&base_test);
    //cout << "基类虚函数表地址" << (int*)&base_test<<endl;
    cout << "基类虚函数表地址" << address << endl;
    //首先取到虚函数表的地址，这个地址里存放的是虚函数也就是第一个虚函数的地址，取出这个地址。
    //cout << "基类虚函数表第一个函数的地址" << (int*)*(int*)&base_test<<endl;
    cout << "基类虚函数表第一个函数的地址" << (int*)(*address)<< endl;
    //在int*的基础上加1则指向第二个虚函数的地址
    cout << "基类虚函数表第二个函数的地址" << (((int*)(*address))+1) << endl;
    cout << "基类虚函数表第三个函数的地址" << ((int*)(*(address)) + 2) << endl;

    //上面得到虚函数的地址，取出这个地址的值然后再用函数指针指向它。

    Pfun p1 = (Pfun)*((int*)(*address));           //函数指针
    Pfun p2 = (Pfun)*(((int*)(*address)) + 1);
    Pfun p3 = (Pfun)*(((int*)(*(address)) + 2));
    p1();  //基类第一个虚函数
    p2();  //基类第二个虚函数
    p3();  //基类第三个虚函数
}

void test2(){
    Derive derive_test;
    int * address2 = (int*)(&derive_test);
    cout << "派生类虚函数表地址" << (int*)&derive_test << endl;
    cout << "派生类虚函数表第一个函数的地址" << (int*)*(int*)&derive_test << endl;
    cout << "派生类虚函数表第二个函数的地址" << ((int*)(*address2)+1) << endl;
    cout << "派生类虚函数表第二个函数的地址" << ((int*)(*address2) + 2) << endl;
    Pfun p4 = (Pfun)*((int*)(*address2));
    Pfun p5 = (Pfun)*(((int*)(*address2)) + 1);
    Pfun p6 = (Pfun)*(((int*)(*(address2)) + 2));
    p4();
    p5();
    p6();
}

int main() {
    test1();

    //**************  子类测试 *************
    test2();

    return 0;
}