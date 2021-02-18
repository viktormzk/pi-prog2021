#include <iostream>
struct circle{
	double x;
	double y;
	double r;
};
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
struct list {
	ListNode* begin;
	ListNode* end;
	std::size_t size;

	list() {
		begin = NULL;
		end = NULL;
		size = 0;
	}
ListNode* search(circle x) {
		ListNode* current = begin;
		while (current) {
			if (current->data.x == x.x && current->data.y == x.y &&current->data.r == x.r  ) {
				return current;
			}
			current = current->next;
		}
		return NULL;
	}
	
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
				std::cout<<current->data.x<<" "<<current->data.y <<" " << current->data.r<<std::endl;
				return current;
			}
			current = current->next;
			i++;
		}
		return NULL;
	}
	
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
	}
bool remove(int index_to_remove) {
	if (index_to_remove < 0){
		index_to_remove+=size;
		//std::cout << "OK" <<std::endl;
	}	
	if (index_to_remove >= size || index_to_remove<0) {
		 std::cout << "Not ok, error index" <<std::endl;
			return false;
	} 
		bool from_begin = false;
		
		if (index_to_remove < size/2) {
			from_begin = true;
		}
		ListNode* current = from_begin ? begin : end;
		std::size_t current_index = from_begin ? 0 : size - 1;
		while (current) {
			if (current_index == index_to_remove) {
				current = remove_node(current);
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
		return false;
	}
void remove_if(list &my_list, circle x){
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
void show(list &my_list ) {
	std::cout << std::endl;
	std::cout << "List: " << std::endl;
		ListNode* current = my_list.begin;
		while (current) {
			std::cout<<current->data.x<<" "<<current->data.y <<" " << current->data.r<<std::endl;
			current = current->next;
		}
		std::cout << std::endl;
	}
	void length(list &my_list)	{
	std::cout <<"Length: "<< my_list.size << std::endl;	
	}
	
bool insert(list &my_list, circle x, int pos)
{   
   if(pos < 0 || pos > my_list.size -1)
   {
      std::cout << "Incorrect position !!!\n";
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
   return true;}
}
void create_empty(list &my_list)
	{
		my_list.begin = NULL;
		my_list.end = NULL;
		my_list.size=0;
	}
	
int main(){
	list my_list;
	int mode=1,interactive=1;
	std::cout << "Select the operating mode: 1 - Demo mode, 2 - Interactive mode, 3 - Benchmark "<<std::endl;
	std::cin >> mode;
	if (mode==1){
		std::cout << "Enter 1 - Create empty list, 2 - Add item to end, 3 - Insert item, "<<
		"4 - Remove by index, 5 - Show length of list, 6 - Show list, 7 - Remove by value, 8 - Get by index, 9 - Exit"<< std::endl;
		int number=-1;
		std::cout << "1" << std::endl;
		std::cout << "6" << std::endl;
		create_empty(my_list);
		show(my_list);
		std::cout << "1" << std::endl;
		std::cout << "2 \n1 1 1 \n2 \n2.23 4.12 2.111" << std::endl;
		std::cout << "6" << std::endl;
		create_empty(my_list);
		my_list.append({1,1,1});
		my_list.append({2.23,4.12,2.111});
		show(my_list);
		std::cout << "1" << std::endl;
		std::cout << "2 \n1 1 1 \n2\n2 4 2 \n2\n12 11 31 \n2\n232 412 212 \n3 \n1 5 7 1" << std::endl;
		std::cout << "6" << std::endl;
		create_empty(my_list);
		my_list.append({1,1,1});
		my_list.append({2,4,2}); 
		my_list.append({12,11,31});
		my_list.append({232,412,212});
		insert(my_list,{1,5,7}, 1);
		show(my_list);
		std::cout << "5 "<<std::endl;
		length(my_list);
		std::cout << std::endl;
		std::cout << "8 \n" <<number<< std::endl;
		my_list.get(number);
		std::cout << "4 \n" <<number<< std::endl;
		std::cout << "6" << std::endl;
		my_list.remove(number);
		show(my_list);
		std::cout << "7 \n1 1 1" << std::endl;
		std::cout << "6" << std::endl;
		my_list.remove_if(my_list, {1,1,1});
		show(my_list);
		} else
	if (mode==2) {
		std::cout << "Enter 1 - Create empty list, 2 - Add item to end, 3 - Insert item, "<<
		"4 - Remove by index, 5 - Show length of list, 6 - Show list, 7 - Remove by value, 9 - Exit"<< std::endl;
		while (interactive!=9){
			std::cin >> interactive;
			if (interactive==1){
				create_empty(my_list);
			} else
			if (interactive==2){
				double x,y,r;
				std::cout << "Write coordinates and radius: "<<std::endl;
				std::cin >> x >> y >> r;
				my_list.append({x,y,r});
			} else
			if (interactive==3){
				double x_ins,y_ins,r_ins;
				int ind;
				std::cout << "Write coordinates, radius and index of insert "<<std::endl;
				std::cin >> x_ins >> y_ins >> r_ins >> ind;
				insert(my_list,{x_ins,y_ins,r_ins}, ind);
			} else
			if (interactive==4){
				int index;
				std::cout << "Write index for remove: "<<std::endl;
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
				std::cout << "Write value for remove: "<<std::endl;
				std::cin >> rem.x >> rem.y >> rem.r;
				my_list.remove_if(my_list, rem);
			}
		}
	}
	
	//I note just for fun :)
	//17.02.21 15:37
	//18.02.21 00:33
	
	//18.02.21 01:51 
	//18.02.21 07:51
	
	//18.02.21 18:51
	//18.02.21 21:02
	
	return 0;
}
