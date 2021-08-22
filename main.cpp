#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int global_x{100};

void test1(){

cout<<"Test1================\n";
int local_x{1000};

auto lambda1 = [local_x] () {
cout<<local_x<<endl;
cout<<global_x<<endl;
};

//calling the lambda
lambda1();
}

void test2(){
cout<<"Test2================\n";

int x{100};

//use mutable keyword so it allows modification in lambda expressions every time it's called
auto lambda2 = [x] () mutable {
x+=100;
cout<<x<<endl;
};

lambda2();
cout<<x<<endl;

lambda2();
cout<<x<<endl;
}


void test3(){
cout<<"Test3==============\n"<<endl;
int x{100};

// we will pass by reference so its value will never change twice
auto lambda3 = [&x]()mutable{
x+=100;
cout<<x<<endl;
};

lambda3();
cout<<x<<endl;
}

void test4(){
cout<<"Test4==============\n"<<endl;

int x = 100;
int y = 100;
int z = 100;

//in here we passed by value so the values won't be changed when we call the lambda expression
auto lambda4 = [=] () mutable{
x +=100;
y+= 100;
cout<<x<<endl;
cout<<y<<endl;
};

lambda4();
cout<<x<<endl;
cout<<y<<endl;
}

void test5(){
cout<<"Test5=============\n";
int x = 100;
int y = 100;
int z = 100;

auto lambda5 = [&] (){
x+=100;
y+= 100;
z+=100;
cout<<x<<endl;
cout<<y<<endl;
cout<<z<<endl;
};

lambda5();
}

void test6(){
cout<<"Test6==============\n";

int x = 100;
int y = 100;
int z = 100;

auto lambda6 = [= , &y]()mutable{
x+=100;
y+=100;
z+=100;
cout<<x<<endl;
cout<<y<<endl;
cout<<z<<endl;
};

lambda6();
cout<<"\n";
cout<<x<<endl;
cout<<y<<endl;
cout<<z<<endl;

}

void test7(){
cout<<"Test7============\n";

int x = 100;
int y = 100;
int z = 100;

auto lambda7 = [&,x,z]() mutable{
x+=100;
y+=100;
z+=100;
cout<<x<<endl;
cout<<y<<endl;
cout<<z<<endl;
};

lambda7();
}

class Person{
friend ostream &operator<<(ostream &os, const Person &rhs);

private:
    string name;
    int age;

public:
    Person() = default;
    Person(string n, int a):name{n},age{a}{}
    Person(const Person &p) = default;
    ~Person() = default;

    string get_name(){return name;}
    void set_name(string name){this->name = name;}

    int get_age(){return age;}
    void set_age(int age){this->age = age;}

    auto change_person1(){return [this](string new_name,int new_age){name = new_name;age = new_age;};}
    auto change_person2(){return [=](string new_name, int new_age){name = new_name; age = new_age;};}
    auto change_person3(){return [&](string new_name, int new_age){name = new_name; age = new_age;};}
};

ostream &operator<<(ostream &os, const Person &rhs){
os<<"[Person: "<<rhs.name<<" : "<<rhs.age<<"]";
return os;
}

void test8(){
cout<<"Test8===============\n";

Person person{"Larry",18};
cout<<person<<endl;

//Default Capture[this]
//This is the preferred way
auto change_person1 = person.change_person1();
change_person1("Moe",30);
cout<<person<<endl;


//Default Capture[=]
//This has been deprecated in C++20
auto change_person2 = person.change_person2();
change_person2("Curly",35);
cout<<person<<endl;

//Default Capture [&]
auto change_person3 = person.change_person3();
change_person3("Meero",18);
cout<<person<<endl;
}

class Lambda{
private:
    int y;
public:
    Lambda(int y): y(y){};

    void operator() (int x) const{
    cout<<x+y<<endl;
    };
};

void test9(){
cout<<"Test9============\n";

int y = 100;
Lambda lambda1(y);
auto lambda2 = [y](int x){cout<<x+y<<endl;};

lambda1(200);
lambda2(200);
}

class People{
private:
    vector<Person> people;
    int max_people;
public:
    People(int max=100):max_people(max){}
    People(const People &p) = default;
    
    void add(string name, int age){
    people.emplace_back(name,age);
    }

    void set_max_people(int max){
    max_people = max;
    }

    int get_max_people()const{
    return max_people;
    }

    vector<Person> get_people(int max_age){
    vector<Person> result;
    int count = 0;
    copy_if(people.begin(),people.end(),back_inserter(result),[this,&count,max_age](Person &p){return p.get_age()> max_age && ++count <= max_people;});
    return result;
    }
};

void test10(){
cout<<"Test10============\n";

People friends;
friends.add("Omar",20);
friends.add("Ahmad",18);
friends.add("Frank",36);
friends.add("James",57);

auto result = friends.get_people(17);
cout<<endl;
for(auto &p: result)
    cout<<p<<endl;

friends.set_max_people(3);
result = friends.get_people(7);

cout<<endl;
for(auto &p: result)
    cout<<p<<endl;

result = friends.get_people(25);
cout<<endl;

for(auto &p: result)
    cout<<p<<endl;
}

int main(){
test10();
}
