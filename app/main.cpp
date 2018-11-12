#include <iostream>
#include <windows.h>
#include <mysql.h>
  #include <winsock.h>
  #include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
void yolcutanimla();
void ucaklar();
void sefertanimla();//
void biletsatma();//
void yolcusorgulama();//
void ucusiptal();
void biletiptal();//
void sefersorgulama();
void dolulukorani();


void biletsatma(){

MYSQL* con;
MYSQL_ROW row;
MYSQL_RES* res;
MYSQL_FIELD *field;
con=mysql_init(0);

int komut;

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


con=mysql_real_connect(con, "127.0.0.1", "root", "Ahmet100$","ahmet", 0, NULL, 0);

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


         if (mysql_query(con, "CREATE TABLE Seferler(ucaklar_kuyrukno INT,basno INT,bitno INT,tarih INT )")) {
     mysql_error(con);
  }

 if (mysql_query(con, "ALTER TABLE Seferler ADD FOREIGN KEY(ucaklar_kuyrukno )REFERENCES Ucaklar(kuyrukno)")) {
       mysql_error(con);
  }
if (mysql_query(con, "ALTER TABLE Seferler ADD PRIMARY KEY(tarih )")) {
       mysql_error(con);
  }

//  YOLCU
 if (mysql_query(con, "CREATE TABLE Yolcular(ytc BIGINT,yismi TEXT,yadresi TEXT,ysehir TEXT,yposta TEXT )")) {
      mysql_error(con);
  }
if (mysql_query(con, "ALTER TABLE Yolcular ADD PRIMARY KEY(ytc )")) {
       mysql_error(con);
  }




  if (mysql_query(con, "CREATE TABLE Yolcu(tarih INT,ukn INT,tc BIGINT,bin INT,bitn INT )")) {
      mysql_error(con);
  }
  if (mysql_query(con, "ALTER TABLE Yolcu ADD FOREIGN KEY(ukn )REFERENCES Ucaklar(kuyrukno)")) {
       mysql_error(con);
  }
if (mysql_query(con, "ALTER TABLE Yolcu ADD FOREIGN KEY(tc )REFERENCES Yolcular(ytc)")) {
       mysql_error(con);
  }
if (mysql_query(con, "ALTER TABLE Yolcu ADD FOREIGN KEY(tarih )REFERENCES Seferler(tarih)")) {
       mysql_error(con);
  }


string a,b,c;
int d;
        cout<<"Baslangic : "<<endl; cin>>a;
        cout<<"Bitis: "<<endl; cin>>b;
        cout<<"Tarih: "<<endl; cin>>c;
        cout<<"Bilet sayisi: "<<endl; cin>>d;
        int ycz=d;

string query="select * from Seferler where basno='"+a+"' and bitno='"+b+"' and tarih='"+c+"'  ";
        const char* q = query.c_str();
     komut = mysql_query(con,q);

  if(!komut){
    res=mysql_store_result(con);
    cout<<"Kuyruk no-----Baslangis------Bitis-----Tarih\n"<<endl;
    while(row=mysql_fetch_row(res)){



      cout <<" "<<row[0]<<"-- "
    <<" "<<row[1]<<"-- "
    <<" "<<row[2]<<"-- "
    <<" "<<row[3] <<endl;

    }

  }

  else{
    cout<<"hata"<<mysql_error(con)<<endl;
  }

/*
string e;
        cout<<" Secilen seferin kuyruk numarasını yazın : "<<endl; cin>>e;

*/
int ss=0;

while(ss<ycz){
string f;
        cout<<" \nTc numarasini yazin :  "<<endl; cin>>f;

      query="select * from Yolcular where ytc='"+f+"' ";
    q = query.c_str();
     komut = mysql_query(con,q);
if(!komut){
    res=mysql_store_result(con);
    cout<<"TC----ISIM------ADRES--SEHIR---POSTA\n"<<endl;
    while(row=mysql_fetch_row(res)){



      cout <<" "<<row[0]<<"-- "
    <<" "<<row[1]<<"-- "
    <<" "<<row[2]<<"-- "
     <<" "<<row[3]<<"-- "
    <<" "<<row[4] <<endl;

    }/*
if(row==0){

    cout<<" "<<row<<endl;
}*/
  }
 else{
    cout<<"hata"<<mysql_error(con)<<endl;
  }
  int yy=10;
  int tt=0;
  while(yy!=0){

int t;
        cout<<" \nbilet sat:: 1\nyolcu kayit ::2 :  "<<endl; cin>>t;
//d tc sayısı
if(t==1){



            string n;


        cout<<" \nkuyruk no girin:  "<<endl; cin>>n;
///////////



     ////////////////////////

    query="insert into Yolcu values('"+c+"','"+n+"','"+f+ "','"+a+"','"+b+"')";
    q = query.c_str();
     komut = mysql_query(con,q);

     if(!komut){

         cout<<"bilet satildi"<<endl;
ss++;





     }

        else
            cout<<"hata "<<mysql_error(con)<<endl;
            tt++;








 yy=0;
 t=4;
    }
if(t==2){
    string isim,adre,sehi,posta;


        cout<<" isim girin:\n  "<<endl; cin>>isim;

        cout<<" adres:\n  "<<endl; cin>>adre;

        cout<<" sehir: \n  "<<endl; cin>>sehi;

        cout<<" e-posta:\n "<<endl; cin>>posta;





 query="insert into Yolcular values('"+f+"','"+isim+"','"+adre+"','"+sehi+"','"+posta+ "')";
    q = query.c_str();
     komut = mysql_query(con,q);

     if(!komut){

         cout<<"yolcu profili oluşturuldu!!"<<endl;

     }

        else{
            cout<<"hata "<<mysql_error(con)<<endl;

        }





        }


}
}


  }




void ucusiptal(){

MYSQL* con;
MYSQL_ROW row;
MYSQL_RES* res;
MYSQL_FIELD *field;
con=mysql_init(0);

int komut;

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


con=mysql_real_connect(con, "127.0.0.1", "root", "Ahmet100$","ahmet", 0, NULL, 0);

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;

/*
Uçuş iptali: İptal edilen uçuş ya da uçuşlar olursa yolcular tablosunda o uçuşla ilgili tüm bilgiler silinecektir.
Bu işlem on delete cascade opsiyonu ile sağlanmalıdır.
Cascade işlemi ile eğer bir uçuş silinirse bu uçuşa bağlı olan başka bir bağlantılı
uçuş (yani bu uçuş aktarmalı uçuşsa) bulunuyorsa bu uçuşunda silinmesi gerekmektedir.
*/
string a,b,c,d;
        cout<<"KUYRUK NO GIRIN GIRIN: "<<endl; cin>>a;
        cout<<"TARIH GIRIN: "<<endl; cin>>b;
        cout<<"BASLANGIC GIRIN: "<<endl; cin>>c;
 cout<<"BITIS GIRIN: "<<endl; cin>>d;


 string query="delete from Yolcu  where tarih='"+b+"' and bin='"+c+"' and  ukn='"+a+"'and  bitn='"+d+"' ";


      const char*  q = query.c_str();
       komut = mysql_query(con,q);
if(!komut)
            cout<<"\nSefer iptali basarili!!!\n"<<endl;
        else
            cout<<"hata: "<<mysql_error(con)<<endl;


 query="delete from Seferler  where tarih='"+b+"' and basno='"+c+"' and  bitno='"+d+"' and ucaklar_kuyrukno='"+a+"'";

      q = query.c_str();
       komut = mysql_query(con,q);
if(!komut)
            cout<<"--"<<endl;
        else
            cout<<"hata: "<<mysql_error(con)<<endl;

}
void biletiptal(){
    MYSQL* con;
MYSQL_ROW row;
MYSQL_RES* res;
MYSQL_FIELD *field;
con=mysql_init(0);

int komut;
 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


con=mysql_real_connect(con, "127.0.0.1", "root", "Ahmet100$","ahmet", 0, NULL, 0);
/*
 if (mysql_query(con, "CREATE TABLE Yolcu(tarih INT,ukn INT,tc BIGINT,bin INT,bitn INT )")) {
      mysql_error(con);
  }

*/

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


        string a,b,c;
        cout<<"TC GIRIN: "<<endl; cin>>a;
        cout<<"TARIH GIRIN: "<<endl; cin>>b;
        cout<<"KUYRUKNO GIRIN: "<<endl; cin>>c;





        string query="delete from Yolcu  where tarih='"+b+"' and tc='"+a+"' and  ukn='"+c+"' ";


        const char* q = query.c_str();
       komut = mysql_query(con,q);
if(!komut)
            cout<<"\nBilet iptali basarili!!!\n"<<endl;
        else
            cout<<"hata: "<<mysql_error(con)<<endl;
}


void  ucaklar(){



MYSQL* con;
MYSQL_ROW row;
MYSQL_RES* res;
MYSQL_FIELD *field;
con=mysql_init(0);

int komut;

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


con=mysql_real_connect(con, "127.0.0.1", "root", "Ahmet100$","ahmet", 0, NULL, 0);


 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;



// UCAKLAR




  if (mysql_query(con, "CREATE TABLE Ucaklar(kuyrukno INT,model TEXT,kapasite INT )")) {
      mysql_error(con);
  }
 if (mysql_query(con, "ALTER TABLE Ucaklar ADD PRIMARY KEY(kuyrukno )")) {
      mysql_error(con);
  }







   if (mysql_query(con,"INSERT INTO Ucaklar VALUES(1,'onur',1999)")) {
      mysql_error(con);
  }
   if (mysql_query(con, "INSERT INTO Ucaklar VALUES(2,'THY',2000)")) {
       mysql_error(con);
  }

  if (mysql_query(con, "INSERT INTO Ucaklar VALUES(3,'airlines',217)")) {
       mysql_error(con);
  }
 if (mysql_query(con,"INSERT INTO Ucaklar VALUES(4,'Boeing',199)")) {
      mysql_error(con);
  }
   if (mysql_query(con, "INSERT INTO Ucaklar VALUES(5,'pegasus',270)")) {
       mysql_error(con);
  }

  if (mysql_query(con, "INSERT INTO Ucaklar VALUES(6,'franse',217)")) {
       mysql_error(con);
  }
   if (mysql_query(con,"INSERT INTO Ucaklar VALUES(7,'american',5)")) {
      mysql_error(con);
  }
   if (mysql_query(con, "INSERT INTO Ucaklar VALUES(8,'emirates',178)")) {
       mysql_error(con);
  }

  if (mysql_query(con, "INSERT INTO Ucaklar VALUES(9,'gold',817)")) {
       mysql_error(con);
  }


}




void sefertanimla(){


MYSQL* con;
MYSQL_ROW row;
MYSQL_RES* res;
MYSQL_FIELD *field;
con=mysql_init(0);

int komut;

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


con=mysql_real_connect(con, "127.0.0.1", "root", "Ahmet100$","ahmet", 0, NULL, 0);

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;
//      SEFERLER


  if (mysql_query(con, "CREATE TABLE Seferler(ucaklar_kuyrukno INT,basno INT,bitno INT,tarih INT ,biletadet INT)")) {
     mysql_error(con);
  }

 if (mysql_query(con, "ALTER TABLE Seferler ADD FOREIGN KEY(ucaklar_kuyrukno )REFERENCES Ucaklar(kuyrukno)")) {
       mysql_error(con);
  }
if (mysql_query(con, "ALTER TABLE Seferler ADD PRIMARY KEY(tarih )")) {
       mysql_error(con);
  }


 string a,b,c,d;
        cout<<"\nUcak kuyruk numarasi: \n"<<endl; cin>>a;
        cout<<"Baslangic: \n"<<endl; cin>>b;
        cout<<"Bitis: \n"<<endl; cin>>c;
        cout<<"Tarih: \n"<<endl; cin>>d;


        string query="insert into Seferler values('"+a+"','"+b+"','"+c+"','"+d+"',0)";


        const char* q = query.c_str();

       komut = mysql_query(con,q);

        if(!komut)
            cout<<"\nSefer Tanimlandi!!!\n"<<endl;
        else
            cout<<"hata: "<<mysql_error(con)<<endl;


}

void yolcusorgulama(){

MYSQL* con;
MYSQL_ROW row;
MYSQL_RES* res;
MYSQL_FIELD *field;
con=mysql_init(0);

int komut;

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


con=mysql_real_connect(con, "127.0.0.1", "root", "Ahmet100$","ahmet", 0, NULL, 0);

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;

//  YOLCU

/*
  if (mysql_query(con, "CREATE TABLE Yolcu(tarih INT,ukn INT,tc BIGINT,bin INT,bitn INT )")) {
      mysql_error(con);
  }
*/


 string a;
        cout<<"enter tc: "<<endl; cin>>a;
        string query="select *from Yolcu  where Yolcu.tc='"+a+"' ";
        const char* q = query.c_str();
       //et    cout<<"query is: "<<q<<endl;
     komut = mysql_query(con,q);
      //komut=mysql_query(con, "select * from Yolcu where Yolcu.tc=8");
       if(!komut){
    res=mysql_store_result(con);

    cout<< "TARIH---KUYRUKNO---TC--BASLANGIC--BITIS\n";
    while(row=mysql_fetch_row(res)){

      cout <<"  "<<row[0]<<"--"
    <<" "<<row[1]<<"--"
    <<" "<<row[2]<<"--"
    <<" "<<row[3]<<"--"
    <<" "<<row[4] <<endl;


    }
     cout <<"\n"<<endl;
       }else{
    cout<<"hata"<<mysql_error(con)<<endl;
  }

}
void sefersorgulama(){


MYSQL* con;
MYSQL_ROW row;
MYSQL_RES* res;
MYSQL_FIELD *field;
con=mysql_init(0);

int komut;

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


con=mysql_real_connect(con, "127.0.0.1", "root", "Ahmet100$","ahmet", 0, NULL, 0);

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;

/*
mysql_query(con, "select * from yolcular where
TCKN IN(select TCKN from yolcular where ukn and tarih IN(select ukn, tarih
from seferler where (bn = '15', and bin = '34' ) and tarih = '2017-05-20')))");
*/
/*
  if (mysql_query(con, "CREATE TABLE Yolcu(tarih INT,ukn INT,tc BIGINT,bin INT,bitn INT )")) {
      mysql_error(con);
  }
*/


 string a,b;
        cout<<"tarih: "<<endl; cin>>a;
         cout<<"kuyruk no: "<<endl; cin>>b;



        string query="  select *from yolcular where ytc IN(select tc from yolcu where ukn='"+b+"' and tarih='"+a+"' ) ";
        const char* q = query.c_str();
       //et    cout<<"query is: "<<q<<endl;
     komut = mysql_query(con,q);
      if(!komut){
    res=mysql_store_result(con);

    cout<< "TC---ISIM--ADRES--SEHIR-POSTA\n";
    while(row=mysql_fetch_row(res)){

      cout <<"  "<<row[0]<<"--"
    <<" "<<row[1]<<"--"
    <<" "<<row[2]<<"--"
    <<" "<<row[3]<<"--"
    <<" "<<row[4] <<endl;


    }
     cout <<"\n"<<endl;
       }else{
    cout<<"hata"<<mysql_error(con)<<endl;
  }


}
void dolulukorani(){

MYSQL* con;
MYSQL_ROW row;
MYSQL_RES* res;
MYSQL_FIELD *field;
con=mysql_init(0);

int komut;

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


con=mysql_real_connect(con, "127.0.0.1", "root", "Ahmet100$","ahmet", 0, NULL, 0);

 if(!con)
        cout << "HATA!" << mysql_error(con)<< endl;


int sayii=0;
 string a,b;
        cout<<"tarih: "<<endl; cin>>a;
         cout<<"kuyruk no: "<<endl; cin>>b;



        string query="  select *from yolcu where ukn='"+b+"' and tarih='"+a+"'  ";
        const char* q = query.c_str();
       //et    cout<<"query is: "<<q<<endl;
     komut = mysql_query(con,q);
      if(!komut){
    res=mysql_store_result(con);

    while(row=mysql_fetch_row(res)){

    sayii++;


    }
     cout <<"\n"<<endl;
       }

 query="  select kapasite from ucaklar where kuyrukno='"+b+"' ";
        q = query.c_str();
       //et    cout<<"query is: "<<q<<endl;
     komut = mysql_query(con,q);
      if(!komut){
    res=mysql_store_result(con);

    while(row=mysql_fetch_row(res)){
 cout <<""<<sayii<<" / ";
 cout <<""<<row[0]<<endl;

    }
     cout <<"\n"<<endl;
       }



}

int main()
{ /*
2.	Bilet satma: Başlangıç ve bitiş noktaları, tarih ve bilet sayısı sorulacaktır. Bu bilgilere göre uygun olan uçuşlardan öncelikle direk uçuşlar, sonra 1 aktarmalı ve son olarak da 2 aktarmalı uçuşlar listelenecektir. Seçilen uçuş numarası için bir önceki aşamada sorulan bilet sayısı kadar TCKN istenecektir. Eğer TCKN yolcu tablosunda yoksa bu TCKN ile ilgili bilgiler istenecektir. Bilet satma işlemi gerçekleştirildiğinde yolcu tablosuna direkt ekleme işlemi yapılacaktır.

4.	Uçuş iptali: İptal edilen uçuş ya da uçuşlar olursa yolcular tablosunda o uçuşla ilgili tüm bilgiler silinecektir. Bu işlem on delete cascade opsiyonu ile sağlanmalıdır. Cascade işlemi ile eğer bir uçuş silinirse bu uçuşa bağlı olan başka bir bağlantılı uçuş (yani bu uçuş aktarmalı uçuşsa) bulunuyorsa bu uçuşunda silinmesi gerekmektedir.

6.	Sefer sorgulama: Verilen tarih ve kuyruk numarasına göre o uçuşta yer alacak yolcuların tüm bilgileri listelenecektir.
7.	Doluluk oranı en fazla olan uçuşlar listelenecektir. Bu işlem için yolcu tablosundan yararlanmanız gerekmektedir.
8.	Tanımlı olmayan uçak için sefer bilgisi, tanımlı olmayan yolcu için uçuş bilgisi oluşturulamayacaktır. Eğer uçak kapasitesi yeterli değilse bilet satışı yapılamayacaktır.

    */
 /*yolcutanimla();
 sefertanimla()
ucaklar();
biletiptal();
biletsatma();
ucusiptal();
*/

ucaklar();

int t=1;
while(t!=0){
int a;
        cout<<"\nSefer Tanimlama : 1 \nBilet Satma: 2  \nYolcu Sorgulama: 3\nUcus Iptal: 4  \nBilet Iptal: 5   \nSefer Sorgulama: 6 \nDoluluk Orani En Fazla Olan Ucuslar: 7  \nCikis: 8\nTercih::?\n   "<<endl;

        cin>>a;

if(a==1){
sefertanimla();
}
if(a==2){
biletsatma();
}
if(a==3){
yolcusorgulama();
}
if(a==4){
ucusiptal();
}
if(a==5){
biletiptal();
}
if(a==6){
sefersorgulama();
}
if(a==7){
dolulukorani();
}
if(a==8){
t=0;
}
}









 mysql_close(0);
    return 0;


}
