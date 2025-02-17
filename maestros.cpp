#include "maestros.h"
#include "ui_maestros.h"
#include <QMessageBox>

Maestros::Maestros(QWidget *parent) : QMainWindow(parent), ui(new Ui::Maestros) {
    ui->setupUi(this);

    loadMaestroUser();

    if (maestrosUsers.isEmpty()) {
        addDefaultMaestro();
        saveMaestroUser();
    }
}

Maestros::~Maestros() {
    delete ui;
}

void Maestros::addDefaultMaestro() {
    Usuario defaultUser = {"0001", "maestro", "1234", "Profesor Predeterminado", "Maestro", "Matemáticas", 15000.0, "", ""};
    maestrosUsers.append(defaultUser);
}

void Maestros::saveMaestroUser() {
    QString rutaMaestros = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/maestros.txt";
    QFile file(rutaMaestros);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "❌ No se pudo abrir el archivo en " << rutaMaestros << " para escritura.";
        return;
    }

    QTextStream out(&file);
    if (maestrosUsers.isEmpty()) {
        qWarning() << "⚠ Advertencia: maestrosUsers está vacío antes de escribir en el archivo.";
    }

    for (const Usuario &user : maestrosUsers) {
        out << user.toText() << "\n";
        qDebug() << "Escribiendo línea en archivo:" << user.toText();
    }

    file.close();
    qDebug() << "✅ Archivo 'maestros.txt' actualizado correctamente.";
}


void Maestros::loadMaestroUser() {
    QString rutaMaestros = "/Users/anavalle/Desktop/Estru Datos I/MiniCanva/maestros.txt";
    QFile file(rutaMaestros);

    if (!file.exists()) {
        qWarning() << "🚨 El archivo 'maestros.txt' no existe en " << rutaMaestros << ". Creándolo.";
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "0001,maestro,1234,Profesor Predeterminado,Maestro,Matemáticas,15000.0,,\n"; // Usuario predeterminado
            file.close();
        }
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        maestrosUsers.clear();

        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            Usuario maestro = Usuario::fromText(line);

            if (!maestro.username.isEmpty()) {
                maestrosUsers.append(maestro);
                qDebug() << "✅ Maestro cargado:" << maestro.toText();
            } else {
                qWarning() << "⚠ Error en línea:" << line;
            }
        }
        file.close();
    } else {
        qWarning() << "❌ No se pudo abrir el archivo en " << rutaMaestros;
    }
}

void Maestros::eliminarMaestro(const QString &nombre) {
    loadMaestroUser();  // Cargar la lista actualizada de maestros

    // 🔹 Filtrar la lista para eliminar el maestro
    auto it = std::remove_if(maestrosUsers.begin(), maestrosUsers.end(),
                             [&](const Usuario &maestro) { return maestro.nombre == nombre; });

    if (it != maestrosUsers.end()) {
        maestrosUsers.erase(it, maestrosUsers.end());  // Eliminar el maestro de la lista
        saveMaestroUser();  // Guardar la lista actualizada en el archivo
        qDebug() << "✅ Maestro eliminado con éxito:" << nombre;
    } else {
        qDebug() << "⚠ No se encontró el maestro a eliminar:" << nombre;
    }
}
void Maestros::addMaestro(const Usuario &nuevoMaestro) {
    qDebug() << "🆕 Agregando nuevo maestro:" << nuevoMaestro.toText();

    // 🔹 Verificar si el usuario ya existe
    for (const Usuario &maestro : maestrosUsers) {
        if (maestro.username == nuevoMaestro.username) {
            QMessageBox::warning(nullptr, "Error", "El usuario ya existe. Elija otro nombre de usuario.");
            return;
        }
    }

    // 🔹 Agregar y guardar en archivo
    maestrosUsers.append(nuevoMaestro);

    // 🔹 Verifica si realmente se agregó antes de guardar
    qDebug() << "📌 Estado actual de maestrosUsers:";
    for (const Usuario &user : maestrosUsers) {
        qDebug() << user.toText();
    }

    saveMaestroUser();
}

QList<Usuario> Maestros::getMaestrosUsers() const {
    return maestrosUsers;
}

void Maestros::modificarMaestro(const QString &usuario, const Usuario &nuevoDatos) {
    loadMaestroUser();  // Cargamos la lista actualizada

    for (Usuario &maestro : maestrosUsers) {
        if (maestro.username == usuario) {
            maestro = nuevoDatos;  // 🔹 Modificamos los datos del maestro
            saveMaestroUser();    // 🔹 Guardamos los cambios en el archivo
            QMessageBox::information(nullptr, "Éxito", "El maestro ha sido actualizado correctamente.");
            return;
        }
    }

    QMessageBox::warning(nullptr, "Error", "El usuario no existe.");
}
