#ifndef PRESTAMO_H
#define PRESTAMO_H

#include <QObject>
#include <QString>
#include <QDate>

class Prestamo
{
public:
    Prestamo();
    // Constructor con parámetros
    Prestamo(int id, const QString& isbnLibro, const QString& dniUsuario,
             const QDate& fechaPrestamo, const QDate& fechaDevolucion);

    // Getters y setters
    int id() const;
    void setId(int id);

    QString isbnLibro() const;
    void setIsbnLibro(const QString &isbnLibro);

    QString dniUsuario() const;
    void setDniUsuario(const QString &dniUsuario);

    QDate fechaPrestamo() const;
    void setFechaPrestamo(const QDate &fechaPrestamo);

    QDate fechaDevolucion() const;
    void setFechaDevolucion(const QDate &fechaDevolucion);

    // Métodos adicionales (opcionales)
    bool estaVencido() const;
    bool estaDevuelto() const;
    int diasRestantes() const;

private:
    int m_id;               // ID del préstamo
    QString m_isbnLibro;    // ISBN del libro prestado
    QString m_dniUsuario;   // DNI del usuario que realizó el préstamo
    QDate m_fechaPrestamo;  // Fecha de préstamo
    QDate m_fechaDevolucion; // Fecha de devolución
};

#endif // PRESTAMO_H