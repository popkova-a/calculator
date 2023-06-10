#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createLcdCalcWidget();
    createSimpleCalcWidget();
    createComplCalcWidget();
    simpleCalc();
    ui->radioButton->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::calculate()
{
    qreal fOperand2 = m_stk.pop().toDouble();
    QString strOperation = m_stk.pop();
    qreal fOperand1 = m_stk.pop().toDouble();
    double fResult = 0;

    if(strOperation == "+")
        fResult = fOperand1 + fOperand2;

    if(strOperation == QString::fromUtf8("\u00d7"))
        fResult = fOperand1 * fOperand2;

    if(strOperation == QString::fromUtf8("\u00f7"))
    {
        if(!fOperand2)
        {
            m_stk.clear();
            m_strDisplay.clear();
            ui->lcdNumber->display("Err");
            return;
        }
        else
            fResult = fOperand1 / fOperand2;
    }

    if(strOperation == QString::fromUtf8("\u2212"))
        fResult = fOperand1 - fOperand2;

    if(strOperation == "x" + QString::fromUtf8("\u207f"))
        fResult = pow(fOperand1,fOperand2);

    if(strOperation == QString::fromUtf8("\u207f") + QString::fromUtf8("\u221a"))
      {
        if(!fOperand2)
        {
            m_stk.clear();
            m_strDisplay.clear();
            ui->lcdNumber->display("Err");
            return;
        }
        else
            fResult = pow(fOperand1,1.0/fOperand2);
      }

    ui->lcdNumber->display(fResult);
}

int MainWindow::factorial(int x)
{
    if (x == 0)
        return 1;
    else
        return
              x * factorial(x - 1);
}

void MainWindow::slotSimpleButtonClicked()
{
    QString str = (qobject_cast<QPushButton *>(sender()))->text();

    if (str == "C")
    {
        m_stk.clear();
        m_strDisplay.clear();
        ui->lcdNumber->display("0");
        return;
    }

    if (str.contains(QRegExp("[0-9]")))
    {
        m_strDisplay += str;
        ui->lcdNumber->display(m_strDisplay);
        return;
    }

    if (str == ".")
    {
        qreal *p_buf = nullptr;
        if(!modf(ui->lcdNumber->value(), p_buf))
        {
            m_strDisplay = QString().setNum(ui->lcdNumber->value()) + ".";
            ui->lcdNumber->display(m_strDisplay);
        }
        return;
    }

    if(str == QString::fromUtf8("\u221a"))
     {
        m_strDisplay.clear();
        ui->lcdNumber->display(sqrt(ui->lcdNumber->value()));
        return;
     }

     if(str == QString::fromUtf8("x\u207B\u00B9"))
     {
        m_strDisplay.clear();
        if(!ui->lcdNumber->value())
        {
            m_stk.clear();
            m_strDisplay.clear();
            ui->lcdNumber->display("Err");
            return;
        }
        else
        {
          ui->lcdNumber->display(1.0/ui->lcdNumber->value());
          return;
        }
     }
}

void MainWindow::slotBinButtonClicked()
{
    QString str = (qobject_cast<QPushButton *>(sender()))->text();

    if (m_stk.count() >= 2)
    {
      m_stk.push(QString().setNum(ui->lcdNumber->value()));
      calculate();
      m_strDisplay.clear();
      m_stk.clear();
      m_stk.push(QString().setNum(ui->lcdNumber->value()));

      if (str != "=")
         m_stk.push(str);
    }
    else
    {
      m_stk.push(QString().setNum(ui->lcdNumber->value()));
      m_stk.push(str);
      m_strDisplay.clear();
    }
}

void MainWindow::slotComplButtonClicked()
{
    QString str = (qobject_cast<QPushButton *>(sender()))->text();

    if (str == "sh")
    {
        m_strDisplay.clear();
        ui->lcdNumber->display(sinh(ui->lcdNumber->value()));
        return;
    }

    if (str == "sin")
    {
        m_strDisplay.clear();
        ui->lcdNumber->display(sin(ui->lcdNumber->value()));
        return;
    }

    if (str == "Exp")
    {
        m_strDisplay.clear();
        ui->lcdNumber->display(exp(ui->lcdNumber->value()));
        return;
    }

    if (str == "x" + QString::fromUtf8("\u00b2"))
    {
        m_strDisplay.clear();
        ui->lcdNumber->display((ui->lcdNumber->value())*(ui->lcdNumber->value()));
        return;
    }

    if (str == "ch")
    {
        m_strDisplay.clear();
        ui->lcdNumber->display(cosh(ui->lcdNumber->value()));
        return;
    }

    if (str == "cos")
    {
        m_strDisplay.clear();
        ui->lcdNumber->display(cos(ui->lcdNumber->value()));
        return;
    }

    if (str == "ln")
    {
        m_strDisplay.clear();
        if(ui->lcdNumber->value()<=0)
        {
            m_stk.clear();
            m_strDisplay.clear();
            ui->lcdNumber->display("Err");
            return;
        }
        else
        {
            ui->lcdNumber->display(log(ui->lcdNumber->value()));
            return;
        }
    }

    if (str == "x" + QString::fromUtf8("\u00b3"))
    {
        m_strDisplay.clear();
        ui->lcdNumber->display(pow(ui->lcdNumber->value(), 3));
        return;
    }

    if (str == "th")
    {
        m_strDisplay.clear();
        ui->lcdNumber->display(tanh(ui->lcdNumber->value()));
        return;
    }

    if (str == "tan")
    {
        m_strDisplay.clear();
        ui->lcdNumber->display(tan(ui->lcdNumber->value()));
        return;
    }

    if (str == "log")
    {
        m_strDisplay.clear();
        if(ui->lcdNumber->value()<=0)
        {
            ui->lcdNumber->display("Err");
            return;
        }
        else
        {
            ui->lcdNumber->display(log10(ui->lcdNumber->value()));
            return;
        }
    }

    if (str == "n!")
    {
        qreal *pbuf = nullptr;

        m_strDisplay.clear();
        if(ui->lcdNumber->value()<0 || modf(ui->lcdNumber->value(),pbuf))
        {
            ui->lcdNumber->display("Err");
            return;
        }
        else
        {
            ui->lcdNumber->display(factorial(ui->lcdNumber->value()));
            return;
        }
    }

    if (str == QString::fromUtf8("\u03c0"))
    {
        m_strDisplay.clear();
        ui->lcdNumber->display(M_PI);
        return;
    }

    if (str == QString::fromUtf8("\u00b3") + QString::fromUtf8("\u221a"))
    {
        m_strDisplay.clear();
        ui->lcdNumber->display(cbrt(ui->lcdNumber->value()));
        return;
    }
}

QPushButton * MainWindow::createSimpleButton(const QString &str)
{
    QPushButton *pcmd = new QPushButton(str);
    pcmd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotSimpleButtonClicked()));

    return pcmd;
}

QPushButton * MainWindow::createBinButton(const QString &str)
{
    QPushButton *pcmd = new QPushButton(str);
    pcmd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotBinButtonClicked()));

    return pcmd;
}

QPushButton * MainWindow::createComplButton(const QString &str)
{
    QPushButton *pcmd = new QPushButton(str);
    pcmd->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    connect(pcmd, SIGNAL(clicked()), SLOT(slotComplButtonClicked()));

    return pcmd;
}

void MainWindow::createLcdCalcWidget()
{
    lcdCalcWidget = new QWidget();

    ui->lcdNumber->setDigitCount(10);
    ui->lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    ui->lcdNumber->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    ui->radioButton->setText("Обычный");
    ui->radioButton_2->setText("Инженерный");
    ui->radioButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->radioButton_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QGridLayout *plcdLayout = new QGridLayout(lcdCalcWidget);

    plcdLayout->addWidget(ui->lcdNumber,0,0,2,5);
    plcdLayout->addWidget(ui->radioButton,2,0,1,4);
    plcdLayout->addWidget(ui->radioButton_2,3,0,1,4);

    QPushButton *cleanButton = createSimpleButton("C");

    cleanButton->setFixedSize(84, 70);
    plcdLayout->addWidget(cleanButton,2,4,2,1);

    ui->lcdNumber->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->radioButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->radioButton_2->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    cleanButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    plcdLayout->setSpacing(0);
    plcdLayout->setContentsMargins(0,0,0,0);
    lcdCalcWidget->setLayout(plcdLayout);
}

void MainWindow::createSimpleCalcWidget()
{
    simpleCalcWidget = new QWidget();

    QGridLayout *ptopLayout = new QGridLayout(simpleCalcWidget);

    ptopLayout->addWidget(createSimpleButton("7"),0,0,1,1);
    ptopLayout->addWidget(createSimpleButton("8"),0,1,1,1);
    ptopLayout->addWidget(createSimpleButton("9"),0,2,1,1);
    ptopLayout->addWidget(createBinButton(QString::fromUtf8("\u00f7")),0,3,1,1);
    ptopLayout->addWidget(createSimpleButton(QString::fromUtf8("\u221a")),0,4,1,1);
    ptopLayout->addWidget(createSimpleButton("4"),1,0,1,1);
    ptopLayout->addWidget(createSimpleButton("5"),1,1,1,1);
    ptopLayout->addWidget(createSimpleButton("6"),1,2,1,1);
    ptopLayout->addWidget(createBinButton(QString::fromUtf8("\u00d7")),1,3,1,1);
    ptopLayout->addWidget(createSimpleButton(QString::fromUtf8("x\u207B\u00B9")),1,4,1,1);
    ptopLayout->addWidget(createSimpleButton("1"),2,0,1,1);
    ptopLayout->addWidget(createSimpleButton("2"),2,1,1,1);
    ptopLayout->addWidget(createSimpleButton("3"),2,2,1,1);
    ptopLayout->addWidget(createBinButton(QString::fromUtf8("\u2212")),2,3,1,1);
    ptopLayout->addWidget(createBinButton("="),2,4,2,1);
    ptopLayout->addWidget(createSimpleButton("0"),3,0,1,2);
    ptopLayout->addWidget(createSimpleButton("."),3,2,1,1);
    ptopLayout->addWidget(createBinButton("+"),3,3,1,1);

    ptopLayout->setSpacing(0);
    ptopLayout->setContentsMargins(0,0,0,0);
    simpleCalcWidget->setLayout(ptopLayout);
    simpleCalcWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void MainWindow::createComplCalcWidget()
{
    complCalcWidget=new QWidget();

    QGridLayout *ptopLayout = new QGridLayout(complCalcWidget);

    ptopLayout->addWidget(createComplButton("sh"),0,0,1,1);
    ptopLayout->addWidget(createComplButton("sin"),0,1,1,1);
    ptopLayout->addWidget(createComplButton("Exp"),0,2,1,1);
    ptopLayout->addWidget(createComplButton("x" + QString::fromUtf8("\u00b2")),0,3,1,1);
    ptopLayout->addWidget(createComplButton("ch"),1,0,1,1);
    ptopLayout->addWidget(createComplButton("cos"),1,1,1,1);
    ptopLayout->addWidget(createComplButton("ln"),1,2,1,1);
    ptopLayout->addWidget(createComplButton("x" + QString::fromUtf8("\u00b3")),1,3,1,1);
    ptopLayout->addWidget(createComplButton("th"),2,0,1,1);
    ptopLayout->addWidget(createComplButton("tan"),2,1,1,1);
    ptopLayout->addWidget(createComplButton("log"),2,2,1,1);
    ptopLayout->addWidget(createBinButton("x" + QString::fromUtf8("\u207f")),2,3,1,1);
    ptopLayout->addWidget(createComplButton("n!"),3,0,1,1);
    ptopLayout->addWidget(createComplButton(QString::fromUtf8("\u03c0")),3,1,1,1);
    ptopLayout->addWidget(createComplButton(QString::fromUtf8("\u00b3") + QString::fromUtf8("\u221a")),3,2,1,1);
    ptopLayout->addWidget(createBinButton(QString::fromUtf8("\u207f") + QString::fromUtf8("\u221a")),3,3,1,1);

    ptopLayout->setSpacing(0);
    ptopLayout->setContentsMargins(0,0,0,0);
    complCalcWidget->setLayout(ptopLayout);
    complCalcWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void MainWindow::simpleCalc()
{
    setWindowTitle("Калькулятор (Обычный)");
    setFixedSize(450, 450);
    mainWidget = new QWidget(this);
    mainWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainWidget->setFixedSize(450,450);

    QGridLayout *pmainLayout = new QGridLayout(mainWidget);
    pmainLayout->addWidget(lcdCalcWidget,0,0,2,5);
    pmainLayout->addWidget(simpleCalcWidget,2,0,4,5);
    pmainLayout->setSpacing(0);
    mainWidget->setLayout(pmainLayout);
    mainWidget->show();
}

void MainWindow::complCalc()
{
    ui->lcdNumber->setDigitCount(15);

    setWindowTitle("Калькулятор (Инженерный)");
    setFixedSize(780, 450);

    mainWidget = new QWidget(this);
    mainWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    mainWidget->setFixedSize(780,450);

    QGridLayout *pmainLayout = new QGridLayout(mainWidget);
    pmainLayout->addWidget(lcdCalcWidget,0,0,2,9);
    pmainLayout->addWidget(complCalcWidget,2,0,4,4);
    pmainLayout->addWidget(simpleCalcWidget,2,4,4,5);
    pmainLayout->setSpacing(0);
    mainWidget->setLayout(pmainLayout);
    mainWidget->show();
}

void MainWindow::on_radioButton_clicked()
{
    mainWidget->hide();
    simpleCalc();
}

void MainWindow::on_radioButton_2_clicked()
{
    mainWidget->hide();
    complCalc();
}
