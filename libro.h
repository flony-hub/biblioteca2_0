#ifndef LIBRO_H
#define LIBRO_H

#include <QString>

class Libro {
public:
    Libro(); // Constructor por defecto
    Libro(const QString& isbn, const QString& titulo, const QString& autor,
          const QString& editorial, int anio, const QString& pais, bool disponible);

    // Getters
    QString isbn() const;
    QString titulo() const;
    QString autor() const ;
    QString editorial() const;
    int anio() const ;
    QString pais() const ;
    bool disponible() const;

    // Setters
    void setIsbn(const QString& isbn) ;
    void setTitulo(const QString& titulo);
    void setAutor(const QString& autor);
    void setEditorial(const QString& editorial);
    void setAnio(int anio);
    void setPais(const QString& pais);
    void setDisponible(bool disponible);

private:
    QString m_isbn;
    QString m_titulo;
    QString m_autor;
    QString m_editorial;
    int m_anio;
    QString m_pais;
    bool m_disponible; // NUEVO
};

#endif // LIBRO_H
