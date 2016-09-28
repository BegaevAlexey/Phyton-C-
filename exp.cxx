//exp.cxx - реализация записи/редактирования в файле
//необходимая платформа: linux, из за системного вызова "clear";
//программа работает в двух режимах.
//первый режим - запись в файл данных, тип которых выбирается пользователем
//второй режим - редактирование файла с данными

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>                  //for system()
#include "exp.h"

const int MAX = 5;
const char *nameFile = "DataBase.txt";

int main(int argc, char* argv[])
{
    using namespace std;
    system("clear");
    int i;
    
    //ввод режима программы(запись/редактирование)
    cout << "Enter a mode program(1-record, 2-editing): ";
    int mode;
    //проверка на ввод
    while (!(cin >> mode) || mode < 1 || mode > 2){
        cin.clear();
        while (cin.get() != '\n')
            continue;
        cout << "Error: Incorrect input.\n";
        cout << "Enter a mode program(1-record, 2-editing): ";
    }
    //режим работы: запись данных в файл
    if (mode==1){
        system("clear");
        //открытие файла на запись
        ofstream fout(nameFile);
        //проверка на открытие
        if (!fout.is_open()){
            cout << "Error: not open file.";
            return 0;
        }
        //создаем массив указателей на базовый класс
        abstr_emp *pAbst[MAX];
        //выводим виды объектов
        cout << "Object types:\n";
        cout << "1. Employee\n2. Manager\n3. Fink\n4. High fink\n";
        //создаем необходимые объекты
        for (i=0; i<MAX; i++){
            cout << "\nEnter a type object #" << i+1 << ": ";
            //проверка на ввод
            while (!(cin >> mode) || mode < 1 || mode > 4){
                cin.clear();
                while (cin.get() != '\n')
                    continue;
                cout << "Error: Incorrect input.\n";
                cout << "Enter a type object #" << i+1 << ": ";
            }
            //индефикатор для дальшейнего редоктирования
            fout << "#" << i+1 << " Mode: " << mode << endl;
            //выделение памяти по выбранному объкту
            switch (mode){
                case 1 : pAbst[i] = new employee;
                         break;
                case 2 : pAbst[i] = new manager;
                         break;
                case 3 : pAbst[i] = new fink;
                         break;
                case 4 : pAbst[i] = new highfink;
                         break;
            }
            pAbst[i] -> SetAll();       //ввод данных
            pAbst[i] -> ShowAll(fout);  //запись в файл
            fout << endl;               //отделение данных пустой строкой
        }
        //отображение записанных данных
        system("clear");                //очистка экрана
        for (i=0; i<MAX; i++){
            cout << "#" << i+1 << endl;
            pAbst[i] -> ShowAll(cout);
            cout << endl;
        }        
        //освобождение памяти
        for (i=0; i<MAX; i++)
            delete pAbst[i];
    }

    //режим редактирования
    if (mode == 2){
        //потоки чтения записи
        ofstream fout(nameFile, ios_base::in | ios_base::out);
        ifstream fin(nameFile, ios_base::in);
        //проверка на открытие для записи
        if (!fout.is_open()){
            cerr << "Error: not open file.";
            return 1;
        }
        //проверка на открытие для чтения
        if (!fout.is_open()){
            cerr << "Error: not open file.";
            return 1;
        }
        //отображение содержимого файла
        char ch;
        while (fin.get(ch))
            cout << ch;
        //если достигнут конец файла
        if (fin.eof())
            fin.clear();
        //ввод позиции для изменнения данных
        cout << "Enter the position to change: ";
        int position;
        //проверка ввода
        while (!(cin >> position) || position < 1 || position > MAX){
            cin.clear();
            while (cin.get() != '\n')
                continue;
            cout << "Error: Incorrect input.\n";
            cout << "Enter the position to change: ";
        }
        //очистка экран
        system("clear");
        //поиск позиции
        int positionBoof = 0;
        bool flag = true;
        fin.seekg(0, ios_base::beg);        
        do{
            while ((ch = fin.get())!='#')
                continue;                
            fin >> positionBoof;
            //нашли позицию       
            if (position == positionBoof){
                //ищем тип объекта, например: "Mode:2"", надо найти '2'
                while (fin.get()!=':')
                    continue;
                fin >> mode;
                fin.get();
                //находим позицию в файле для входного потока
                int positionBytes;
                positionBytes = fin.tellg();
                //переставляем указатель выходного потока на позицию изменения
                fout.seekp(positionBytes, ios_base::beg);                
                //выводим данные необходимого объекта
                while ((ch = fin.get())!= '#')
                    cout << ch;                
                //создаем указатель на базовый объекта
                abstr_emp *pAbst;                
                //выделение памяти по найденному объкту
                switch (mode){
                    case 1 : pAbst = new employee;
                            break;
                    case 2 : pAbst = new manager;
                            break;
                    case 3 : pAbst = new fink;
                            break;
                    case 4 : pAbst = new highfink;
                            break;
                }
                pAbst -> SetAll();       //ввод данных
                pAbst -> ShowAll(fout);  //запись в файл
                system("clear");         //очистка экрана
                fin.seekg(0);    // установка входного потока в начало файла
                //отображение содержимого файла
                while (fin.get(ch))
                    cout << ch;
                //если достигнут конец файла
                if (fin.eof())
                    fin.clear();
                flag = false;
            }
        }while (flag);
    }    
    cout << "Bay!\n";
    return 0;
}


