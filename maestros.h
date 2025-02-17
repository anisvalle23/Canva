#ifndef MAESTROS_H
#define MAESTROS_H

#include "estructuras.h"
#include "mainwindow.h"
#include <QMainWindow>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>


namespace Ui {
class Maestros;
}

class Maestros : public QMainWindow {
    Q_OBJECT

public:
    explicit Maestros(QWidget *parent = nullptr);
    ~Maestros();

    void saveMaestroUser();  // Guardar usuarios en archivo de texto
    void loadMaestroUser();  // Cargar usuarios desde archivo de texto
    QList<Usuario> getMaestrosUsers() const;   // Obtener la lista de maestros
    void addMaestro(const Usuario &nuevoMaestro); // Agregar un nuevo maestro
    void modificarMaestro(const QString &usuario, const Usuario &nuevoDatos); // Modificar maestro existente
    void eliminarMaestro(const QString &nombre);

private:
    Ui::Maestros *ui;
    QList<Usuario> maestrosUsers; // Lista de usuarios
    void addDefaultMaestro(); // Agregar usuario predeterminado

private slots:
    // void on_pushButton_2_clicked(); // Acción del botón (cambiar página)
    // void on_pushButton_6_clicked();
    // void on_pushButton_10_clicked();
    // void on_pushButton_14_clicked();
    // void on_pushButton_25_clicked();
    // void on_pushButton_29_clicked();
    // void on_pushButton_33_clicked();
    // void on_pushButton_38_clicked();
    // void on_pushButton_47_clicked();
    // void on_pushButton_51_clicked();
    // void on_pushButton_55_clicked();
    // void on_pushButton_3_clicked();
    // void on_pushButton_7_clicked();
    // void on_pushButton_11_clicked();
    // void on_pushButton_15_clicked();
    // void on_pushButton_19_clicked();
    // void on_pushButton_26_clicked();
    // void on_pushButton_30_clicked();
    // void on_pushButton_34_clicked();
    // void on_pushButton_39_clicked();
    // void on_pushButton_52_clicked();
    // void on_pushButton_56_clicked();
    // void on_pushButton_5_clicked();
    // void on_pushButton_9_clicked();
    // void on_pushButton_13_clicked();
    // void on_pushButton_17_clicked();
    // void on_pushButton_24_clicked();
    // void on_pushButton_28_clicked();
    // void on_pushButton_32_clicked();
    // void on_pushButton_37_clicked();
    // void on_pushButton_46_clicked();
    // void on_pushButton_50_clicked();
    // void on_pushButton_54_clicked();
    // void on_pushButton_20_clicked();
    // void on_pushButton_21_clicked();
    // void on_pushButton_22_clicked();
    // void on_pushButton_23_clicked();
    // void on_pushButton_41_clicked();
    // void on_pushButton_42_clicked();
    // void on_pushButton_43_clicked();
    // void on_pushButton_44_clicked();
    // void on_pushButton_45_clicked();
    // void on_pushButton_4_clicked();
    // void on_pushButton_8_clicked();
    // void on_pushButton_12_clicked();
    // void on_pushButton_58_clicked();
    // void on_pushButton_27_clicked();
    //  void on_pushButton_31_clicked();
    //  void on_pushButton_35_clicked();
    //   void on_pushButton_40_clicked();
    //   void on_pushButton_49_clicked();
    //    void on_pushButton_53_clicked();
    //    void on_pushButton_57_clicked();
};

#endif // MAESTROS_H
