#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "registro.h"
#include "maestros.h"
#include "alumnos.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Cargar usuarios desde archivos de texto
    loadRegistroUsers();
    loadMaestroUsers();
    loadAlumnosUsers();
}

MainWindow::~MainWindow() {
    delete ui;
}

// 🔹 Cargar usuarios del archivo de registro
void MainWindow::loadRegistroUsers() {
    QString filePath = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/registro.txt";
    QFile registroFile(filePath);

    if (!registroFile.exists()) {
        qWarning() << "🚨 El archivo 'registro.txt' NO existe en la ruta:" << filePath;
        return;
    }

    if (!registroFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ No se pudo abrir el archivo.";
        return;
    }

    QTextStream in(&registroFile);
    registroUsers.clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || !line.contains(",")) continue;

        Usuario user = Usuario::fromText(line);
        if (!user.username.isEmpty()) {
            registroUsers.append(user);
            qDebug() << "✅ Usuario agregado al registro: " << user.username;
        }
    }

    registroFile.close();
}

// 🔹 Cargar usuarios del archivo de maestros
void MainWindow::loadMaestroUsers() {
    QString rutaMaestros = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/maestros.txt";
    QFile maestrosFile(rutaMaestros);

    if (!maestrosFile.exists()) {
        qWarning() << "🚨 El archivo 'maestros.txt' NO existe en la ruta:" << rutaMaestros;
        return;
    }

    if (!maestrosFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ No se pudo abrir el archivo.";
        return;
    }

    QTextStream in(&maestrosFile);
    maestrosUsers.clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || !line.contains(",")) continue;

        Usuario maestro = Usuario::fromText(line);
        if (!maestro.username.isEmpty()) {
            maestrosUsers.append(maestro);
            qDebug() << "✅ Maestro agregado: " << maestro.username;
        }
    }

    maestrosFile.close();
}

// 🔹 Guardar usuarios de maestros
void MainWindow::saveMaestroUsers() {
    QString rutaMaestros = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/maestros.txt";
    QFile maestrosFile(rutaMaestros);

    if (!maestrosFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "❌ No se pudo abrir el archivo 'maestros.txt' para escritura.";
        return;
    }

    QTextStream out(&maestrosFile);
    for (const Usuario &maestro : maestrosUsers) {
        out << maestro.toText() << "\n";
    }

    maestrosFile.close();
    qDebug() << "📁 Maestros guardados correctamente.";
}

// 🔹 Cargar usuarios del archivo de alumnos
void MainWindow::loadAlumnosUsers() {
    QString rutaAlumnos = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/alumnos.txt";
    QFile alumnosFile(rutaAlumnos);

    if (!alumnosFile.exists()) {
        qWarning() << "🚨 El archivo 'alumnos.txt' NO existe en la ruta:" << rutaAlumnos;
        return;
    }

    if (!alumnosFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ No se pudo abrir el archivo.";
        return;
    }

    QTextStream in(&alumnosFile);
    alumnosUsers.clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || !line.contains(",")) continue;

        Usuario alumno = Usuario::fromText(line);
        if (!alumno.username.isEmpty()) {
            alumnosUsers.append(alumno);
            qDebug() << "✅ Alumno agregado: " << alumno.username;
        }
    }

    alumnosFile.close();
}

// 🔹 Guardar usuarios de alumnos
void MainWindow::saveAlumnosUsers() {
    QString rutaAlumnos = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/alumnos.txt";
    QFile alumnosFile(rutaAlumnos);

    if (!alumnosFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "❌ No se pudo abrir el archivo 'alumnos.txt' para escritura.";
        return;
    }

    QTextStream out(&alumnosFile);
    for (const Usuario &alumno : alumnosUsers) {
        out << alumno.toText() << "\n";
    }

    alumnosFile.close();
    qDebug() << "📁 Alumnos guardados correctamente.";
}

// 🔹 Agregar un nuevo alumno
void MainWindow::addAlumno(const Usuario &nuevoAlumno) {
    for (const Usuario &alumno : alumnosUsers) {
        if (alumno.username == nuevoAlumno.username) {
            QMessageBox::warning(this, "Error", "El usuario ya existe. Elija otro nombre de usuario.");
            return;
        }
    }

    alumnosUsers.append(nuevoAlumno);
    saveAlumnosUsers();
    qDebug() << "✅ Nuevo alumno agregado: " << nuevoAlumno.toText();
}

// 🔹 Iniciar sesión en la aplicación
void MainWindow::on_InicioButton_clicked() {
    QString username = ui->user->text().trimmed();
    QString password = ui->password->text().trimmed();

    qDebug() << "🔍 Intentando iniciar sesión con:" << username << password;

    // Comparar con el registro de usuarios administrativos
    for (const Usuario &user : registroUsers) {
        if (user.username == username && user.password == password) {
            qDebug() << "✅ Inicio de sesión exitoso (Registro) para:" << username;
            auto *registroWindow = new Registro();
            registroWindow->show();
            this->close();
            return;
        }
    }

    // Comparar con los maestros
    for (const Usuario &maestro : maestrosUsers) {
        if (maestro.username == username && maestro.password == password) {
            qDebug() << "✅ Inicio de sesión exitoso (Maestro) para:" << username;
            auto *maestrosWindow = new Maestros();
            maestrosWindow->show();
            this->close();
            return;
        }
    }

    // Comparar con los alumnos
    for (const Usuario &alumno : alumnosUsers) {
        if (alumno.username == username && alumno.password == password) {
            qDebug() << "✅ Inicio de sesión exitoso (Alumno) para:" << username;
            auto *alumnosWindow = new Alumnos();
            alumnosWindow->show();
            this->close();
            return;
        }
    }

    qDebug() << "❌ Inicio de sesión fallido.";
    QMessageBox::warning(this, "Error", "Usuario o contraseña incorrectos.");
}
