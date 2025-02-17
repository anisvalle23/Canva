/********************************************************************************
** Form generated from reading UI file 'alumnos.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALUMNOS_H
#define UI_ALUMNOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Alumnos
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QLabel *label;
    QWidget *page_2;

    void setupUi(QMainWindow *Alumnos)
    {
        if (Alumnos->objectName().isEmpty())
            Alumnos->setObjectName("Alumnos");
        Alumnos->resize(1000, 700);
        centralwidget = new QWidget(Alumnos);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(0, 0, 1000, 700));
        page = new QWidget();
        page->setObjectName("page");
        label = new QLabel(page);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 1000, 700));
        label->setPixmap(QPixmap(QString::fromUtf8(":/resources/InicioAlumno.png")));
        label->setScaledContents(true);
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);
        Alumnos->setCentralWidget(centralwidget);

        retranslateUi(Alumnos);

        QMetaObject::connectSlotsByName(Alumnos);
    } // setupUi

    void retranslateUi(QMainWindow *Alumnos)
    {
        Alumnos->setWindowTitle(QCoreApplication::translate("Alumnos", "MainWindow", nullptr));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Alumnos: public Ui_Alumnos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALUMNOS_H
