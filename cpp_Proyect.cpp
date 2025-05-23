#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <ctime>
using namespace std;

struct Reserva {
    int numeroHabitacion;
    int numReserva;
    string nombre;
    string fechaEntrada;
    string fechaSalida;
    string telefono;
};

const int maxHabitaciones = 100;

std::vector<Reserva> reservas;

// Miguel Monsalve
// Funcion para generar un numero de reserva aleatorio
int bookingNumGenerator(){
    srand(time(0));
    int numReserva = rand() % 1000 + 5000;
    for(int i = 0; i < reservas.size(); i++) {
        if(numReserva == reservas[i].numReserva) {
            numReserva = rand() % 1000 + 5000;
        }
    }
    return numReserva;
}

// Jean Padilla
// Funcion para verificar la disponibilidad de habitaciones
int roomsdisponibility(vector<Reserva>& reservas){
    int habitacionesdisponibless = 0;
    for(int i = 0; i < reservas.size(); i++) {
        if(reservas[i].numeroHabitacion == 0){
            return habitacionesdisponibless++;
        }
    }
}

// Miguel Monsalve
// Funcion para buscar reservas por numero de reserva o nombre
int search(vector<Reserva>& reservas){
    int opcion;
    string nombre;
    int numReserva;
    cout << R"(Como desea buscar la reserva?
    1 - Numero de reserva
    2 - Nombre de la reserva
    )" << endl;

    cin>>opcion;
    cin.ignore();

    if(opcion == 1){
        cout << "Ingrese el numero de reserva: ";
        cin >> numReserva;

        for(int i = 0; i < reservas.size(); i++) {
            if (reservas[i].numReserva == numReserva) {
                cout << "Reserva encontrada: " << reservas[i].numReserva << endl;
                return i;
            }
        }

    } else if(opcion == 2){
        cout << "Ingrese el nombre de la reserva: ";
        cin.ignore();
        getline(cin, nombre);

        for(int i = 0; i < reservas.size(); i++){
            if (reservas[i].nombre == nombre){
                cout << "Reserva encontrada: " << reservas[i].nombre << endl;
                return i;
            }
        }
    } else{
        cout << "Input invalido" << endl;
        return -1;
    }

    cout << "Reserva no encontrada" << endl;
    return -1;
}

// Miguel Monsalve
// Funcion para mostrar las reservas
void showbooking(vector<Reserva>& reservas){
    if(reservas.empty()){
        cout << "No hay reservas realizadas.\n";
    } else
        cout << " \n Las reservas actuales son: " << endl;
    cout << "_____________________________________________________________________________" << endl;
    cout << std::setw(20) << std::left << "Nombre"
         << std::setw(20) << std::left << "Fecha de entrada"
         << std::setw(20) << std::left << "Fecha de salida"
         << std::setw(20) << std::left << "Numero de reserva"
         << std::setw(20) << std::left << "numero de habitacion"
         << std::setw(20) << std::left << "Telefono"
         << std::endl;
    for(int i = 0; i < reservas.size(); i++) {
        cout << std::setw(20) << std::left << reservas[i].nombre
             << std::setw(20) << std::left << reservas[i].fechaEntrada
             << std::setw(20) << std::left << reservas[i].fechaSalida
             << std::setw(20) << std::left << reservas[i].numReserva
             << std::setw(20) << std::left << reservas[i].numeroHabitacion
             << std::setw(20) << std::left << reservas[i].telefono
             << std::endl;
    }
    cout << "_____________________________________________________________________________" << endl;
}

// Jean Padilla
// Funcion para agregar reservas
void addbooking(vector<Reserva>& reservas){
    char respuesta;
    Reserva nueva;
    int numReserva;

    do {
        cout << "Ingrese su nombre completo: " <<endl;
        cin.ignore();
        getline(cin, nueva.nombre);
        cout << "Ingrese su numero de telefono: " <<endl;

        getline(cin, nueva.telefono);
        if (nueva.telefono.length() > 10) {
            cout << "El numero de telefono no es valido" <<endl;
            return;
        }
        cout << "Ingrese la fecha de entrada (MM/DD/YYYY): " <<endl;
        getline(cin, nueva.fechaEntrada);

        cout << "Ingrese la fecha de salida (MM/DD/YYYY): " <<endl;
        getline(cin, nueva.fechaSalida);

        if (nueva.fechaEntrada > nueva.fechaSalida) {
            cout << "La fecha de entrada no puede ser mayor a la fecha de salida." <<endl;
            return;
        }
        cout << "Ingrese el numero de habitacion: " <<endl;
        cin >> nueva.numeroHabitacion;
        cin.ignore();
        if(nueva.numeroHabitacion < 1 || nueva.numeroHabitacion > maxHabitaciones){
            cout << "El numero de habitacion no es valido." << endl;
            return;
        }
        for(int i = 0; i < reservas.size(); i++){
            if (nueva.numeroHabitacion == reservas[i].numeroHabitacion){
                cout << "La habitacion ya esta reservada." <<endl;
                return;
            }
        }

        numReserva = bookingNumGenerator();
        nueva.numReserva = numReserva;

        reservas.push_back(nueva);
        cout << "Reserva agregada exitosamente." <<endl;

        cout << "Desea agregar otra reserva? (S/N): " <<endl;
        cin >> respuesta;
        respuesta = toupper(respuesta);
        if(respuesta != 'S' && respuesta != 'N'){
            cout << "Input invalido" << endl;
        }

    } while(respuesta != 'N');
}

// Miguel Monsalve
// Funcion para eliminar reservas
void deletebooking(vector<Reserva>& reservas){
    bool found = false;
    string nombreReserva;
    cout << "Ingrese el nombre de la reserva que desea eliminar: ";
    cin.ignore();
    getline(cin,nombreReserva);

    int i;
    for(i = 0; i < reservas.size(); i++){
        if(reservas[i].nombre == nombreReserva){
            found = true;
            reservas.erase(reservas.begin() + i);
        }
    }
    if(!found){
        cout << "Reserva no encontrada" << endl;
        return;
    } else
        cout << "La reserva ha sido eliminada" << endl;
    cout << "Las reservas actuales son: " << endl;
    showbooking(reservas);
}

// Jean Padilla
// Funcion para modificar reservas
void modifybooking(vector<Reserva>& reservas){
    string nombreReserva;
    int opcion;
    int index = search(reservas);

    if (index == -1) {
        cout << "Reserva no encontrada." << endl;
        return;
    }

    cout << "Reserva encontrada: " << reservas[index].nombre << endl;
    cout << R"(Que desea modificar de la reserva?
    1 - Nombre
    2 - Fecha de entrada y salida
    3 - Telefono
    4 - Numero de habitacion)" << endl;
    cin >> opcion;
    cin.ignore();
    switch (opcion){
        case 1:{
            cout << "Ingrese el nuevo nombre: ";
            getline(cin, reservas[index].nombre);
            cout << "Nombre modificado exitosamente." << endl;
            break;
        }
        case 2:{
            cout << "Ingrese la nueva fecha de entrada: ";
            cin >> reservas[index].fechaEntrada;
            cout << "Ingrese la nueva fecha de salida: ";
            cin >> reservas[index].fechaSalida;
            cout << "Las fechas de la reserva fueron modificadas." << endl;
            break;
        }
        case 3:{
            cout << "Ingrese el nuevo telefono: ";
            cin >> reservas[index].telefono;
            cout << "El numero de telefono fue modificado." << endl;
            break;
        }
        case 4:{
            cout << "Ingrese el nuevo numero de habitacion: ";
            cin >> reservas[index].numeroHabitacion;
            cout << "La habitacion fue modificada." << endl;
            break;
        }
        default:
            cout << "Opcion no valida." << endl;
            break;
    }
}

// Miguel Monsalve
// Funcion para guardar reservas en un archivo
void savetofile(vector<Reserva>& reservas){
    ofstream file("Reporte_reservas.txt");
    for (int i = 0; i < reservas.size(); i++){
        file << "Nombre: " << reservas[i].nombre <<"\n"
             << "Fecha de entrada: " << reservas[i].fechaEntrada
             << "Fecha de salida: " << reservas[i].fechaSalida <<"\n"
             << "Telefono: " << reservas[i].telefono << "\n"
             << "Numero de habitacion: " << reservas[i].numeroHabitacion <<"\n"
             << "Numero de reserva: " << reservas[i].numReserva <<"\n"
             << endl;
        file << "_____________________________________________________________________________" <<endl;
    }
    file << "Total de reservas: " << reservas.size() <<endl;

    cout << "Reservas guardadas exitosamente en el archivo Reporte_reservas.txt." <<endl;
    file.close();
    if (file.is_open()) {
        cout << "Error al guardar el archivo" <<endl;
    }
}

// Jean Padilla
int main() {
    int menuOpt;

    do {
        cout << R"(
     _______________________________________________________________
     Bienvenido al sistema de reservas de hotel
     _______________________________________________________________
     Elija una opcion o presione 0 para salir del programa
     1 - Agregar reserva
     2 - Eliminar reserva
     3 - Modificar reserva
     4 - Mostrar reservas
     5 - Guardar reservas en archivo
     0 - Salir del programa
     _______________________________________________________________
     )";
        cout << "Ingrese la opcion deseada: ";
        cin >> menuOpt;
        if(menuOpt < 0 || menuOpt > 5){
            cout << "Input no valido" <<endl;
        }
        switch (menuOpt){
            case 1:
                addbooking(reservas);
                break;
            case 2:
                deletebooking(reservas);
                break;
            case 3:
                modifybooking(reservas);
                break;
            case 4:
                showbooking(reservas);
                break;
            case 5:
                savetofile(reservas);
                break;
        }
    } while(menuOpt != 0);
    return 0;
}
