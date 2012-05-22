#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <cstdlib>
#include <fstream>
#include <string.h>
using namespace std;
int getch()
{
        int ch;
        struct termios oldt, newt;
        tcgetattr( STDIN_FILENO, &oldt );
        newt = oldt;
        newt.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newt );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
        return ch;
}

#define lim 20
#define end cout<<endl;
class Menu{
    private:
    string menu[lim];
    string menuelements[lim];
    int kol;
    public:
    Menu() {kol=0;};
        void Add(string Str){
            menuelements[kol]=Str;
            kol++;
            for(int i=0;i<kol;i++){
            menu[i]="   "+menuelements[i];
            }
        }
        void Print(){
            cout<<"Нажмите y что бы войти в меню";
            end end end
        for(int i=0;i<kol;i++){
            for (int j=0;abs(j)< menu[i].size();j++){
            cout<<menu[i][j];
            }
            end
            }
        }
        void Push(int Poz){//add target
            menu[Poz]="-->"+menuelements[Poz];
            int i=0;
            while (i<kol){//untarget other elements
            if (i!=Poz){
                menu[i]="   "+menuelements[i];
                }
                i++;
            }
        }
        int Sum(){
        return kol;
        }
};

struct Link{
    string El;
    int id;
    Link *Next;
};
class Base{
    private:
    int idclass;
    Link *Head;// адрес головного элемента
    Link *Tail;
    int Count;
    public:
    Base();
    ~Base();
    void Add(string Str);//добавление элемента, новый становится последним
    void Del(); // Удаление элемента, удаляется головной элемент
    void DelAll();// Гепоцид
    void EditByNumber(int Num);
    void Print();//Печать всех элементов, начиная с готовного
    int GetCount();// Получение кол-ва элементов
    void Mkol(int a);
    void addnum(string Str, int Num);
    void loadfile();
    void savefile();
    int Kol();
};

Base::Base(){
    //Создаем пустой список
    idclass=0;
    Head=Tail=NULL;
    Count=0;
}
int Base::Kol(){
return idclass;
}
Base::~Base(){
    //Удаляем весь список
    DelAll();
}
int Base::GetCount(){
    return Count;
}
void Base::Add(string Str){
    Count++;
    Link *temp= new Link;
    temp->El=Str;
    temp->id=idclass;
    idclass++;
    temp->Next=NULL;
    if(Head!=NULL){
    Tail->Next=temp;
    Tail=temp;
    }
    else {
    Head=Tail=temp;
    }
}

void Base::Del(){
    if (Count>0) Count--;
        if(Head!= NULL){

    Link *temp=Head;
    Head=Head->Next;
    delete temp;
    }
}
void Base::DelAll(){
    while(Head!=0){
    Del();
}
}

void Base::EditByNumber(int Num){
Link *temp = Head;
    while(temp){
    if (temp->id == Num){
        string Str;
        cout<<"Введите новое название"<<endl;
        cin>>Str;
        temp->El=Str;
        }
        temp=temp->Next;
    }

}
void Base::Print(){
    Link *temp=Head;
    while(temp !=0){
    cout<< temp->id<< "\t";
    cout<<temp->El<< endl;
    temp=temp->Next;
    }
}

void Base::addnum(string Str, int Num){
Link *temp= Head;
Link *added = new Link;
if(temp==NULL){
Head=added;
}
else {
while(temp->Next!= NULL)
{
    temp=temp->Next;
}
    temp->Next=added;
}
added->Next=NULL;
added->El=Str;
added->id=Num;
}
void Base::Mkol(int a){
idclass=a;
}
void Base::loadfile(){
this->DelAll();
ifstream out ("base.bin", ios::binary);
int kol;
out>>kol;
this->Mkol(kol);
while (!out.eof()){
string Str;

int cur;
out>>Str;
out>>cur;
this->addnum(Str,cur);
}

out.close();

}
void Base::savefile(){
ofstream to ("base.bin", ios::binary);
to<<this->Kol();
Link *temp=Head;
while (temp){
to<<temp->El<<' ';
to<<temp->id;
temp=temp->Next;
}
to.close();
}
bool t_exit(){
cout<<"Нажмите 'y' для выхода:  ";
char y;
y=getch();
if (y== 'y'){
return 1;
}
else{
system("clear");
return 0;
}
}
int main(){
    Base List;
    string s;
    //Make base Menu
    Menu *MainMenu= new Menu;
//    Menu *Add= new Menu;
    MainMenu->Add("Files");
    MainMenu->Add("Show");
    MainMenu->Add("Add");
    MainMenu->Add("Edit");
    MainMenu->Add("Delete");
    MainMenu->Add("Exit");
    Menu *FileMenu= new Menu;
    FileMenu->Add("Открыть файл");
    FileMenu->Add("Сохранить изменения в файл");
    FileMenu->Add("Вернуться в главное меню");
    Menu *DelMenu= new Menu;
    DelMenu->Add("Удалить первый элемент");
    DelMenu->Add("Удалить по номеру");
    DelMenu->Add("Вернуться в главное меню");
    int Cur_Poz=0;
    int Cur_Poz_f=0;
    int Cur_Poz_d=0;
    MainMenu->Push(Cur_Poz);
    MainMenu->Print();

    //system("clear");
    //int a=getch();
    //cout<<a;
    while (true){
    switch (getch()) {
        case 119:
            system("clear");
            Cur_Poz--;
            if(Cur_Poz<0){
                Cur_Poz=MainMenu->Sum()-1;
            }
            //cout<<Cur_Poz;
            MainMenu->Push(Cur_Poz);
            MainMenu->Print();

        break;
        case 115:
            system("clear");
            Cur_Poz++;
            if(Cur_Poz>MainMenu->Sum()-1){
                Cur_Poz=0;
            }
            //cout<<Cur_Poz;
            MainMenu->Push(Cur_Poz);
            MainMenu->Print();
        break;
        case 27:
        system("clear");
        if (t_exit()==1)
        {
            exit(0);
        }
        else

        {
            MainMenu->Print();
            break;
        }
        break;
        case 121:
            switch (Cur_Poz){
            case 0:
            system("clear");
            FileMenu->Push(Cur_Poz_f);
            FileMenu->Print();
            int a;
                  do  {
                    a=getch();
                    switch (a) {
                    case 119:
                        system("clear");
                        Cur_Poz_f--;
                        if(Cur_Poz_f<0){
                            Cur_Poz_f=FileMenu->Sum()-1;
                        }
                        //cout<<Cur_Poz;
                        FileMenu->Push(Cur_Poz_f);
                        FileMenu->Print();

                    break;
                    case 115:
                        system("clear");
                        Cur_Poz_f++;
                        if(Cur_Poz_f>FileMenu->Sum()-1){
                            Cur_Poz_f=0;
                        }
                        //cout<<Cur_Poz;
                        FileMenu->Push(Cur_Poz_f);
                        FileMenu->Print();
                        break;
                    case 121:
                        switch(Cur_Poz_f){
                        case 0:
                        List.loadfile();
                        break;
                        case 1:
                        List.savefile();
                        break;
//////////////////////////////////////////////////////////////Exit to main menu
                        case 2: system("clear"); MainMenu->Print();
                        break;
                        }
                        break;
                    }
                    }
                    while (a!=121 || Cur_Poz_f!=2);

            break;
            case 1:
            system("clear");
            cout<<"Show Menu";
           // int i=List->GetCount();
            if (List.GetCount()!=0)
            {
                end end end
            List.Print();
            }
            else
            {
                end end end
                cout<<"No elements";
            }
            break;
            case 2:
            cout<<"New Element: ";
            cin>>s;
            end
            List.Add(s);
            s='\0';
            system("clear");
            cout<<"Success Added\n";
            MainMenu->Print();
            break;
            case 4:
                system("clear");
                DelMenu->Push(Cur_Poz_d);
                DelMenu->Print();
                int b;
                  do  {
                    b=getch();
                    switch (b) {
                    case 119:
                        system("clear");
                        Cur_Poz_d--;
                        if(Cur_Poz_d<0){
                            Cur_Poz_d=DelMenu->Sum()-1;
                        }
                        //cout<<Cur_Poz;
                        DelMenu->Push(Cur_Poz_d);
                        DelMenu->Print();

                    break;
                    case 115:
                        system("clear");
                        Cur_Poz_d++;
                        if(Cur_Poz_d>DelMenu->Sum()-1){
                            Cur_Poz_d=0;
                        }
                        //cout<<Cur_Poz;
                        DelMenu->Push(Cur_Poz_d);
                        DelMenu->Print();
                        break;
                    case 121:
                        switch(Cur_Poz_d){
                            case 0: List.Del(); DelMenu->Print();
                            case 1:
//////////////////////////////////////////////////////////////Exit to main menu
                        case 2: system("clear"); MainMenu->Print();
                        break;
                        }
                        break;
                    }
                  }
                 while (b!=121 || Cur_Poz_d!=2);
                 break;

            case 3:
            system("clear");
            cout<<"Редактирование"<<endl<<endl<<endl;
            cout<<"Введите номер элемента:  ";
            int del;
            cin>> del;
            List.EditByNumber(del);
            break;
            case 5:
            if (t_exit()==1)
            {
                exit(0);
            }
            else
            {
                system("clear");
                MainMenu->Print();
            }
            break;
            }

        break;
        }

    }

    setlocale (LC_ALL,"");
    return 0;
}

