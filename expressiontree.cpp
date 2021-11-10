//Expression Tree -- IB Computer Science SL Internal Assessment

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <cmath>

using namespace std;

int place = 1;  //Global variable used to determine divide by 0 condition

class ENode{
private:    //Hidden data from outside world
    char data;
    double value;
    ENode *left;
    ENode *right;
public:
    ENode (double nData, ENode *l, ENode *r){       //Parameterized Constructor
        data = nData;
        if(isdigit(data)){ value = (int)data - 48; }
        left = l;
        right = r;
    }
    char getData(){ return data; }  //user-defined methods with appropriate return value(s)
    void setData(char newd){ data = newd; }
    double getValue(){ return value; }
    void setValue(double newv){ value = newv; }
    ENode * getLeft(){ return left; }
    void setLeft(ENode *l){ left = l; }
    ENode * getRight(){ return right; }
    void setRight(ENode *r){ right = r; }
};

class ETree{
private:
    ENode *root;
public:
    ETree(){ root = NULL; }     //Default Constructor
    void menu();
    void create(string, ENode *);
    void print(ENode *);
    void evaluate(ENode *);
    void printAnswer();
};

void ETree::menu(){
    int option = 0;
    cout<<endl;
    printf("\033[1m\033[35mWelcome to the Expression Tree Calculator! \x1b[0m \n\n");
    //Greeting

    while(option!=4){
        string expression=" ";
        printf("\x1b[36m1) Insert a prefix expression\n");
        printf("\x1b[36m2) Print expression in infix notation\n");
        printf("\x1b[36m3) Evaluate expression\n");
        printf("\x1b[36m4) Quit\n\n");
        printf("\033[1m\033[33mChoose an option above (enter number): \x1b[0m");
        cin>>option;
        cout<<endl;
        //Output menu options

        switch (option){
            case 1:
                printf("\033[1m\033[32mPlease enter an expression in prefix notation (enter 'b' to go back): \x1b[0m");
                cin>>expression;
                if (expression!="b"){
                    root=NULL;
                    place = 1;
                    create(expression, root);
                }
                cout<<endl;
                break;
            
            case 2:
                print (root);
                cout<<endl<<endl;
                break;

            case 3:
                printAnswer();
                break;

            case 4:
                break;

            default:
                cout<<"That is not a valid option. Please try again!"<<endl<<endl;
        }
    }
}

void ETree::create(string phrase, ENode *temp){
    if(root==NULL){
        root = new ENode (phrase[0], NULL, NULL);
        create(phrase, root);
    }
    else{
        ENode *current = temp;
        if(isdigit(current->getData())==0){
            ENode *left = new ENode (phrase[place], NULL, NULL);
            place++;
            current->setLeft(left);

            if(isdigit(left->getData())==0){
                create(phrase, left);
            }

            ENode *right = new ENode (phrase[place], NULL, NULL);
            place++;
            current->setRight(right);

            if(isdigit(right->getData())==0){
                create(phrase, right);
            }
        }
    }
}

void ETree::print(ENode *temp){
    ENode *current = temp;
    if(temp==NULL){ cout<<"There is no expression to print. Please enter one and try again!"; }
    else{   //Recursion
        if(current->getLeft()!=NULL){
            cout<<"(";
            print(current->getLeft());
        }
        if (isdigit(current->getData())==0){
            cout<<" "<<current->getData()<<" ";
        }
        else{
            cout<<current->getData();
        }
        if(current->getRight()!=NULL){
            print(current->getRight());
            cout<<")";
        }
    }
}

void ETree::evaluate(ENode *temp){
    ENode *current = temp;
    if(isdigit(current->getLeft()->getData())==0){
        evaluate(current->getLeft());
    }
    if(isdigit(current->getRight()->getData())==0){
        evaluate(current->getRight());
    }

    if(current->getData()=='*'){
        current->setValue((current->getLeft()->getValue())*(current->getRight()->getValue()));
    }
    else if(current->getData()=='+'){
        current->setValue((current->getLeft()->getValue())+(current->getRight()->getValue()));
    }
    else if(current->getData()=='-'){
        current->setValue((current->getLeft()->getValue())-(current->getRight()->getValue()));
    }
    else if(current->getData()=='/'){
        if(current->getRight()->getValue()==0){ place=0; }
        else{ current->setValue((current->getLeft()->getValue())/(current->getRight()->getValue())); }
    }
    else if (current->getData()=='^'){
        double base = current->getLeft()->getValue();
        double exponent = current->getRight()->getValue();
        current->setValue(pow(base, exponent));
    }
}

void ETree::printAnswer(){
    if(root==NULL){
        cout<<"No Expression Tree = No Answer. Please enter an expression first!"<<endl<<endl;
    }
    else{
        try{
            evaluate(root);
            if(place!=0){   //Tests whether expression will have to divide by zero or not
                setprecision(2);
                //print(root);
                cout<<"The answer to the expression is: "<<root->getValue()<<endl<<endl;
            } else{
                throw 505;
            }
        }
        catch (...){
            cout<<"Sorry, you cannot divide by zero (undefined). Please enter a new (defined) expression."<<endl<<endl;
        }
    }
}

int main(){
    ETree l;
    l.menu();

    return 0;
}