#include <iostream>
// 17.02.21 15:37
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
	}	
	if (index_to_remove >= size || index_to_remove<0) {
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
		ListNode* current = my_list.begin;
		while (current) {
			std::cout<<current->data.x<<" "<<current->data.y <<" " << current->data.r<<std::endl;
			current = current->next;
		}
		std::cout<<std::endl;
	}
	void length(list &my_list)	{
	std::cout << my_list.size << std::endl;	
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
	int number=-2;
	std::cout << "	Test empty list" << std::endl;
	create_empty(my_list);
	show(my_list);
	std::cout << "	Test add1" << std::endl;
	create_empty(my_list);
	my_list.append({1,1,1});
	my_list.append({2,4,2});
	show(my_list);
	std::cout << "	Test insert" << std::endl;
	create_empty(my_list);
	my_list.append({1,1,1});
	my_list.append({2,4,2}); 
	my_list.append({12,11,31});
	my_list.append({232,412,212});
	insert(my_list,{1,5,7}, 1);
	show(my_list);
	std::cout << "	Test length" << std::endl;
	length(my_list);
	std::cout << "	Test get " <<number<< std::endl;
	my_list.get(number);
	std::cout << "	Test remove " <<number<< std::endl;
	bool removed = my_list.remove(number);
	if (removed) {
		std::cout<<"removed "<<number<<std::endl;

	} else {
		std::cout<<"Dont removed "<<number<<std::endl;
	}
	show(my_list);
	
	
	
	
	//18.02.21 00:33
	//18.02.21 01:51
	return 0;
}
