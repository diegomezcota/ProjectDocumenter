#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string createHtml(string &cut){
  string type = "";
  string code = "";
  string end = " ";
  int ind = cut.find("@");
  if (ind != -1){
    type = cut.substr(ind, cut.find(" ") - ind);
    end = cut.substr(cut.find(" ") + 1);
    if (type == "@progName"){
      code = "<h2>\nPrograma: " + end + "\n<br>\n</h2>";
    } else if (type == "@funcName"){
      code = "<h3>\n<hr>\n<br>\nFunción: " + end + "\n<br>\n</h3>\n";
    }
      else {
      if (type == "@desc"){
        type = "Descripción: ";
      } else {
        if (type == "@author"){
          type = "Autor: ";
        } else if (type == "@date"){
          type = "Fecha: ";
        } else if (type == "@param"){
          type = "Parámetros: ";
        } else if (type == "@return") {
          type = "Valor de retorno: ";
        }
      }
        code = "<strong>\n" + type + "\n</strong>\n" + end + "\n<br>";
    }
  }
  return code;
}

void pedirPrograma(string &prog){
  cout << "Cual es tu programa (sin extension)? ";
  cin >> prog;
  prog += ".txt";
}

int main() {
  string programa = "", code = "";
  pedirPrograma(programa);
  // @quepedo
  ifstream inFile(programa.c_str());
  ofstream outFile("output.html");
  programa.erase(programa.find('.'));
  outFile << "<!DOCTYPE html>\n<html>\n<head>\n<title>\nDocumentacion del archivo " << programa << ".cpp\n</title>\n</head>\n";
  string linea = "";
  if (inFile.is_open()){
    while (!inFile.eof()){
      getline(inFile, linea);
      if (linea.find("/**") != -1){
        while (linea.find("*/") == -1){
          getline(inFile, linea);
          code = createHtml(linea);
          outFile << code;
        } 
      }
    }
  } else {
    cout << "No abri el archivo.";
  }
  inFile.close();
  outFile.close();
  return 0;
}