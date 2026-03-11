#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QList>
#include <QString>
#include <QDate>
#include "libro.h"
#include "usuario.h"
#include "prestamo.h"

class DatabaseManager {
public:
    // Singleton
    static DatabaseManager& getInstance();
    
    // Eliminar copias
    DatabaseManager(const DatabaseManager&) = delete;
    DatabaseManager& operator=(const DatabaseManager&) = delete;

    ~DatabaseManager();

    bool openDatabase(const QString& dbPath = "biblioteca.db");
    void closeDatabase();
    bool isOpen() const;
    QString getLastError() const;

    bool createTables();

    // Operaciones para libros
    bool agregarLibro(const Libro& libro);
    Libro obtenerLibro(const QString& isbn);
    QList<Libro> obtenerTodosLibros();
    bool actualizarLibro(const Libro& libro);
    bool eliminarLibro(const QString& isbn);
    QList<Libro> buscarLibros(const QString& titulo, const QString& autor,
                              const QString& editorial, const QString& palabrasClave);

    

    // Operaciones para usuarios
    bool agregarUsuario(const Usuario& usuario);
    Usuario obtenerUsuario(const QString& dni);
    QList<Usuario> obtenerTodosUsuarios();
    QList<Usuario> exportarUsuarios();
    bool actualizarUsuario(const Usuario& usuario);
    bool eliminarUsuario(const QString& dni);


    // Operaciones para préstamos
    bool realizarPrestamo(const QString& isbnLibro, const QString& dniUsuario, 
                         const QDate& fechaPrestamo, const QDate& fechaDevolucion);
    Prestamo obtenerPrestamo(int idPrestamo);
    QList<Prestamo> obtenerTodosPrestamos();
    QList<Prestamo> obtenerPrestamosPorUsuario(const QString& dniUsuario);
    QList<Prestamo> obtenerPrestamosPorLibro(const QString& isbnLibro);
    bool actualizarPrestamo(const Prestamo& prestamo);
    bool finalizarPrestamo(int idPrestamo, const QDate& fechaDevolucion);
    bool eliminarPrestamo(int idPrestamo);

    // Funciones auxiliares
    bool libroExiste(const QString& isbn);
    bool usuarioExiste(const QString& dni);
    bool libroDisponible(const QString& isbn);

private:
    DatabaseManager();  // Constructor privado
    QSqlDatabase m_db;
    QString m_lastError;
};

#endif // DATABASEMANAGER_H
