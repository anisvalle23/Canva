#ifndef REGISTRO_H
#define REGISTRO_H
#include "estructuras.h"
#include "mainwindow.h"
#include <QMainWindow>
#include <QList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include "maestros.h"
#include <QListWidgetItem>
#include <QListWidget>
#include "alumnos.h"
#include "clases.h"



class Maestros;

namespace Ui {
class Registro;
}

class Registro : public QMainWindow {
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = nullptr);
    ~Registro();

    void saveRegistroUser();  // Guardar usuarios en archivo de texto
    void loadRegistroUser();  // Cargar usuarios desde archivo de texto
    void cargarListaMaestros();
   void cargarListaMaestrosEliminar();
   void cargarListaAlumnos();
   void cargarListaAlumnosEliminar();
   void cargarListaClases();





private:
    Ui::Registro *ui;
    QList<Usuario> registroUsers; // Lista de usuarios
       Maestros *maestrosManager;
    Alumnos *alumnosManager;  // 🔹 Declaramos alumnosManager
     Clases *clasesManager;

    void addDefaultRegistro(); // Agregar usuario predeterminado

private slots:
    // Todos los slots definidos
    void on_CuentaButton_clicked();
    void on_AlumnoButton_clicked();
    void on_Cuenta1Button_clicked();
    void on_alum1Button_clicked();
    void on_nuevoAlumButton_clicked();
    void on_pushButton_clicked();
    void on_CancelarButton_clicked();
    void on_ModiAlumButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_ElimAlumButton_clicked();
    void on_CuentaButton_2_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_17_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_19_clicked();
    void on_pushButton_20_clicked();
    void on_pushButton_21_clicked();
    void on_pushButton_22_clicked();
    void on_pushButton_23_clicked();
    void on_pushButton_26_clicked();
    void on_pushButton_24_clicked();
    void on_pushButton_25_clicked();
    void on_pushButton_27_clicked();
    void on_pushButton_28_clicked();
    void on_pushButton_29_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_31_clicked();
    void on_pushButton_32_clicked();
    void on_pushButton_33_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_34_clicked();
    void on_pushButton_35_clicked();
    void on_pushButton_36_clicked();
    void on_pushButton_40_clicked();
    void on_pushButton_41_clicked();
    void on_pushButton_42_clicked();
    void on_pushButton_43_clicked();
    void on_pushButton_37_clicked();
    void on_pushButton_45_clicked();
    void on_pushButton_46_clicked();
    void on_pushButton_47_clicked();
    void on_pushButton_48_clicked();
    void on_pushButton_49_clicked();
    void on_pushButton_50_clicked();
    void on_pushButton_51_clicked();
    void on_pushButton_52_clicked();
    void on_pushButton_54_clicked();
    void on_pushButton_55_clicked();
    void on_pushButton_56_clicked();
    void on_pushButton_57_clicked();
    void on_pushButton_58_clicked();
    void on_pushButton_59_clicked();
    void on_pushButton_60_clicked();
    void on_pushButton_61_clicked();
    void on_pushButton_62_clicked();
    void on_pushButton_63_clicked();
    void on_pushButton_64_clicked();
    void on_pushButton_65_clicked();
    void on_pushButton_66_clicked();
    void on_pushButton_67_clicked();
    void on_pushButton_68_clicked();
    void on_pushButton_69_clicked();
    void on_pushButton_70_clicked();
    void on_pushButton_71_clicked();
    void on_pushButton_72_clicked();
    void on_pushButton_73_clicked();
    void on_pushButton_76_clicked();
    void on_pushButton_77_clicked();
    void on_pushButton_78_clicked();
    void on_pushButton_79_clicked();
    void on_pushButton_80_clicked();
    void on_pushButton_81_clicked();
    void on_pushButton_82_clicked();
    void on_pushButton_83_clicked();
    void on_pushButton_84_clicked();
    void on_pushButton_85_clicked();
    void on_pushButton_86_clicked();
    void on_pushButton_87_clicked();
    void on_pushButton_88_clicked();
    void on_pushButton_89_clicked();
    void on_pushButton_90_clicked();
    void on_pushButton_91_clicked();
    void on_pushButton_92_clicked();
    void on_pushButton_74_clicked();
    void on_pushButton_75_clicked();
    void on_pushButton_95_clicked();
    void on_pushButton_96_clicked();
    void on_pushButton_97_clicked();
    void on_pushButton_98_clicked();
    void on_pushButton_103_clicked();
    void on_pushButton_99_clicked();
    void on_pushButton_100_clicked();
    void on_pushButton_101_clicked();
    void on_pushButton_102_clicked();
    void on_pushButton_93_clicked();
    void on_pushButton_38_clicked();
    void on_pushButton_39_clicked();
    void on_pushButton_105_clicked();
    void on_pushButton_106_clicked();
    void on_pushButton_107_clicked();
    void on_pushButton_108_clicked();
    void on_pushButton_109_clicked();
    void on_pushButton_113_clicked();
    void on_pushButton_114_clicked();
    void on_pushButton_115_clicked();
    void on_pushButton_116_clicked();
    void on_pushButton_117_clicked();
    void on_pushButton_118_clicked();
    void on_pushButton_120_clicked();
    void on_pushButton_121_clicked();
    void on_pushButton_122_clicked();
    void on_pushButton_123_clicked();
    void on_pushButton_124_clicked();
    void on_pushButton_125_clicked();
    void on_pushButton_126_clicked();
    void on_pushButton_127_clicked();
    void on_pushButton_128_clicked();
    void on_pushButton_129_clicked();
    void on_pushButton_130_clicked();
    void on_pushButton_131_clicked();
    void on_pushButton_133_clicked();
    void on_pushButton_134_clicked();
    void on_pushButton_135_clicked();
    void on_pushButton_136_clicked();
    void on_pushButton_137_clicked();
    void on_pushButton_138_clicked();
    void on_pushButton_139_clicked();
    void on_pushButton_140_clicked();
    void on_pushButton_141_clicked();
    void on_pushButton_142_clicked();
    void on_pushButton_143_clicked();
    void on_pushButton_145_clicked();
    void on_pushButton_146_clicked();
    void on_pushButton_147_clicked();
    void on_pushButton_148_clicked();
    void on_pushButton_149_clicked();
    void on_pushButton_150_clicked();
    void on_pushButton_151_clicked();
    void on_pushButton_152_clicked();
    void on_pushButton_153_clicked();
    void on_pushButton_154_clicked();
    void on_pushButton_155_clicked();
    void on_pushButton_156_clicked();
    void on_pushButton_157_clicked();
    void on_pushButton_158_clicked();
    void on_pushButton_159_clicked();
    void on_pushButton_160_clicked();
    void on_pushButton_161_clicked();
    void on_pushButton_162_clicked();
    void on_pushButton_163_clicked();
    void on_pushButton_164_clicked();
    void on_pushButton_165_clicked();
    void on_pushButton_166_clicked();
    void on_pushButton_167_clicked();
    void on_pushButton_168_clicked();
    void on_pushButton_169_clicked();
    void on_pushButton_170_clicked();
    void on_pushButton_171_clicked();
    void on_pushButton_172_clicked();
    void on_pushButton_173_clicked();
    void on_pushButton_174_clicked();
    void on_pushButton_175_clicked();
    void on_pushButton_176_clicked();
    void on_pushButton_144_clicked();
    void on_pushButton_177_clicked();
    void on_pushButton_178_clicked();
    void on_pushButton_179_clicked();
    void on_pushButton_180_clicked();
    void on_pushButton_181_clicked();
    void on_pushButton_182_clicked();
    void on_pushButton_183_clicked();
    void on_AgregarButton_clicked();
    // void on_pushButton_4_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    // vo;id on_listWidget_2_itemDoubleClicked(QListWidgetItem *item)

    void on_listWidgetEliminarAlumnos_itemDoubleClicked(QListWidgetItem *item);
    void on_AggButton_clicked();
    void on_listWidgetAlumnos_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_4_clicked();
    void on_AgregarButton_2_clicked();
    void on_listWidgetClases_itemDoubleClicked(QListWidgetItem *item);
};

#endif // REGISTRO_H
