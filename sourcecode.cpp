/*
  Lütfi Erdem EYÜBOĞLU No:314018
  Mail:l.erdemeyuboglu@gmail.com
  Tel.No. :+905395201200
  


   A "Matrix, Image and Table Operations" */
/*
For Linux-On Terminal--To compile my c++ code,use 
$g++ codes.cpp
$./a. out
OR
$chmod +x ./a. out
OR for Nameless
$g++ -o output codes.cpp                                 
*/
/*

  Tanımladığım metodlar içerisinde try-catch yapısı kullandım. Bu sayede method içerisinde istemediğim bir durum olduğunda (exeption)
  ilgili throw satırındaki mesajı ekrana yazar.Bu sayede hangi fonksiyon içierisinden hata aldığımızı anlamış oluruz.Örnek vermek gerekirse aşağıdaki gibi 4'e 6'lık bir matris verildiğinde matris kare matris olmadığı için hata mesajını ekrana yazar.
	
	try{
		Matrix<int> (4,6,'e');	
	}
	catch(const char* exception){
		cout << exception;
	}
	
	bu kod 
	"matris kare degil . birim()"
	şeklinde hata verir.
	Hata mesajlarının içerisinde hangi metod içinde hata olduğunu da hata mesajının sonuna ekledim.
*/
	
#include <iostream>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <math.h>
#include <fstream>
using namespace std;

template <class E>
class Satir{
		E* data;
		int uzunluk;
	public:
		Satir();
		//default constractor  uzunluk = 0 dan atar.
		Satir(int uzunluk);
		//Satiri istenilen uzunlukta baslatir. Deger doldurmaz.
		Satir(int uzunluk,const E& deger);
		/*Satir istenilen uzunlukta baslatir.
		Degerler deger olacak sekilde doldurur.*/
		Satir(const Satir<E>& sag);
		// copy constractor
		~Satir();
		// destractor
		
		void init(int uzunluk);
		//gerekli olan belleği ayırırdıktan sonra satiri başlatır.
    int size()const;
		// kaç elemanlı olduğunu dondurur.
    bool checkSize(const Satir<E>& sag)const;
		//satır boyutları aynı ise true değil ise false döner.

    void doldur(int baslangic,int bitis,const E& deger);
		//	baslangiç ve biti indislerine göre satiri doldurur.
		void kaldir();
		//	bellekte tahsis edilen alanı sisteme geri bırakır.		
		bool sifirKontrol()const;//  elemanların sıfır mı değil mi kontrol eder.
		
		Satir<E>& operator=(const Satir<E>& sag);
		/* 
			 satirdaki degerleri kopyalar.
			buna göre bellekten yer ayırır.
		*/
		E& operator[](int index);//indeks kaç ise o elamana elemana ulasir.
		Satir<E>& kopya(const Satir<E>& sag);
		/*
		  satirin degerlerini kopyalar. 
			bellekte yeniden yer ayırmaz.
		*/
		Satir<E>& resize(int uzunluk);
		/*
			matrisin boyutunu yeniden belirler.
      Daha küçük boyuta geçerken fazla olanları direk atar,
			Daha buyuk bir boyuta gecerken yeni satırları sıfır ile doldurur.
		*/
		
		
		//Satir operatorleri
		Satir<E> operator+(const Satir<E>& sag)const;
		Satir<E> operator-(const Satir<E>& sag)const;
		Satir<E> operator*(const Satir<E>& sag)const;
		
		// Skaler operatorleri
		Satir<E> operator+(const E& skaler)const;
		Satir<E> operator-(const E& skaler)const;
		Satir<E> operator*(const E& skaler)const;
		Satir<E> operator/(const E& skaler)const;
		Satir<E> operator%(const E& skaler)const;
		
		E toplam()const;
		// tüm satirdaki elemanlarin toplam degerini bulur.
		string toString(bool isSpace = false)const;
		/*
			satır değerini stringe cevirir.
      isSpace =false ise boşluk yok, 
			 =true ise boşuk var.
		*/
};

template<class E>
class Matrix{

	public:
		Matrix(int satir = 10,int sutun = 10,const E& deger = E());
		// default constractor
		Matrix(int satir,int sutun,char ch);
		/* 
			birim matris için ch='e'
			rastgele değerler için ch='r'.
		*/
		Matrix(const Matrix<E>& sag);
		// copy constractor
		~Matrix();
		// destractor
		
		Matrix<E>& kopya(const Matrix<E>& sag);
		/* 
			bir Matrisin degerlerini kopyalar.
			Yeniden bellek tahsisi yapmaz.
			Ayni boyutta degilse hata verir.
		*/
		
		Matrix<E>& set(const Matrix<E>& sag,int rBasla = 0,int cBasla = 0);
		/*
			bir Matrisin degerlerini set eder. 
			Yeniden bellek tahsisi yapmaz.
			rBasla baslangic satiri,cBasla baslangic kolunu indeksleridir. 
		*/
		
		Matrix<E> get(int rBasla,int rbitis,int cBasla,int cbitis);
		/*
			bir Matrisden alt matris cikartir
			rBasla baslangic,rbitis bitis satir indeksi
			cBasla baslangic,cbitis bitis sütununu indeksleridir.
		*/
		
		void resize(int satir, int sutun);
		/* 
			yeniden boyutlandirma. 
			Daha buyuk bir boyuta gecerken yeni alanları 0 ile doldurur.
		*/
		
		Matrix<E>& operator=(const Matrix<E>& sag);
		/*
			bir satirin degerlerini kopyalar. 
			Yeniden bellek tahsisi yapar.
		*/
		Satir<E>& operator[](int index);
		/*
			indeksinci satir referansi doner.
			Satir duzeyinde islemlerde kullanmak icin.
		*/
	
		void doldur(int baslangic,int bitis,const E& deger);
		/*
			Matrisi doldurur. baslangic = baslangic, 
			bitis = bitis satir indeksleridir.
		*/
		void init(int satir,int sutun);
		// bellek tahsisi yaparak Matrisi baslatir.
		void doldur(int rBasla,int rbitis,int cBasla,int cbitis,const E& deger);
		/* 
			Matrisi doldurur. rBasla = baslangic satiri, 
			rbitis = bitis satiri, cBasla = baslangic sutunu,
			cbitis = bitis satir indeksleridir.
		*/
		void doldur(char ch);
		/*
			Matrisi doldurur. ch = 'e' ise birim matris olarak,
			ch = 'r' 0-255 arasinda degerler olacak sekilde doldurur.
			Birim matris olustururken kare olmasi gerekir yoksa hata verir.
		*/
		void kaldir();
		/*
			tahsis edilmis bellek varsa sisteme geri iade 
			ederek matrisi kaldirir.
		*/
		
		int satirUzun()const;
		// Satir uzunlugunu dondurur.Tahsis edilmemis matrisde 0 doner.
		int sutunUzun()const;
		// Sutun uzunlugunu dondurur.Tahsis edilmemis matrisde 0 doner.
		
		bool boyutKontrol(const Matrix<E>& sag)const;
		/*
			Parametre matris ile satir sutun uzunluklarının 
			aynı olup olmadigini kontrol eder. Ayni ise true doner.
		*/
		bool kareMi()const;
		// kareMi ? kare mi değil mi. 
		void birim();
		// Birim matris olacak sekilde elemanlari doldurur.
		void random();
		//  random olarak 0-255 degerlerle doldurur.
		string toString(bool hasSpace = false)const;
		/*
			Matrisi stringe cevirir.
			Her satirin toString kullanir.
			elemanlar arasinda bosluk istenirse hasSpace = true olmalidir.
		*/
		
		void print(bool hasSpace = true)const;
		/*
			Matrisi ekrana yazar.
			hasSpace = true ise elemanlar arası boşluk olur.
      hasSpace = false ise elemanlar bitişik olur.
		*/
		void print(string filename,bool hasSpace = false)const;
		/*	
			Matrisi dosyaya yazar.
			hasSpace = true ise elemanlar arası boşluk olur.
      hasSpace = false ise elemanlar bitişik olur.
		*/
		
		Satir<E> inciSatir(int index)const;
		// nesne olarak indexdeki satırı döndürür
		Satir<E> inciSutun(int index)const;
		// nesne olarak indexdeki sutunu döndürür
				
		// Matrix operasyonları
		Matrix<E> operator+(const Matrix<E>& sag)const;
		Matrix<E> operator-(const Matrix<E>& sag)const;
		Matrix<E> operator*(const Matrix<E>& sag)const;
		Matrix<E> T()const;
		Matrix<E> emul(const Matrix<E>& sag)const;
		Matrix<E> inv()const;
		/*	
		kendi matrisimizin bir kopyası solda,sağında ise birim matris olacak şekilde Gaus-Jordan metodu kullanılarak tersi alınır.İşlem sonucunda solda birim matris sağda ise ilk matrisin tersi elde edilir.  !	Matris kare degilse veya determinant 0 ise hata döndürür.
		*/
			
		E det()const;
		/*
			Laplace algoritması ile rekursif olarak hesaplanır.
			nxn lik tüm matrislerin determinantını laplace ile rekürsif şekilde hesaplar.	
		*/
		
		E toplam()const;
		
		// skaler operasyon
		Matrix<E> operator+(const E& skaler)const;
		Matrix<E> operator-(const E& skaler)const;
		Matrix<E> operator*(const E& skaler)const;
		Matrix<E> operator/(const E& skaler)const;
		Matrix<E> operator%(const E& skaler)const;
		Matrix<E> operator^(const E& skaler)const;	

    protected:
		Satir<E>* data;
		int uzunluk;
};

template<class E>
class Table : public Matrix<E>{
		string* satirAdi;
		string* sutunAdi;
	public:
		Table(int r = 10,int c = 10,const E& deger = E());
		/*
			r satirlik,c sutunluk table olusturur.
			Arka planda matrix sinifi kullanir.
			deger matrisin varsayilan degerleridir.
		*/
		Table(int r,int c,char ch);
		/*
			r satirlik,c sutunluk table olusturur.
			Arka planda matrix sinifi kullanir.
			ch = 'r' ise 0-255 arasinda degerler alir.
			ch != 'r' ise 0 degerini alir.
		*/
		
		Table(const Table<E>& sag);
		// copy constractor
		~Table();
		
		void setDefaultNames(int satir,int sutun);
		/*
			default satir ve sutun isimleri hesaplar
			kolon isimleri icin kac harfli olmasi gerektigini bulur ve
			oruntusel olarak harf atamalari yapar.
			ornegin sutun = 27 icin AA,AB,...,AZ,BA olarak
			ornegin sutun 677 icin AAA,AAB,AAC...AAZ,ABA,ABB,ABA,...,AZZ,BAA olarak atama yapar.
			Yani her kelimenin en sagindaki harf bittiginde hemen solundaki
			bir sonraki harf olarak atayarak tekrar A dan baslar.
			
		*/
		void init(int satir,int sutun);
		/*
			Tableyi baslatir. satir ve sutun stringleri icin yer ayrimi yapar.
			Datalari saklamak icin Matrix sinifini kullanir.
		*/
		void kaldir();
		/*
			satir ve sutun isimleri yer ayrilmissa kaldirir.
		*/
		
		Table<E>& operator=(const Table<E>& sag);
		
		E& itemAt(int r,int c);
		E& itemAt(string s);
		E& itemAt(string rs,string cs);
		
		void setsatirAdi(string* newsatirAdi,int n);
		void setsutunAdi(string* newsutunAdi,int n);
		string toString(int space = 5)const;
		//stringe cevirir. Elemanlar arasinda space kadar bosluk koyar
		void print()const;
};

enum Type{BINARY,GRAY,RGB};
template<class E>
class Image:public Matrix<E>{
		Type type;
		void readFromBin(ifstream &f); // Gri olarak .bin dosyası okur
		void readFromBin(ifstream &f,bool);//renkli olarak .bin dosyası okur
		void readFromBMP(ifstream &f);//Gri olarak .BMP dosyası okur
		void readFromBMP(ifstream &f,bool);//renkli olarak .BMP dosyası okur
	public:
		Image(int sutunSayisi = 255,int satirSayisi = 255,const E& deger = E(),Type type = RGB);
		/*	Matrix sifindan turer.
			satirSayisi -> Matrix sinifina satir sayisi olarak,
			sutunSayisi -> MAtrix sinifina sutun sayisi olarak parametre gonderilir.
			Extra Type degiskeni goruntunun BINARY - GRAY - RGB oldugunu takip eder.
			Varsayılan deger RGB dir.
		*/
		Image(string filename,string format);
		
		Type getType()const; // Resim tipini dondurur. BINARY - GRAY - RGB
		int getGenislik()const; // genislik 
		int getYukseklik()const; // yukseklik 
		bool boyutKontrolOdd()const; // boyutlar tek sayimi kontrol eder.
		
		void imread(string filename,string format); // dosyadan okur
		void imwrite(string filename,string format);
		
		void color2gray();
		/*	
			Renkli görüntüden Gray görüntü yapar
			O pikseldeki Red,Green,Blue degerlerinin ortalamasini 
			alarak pixeli GRAY a cevirir.
		*/	
		void gray2binary(int threshold);
		/*	
		Gray görüntüden binary yapar.
			Her Pixelin degeri belirlenen eksikten buyuk ise 1 olarak kucukse 0 olarak deger alir.
		*/
		void erosion(const Image<E>& structElement); 
		/*
			Yapisal elemandaki tum elemanlar goruntunun o bolgesine FIT oluyorsa
			yani noktasal carpimi yine yapisal elemanin eleman toplamina esitse
			o pixel degerine dokunmaz. Eger ki FIT olmuyorsa o pixel degerini
			0 yapar yani siler.
		*/
		void dilation(const Image<E>& structElement);
			/*
			Yapisal elemandaki tum elemanlar goruntunun o bolgesine Hit oluyorsa
			yani noktasal carpim degeri sifir degilse en az bir eleman eslesiyor
			demektir.Bu durumda o pixel degeri 1 olur.
			Hicbir eşleşme yok ise o pixel degerine dokunmaz.
		*/
		void opening(const Image<E>& structElement); 
		/* 
			Bu islemde erosion ve dilation islemleri arka arka sirasi ile 
			ayni goruntuye uygulanir.
			yani asindirma + genisletme
		*/
		void closing(const Image<E>& structElement); // genisletme + asindirma
		/* 
			Bu islemde dilation ve erosion islemleri arka arka sirasi ile
			ayni goruntuye uygulanir.
			yani genisletme + asindirma
		*/
};
struct rgb{
	int red;
	int green;
	int blue;
	rgb(int red = 0,int green = 0,int blue = 0)
	: red(red),green(green),blue(blue)
	{	}
};
// create pixel level
rgb createPixelRGB(int red,int green,int blue);
rgb createPixelGray(int gray);

// convert pixel before to(2) after
rgb convertBGR2RGB(const rgb& pixel);
rgb convertRGB2Gray(const rgb& pixel);
rgb convertBGR2Gray(const rgb& pixel);
rgb convertGray2Binary(const rgb& pixel,int threshold);

// RGB struct operasyonlar 
rgb operator+(const rgb& sol,const rgb& sag);
rgb operator-(const rgb& sol,const rgb& sag);
rgb operator*(const rgb& sol,const rgb& sag);

// RGB skaler operasyonlar 
template<typename E>
rgb operator+(const rgb& sol,E skaler);
template<typename E>
rgb operator-(const rgb& sol,E skaler);
template<typename E>
rgb operator*(const rgb& sol,E skaler);
template<typename E>
rgb operator/(const rgb& sol,E skaler);
template<typename E>
rgb operator%(const rgb& sol,E skaler);

bool operator>(const rgb& sol, const rgb& sag)
{	return	sol.green > sag.green;	}
bool operator<(const rgb& sol, const rgb& sag)
{	return	sol.green < sag.green;	}
bool operator==(const rgb& sol, const rgb& sag)
{	return	sol.green == sag.green;	}

ostream& operator<<(ostream& out,const rgb& r);

rgb createPixelRGB(int red,int green,int blue)
{	return rgb(red,green,blue);	}

rgb createPixelGray(int gray)
{	return rgb(0,gray,0);	}

// convert pixel before to(2) after
rgb convertBGR2RGB(const rgb& pixel)
{	return rgb(pixel.blue,pixel.green,pixel.red);	}

rgb convertRGB2Gray(const rgb& pixel)
{	return createPixelGray((pixel.red + pixel.green + pixel.blue) / 3); }

rgb convertBGR2Gray(const rgb& pixel)
{	return convertBGR2Gray(convertBGR2RGB(pixel));	}

rgb convertGray2Binary(const rgb& pixel,int threshold)
{	
	return 	pixel.green > threshold 
			? createPixelGray(0)
			: createPixelGray(1);
}

rgb operator+(const rgb& sol,const rgb& sag)
{
	int red = sol.red + sag.red;
	int green = sol.green + sag.green;
	int blue = sol.blue + sag.blue;
	return rgb(red,green,blue);
}

rgb operator-(const rgb& sol,const rgb& sag)
{	return sol + (sag * -1.0);	}

rgb operator*(const rgb& sol,const rgb& sag)
{
	int red = sol.red * sag.red;
	int green = sol.green * sag.green;
	int blue = sol.blue * sag.blue;
	return rgb(red,green,blue);
}

template<typename E>
rgb operator+(const rgb& sol,E skaler)
{	return sol + rgb(skaler,skaler,skaler);	}

template<typename E>
rgb operator-(const rgb& sol,E skaler)
{	return sol - rgb(skaler,skaler,skaler);	}

template<typename E>
rgb operator*(const rgb& sol,E skaler)
{	return sol * rgb(skaler,skaler,skaler);	}

template<typename E>
rgb operator/(const rgb& sol,E skaler)
{
	int red = sol.red / skaler;
	int green = sol.green / skaler;
	int blue = sol.blue / skaler;
	return rgb(red,green,blue);
}

template<typename E>
rgb operator%(const rgb& sol,E skaler)
{
	int red = sol.red % skaler;
	int green = sol.green % skaler;
	int blue = sol.blue % skaler;
	return rgb(red,green,blue);
}

ostream& operator<<(ostream& out,const rgb& r)
{	
	out << r.green;
  //out << r.red << "," << r.green << "," << r.blue;
	return out;
}



template<class E>
Satir<E>::Satir()
: data(NULL),uzunluk(0)
{	}
		
template<class E>
Satir<E>::Satir(int uzunluk)
: Satir<E>()
{	init(uzunluk); } 

template<class E>
Satir<E>::Satir(int uzunluk,const E& deger)
: Satir<E>(uzunluk)
{	
	doldur(0,uzunluk,deger);
}

template<class E>
Satir<E>::Satir(const Satir<E>& sag)
: data(NULL)
{	*this = sag;	}

template<class E>
Satir<E>::~Satir()
{	kaldir();	}

template<class E>
Satir<E>& Satir<E>::operator=(const Satir<E>& sag)
{
	if(this != &sag){
		init(sag.uzunluk);
		kopya(sag);
	}
	return *this;	
}

template<class E>
void Satir<E>::init(int uzunluk)
{
	kaldir();
	this->uzunluk = uzunluk;
	data = new E[uzunluk];
}	

template<class E>
void Satir<E>::kaldir()
{
	if(data){
		delete[] data;
		data = NULL;
	}
}

template<class E>
void Satir<E>::doldur(int baslangic,int bitis,const E& deger)
{
	if(data){
		for(int i = baslangic;i < bitis;i++)
			data[i] = deger;
	}
	else
		throw "dataya yer ayrilmamis .doldur(baslangic,bitis,deger) ";
}

template<class E>
int Satir<E>::size()const
{	return uzunluk;	}

template<class E>
bool Satir<E>::checkSize(const Satir<E>& sag)const
{	return uzunluk == sag.uzunluk;	}

template<class E>
bool Satir<E>::sifirKontrol()const
{	
	for(int i = 0;i<uzunluk;i++)
		if(data[i] != 0)
			return false;
	return true;
}

template<class E>
Satir<E>& Satir<E>::kopya(const Satir<E>& sag)
{
	if(!checkSize(sag))
		throw "boyutlar ayni degil . kopya(sag) ";
	for(int i = 0 ; i < uzunluk;i++)
		data[i] = sag.data[i];
	return *this;
}

template<class E>
Satir<E>& Satir<E>::resize(int uzunluk)
{
	if(this->uzunluk != uzunluk){
		Satir<E> tmp(uzunluk);
		int availableLength = this->uzunluk < uzunluk ? this->uzunluk : uzunluk;
		for(int i=0;i<availableLength;i++)
			tmp[i] = data[i];
		*this = tmp;
	}
	return *this;
}

template<class E>
E& Satir<E>::operator[](int index)
{
	if(index < 0 || index >= uzunluk)
		throw " index hatali operator[](index)";
	return data[index];
}

template<class E>
Satir<E> Satir<E>::operator+(const Satir<E>& sag)const
{
	if(!checkSize(sag))
		throw "boyutlar ayni degil. operator+(sag) ";
	Satir<E> tmp(uzunluk);
	for(int i=0;i<uzunluk;i++)
		tmp[i] = data[i] + sag.data[i];
	return tmp;
}

template<class E>
Satir<E> Satir<E>::operator-(const Satir<E>& sag)const
{
	if(!checkSize(sag))
		throw "boyutlar ayni degil. operator-(sag) ";
	return *this + Satir<E>(uzunluk,-1) * sag;
}

template<class E>
Satir<E> Satir<E>::operator*(const Satir<E>& sag)const
{
	if(!checkSize(sag))
		throw " boyutlar ayni degil . operator*(sag)";
	Satir<E> tmp(uzunluk);
	for(int i=0;i<uzunluk;i++)
		tmp[i] = data[i] * sag.data[i];
	return tmp;
}

template<class E>
Satir<E> Satir<E>::operator+(const E& skaler)const
{	return *this + Satir<E>(uzunluk,skaler);	}

template<class E>
Satir<E> Satir<E>::operator-(const E& skaler)const
{	return *this - Satir<E>(uzunluk,skaler);	}

template<class E>
Satir<E> Satir<E>::operator*(const E& skaler)const
{	return *this * Satir<E>(uzunluk,skaler);	}

template<class E>
Satir<E> Satir<E>::operator/(const E& skaler)const
{
	Satir<E> tmp(uzunluk);
	for(int i=0;i<uzunluk;i++)
		tmp[i] = data[i] / skaler;
	return tmp;
}

template<class E>
Satir<E> Satir<E>::operator%(const E& skaler)const
{
	Satir<E> tmp(uzunluk);
	for(int i=0;i<uzunluk;i++)
		tmp[i] = data[i] % skaler;
	return tmp;
}

template<class E>
E Satir<E>::toplam()const
{
	E result = E();
	if(data){
		for(int i=0;i<uzunluk;i++)
			result = result + data[i];
	}
	return result;
}

template<class E>
string Satir<E>::toString(bool isSpace)const
{
	stringstream ss;
	string space = (isSpace ? " ":"");
	if(data){
		for(int i = 0 ; i < uzunluk;i++)
			ss << data[i] << space;
	}
	return ss.str();
}



template<class E>
Matrix<E>::Matrix(int satir,int sutun,const E& deger)
: data(NULL)
{
	init(satir,sutun);
	doldur(0,satir,0,sutun,deger);
}

template<class E>
Matrix<E>::Matrix(int satir,int sutun,char ch)
: data(NULL)
{	
	init(satir,sutun);
	doldur(ch);
}

template<class E>
Matrix<E>::Matrix(const Matrix<E>& sag) : data(NULL)
{	*this = sag;	}

template<class E>
Matrix<E>::~Matrix()
{	kaldir();	}

template<class E>
Matrix<E>& Matrix<E>::kopya(const Matrix<E>& sag){
	if(!boyutKontrol(sag))
		throw " boyutlar ayni degil. kopya(sag)";
	return set(sag);
}
template<class E>
Matrix<E>& Matrix<E>::set(const Matrix<E>& sag,int rBasla,int cBasla){
	int rBoyut = satirUzun();
	int cBoyut = sutunUzun();
	int sag_rBoyut = sag.satirUzun();
	int sag_cBoyut = sag.sutunUzun();
	if(rBasla < 0 || sag_rBoyut + rBasla > rBoyut)
		throw "rBasla hatali. set(sag,rBasla,cBasla) ";
	if(cBasla < 0 || sag_cBoyut + cBasla > cBoyut)
		throw "cBasla hatali. set(sag,rBasla,cBasla) ";
	for(int i = 0 ;i < sag_rBoyut;i++){
		for(int j=0;j< sag_cBoyut;j++)
			data[rBasla + i][cBasla + j] = sag.data[i][j];
	}
	return *this;
}

template<class E>
Matrix<E> Matrix<E>::get(int rBasla,int rbitis,int cBasla,int cbitis)
{
	int rBoyut = satirUzun();
	int cBoyut = sutunUzun();
		
	if(rBasla < 0 || rBasla >= rBoyut || rBasla > rbitis)
		throw "rBasla hatali get(rBasla,rbitis,cBasla,cbitis) ";
	if(rbitis < 0 || rbitis > rBoyut)
		throw "rbitis hatali get(rBasla,rbitis,cBasla,cbitis) ";
	if(cBasla < 0 || cBasla >= cBoyut || cBasla > cbitis)
		throw "cBasla hatali get(rBasla,rbitis,cBasla,cbitis) ";
	if(cbitis < 0 || cbitis > cBoyut)
		throw "cbitis hatali . get(rBasla,rbitis,cBasla,cbitis) ";
	Matrix<E> tmp(rbitis-rBasla,cbitis-cBasla);
	for(int i=rBasla;i < rbitis;i++){
		int new_i = i-rBasla;
		for(int j = cBasla;j<cbitis;j++)
		{
			tmp[new_i][j-cBasla] = data[i][j];
		}
	}
	return tmp;
}


template<class E>
void Matrix<E>::resize(int satir, int sutun)
{
	Matrix<E> tmp(satir,sutun);
	int forrow = satir < satirUzun() ? satir : satirUzun();
	int forcol = sutun < sutunUzun() ? sutun : sutunUzun();
	for(int i=0;i<forrow;i++)
		for(int j = 0;j < forcol;j++)
			tmp[i][j] = data[i][j];
	*this = tmp;
}

template<class E>
Matrix<E>& Matrix<E>::operator=(const Matrix<E>& sag)
{
	if(this != &sag){
		init(sag.satirUzun(),sag.sutunUzun());
		kopya(sag);
	}
	return *this;
}

template<class E>
Satir<E>& Matrix<E>::operator[](int index)
{
	if(index < 0 || index >= uzunluk)
		throw "index hatali. operator[](index) ";
	return data[index];
}

template<class E>
void Matrix<E>::init(int satir,int sutun)
{
	kaldir();
	uzunluk = satir;
	data = new Satir<E>[uzunluk];
	for(int i=0;i<uzunluk;i++)
		data[i].init(sutun);
}

template<class E>
void Matrix<E>::kaldir()
{
	if(data){
		for(int i = 0; i < uzunluk;i++)
			data[i].kaldir();
		delete [] data;
		data = NULL;
	}
}

template<class E>
int Matrix<E>::satirUzun()const
{	return data ? uzunluk : 0;	}

template<class E>
int Matrix<E>::sutunUzun()const
{	return data ? data[0].size() : 0;	}

template<class E>
void Matrix<E>::doldur(int rBasla,int rbitis,int cBasla,int cbitis,const E& deger)
{
	for(int i=rBasla;i<rbitis;i++)
		data[i].doldur(cBasla,cbitis,deger);	
}

template<class E>
void Matrix<E>::doldur(char ch)
{
	switch(ch){
		case 'e':
		case 'E':
			birim();
			break;
		case 'r':
		case 'R':
			random();
			break;
	}
}

template<class E>
bool Matrix<E>::boyutKontrol(const Matrix<E>& sag)const
{	
	return 	satirUzun() == sag.satirUzun() &&
			sutunUzun() == sag.sutunUzun();
}
		
template<class E>
bool Matrix<E>::kareMi()const
{	return data && satirUzun() == sutunUzun();	}

template<class E>
void Matrix<E>::birim()
{
	if(data){
		if(!kareMi())
			throw "matris kare degil . birim() ";
		int cBoyut = sutunUzun();
		int rBoyut = satirUzun();
		
		for(int i = 0 ; i < rBoyut;i++){
			for(int j = 0 ; j < cBoyut;j++)
				//data[i][j] = i == j ? 1.0 : 0.0;
         if(i==j){
          data[i][j]=1.0;
        }
        else{
          data[i][j]=0.0;
        }
		}
	}
}

template<class E>
void Matrix<E>::random()
{
	if(data){
		int sutun = data[0].size();
		for(int i = 0 ; i < uzunluk;i++){
			for(int j = 0 ; j < sutun;j++)
				data[i][j] = rand() % 256;
		}
	}
}

template<class E>
string Matrix<E>::toString(bool isSpace)const
{
	string tmp;
	for(int i = 0 ; i < uzunluk;i++)
		tmp += data[i].toString(isSpace) + "\n";
	return tmp;
}

template<class E>
void Matrix<E>::print(bool hasSpace)const
{
	cout << toString(hasSpace);	
}

template<class E>
void Matrix<E>::print(string filename,bool hasSpace)const
{
	ofstream f(filename.c_str());
	if(f.is_open()){
		f << toString(hasSpace);
		f.close();
	}
}

template<class E>
Satir<E> Matrix<E>::inciSatir(int index)const
{
	if(index < 0 || index >=uzunluk)
		throw "index hatali . getRow(index) ";			
	return data[index];
}

template<class E>
Satir<E> Matrix<E>::inciSutun(int index)const
{
	try{
		int rBoyut = satirUzun();
		Satir<E> tmp(rBoyut);
		for(int i = 0 ; i < rBoyut;i++)
			tmp[i] = inciSatir(i)[index];
		return tmp;
	}
	catch(...){	
		throw " index hatali . inciSutun(index)";			
	}	
}


template<class E>
Matrix<E> Matrix<E>::operator+(const Matrix<E>& sag)const
{
	if(!boyutKontrol(sag))
		throw " boyutlar ayni degil . operator+(sag)";
	int rBoyut = satirUzun();
	Matrix<E> tmp(rBoyut,sutunUzun());
	for(int i = 0 ; i < rBoyut;i++)
		tmp[i] = inciSatir(i) + sag.inciSatir(i);
	return tmp;
}

template<class E>
Matrix<E> Matrix<E>::operator-(const Matrix<E>& sag)const
{
	try{
		return *this + sag * -1;
	}
	catch(...){	
		throw "boyutlar ayni degil. operator-(sag) ";
	}
}

template<class E>
Matrix<E> Matrix<E>::operator*(const Matrix<E>& sag)const
{
	if(sutunUzun() != sag.satirUzun())
		throw "boyutlar uygun degil. operator* ";
	int rBoyut = satirUzun();
	int cBoyut = sag.sutunUzun();
	Matrix<E> tmp(rBoyut,cBoyut);
	for(int i = 0; i < rBoyut ; i++){
		Satir<E> satir = inciSatir(i);
		for(int j = 0 ; j < cBoyut ; j++)
			tmp[i][j] = (satir * sag.inciSutun(j)).toplam();
	}
	return tmp;
}


template<class E>
Matrix<E> Matrix<E>::T()const
{
	int cBoyut = sutunUzun();
	Matrix<E> tmp(cBoyut,satirUzun());
	for(int i = 0 ; i < cBoyut; i++)
		tmp[i] = inciSutun(i);
	return tmp;
}

template<class E>
Matrix<E> Matrix<E>::emul(const Matrix<E>& sag)const
{
	if(!boyutKontrol(sag))
		throw "boyutlar ayni degil. emul(sag) ";
	int rBoyut = satirUzun();
	Matrix<E> tmp(rBoyut,rBoyut);
	for(int i = 0 ; i < rBoyut;i++)
		tmp[i] = inciSatir(i) * sag.inciSatir(i);
	return tmp;
}

template<class E>
Matrix<E> Matrix<E>::inv()const
{
	if(!kareMi())
		throw "matrix kare degil . inv() ";
	if(det() == E())
		throw " matrixin determinanti 0 . inv()";
	int rBoyut = satirUzun();
	Matrix<E> copyMatrix = *this;
	Matrix<E> ters(rBoyut,rBoyut,'e');
	int i = 0;
	//Matris(üstucgen)
	while(i < rBoyut){
		E pivotCoeffient = copyMatrix[i][i];
		if(pivotCoeffient == E()){
			for(int j = i ; j < rBoyut ; j++)
			{
				if(copyMatrix[j][i] != E()){
					Satir<E>  satir = copyMatrix[i];
					copyMatrix[i] = copyMatrix[j];
					copyMatrix[j] = satir;
					 
					satir = ters[i];
					ters[i] = ters[j];
					ters[j] = satir;
					pivotCoeffient = copyMatrix[i][i];
					break;
				}
			}
		}
		copyMatrix[i] = copyMatrix[i] / pivotCoeffient;
		ters[i] = ters[i] / pivotCoeffient;
		for(int j = i + 1;j< rBoyut;j++){
			E coeffient = copyMatrix[j][i];
			copyMatrix[j] = copyMatrix[j] -  copyMatrix[i] * coeffient;
			ters[j] = ters[j] - ters[i] * coeffient;
		}
		i++;
	}
	
	//Matris(altücgen)
	while(--i > 0){
		for(int j = i - 1;j >= 0;j--){
			E coeffient = copyMatrix[j][i];
			copyMatrix[j] = copyMatrix[j] -  copyMatrix[i] * coeffient;
			ters[j] = ters[j] - ters[i] * coeffient;
		}
	}

	return ters;
}

template<class E>
E Matrix<E>::det()const
{
	if(!kareMi())
		throw " matrix kare degil. det()";
	if(satirUzun() == 1)
		return data[0][0];
	int rBoyut = satirUzun();
	E result = E();
	for(int i = 0 ; i < rBoyut ; i++){
		if(data[0][i] != 0){
			Matrix<E> tmp(rBoyut - 1,rBoyut - 1);
			for(int j = 1 ; j < rBoyut ; j++)
			{
				for(int k = 0; k < rBoyut;k++){
					if(k < i)
						tmp[j-1][k] = data[j][k];
					else if(k > i)
						tmp[j-1][k - 1] = data[j][k];
				}
			}
			result += pow(-1,i) * data[0][i] * tmp.det();
		}
	}

	return result;
}

template<class E>
Matrix<E> Matrix<E>::operator+(const E& skaler)const
{	return *this + Matrix<E>(satirUzun(),sutunUzun(),skaler);	}

template<class E>
Matrix<E> Matrix<E>::operator-(const E& skaler)const
{	return *this - Matrix<E>(satirUzun(),sutunUzun(),skaler);	}


template<class E>
Matrix<E> Matrix<E>::operator*(const E& skaler)const
{
	int rBoyut = satirUzun();
	Matrix<E> tmp(rBoyut,sutunUzun());
	for(int i = 0 ; i < rBoyut ;i++)
		tmp[i] = inciSatir(i) * skaler;
	return tmp;
}

template<class E>
Matrix<E> Matrix<E>::operator/(const E& skaler)const
{
	Matrix<E> tmp = *this;
	int rBoyut = satirUzun();
	for(int i = 0;i < rBoyut;i++)
		tmp[i] = tmp[i] / skaler;
	return tmp;
}

template<class E>
Matrix<E> Matrix<E>::operator%(const E& skaler)const
{
	Matrix<E> tmp = *this;
	int rBoyut = satirUzun();
	for(int i = 0;i < rBoyut;i++)
		tmp[i] = tmp[i] % skaler;
	return tmp;
}

template<class E>
Matrix<E> Matrix<E>::operator^(const E& skaler)const
{
	Matrix<E> tmp(satirUzun(),sutunUzun(),'e');
	for(int i = 0;i<skaler;i++)
		tmp = tmp * *this;
	return tmp;
}

template<class E>
E Matrix<E>::toplam()const
{
	E result = E();
	int rBoyut = satirUzun();
	for(int i=0;i<rBoyut;i++)
		result = result + inciSatir(i).toplam();
	return result;
}

template<class E>
Table<E>::Table(int r,int c,const E& deger)
: Matrix<E>(r,c,deger), satirAdi(NULL),sutunAdi(NULL)
{	
	init(r,c);
	setDefaultNames(r,c);
}

template<class E>
Table<E>::Table(int r,int c,char ch)
: Matrix<E>(r,c) , satirAdi(NULL),sutunAdi(NULL)
{	
	switch(ch){
		case 'r':
		case 'R':
			Matrix<E>::random();
			break;
	}
	init(r,c);
	setDefaultNames(r,c);
}

template<class E>
Table<E>::Table(const Table<E>& sag)
: satirAdi(NULL),sutunAdi(NULL)
{	*this = sag;	}

template<class E>
Table<E>::~Table()
{	kaldir();	}

template<class E>
void Table<E>::init(int satir,int sutun)
{
	kaldir();
	satirAdi = new string[satir];
	sutunAdi = new string[sutun];
}

template<class E>
void Table<E>::setDefaultNames(int satir,int sutun)
{
	string tmpsatirAdi[satir];
	string tmpsutunAdi[sutun];
	stringstream ss;
	
	for(int i = 0 ; i < satir;i++)
	{
		ss << i;
		getline(ss,tmpsatirAdi[i]);
		ss.clear();
	}
	
	int letterCount = 26;
	int entropy = sutun == 1 ? 1 : ceil(log(sutun) / log(letterCount));
	for(int i = 0 ; i < sutun ; i++){
		int deger = i;
		for(int e = entropy - 1 ; e >= 0 ; e--){
			int energy = deger / pow(letterCount,e);
			tmpsutunAdi[i] += (char)(energy + 65);
			deger -= energy * pow(letterCount,e);
		}
	}
	setsatirAdi(tmpsatirAdi,satir);
	setsutunAdi(tmpsutunAdi,sutun);
}

template<class E>
void Table<E>::kaldir()
{
	if(satirAdi)
		delete [] satirAdi;
	if(sutunAdi)
		delete [] sutunAdi;
	satirAdi = NULL;
	sutunAdi = NULL;
}

template<class E>
Table<E>& Table<E>::operator=(const Table<E>& sag)
{
	if(this != &sag){
		Matrix<E>::operator=(sag);
		int rBoyut = sag.satirUzun();
		int cBoyut = sag.sutunUzun();
		init(rBoyut,cBoyut);
		setsatirAdi(sag.satirAdi,rBoyut);
		setsutunAdi(sag.sutunAdi,cBoyut);
	}
	return *this;
}

template<class E>
E& Table<E>::itemAt(int r,int c)
{
	if(r < 0 || r >= Matrix<E>::satirUzun())
		throw "r parametresi hatali . itemAt(r,c) ";
	if(c < 0 || c >= Matrix<E>::sutunUzun())
		throw "c parametresi hatali. itemAt(r,c) ";
	return Matrix<E>::data[r][c];
}

template<class E>
E& Table<E>::itemAt(string s)
{
	if(s.empty())
		throw " s stringi bos. itemAt(s)";
	int rBoyut = Matrix<E>::satirUzun();
	int cBoyut = Matrix<E>::sutunUzun();
	for(int i = 0 ; i < cBoyut;i++)
	{
		for(int j = 0;j< rBoyut;j++)
			if(s == sutunAdi[i] + satirAdi[j])
				return itemAt(j,i);
	}
	throw " aranan indeksler bulunamad. itemAt(s)i";
}

template<class E>
E& Table<E>::itemAt(string rs,string cs)
{
	try{
		return itemAt(cs + rs);
	}
	catch(...){
		throw " aranan indeksler bulunamadi . itemAt(rs,cs)";
	}
}

template<class E>
void Table<E>::setsatirAdi(string* newsatirAdi,int n)
{
	if(satirAdi){
		for(int i = 0;i<n;i++)
			satirAdi[i] = newsatirAdi[i];
	}
}

template<class E>
void Table<E>::setsutunAdi(string* newsutunAdi,int n)
{
	if(sutunAdi){
		for(int i = 0;i<n;i++)
			sutunAdi[i] = newsutunAdi[i];
	}
}

template<class E>
string Table<E>::toString(int space)const
{
	stringstream matSS,ss;
	matSS << Matrix<E>::toString(true);
	int sutun = Matrix<int>::sutunUzun();
	ss << left << setw(space * 2) << "";
	for(int i = 0 ; i < sutun;i++)
		ss  << setw(space) << sutunAdi[i];
	ss << endl;
	int satir = 0;
	string line;
	while(getline(matSS,line)){
		ss << setw(space * 2) << satirAdi[satir];
		stringstream lineSS;
		lineSS << line;
		string lineReader;
		while(lineSS >>lineReader)
			ss << setw(space) << lineReader;
		ss << endl;
		satir++;
	}
	return ss.str();
}

template<class E>
void Table<E>::print()const{
	cout << toString();//bosluklar icin varsayilan degeri baz alir.
}


template<class E>
Image<E>::Image(int sutunSayisi,int satirSayisi,const E& deger,Type type)
: Matrix<E>(satirSayisi,sutunSayisi,deger), type(type)
{		}

template<class E>
Image<E>::Image(string filename,string format)
{	imread(filename,format);	}

template<class E>
Type Image<E>::getType()const
{	return type;	}

template<class E>
int Image<E>::getGenislik()const
{	return Matrix<E>::sutunUzun();	}

template<class E>
int Image<E>::getYukseklik()const
{	return Matrix<E>::satirUzun();	}

template<class E>
bool Image<E>::boyutKontrolOdd()const
{	return getGenislik() % 2 && getYukseklik() % 2;	}

template<class E>
void Image<E>::readFromBin(ifstream &f)
{
	unsigned char size[2];
	unsigned char reader;
	f.read((char*)size,sizeof(size));
	int satirSayisi = (int)size[0];
	int sutunSayisi = (int)size[1];
	Matrix<E>::resize(satirSayisi,sutunSayisi);
	for(int i=0;i<satirSayisi;i++){
		for(int j = 0 ; j < sutunSayisi;j++){
			f.read((char*)&reader,sizeof(reader));
			Matrix<E>::data[i][j] = createPixelGray(reader);
		}
	}
	
}
template<class E>
void Image<E>::readFromBin(ifstream &f,bool)
{

	unsigned char size[2];
	unsigned char reader[3];
	f.read((char*)size,sizeof(size));
	int satirSayisi = (int)size[0];
	int sutunSayisi = (int)size[1];
	Matrix<E>::resize(satirSayisi,sutunSayisi);
	for(int i=0;i<satirSayisi;i++){
		for(int j = 0 ; j < sutunSayisi;j++){
			f.read((char*)&reader,sizeof(reader));
			rgb pixel = createPixelRGB(reader[0],reader[1],reader[2]);
			Matrix<E>::data[i][j] = convertBGR2RGB(pixel);

		}
	}
	
}
template<class E>
void Image<E>::readFromBMP(ifstream &f)
{	
	unsigned char info[54];
	f.read((char*)info,sizeof(info));
	int satirSayisi = (int)info[22];
	int sutunSayisi = (int)info[18];
	unsigned char reader;
	Matrix<E>::resize(satirSayisi,sutunSayisi);
	f.seekg((int)info[10],ios::beg);
	for(int i=0;i<satirSayisi;i++){
		for(int j = 0 ; j < sutunSayisi;j++){
			f.read((char*)&reader,sizeof(reader));
			Matrix<E>::data[i][j] = createPixelGray(reader);
		}
	}
}

template<class E>
void Image<E>::readFromBMP(ifstream &f,bool)
{	
	unsigned char info[54];
	f.read((char*)info,sizeof(info));
	int satirSayisi = (int)info[22];
	int sutunSayisi = (int)info[18];
	Matrix<E>::resize(satirSayisi,sutunSayisi);
	unsigned char reader[3];
	f.seekg((int)info[10],ios::beg);
	for(int i=0;i<satirSayisi;i++){
		for(int j = 0 ; j < sutunSayisi;j++){
			f.read((char*)&reader,sizeof(reader));
			rgb pixel = createPixelRGB(reader[0],reader[1],reader[2]);
			Matrix<E>::data[i][j] = convertBGR2RGB(pixel);

		}
	}
}

template<class E>
void Image<E>::imread(string filename,string format){
	ifstream f(filename.c_str(),ios::binary);
	if(!f.is_open())
		throw " dosya acilamadi. imread(filename,format)";
	string postFix = filename.substr(filename.rfind(".") + 1);
	if(format == "color"){
		type = RGB;
		if(postFix == "bin")
			readFromBin(f,true);
		else if(postFix == "bmp")
			readFromBMP(f,true);
		else
			throw "filename uzantisi hataliimread(filename,format) ";
	}
	else if(format == "gray"){
		type = GRAY;
		if(postFix == "bin")
			readFromBin(f);
		else if(postFix == "bmp")
			readFromBMP(f);
		else
			throw "filename uzantisi hatali . imread(filename,format) ";
	}
	else
		throw "format hatali . imread(filename,format) ";
	
}

template<class E>
void Image<E>::imwrite(string filename,string format){
	if(format == "color"){
		
	}else if("gray"){
		
	}
}

template<class E>
void Image<E>::color2gray(){
	if(getType() == RGB){
		int sutunSayisi = Matrix<E>::sutunUzun();
		int satirSayisi = Matrix<E>::satirUzun();
		for(int i = 0;i< satirSayisi;i++){
			for(int j=0;j<sutunSayisi;j++)
				Matrix<E>::data[i][j] = convertRGB2Gray(Matrix<E>::data[i][j]);
		}
		type = GRAY;
	}
}

template<class E>
void Image<E>::gray2binary(int threshold){
	if(getType() == GRAY){
		int sutunSayisi = Matrix<E>::sutunUzun();
		int satirSayisi = Matrix<E>::satirUzun();
		for(int i = 0;i< satirSayisi;i++){
			for(int j=0;j<sutunSayisi;j++)
				Matrix<E>::data[i][j] = convertGray2Binary(Matrix<E>::data[i][j],threshold);
		}
		type = BINARY;
	}
	
}

template<class E>
void Image<E>::erosion(const Image<E>& structElement){
	if(getType() == BINARY){
		if(structElement.getType() != BINARY)
			throw "structElementin tipi BINARY degil . erosion(structElement) ";
		if(!structElement.boyutKontrolOdd())
			throw "structElementin boyutlari tek sayi degil. erosion(structElement) ";
		int genislik = structElement.getGenislik();
		int yukseklik = structElement.getYukseklik();
		int sutunSayisi = getGenislik();
		int satirSayisi = getYukseklik();
		int merkezX = genislik / 2;
		int merkezY = yukseklik / 2;
		Image<E> result(sutunSayisi + 2 * merkezX,satirSayisi + 2 * merkezY);
		Image<E> tmp(genislik,yukseklik);
		result.set(*this,merkezY,merkezX);
		E structElementTotal = structElement.toplam();
		for(int i = 0 ; i < satirSayisi;i++){
			for(int j = 0; j < sutunSayisi;j++){
				tmp.kopya(result.get(i,yukseklik + i,j,genislik + j));
				if(!((structElement.emul(tmp)).toplam() == structElementTotal))
						Matrix<E>::data[i][j] = E(0,0,0);
			}
		}	
	}
}

template<class E>
void Image<E>::dilation(const Image<E>& structElement){
	if(getType() == BINARY){
		if(structElement.getType() != BINARY)
			throw " structElementin tipi BINARY degil.  dilation(structElement)";
		if(!structElement.boyutKontrolOdd())
			throw " structElementin boyutlari tek sayi degil. dilation(structElement)";
		int genislik = structElement.getGenislik();
		int yukseklik = structElement.getYukseklik();
		int sutunSayisi = getGenislik();
		int satirSayisi = getYukseklik();
		int merkezX = genislik / 2;
		int merkezY = yukseklik / 2;
		Image<E> result(sutunSayisi + 2 * merkezX,satirSayisi + 2 * merkezY);
		Image<E> tmp(genislik,yukseklik);
		result.set(*this,merkezY,merkezX);
		for(int i = 0 ; i < satirSayisi;i++){
			for(int j = 0; j < sutunSayisi;j++){
				tmp.kopya(result.get(i,yukseklik + i,j,genislik + j));
				if((structElement.emul(tmp)).toplam() > E(0))
					Matrix<E>::data[i][j] = E(0,1,0);
			}
		}
	}
}

template<class E>
void Image<E>::opening(const Image<E>& structElement){
	if(getType() == BINARY){
		if(structElement.getType() != BINARY)
			throw " structElementin tipi BINARY degil. opening(structElement)";
		if(!structElement.boyutKontrolOdd())
			throw " structElementin boyutlari tek sayi degil. erosion(structElement)";
		erosion(structElement);
		dilation(structElement);
	}
}

template<class E>
void Image<E>::closing(const Image<E>& structElement){
	if(getType() == BINARY){
		if(structElement.getType() != BINARY)
			throw "structElementin tipi BINARY degil.  opening(structElement) ";
		if(!structElement.boyutKontrolOdd())
			throw "structElementin boyutlari tek sayi degil. erosion(structElement) ";
		dilation(structElement);
		erosion(structElement);
	}
}


int main(){
	srand(time(0));
	
	try{
	/*
    // Matris kare değil.Bu nedenle birim matris yapamadı.
  	Matrix<int> (3,4,'e');
  */
  
   /*   
   //3'e 4'lük matrisi random doldurur.  
  	Matrix<int> m(3,4,'r');
    m.print();
   */
   


  /*  
  //gray.txt vebinary.txt dosyalarını oluşturur.
    Image<rgb> image1("image1.bin", "gray");
    image1.print("gray.txt", true);
    image1.gray2binary(100);
    image1.print("binary.txt",true);
    Image<rgb> cekirdek(3,3,1,BINARY);
  */
  /*
   //3lerle dolu 5'e 3lük matrisle 2lerle dolu 3'e 6lık matrisin çarpımı verir.
	  Matrix<int> m(5,3,3);
	  m.print();
    
	  Matrix<int> m2(3,6,2);
	  m2.print();
    
	  Matrix<int> m3 = m * m2;
	  m3.print();
  */
 
  
  /*
  //Table sınıfında satır ve sütünları isimlendirir.
    Table<int> table(5,2,'r');
    table.print();
  */
  
  
  /*
    Matrix<int> m1(3,3);
	  m1.print();
	  cout << endl;
	  Matrix<int> m2(3,3,'e');
		m2.print();
		cout << endl;
		m1 = Matrix<int>(3,3,'r');
		m1.print();
		cout << endl;
		Matrix<int> m3;
		m3 = m1 + m2;
		m3.print();
		cout << endl;
		m3 = m1 - m2;
		m3.print();
		cout << endl;
		m3 = m1 + 2;
		m3.print();
		cout << endl;
		m3 = m1 * m2;
		m2.print();
		cout << endl;
		m3 = m1 + 2;
		m3.print();
		cout << endl;
		m3 = m1 - 3;
		m3.print();
		cout << endl;
		m3 = m1 * 4;
		m3.print();
		cout << endl;
		m3 = m1 / 2;
		m3.print();
		cout << endl;
		m3 = m1 % 2;
		m3.print();
		cout << endl;
		m3 = m1 ^ 2;
		m3.print();
		cout << endl;
		cout << m1.det() << endl;
		m1.inv().print();
  */
  /*
  //table sınıfı ile satır ve sütun isimlerini yeniden adlandırır.
    Table<int> t1;
		t1.print();
		cout << endl;
		Table<int> t2(2,3,10);
		t2.print();
		cout << endl;
		Table<int> t3(5,5,'r');
		t3.print();
		cout << endl;
		cout << t3.itemAt(3,4) << endl;
		cout << t3.itemAt("D4") << endl;
		cout << t3.itemAt("4","D") << endl;
		string satirAdi[] = {"1.satir","2.satir","3.satir","4.satir","5.satir"};
		// bilerek 3. satiri atladim;
		string sutunAdi[] = {"S1","S2","S3","S4","S5"};
		
		t3.setsatirAdi(satirAdi,5);
		t3.setsutunAdi(sutunAdi,5);
		t3.print();
	*/
  /*Matrix<int>		*m2 = new Matrix<int>(5, 5, 'r');
   m2->print();
   cout<<endl;
   Matrix<int>		*m3 = new Matrix<int>(5, 5, 'r');
   m3->print();

   Matrix<int>   m4= (*m3)*(*m2);
   m4.print();
   
*/
/*
//resize örneği	
  Matrix<int>	*m = new Matrix<int>(6, 6, 'e');
  m->print() ;
  cout<<endl;
  m->resize(9, 5);
  m->print();
*/
/*
//matrix operasyon
Matrix<int>		*m1 = new Matrix<int>(5, 5, 0);
m1->print();
Matrix<int>	*m2 = new Matrix<int>(4, 4, 'r');
m2->print();
Matrix<int>	*m3 = new Matrix<int>(4, 4, 2);
m3->print();
*m1 = *m2 + *m3;	
m1->print();
*/
/*
//verilen matrisin transpozesini alır.
Matrix<int> m(3,3,'r');
		m.print();
    cout<<endl;
    (m.T()).print();
    
*/  
/*
//matrisin determinantı
Matrix<int> m(3,3,'r');
m.print();
cout<<endl;
cout<<m.det();
*/





  }
	catch(const char* exception){
		cout << exception;
	}
	

	return 0;
}


