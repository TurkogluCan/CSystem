#include "stdio.h"


int main(void)
{

	return 0;
}





/****************************************************** Others
 * KOD CALSTIRMA ORNEGI:
 * gcc -o sample sample.c
 * ./sample
 *
*/

/************************************************ CODE PARTICLES
 *
 * typedef int I demek, I değişken ismini, o değişkenin türüne ilişkin tür ismi haline getiriyor. Complier için artık I ile int aynı anlamdadır.
 * typedef sadece legal bir bildirime getirilebilir. Her türlü legal bildirimin önüne getirilebilir. 
 * typedef bildirimi de scope'a özgüdür. Yani nerede tanımlarsan o bloktan erişilebilir. Fakat genellikle typedef bildirimleri global olarak tanımlanır.
 * 
 *
 * typedef int I ile  int typedef I aynı şeydir. Bildirim içinde yer değiştirebilir.
 * const int x = 10   ile  int const x = 10 aynı şeydir.
 *
 * typedef int *PI; ise
 * PI a;  <=> int *a;
 *
 *
 * typedef int ARY[10];
 * ARY a,b;  <=>  int a[10], b[10];
 * 
 * 
 * typedef char *STR[3];
 * STR  names = {"ali", "veli", "selami"};
 * 
 * 
 * struct Sample 
 * {
 *   int a;
 *   int b;
 *   int c;
 * };
 * 
 * C ve C++'da her yapı bildirimi yeni bir tür oluşturmaktadır. Oluşturulan türün ismi struct ve ismi ile birlikte ifade edilir. Yukarıda oluşturulan 
 * türün ismi "struct Sample"dır. Nasıl int a deniyorsa, burada da "struct Sample" denir. Yani C'ye göre değişken türü nasıl int ise, burada da struct Sample'dır,
 * sadece Sample değildir.
 * 
 * struct Sample a;   ile   int b; bildirimi benzerdir.
 * 
 * 
 * typedef ile kullanılacak olunursa;
 * 
 * typedef struct Sample SMP;
 * SMP S;   <=>   struct Sample S;
 * 
 * 
 * C'de eğer bir yapı bildirmişsen, bu yapı türünden değişken de tanımlanabilir. SMP strcut Sample türünden bir değişkendir. 
 * 
 * struct Sample 
 * {
 *   int a;
 *   int b;
 *   int c;
 * }SMP;
 * 
 * C standartlarında bildirimler   <tür> <değişken ismi> olarak yapılır. Buradaki bildirim de benzerdir.
 * 
 * Burada 
   struct Sample 
 * {
 *   int a;
 *   int b;
 *   int c;
 * }						TÜR
 * 
 * SMP						DEĞİŞKEN İSMİ'dir.
 * 
 * O zaman ben buraya typedef getirirsem 
 * typedef <tür><değişken ismi>
 * 
 * typedef struct Sample 
 * {
 *   int a;
 *   int b;
 *   int c;
 * }SMP;
 * Bu durumda typedef kullanılarak, SMP artık burada "struct Sample"ı temsil etmiş olur.   
 * SMP xxx;  <=>  struct Sample xxx;
 * --------------
 * C standartlarına göre isimsiz bir yapı bildirilebilir ama değişken tanımlanması gerekir.
 * struct 
 * {
 *   int a;
 *   int b;
 *   int c;
 * }SMP;
 * 
 * Bu bildirim typedef kullanılarak aşağıdaki gibi de yapılabilir.
 * typedef struct 
 * {
 *   int a;
 *   int b;
 *   int c;
 * }SMP;
 * --------------
 * typedef struct Sample
 * {
 *   int a;
 *   int b;
 *   int c;
 * }X, *PX;     ise
 * 
 * PX s;   <=>   struct Sample *s;
 * --------------
 * 
 * 
 * --------------
 * const int *pint;
 * Burada pint'in gösterdiği yer consttur.
 * 
 * int * const pint;
 * Burada ise pint consttur.
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 
 
 * int *p, a;
 * Tanımlamasında p, int * türünden, a ise int türünden bir değişkendir. Eğer ifade
 * int* p, a;
 * olarak değiştirilirse, yine aynı şekilde kalır. Derleyici için hiçbir fark yoktur. Yine p, int * türünden, a ise int türünden bir değişkendir.
 ******************************************************************************************************************************************************


******************************************************************************************************************************************************
*/