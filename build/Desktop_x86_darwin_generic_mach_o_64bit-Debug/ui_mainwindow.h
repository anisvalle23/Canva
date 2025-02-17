/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLineEdit *user;
    QLineEdit *password;
    QPushButton *InicioButton;
    QComboBox *comboBox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        MainWindow->setAutoFillBackground(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 1000, 700));
        label->setPixmap(QPixmap(QString::fromUtf8(":/resources/Inicio.png")));
        label->setScaledContents(true);
        user = new QLineEdit(centralwidget);
        user->setObjectName("user");
        user->setGeometry(QRect(320, 230, 361, 61));
        QFont font;
        font.setPointSize(18);
        user->setFont(font);
        user->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"border: none;\n"
"color: black; \n"
""));
        password = new QLineEdit(centralwidget);
        password->setObjectName("password");
        password->setGeometry(QRect(320, 360, 361, 51));
        password->setFont(font);
        password->setStyleSheet(QString::fromUtf8("background: transparent;\n"
"border: none;\n"
"color: black; \n"
""));
        password->setEchoMode(QLineEdit::EchoMode::Password);
        InicioButton = new QPushButton(centralwidget);
        InicioButton->setObjectName("InicioButton");
        InicioButton->setGeometry(QRect(540, 420, 141, 41));
        InicioButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background: transparent;\n"
"    border: none;\n"
"    color: white;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background: rgba(255, 255, 255, 0.2); /* Fondo semi-transparente */\n"
"    border-radius: 5px;\n"
"}\n"
""));
        comboBox = new QComboBox(centralwidget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        comboBox->setGeometry(QRect(310, 430, 201, 41));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        InicioButton->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Registro", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Maestro", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Alumno", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
