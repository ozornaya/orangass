#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QTextCodec>
#include "/home/vasuyan/Downloads/var7/laba_first_first/linkedlist.h"
#include "/home/vasuyan/Downloads/var7/laba_first_first/dish.h"
#include "/home/vasuyan/Downloads/var7/laba_first_first/dish.cpp"
#include "/home/vasuyan/Downloads/var7/laba_first_first/lunch.h"
#include <QObject>
#include <bits/stdc++.h>
#include "QStandardItemModel"
#include <QInputDialog>
#include "QStandardItem"
#include <QStringListModel>
#include <stdlib.h>
//#include <crtdbg.h>

static QString filepathto = "";
static QString filepathfrom = "";
static LinkedList<Dish*> statListG;
static LinkedList<Base*> statListForLunch;
static  std::string servicePath =
        "/home/vasuyan/Downloads/var7/laba_first_first/ServiceFileToReturn.txt";
static  std::string servicePathNode =
        "/home/vasuyan/Downloads/var7/laba_first_first/ServiceFileToReturnNode.txt";
static  std::string servicePathLunch =
        "/home/vasuyan/Downloads/var7/laba_first_first/ServiceFileToReturnLunch.txt";
static  std::string servicePathLunchForAdding =
        "/home/vasuyan/Downloads/var7/laba_first_first/ServiceFileToReturnSearchLunch";
int MainWindow::fillTheList(std::string path, int choice){
    /* Methon used for symplifying making of lists */
    QStringListModel *model1 = new QStringListModel(this);

    QStringList List;
    std::string pathToFileste = path;
    std::string line1;
    std::string line2, line3, line4, line5, line6, line7;
    std::fstream finas;
    finas.open(path);
    if(choice == 3){
        while(!finas.eof()){
            finas >> line1 >> line2 >> line3 >> line4 >> line5;
            QString qsWord1 = QString::fromStdString(line1);
            QString qsWord2 = QString::fromStdString(line2);
            QString qsWord3 = QString::fromStdString(line3);
            QString qsWord4 = QString::fromStdString(line4);
            QString qsWord5 = QString::fromStdString(line5);
            List << qsWord1<< qsWord2 <<qsWord3 << qsWord4<<qsWord5;
            model1->setStringList(List);
            ui->listView_2->setModel(model1);
            return 0;
        }
    }
    if(choice == 5){

        auto iterator = ::statListForLunch.begin();
        int j = 0;
        while(j < ::statListForLunch.size()){
            List << QString::fromStdString((*iterator)->returnName()) <<
                    QString::number((*iterator)->findEnergy());
            j++;
            iterator++;
        }
        model1->setStringList(List);
        ui->listView->setModel(model1);
        finas.close();
        return 0;
    }
    else{
        LinkedList<Dish*> list;
        list.getFromFile(path);
        while(!finas.eof()){
            finas >> line1 >> line2 >> line3 >> line4 >> line5 >> line6 >> line7;
            QString qsWord1 = QString::fromStdString(line1);
            QString en;
            if(line1!=""){ auto *n1 = list.accessNode(line1);
                en =
                     QString::fromStdString(std::to_string(floor(((n1->findEnergy())))));
            if(!List.contains(qsWord1) && en.toStdString() != "")
                List << qsWord1 << en;}
            else{
                if(!List.contains(qsWord1))
                    List << qsWord1;
            }
        }

        if(choice == 1){
            finas.close();
            model1->setStringList(List);
            ui->listView->setModel(model1);
            return List.size();
        }
        else if(choice == 2){
            finas.close();
            model1->setStringList(List);
            ui->listView_2->setModel(model1);
            return List.size();
        }
        else {
            finas.close();
            return List.size();
        }
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->findButton->setEnabled(false);
    ui->clearButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
    ui->findMeal->setEnabled(false);
    ui->changeSetButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::raiseError(){
    QMessageBox::information(0,"info", "error");
}

void MainWindow::on_setPathFrom_clicked()
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("Windows-1251"));
    QString filepathfrom;
    ::filepathfrom = QFileDialog::getOpenFileName(
                this,
                tr("Open file"),
                "C://",
                "All files (*.*);;Text file (*.txt);;"
                );
    if(::filepathfrom.toStdString() != ""){

        int size = fillTheList(::filepathfrom.toStdString(), 1);
        if(size != 0){
            ui->findButton->setEnabled(true);
            ui->clearButton->setEnabled(true);

            ui->findMeal->setEnabled(true);
            ui->changeSetButton->setEnabled(true);
            ui->deleteButton->setEnabled(true);
        }
    }
    else{
        raiseError();
    }
}

void MainWindow::on_setPathSave_clicked()
{
    ::filepathto = QFileDialog::getOpenFileName(
                this,
                tr("Open file"),
                "C://",
                "All files (*.*);;Text file (*.txt);;"
                );
    if(::filepathto.toStdString() != "")
        ui->saveButton->setEnabled(true);
}

void MainWindow::on_addButton_clicked()
{

    QString name = ui->newNameLine->text();
    std::string _name = name.toStdString();
    QString weight = ui->wLine->text();
    double wweight = weight.toDouble();
    QString fats = ui->fLine->text();
    double ffats = fats.toDouble();
    QString carbs = ui->carbLine->text();
    double ccarbs = carbs.toDouble();
    QString cell = ui->cLine->text();
    cell.toDouble();
    double ccell = cell.toDouble();
    QString acids = ui->acLine->text();
    double aacids = acids.toDouble();
    QString proteins = ui->pLine->text();
    double pproteins = proteins.toDouble();

    if(::filepathfrom.toStdString() == ""){
        Dish *new_dish = new Dish(_name,wweight,ffats,ccarbs,
                                  ccell,aacids,pproteins);
        ::statListG.insert(new_dish);
        ::statListG.returnToFile(::servicePath);
        int size = fillTheList(::servicePath, 1);
        if (size > 0){
            ui->findButton->setEnabled(true);
            ui->clearButton->setEnabled(true);
            ui->findMeal->setEnabled(true);
            ui->changeSetButton->setEnabled(true);
            ui->deleteButton->setEnabled(true);
        }

    }
    else{
        LinkedList<Base*> listFromFile;
        Dish *new_dish = new Dish(_name,wweight,ffats,ccarbs,
                                  ccell,aacids,pproteins);
        listFromFile.getFromFile(::filepathfrom.toStdString());
        listFromFile.insert(new_dish);
        listFromFile.returnToFile(::filepathfrom.toStdString());
        int size = fillTheList(::filepathfrom.toStdString(), 1);
        if (size > 0){
            ui->findButton->setEnabled(true);
            ui->clearButton->setEnabled(true);
            ui->findMeal->setEnabled(true);
            ui->changeSetButton->setEnabled(true);
            ui->deleteButton->setEnabled(true);
        }
    }

}

void MainWindow::on_changeSetButton_clicked()
{
    QString old_name = ui->oldNameLine->text();
    std::string old_name_str = old_name.toStdString();
    QString name = ui->newNameLine->text();
    std::string _name = name.toStdString();
    QString weight = ui->wLine->text();
    double wweight = weight.toDouble();
    QString fats = ui->fLine->text();
    double ffats = fats.toDouble();
    QString carbs = ui->carbLine->text();
    double ccarbs = carbs.toDouble();
    QString cell = ui->cLine->text();
    double ccell = cell.toDouble();
    QString acids = ui->acLine->text();
    double aacids = acids.toDouble();
    QString proteins = ui->pLine->text();
    double pproteins = proteins.toDouble();
    if(_name == "") _name = old_name_str;
    if(::filepathfrom.toStdString() == ""){
        if(::statListG.accessNode(old_name_str) == nullptr ||
                old_name_str == "") raiseError();
        else{
            double o_weight, o_fats, o_carbs, o_cell,o_prot,o_acids;
            auto accesableNode = ::statListG.accessNode(old_name_str);
            o_weight = accesableNode->retweight();
            o_fats = accesableNode->retfats();
            o_carbs = accesableNode->retcarbs();
            o_cell = accesableNode->retcellulose();
            o_prot = accesableNode->retproteins();
            o_acids = accesableNode->retacids();
            ::statListG.removeNode(accesableNode);
            Dish *n2 = new Dish(_name, wweight, o_fats,
                                o_prot, o_carbs, o_acids,o_cell);
            if(weight.toStdString() == "")
                n2->changeweight(wweight);
            if(fats.toStdString() != "")
                n2->changefats(ffats);
            if(carbs.toStdString() != "")
                n2->changecarbs(ccarbs);
            if(cell.toStdString() != "")
                n2->changecell(ccell);
            if(acids.toStdString() != "")
                n2->changeacids(aacids);
            if(proteins.toStdString() != "")
                n2->changeprot(pproteins);
            n2->changename(_name);
            ::statListG.insert(n2);
            ::statListG.returnToFile(::servicePath);
            fillTheList(::servicePath, 1);
            proteins.clear();
            weight.clear();
            name.clear();
            fats.clear();
            cell.clear();
            carbs.clear();
            acids.clear();
            old_name.clear();
            name.clear();
            delete accesableNode;
        }
    }
    else{
        LinkedList<Dish*> listFromFile;
        listFromFile.getFromFile(::filepathfrom.toStdString());
        if(listFromFile.accessNode(old_name_str) == nullptr ||
                old_name_str == "") return;
        else{
            if(_name == "") _name = old_name_str;
            double o_weight, o_fats, o_carbs, o_cell,o_prot,o_acids;
            auto accesableNode = listFromFile.accessNode(old_name_str);
            o_weight = accesableNode->retweight();
            o_fats = accesableNode->retfats();
            o_carbs = accesableNode->retcarbs();
            o_cell = accesableNode->retcellulose();
            o_prot = accesableNode->retproteins();
            o_acids = accesableNode->retacids();
            listFromFile.removeNode(accesableNode);
            Dish *n2 = new Dish(_name, wweight, o_fats,
                                o_prot, o_carbs, o_acids,o_cell);
            if(weight.toStdString() == "")
                n2->changeweight(wweight);
            if(fats.toStdString() != "")
                n2->changefats(ffats);
            if(carbs.toStdString() != "")
                n2->changecarbs(ccarbs);
            if(cell.toStdString() != "")
                n2->changecell(ccell);
            if(acids.toStdString() != "")
                n2->changeacids(aacids);
            if(proteins.toStdString() != "")
                n2->changeprot(pproteins);
            n2->changename(_name);

            listFromFile.insert(n2);
            listFromFile.returnToFile(::filepathfrom.toStdString());
            fillTheList(::filepathfrom.toStdString(), 1);
            proteins.clear();
            weight.clear();
            name.clear();
            fats.clear();
            cell.clear();
            carbs.clear();
            acids.clear();
            old_name.clear();
            name.clear();
            delete accesableNode;
            delete n2;
        }
    }

}

void MainWindow::on_deleteButton_clicked()
{
    bool ok;

    QString s = QInputDialog::getText(this, tr("Delete the meal"),
                                      tr("Name of the meal"), QLineEdit::Normal,
                                      "", &ok);

    std::string name = s.toStdString();
    if(::filepathfrom.toStdString() == "" && ::statListG.size() == 0) return;
    else if(::filepathfrom.toStdString() == "" && ::statListG.size() != 0){
        auto n1 = ::statListG.accessNode(name);
        if (n1 == nullptr){
            raiseError();
            return;
        }
        ::statListG.removeNode(n1);
        ::statListG.returnToFile(::servicePath);
        if(::statListG.size() == 0){
            ui->findButton->setEnabled(false);
            ui->clearButton->setEnabled(false);
            ui->findMeal->setEnabled(false);
            ui->changeSetButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
        }
        fillTheList(::servicePath, 1);
    }
    else {
        LinkedList<Dish*> llist;
        llist.getFromFile(::filepathfrom.toStdString());
        auto n1 = llist.accessNode(name);
        if (n1 == nullptr){
            raiseError();
        }else{
            llist.removeNode(n1);
            llist.returnToFile(::filepathfrom.toStdString());
        }
        if(llist.size() == 0){
            ui->findButton->setEnabled(false);
            ui->clearButton->setEnabled(false);
            ui->findMeal->setEnabled(false);
            ui->changeSetButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
        }
        fillTheList(::filepathfrom.toStdString(), 1);
    }
}


void MainWindow::on_findMeal_clicked()
{
    bool ok;
    double s = QInputDialog::getDouble(this, tr("Find meals"),
                                       tr("Meal:"), 0, 0, 4000, 1, &ok);
    bool flag = true;

    Dish *n1;
    if(ok == false) return;
    else if(::filepathfrom.toStdString() == "" && ::statListG.size() > 0){
        LinkedList<Dish*> l1;
        l1.getFromFile(::servicePath);
        auto iter = l1.begin();
        int j = 0;
        int i = 25;
        while(j < l1.size() && flag!=false){
            if((*iter)->findEnergy() == s ||
                    ((*iter)->findEnergy() >= (s-i)
                     && ((*iter)->findEnergy() <= (s))) ||
                    ((*iter)->findEnergy() > (s)
                     && ((*iter)->findEnergy() <= (s+i))
                     &&flag==true)) {
                flag = false;
                n1 = *iter;
            }
            iter++;
            j++;
            i++;
        }
        if(flag == false){
            LinkedList<Dish*> llist1;
            llist1.insert(n1);
            llist1.returnToFile(::servicePathNode);
            fillTheList(::servicePathNode, 2);
            QMessageBox::information(0,"info", "Found");
        }
        else QMessageBox::information(0,"info", "Not found");
    }
    else{
        LinkedList<Dish*> l1;
        l1.getFromFile(::filepathfrom.toStdString());
        auto iter = l1.begin();
        int j = 0;
        int i = 25;
        while(j < l1.size() && flag!=false){
            if((*iter)->findEnergy() == s ||
                    ((*iter)->findEnergy() >= (s-i)
                     && ((*iter)->findEnergy() <= (s))) ||
                    ((*iter)->findEnergy() > (s)
                     && ((*iter)->findEnergy() <= (s+i))
                     &&flag==true)) {
                flag = false;
                n1 = *iter;
            }
            iter++;
            j++;
            i = i + 25;
        }
        if(flag == false){
            LinkedList<Dish*> llist1;
            llist1.insert(n1);
            llist1.returnToFile(::servicePathNode);
            fillTheList(::servicePathNode, 2);
            QMessageBox::information(0,"info", "Found");
        }
        else QMessageBox::information(0,"info", "Not found");
    }

}

void MainWindow::on_clearButton_clicked()
{
    if(::filepathfrom.toStdString() == "" && ::statListG.size() > 0){
        ::statListG.removeAllNodes();
        ::statListG.returnToFile(::servicePath);
        fillTheList(::servicePath, 1);
        ui->findButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->saveButton->setEnabled(false);
        ui->findMeal->setEnabled(false);
        ui->changeSetButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
    }
    else{
        LinkedList<Dish*> llist1;
        llist1.getFromFile(::filepathfrom.toStdString());
        llist1.removeAllNodes();
        llist1.returnToFile(::filepathfrom.toStdString());
        fillTheList(::servicePath, 1);
        ui->findButton->setEnabled(false);
        ui->clearButton->setEnabled(false);
        ui->saveButton->setEnabled(false);
        ui->findMeal->setEnabled(false);
        ui->changeSetButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
    }
}

void MainWindow::on_saveButton_clicked()
{
    if(::filepathfrom.toStdString() == "" && ::statListG.size() > 0){
        if(::filepathto.toStdString() == ""){
            raiseError();
        }
        else{
            ::statListG.returnToFile(::filepathto.toStdString());
            QMessageBox::information(0,"info", "Saved");
        }
    }
    else if(::filepathto.toStdString() == ""){
        raiseError();
    }
    else {
        LinkedList<Dish*> llist1;
        llist1.getFromFile(::filepathfrom.toStdString());
        llist1.returnToFile(::filepathfrom.toStdString());
        QMessageBox::information(0,"info", "Saved");
    }
}

void MainWindow::on_findButton_clicked()
{
    bool ok;
    double s = QInputDialog::getDouble(this, tr("Find dinner"),
                                       tr("Find:"), 0, 0, 4000, 1, &ok);
    if(ok == false) return;
    if(::filepathfrom.toStdString() == "" && ::statListG.size() > 0){
        ::statListG.returnToFile(::servicePath);
        LinkedList<Dish*> llist;
        Dish *node1, *node2, *node3;

        std::string path = ::servicePath;
        llist.getFromFile(path);
        auto iter = llist.begin();
        bool flag = true;
        if (s == 0){
            node1 = *iter;
        }else{
            Dish *maxm;
            maxm = nullptr;
            int j = 0;
            int max = INT_MIN;
            iter = llist.begin();
            while (j < llist.size()){
                if ((*iter)->findEnergy() >= max && (*iter)->findEnergy()
                        <s*0.5){
                    maxm = *iter;
                    max = maxm->findEnergy();
                }
                j++;
                iter++;
            }
            node1 = maxm;
        }

        iter = llist.begin();
        flag = true;
        if (s <= 0){
            iter++;
            node2 = *iter;
        }
        else {
            if(node1 == nullptr) raiseError();else{
                Dish* maxm;
                maxm = nullptr;
                int j = 0;
                int max = INT_MIN;
                iter = llist.begin();
                while (j < llist.size()){
                    if ((*iter)->findEnergy() >= max &&
                            (*iter)->findEnergy()
                            <s*0.25 && (*iter)->returnName()
                            != node1->returnName()){
                        maxm = *iter;
                        max = maxm->findEnergy();
                    }
                    j++;
                    iter++;
                } node2 = maxm;
            }
        }
        iter = llist.begin();
        flag = true;
        if (s <= 0){
            iter++;
            iter++;
            node3 = *iter;
        }
        else{
            if (node1 == nullptr || node2 == nullptr) raiseError(); else{
                Dish* maxm;
                maxm = nullptr;
                int j = 0;
                int max = INT_MIN;
                iter = llist.begin();
                while (j < llist.size()){
                    if ((*iter)->findEnergy() >= max &&
                            (*iter)->findEnergy()
                            <s*0.25 && (*iter)->returnName()
                            != node1->returnName()
                            &&(*iter)->returnName() != node2->returnName()){
                        maxm = *iter;
                        max = maxm->findEnergy();
                    }
                    j++;
                    iter++;
                } node3 = maxm;
            }
        }

        if (node1 != nullptr && node2 != nullptr && node3 != nullptr &&
                node1->returnName()!=node2->returnName()
                && node1->returnName()!=node3->returnName() &&
                node2->returnName() != node3->returnName()){
            LinkedList<Base*> llist1;
            ::statListG.returnToFile(::servicePathLunchForAdding);
            llist1.getFromFile(::servicePathLunchForAdding);
            Lunch *lun = new Lunch("lunch", node1->returnName(),
                                   node2->returnName(), node3->returnName());
            lun->extractEnergy(node1, node2, node3);
            llist1.insert(lun);
            llist1.returnToFile(::servicePathLunchForAdding);
            fillTheList(::servicePathLunchForAdding, 1);
            fillTheList(::servicePathLunchForAdding, 3);
            QMessageBox::information(0,"info", "found");
        }else QMessageBox::information(0,"info", "Not found");
    }
    else{

        LinkedList<Dish*> llist;
        Dish *node1, *node2, *node3;
        std::string path = ::filepathfrom.toStdString();
        llist.getFromFile(path);
        auto iter = llist.begin();
        bool flag = true;
        if (s == 0){
            node1 = *iter;
        }else{
            Dish *maxm;
            maxm = nullptr;
            int j = 0;
            int max = INT_MIN;
            iter = llist.begin();
            while (j < llist.size()){
                if ((*iter)->findEnergy() >= max && (*iter)->findEnergy()
                        <s*0.5){
                    maxm = *iter;
                    max = maxm->findEnergy();
                }
                j++;
                iter++;
            }
            node1 = maxm;
        }

        iter = llist.begin();
        flag = true;
        if (s <= 0){
            iter++;
            node2 = *iter;
        }
        else {
            if(node1 == nullptr) raiseError();else{
                Dish* maxm;
                maxm = nullptr;
                int j = 0;
                int max = INT_MIN;
                iter = llist.begin();
                while (j < llist.size()){
                    if ((*iter)->findEnergy() >= max &&
                            (*iter)->findEnergy()
                            <s*0.25 && (*iter)->returnName()
                            != node1->returnName()){
                        maxm = *iter;
                        max = maxm->findEnergy();
                    }
                    j++;
                    iter++;
                } node2 = maxm;
            }
        }
        iter = llist.begin();
        flag = true;
        if (s <= 0){
            iter++;
            iter++;
            node3 = *iter;
        }
        else{
            if (node1 == nullptr || node2 == nullptr) raiseError(); else{
                Dish* maxm;
                maxm = nullptr;
                int j = 0;
                int max = INT_MIN;
                iter = llist.begin();
                while (j < llist.size()){
                    if ((*iter)->findEnergy() >= max &&
                            (*iter)->findEnergy()
                            <s*0.25 && (*iter)->returnName()
                            != node1->returnName()
                            &&(*iter)->returnName() != node2->returnName()){
                        maxm = *iter;
                        max = maxm->findEnergy();
                    }
                    j++;
                    iter++;
                } node3 = maxm;
            }
        }

        if (node1 != nullptr && node2 != nullptr && node3 != nullptr &&
                node1->returnName()!=node2->returnName()
                && node1->returnName()!=node3->returnName() &&
                node2->returnName() != node3->returnName()){
            LinkedList<Base*> llist1;

            ::statListForLunch.getFromFile(::filepathfrom.toStdString());
            Lunch *lun = new Lunch("lunch", node1->returnName(),
                                   node2->returnName(), node3->returnName());
            lun->extractEnergy(node1, node2, node3);
            ::statListForLunch.insert(lun);
            llist1.insert(lun);
            llist1.returnToFile(::servicePathLunch);
            fillTheList("", 5);
            fillTheList(::servicePathLunch, 3);
            ::statListForLunch.removeAllNodes();
            QMessageBox::information(0,"info", "found");
        }

        else QMessageBox::information(0,"info", "Not found");
    }}

