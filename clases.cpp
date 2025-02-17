#include "clases.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Clases::Clases() {
    loadClases();
}

void Clases::saveClases() {
    QFile file(archivoClases);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Clase &clase : listaClases) {
            out << clase.toText() << "\n";  // 📌 Guardamos en formato de texto
        }
        file.close();
        qDebug() << "✅ Archivo 'registro.txt' actualizado con clases.";
    } else {
        qWarning() << "❌ No se pudo abrir 'registro.txt' para guardar clases.";
    }
}

void Clases::loadClases() {
    QFile file(archivoClases);

    // 🔹 Si el archivo no existe, lo creamos vacío
    if (!file.exists()) {
        qWarning() << "🚨 El archivo 'registro.txt' no existe. Se creará al guardar.";
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "❌ No se pudo abrir 'registro.txt' para cargar clases.";
        return;
    }

    QTextStream in(&file);
    listaClases.clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            Clase clase = Clase::fromText(line);
            if (!clase.id.isEmpty()) {
                listaClases.append(clase);
                qDebug() << "✅ Clase cargada:" << clase.toText();
            } else {
                qWarning() << "⚠ Error en línea:" << line;
            }
        }
    }
    file.close();
}

void Clases::addClase(const Clase &nuevaClase) {
    for (const Clase &clase : listaClases) {
        if (clase.id == nuevaClase.id) {
            qWarning() << "⚠ La clase con ID" << nuevaClase.id << "ya existe.";
            return;
        }
    }

    listaClases.append(nuevaClase);
    saveClases();
    qDebug() << "✅ Nueva clase agregada:" << nuevaClase.toText();
}

void Clases::eliminarClase(const QString &id) {
    auto it = std::remove_if(listaClases.begin(), listaClases.end(),
                             [&](const Clase &clase) { return clase.id == id; });

    if (it != listaClases.end()) {
        listaClases.erase(it, listaClases.end());  // Elimina el elemento correctamente
        saveClases();
        qDebug() << "✅ Clase eliminada con ID:" << id;
    } else {
        qWarning() << "⚠ No se encontró la clase con ID:" << id;
    }
}

// // 🔹 Método para modificar una clase existente
// void Clases::modificarClase(const QString &id, const Clase &nuevosDatos) {
//     for (Clase &clase : listaClases) {
//         if (clase.id == id) {
//             clase = nuevosDatos;  // Modifica los datos de la clase
//             saveClases();  // Guarda los cambios
//             qDebug() << "✅ Clase modificada:" << nuevosDatos.toText();
//             return;
//         }
//     }
//     qWarning() << "⚠ No se encontró la clase con ID:" << id;
// }

// // 🔹 Método para obtener una clase por su ID
// Clase Clases::getClasePorID(const QString &id) const {
//     for (const Clase &clase : listaClases) {
//         if (clase.id == id) {
//             return clase;
//         }
//     }
//     return {};  // Devuelve un objeto vacío si no se encuentra
// }
