#include <iostream>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <string>
#include <cstdlib>
#include <vector>
#include <cstdlib>
#include <ctime>
#define ENTER 13
#define BACKSPACE 8
#define INTENTOS 3
using namespace std;
struct cuenta{
	string nombre;
	string contrasena;
	double monto;//Salario o monto
	string tipocuenta;//Vendedor Cliente
};
struct Producto{
	int id,cantidad;
	string nombre_producto;
	double precio;
	int accion;//1agregar//2 añadir stock
};
struct Proveedor{
	string nombre_proveedor;
	int telefono_proveedor;	
};
struct Historial{
	int id;//1 agregar //2 añadir stock 
};
struct Fecha{
    time_t t = time(0);   // get time now
    tm* now = localtime(&t);
    int dia=now->tm_mday;
    int mes=now->tm_mon+1;
    int anio=now->tm_year+1900;
};
		ofstream es_cuenta;
		ifstream lec_cuenta;
		ofstream es_prove;
		ofstream Esc;//Producto
		ifstream Lec;//Producto
		ifstream Lec_historial;//historial
		ofstream es_historial;//historial
		string nombcli;
		string nombven;
		int cont=100;
		int contador=1000;
		string auxxx;
int MenuLogin();
void Ver_Registro_Clientes();
void verificarEliminar();
void GenerarRegistro(ofstream &,string);
string CifradoContrasena();
bool ValidacionNombresRepetidos(string);
bool Vereficar_IdProducto(int,string);
void VisualizarRegistro(ifstream &);
void Modificar_Producto(ifstream &);
int loginClientes(string ,string );
int IntentosLogin(bool,int);
void Login();
void Archivar_Producto(ofstream &);
void Eleminar_Producto(ifstream &);
void Ver_Registro_Producto(ifstream &);
void saldo();
void Ver_Registro_Proveedor(ifstream &);
void Comprar_Producto_Cliente();
void ver_historial_cliente();
void ver_historial_producto();
void ver_historial_proveedor();
void Archivar_Provee(ofstream &es, string nombpro, int telef);
bool Vereficar_Provee(string nombre);
void mostrarProveedor(ifstream &);
int NoEliminar(int);
int MenuCliente();
int MenuVendedor();

int main(){//Terminado
	system("COLOR 1F");
	system("mode con: cols=150 lines=60");
	string nombven;
	string nombcli;
	ofstream es;
	ifstream lec;
	int opc;
	do{
		system("cls");
		opc=MenuLogin();
		switch(opc){
			case 1:{	
				Login();
				break;
			}
			case 2:{
				GenerarRegistro(es_cuenta,"Cliente");
				break;
			}
			case 3:{
				GenerarRegistro(es_cuenta,"Vendedor");
				break;
			}
		} cout<<endl;
		 system("pause");
	}while(opc!=4);
	return 1;
}
int MenuLogin(){
	system("cls");
	int opc;
	cout<<"\n\t\t\t\t\t\t[Menu Login]\n";
	cout<<"\n\t\t\t\t\t[1]Loguearse\n";
	cout<<"\n\t\t\t\t\t[2]Registrar Cliente\n";
	cout<<"\n\t\t\t\t\t[3]Registrar Vendedor\n";
	cout<<"\n\t\t\t\t\t[4]Salir\n";
	cout<<"\n\t\t\t\tIngrese opcion:";
	cin>>opc;
	return opc;
}

int loginClientes(string usuario,string contrasena){
	cuenta c;
	ifstream leer("Registro_Clientes.txt",ios::out|ios::app);
	if(leer.is_open()){
		leer>>c.nombre;
		while(!leer.eof()){
		leer>>c.contrasena;
		leer>>c.monto;
		leer>>c.tipocuenta;
			if(usuario==c.nombre && contrasena==c.contrasena &&c.tipocuenta =="Cliente"){
			leer.close();
			return 1;
			}else if(usuario==c.nombre && contrasena==c.contrasena &&c.tipocuenta =="Vendedor"){
			leer.close();
			return 2;
			}
	 		leer>>c.nombre;
    	}	
	}else{
	  cout<<"\t\t\t Error al abrir el archivo"<<endl;	
	}
	return 3;
}

void Login(){
	int contador=0; bool ingresa=false;
	system("cls");
	setlocale(LC_ALL,"spanish");
	cuenta c;
	cout<<"\n\t\t\t\t\t\t[Login]\n";
	cout<<"\n\t\t\t\t\tIngrese Usuario:";
	cin>>c.nombre;
	cout<<"\n\t\t\t\t\tIngrese Contraseña:";
	c.contrasena=CifradoContrasena();
	if(loginClientes(c.nombre,c.contrasena)==1){
		nombcli=c.nombre;
		cout<<"Logueo Exitoso"<<endl;
	MenuCliente();	
	}else if(loginClientes(c.nombre,c.contrasena)==2){
    	nombven=c.nombre;
    	cout<<"Logueo Exitoso"<<endl;
	MenuVendedor();	
	}else{
		cout<<"\nLa cuenta no existe\n";
	}	
	system("pause");
}
bool ValidacionNombresRepetidos(string repetido){
	ifstream leer("Registro_Clientes.txt",ios::out|ios::app);
	cuenta c;
	leer>>c.nombre;
	while(!leer.eof()){
		leer>>c.contrasena;
		leer>>c.monto;
		leer>>c.tipocuenta;
		if(c.nombre==repetido){
			leer.close();
			return false;
		}
		leer>>c.nombre;//Para que el archivos continue
	}
	leer.close();
	return true;
}
void GenerarRegistro(ofstream &es,string tipo){	
	system("cls");
	setlocale(LC_ALL,"spanish");
	cuenta c;
	es.open("Registro_Clientes.txt",ios::out | ios::app);
	cout<<"\n\t\t\t\t\t\t[Registrando Usuarios]"<<endl;
	cout<<"\n\t\t\t\t\tIngrese su nuevo Usuario:";
	cin>>c.nombre;
	cout<<"\n\t\t\t\t\tIngrese su nuevo Constraseña:";
	c.contrasena=CifradoContrasena();
        c.monto=2500+rand()%(4001-2500);
        c.tipocuenta=tipo;
        if(ValidacionNombresRepetidos(c.nombre)){
        	es<<c.nombre<<" "<<c.contrasena<<" "<<c.monto<<" "<<c.tipocuenta<<"\n";
        	cout<<endl<<"\n\t\t\t\t\tRegistrado Correctamente\n";
	}else{
		cout<<"\n\t\t\t\t\tEl nombre que desea registrar, ya existe\n";
	}
	system("pause");
        es.close();
}
string CifradoContrasena(){
	string passwords;
	char caracter;
	caracter = getch();
	passwords =""; // para poner cadena vacia
	while(caracter!= ENTER){ 
		if(caracter!= BACKSPACE ){ // espacio
		passwords.push_back(caracter);
		cout<<"*"; 
		}else{
			if(passwords.length()>0){
		cout<< "\b \b";  //borrar caracter
		passwords = passwords.substr(0,passwords.length() -1);
			}
		}
		caracter = getch();
        	}
        return passwords;
        
}
int MenuCliente(){
	setlocale(LC_ALL,"spanish");
	char opc;
	do{
			system("cls");
			saldo();
			cout<<"\n\t\t\t\t\t\t[Menu Cliente]\n";
			cout<<"\n\t\t\t\t\t[1]Comprar Producto\n";
			cout<<"\n\t\t\t\t\t[2]Salir\n";
			cout<<"\n\t\t\t\tIngrese opcion:";
			opc = getche();// nos permite leer un caracter del teclado
		switch(opc){
			case '1':{
				Ver_Registro_Producto(Lec);
				Comprar_Producto_Cliente();
				break;
			}
			case '2':{
//				Ver_Movimiento_cuenta();
				break;
			}
		}cout<<endl;
		_getch();
	} while(opc!='2');    
}
//void Ver_Movimiento_cuenta(){
	
//}
void saldo(){
	lec_cuenta.open("Registro_Clientes.txt",ios::in);
	cuenta c;
	lec_cuenta>>c.nombre;
	while(!lec_cuenta.eof()){
		lec_cuenta>>c.contrasena;
		lec_cuenta>>c.monto;
		lec_cuenta>>c.tipocuenta;
		if(c.nombre==nombcli){
			cout<<"\nUsuario:"<<c.nombre;
			cout<<"\nSaldo Actual:"<<c.monto;	
		}
		lec_cuenta>>c.nombre;
	}
	lec_cuenta.close();
}
void Ver_Registro_Producto(ifstream &){
	Lec.open("Productos.txt", ios::in);
	Producto p;
	Proveedor pro;
	if(Lec.is_open()){
		Lec>>pro.nombre_proveedor;
		cout<<endl<<"\t\t******Inventario de productos****"<<endl;
		cout<<"\t\tProveedor\t\tTelefono\t\tID\t\tNOMBRE\t\tCANTIDAD\tPRECIO(U)\n";
		while(!Lec.eof()){
			Lec>>pro.telefono_proveedor;
			Lec>>p.id;
			Lec>>p.nombre_producto;
			Lec>>p.cantidad;
			Lec>>p.precio;
			cout<<"\t\t"<<pro.nombre_proveedor;
			cout<<"\t\t\t"<<pro.telefono_proveedor;
			cout<<"\t\t"<<p.id;
			cout<<"\t\t"<<p.nombre_producto;
			cout<<"\t\t"<<p.cantidad;
			cout<<"\t\t"<<p.precio<<endl;
			Lec>>pro.nombre_proveedor;
		}
		Lec.close();
	} else{
		cout<<"Error al abrir el archivo"<<endl;
	}
}
void Ver_Registro_Proveedor(ifstream &){
	Lec.open("Productos.txt", ios::in);
    Producto p;
    Proveedor pro;
    if(Lec.is_open()){
        Lec>>pro.nombre_proveedor;
        while(!Lec.eof()){
            Lec>>pro.telefono_proveedor;
            Lec>>p.id;
            Lec>>p.nombre_producto;
            Lec>>p.cantidad;
            Lec>>p.precio;
            Archivar_Provee(es_cuenta,pro.nombre_proveedor,pro.telefono_proveedor);
            Lec>>pro.nombre_proveedor;
        }
        Lec.close();
    } else{
        cout<<"Error al abrir el archivo"<<endl;
    }

}

void Comprar_Producto_Cliente(){
    cuenta c;
    Producto p;
    Proveedor pro;
    Fecha f;
    int id;
    int cant;
    double precioaux;
    time_t now = time(0);
    tm * time = localtime(&now);
    es_historial.open("HistorialCliente.txt",ios::out|ios::app);
    Esc.open("HistorialProducto.txt",ios::out|ios::app);
    Lec.open("Productos.txt",ios::in);
    lec_cuenta.open("Registro_Clientes.txt",ios::in);
    ofstream aux_producto("AuxiliarProducto.txt",ios::out|ios::app);
    ofstream aux_cuenta("AuxiliarCliente.txt",ios::out|ios::app);
    p.accion=4;
    cout<<"Ingrese el ID del producto que desea comprar:";
    cin>>id;
    //if(cant<=p.cantidad)
    Lec>>pro.nombre_proveedor;
    lec_cuenta>>c.nombre;
    while(!Lec.eof()){
    	Lec>>pro.telefono_proveedor;
    	Lec>>p.id;
        Lec>>p.nombre_producto;
        Lec>>p.cantidad;
        Lec>>p.precio;
        if(id==p.id){
        do{
            cout<<"Ingrese la cantidad que desea comprar:";
    	    cin>>cant;
    	    if(cant>p.cantidad){
    	    	cout<<"\n\n\tLa cantidad que desea comprar excede el stock\n\n"<<endl;
			}else{
				cout<<"\n\n\tCompra exitosa\n\n"<<endl;
			}
    	    }while(cant>p.cantidad);
            aux_producto<<pro.nombre_proveedor<<" "<<pro.telefono_proveedor<<" "<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad-cant<<" "<<p.precio<<"\n";
            Esc<<p.id<<" "<<p.nombre_producto<<" "<<cant<<" "<<p.precio<<" "<<p.accion<<" "<<f.dia<<" "<<f.mes<<" "<<f.anio<<endl;
	    es_historial<<nombcli<<" "<<p.nombre_producto<<" "<<cant<<" "<<p.precio<<" "<<p.precio*cant<<" "<<f.dia<<" "<<f.mes<<" "<<f.anio<<endl;"\n";
            precioaux=p.precio;
        }else{
            aux_producto<<pro.nombre_proveedor<<" "<<pro.telefono_proveedor<<" "<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad<<" "<<p.precio<<"\n";
        }
        Lec>>pro.nombre_proveedor;
    } 
	Lec.close();
    while(!lec_cuenta.eof()){
        lec_cuenta>>c.contrasena;
        lec_cuenta>>c.monto;
        lec_cuenta>>c.tipocuenta;
        if(nombcli==c.nombre){
            aux_cuenta<<c.nombre<<" "<<c.contrasena<<" "<<c.monto-(cant*precioaux)<<" "<<c.tipocuenta<<"\n";
        }else{
            aux_cuenta<<c.nombre<<" "<<c.contrasena<<" "<<c.monto<<" "<<c.tipocuenta<<"\n";
        }
        lec_cuenta>>c.nombre;
    }
    lec_cuenta.close();
    aux_producto.close();
    aux_cuenta.close();
    es_historial.close();
    Esc.close();
    remove("Productos.txt");
    remove("Registro_Clientes.txt");
    rename("AuxiliarProducto.txt","Productos.txt");
    rename("AuxiliarCliente.txt","Registro_Clientes.txt");

}
int MenuVendedor(){//terminado
	int opc;
	do{
		system("cls");
		cout<<"\n\t\t\t\t\t\t[Menu Vendedor]\n";
		cout<<"\n\t\t\t\t\t[1]REGISTRO DE INGRESO DE PRODUCTO\n";
		cout<<"\n\t\t\t\t\t[2]REPOSICION DE PRODUCTO\n";
		cout<<"\n\t\t\t\t\t[3]ELIMINAR DE PRODUCTO\n";
		cout<<"\n\t\t\t\t\t[4]MOSTRAR LISTA DE PRODUCTO\n";
		cout<<"\n\t\t\t\t\t[5]MOSTRAR LISTA DE CLIENTES\n";
		cout<<"\n\t\t\t\t\t[6]MOSTRAR LISTA DE PROVEEDORES\n";
		cout<<"\n\t\t\t\t\t[7]VER MOVIMIENTOS DE PRODUCTOS\n";
		cout<<"\n\t\t\t\t\t[8]VER MOVIMIENTOS DE CLIENTES\n";
		cout<<"\n\t\t\t\t\t[9]VER MOVIMIENTOS DE PROVEEDORES\n";
		cout<<"\n\t\t\t\t\t[10]SALIR\n";
		cout<<"\n\t\t\t\tIngrese opcion:";
		cin>>opc;// nos permite leer un caracter del teclado
		switch(opc){
			case 1:{
				Archivar_Producto(Esc);//archivar producto vendedores
				break;
			}
			case 2:{
				Modificar_Producto(Lec);//modificar Producto vendedores
				break;
			}
			case 3:{
				Eleminar_Producto(Lec);//Eliminar Producto Vendedores
				break;
			}
			case 4:{
				Ver_Registro_Producto(Lec);//Ver Registro Producto
				break;
			}
			case 5:{
				Ver_Registro_Clientes();
				break;
			}
			case 6:{
				Ver_Registro_Proveedor(Lec);
				mostrarProveedor(Lec);
				break;
			}
			case 7:{
				ver_historial_producto();
				
				break;
			}
			case 8:{
				ver_historial_cliente();
			
				break;
			}
			case 9:{
				ver_historial_proveedor();
				break;
			}
		} cout<<endl;
		system("pause");
	} while(opc!=10);
}
int telefono(string nombre){
	ifstream leer("Productos.txt",ios::out|ios::app);
	Producto p;
	Proveedor pro;
	leer>>pro.nombre_proveedor;
	while(!leer.eof()){
		leer>>pro.telefono_proveedor;
		leer>>p.id;
		leer>>p.nombre_producto;
		leer>>p.cantidad;
		leer>>p.precio;
		if(nombre==pro.nombre_proveedor){
			return pro.telefono_proveedor;
		}
		leer>>pro.nombre_proveedor;//Para que el archivos continue
	}
	return 0;
}
void Archivar_Producto(ofstream &es){
	system("cls");
		time_t now = time(0);
    	tm * time = localtime(&now);
	setlocale(LC_ALL,"spanish");
	Producto p;
	Proveedor pro;
	Fecha f;
	es.open("Productos.txt",ios::out|ios::app);
	es_historial.open("HistorialProducto.txt",ios::out|ios::app);
	es_prove.open("HistorialProveedor.txt",ios::out|ios::app);
    	cout<<"\n\t\t\t\t\t\tAñadiendo Producto"<<endl;
    	cout<<"\n\t\t\t Ingrese nombre proveedor: "; cin>>pro.nombre_proveedor;
    	if(telefono(pro.nombre_proveedor)==0){
    		cout<<"\n\t\t\t Ingrese telefono proveedor: "; cin>>pro.telefono_proveedor;
	    }else{
	    	pro.telefono_proveedor=telefono(pro.nombre_proveedor);
    		cout<<"\n\t\t\t Telefono del proveedor : "<<pro.telefono_proveedor<<endl;
	    }
	{			
	cout<<"\n\t\t\t Ingrese codigo del Producto: ";cin>>p.id;
	cout<<"\n\t\t\t Ingrese nombre del producto: ";cin>>p.nombre_producto;
	cout<<"\n\t\t\t Ingrese cantidad del producto: ";cin>>p.cantidad;
	cout<<"\n\t\t\t Ingrese precio unitario del producto:";cin>>p.precio;
}	
	if(Vereficar_IdProducto(p.id,p.nombre_producto)){
		p.accion=1;
		es<<pro.nombre_proveedor<<" "<<pro.telefono_proveedor<<" "<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad<<" "<<p.precio<<"\n";
		es_historial<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad<<" "<<p.precio<<" "<<p.accion<<" "<<f.dia<<" "<<f.mes<<" "<<f.anio<<endl;
		es_prove<<pro.nombre_proveedor<<" "<<pro.telefono_proveedor<<" "<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad<<" "<<p.precio<<" "<<p.accion<<" "<<f.dia<<" "<<f.mes<<" "<<f.anio<<endl;
	}else{
		cout<<"El producto no se pudo agregar."<<endl;
	}
	es.close();
	es_historial.close();
	es_prove.close();
}
bool Vereficar_IdProducto(int ID,string nombre){
	ifstream leer("Productos.txt",ios::out|ios::app);
	Producto p;
	Proveedor pro;
	leer>>pro.nombre_proveedor;
	while(!leer.eof()){
		leer>>pro.telefono_proveedor;
		leer>>p.id;
		leer>>p.nombre_producto;
		leer>>p.cantidad;
		leer>>p.precio;
		if(p.id == ID or p.nombre_producto==nombre){
			leer.close();
			return false;
		}
		leer>>pro.nombre_proveedor;//Para que el archivos continue
	}
	leer.close();
	return true;
}
void Modificar_Producto(ifstream &Lec){
	system("cls");
	time_t now = time(0);
    tm * time = localtime(&now);
    Fecha f;
	Producto p;
	Proveedor pro;
	int idaux,cantidadaux;
	string nombre_productoaux;
	double precioaux;
	int band;
	Lec.open("Productos.txt",ios::in);//Lectura
	es_prove.open("HistorialProveedor.txt",ios::out|ios::app);
	ofstream aux("auxiliar.txt",ios::out|ios::app);//Escritura
	es_historial.open("HistorialProducto.txt",ios::out|ios::app);
	if(Lec.is_open()){
		cout<<"\n\t\t\t\t\t\t[MODIFICANDO PRODUCTO]\n";
		cout<<"\n\t\t\t\t\t[ID]:";
		cin>>idaux;
		Lec>>pro.nombre_proveedor;
		while(!Lec.eof()){
			Lec>>pro.telefono_proveedor;
			Lec>>p.id;
			Lec>>p.nombre_producto;
			Lec>>p.cantidad; 
			Lec>>p.precio;
			if(p.id==idaux){
				band = 2;
				cout<<"\n\t\t\t\t\tNombre Proveedor:"<<pro.nombre_proveedor;
				cout<<"\n\t\t\t\t\tTelefono Proveedor:"<<pro.telefono_proveedor;
				cout<<"\n\t\t\t\t\tNombre Producto:"<<p.nombre_producto;
				cout<<"\n\t\t\t\t\tCantidad Producto:"<<p.cantidad;
				cout<<"\n\t\t\t\t\tPrecio Producto:"<<p.precio;
				cout<<"\n\t\t\t\t\tCuanto stock desea agregar:";
				cin>>cantidadaux;
				p.accion=3;
				es_prove<<pro.nombre_proveedor<<" "<<pro.telefono_proveedor<<" "<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad+cantidadaux<<" "<<p.precio<<" "<<p.accion<<" "<<f.dia<<" "<<f.mes<<" "<<f.anio<<endl;
				aux<<pro.nombre_proveedor<<" "<<pro.telefono_proveedor<<" "<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad+cantidadaux<<" "<<p.precio<<"\n";
				cout<<"El nuevo stock del producto es "<< p.cantidad+cantidadaux<<endl;
				es_historial<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad+cantidadaux<<" "<<p.precio<<" "<<p.accion<<" "<<f.dia<<" "<<f.mes<<" "<<f.anio<<endl;
			}else{
				aux<<pro.nombre_proveedor<<" "<<pro.telefono_proveedor<<" "<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad<<" "<<p.precio<<"\n";
			}
			Lec>>pro.nombre_proveedor;
		}
		aux.close();
		Lec.close();
		es_historial.close();
	} else{
		cout<<"Error el archivo producto no se encuentra"<<endl;
	} 
	if(band!=2){
		cout<<"\t\t\tEl id no existe"<<endl;
	}else{
		cout<<"\t\t\tProducto Modificado"<<endl;
	}
	remove("Productos.txt");
	rename("auxiliar.txt","Productos.txt");
}

void Eleminar_Producto(ifstream &){
	system("cls");
	time_t now = time(0);
    tm * time = localtime(&now);
    Fecha f;
	Producto p;
	Proveedor pro;
	int idaux,cantidadaux;
	string nombre_productoaux;
	double precioaux;
	cout<<"\n\t\t\t\t\t\t[ELIMINADO PRODUCTO]\n";
	cout<<"\n\t\t\t\t\t[ID]:";cin>>idaux;
	if(NoEliminar(idaux)==1){
	es_historial.open("HistorialProducto.txt",ios::out|ios::app);
	es_prove.open("HistorialProveedor.txt",ios::out|ios::app);
	Lec.open("Productos.txt",ios::in);//Lectura
	ofstream aux("auxiliar.txt",ios::out);//Escritura
	if(Lec.is_open()){
		Lec>>pro.nombre_proveedor;
		while(!Lec.eof()){
			Lec>>pro.telefono_proveedor;
			Lec>>p.id;
			Lec>>p.nombre_producto;
			Lec>>p.cantidad;
			Lec>>p.precio;
			if(p.id==idaux){
				p.accion=2;
				es_historial<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad<<" "<<p.precio<<" "<<p.accion<<" "<<f.dia<<" "<<f.mes<<" "<<f.anio<<endl;
				es_prove<<pro.nombre_proveedor<<" "<<pro.telefono_proveedor<<" "<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad<<" "<<p.precio<<" "<<p.accion<<" "<<f.dia<<" "<<f.mes<<" "<<f.anio<<endl;
				cout<<"\n\t\t\t\t\tEliminado"<<endl;
			}else{
				aux<<pro.nombre_proveedor<<" "<<pro.telefono_proveedor<<" "<<p.id<<" "<<p.nombre_producto<<" "<<p.cantidad<<" "<<p.precio<<"\n";
			}
			Lec>>pro.nombre_proveedor;
		}
		es_prove.close();
		aux.close();
		Lec.close();	
		es_historial.close();
	} else{
		cout<<"Error"<<endl;
	}
		remove("Productos.txt");
		rename("auxiliar.txt","Productos.txt");
	}else{
		cout<<"Producto no eliminado"<<endl;
	}
}
void ver_producto(string nombre){
    Producto p;
    Proveedor pro;
//    system("cls");
    Lec.open("Productos.txt",ios::in);
    Lec>>pro.nombre_proveedor;
    while(!Lec.eof()){
    Lec>>pro.telefono_proveedor;
    Lec>>p.id;
    Lec>>p.nombre_producto;
    Lec>>p.cantidad;
    Lec>>p.precio;
    if(p.nombre_producto==nombre){
    cout<<endl<<"\t\tProveedor\t\tTelefono\t\tID\t\tNOMBRE\t\tCANTIDAD\tPRECIO(U)\n";
    cout<<"\t\t"<<pro.nombre_proveedor;
    cout<<"\t\t\t"<<pro.telefono_proveedor;
    cout<<"\t\t"<<p.id;
    cout<<"\t\t"<<p.nombre_producto;
    cout<<"\t\t"<<p.cantidad;
    cout<<"\t\t"<<p.precio<<endl;
    }
    Lec>>pro.nombre_proveedor;
    }
    Lec.close();
    cout<<endl;
}
void ver_historial_producto(){
    system("cls");
    string dato;
    Producto p;
    Fecha f;
    int total=0;
    Lec_historial.open("HistorialProducto.txt",ios::in);
    cout<<endl<<"\n\t\t\t\t\t*Movimientos de los Producto"<<endl;
    cout<<"\t\t\t Ingrese el nombre del producto que desea consultar:";
    cin>>dato;
    ver_producto(dato);
    Lec_historial>>p.id;
    cout<<"\t\tPRODUCTO\tACCION\t\tCANTIDAD\tPRECIO(U)\tFECHA\n";
    while(!Lec_historial.eof()){
        Lec_historial>>p.nombre_producto;
        Lec_historial>>p.cantidad;
        Lec_historial>>p.precio;
        Lec_historial>>p.accion;
        Lec_historial>>f.dia;
        Lec_historial>>f.mes;
        Lec_historial>>f.anio;
    if(p.nombre_producto==dato){
        if(p.accion==1){
            cout<<"\t\t"<<p.nombre_producto;
            cout<<"\t\t"<<"COMPRA";
            cout<<"\t\t"<<p.cantidad;
            cout<<"\t\t"<<p.precio;
            cout<<"\t\t"<<f.dia<<"/"<<f.mes<<"/"<<f.anio<<endl;
        }
        else if(p.accion==2){
            cout<<"\t\t"<<p.nombre_producto;
            cout<<"\t\t"<<"ELIMINA";
            cout<<"\t\t"<<p.cantidad;
            cout<<"\t\t"<<p.precio;
            cout<<"\t\t"<<f.dia<<"/"<<f.mes<<"/"<<f.anio<<endl;
        }
        else if(p.accion==3){
            cout<<"\t\t"<<p.nombre_producto;
            cout<<"\t\t"<<"ACTUALIZO";
            cout<<"\t"<<p.cantidad;
            cout<<"\t\t"<<p.precio;
            cout<<"\t\t"<<f.dia<<"/"<<f.mes<<"/"<<f.anio<<endl;
        }
        else{
            cout<<"\t\t"<<p.nombre_producto;
            cout<<"\t\t"<<"VENTA";
            cout<<"\t\t"<<p.cantidad;
            cout<<"\t\t"<<p.precio;
            cout<<"\t\t"<<f.dia<<"/"<<f.mes<<"/"<<f.anio<<endl;
            total=total+p.cantidad;
        }
    }
    Lec_historial>>p.nombre_producto;
    }
    cout<<"\nTotal de producto vendido:"<<total;
    Lec_historial.close();
}
void ver_historial_proveedor(){
    system("cls");
    Fecha f;
    string dato;
    Producto p;
    Proveedor pro;
    Lec_historial.open("HistorialProveedor.txt",ios::in);
    cout<<endl<<"\n\t\t\t*Historial Proveedor"<<endl;
    cout<<"Ingrese el nombre del Proveedor que desea consultar:";
    cin>>dato;
    Lec_historial>>pro.nombre_proveedor;
    cout<<"\t\tProveedor\tTelefono\tAccion\t\tProductos\tCantidad\tPrecio(U)\tFecha\n";
    while(!Lec_historial.eof()){
        Lec_historial>>pro.telefono_proveedor;
        Lec_historial>>p.id;
        Lec_historial>>p.nombre_producto;
        Lec_historial>>p.cantidad;
        Lec_historial>>p.precio;
        Lec_historial>>p.accion;
        Lec_historial>>f.dia;
        Lec_historial>>f.mes;
        Lec_historial>>f.anio;
    if(pro.nombre_proveedor==dato){
        if(p.accion==1){
            //se añadio al proveedor tal el producto , Se añadio el producto tal a l proveedor tal
            cout<<"\t\t"<<pro.nombre_proveedor;
            cout<<"\t\t"<<pro.telefono_proveedor;
            cout<<"\t"<<"VENDIO";
            cout<<"\t\t"<<p.nombre_producto;
            cout<<"\t\t"<<p.cantidad;
            cout<<"\t\t"<<p.precio;
            cout<<"\t\t"<<f.dia<<"/"<<f.mes<<"/"<<f.anio<<endl;
        }
        else if(p.accion==2){
            cout<<"\t\t"<<pro.nombre_proveedor;
            cout<<"\t\t"<<pro.telefono_proveedor;
            cout<<"\t"<<"ELIMINO";
            cout<<"\t\t"<<p.nombre_producto;
            cout<<"\t\t"<<p.cantidad;
            cout<<"\t\t"<<p.precio;
            cout<<"\t\t"<<f.dia<<"/"<<f.mes<<"/"<<f.anio<<endl;
        }
        else{
            cout<<"\t\t"<<pro.nombre_proveedor;
            cout<<"\t\t"<<pro.telefono_proveedor;
            cout<<"\t"<<"ACTUALIZO";
            cout<<"\t"<<p.nombre_producto;
            cout<<"\t\t"<<p.cantidad;
            cout<<"\t\t"<<p.precio;
            cout<<"\t\t"<<f.dia<<"/"<<f.mes<<"/"<<f.anio<<endl;
            }
        }
        Lec_historial>>pro.nombre_proveedor;
    }
            Lec_historial.close();
}

void ver_historial_cliente(){
    system("cls");
    cuenta c;
    Producto p;
    Fecha f;
    string dato;
    double total;
    Lec_historial.open("HistorialCliente.txt",ios::in);
    cout<<endl<<"\n\t\t\t*Historial Cliente"<<endl;
    cout<<endl;
    cout<<"Ingrese el nombre del cliente a consultar:";
    cin>>dato;
    Lec_historial>>c.nombre;
        cout<<"\t\t\t HISTORIAL CLIENTES"<<endl;
        cout<<"\t\tClientes\tAccion\tProducto\tCANTIDAD\tPRECIO(U)\tTotal\tFecha\n";
    while(!Lec_historial.eof()){
        Lec_historial>>p.nombre_producto;
        Lec_historial>>p.cantidad;
        Lec_historial>>p.precio;
        Lec_historial>>total;
        Lec_historial>>f.dia;
        Lec_historial>>f.mes;
        Lec_historial>>f.anio;
        if(c.nombre==dato){
        	cout<<"\t\t"<<c.nombre;
			cout<<"\t\t"<<"COMPRO";
			cout<<"\t"<<p.nombre_producto;
			cout<<"\t\t"<<p.cantidad;
			cout<<"\t\t"<<p.precio;
			cout<<"\t\t"<<total;
			cout<<"\t\t"<<f.dia<<"/"<<f.mes<<"/"<<f.anio<<endl;
	}
        Lec_historial>>c.nombre;
    }
    Lec_historial.close();
}
	
void Ver_Registro_Clientes(){
	lec_cuenta.open("Registro_Clientes.txt", ios::in);
	cuenta c;
	if(lec_cuenta.is_open()){
		lec_cuenta>>c.nombre;
		cout<<endl<<"\t\t******Lista de Clientes****"<<endl;	
		cout<<"\t\tNombre\tContrasena\tMonto\tTipocuenta\n";
		while(!lec_cuenta.eof()){
			lec_cuenta>>c.contrasena;
			lec_cuenta>>c.monto;
			lec_cuenta>>c.tipocuenta;
			cout<<"\t\t"<<c.nombre;
			cout<<"\t"<<c.contrasena;
			cout<<"\t\t"<<c.monto;
			cout<<"\t"<<c.tipocuenta<<endl;
			lec_cuenta>>c.nombre;
		}
		lec_cuenta.close();
	} else{
		cout<<"El Archivo no existe"<<endl;
	}
}
//1era
void Archivar_Provee(ofstream &es, string nombpro, int telef){
    Proveedor pro;
    es.open("Proveedor.txt",ios::out|ios::app);
    if(Vereficar_Provee(nombpro)){
        es<<nombpro<<" "<<telef<<"\n";
    }
    es.close();
}

//2da
bool Vereficar_Provee(string nombre){
    ifstream leer("Proveedor.txt",ios::out|ios::app);
    Proveedor pro;
    leer>>pro.nombre_proveedor;
    while(!leer.eof()){
        leer>>pro.telefono_proveedor;
        if(pro.nombre_proveedor==nombre){
            leer.close();
            return false;
        }
        leer>>pro.nombre_proveedor;//Para que el archivos continue
    }
    leer.close();
    return true;
}
//3era
void mostrarProveedor(ifstream &){
    Lec.open("Proveedor.txt", ios::in);
    Producto p;
    Proveedor pro;

    if(Lec.is_open()){
        Lec>>pro.nombre_proveedor;
        cout<<endl<<"\t\t\t\t\t**Registro Proveedor**"<<endl;
        cout<<"\t\t\t\t\tProveedor\tTelefono\n";
        while(!Lec.eof()){
            Lec>>pro.telefono_proveedor;
            cout<<"\t\t\t\t\t"<<pro.nombre_proveedor;
            cout<<"\t\t"<<pro.telefono_proveedor<<endl;
            Lec>>pro.nombre_proveedor;
        }
        Lec.close();
    } else{
        cout<<"Error al abrir el archivo"<<endl;
    }
}

int NoEliminar(int idaux){
    Lec_historial.open("HistorialProducto.txt",ios::in);
    Producto p;
    Fecha f;
    int bandera;
    Lec_historial>>p.id;
    while(!Lec_historial.eof()){
        Lec_historial>>p.nombre_producto;
        Lec_historial>>p.cantidad;
        Lec_historial>>p.precio;
        Lec_historial>>p.accion;
        Lec_historial>>f.dia;
        Lec_historial>>f.mes;
        Lec_historial>>f.anio;
        if(p.accion==1 && p.id==idaux){
        	bandera=1;
	}else if(p.accion!=1 && p.id==idaux){
		bandera=0;
	}
	Lec_historial>>p.id;
        }
        Lec_historial.close();
	if(bandera==1){
		return 1;//eliminarlo
	}else if(bandera==0){
		return 0;//no eliminar
	}
}



