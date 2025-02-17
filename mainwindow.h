#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "estructuras.h"  // Para la estructura Usuario
#include "registro.h"     // Para abrir la ventana Registro
#include "maestros.h"     // Para abrir la ventana Maestros
#include "alumnos.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // 🔹 Métodos para manejar maestros
    void addMaestro(const Usuario &nuevoMaestro);  // Agregar un nuevo maestro evitando duplicados
    void updateMaestroUsers();                     // Actualizar la lista de maestros

    // 🔹 Métodos para manejar alumnos (🚀 Agregamos esto)
    void addAlumno(const Usuario &nuevoAlumno);  // Agregar un nuevo alumno evitando duplicados

private slots:
    void on_InicioButton_clicked(); // Slot para manejar el botón de inicio de sesión

private:
    Ui::MainWindow *ui;

    // 🔹 Listas de usuarios
    QList<Usuario> registroUsers;  // Lista de usuarios del registro
    QList<Usuario> maestrosUsers;  // Lista de usuarios maestros
    QList<Usuario> alumnosUsers;   // Lista de usuarios alumnos

    // 🔹 Métodos para cargar y guardar datos desde archivos
    void loadRegistroUsers();  // Cargar usuarios del registro desde archivo
    void saveRegistroUsers();  // Guardar usuarios del registro en archivo

    void loadMaestroUsers();   // Cargar usuarios maestros desde archivo
    void saveMaestroUsers();   // Guardar usuarios maestros en archivo

    void loadAlumnosUsers();   // Cargar usuarios alumnos desde archivo
    void saveAlumnosUsers();   // Guardar usuarios alumnos en archivo
};

#endif // MAINWINDOW_H
