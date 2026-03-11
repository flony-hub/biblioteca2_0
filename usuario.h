#ifndef USUARIO_H
#define USUARIO_H

#include <QObject>
#include <QString>

class Usuario
{
public:
    Usuario() : m_dni(""), m_nombre(""), m_email(""), m_telefono(""), m_domicilio("") {}
    // Constructor con parámetros
    Usuario(const QString& dni, const QString& nombre, const QString& email,
            const QString& telefono, const QString& domicilio);

    // Getters y setters
    QString dni() const;
    void setDni(const QString &dni);

    QString nombre() const;
    void setNombre(const QString &nombre);

    QString email() const;
    void setEmail(const QString &email);

    QString telefono() const;
    void setTelefono(const QString &telefono);

    QString domicilio() const;
    void setDomicilio(const QString &domicilio);

private:
    QString m_dni;      // DNI del usuario
    QString m_nombre;   // Nombre del usuario
    QString m_email;    // Email del usuario
    QString m_telefono; // Teléfono del usuario
    QString m_domicilio; //Domicilio del usuario
};

#endif // USUARIO_H
