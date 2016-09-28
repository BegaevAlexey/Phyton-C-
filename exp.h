//exp.h - иерархия классов с множественным наследованием и базовым виртульным классом

#ifndef EXP_H_
#define EXP_H_

#include <iostream>
#include <string>

using namespace std;

//абстактный базовый класс
class abstr_emp
{
private:
    //данные работника
    string fname;
    string lname;
    string job;

public:
    abstr_emp();
    abstr_emp(const string &fn, const string &ln, const string &j);
    virtual void ShowAll(ostream &os) const;      // выводит все данные
    virtual void SetAll();          // запрашивает значения у пользователя
    friend ostream & operator<<(ostream &os, const abstr_emp &e); // выводит только имя и фамилию
    virtual ~abstr_emp() = 0;       // виртуальный базовый класс
};

class employee : public abstr_emp
{
public:
    employee();
    employee(const string &fn, const string &ln, const string &j);
    virtual void ShowAll(ostream &os) const;
    virtual void SetAll();
};

class manager : virtual public abstr_emp
{
private:
    int inchargeof; // количество подчененных

protected:
    int InChargeOf() const {return inchargeof;}
    int & InChargeOf() {return inchargeof;}

public:
    manager();
    manager(const string &fn, const string &ln,
            const string &j, int ico);
    manager(const abstr_emp &e, int ico);
    manager(const manager &m);
    virtual void ShowAll(ostream &os) const;
    virtual void SetAll();
};

class fink : virtual public abstr_emp
{
private:
    string reportsto;    //кому отправлять отчет

protected:
    const string ReportsTo() const {return reportsto;}
    string & ReportsTo() {return reportsto;}

public:
    fink();
    fink(const string &fn, const string &ln,
         const string &j, const string &rpo);
    fink(const abstr_emp &e, const string &rpo);
    fink(const fink &e);
    virtual void ShowAll(ostream &os) const;
    virtual void SetAll();
};

//надзор за управляющими
class highfink : public manager, public fink
{
public:
    highfink();
    highfink(const string &fn, const string &ln,
             const string &j, const string &rpo, int ico);
    highfink(const abstr_emp &e, const string &rpo, int ico);
    highfink(const fink &f, int ico);
    highfink(const manager &m, const string &pro);
    virtual void ShowAll(ostream &os) const;
    virtual void SetAll();
};

#endif