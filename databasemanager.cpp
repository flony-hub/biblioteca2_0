#include "databasemanager.h"
#include <QDebug>
#include <QCoreApplication>
#include <QDir>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>


DatabaseManager& DatabaseManager::getInstance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}

DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

bool DatabaseManager::openDatabase(const QString& dbPath) {
    QString path = dbPath.isEmpty() ? 
        QCoreApplication::applicationDirPath() + "/biblioteca.db" : dbPath;
    
    m_db.setDatabaseName(path);
    qDebug() << "Base de datos en:" << QDir::toNativeSeparators(path);
    
    if (!m_db.open()) {
        qDebug() << "Error al abrir la base de datos:" << m_db.lastError().text();
        return false;
    }
    return true;
}

void DatabaseManager::closeDatabase() {
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool DatabaseManager::isOpen() const {
    return m_db.isOpen();
}

QString DatabaseManager::getLastError() const {
    return m_lastError;
}



bool DatabaseManager::createTables() {
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    bool success = true;

    // Tabla libro
    success &= query.exec("CREATE TABLE IF NOT EXISTS libro ("
                         "isbn TEXT PRIMARY KEY, "
                         "titulo TEXT NOT NULL, "
                         "autor TEXT NOT NULL, "
                         "editorial TEXT, "
                         "año INTEGER, "
                         "pais TEXT, "
                         "disponible BOOLEAN DEFAULT 1)");

    // Tabla usuario (corregido nombre de tabla)
    success &= query.exec("CREATE TABLE IF NOT EXISTS usuario ("
                          "dni TEXT PRIMARY KEY, "
                          "nombre TEXT NOT NULL, "
                          "email TEXT NOT NULL, "
                          "telefono TEXT, "
                          "domicilio TEXT NOT NULL)");

    // Tabla prestamo
    success &= query.exec("CREATE TABLE IF NOT EXISTS prestamo ("
                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                         "isbn_libro TEXT NOT NULL, "
                         "dni_usuario TEXT NOT NULL, "
                         "fecha_prestamo DATE NOT NULL, "
                         "fecha_devolucion DATE, "
                         "FOREIGN KEY (isbn_libro) REFERENCES libro(isbn), "
                         "FOREIGN KEY (dni_usuario) REFERENCES usuario(dni))");

    if (!success) {
        qDebug() << "Error al crear tablas:" << query.lastError().text();
    }

    return success;
}


// Operaciones para la tabla libro
//----------------------------------------------------------------------------------------------------
bool DatabaseManager::agregarLibro(const Libro& libro) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return false;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO libro (isbn, titulo, autor, editorial, año, pais) "
                  "VALUES (:isbn, :titulo, :autor, :editorial, :año, :pais)");
    query.bindValue(":isbn", libro.isbn());
    query.bindValue(":titulo", libro.titulo());
    query.bindValue(":autor", libro.autor());
    query.bindValue(":editorial", libro.editorial());
    query.bindValue(":año", libro.anio());
    query.bindValue(":pais", libro.pais());

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Error al agregar libro:" << m_lastError;
        return false;
    }

    return true;
}

Libro DatabaseManager::obtenerLibro(const QString& isbn) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return Libro();
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM libro WHERE isbn = :isbn");
    query.bindValue(":isbn", isbn);

    if (query.exec() && query.next()) {
        return Libro(query.value("isbn").toString(),
                     query.value("titulo").toString(),
                     query.value("autor").toString(),
                     query.value("editorial").toString(),
                     query.value("año").toInt(),
                     query.value("pais").toString(),
                     query.value("disponible").toBool());
    }
    return Libro();
}

QList<Libro> DatabaseManager::obtenerTodosLibros() {
    QList<Libro> libros;
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return libros;
    }

    QSqlQuery query("SELECT * FROM libro");

    while (query.next()) {
        libros.append(Libro(query.value("isbn").toString(),
                            query.value("titulo").toString(),
                            query.value("autor").toString(),
                            query.value("editorial").toString(),
                            query.value("año").toInt(),
                            query.value("pais").toString(),
                            query.value("disponible").toBool()));
    }
    return libros;
}

bool DatabaseManager::actualizarLibro(const Libro& libro) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return false;
    }
    QSqlQuery query;
    query.prepare("UPDATE libro SET titulo = :titulo, autor = :autor, editorial = :editorial, "
                  "año = :año, pais = :pais WHERE isbn = :isbn");
    query.bindValue(":titulo", libro.titulo());
    query.bindValue(":autor", libro.autor());
    query.bindValue(":editorial", libro.editorial());
    query.bindValue(":año", libro.anio());
    query.bindValue(":pais", libro.pais());
    query.bindValue(":isbn", libro.isbn());

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Error al actualizar libro:" << m_lastError;
        return false;
    }

    return true;
}

bool DatabaseManager::eliminarLibro(const QString& isbn) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return false;
    }
    QSqlQuery query;
    query.prepare("DELETE FROM libro WHERE isbn = :isbn");
    query.bindValue(":isbn", isbn);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Error al eliminar libro:" << m_lastError;
        return false;
    }

    return true;
}

QList<Libro> DatabaseManager::buscarLibros(const QString& titulo, const QString& autor,
                                           const QString& editorial, const QString& palabrasClave)
{
    QList<Libro> libros;

    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return libros;
    }

    QSqlQuery query;
    QString sql = "SELECT * FROM libro WHERE 1=1";

    // Agregar condiciones dinámicamente
    if (!titulo.isEmpty())
        sql += " AND LOWER(titulo) LIKE LOWER(:titulo)";
    if (!autor.isEmpty())
        sql += " AND LOWER(autor) LIKE LOWER(:autor)";
    if (!editorial.isEmpty())
        sql += " AND LOWER(editorial) LIKE LOWER(:editorial)";
    if (!palabrasClave.isEmpty())
        sql += " AND LOWER(titulo || ' ' || autor || ' ' || editorial) LIKE LOWER(:palabrasClave)";

    query.prepare(sql);

    // Enlazar valores
    if (!titulo.isEmpty())
        query.bindValue(":titulo", "%" + titulo + "%");
    if (!autor.isEmpty())
        query.bindValue(":autor", "%" + autor + "%");
    if (!editorial.isEmpty())
        query.bindValue(":editorial", "%" + editorial + "%");
    if (!palabrasClave.isEmpty())
        query.bindValue(":palabrasClave", "%" + palabrasClave + "%");

    if (!query.exec()) {
        qDebug() << "Error en búsqueda de libros:" << query.lastError().text();
        return libros;
    }

    while (query.next()) {
        libros.append(Libro(
            query.value("isbn").toString(),
            query.value("titulo").toString(),
            query.value("autor").toString(),
            query.value("editorial").toString(),
            query.value("año").toInt(),
            query.value("pais").toString(),
            query.value("disponible").toBool()
            ));
    }

    return libros;
}



// Operaciones para la tabla usuario
//-----------------------------------------------------------------------------------------------------
bool DatabaseManager::agregarUsuario(const Usuario& usuario) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return false;
    }
    QSqlQuery query;
    query.prepare("INSERT INTO usuario (dni, nombre, email, telefono, domicilio) "
                  "VALUES (:dni, :nombre, :email, :telefono, :domicilio)");
    query.bindValue(":dni", usuario.dni());
    query.bindValue(":nombre", usuario.nombre());
    query.bindValue(":email", usuario.email());
    query.bindValue(":telefono", usuario.telefono());
    query.bindValue("domicilio", usuario.domicilio());

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Error al agregar usuario:" << m_lastError;
        return false;
    }

    return true;
}

Usuario DatabaseManager::obtenerUsuario(const QString& dni) {
    if (!m_db.isOpen() && !openDatabase()) {
        qDebug() << "Error: No se pudo abrir la base de datos";
        return Usuario();
    }

    QSqlQuery query;
    query.prepare("SELECT dni, nombre, email, telefono, domicilio FROM usuario WHERE dni = :dni");
    query.bindValue(":dni", dni);

    if (!query.exec()) {
        qCritical() << "Error al buscar usuario:" << query.lastError().text();
        return Usuario();
    }

    if (query.next()) {
        return Usuario(
            query.value("dni").toString(),
            query.value("nombre").toString(),
            query.value("email").toString(),
            query.value("telefono").toString(),
            query.value("domicilio").toString());
    }

    qDebug() << "No se encontró usuario con DNI:" << dni;
    return Usuario();
}


QList<Usuario> DatabaseManager::obtenerTodosUsuarios() {
    QList<Usuario> usuarios;
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return usuarios;
    }
    QSqlQuery query("SELECT * FROM usuario");

    while (query.next()) {
        usuarios.append(Usuario(query.value("dni").toString(),
                               query.value("nombre").toString(),
                               query.value("email").toString(),
                               query.value("telefono").toString(),
                               query.value("domicilio").toString()));
    }
    return usuarios;
}


bool DatabaseManager::actualizarUsuario(const Usuario& usuario) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return false;
    }
    QSqlQuery query;
    query.prepare("UPDATE usuario SET nombre = :nombre, email = :email, telefono = :telefono, domicilio = :domicilio "
                  "WHERE dni = :dni");
    query.bindValue(":nombre", usuario.nombre());
    query.bindValue(":email", usuario.email());
    query.bindValue(":telefono", usuario.telefono());
    query.bindValue(":dni", usuario.dni());
    query.bindValue(":domicilio", usuario.domicilio());

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Error al actualizar usuario:" << m_lastError;
        return false;
    }

    return true;
}

bool DatabaseManager::eliminarUsuario(const QString& dni) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return false;
    }
    QSqlQuery query;
    query.prepare("DELETE FROM usuario WHERE dni = :dni");
    query.bindValue(":dni", dni);
    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Error al eliminar usuario:" << m_lastError;
        return false;
    }

    return true;
}



//inicia prestamo
//-----------------------------------------------------------------------------------------------------------
bool DatabaseManager::libroExiste(const QString& isbn) {
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM libro WHERE isbn = :isbn");
    query.bindValue(":isbn", isbn);

    return query.exec() && query.next() && query.value(0).toInt() > 0;
}

bool DatabaseManager::usuarioExiste(const QString& dni) {
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM usuario WHERE dni = :dni");
    query.bindValue(":dni", dni);

    return query.exec() && query.next() && query.value(0).toInt() > 0;
}

bool DatabaseManager::libroDisponible(const QString& isbn) {
    if (!m_db.isOpen()) return false;

    QSqlQuery query;
    query.prepare("SELECT disponible FROM libro WHERE isbn = :isbn");
    query.bindValue(":isbn", isbn);

    if (query.exec() && query.next()) {
        return query.value("disponible").toBool();
    }
    return false;
}

bool DatabaseManager::realizarPrestamo(const QString& isbnLibro, const QString& dniUsuario,
                                       const QDate& fechaPrestamo, const QDate& fechaDevolucion) {
    // 1. Verificar conexión a la base de datos
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return false;
    }

    // 2. Validaciones básicas de parámetros
    if (isbnLibro.isEmpty() || dniUsuario.isEmpty()) {
        qDebug() << "Error: ISBN o DNI de usuario vacío";
        return false;
    }

    if (fechaDevolucion < fechaPrestamo) {
        qDebug() << "Error: Fecha de devolución anterior a fecha de préstamo";
        return false;
    }

    // 3. Verificar existencia del libro y usuario
    if (!libroExiste(isbnLibro)) {
        qDebug() << "Error: El libro con ISBN" << isbnLibro << "no existe";
        return false;
    }

    if (!usuarioExiste(dniUsuario)) {
        qDebug() << "Error: El usuario con DNI" << dniUsuario << "no existe";
        return false;
    }

    // 4. Verificar disponibilidad del libro
    if (!libroDisponible(isbnLibro)) {
        qDebug() << "Error: El libro con ISBN" << isbnLibro << "no está disponible";
        return false;
    }

    // 5. Iniciar transacción
    m_db.transaction();

    // 6. Preparar y ejecutar consulta
    QSqlQuery query;
    query.prepare("INSERT INTO prestamo (isbn_libro, dni_usuario, fecha_prestamo, fecha_devolucion) "
                  "VALUES (:isbn_libro, :dni_usuario, :fecha_prestamo, :fecha_devolucion)");
    query.bindValue(":isbn_libro", isbnLibro);
    query.bindValue(":dni_usuario", dniUsuario);
    query.bindValue(":fecha_prestamo", fechaPrestamo.toString("yyyy-MM-dd"));
    query.bindValue(":fecha_devolucion", fechaDevolucion.toString("yyyy-MM-dd"));

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Error al realizar prestamo:" << m_lastError;
        return false;
    }


    // 7. Actualizar estado del libro (marcar como no disponible)
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE libro SET disponible = 0 WHERE isbn = :isbn");
    updateQuery.bindValue(":isbn", isbnLibro);

    if (!updateQuery.exec()) {
        qDebug() << "Error al actualizar estado del libro:" << updateQuery.lastError().text();
        m_db.rollback();
        return false;
    }

    // 8. Confirmar transacción
    m_db.commit();
    qDebug() << "Préstamo registrado correctamente";
    return true;
}





Prestamo DatabaseManager::obtenerPrestamo(int idPrestamo) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return Prestamo();
    }
    QSqlQuery query;
    query.prepare("SELECT * FROM prestamo WHERE id = :id");
    query.bindValue(":id", idPrestamo);

    if (query.exec() && query.next()) {
        return Prestamo(query.value("id").toInt(),
                        query.value("isbn_libro").toString(),
                        query.value("dni_usuario").toString(),
                        QDate::fromString(query.value("fecha_prestamo").toString(), "yyyy-MM-dd"),
                        QDate::fromString(query.value("fecha_devolucion").toString(), "yyyy-MM-dd"));
    }
    return Prestamo();
}

QList<Prestamo> DatabaseManager::obtenerTodosPrestamos() {
    QList<Prestamo> prestamos;
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return prestamos;
    }

    QSqlQuery query("SELECT * FROM prestamo");

    while (query.next()) {
        prestamos.append(Prestamo(
            query.value("id").toInt(),                  // ID del préstamo
            query.value("isbn_libro").toString(),       // ISBN del libro
            query.value("dni_usuario").toString(),      // DNI del usuario
            QDate::fromString(query.value("fecha_prestamo").toString(), "yyyy-MM-dd"),  // Fecha de préstamo
            QDate::fromString(query.value("fecha_devolucion").toString(), "yyyy-MM-dd") // Fecha de devolución
            ));
    }
    return prestamos;
}

QList<Prestamo> DatabaseManager::obtenerPrestamosPorLibro(const QString& isbnLibro) {
    QList<Prestamo> prestamos;
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return prestamos;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM prestamo WHERE isbn_libro = :isbn_libro");
    query.bindValue(":isbn_libro", isbnLibro);

    while (query.exec() && query.next()) {
        prestamos.append(Prestamo(query.value("id").toInt(),
                               query.value("isbn_libro").toString(),
                               query.value("dni_usuario").toString(),
                               QDate::fromString(query.value("fecha_prestamo").toString(), "yyyy-MM-dd"),
                               QDate::fromString(query.value("fecha_devolucion").toString(), "yyyy-MM-dd")));
    }
    return prestamos;
}

bool DatabaseManager::actualizarPrestamo(const Prestamo& prestamo) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return false;
    }
    QSqlQuery query;
    query.prepare("UPDATE prestamo SET isbn_libro = :isbn_libro, dni_usuario = :dni_usuario, "
                  "fecha_prestamo = :fecha_prestamo, fecha_devolucion = :fecha_devolucion "
                  "WHERE id = :id");
    query.bindValue(":isbn_libro", prestamo.isbnLibro());
    query.bindValue(":dni_usuario", prestamo.dniUsuario());
    query.bindValue(":fecha_prestamo", prestamo.fechaPrestamo().toString("yyyy-MM-dd"));
    query.bindValue(":fecha_devolucion", prestamo.fechaDevolucion().toString("yyyy-MM-dd"));
    query.bindValue(":id", prestamo.id());

    if (!query.exec()) {
        qDebug() << "Error al actualizar préstamo:" << query.lastError().text();
        return false;
    }
    return true;
}

bool DatabaseManager::finalizarPrestamo(int idPrestamo, const QDate& fechaDevolucion) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return false;
    }
    QSqlQuery query;
    query.prepare("UPDATE prestamo SET fecha_devolucion = :fecha_devolucion WHERE id = :id");
    query.bindValue(":fecha_devolucion", fechaDevolucion.toString("yyyy-MM-dd"));
    query.bindValue(":id", idPrestamo);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Error al finalizar prestamo:" << m_lastError;
        return false;
    }

        // Actualizar disponibilidad del libro
        QString isbn = obtenerPrestamo(idPrestamo).isbnLibro();
        if (!isbn.isEmpty()) {
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE libro SET disponible = 1 WHERE isbn = :isbn");
            updateQuery.bindValue(":isbn", isbn);
            return updateQuery.exec();
        }
    
    return true;
}

bool DatabaseManager::eliminarPrestamo(int idPrestamo) {
    if (!m_db.isOpen()) {
        qDebug() << "Error: Base de datos no abierta";
        return false;
    }
    QSqlQuery query;
    query.prepare("DELETE FROM prestamo WHERE id = :id");
    query.bindValue(":id", idPrestamo);

    if (!query.exec()) {
        m_lastError = query.lastError().text();
        qDebug() << "Error al eliminar prestamo:" << m_lastError;
        return false;
    }

    return true;
}
