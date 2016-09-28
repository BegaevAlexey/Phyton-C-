// exp_f.cxx - реализация методов 

#include <iostream>
#include <string>
#include <iomanip>
#include "exp.h"

using namespace std;

// методы abstr_emp
// конструкторы
abstr_emp::abstr_emp()
{
    fname = "No name";
    lname = "No name";
    job = "None";
}
abstr_emp::abstr_emp(const string &fn, const string &ln, const string &j)
          :fname(fn), lname(ln), job(j) { }

//дисктруктор
abstr_emp::~abstr_emp() { }
    
// выводит все данные
void abstr_emp::ShowAll(ostream &os) const 
{
    os << left;
    os << setw(15) << setfill('.') << "First name" 
       << setw(10) << setfill(' ') << fname << endl;
    os << setw(15) << setfill('.') << "Last name" 
       << setw(10) << setfill(' ') << lname << endl;
    os << setw(15) << setfill('.') << "Job" 
       << setw(10) << setfill(' ') << job << endl;
}

// запрашивает значения у пользователя
void abstr_emp::SetAll()
{
    cout << "Enter first name (str): ";
    cin >> fname;
    cout << "Enter last name (str): ";
    cin >> lname;
    cout << "Enter a job (str): ";
    cin >> job;
}

// выводит только имя и фамилию    
ostream & operator<<(ostream &os, const abstr_emp &e)
{
    cout << e.lname << ", " << e.fname;
}

// методы employee
// конструкторы
employee::employee() { }
employee::employee(const string &fn, const string &ln, const string &j)
         :abstr_emp(fn, ln, j) { }

// выводит все данные
void employee::ShowAll(ostream &os) const
{
    abstr_emp::ShowAll(os);
}

// запрашивает значения у пользователя
void employee::SetAll()
{
    abstr_emp::SetAll();
}

// методы manager
// конструкторы
manager::manager() : abstr_emp(), inchargeof(0) { } 
manager::manager(const string &fn, const string &ln, 
                 const string &j, int ico=0)
        :abstr_emp(fn, ln, j), inchargeof(0) { }
manager::manager(const abstr_emp &a, int ico) 
        :abstr_emp(a), inchargeof(ico) { }
manager::manager(const manager &m) :abstr_emp(m) 
{
    inchargeof = m.inchargeof;
}

// выводит все данные  
void manager::ShowAll(ostream &os) const
{
    abstr_emp::ShowAll(os);
    os << left;
    os << setw(15) << setfill('.') << "In charge of" 
       << setw(10) << setfill(' ')<< inchargeof << endl;
}

// запрашивает значения у пользователя
void manager::SetAll()
{
    abstr_emp::SetAll();
    cout << "Enter in charge Of (int): ";
    cin >> inchargeof;
}

 // методы fink
 // конструкторы
fink::fink() :abstr_emp() , reportsto("No name"){ }
fink::fink(const string &fn, const string &ln,
           const string &j, const string &rpo)
     :abstr_emp(fn, ln, j), reportsto(rpo) { }
fink::fink(const abstr_emp &e, const string &rpo)
     :abstr_emp(e), reportsto(rpo) { }
fink::fink(const fink &f) :abstr_emp(f)
{
    reportsto = f.reportsto;
}

// выводит все данные  
void fink::ShowAll(ostream &os) const
{
    abstr_emp::ShowAll(os);
    os << left;
    os << setw(15) << setfill('.') << "Reports to" 
       << setw(10) << setfill(' ') << reportsto << endl;
}

// запрашивает значения у пользователя
void fink::SetAll()
{
    abstr_emp::SetAll();
    cout << "Enter reports to (str): ";
    cin >> reportsto;
}

// методы highfink
// конструкторы
highfink::highfink() { }
highfink::highfink(const string &fn, const string &ln,
             const string &j, const string &rpo, int ico)
         :abstr_emp(fn,ln,j), manager(fn, ln, j, ico), fink(fn, ln, j, rpo) { }
highfink::highfink(const abstr_emp &a, const string &rpo, int ico)
         :abstr_emp(a), manager(a,ico), fink(a,rpo) { }
highfink::highfink(const fink &f, int ico)
         :abstr_emp(f), manager(f, ico),fink(f) { }
highfink::highfink(const manager &m, const string &rpo)
         :abstr_emp(m), manager(m), fink(m, rpo) { }
//highfink::highfink(const highfink &h);

// выводит все данные 
void highfink::ShowAll(ostream &os) const
{
    abstr_emp::ShowAll(os);
    os << left;
    os << setw(15) << setfill('.') << "In charge of" 
       << setw(10) << setfill(' ') << manager::InChargeOf() << endl;
    os << setw(15) << setfill(' ') << "Reports to" 
       << setw(10) << setfill(' ')<< fink::ReportsTo() << endl;
}

// запрашивает значения у пользователя
void highfink::SetAll()
{
    abstr_emp::SetAll();
    cout << "Enter in charge of (int): ";
    cin >> manager::InChargeOf();
    cout << "Enter reports to  (str): ";
    cin >> fink::ReportsTo();
}
