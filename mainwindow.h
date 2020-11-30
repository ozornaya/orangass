#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void raiseError();
    int fillTheList(std::string path, int choice);
private slots:
    void on_setPathFrom_clicked();

    void on_setPathSave_clicked();

    void on_addButton_clicked();


    void on_changeSetButton_clicked();

    void on_deleteButton_clicked();

    void on_findMeal_clicked();

    void on_clearButton_clicked();

    void on_saveButton_clicked();

    void on_findButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
