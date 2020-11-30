#ifndef DISH_H
#define DISH_H
#include <string>
#include "node.h"
#include "math.h"
// YURY BORODIN 2019
class Base {
public:

    std::string name;
    Base(const Base &other);

    virtual ~Base();
    virtual int who() const;
    Base(std::string n_name);
    Base();
    virtual double findEnergy() = 0;
    virtual std::string returnName();
    virtual void returnCharact(double* _weight, double* _fats,
                               double* _proteins, double* _carbs,
                               double* _acids, double* _cellulose){}
    virtual void changename(std::string m_name) = 0;
};

class Dish: public Base{
public:
    double weight, fats, proteins, carbs, acids, cellulose;
    std::string name;
    virtual ~Dish();

    int virtual who() const;
    virtual double findEnergy();
    virtual void changename(std::string n_name);
    Dish(const Dish &other);
    Dish();
    Dish(std::string _name, double m_weight, double m_fats,
         double m_proteins, double m_carbs, double m_acids,
         double m_cellulose);
    virtual std::string returnName();
    double retEnergy() const;
    double retweight() const;
    double retfats() const;
    double retproteins() const;
    double retcarbs() const;
    double retacids() const;
    double retcellulose() const;
    virtual void returnCharact(double* _weight, double* _fats,
                               double* _proteins,double* _carbs,
                               double* _acids, double* _cellulose);
    void changeweight(double n_weight);
    void changefats(double n_fats);

    void changeprot(double n_prot);
    void changecarbs(double n_carbs);
    void changecell(double n_cellulose);
    void changeacids(double n_acids);
};

class Lunch : public Base {
protected:
    double energy;
    std::string name, name1,name2, name3;
    template<class T>
    friend class LinkedList;
public:
    double findEnergy();
    double extractEnergy(Dish* en1, Dish* en2, Dish* en3);
    int virtual who() const;
    Lunch();
    virtual ~Lunch();
    Lunch(std::string name,
          std::string _name1, std::string _name2, std::string _name3);
    virtual std::string returnName();
    std::string returnName1()  const;
    std::string returnName2() const;
    std::string returnName3() const;
    void changename(std::string _name);
    void changename1(std::string _name1);
    void changename2(std::string _name2);
    void changename3(std::string _name3);

};

#endif // CAFETERIA_H
