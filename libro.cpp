#include "libro.h"

// Constructor por defecto
Libro::Libro() : m_anio(0) {}

// Constructor con parámetros
Libro::Libro(const QString& isbn, const QString& titulo, const QString& autor,
             const QString& editorial, int anio, const QString& pais, bool disponible)
    : m_isbn(isbn), m_titulo(titulo), m_autor(autor),
    m_editorial(editorial), m_anio(anio), m_pais(pais), m_disponible(disponible) {}


// Getters
QString Libro::isbn() const { return m_isbn; }
QString Libro::titulo() const { return m_titulo; }
QString Libro::autor() const { return m_autor; }
QString Libro::editorial() const { return m_editorial; }
int Libro::anio() const { return m_anio; }
QString Libro::pais() const { return m_pais; }
bool Libro::disponible() const { return m_disponible; }


// Setters
void Libro::setIsbn(const QString &isbn) { m_isbn = isbn; }
void Libro::setTitulo(const QString &titulo) { m_titulo = titulo; }
void Libro::setAutor(const QString &autor) { m_autor = autor; }
void Libro::setEditorial(const QString &editorial) { m_editorial = editorial; }
void Libro::setAnio(int anio){m_anio=anio;}
void Libro::setPais(const QString &pais) { m_pais = pais; }
void Libro::setDisponible(bool disponible) { m_disponible = disponible; }



