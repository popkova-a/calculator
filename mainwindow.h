#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QStack>
#include <QString>
#include <QLCDNumber>
#include <cmath>
#include <string>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

    void calculate();
    int factorial(int x);

    void createLcdCalcWidget();
    void createSimpleCalcWidget();
    void createComplCalcWidget();

    void simpleCalc();
    void complCalc();

    QPushButton * createSimpleButton(const QString &str);
    QPushButton * createBinButton(const QString &str);
    QPushButton * createComplButton(const QString &str);

private:

    Ui::MainWindow *ui;

    QStack<QString> m_stk;

    QString m_strDisplay;

    QWidget *simpleCalcWidget;

    QWidget *complCalcWidget;

    QWidget *lcdCalcWidget;

    QWidget *mainWidget;

private slots:

    void slotSimpleButtonClicked();
    void slotComplButtonClicked();
    void slotBinButtonClicked();

    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
};
#endif // MAINWINDOW_H
