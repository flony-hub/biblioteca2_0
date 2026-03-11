#include "prestamo.h"

// Constructor por defecto
Prestamo::Prestamo() :
    m_id(-1),
    m_isbnLibro(""),
    m_dniUsuario(""),
    m_fechaPrestamo(QDate()),
    m_fechaDevolucion(QDate())
{
}

// Constructor con parámetros
Prestamo::Prestamo(int id, const QString& isbnLibro, const QString& dniUsuario,
                   const QDate& fechaPrestamo, const QDate& fechaDevolucion) :
    m_id(id),
    m_isbnLibro(isbnLibro),
    m_dniUsuario(dniUsuario),
    m_fechaPrestamo(fechaPrestamo),
    m_fechaDevolucion(fechaDevolucion)
{
}

// Implementación de getters
int Prestamo::id() const { return m_id; }
QString Prestamo::isbnLibro() const { return m_isbnLibro; }
QString Prestamo::dniUsuario() const { return m_dniUsuario; }
QDate Prestamo::fechaPrestamo() const { return m_fechaPrestamo; }
QDate Prestamo::fechaDevolucion() const { return m_fechaDevolucion; }

// Implementación de setters
void Prestamo::setId(int id) { m_id = id; }
void Prestamo::setIsbnLibro(const QString &isbnLibro) { m_isbnLibro = isbnLibro; }
void Prestamo::setDniUsuario(const QString &dniUsuario) { m_dniUsuario = dniUsuario; }
void Prestamo::setFechaPrestamo(const QDate &fechaPrestamo) { m_fechaPrestamo = fechaPrestamo; }
void Prestamo::setFechaDevolucion(const QDate &fechaDevolucion) { m_fechaDevolucion = fechaDevolucion; }

// Implementación de métodos adicionales
bool Prestamo::estaVencido() const
{
    return !estaDevuelto() && QDate::currentDate() > m_fechaDevolucion;
}

bool Prestamo::estaDevuelto() const
{
    return m_fechaDevolucion.isValid();
}

int Prestamo::diasRestantes() const
{
    if (estaDevuelto()) return 0;
    return QDate::currentDate().daysTo(m_fechaDevolucion);
}