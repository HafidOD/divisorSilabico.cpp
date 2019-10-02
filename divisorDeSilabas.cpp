#include <iostream>
#include <string.h>
#include<windows.h>
#include<stdlib.h>
#include <vector>
using namespace std;

bool isHiato(char v1, char v2);
string silabaTemp(string text);
bool noSeparable(char c1,char c2);
bool strVVstr(string t1, string t2);
string separaSilaba(string text);
int tipoLetra(char letter);
bool onlyConsonants(string text);
void funcSound(string s);

int main() {
  vector<string> words;
  string temp,text;
  cout << "Ingrese texto: "<<endl;
  getline(cin,text);
  // vector of words
  for(int i=0;i<text.length();i++){
    char character = text[i];
    char space = 0x20;
    if(character != space){
      temp+=text[i];
    }
    else{ 
      words.push_back(temp);
      temp="";
    }
  }
  //last elem
  words.push_back(temp);

  for(string word:words){
    string ss= separaSilaba(word);
    cout << ss<<endl;
    funcSound(ss);
  }

  cout<<"Fin del programa" <<endl;
  cin.get();

  return 0;
}


int tipoLetra(char letter){
  int type = 5;
  switch(letter){
    case 'a': 
    type=1;
    break;
    case 'e':
    type=1;
    break;
    case 'o':
    type=1;
    break;
    case 'h':
    type=6;
    break;
    case 'i':
    type=2;
    break;
    case 'u':
    type=2;
    break;
    case '\xFC':
    type=2;
    break;
    case '\xE1':
    type=3;
    break;
    case '\xE9':
    type=3;
    break;
    case '\xF3':
    type=3;
    break;
    case '\xED':
    type=4;
    break;
    case '\xFA':
    type=4;
    break;
  }
  return type;
}
string silabaTemp(string text){
  string temp="";
  string cadena = "";
  char a,b,c;
  a=text[0];
  b=text[1];
  c=text[2];
  int sizeCadena = text.length();
  if (sizeCadena < 3){
    if(sizeCadena == 2){
      if(tipoLetra(a)!=5 && tipoLetra(b) !=5){
        cadena = isHiato(a,b) ? text.substr(0,1): text;
      } else {
        cadena = text;
      }
    } else {
      cadena = text;
    }
  } else {
    if(tipoLetra(a)!=5){
      if(tipoLetra(b)!=5){
        if(tipoLetra(c)!=5){
          if(isHiato(a,b)){
            cadena= text.substr(0,1);
          }
          else{
            if(isHiato(b,c)){
              cadena = text.substr(0,2);
            }
            else {
              cadena = text.substr(0,3);
            }
          }
        }else {
          if(isHiato(a,b)){
            cadena = text.substr(0,1);
          }
          else{
            cadena = text.substr(0,2);
          }
        } 
      } else {
        if (tipoLetra(c)!=5){
          if(b=='h'){
            if(isHiato(a,c)){
              cadena = text.substr(0,1);
            } 
            else {
              cadena = text.substr(0,3);
            }
          } else {
          cadena = text.substr(0,1);
          }
        }
        else {
          if(noSeparable(b,c)){
            cadena = text.substr(0,1);
          } else {
            cadena = text.substr(0,2);
          }
        }
      }
    } else { 
      if (tipoLetra(b)!= 5){
        if (tipoLetra(c)!= 5){
          temp = text.substr(0,3);
          if (temp == "que" || temp == "qui" || temp == "gue" || temp =="gui"){
            cadena = text.substr(0,3);
          }
          else{
            if (isHiato(b,c)){
              cadena = text.substr(0,2);
            }
            else{
              cadena = text.substr(0,3);
            }
          }
        }
        else{
          cadena = text.substr(0,2);
        }
      }
      else{
        if (tipoLetra(c)!= 5){
          if (noSeparable(a,b)){
            cadena = text.substr(0,3);
          }
          else{
            cadena = text.substr(0,1);
          } 
        }
        else{
          if (noSeparable(b,c)){
            cadena = text.substr(0,1);
          }
          else{
            cadena = text.substr(0,1);
          }
        }
      } 
    }
  }
  return cadena;
}

bool noSeparable(char c1,char c2){
  if (c1 == 'b' || c1 == 'c' || c1 == 'd' || c1 == 'f' || c1 == 'g' || c1 == 'p' || c1 == 'r' || c1 == 't'){
    if(c2=='r'){
      return true;
    }
  }
  if (c1 == 'b' || c1 == 'c' || c1 == 'f' || c1 == 'g' || c1 == 'p' || c1 == 't' || c1 =='l' || c1 == 'k'){
    if(c2=='l'){
      return true;
    }
  }
  if( c1 == 'c' && c2 == 'h'){
    return true;
  }
  return false;
}
bool isHiato(char v1,char v2){
  bool booleano = false;
      
  int tipoVocal1 = tipoLetra(v1);
  int tipoVocal2 = tipoLetra(v2);
  
  if (tipoVocal1 == 1 || tipoVocal1 == 3){

    if (tipoVocal2 == 1 || tipoVocal2 == 3){
      booleano = true;
    }
    else{
      booleano = tipoVocal2 == 4? true : false;
    }
  }
  else{

    if (tipoVocal2 == 1){
      tipoVocal1 = tipoLetra(v1);
      booleano = tipoVocal1 == 4 ? true : false;
    }
    else{
      booleano = v1 == v2 ? true: false;
    }
  }
  return booleano;

}
string separaSilaba(string text){
  string cadena = "";

  for(int i=0;i<text.length();i++){
    cadena += tolower(text[i]);
  }

  string s="";
  int cadenaTamano = text.length();
  string temp = text;
  int i=0;
  while(text!=""){

    temp = silabaTemp(text);
	
    if (i==0){
      s += temp;
    }
    else {
      if (onlyConsonants(temp)){
        s += temp;
      } else {
        if (strVVstr(s,temp)){
         s += temp;
        } else {
          if (onlyConsonants(temp)){
            s += temp;
          } else {
            s+= "-" + temp;
          }
        }
      }
    }
    i+=1;
    text=text.substr(temp.length(),text.length());
  }
  return s;
}
bool onlyConsonants(string text){
  int nvocales = 0;
  int i=0;
  char letra;
  while( i < text.length() && nvocales==0){
    letra = text[i];
    if (tipoLetra(letra) != 5){
      nvocales+=1;
    }
    i+=1;
  }
  return nvocales == 0;
}

bool strVVstr(string t1,string t2){
  bool booleano = false;
  char c1 = t1[t1.length()-1];
  char c2 = t2[0];
  if (tipoLetra(c1) != 5 && tipoLetra(c2) != 5){
    if (!isHiato(c1,c2)){
      booleano = true;
    }
  }
  return booleano;
}

void funcSound(string s){

  vector<string> words2;
	string temp2;
	// vector of words
	for(int i=0;i<s.length();i++){
		char character = s[i];
		char guion = 0x2d;
		if(character != guion){
			temp2+=s[i];
		}
		else{ 
			words2.push_back(temp2);
			temp2="";
		}
	}
	//last elem
	words2.push_back(temp2);
		//cout<<words[0]+ ".wav"<<endl;
	
	for(string word:words2){
		string i= word + ".wav";
		PlaySound((i.c_str()),NULL,SND_SYNC);
	}	
}
