#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h> 
#include <vector>
#include <cstring>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <set>
using namespace std;
struct production{
	int hour;
	int min;
	int day;
	int month;
	int year;
	
};
struct product {
	string id;
	string name;
	string uom; //units of measurement
	int num ;
	production data;
	int term;
	
};
string to_string(int n)
{
    char buf[40];
    sprintf(buf,"%d",n);
    return buf;
};
int main()
{   product f;
	FILE *fout_bin;
	fout_bin=fopen("products_bin.dat", "ab+");
	ofstream fout("products.txt", ios_base::app); 

cin >> f.id >> f.name >> f.uom >> f.num >> f.data.hour
>> f.data.min >> f.data.day >> f.data.month>>
f.data.year>> f.term;
string words;
 words=f.id +" "+ f.name +" "+ f.uom+" "+to_string(f.num) +" "+to_string(f.data.hour)
+":"+ to_string(f.data.min) +" "+to_string(f.data.day) +"."+ to_string(f.data.month)+"."+
to_string(f.data.year)+" "+ to_string(f.term) ; 

fout << words << endl;
 int i;
 for (i=0;i<words.length();i++) fwrite((char*)&words[i],sizeof(char),1, fout_bin);
fout.close();
fclose(fout_bin);
return 0;     
}
