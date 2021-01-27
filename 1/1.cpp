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
	cout << "Select the operating mode: 1 Interactive mode, 2 Demonstration mode, 3 Benchmark mode,9 EXIT: "<<endl;
	cin >> mode;
	while (mode!=9){
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
			for (i=ind;i<ind+numb;i++){
				cin >> out[i].id >> out[i].name >>out[i].uom >> out[i].num >> out[i].data.hour
				>> out[i].data.min >> out[i].data.day >> out[i].data.month>>
				out[i].data.year>> out[i].term;
 			/*	words[i]=out[i].id +" "+ out[i].name +" "+ out[i].uom+" "+to_string(out[i].num) +" "+to_string(out[i].data.hour)
				+" "+ to_string(out[i].data.min) +" "+to_string(out[i].data.day) +" "+ to_string(out[i].data.month)+" "+
				to_string(out[i].data.year)+" "+ to_string(out[i].term) ; */} 
				}
				
		if (interactive==2){
		fout_bin=fopen("products_bin.dat", "a"/*, "ab+"*/);
		ofstream fout("products.txt"/*, ios_base::app*/); 
		fout << endl;
			for (i=0;i<numb+ind;i++){
				words[i]=out[i].id +" "+ out[i].name +" "+ out[i].uom+" "+to_string(out[i].num) +" "+to_string(out[i].data.hour)
				+" "+ to_string(out[i].data.min) +" "+to_string(out[i].data.day) +" "+ to_string(out[i].data.month)+" "+
				to_string(out[i].data.year)+" "+ to_string(out[i].term) ; 
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
			int hour,minutes,day,month,year;
			bool flag=false;
			int len=str_name.length(), min, max;
			cout << "Write the min number: "<<endl;
			cin >> min;
			cout << "Write the max number: "<<endl;
			cin >> max;
			cout <<"Write units of measurement: "<<endl;
			cin >> str_uom;
			cout << "Produced no later than :"<<endl;
			cin >> hour >> minutes >> day >> month >> year;
			
				for (i=0;i<ind;i++){
					if ( out[i].name.length()>=len)
					new_name=out[i].name.erase(len,out[i].name.length()-len);
					
					if (out[i].data.year>year || (out[i].data.year>=year
					&& out[i].data.month>month) || ( out[i].data.year>=year
					&& out[i].data.month>=month && out[i].data.day>day) ||
					( out[i].data.year>=year && out[i].data.month>=month && out[i].data.day>=day
					&& out[i].data.hour>hour)|| ( out[i].data.year>=year && out[i].data.month>=month 
					&& out[i].data.day>=day	&& out[i].data.hour>=hour && out[i].data.min>minutes )) flag=true;
					//cout << new_name << endl;
					if (new_name==str_name && out[i].num>min && out[i].num<max 
					&& out[i].uom == str_uom && flag) cout << line [i] << endl;
				}	
				
				
		   }
		   
		   if (interactive==6) {
		   	// Everything was fine until I started writing modifications...
		   	string name, categ, value;
		   	int spec=-1;
		   	cout <<"Write product name and which category you want to change "<<
			   "(id,name,uom,number,hour,min,day,month,year,term) and new value: "<<endl;
		   	cin >> name >> categ >> value;
		   	for (i=0;i<ind;i++){
		   		 if (out[i].name==name) spec=i; 
			   } if (spec!=-1){
			   if (categ=="id") out[spec].id=value; else
			   if (categ=="name") out[spec].name=value; else
			   if (categ=="uom") out[spec].uom=value; else {
			   	int trash =atoi(value.c_str());
			   	   if (categ=="hour") out[spec].data.hour=trash; else
			  		 if (categ=="min") out[spec].data.min=trash; else
			  		 if (categ=="day") out[spec].data.day=trash; else
			  		 if (categ=="month") out[spec].data.month=trash; else
			  	  	 if (categ=="year") out[spec].data.year=trash; else
			  		 if (categ=="term") out[spec].term=trash;}} 
					   else cout <<"ERROR NAME"<<endl;
					   
		   }
		   
		   } }
	
	
}
return 0;     
}
