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
#include <stdlib.h>
#include <ctime>
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
    char buf[15];
    sprintf(buf,"%d",n);
    return buf;
};
func(int gen){
		FILE *fout_bin;
		int i,j;
		string* words=new string[100000];
		product* f=new product[100000];
		string name[200]={"bacon","beef","chicken","cooked_meat","duck","ham","kidneys",
	"lamb","liver","mince","pate","salami","sausages","pork","pork_pie","turkey_veal",
	"apple","apricot","banana","blackberry","blackcurrant","blueberry","cherry",
	"coconut","fig","gooseberry","grape","grapefruit","kiwi","lemon","lime","mango",
	"melon","orange","peach","pear","pineapple","plum","pomegranate","raspberry",
	"redcurrant","rhubarb","strawberry","bananas","anchovy","cod","haddock",
	"herring","kipper","mackerel","pilchard","plaice","salmon","sardine",
	"sole","trout","tuna","artichoke","asparagus","ubergine","avocado",
	"beansprouts","beetroot","broccoli","cabbage","carrot","cauliflower","celery"}, units[4]={"kilo", "litr", "pieces"};
		fout_bin=fopen("products_bin.dat", "ab+");
	     	ofstream fout("products.txt"); 
	     	//random value 
		for (i=0;i<gen;i++){
			f[i].id="id"+to_string(rand() % 1000)+to_string(rand() % 1000);
			f[i].name=name[rand()%60];
			f[i].uom=units[rand()%3];
			f[i].num=rand()%100+10;
			f[i].data.hour=rand()%24;
			f[i].data.min=rand()%60;
			f[i].data.day=rand()&28+1;
			f[i].data.month=rand()%13+1;
			f[i].data.year= (rand()%10) + 2011;
			f[i].term=(rand()%3451) + 200; 
			
			words[i]=f[i].id +" "+ f[i].name +" "+ f[i].uom+" "+to_string(f[i].num) +" "+to_string(f[i].data.hour)
				+" "+ to_string(f[i].data.min) +" "+to_string(f[i].data.day) +" "+ to_string(f[i].data.month)+" "+
				to_string(f[i].data.year)+" "+ to_string(f[i].term) ; 
				if (i!=gen-1)	fout << words[i] << endl; 
					else fout << words[i];
						
				//fwrite("\n",sizeof(char),1, fout_bin);	
					for (j=0;j<words[i].length();j++) 					
						fwrite((char*)&words[i][j],sizeof(char),1, fout_bin);
						fwrite("\n",sizeof(char),1, fout_bin);	
			} 
			fout.close();
			fclose(fout_bin);
			delete [] words, f;
}
int main()
{   product* f= new product[100000];
	product* out= new product[100000];
	int mode=1, interactive=0,numb,i,j,k,ind=0,gen=10;
	FILE *fout_bin;
	string * words=new string[100000],*line=new string[100000],*my_line=new string[100000];
	string str_name,str_uom,new_name;

	long long memory;
		func(gen);
	
		
	//char new_name[100];
	cout << "Select the operating mode: 1 Interactive mode, 2 Demonstration mode, 3 Benchmark mode,9 EXIT: "<<endl;
	while (mode!=9){
		cin >> mode;
		// interactive
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
				cin >> f[i].id >> f[i].name >>f[i].uom >> f[i].num >> f[i].data.hour
				>> f[i].data.min >> f[i].data.day >> f[i].data.month>>
				f[i].data.year>> f[i].term;
 			/*	words[i]=out[i].id +" "+ out[i].name +" "+ out[i].uom+" "+to_string(out[i].num) +" "+to_string(out[i].data.hour)
				+" "+ to_string(out[i].data.min) +" "+to_string(out[i].data.day) +" "+ to_string(out[i].data.month)+" "+
				to_string(out[i].data.year)+" "+ to_string(out[i].term) ; */} 
				}
				
		if (interactive==2){
		fout_bin=fopen("products_bin.dat", "ab+");
		ofstream fout("products.txt", ios_base::app); 
		fout << endl;
			for (i=0;i<numb;i++){
			words[i]=f[i].id +" "+ f[i].name +" "+ f[i].uom+" "+to_string(f[i].num) +" "+to_string(f[i].data.hour)
				+" "+ to_string(f[i].data.min) +" "+to_string(f[i].data.day) +" "+ to_string(f[i].data.month)+" "+
				to_string(f[i].data.year)+" "+ to_string(f[i].term) ; 
					if (i!=numb-1) 	fout << words[i] << endl;
						else fout << words[i];
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
		ind=0;
		/*int n=100;
		char *buffer=new char[n+1];
		buffer[n]=0;*/ 
			while (!file.eof()){
				file >> out[ind].id >> out[ind].name >> out[ind].uom >>out[ind].num >> out[ind].data.hour
				>> out[ind].data.min >> out[ind].data.day >>out[ind].data.month>>
				out[ind].data.year>> out[ind].term;
			//	file.getline(buffer,n);
			  
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
					&& out[i].uom == str_uom && flag==true) {cout << line [i] << endl;
				 		flag=false;}
				}	
				
				
		   }
		   
		   /*if (interactive==6) {
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
					   
		   }*/
		   
		   } } else 
		   
		   //mode 2
		   // demo
		   
		   if (mode==2) {
		    cout << "Select the operating mode: 1 Adding item, "<<
			"2 Data storage, 3 Data recovery, 4 Output of all saved data, "<<
			"5 Search by particle of name, "<<
			"6 Modification of elements, 7 Delete items, 9 Exit" << endl;
			cout << 1 <<endl;
			cout << "Write number of items: 1" <<endl;
			cout << "id213123 Carrot kilo 124 23 55 11 12 2020 65 "<<endl;
			f[0]={"id213123","Carrot","kilo", 124, 23,55,11,12,2020,65}; // for c++ 11 and new	
			cout << 2 << endl;		
			fout_bin=fopen("products_bin.dat", "ab+");
			ofstream fout("products.txt", ios_base::app); 
			fout << endl;
			i=0;
			words[i]=f[i].id +" "+ f[i].name +" "+ f[i].uom+" "+to_string(f[i].num) +" "+to_string(f[i].data.hour)
				+" "+ to_string(f[i].data.min) +" "+to_string(f[i].data.day) +" "+ to_string(f[i].data.month)+" "+
				to_string(f[i].data.year)+" "+ to_string(f[i].term) ; 
					fout << words[i];
		
					for (j=0;j<words[i].length();j++) 					
						fwrite((char*)&words[i][j],sizeof(char),1, fout_bin);
						fwrite("\n",sizeof(char),1, fout_bin);	
			
			fout.close();
			fclose(fout_bin);
		
		
		 cout << "3"<<endl;
		ifstream file("products.txt"); 
		ind=0;
		
			while (!file.eof()){
				file >> out[ind].id >> out[ind].name >> out[ind].uom >>out[ind].num >> out[ind].data.hour
				>> out[ind].data.min >> out[ind].data.day >>out[ind].data.month>>
				out[ind].data.year>> out[ind].term;
						  
				line[ind]=out[ind].id+" "+out[ind].name+" "+out[ind].uom+
				" "+to_string(out[ind].num)+" "+ to_string(out[ind].data.hour)
				+" "+to_string(out[ind].data.min)+" "+ to_string(out[ind].data.day)+" "+
				to_string(out[ind].data.month)+" "+to_string(out[ind].data.year)+" "+
				to_string(out[ind].term);
				ind++;
			} file.close();	
		
		
		cout << "4" << endl;
			for(i=0;i<ind;i++){
				cout << line[i]<<endl;
			} 
	
		
		cout << "5" << endl;
		
			cout << "Write the beginning of the product: "<<endl;
			cout << "Ca" <<endl;
			int hour,minutes,day,month,year;
			bool flag=false;
			int len=str_name.length(), min, max;
			cout << "Write the min number: "<<endl;
			cout << "10" << endl;
			cout << "Write the max number: "<<endl;
			cout << "200" <<endl;
			cout <<"Write units of measurement: "<<endl;
			cout << "kilo"<<endl;
			cout << "Produced no later than :"<<endl;
			cout << "10 10 10 12 2020" <<endl;
			int ind_t;
			string str_name="Ca",str_uom="kilo";
			int hours=10,minutess=10,days=10,months=12,years=2020;
			bool flags=false;
			int mins=10, maxs=200;
		
				for (i=0;i<ind;i++){
					if ( out[i].name.length()>=2) {
					new_name=out[i].name.erase(2,out[i].name.length()-2);
					
					if (out[i].data.year>years || (out[i].data.year>=years
					&& out[i].data.month>months) || ( out[i].data.year>=years
					&& out[i].data.month>=months && out[i].data.day>days) ||
					( out[i].data.year>=years && out[i].data.month>=months && out[i].data.day>=days
					&& out[i].data.hour>hours)|| ( out[i].data.year>=years && out[i].data.month>=months 
					&& out[i].data.day>=days	&& out[i].data.hour>=hours && out[i].data.min>minutess )) flags=true;
					//cout << new_name << endl;
					if (new_name==str_name && out[i].num>mins && out[i].num<maxs 
					&& out[i].uom == str_uom && flags==true) {
					cout << line[i] <<endl;
					my_line[ind_t]=line[i];
					ind_t++;
				 		flags=false;}
				}}	
				cout << "9" <<endl;
				
		   } else
		   // mode 3 
		   // benchmark
		   if (mode==3){ 
		   	unsigned long search_time=0, start_time, end_time,sum_time=0;
		   	memory=0;
		   cout << "Write your number: ";
		   cin >> gen;
		   int key;
		  // for (key=1;key<100;key++){
		   	memory=0;
		   while (sum_time<1000){
		   	start_time =  clock();
		   	// generation
		   	func(gen);
		   	ifstream file("products.txt"); 
		    ind=0;
		    // Data recovery
			while (!file.eof()){
				file >> out[ind].id >> out[ind].name >> out[ind].uom >>out[ind].num >> out[ind].data.hour
				>> out[ind].data.min >> out[ind].data.day >>out[ind].data.month>>
				out[ind].data.year>> out[ind].term;
					  
				line[ind]=out[ind].id+" "+out[ind].name+" "+out[ind].uom+
				" "+to_string(out[ind].num)+" "+ to_string(out[ind].data.hour)
				+" "+to_string(out[ind].data.min)+" "+ to_string(out[ind].data.day)+" "+
				to_string(out[ind].data.month)+" "+to_string(out[ind].data.year)+" "+
				to_string(out[ind].term);
				
				ind++;
				memory+=sizeof(line[i])+sizeof(ind);
			} file.close();	
			
			// Search item
			
			int ind_t;
			string str_name="Ca",str_uom="kilo";
			int hours=10,minutess=10,days=10,months=12,years=2020;
			bool flags=false;
			int mins=10, maxs=200;
		
				for (i=0;i<ind;i++){
					if ( out[i].name.length()>=2) {
					new_name=out[i].name.erase(2,out[i].name.length()-2);
					
					if (out[i].data.year>years || (out[i].data.year>=years
					&& out[i].data.month>months) || ( out[i].data.year>=years
					&& out[i].data.month>=months && out[i].data.day>days) ||
					( out[i].data.year>=years && out[i].data.month>=months && out[i].data.day>=days
					&& out[i].data.hour>hours)|| ( out[i].data.year>=years && out[i].data.month>=months 
					&& out[i].data.day>=days	&& out[i].data.hour>=hours && out[i].data.min>minutess )) flags=true;
					if (new_name==str_name && out[i].num>mins && out[i].num<maxs 
					&& out[i].uom == str_uom && flags==true) {
					my_line[ind_t]=line[i];
					ind_t++;
				 		flags=false;}
				}}
				
		   	end_time = clock();
		   	search_time = end_time - start_time;
		   	sum_time+=search_time;
		   	//cout << search_time <<endl;
		   	gen=gen*2; 
		   }
		   int current_gen=gen;
		   // second part ariph prog
		   
		   while (sum_time<10000){
		   	
		   	start_time =  clock();
		   	current_gen+=gen;
		   	// generation
		   	func(current_gen);
		   	ifstream file("products.txt"); 
		    ind=0;
		    // Data recovery
			while (!file.eof()){
				file >> out[ind].id >> out[ind].name >> out[ind].uom >>out[ind].num >> out[ind].data.hour
				>> out[ind].data.min >> out[ind].data.day >>out[ind].data.month>>
				out[ind].data.year>> out[ind].term;
				
				line[ind]=out[ind].id+" "+out[ind].name+" "+out[ind].uom+
				" "+to_string(out[ind].num)+" "+ to_string(out[ind].data.hour)
				+" "+to_string(out[ind].data.min)+" "+ to_string(out[ind].data.day)+" "+
				to_string(out[ind].data.month)+" "+to_string(out[ind].data.year)+" "+
				to_string(out[ind].term);
				
				ind++;
				memory+=sizeof(line[i])+sizeof(ind);
			} file.close();	
			
			// Search item
			
			int ind_t;
			string str_name="Ca",str_uom="kilo";
			int hours=10,minutess=10,days=10,months=12,years=2020;
			bool flags=false;
			int mins=10, maxs=200;
		
				for (i=0;i<ind;i++){
					if ( out[i].name.length()>=2) {
					new_name=out[i].name.erase(2,out[i].name.length()-2);
					
					if (out[i].data.year>years || (out[i].data.year>=years
					&& out[i].data.month>months) || ( out[i].data.year>=years
					&& out[i].data.month>=months && out[i].data.day>days) ||
					( out[i].data.year>=years && out[i].data.month>=months && out[i].data.day>=days
					&& out[i].data.hour>hours)|| ( out[i].data.year>=years && out[i].data.month>=months 
					&& out[i].data.day>=days	&& out[i].data.hour>=hours && out[i].data.min>minutess )) flags=true;
					if (new_name==str_name && out[i].num>mins && out[i].num<maxs 
					&& out[i].uom == str_uom && flags==true) {
					my_line[ind_t]=line[i];
					ind_t++;
				 		flags=false;}
				}}
				
		   	end_time = clock();
		   	search_time = end_time - start_time;
		   	sum_time+=search_time;
		   	//cout << search_time <<endl;
		   	
			}
			
		   //cout << key << endl;
		   /*ofstream fout("result.txt", ios_base::app);
		   fout <<"N: "<< key << endl;
		   fout <<"Sum_time: "<<sum_time<<"ms" <<endl;
		   fout <<"Memory: "<<memory <<endl;
		   fout <<"Current number of generation: "<<current_gen <<endl;
		   fout <<endl;
		   fout.close();*/
		   
		    
		   } 
		   }
		   	
		   	
		   
	delete[] words,line,my_line,f,out;
	
	
	

return 0;     
}
