#include "usuario.h"


// Constructor con parámetros
Usuario::Usuario(const QString& dni, const QString& nombre, const QString& email,
                 const QString& telefono, const QString& domicilio)
    :m_dni(dni), m_nombre(nombre), m_email(email), m_telefono(telefono), m_domicilio(domicilio) {}

// Getter para el DNI
QString Usuario::dni() const {
    return m_dni;
}

// Setter para el DNI
void Usuario::setDni(const QString &dni) {
    m_dni = dni;
}

// Getter para el nombre
QString Usuario::nombre() const {
    return m_nombre;
}

// Setter para el nombre
void Usuario::setNombre(const QString &nombre) {
    m_nombre = nombre;
}

// Getter para el email
QString Usuario::email() const {
    return m_email;
}

// Setter para el email
void Usuario::setEmail(const QString &email) {
    m_email = email;
}

// Getter para el teléfono
QString Usuario::telefono() const {
    return m_telefono;
}

// Setter para el teléfono
void Usuario::setTelefono(const QString &telefono) {
    m_telefono = telefono;
}

//Getter para domicilio
QString Usuario::domicilio() const{
    return m_domicilio;
}

//Setter para domicilio
void Usuario::setDomicilio(const QString &domicilio){
    m_domicilio = domicilio;
}
