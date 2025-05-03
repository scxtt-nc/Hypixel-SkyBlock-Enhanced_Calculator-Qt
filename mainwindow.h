#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_calculateButton_clicked(); // Slot for button click
    void on_resetButton_clicked();     // Slot for the new reset button

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
