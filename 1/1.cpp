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
{   product f[100],out[100];
	int mode, interactive=0,numb,i,j,k,ind=0;
	FILE *fout_bin;
	string words[100],line[100],str_name,str_uom,new_name;
	//char new_name[100];
	cout << "Select the operating mode: 1 Interactive mode, 2 Demonstration mode, 3 Benchmark mode: "<<endl;
	cin >> mode;
	if (mode==1){
		cout << "Select the operating mode: 1 Adding item, "<<
		"2 Data storage, 3 Data recovery, 4 Output of all saved data, "<<
		"5 Search by particle of name, "<<
		"6 Modification of elements, 7 Delete items, 9 Exit" << endl;
		while (interactive!=9){
		cin >> interactive;
		
		if (interactive==1) {
			cout << "Write number of items: ";
			cin >> numb;
			for (i=0;i<numb;i++){
				cin >> f[i].id >> f[i].name >> f[i].uom >> f[i].num >> f[i].data.hour
				>> f[i].data.min >> f[i].data.day >> f[i].data.month>>
				f[i].data.year>> f[i].term;
 				words[i]=f[i].id +" "+ f[i].name +" "+ f[i].uom+" "+to_string(f[i].num) +" "+to_string(f[i].data.hour)
				+" "+ to_string(f[i].data.min) +" "+to_string(f[i].data.day) +" "+ to_string(f[i].data.month)+" "+
				to_string(f[i].data.year)+" "+ to_string(f[i].term) ; } 
				}
				
		if (interactive==2){
		fout_bin=fopen("products_bin.dat", "ab+");
		ofstream fout("products.txt", ios_base::app); 
		fout << endl;
			for (i=0;i<numb;i++){
				fout << words[i] << endl;
				//fwrite("\n",sizeof(char),1, fout_bin);	
					for (j=0;j<words[i].length();j++) 					
						fwrite((char*)&words[i][j],sizeof(char),1, fout_bin);
						fwrite("\n",sizeof(char),1, fout_bin);	
			} 
			fout.close();
			fclose(fout_bin);
		}
		
		if (interactive==3){
		ifstream file("products.txt"); 
		/*int n=100;
		char *buffer=new char[n+1];
		buffer[n]=0;*/ 
			while (!file.eof()){
				file >> out[ind].id >> out[ind].name >> out[ind].uom >>out[ind].num >> out[ind].data.hour
				>> out[ind].data.min >> out[ind].data.day >>out[ind].data.month>>
				out[ind].data.year>> out[ind].term;
			//	file.getline(buffer,n);
			 //  if (out[ind].term<=3650)
				line[ind]=out[ind].id+" "+out[ind].name+" "+out[ind].uom+
				" "+to_string(out[ind].num)+" "+ to_string(out[ind].data.hour)
				+" "+to_string(out[ind].data.min)+" "+ to_string(out[ind].data.day)+" "+
				to_string(out[ind].data.month)+" "+to_string(out[ind].data.year)+" "+
				to_string(out[ind].term);
				ind++;
			} file.close();	
		}
		
		if (interactive==4){
			for(i=0;i<ind;i++){
				if (out[i].term<=3650 && out[i].term>0)
				cout << line[i]<<endl;
			}
		}
		
		if (interactive==5){
			cout << "Write the beginning of the product: "<<endl;
			cin >> str_name;
			int len=str_name.length(), min, max;
			cout << "Write the min number: "<<endl;
			cin >> min;
			cout << "Write the max number: "<<endl;
			cin >> max;
			cout <<"Write units of measurement: "<<endl;
			cin >> str_uom;
			
				for (i=0;i<ind;i++){
					if ( out[i].name.length()>=len)
					new_name=out[i].name.erase(len,out[i].name.length()-len);
					//cout << new_name << endl;
					if (new_name==str_name && out[i].num>min && out[i].num<max 
					&& out[i].uom == str_uom) cout << line [i] << endl;
				}	
		   }	
		   } }
	
	

return 0;     
}
