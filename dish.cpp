#include "dish.h"
// YURY BORODIN 2019
// LAB 1 PART 1 (INHER.)

Base::Base(const Base &other){
    this->name = other.name;
}
Base::Base(std::string n_name){
    if (n_name == " "){
        this->name = "Base";
    }
    else{
        this->name = n_name;
    }
}
Base::Base(){
    this->name = "Base";
}
Base::~Base(){

}
std::string Base::returnName(){
    return this->name;
}
int Base::who() const{
    return -1;
}
Dish::~Dish(){
};
int Dish::who() const{
    return 1;
}
double Dish::findEnergy(){
    double _energy = ((this->weight/100) * (this->fats * (9.29)     +
    this->proteins * (4.1) + this->carbs * (4.1) + this->acids * (2.2)
                                          + this->cellulose * (1.9)));
    return _energy;
}
void Dish::changename(std::string n_name){
    if (n_name != "")
    this->name = n_name;
}
Dish::Dish(const Dish &other){
        this->name = other.name;
        this->weight = other.weight;
        this->fats = other.fats;
        this->proteins = other.proteins;
        this->carbs = other.carbs;
        this->acids = other.acids;
        this->cellulose = other.cellulose;
    }
Dish::Dish(){
    this->name = "Dish";
    this->weight = 100;
    this->fats = 1;
    this->proteins = 1;
    this->carbs = 1;
    this->acids = 1;
    this->cellulose = 1;
}
Dish::Dish(std::string _name, double m_weight,
           double m_fats, double m_proteins, double m_carbs, double m_acids,
           double m_cellulose):Base(_name)
{
    if (_name == " " || _name.empty() || _name == ""){
        this->name = "Dish";
    }
    else this->name = _name;

    if (m_weight > 0)
    {
        this->weight = m_weight;
    }
    else{
        this->weight = 100;
    }
    if (m_fats > 0 && m_fats < 100)
    {
        this->fats = m_fats;
    }
    else{
        this->fats = 1;
    }
    if (m_proteins > 0 && m_proteins < 100)
    {
        this->proteins = m_proteins;
    }
    else {
        this->proteins = 1;
    }
    if (m_carbs > 0 && m_carbs < 100)
    {
        this->carbs = m_carbs;
    }
    else {
        this->carbs = 1;
    }
    if (m_acids > 0 && m_acids < 100)
    {
        this->acids = m_acids;
    }
    else {
        this->acids = 1;
    }

    if (m_cellulose > 0 && m_cellulose < 100)
    {
        this->cellulose = m_cellulose;
    }
    else
        this->cellulose = 1;

}
std::string Dish::returnName(){
    return name;
}
double Dish::retweight() const{
    return weight;
}
double Dish::retfats() const{
    return fats;
}
double Dish::retproteins() const{
    return proteins;
}
double Dish::retcarbs() const{
    return carbs;
}
double Dish::retacids() const{
    return acids;}
double Dish::retcellulose() const{
    return cellulose;}
void Dish::returnCharact(double* _weight, double* _fats, double* _proteins,
                           double* _carbs, double* _acids, double* _cellulose){
    *_weight = this->weight;
    *_fats = this->fats;
    *_proteins = this->proteins;
    *_carbs = this->carbs;
    *_acids = this->acids;
    *_cellulose = this->cellulose;
}
void Dish::changeweight(double n_weight){
    if (n_weight > 0)
    {
        this->weight = n_weight;
    }
}
void Dish::changefats(double n_fats){
    if (n_fats >= 0 && n_fats < 100)
    {
        this->fats = n_fats;
    }
}

void Dish::changeprot(double n_prot){
    if (n_prot >= 0 && n_prot < 100)
    {
        this->proteins = n_prot;
    }
}
void Dish::changecarbs(double n_carbs){
    if (n_carbs >= 0 && n_carbs < 100)
    {
        this->carbs = n_carbs;
    }
}
void Dish::changecell(double n_cellulose){
    if (n_cellulose >= 0 && n_cellulose < 100)
    {
        this->cellulose = n_cellulose;
    }
}
void Dish::changeacids(double n_acids){
    if (n_acids >= 0 && n_acids < 100)
    {
        this->acids = n_acids;
    }
}

double Lunch::findEnergy(){
    return this->energy;
}
double Lunch::extractEnergy(Dish* en1, Dish* en2, Dish* en3){
    this->energy =  en1->findEnergy() + en2->findEnergy()
            + en3->findEnergy();
    return this->energy;
}
int  Lunch::who() const{
    return 2;
}
Lunch::Lunch(){
    this->name = "Basic Lunch";
    this->name1 = "Soup";
    this->name2 = "Mac and Cheese";
    this->name3 = "Ice Cream";
}
Lunch::~Lunch(){}
Lunch::Lunch(std::string name,
      std::string _name1, std::string _name2, std::string _name3):
    Base (name){
    this->name = name;
    this->name1 = _name1;
    this->name2 = _name2;
    this->name3 = _name3;

}std::string Lunch::returnName(){
    return  this->name + " " + name1 + " " + name2 + " " + name3;
}
std::string Lunch::returnName1()  const{
    return name1;
}
std::string Lunch::returnName2() const{
    return name2;
}
std::string Lunch::returnName3() const{
    return name3;
}
void Lunch::changename(std::string _name){
    this->name = _name;
}
void Lunch::changename1(std::string _name1){
    this->name1 = _name1;
}
void Lunch::changename2(std::string _name2){
    this->name2 = _name2;
}
void Lunch::changename3(std::string _name3){
    this->name3 = _name3;
}

