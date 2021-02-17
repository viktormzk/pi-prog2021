#include <iostream>
// 17.02.21 15:37
struct circle{
	double x;
	double y;
	double r;
};
struct ListNode {
	circle data;
	ListNode* Prev;
	ListNode* Next;
	};
	
struct	list {
		ListNode* head; 
		ListNode* tail; 
		std::size_t size;
	}; 

void create_empty(list &my_list)
{
	my_list.head = NULL;
	my_list.size=0;
}
	bool chk_empty(list my_list)
	{
		return (my_list.head==NULL);
	}	
void add(list &my_list, circle nt)
{
	ListNode* new_item = new ListNode();
	new_item->data=nt;
	new_item->Next = NULL;
	if (chk_empty(my_list))
		my_list.head = new_item;
	else
		my_list.tail->Next = new_item;
		
	my_list.size+=1;
	my_list.tail = new_item;
} 

void show(list &my_list){
	ListNode* current = my_list.head;
	while(current){
		std::cout << current->data.x <<" " << current->data.y <<" "<< current->data.r << std::endl;
		current=current->Next;
	}
	
}
void insert(list &my_list,circle x, int k){
	std::string ans=(my_list.size>1) ? " elements" : " element" ;
	if (k<0 || k>my_list.size-1) std::cout << "In list "<<	my_list.size << ans << ", uncorrect number"<<std::endl; 
	else {
	ListNode* temp = new ListNode();
    temp -> data = x;
    temp -> Next = NULL;

    if ( k == 0 )
    {
        temp -> Next = my_list.head;
        my_list.head = temp;
        return;
    }

    ListNode* temp1 = my_list.head;

    for (int i = 0; i < k-1; i++)
    {
        temp1 = temp1 -> Next;
    }


    temp -> Next = temp1 -> Next;
    temp1 -> Next = temp;
	}
	my_list.size+=1;
	
}

ListNode* remove_node(list &my_list, ListNode  *current) {
		if (current->Prev) {
		current->Prev->Next = current->Next;
		} else {
			my_list.head = current->Next;
		}
		if (current->Next) {
			current->Next->Prev = current->Prev;
		} else {
			my_list.tail = current->Prev;
		}
		delete current;
		my_list.size--;
		return current;
		
	}

void remove(list &my_list, std::size_t index_to_remove) {
	bool from_begin;
		if (index_to_remove > my_list.size-1 || index_to_remove<0) {
			std::cout << "Error index for remove"<<std::endl;
		} else {
		if (index_to_remove < (my_list.size-1)/2) {
			from_begin = true;
		}
		ListNode* current = from_begin ? my_list.head : my_list.tail;
		std::size_t current_index = from_begin ? 0 : my_list.size-1 ;
		while (current) {
			if (current_index == index_to_remove) {
				current = remove_node(my_list, current);
			}
			if (from_begin) {
				current = current->Next;
				current_index++;
			} else {
				current = current->Prev;
				current_index--;
			}
		}
				}
}
	
	
int main(){
	list my_list;
	int number=2;
	std::cout << "Test 1" << std::endl;
	create_empty(my_list);
	show(my_list);
	std::cout << "Test 2" << std::endl;
	add(my_list,{1.12,2.23,3.76}); //gnu++ 11
	add(my_list,{5.12,6.23,12.76}); 
	show(my_list);
	std::cout << "Test 3" << std::endl;
	create_empty(my_list);
	add(my_list,{1.12,2.23,3.76}); 
	add(my_list,{5.12,6.23,12.76}); 
	add(my_list,{51.12,62.23,122.76}); 
	insert(my_list,{1.1,2.2,3.4}, number);
	show(my_list);
	std::cout << my_list.size << std::endl;
	std::cout << "Test 4" << std::endl;
	remove(my_list, 1);
	show(my_list);
	
	
	
	
	
	return 0;
}
