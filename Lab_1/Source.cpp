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
//#include <filesystem>
//#include <sqlite3.c>

 //database include
 #include "sqlite3.h"
//for sqlite
/*const char* SQL = "CREATE TABLE IF NOT EXISTS foo(a char(100)); INSERT INTO FOO VALUES(\"id-1 Carrot kilo 123 12 12 13 1 2020 52\");";
string sql_str;*/



struct production {
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
	int num;
	production data;
	int term;
};
//main sqlite function
/*void database(const char*& SQL) {

	sqlite3* db = 0; // handle
	char* err = 0;

	//open
	if (sqlite3_open("test.db", &db))
		fprintf(stderr, "Can not open \ write to DB: %s\n", sqlite3_errmsg(db));
	//start write
	else if (sqlite3_exec(db, SQL, 0, 0, &err))
	{
		fprintf(stderr, "ERROR SQL: %sn", err);
		sqlite3_free(err);
	}
	//close
	sqlite3_close(db);

}*/
// to_string work in VS studio, but doesnt work in dev-cpp
string to_string(int n)
{
	char buf[15];
	sprintf(buf, "%d", n);
	return buf;
}

//for reading from bin file
/*vector<product> a[200000];

void initfromfile(vector<product> a)
{
    ifstream infile("products_bin.dat", ios::binary | ios::in);
    if (infile.is_open())
    {
        product *x = new product; //read from binary
        while (infile.read((char*)(x), sizeof(product)))
        {
            //add to vector
            a.push_back(*x);
        }
    }
    else cout << "Problem with Binary File ";
    infile.close();
}*/
// get_file_size
/*int get_file_size(string filename) // path to file
{
	FILE *p_file = NULL;
	p_file = fopen(filename.c_str(),"rb");
	fseek(p_file,0,SEEK_END);
	int size = ftell(p_file);
	fclose(p_file);
	return size;
}*/
//fileSize
int fileSize(const char* add) {
	ifstream mySource;
	mySource.open(add);
	mySource.seekg(0, ios_base::end);
	int size = mySource.tellg();
	mySource.close();
	return size;
}
//BinFileSize
int fileSize_bin(const char* add) {
	ifstream mySource;
	mySource.open(add, ios_base::binary);
	mySource.seekg(0, ios_base::end);
	int size = mySource.tellg();
	mySource.close();
	return size;
}
//generation
void func(int gen,int mode, unsigned int &time_bin,unsigned int  &time_str,int &data_id,int &memory,int k) {
	FILE* fout_bin;
	int i, j;
	string* words = new string[gen+1];
	product* f = new product[gen+1];
	ofstream fout;
	string name[100] = { "bacon","beef","chicken","cooked_meat","duck","ham","kidneys",
"lamb","liver","mince","pate","salami","sausages","pork","pork_pie","turkey_veal",
"apple","apricot","banana","blackberry","blackcurrant","blueberry","cherry",
"coconut","fig","gooseberry","grape","grapefruit","kiwi","lemon","lime","mango",
"melon","orange","peach","pear","pineapple","plum","pomegranate","raspberry",
"redcurrant","rhubarb","strawberry","bananas","anchovy","cod","haddock",
"herring","kipper","mackerel","pilchard","plaice","salmon","sardine",
"sole","trout","tuna","artichoke","asparagus","ubergine","avocado",
"beansprouts","beetroot","broccoli","cabbage","carrot","cauliflower","celery" }, units[4] = { "kilo", "litr", "pieces" };
unsigned int time_bin_start=0, time_bin_end=0, time_str_end=0,  time_str_start=0;
	if (mode==1){
	fout_bin = fopen("products_bin.dat", "wa+");
	fout.open("products.txt");
	data_id=0;
	}
	else if(mode==2){
	fout_bin = fopen("products_bin.dat", "ab+");
	fout.open("products.txt",  ios_base::app);
	}
	//random value 
	for (i = 0;i < gen;i++) {
		f[i].id = "id" + to_string(data_id);
		data_id++;
		f[i].name = name[rand() % 60];
		f[i].uom = units[rand() % 3];
		f[i].num = rand() % 100 + 10;
		f[i].data.hour = rand() % 24;
		f[i].data.min = rand() % 60;
		f[i].data.day = (rand() % 28) + 1;
		f[i].data.month = rand() % 12 + 1;
		f[i].data.year = (rand() % 10) + 2011;
		f[i].term = (rand() % 3451) + 200;
	
		words[i] = f[i].id + " " + f[i].name + " " + f[i].uom + " " + to_string(f[i].num) + " " + to_string(f[i].data.hour)
			+ " " + to_string(f[i].data.min) + " " + to_string(f[i].data.day) + " " + to_string(f[i].data.month) + " " +
			to_string(f[i].data.year) + " " + to_string(f[i].term);
		//cout << sizeof(f[i]) << endl;
		memory+=words[i].size();	
		time_str_start=clock();
		// ofstream
		if (mode==1 && k==1){
			if (i==gen) fout << words[i];
			else fout << words[i] << endl;
		} else if (mode==1 && k==0){
			fout << words[i] << endl;
		} else
		fout << words[i] << endl;
		
		time_str_end=clock();
		time_str+=time_str_end-time_str_start;
		
		/*if (gen == 1) fout << words[i] << endl; else
			if (i != gen - 1)	fout << words[i] << endl;
			else fout << words[i];*/
		//binary
		time_bin_start=clock();
		if (i!=0){
		fwrite("\n",sizeof(char),1, fout_bin);
		for (j = 0;j < words[i].length();j++)
			fwrite(/*(char*)*/&words[i][j], sizeof(char), 1, fout_bin);}
			else {
				for (j = 0;j < words[i].length();j++)
				fwrite(/*(char*)*/&words[i][j], sizeof(char), 1, fout_bin);
		}
		time_bin_end=clock();
		time_bin+=time_bin_end-time_bin_start;
		//fwrite("\n", sizeof(char), 1, fout_bin);

		//sql
		/*sql_str = " CREATE TABLE IF NOT EXISTS foo(a char(100)); INSERT INTO FOO VALUES(\" ";
		sql_str += words[i];
		sql_str += "\");";
		const char* SQL = sql_str.c_str();
		database(SQL);*/
	}
	/*if (data_id>200000) {
		cout << "Work up to 200k lines, u can change"<<endl;
		exit(-1);
	}*/
	fout.close();
	fclose(fout_bin);
	delete[] words, f;
}

//adding for interactive
void add_items(int numb,string* words){
	int i=0;
		if (numb>199990){
					cout << "In main up to 200k products, u can change "<<endl;
				} else 
		if (numb<=0) cout <<"Incorrect number"<<endl; 
				else
				{
				product* f = new product[numb+1];
				for (i = 0;i < numb;i++) {
					cin >> f[i].id >> f[i].name >> f[i].uom >> f[i].num >> f[i].data.hour
						>> f[i].data.min >> f[i].data.day >> f[i].data.month >>
						f[i].data.year >> f[i].term;
						
						words[i]=f[i].id +" "+ f[i].name +" "+ f[i].uom+" "+to_string(f[i].num) +" "+to_string(f[i].data.hour)
						+" "+ to_string(f[i].data.min) +" "+to_string(f[i].data.day) +" "+ to_string(f[i].data.month)+" "+
						to_string(f[i].data.year)+" "+ to_string(f[i].term) ; 
				}
				delete []f;
				} 
}
//saving for interactive
void save_items(string *words,int numb){
	FILE * fout_bin;
	fout_bin = fopen("products_bin.dat", "ab+");
				ofstream fout("products.txt", ios_base::app);
				fout << endl;
				int i,j;
				for (i = 0;i < numb;i++) {
					/*words[i] = f[i].id + " " + f[i].name + " " + f[i].uom + " " + to_string(f[i].num) + " " + to_string(f[i].data.hour)
						+ " " + to_string(f[i].data.min) + " " + to_string(f[i].data.day) + " " + to_string(f[i].data.month) + " " +
						to_string(f[i].data.year) + " " + to_string(f[i].term);*/
					if (i != numb - 1) 	fout << words[i] << endl;
					else fout << words[i];
					
					fwrite("\n",sizeof(char),1, fout_bin);
					for (j = 0;j < words[i].size();j++)
						fwrite(/*(char*)*/&words[i][j], sizeof(char), 1, fout_bin);
					//fwrite("\n", sizeof(char), 1, fout_bin);

					/*sql_str = "CREATE TABLE IF NOT EXISTS foo(a char(60)); INSERT INTO FOO VALUES(\" ";
					sql_str += words[i];
					sql_str += "\");";
					const char* SQL = sql_str.c_str();
					database(SQL);*/
				}
				fout.close();
				fclose(fout_bin);
}
//recovery data for interactive
void recovery_items(string* line,int &index){
			ifstream file("products.txt");
				int ind = 0;
				//if (mode==1) product* out = new product[200000]; else
				product* out = new product[200000];		
				/*int n=100;
				char *buffer=new char[n+1];
				buffer[n]=0;*/
				while (!file.eof()) {			
					file >> out[ind].id >> out[ind].name >> out[ind].uom >> out[ind].num >> out[ind].data.hour
						>> out[ind].data.min >> out[ind].data.day >> out[ind].data.month >>
						out[ind].data.year >> out[ind].term;
					//	file.getline(buffer,n);
					//initfromfile(a[i]);	
				line[ind] = out[ind].id + " " + out[ind].name + " " + out[ind].uom +
						" " + to_string(out[ind].num) + " " + to_string(out[ind].data.hour)
						+ " " + to_string(out[ind].data.min) + " " + to_string(out[ind].data.day) + " " +
						to_string(out[ind].data.month) + " " + to_string(out[ind].data.year) + " " +
						to_string(out[ind].term);	
					ind++;
				} file.close();
				index=ind;
			delete [] out;			
	
}
void recovery_benchmark(int &data_id, int &memory){
			ifstream file("products.txt");
				int ind = 0;
				//if (mode==1) product* out = new product[200000]; else
				product* out = new product[data_id+1];		
				/*int n=100;
				char *buffer=new char[n+1];
				buffer[n]=0;*/
				while (!file.eof()) {				
					file >> out[ind].id >> out[ind].name >> out[ind].uom >> out[ind].num >> out[ind].data.hour
						>> out[ind].data.min >> out[ind].data.day >> out[ind].data.month >>
						out[ind].data.year >> out[ind].term;
					//	file.getline(buffer,n);
					memory+=sizeof(out[ind]);
					//initfromfile(a[i]);	
					
					ind++;
				} 
				file.close();
				
			delete [] out;			
	
}

void print_items(string* &line, int ind){
	int i;
	for (i = 0;i < ind;i++) { 
	if (line[i][0]=='i')
					cout << line[i] << endl;
				}
}
void search_items(int mode, int &memory, string* line,string* my_line, int ind_my_line){
	if (mode==1){
	string str_name,str_uom,new_name;
	int i=0;
				cout << "Write the beginning of the product: " << endl;
				cin >> str_name;
				int hour, minutes, day, month, year;
				bool flag = false;
				int len = str_name.length(), min, max;
				cout << "Write the min number: " << endl;
				cin >> min;
				cout << "Write the max number: " << endl;
				cin >> max;
				cout << "Write units of measurement: " << endl;
				cin >> str_uom;
				cout << "Produced no later than :" << endl;
				cin >> hour >> minutes >> day >> month >> year;
				int k = 0;
				product search;
				ifstream file("products.txt");
				while (!file.eof()) {
					file >> search.id >> search.name >> search.uom >> search.num >> search.data.hour
						>> search.data.min >> search.data.day >> search.data.month >>
						search.data.year >> search.term;
						
							new_name = search.name.erase(len, search.name.length() - len);

								if (search.data.year > year || (search.data.year >= year
									&& search.data.month > month) || (search.data.year >= year
										&& search.data.month >= month && search.data.day > day) ||
									(search.data.year >= year && search.data.month >= month && search.data.day >= day
										&& search.data.hour > hour) || (search.data.year >= year && search.data.month >= month
											&& search.data.day >= day && search.data.hour >= hour && search.data.min > minutes)) flag = true;
								if (new_name == str_name && search.num > min && search.num < max
									&& search.uom == str_uom && flag == true) {
										//save my_line;
									my_line[ind_my_line] = line[i];
									ind_my_line++;
									flag = false;					
					}
			 		}
					file.close();} else
					if (mode==2){
					int ind_t = 0;
						string str_name = "Ca", str_uom = "kilo",new_name,len;
						int hour = 10, minutes = 10, day = 10, month = 12, year = 2020;
						bool flag = false;
						int min = 10, max = 200;
						product search;
				ifstream file("products.txt");
				while (!file.eof()) {
					file >> search.id >> search.name >> search.uom >> search.num >> search.data.hour
						>> search.data.min >> search.data.day >> search.data.month >>
						search.data.year >> search.term;
						
							new_name = search.name.erase(2, search.name.length() - 2);

								if (search.data.year > year || (search.data.year >= year
									&& search.data.month > month) || (search.data.year >= year
										&& search.data.month >= month && search.data.day > day) ||
									(search.data.year >= year && search.data.month >= month && search.data.day >= day
										&& search.data.hour > hour) || (search.data.year >= year && search.data.month >= month
											&& search.data.day >= day && search.data.hour >= hour && search.data.min > minutes)) flag = true;
								if (new_name == str_name && search.num > min && search.num < max
									&& search.uom == str_uom && flag == true) {
										//save my_line;
									my_line[ind_my_line] = search.id + search.name + search.uom + to_string(search.num )+to_string( search.data.hour)
						+to_string( search.data.min ) +to_string(search.data.day )+to_string( search.data.month )+
						to_string(search.data.year )+to_string(search.term);
						memory+=my_line[ind_my_line].size();
									ind_my_line++;
									flag = false;
						
					}
					//memory+=sizeof(search);	
					} file.close();} 
}

int main()
{ 	string* words = new string[200000],* line = new string[200000],*my_line = new string[200000];
	int memory=0,data_id=0,id=0;
	int index=0,ind=0,ind_my_line=0;
	int numb=0;
	//product* f = new product[200000];
	//product* out = new product[200000];
	int mode = 1, interactive = 0, i, j, k, gen = 10;
	FILE* fout_bin;
	string str_name, str_uom, new_name;
	//for clear database

	/*sql_str = "DELETE FROM foo;";
	const char* SQL = sql_str.c_str();
	database(SQL);*/


	//char new_name[100];
	cout << "Select the operating mode: 1 Interactive mode, 2 Demonstration mode, 3 Benchmark mode,9 EXIT: " << endl;
	//while (mode!=9){

	cin >> mode;
	// interactive
	if (mode == 1) {
		unsigned int x,y;
		int id=0;
		func(gen,1,x,y,id,memory,1);
		cout << "Select the operating mode: 1 Adding item, " <<
			"2 Data storage, 3 Data recovery, 4 Output of all saved data, " <<
			"5 Search by particle of name, 9 EXIT. " << endl;
		//"6 Modification of elements, 7 Delete items, 9 Exit" << endl;
		while (interactive != 9) {
			cin >> interactive;
			if (interactive == 1) {
				cout << "Write number of items: ";
				cin >> numb;
				add_items(numb, words);
				}else

			if (interactive == 2) {
				save_items(words, numb);	
			} else

			if (interactive == 3) {
				recovery_items(line, ind);
			}  else

			if (interactive == 4) {
				print_items(line,ind);
			} else

			if (interactive == 5) {
				search_items(1,memory,line,my_line,ind_my_line);
			} 
			}
			 } else

		//mode 2
		// demo

		if (mode == 2) {
			unsigned int x,y;
			id=0;
			func(gen,1,x,y,id,memory,0);
			cout << "Select the operating mode: 1 Adding item, " <<
				"2 Data storage, 3 Data recovery, 4 Output of all saved data, " <<
				"5 Search by particle of name, " <<
				"6 Modification of elements, 7 Delete items, 9 Exit" << endl;
			cout << "1" << endl;
			cout << "Write number of items: 1" << endl;
			cout << "id10 carrot kilo 24 23 55 11 12 2020 65 " << endl;
				product f[1];
			f[0].id = "id10";
			f[0].name = "carrot";
			f[0].uom = "kilo";
			f[0].num = 24;
			f[0].data.hour = 23;
			f[0].data.min = 55;
			f[0].data.day = 11;
			f[0].data.month = 12;
			f[0].data.year = 2020;
			f[0].term = 65;
			cout << "2" << endl;

			fout_bin = fopen("products_bin.dat", "ab+");
			ofstream fout("products.txt", ios_base::app);
			fout << endl;
			i = 0;
			string str_mode2;
			str_mode2 = f[i].id + " " + f[i].name + " " + f[i].uom + " " + to_string(f[i].num) + " " + to_string(f[i].data.hour)
				+ " " + to_string(f[i].data.min) + " " + to_string(f[i].data.day) + " " + to_string(f[i].data.month) + " " +
				to_string(f[i].data.year) + " " + to_string(f[i].term);
			fout << str_mode2;
			
			fwrite("\n", sizeof(char), 1, fout_bin);
			for (j = 0;j < str_mode2.length();j++)
				fwrite(/*(char*)*/&str_mode2[j], sizeof(char), 1, fout_bin);
			
			//sql
			/*sql_str = "CREATE TABLE IF NOT EXISTS foo(a char(60)); INSERT INTO FOO VALUES(\" ";
			sql_str += words[i];
			sql_str += "\");";
			const char* SQL = sql_str.c_str();
			database(SQL);*/

			fout.close();
			fclose(fout_bin);


			cout << "3" << endl;
			ifstream file("products.txt");
			ind = 0;
			product recovery_demo[11];
			while (!file.eof()) {
				file >>  recovery_demo[ind].id >>  recovery_demo[ind].name >>  recovery_demo[ind].uom >>  recovery_demo[ind].num >>  recovery_demo[ind].data.hour
					>>  recovery_demo[ind].data.min >>  recovery_demo[ind].data.day >>  recovery_demo[ind].data.month >>
					 recovery_demo[ind].data.year >>  recovery_demo[ind].term;

				line[ind] =  recovery_demo[ind].id + " " +  recovery_demo[ind].name + " " +  recovery_demo[ind].uom +
					" " + to_string( recovery_demo[ind].num) + " " + to_string( recovery_demo[ind].data.hour)
					+ " " + to_string( recovery_demo[ind].data.min) + " " + to_string( recovery_demo[ind].data.day) + " " +
					to_string( recovery_demo[ind].data.month) + " " + to_string( recovery_demo[ind].data.year) + " " +
					to_string( recovery_demo[ind].term);
				ind++;
			} file.close();


			cout << "4" << endl;
			for (i = 0;i < ind;i++)	cout << line[i] << endl;


			cout << "5" << endl;

			cout << "Write the beginning of the product: " << endl;
			cout << "ca" << endl;
			cout << "Write the min number: " << endl;
			cout << "10" << endl;
			cout << "Write the max number: " << endl;
			cout << "100" << endl;
			cout << "Write units of measurement: " << endl;
			cout << "kilo" << endl;
			cout << "Produced no later than :" << endl;
			cout << "10 10 10 12 2020" << endl;
			int ind_t = 0;
			string str_names = "ca", str_uoms = "kilo";
			int hours = 10, minutess = 10, days = 10, months = 12, years = 2020;
			bool flags = false;
			int mins = 10, maxs = 100;

			for (i = 0;i < ind;i++)
				if ( recovery_demo[i].name.length() >= 2) {
					new_name =  recovery_demo[i].name.erase(2,  recovery_demo[i].name.length() - 2);

					if ( recovery_demo[i].data.year > years || ( recovery_demo[i].data.year >= years
						&&  recovery_demo[i].data.month > months) || ( recovery_demo[i].data.year >= years
							&&  recovery_demo[i].data.month >= months &&  recovery_demo[i].data.day > days) ||
						( recovery_demo[i].data.year >= years &&  recovery_demo[i].data.month >= months &&  recovery_demo[i].data.day >= days
							&&  recovery_demo[i].data.hour > hours) || ( recovery_demo[i].data.year >= years &&  recovery_demo[i].data.month >= months
								&&  recovery_demo[i].data.day >= days &&  recovery_demo[i].data.hour >= hours &&  recovery_demo[i].data.min > minutess)) flags = true;
					//cout << new_name << endl;
					if (new_name == str_names &&  recovery_demo[i].num > mins &&  recovery_demo[i].num < maxs
						&&  recovery_demo[i].uom == str_uoms && flags == true) {
						cout << line[i] << endl;
						/*my_line[ind_t]=line[i];
						ind_t++;*/
						flags = false;
					}
				}

			cout << "9" << endl;

			}
			else
			// mode 3 
			// benchmark
			if (mode == 3) {
				/* product* out_new= new product[200000];
				string  *lines=new string[200000],*my_lines=new string[200000];*/
				unsigned long search_time = 0, start_time, end_time, sum_time = 0, s_time = 0, g_time = 0, r_time = 0,
				 start_s_time = 0, start_g_time = 0, start_r_time = 0, end_s_time = 0, end_g_time = 0, end_r_time = 0;
				//memory = 0;
				int key;
				unsigned int time_bin=0,time_str=0;
				long sum_gen;
					cout << "Write your number: ";
					cin >> key;

			//	for (key = 1;key <= 10;key++) {
					//for clear database
					/*sql_str = "DELETE FROM foo;";
					const char* SQL = sql_str.c_str();
					database(SQL);*/
					sum_gen = 0;			
					memory=0;
					sum_time = 0;
					s_time = 0;
					g_time = 0;
					r_time = 0;
					gen = key;
					
					while (sum_time < 1000) {
						start_time = clock();
						
						// generation
						start_s_time = clock();
						if (gen == key) func(gen,1, time_bin, time_str, data_id , memory,0); else func(gen,2,time_bin, time_str,data_id,memory,0);
						end_s_time = clock();
						s_time += end_s_time - start_s_time;
						
						ind = 0;
						sum_gen += gen;
						// Data recovery
						start_r_time = clock();
						recovery_benchmark(data_id, memory);
						end_r_time = clock();
						r_time += end_r_time - start_r_time;

						// Search item
						start_s_time = clock();
						search_items(2, memory,line,my_line,ind_my_line);
						end_s_time = clock();
						s_time = end_s_time - start_s_time;
						
						end_time = clock();
						search_time = end_time - start_time;
						sum_time += search_time;
						
						// for check time;
						//cout << search_time <<" "<< gen <<endl;
						gen = gen * 2;
					}
					int current_gen = gen / 2;
					
					// second part,ariph prog

					while (sum_time < 10000) {

						start_time = clock();
						current_gen += gen / 2;
						sum_gen += current_gen;
						// generation
						start_g_time = clock();
						func(current_gen,2, time_bin, time_str,data_id, memory,0);
						end_g_time = clock();
						g_time += end_g_time - start_g_time;

						ind = 0;
						// Data recovery
						start_r_time = clock();
						recovery_benchmark(data_id, memory);
						end_r_time = clock();
						r_time += end_r_time - start_r_time;

						// Search item
						start_s_time = clock();
						search_items(2,memory,line,my_line,ind_my_line);
						end_s_time = clock();
						s_time = end_s_time - start_s_time;
						
						end_s_time = clock();
						s_time += end_s_time - start_s_time;
						//	delete[] out, line,my_line;	
						end_time = clock();
						search_time = end_time - start_time;
						sum_time += search_time;

						// for check time;
						 // cout << search_time <<" "<< current_gen << endl;

					}
					//cout << key << endl;
					//for writing in file
				/*	ofstream fout("result_new.txt", ios_base::app);
				fout << "N: " << key << endl;
				fout << "Sum_time: " << sum_time << "ms" << endl;
				fout << "	Time of searching: "<<s_time<<"ms"<<endl;
				fout << "	Time of generation and writing: "<<g_time<<"ms"<<endl;
				fout << "		Time of writing to stream: "<<time_str<<"ms"<<endl;
				fout << "		Time of writing to binary: "<<time_bin<<"ms"<<endl;
				fout << "	Time of recovery data: "<<r_time<<"ms"<<endl;
				fout << "Used memory: " << memory << " bytes"<<endl;
				fout << "Number of last generation: " << current_gen << endl;
				fout << "Sum of generation: " << sum_gen << endl;
				fout << "Size of File: "<<fileSize("products.txt")<< " bytes"<<endl;
				fout << "Size of binary File: "<<fileSize_bin("products_bin.dat")<< " bytes"<<endl;
				fout << endl;
				fout.close();*/
				

					//output result
				cout << "N: " << key << endl;
				cout << "Sum_time: " << sum_time << "ms" << endl;
				cout << "	Time of searching: "<<s_time<<"ms"<<endl;
				cout << "	Time of generation and writing: "<<g_time<<"ms"<<endl;
				cout << "		Time of writing to stream: "<<time_str<<"ms"<<endl;
				cout << "		Time of writing to binary: "<<time_bin<<"ms"<<endl;
				cout << "	Time of recovery data: "<<r_time<<"ms"<<endl;
				cout << "Used memory: " << memory << " bytes"<<endl;
				cout << "Number of last generation: " << current_gen << endl;
				cout << "Sum of generation: " << sum_gen+1 << endl;
				cout << "Size of File: "<<fileSize("products.txt")<< " bytes"<<endl;
				cout << "Size of binary File: "<<fileSize_bin("products_bin.dat")<< " bytes"<<endl;
				cout << endl;


				}

		//	}



	//delete trash memory from mode 1 and mode 2
	delete[] words, line, my_line;





	return 0;
}
