#ifndef caculator_h
#define caculator_h

#include <cstdlib>
#include <iostream>
#include <memory>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <cctype>

using std::cout,std::cin;
using std::setprecision,std::fixed;
using std::string;
using std::shared_ptr,std::make_shared;
using std::string;
using std::isdigit;

class vec_s{//顺序表完成向量
    public:
    double* elements;
    vec_s(int n, double fill=0):length(n){
        elements=(double*)malloc(sizeof(double)*n);
        for(int i=0; i<n; i++)elements[i]=fill;
    }
    ~vec_s(){
        free(elements);
    }
    vec_s(const vec_s& other){
        length=other.length;
        elements=(double*)malloc(length*sizeof(double));
        for(int i=0; i<length; i++)elements[i]=other.elements[i];
    }
    vec_s& operator=(const vec_s& other){
        if(&other!=this){
            length=other.length;
            free(elements);
            elements=(double*)malloc(length*sizeof(double));
            for(int i=0; i<length; i++)elements[i]=other.elements[i];
        }
        return *this;
    }
    void update(){
        for(int i=0; i<length; i++){
            cin >> elements[i];
        }
    }
    void clear(){//清空
        for(int i=0;i<length;i++){
            elements[i]=0;
        }
    }
    void iterate(const int precision=2)const{
        for(int i=0; i<length; i++){
            cout << fixed << setprecision(precision)<<elements[i]<<" ";
        }
    }
    vec_s operator+(const vec_s& other)const{
        checkCal(other);
        vec_s res((this->length),0);
        for(int i=0; i<res.length;i++){
            res.elements[i]=this->elements[i]+other.elements[i];
        }
        return res;
    }
    vec_s operator-(const vec_s& other)const{
        checkCal(other);
        vec_s res(this->length,0);
        for(int i=0; i<res.length; i++){
            res.elements[i]=this->elements[i]-other.elements[i];
        }
        return res;
    }
    double cosSimilarity(vec_s other){
        double dotProdect=0,res,amod=0,bmod=0;
        for(int i=0; i<length; i++){
            dotProdect+=elements[i]*other.elements[i];
            amod+=elements[i]*elements[i];
            bmod+=other.elements[i]*other.elements[i];
        }
        amod=sqrt(amod);
        bmod=sqrt(bmod);
        res=dotProdect/(amod*bmod);
        return res;
    }
    private:
    int length;
    void checkCal(const vec_s& other)const{
        if(this->length!=other.length)throw std::invalid_argument("无效计算：两个向量应该有同样的维数");
        else if(this->elements==NULL||other.elements==NULL)throw std::invalid_argument("无效计算：向量为空");
    }
};

typedef struct term{
    double co;//系数
    int de;//次数
}term;

class poly_s{
    public:
        term* elements;
        poly_s(){
            cout<<"请输入多项式的项数：";
            cin>>length;
            elements=(term*)malloc(length*sizeof(term));
            for(int i=0; i<length; i++){
                cout<<"请输入第"<<i+1<<"项的系数和次数";
                cin>>elements[i].co>>elements[i].de;
                cout<<std::endl;
            }
            sort();
        }
        poly_s(int n){
            length=n;
            elements=(term*)malloc((length>0?length:1)*sizeof(term));
            elements[0].co=0;
            elements[0].de=0;
        }
        ~poly_s(){
            free(elements);
        }
        poly_s(const poly_s& other){
            length=other.length;
            elements=(term*)malloc(length*sizeof(term));
            for(int i=0; i<length; i++){
                elements[i]=other.elements[i];
            }
        }
        poly_s& operator=(const poly_s& other){
            if(&other!=this){
                free(elements);
                length=other.length;
                elements=(term*)malloc(length*sizeof(term));
                for(int i=0; i<length; i++){
                    elements[i]=other.elements[i];
                }
            }
            return *this;
        }
        poly_s operator+(const poly_s& other)const{
            checkNull();
            other.checkNull();
            int i=0,j=0,p=0;
            poly_s res(0);
            while(i<length&&j<other.length){
                if(elements[i].de<other.elements[j].de){
                    res.insert(elements[i]);
                    i++;
                }
                else if(elements[i].de>other.elements[j].de){
                    res.insert(other.elements[j]);
                    j++;
                }
                else{
                    term nt;
                    nt.co=elements[i].co+other.elements[j].co;
                    nt.de=elements[i].de;
                    if(nt.co){
                        res.insert(nt);
                    }
                    i++;
                    j++;
                }
            }
            while(i<length){
                res.insert(elements[i]);
                i++;
            }
            while(j<other.length){
                res.insert(other.elements[j]);
                j++;
            }
            return res;
        }
        poly_s operator-(const poly_s& other)const{
            checkNull();
            other.checkNull();
            int i=0,j=0,p=0;
            poly_s res(0);
            while(i<length&&j<other.length){
                if(elements[i].de<other.elements[j].de){
                    res.insert(elements[i]);
                    i++;
                }
                else if(elements[i].de>other.elements[j].de){
                    term nt=other.elements[j];
                    nt.co*=-1;
                    res.insert(nt);
                    j++;
                }
                else{
                    term nt;
                    nt.co=elements[i].co-other.elements[j].co;
                    nt.de=elements[i].de;
                    if(nt.co){
                        res.insert(nt);
                    }
                    i++;
                    j++;
                }
            }
            while(i<length){
                res.insert(elements[i]);
                i++;
            }
            while(j<other.length){
                term nt=other.elements[j];
                nt.co*=-1;
                res.insert(nt);
                j++;
            }
            return res;
        }
        poly_s operator*(const poly_s& other)const{
            checkNull();
            other.checkNull();
            int i=0,j=0,p=0;
            poly_s res(0);
            for(i=0;i<length;i++){
                for(j=0;j<other.length;j++){
                    term nt;
                    nt.co=elements[i].co*other.elements[j].co;
                    nt.de=elements[i].de+other.elements[j].de;
                    res.insert(nt);
                }
            }
            res.sort();
            return res;
        }
        poly_s differentiate()const{
            checkNull();
            poly_s res(0);
            if(length==0||(length==1&&elements[0].de==0))return res;
            else{
                for(int i=0; i<length; i++){
                    if(elements[i].de==0)continue;
                    else{
                        term nt=elements[i];
                        nt.de-=1;
                        res.insert(nt);
                    }
                }
            }
            return res;
        }
        int getLength()const{
            return length;
        }
        void iterate()const{
            checkNull();
            if(length==0){
                cout<<0<<std::endl;
                return;
            }
            for(int i=0; i<length; i++){
                if(i==0||elements[i].co<0)cout<<elements[i].co;
                else cout<<"+"<<elements[i].co;
                if(elements[i].de!=0)cout<<"x^"<<elements[i].de;
            }
            cout<<std::endl;
            return;
        }
    private:
        int length;
        void checkNull()const{
            if(elements==NULL)throw std::invalid_argument("无效多项式：空");
        }
        void checkLength(int k)const{
            if(k>length)throw std::invalid_argument("无效下标：大于长度");
        }
        void sort(){
            int decrease=0;
            for(int i=0; i<length; i++){
                for(int j=0; j<length-i-1; j++){
                    if(elements[j].co==0){
                        term temp=elements[j];
                        elements[j]=elements[j+1];
                        elements[j+1]=temp;
                    }
                    else if(elements[j].de>elements[j+1].de){
                        term temp=elements[j];
                        elements[j]=elements[j+1];
                        elements[j+1]=temp;
                    }
                    else if(elements[j].de==elements[j+1].de){
                        elements[j].co+=elements[j+1].co;
                        elements[j+1].co=0;
                        decrease++;
                    }
                }
            }
            length-=decrease;
        }
        void insert(const term& nt){
            length++;
            term* p=(term*)realloc(elements,length*sizeof(term));
            if(p==NULL)throw std::bad_alloc();
            else elements=p;
            elements[length-1]=nt;
        }
};

typedef struct Node{
    double co;
    int de;
    shared_ptr<Node> next;
}node;

class poly_c{
    public:
        shared_ptr<node> head;
        poly_c(){
            cout<<"请输入多项式的项数：";
            cin>>length;
            head=make_shared<node>();
            head->co=0;
            head->de=0;
            shared_ptr<node> p=head;
            for(int i=0; i<length; i++){
                shared_ptr<node> nt=make_shared<node>();
                cout<<"请输入第"<<i+1<<"项的系数与次数：";
                cin>>nt->co>>nt->de;
                nt->next=nullptr;
                p->next=nt;
                p=p->next;
                cout<<std::endl;
            }
            sort();
        }
        poly_c(int n):length(n){
            head=make_shared<node>();
            head->co=0;
            head->de=0;
        }
        poly_c operator+(const poly_c& other)const{
            checkNull();
            other.checkNull();
            poly_c res(0);
            shared_ptr<node> pa=head->next,pb=other.head->next;
            while(pa!=nullptr&&pb!=nullptr){
                if(pa->de<pb->de){
                    res.insert(pa);
                    pa=pa->next;
                }
                else if(pa->de>pb->de){
                    res.insert(pb);
                    pb=pb->next;
                }
                else{
                    shared_ptr<node> nt=make_shared<node>();
                    nt->co=pa->co+pb->co;
                    nt->de=pa->de;
                    nt->next=nullptr;
                    if(nt->co){
                        res.insert(nt);
                    }
                    pa=pa->next;
                    pb=pb->next;
                }
            }
            while(pa!=nullptr){
                res.insert(pa);
                pa=pa->next;
            }
            while(pb!=nullptr){
                res.insert(pb);
                pb=pb->next;
            }
            return res;
        }
        poly_c operator-(const poly_c& other)const{
            checkNull();
            other.checkNull();
            poly_c res(0);
            shared_ptr<node> pa=head->next,pb=other.head->next;
            while(pa!=nullptr&&pb!=nullptr){
                if(pa->de<pb->de){
                    res.insert(pa);
                    pa=pa->next;
                }
                else if(pa->de>pb->de){
                    shared_ptr<node> nn=make_shared<node>();
                    nn->co=pb->co*-1;
                    nn->de=pb->de;
                    nn->next=nullptr;
                    res.insert(nn);
                    pb=pb->next;
                }
                else{
                    shared_ptr<node> nt=make_shared<node>();
                    nt->co=pa->co-pb->co;
                    nt->de=pa->de;
                    nt->next=nullptr;
                    if(nt->co){
                        res.insert(nt);
                    }
                    pa=pa->next;
                    pb=pb->next;
                }
            }
            while(pa!=nullptr){
                res.insert(pa);
                pa=pa->next;
            }
            while(pb!=nullptr){
                shared_ptr<node> nn=make_shared<node>();
                nn->co=pb->co*-1;
                nn->de=pb->de;
                nn->next=nullptr;
                res.insert(nn);
                pb=pb->next;
            }
            return res;
        }
        poly_c operator*(const poly_c& other)const{
            checkNull();
            other.checkNull();
            poly_c res(0);
            shared_ptr<node> pa=head->next,pb=other.head->next;
            while(pa!=nullptr){
                pb=other.head->next;
                while(pb!=nullptr){
                    shared_ptr<node> nn=make_shared<node>();
                    nn->co=pa->co*pb->co;
                    nn->de=pa->de+pb->de;
                    res.insert(nn);
                    pb=pb->next;
                }
                pa=pa->next;
            }
            res.sort();
            return res;
        }
        void iterate()const{
            checkNull();
            if(length==0){
                cout<<0<<std::endl;
                return;
            }
            shared_ptr<node> p=head->next;
            for(int i=0; i<length; i++){
                if(i==0||p->co<0)cout<<p->co;
                else cout<<"+"<<p->co;
                if(p->de!=0)cout<<"x^"<<p->de;
                p=p->next;
            }
            cout<<std::endl;
            return;
        }
        poly_c differentiate()const{
            checkNull();
            poly_c res(0);
            if(length==0||(length==1&&head->next->de==0))return res;
            else{
                shared_ptr<node> p=head->next;
                for(int i=0; i<length; i++){
                    if(p->de==0){
                        p=p->next;
                        continue;
                    }
                    else{
                        shared_ptr<node> nn=make_shared<node>();
                        nn->co=p->co;
                        nn->de=p->de-1;
                        nn->next=nullptr;
                        res.insert(nn);
                        p=p->next;
                    }
                }
            }
            return res;
        }
    private:
        int length;
        void checkNull()const{
            if(head==nullptr)throw std::invalid_argument("无效多项式：空");
        }
        void sort(){
            checkNull();
            int decrease=0;
            for(int i=0; i<length; i++){
                shared_ptr<node> p=head->next;
                for(int j=0; j<length-i-1; j++){
                    if(p->co==0){
                        int de=p->de;
                        double co=p->co;
                        p->de=p->next->de;
                        p->next->de=de;
                        p->co=p->next->co;
                        p->next->co=co;
                    }
                    else if(p->de==p->next->de){
                        p->co+=p->next->co;
                        p->next->co=0;
                        decrease++;
                    }
                    else if(p->de>p->next->de){
                        int de=p->de;
                        double co=p->co;
                        p->de=p->next->de;
                        p->next->de=de;
                        p->co=p->next->co;
                        p->next->co=co;
                    }
                    p=p->next;
                }
            }
            shared_ptr<node>p=head->next;
            for(int i=0; i<length-decrease; i++){
                p=p->next;
            }
            if(p!=nullptr)p->next=nullptr;
            length-=decrease;
        }
        void insert(shared_ptr<node> np){
            checkNull();
            shared_ptr<node> nn=make_shared<node>();
            nn->co=np->co;
            nn->de=np->de;
            nn->next=nullptr;
            shared_ptr<node> p=head;
            for(int i=0; i<length; i++){
                p=p->next;
            }
            p->next=nn;
            length++;
        }
};

template<typename T>
struct snode{
    T content;
    shared_ptr<snode<T>> next;
};

template<typename T>
class stack{
    public:
        shared_ptr<snode<T>> head;
        stack(){
            head=make_shared<snode<T>>();
            head->next = nullptr;
        }
        stack(const stack& other){
            head=make_shared<snode<T>>();
            shared_ptr<snode<T>> op = other.head->next,tp=head;
            while(op!=nullptr){
                shared_ptr<snode<T>> newp=make_shared<snode<T>>();
                newp->content=op->content;
                newp->next=nullptr;
                tp->next=newp;
                tp=tp->next;
                op=op->next; 
            }
        }
        stack& operator=(const stack& other){
            if(&other!=this){
                head=make_shared<snode<T>>();
                shared_ptr<snode<T>> op = other.head,tp=head;
                while(op!=nullptr){
                    shared_ptr<snode<T>> newp=make_shared<snode<T>>();
                    newp->content=op->content;
                    newp->next=nullptr;
                    tp->next=newp;
                    tp=tp->next;
                    op=op->next; 
                }
            }
            return *this;
        }
        T peek()const{
            checkNull();
            return head->next->content;
        }
        T pop(){
            T res=head->next->content;
            head->next=head->next->next;
            return res;
        }
        void push(const T& nt){
            shared_ptr<snode<T>> np=make_shared<snode<T>>();
            np->content=nt;
            np->next=head->next;
            head->next=np;
        }
        bool empty()const{
            if(head->next==nullptr)return true;
            else return false;
        }
    private:
        
        void checkNull()const{
            if(head->next==nullptr)throw std::invalid_argument("栈为空");
        }
};

struct express{
    bool isvariable;
    string name;
    bool isdigit;
    char oper;
    double num;
};

int priority(char a){
    switch(a){
        case '*':
        case '/':
            return 2;
            break;
        case '+':
        case '-':
            return 1;
            break;
        case '(':
            return 0;
            break;
    }
    return -1;
}

bool isOperator(char a){
    if(a=='+'||a=='-'||a=='*'||a=='/'||a=='('||a==')') return true;
    else return false;
}

void caculate(stack<express> reverse, double variable){
    stack<double> cal;
    while(!reverse.empty()){
        express token = reverse.pop();
        if(token.isdigit){
            cal.push(token.num);
        }
        else if(token.isvariable){
            cal.push(variable);
        }
        else{
            double a,b;
            if(!cal.empty())b=cal.pop();
            if(!cal.empty())a=cal.pop();
            else break;
            switch(token.oper){
                case '+':
                    cal.push(a+b);
                    break;
                case '-':
                    cal.push(a-b);
                    break;
                case '*':
                    cal.push(a*b);
                    break;
                case '/':
                    cal.push(a/b);
                    break;
            }
        }
    }
    if(cal.empty())cout<<"表达式无效"<<std::endl;
    else{
        double res=cal.pop();
        if(!cal.empty())cout<<"表达式无效"<<std::endl;
        else cout<<"计算结果是："<<res<<std::endl;
    }
}

void basicArithmetic(int mode){//mode为1则有变量，否则无
    string str;
    cout<<"请输入四则运算表达式：";
    cin>>str;
    cout<<std::endl;
    stack<express> final,oper;
    std::istringstream iss(str);
    bool lt=true; //上一个是不是符号
    while(iss.peek()!=EOF){
        express ne;
        ne.isvariable=false;
        if(isdigit(iss.peek())){
            ne.isdigit=true;
            ne.oper='\0';
            iss>>ne.num;
            final.push(ne);
            lt=false;
        }
        else if(iss.peek()=='-'){
            char tmp=iss.get();
            if(lt){
                iss.putback(tmp);
                ne.isdigit=true;
                ne.oper='\0';
                iss>>ne.num;
                final.push(ne);
                lt=false;
            }
            else{
                ne.isdigit=false;
                ne.num=0;
                ne.oper=tmp;
                while(!oper.empty()&&(priority(oper.peek().oper))>=priority(ne.oper)){
                    final.push(oper.pop());
                }
                oper.push(ne);
                lt=true;
            }
        }
        else if(iss.peek()=='('){
            ne.isdigit=false;
            ne.num=0;
            iss>>ne.oper;
            oper.push(ne);
            lt=true;
        }
        else if(iss.peek()==')'){
            iss.get();
            while(!oper.empty()&&oper.peek().oper!='('){
                final.push(oper.pop());
            }
            if(!oper.empty()&&oper.peek().oper=='(')oper.pop();
            lt=false;
        }
        else if(isOperator(iss.peek())){
            ne.isdigit=false;
            ne.num=0;
            iss>>ne.oper;
            while(!oper.empty()&&(priority(oper.peek().oper))>=priority(ne.oper)){
                final.push(oper.pop());
            }
            oper.push(ne);
            lt=true;
        }
        else if(isalpha(iss.peek())){
            ne.name="";
            ne.isvariable=true;
            if(!lt)throw std::invalid_argument("变量名要以字母开始");
            else{
                while(iss.peek()!=EOF&&!isOperator(iss.peek())){
                    if(!(isalpha(iss.peek())||isdigit(iss.peek())||iss.peek()=='_')){
                        throw std::invalid_argument("变量名只能包含字母、数字和下划线");
                    }
                    ne.name+=iss.get();
                }
            }
            final.push(ne);
            lt=false;
        }
    }
    while(!oper.empty()){
        final.push(oper.pop());
    }//将中缀表达式改为后缀表达式
    double variable;
    stack<express> reverse;
    while(!final.empty()){
        reverse.push(final.pop());
    }
    if(mode){
        while(true){
            cout<<"请输入变量的值：";
            cin>>variable;
            cout<<std::endl;
            caculate(reverse,variable);
            cout<<"是否退出？（1：继续，0：退出） ";
            int exit;
            cin>>exit;
            if(!exit)break;
        }
    }
    else{
        caculate(reverse,0);
    }
}

#endif