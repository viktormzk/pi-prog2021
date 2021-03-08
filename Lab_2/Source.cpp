#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cstring>
#define MAX_LEVEL 6
const float P = 0.5;
using namespace std;
/*
 * Skip Node 
 */
struct snode
{
    int value;
    snode **forw;
    snode(int level, int &value)
    {
        forw = new snode * [level + 1];
        memset(forw, 0, sizeof(snode*) * (level + 1));
        this->value = value; 
    }
    ~snode()
    {
        delete [] forw;        
    } 
};
/*
 * Skip List 
 */
struct skiplist
{
    snode *header;
    int value;
    int level;
    skiplist() 
    {
        header = new snode(MAX_LEVEL, value);
        level = 0;
    }
    ~skiplist() 
    {
        delete header;
    }
    void display();
    bool contains(int &);
    void insert_element(int &);
    void delete_element(int &);        
};
/*
 * Random Value Generator
 */
float frand() 
{
    return (float) rand() / RAND_MAX;
}
/*
 * Random Level Generator
 */
int random_level() 
{
    static bool first = true;
    if (first) 
    {
        srand((unsigned)time(NULL));
        first = false;
    }
    int lvl = (int)(log(frand()) / log(1.-P));
    return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
}
 
/*
 * Insert Element in Skip List
 */
void skiplist::insert_element(int &value) 
{
    snode *x = header;	
    snode *update[MAX_LEVEL + 1];
    memset(update, 0, sizeof(snode*) * (MAX_LEVEL + 1));
    for (int i = level;i >= 0;i--) 
    {
        while (x->forw[i] != NULL && x->forw[i]->value < value) 
        {
            x = x->forw[i];
        }
        update[i] = x; 
    }
    x = x->forw[0];
    if (x == NULL || x->value != value) 
    {        
        int lvl = random_level();
        if (lvl > level) 
        {
            for (int i = level + 1;i <= lvl;i++) 
            {
                update[i] = header;
            }
            level = lvl;
        }
        x = new snode(lvl, value);
        for (int i = 0;i <= lvl;i++) 
        {
            x->forw[i] = update[i]->forw[i];
            update[i]->forw[i] = x;
        }
    }
}
/*
 * Display Elements of Skip List
 */
void skiplist::display() 
{
    const snode *x = header->forw[0];
    while (x != NULL) 
    {
        cout << x->value;
        x = x->forw[0];
        if (x != NULL)
            cout << " - ";
    }
    cout <<endl;
}
/*
 * Search Elements in Skip List
 */
bool skiplist::contains(int &s_value) 
{
    snode *x = header;
    for (int i = level;i >= 0;i--) 
    {
        while (x->forw[i] != NULL && x->forw[i]->value < s_value)
        {
            x = x->forw[i];
        }
    }
    x = x->forw[0];
    return x != NULL && x->value == s_value;
}

/*
* circle 2a
*/
struct circle{
	double x;
	double y;
	double r;
};
/*
* List Node for circle
*/
struct ListNode {
	circle data;
	ListNode* prev;
	ListNode* next;
	ListNode(circle data, ListNode* prev = NULL, ListNode* next = NULL) {
		this->data = data;
		this->prev = prev;
		this->next = next;
	}
};
/*
* list 
*/
struct list {
	ListNode* begin;
	ListNode* end;
	size_t size;

	list() {
		begin = NULL;
		end = NULL;
		size = 0;
	}
	/*
	* Search in list
	*/
ListNode* search(circle x) {
		ListNode* current = begin;
		while (current) {
			if (current->data.x == x.x && current->data.y == x.y &&current->data.r == x.r  ) {
				return current;
			}
			current = current->next;
		}
		delete[] current;
		return NULL;
	}
	/*
	*Rotate list
	*/
ListNode* rotate(list &my_list,int heat, int new_heat, int tail) { //for interactive and demo
	if (heat<0 || tail>my_list.size-1 || new_heat>tail || new_heat<heat){
		cout << "Error rotate! False index."<<endl;
		return NULL;
	}
		ListNode* current = begin;
		circle* cir=new circle[my_list.size+2];
		int i=0,k=0,z=0;
		
		while (current) {
			//cout << i << endl;
			if (i==heat) {
				while (i<new_heat){
				//cout <<"NEW heat: "<< i << endl;
				current = current->next;
				i++;
				}		
			while (i<=tail){
				//cout <<"tail: "<< i << endl;
				cir[k]={current->data.x,current->data.y,current->data.r};	
				if (i<tail)current = current->next;				
					i++;
					k++;
				}
				while (i>heat){
					if(i>1) current=current->prev;
					//cout <<"heat+tail-new_heat: "<< i << endl;
					i--;
				}
				while (i<new_heat){
					//cout <<"size: "<< i << endl;
					cir[k].x=current->data.x;
					cir[k].y=current->data.y;
					cir[k].r=current->data.r;
					if (i!=new_heat-1)current = current->next;					
					i++;
					k++;
			}
			
			}
			current = current->next;
			i++;
		}
		z=k-2;
		k=0;
		i=0;
		current=begin;
		//bool flag_2=false;
		while (current) {
			if (i==heat) {
				while (i<tail && current->next){
				//cout << i << endl;
				current->data.x=cir[k].x;
				current->data.y=cir[k].y;
				current->data.r=cir[k].r;
				
				if (i!=tail && z==k){
				current->next->data.x=cir[k+1].x;
				current->next->data.y=cir[k+1].y;
				current->next->data.r=cir[k+1].r;
			} else
			if (i==tail && z!=k){
				current->next->data.x=cir[k].x;
				current->next->data.y=cir[k].y;
				current->next->data.r=cir[k].r;
			}
				k++;
				i++;
			 current=current->next;
			} 
			//flag_2=true;
		}
			current=current->next;
			i++;
		}
	delete[] cir;
		return NULL;
}
/*
* Get by index
*/	
ListNode* get(int data_to_search) {
		if (data_to_search<0){
		data_to_search+=this->size;
	}
	if (data_to_search >= this->size) {
			return 0x0;
		} 
		ListNode* current = begin;
		int i=0;
		while (current) {
			if (i == data_to_search) {
				cout<<current->data.x<<" "<<current->data.y <<" " << current->data.r<<endl;
				return current;
			}
			current = current->next;
			i++;
		}
		return NULL;
	}
/*
*Append in end of the list
*/	
ListNode* append(circle data) {
		ListNode* new_item = new ListNode(data,this->end);
		if (end) { // list is not empty
			this->end->next = new_item;
		} else { // list is empty
			this->begin = new_item;
		}
		this->end = new_item;
		this->size++;
		return new_item;
		delete[] new_item;
	}
/*
*Remove from list
*/	
bool remove(int index_to_remove) {
	if (index_to_remove < 0){
		index_to_remove+=size;
		//cout << "OK" <<endl;
	}	
	if (index_to_remove >= size || index_to_remove<0) {
		 cout << "Not ok, error index" <<endl;
			return false;
	} 
		bool from_begin = false;
		
		if (index_to_remove < size/2) {
			from_begin = true;
		}
		ListNode* current = from_begin ? begin : end;
		size_t current_index = from_begin ? 0 : size - 1;
		while (current) {
			if (current_index == index_to_remove) {
				current = remove_node(current);
				delete[] current;
				return true;
			}
			if (from_begin) {
				current = current->next;
				current_index++;
			} else {
				current = current->prev;
				current_index--;
			}
		}
		delete[] current;
		return false;
	} 
/*
*Remove if value == value in list
*/	
void remove_if(list &my_list, circle x){ //for interactive and demo
	ListNode* current=my_list.search(x); //add new func search by value
	current = remove_node(current);	
}

private:
	ListNode* remove_node(ListNode* current) {
		if (current->prev) {
			current->prev->next = current->next;
		} else {
			this->begin = current->next;
		}
		if (current->next) {
			current->next->prev = current->prev;
		} else {
			this->end = current->prev;
		}
		delete current;
		this->size--;
		return current;
	}
};
/*
* Show list of circles
*/
void show(list &my_list ) {
	cout <<"-----------"<< endl;
	cout << "List: " << endl;
		ListNode* current = my_list.begin;
		while (current) {
			cout<<current->data.x<<" "<<current->data.y <<" " << current->data.r<<endl;
			current = current->next;
		}
		cout <<"-----------"<< endl;
		delete[] current;
	}
	void length(list &my_list)	{
	cout <<"Length: "<< my_list.size << endl;	
	}
/*
*Insert element in list
*/	
bool insert(list &my_list, circle x, int pos)
{   
   if(pos < 0 || pos > my_list.size -1)
   {
      cout << "Incorrect position !!!\n";
      return false;
   } else
 
   if(pos == my_list.size)
   {
      my_list.append(x);
      my_list.size++;
      return true;
   } else {
  
   int i = 1;
 
   ListNode * Ins = my_list.begin;
 
   while(i <= pos)
   {
      Ins = Ins->next;
      i++;
   }
   ListNode * PrevIns = Ins->prev;
   ListNode * temp = new ListNode(x,PrevIns,Ins);
    PrevIns->next = temp;
 
   temp->next = Ins;
   temp->prev = PrevIns;
   Ins->prev = temp;
 
   my_list.size++;
   delete[] PrevIns,temp,Ins;
   return true;}
}
/*
*Create empty list
*/
void create_empty(list &my_list)
	{
		my_list.begin = NULL;
		my_list.size=0;
	}
	
int main(){
	list my_list;
	int global_mode=1;
	/*
	* Select the list of circles or skip list
	*/
	cout << "Select the list: 1 - Circles, 2 - Skip List"<< endl;
	cin >> global_mode;
	/*
	* In list of crc select mode
	*/
	if (global_mode==1){
	cout << "Select the operating mode: 1 - Demo mode, 2 - Interactive mode, 3 - Benchmark "<<endl;
	int mode=1;
	cin >> mode;
	/*
	* Demo mode for list of crc 
	*/
	if (mode==1){
		cout << "Enter 1 - Create empty list, 2 - Add item to end, 3 - Insert item, "<<
		"4 - Remove by index, 5 - Show length of list, 6 - Show list, 7 - Remove by value, 8 - Get by index, 9 - Rotate, 10 - EXIT"<< endl;
		int number=2;
		cout << "1" << endl;
		cout << "6" << endl;
		create_empty(my_list);
		show(my_list);
		cout << "1" << endl;
		cout << "2 \n1 1 1 \n2 \n2.23 4.12 2.111" << endl;
		cout << "6" << endl;
		create_empty(my_list);
		my_list.append({1,1,1});
		my_list.append({2.23,4.12,2.111});
		show(my_list);
		cout << "2 \n1 1 1 \n2\n2 4 2 \n2\n12 11 31 \n2\n232 412 212 \n3 \n1 5 7 1" << endl;
		cout << "6" << endl;
		my_list.append({2,4,2}); 
		my_list.append({12,11,31});
		my_list.append({232,412,212});
		insert(my_list,{1,5,7}, 2);
		show(my_list);
		
		cout << "5 "<<endl;
		length(my_list);
		cout << endl;
		
		cout << "4 \n" <<-1<< endl;
		cout << "6" << endl;
		my_list.remove(-1);
		show(my_list);
		
		cout << "7 \n1 1 1" << endl;
		cout << "6" << endl;
		my_list.remove_if(my_list, {1,1,1});
		show(my_list);
		
		cout << "8 \n2" << endl;
		cout << "6" << endl;
		my_list.get(2);
		show(my_list);
		
		cout << "9 \n0 1 1" << endl;
		cout << "6" << endl;
		my_list.rotate(my_list,0,1,1);
		show(my_list);
		
		} else
	/*
	* Interactive mode for list of crc 
	*/
	if (mode==2) {
		cout << "Enter 1 - Create empty list, 2 - Add item to end, 3 - Insert item, "<<
		"4 - Remove by index, 5 - Show length of list, 6 - Show list, 7 - Remove by value, 8 - Get by index, 9 - Rotate, 10 - EXIT"<< endl;
		int interactive=1;
		while (interactive!=10){
			cin >> interactive;
			if (interactive==1){
				create_empty(my_list);
			} else
			if (interactive==2){
				double x,y,r;
				cout << "Write coordinates and radius: "<<endl;
				cin >> x >> y >> r;
				my_list.append({x,y,r});
			} else
			if (interactive==3){
				double x_ins,y_ins,r_ins;
				int ind;
				cout << "Write coordinates, radius and index of insert "<<endl;
				cin >> x_ins >> y_ins >> r_ins >> ind;
				insert(my_list,{x_ins,y_ins,r_ins}, ind);
			} else
			if (interactive==4){
				int index;
				cout << "Write index for remove: "<<endl;
				my_list.remove(index);
			}else
			if (interactive==5){
				length(my_list);
			} else
			if (interactive==6){
				show(my_list);	
			}else
			if (interactive==7){
				circle rem;
				cout << "Write value for remove: "<<endl;
				cin >> rem.x >> rem.y >> rem.r;
				my_list.remove_if(my_list, rem);
			}else
			if (interactive==8){
				int i;
				cout << "Write idex for get item: "<<endl;
				cin >> i;
				my_list.get(i);
			}else
			if (interactive==9){
				int x,y,z;
				cout << "Write value for rotate: "<<endl;
				cin >> x >> y >> z;
				my_list.rotate(my_list,x,y,z);
			}
		}
	} else
	/*
	* Benchmark mode for list of crc 
	*/
	 if (mode==3) {
	 	ofstream input("result.txt");
	 	int k=0;
	 	long long i=0;
	 	unsigned int start=0, end=0,search=0;
	 	
		input<< "Create empty(*1): ";
		while(search<10000){
		start=clock();
		i=i+100000;
		for (k=0;k<100000;k++)
		create_empty(my_list);
		end=clock();
		search+=end-start;
		}
		input << search <<" ms"<< endl;
		input << "Number: "<< i <<endl;
		
		search=0;
		i=0;
		input << "Add 1 item(1,1,1)(*1): ";
		while(search<10000){
		start=clock();
		i+=100000;
		for (k=0;k<100000;k++){
		create_empty(my_list);
		my_list.append({1,1,1});}
		end=clock();
		search+=end-start;}
		input << search <<" ms"<< endl;
		input << "Number: "<< i <<endl;
		
		search=0;
		i=0;
		input << "Add 1 item(212312.213213,41231231.213123112,2.12312312311)(*1): " ;
		while(search<10000){
		start=clock();
		i+=100000;
		for (k=0;k<100000;k++){
		create_empty(my_list);
		my_list.append({212312.213213,41231231.213123112,253453.123312311});}
		end=clock();
		search+=end-start;}
		input << search <<" ms"<< endl;
		input << "Number: "<< i <<endl;
		
		search=0;
		i=0;
		input << "Insert 1 item(1,5,7)(*1): ";
		while(search<10000){
		start=clock();
		i+=100000;
		for (k=0;k<100000;k++){
		create_empty(my_list);
		insert(my_list,{1,5,7}, 0);	}
		end=clock();
		search+=end-start;}
		input << search <<" ms"<< endl;
		input << "Number: "<< i <<endl;
		
		search=0;
		i=0;
		input << "Insert 1 item(12312312.1323123,5123123.12314325,7345345345.14124124)(*1): ";
		while(search<10000){
		start=clock();
		i+=100000;
		for (k=0;k<100000;k++){
		create_empty(my_list);
		insert(my_list,{12312312.1323123,5123123.12314325,7345345345.14124124}, 0);	}
		end=clock();
		search+=end-start;}
		input << search <<" ms"<< endl;
		input << "Number: "<< i <<endl;
		
		search=0;
		i=0;
		input << "Get length(*1): ";
		while(search<10000){
		start=clock();
		i+=100;
		for (k=0;k<100;k++){
		create_empty(my_list);
		length(my_list);}
		end=clock();
		search+=end-start;}
		input << search <<" ms"<<endl;
		input << "Number: "<< i <<endl;
		
		i=0;
		search=0;
		create_empty(my_list);
		input << "Remove(*1): ";
		while(search<10000){
		start=clock();
		i+=100000;
		for (k=0;k<100000;k++){
		my_list.append({1,1,1});
		my_list.remove(-1);}
		end=clock();
		search+=end-start;}
		input << search <<" ms"<< endl;
		input << "Number: "<< i <<endl;
		
		search=0;
		i=0;
		create_empty(my_list);
		my_list.append({1,1,1});
		input << "Get by index(*1): ";
		while(search<10000){
		start=clock();
		i+=10000;
		for (k=0;k<10000;k++)
		my_list.get(0);
		end=clock();
		search+=end-start;}
		input << search <<" ms"<< endl;
		input << "Number: "<< i <<endl;
		
		search=0;
		i=0;
		create_empty(my_list);
		my_list.append({1,1,1});
		input << "Show list(*1): ";
		while(search<10000){
		i+=1000;
		start=clock();
		for (k=0;k<1000;k++)
		show(my_list);
		end=clock();
		search+=end-start;}
		input << search <<" ms"<<endl;
		input << "Number: "<< i <<endl;
		
		input.close();
		 }
	return 0;
	}
	/*
	*Select Skip List
	*/
	else if (global_mode==2){
	skiplist ss;
    int choice, n;
    int mode=1;
    cout << "Select mode: 1 - Interactive, 2 - Demo"<<endl;
    cin >> mode;
    if (mode==1){
    	/*
    	* Interactive mode for skip list
    	*/
        cout<<"Secelt operation: 1 - Add Element, 2 -Search Element, 3 - Display List, 4 - EXIT "<<endl;
        while(1){
    	cin>>choice;
        switch(choice)
        {
        case 1:
             cout<<"Enter the element to be inserted: ";
             cin>>n;
             ss.insert_element(n);
             if(ss.contains(n))
                 cout<<"Element Inserted"<<endl;
             break;
        case 2:
             cout<<"Enter the element to be searched: ";
             cin>>n; 
             if(ss.contains(n))
                 cout<<"Element "<< n <<" is in the list"<<endl;
             else
                 cout<<"Element not found"<<endl;
             break;
        case 3:
             cout<<"The List is: ";
             ss.display();
             break;
        case 4:
             exit(0);
             break;
        default:
             cerr<<"Wrong Choice!"<<endl;
             return 0;
        }
    }
        return 0;
	}else if (mode==2){
		/*
    	* Interactive mode for skip list
    	*/
    	int n=0;
    	cout<<"Secelt operation: 1 - Add Element, 2 -Search Element, 3 - Display List, 4 - EXIT "<<endl;
             
             cout << 1 << endl;
			 cout<<"Enter the element to be inserted: 12";
             n=12;
             ss.insert_element(n);
             if(ss.contains(n))
                 cout<<"Element Inserted"<<endl;
              
			 cout << 2 <<endl; 
             cout<<"Enter the element to be searched: 13"<<endl;
             n=13; 
             if(ss.contains(n))
                 cout<<"Element "<< n <<" is in the list"<<endl;
             else
                 cout<<"Element not found"<<endl;
                
			cout << 2 <<endl; 
            cout<<"Enter the element to be searched: 12"<<endl;
                 
             n=12; 
             if(ss.contains(n))
                 cout<<"Element "<< n <<" is in the list"<<endl;
             else
                 cout<<"Element not found"<<endl;
           	 cout << 3 <<endl; 
             cout<<"The List is: ";
             ss.display();
             cout << 4 <<endl;
    	
    	return 0;
	} else
		/*
    	* If not correct mode of skip list
    	*/
	cerr << "Error mode!"<<endl;
	return 0;
	
	}
		/*
    	* If not correct mode of kind of list
    	*/
	 else
	cerr <<"Error choose!"<<endl;

	//I note just for fun :)
	
	//17.02.21 15:37
	//18.02.21 00:33
	
	//18.02.21 01:51 
	//18.02.21 07:51
	
	//18.02.21 18:51
	//18.02.21 21:02
	
	//19.02.21 14:24
	//19.02.21 23:51
	
	//20.02.21 01:30
	//20.02.21 08:30
	
	//20.02.21 13:01
	//20.02.21 14:12
	
	//22.02.21 13:22
	//22.02.21 21:18
	
	//23.02.21 15:12
	//23.02.21 23:23
	
	return 0;
}
