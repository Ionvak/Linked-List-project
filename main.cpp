#include <iostream>
#include <string>
#include "sequence.hpp"
#include "split.hpp"






int main()
{
 Sequence<std::string,int> list1;
 std::string returned;


    //****************************** test zone 1 ****************************  (Testing following functions: PushBack, Print, GetLast, GetFirst, GetInfo.)
    std::cout << "-Test Zone 1-\n" << std::endl;

    if(list1.GetFirst() != nullptr) std::cerr << "GetFirst returns non-Null pointer in empty list." << std::endl;
    if(list1.GetLast() != nullptr) std::cerr << "GetLast returns non-Null pointer in empty list." << std::endl;
    if(list1.GetInfo(0,returned)) std::cerr << "Element found in empty list." << std::endl;
    list1.Print();
    std::cout << '\n' << std::endl;

    list1.PushBack("ABC",1);
    if(!list1.GetInfo(1,returned)) std::cerr << "The element with key 1 can't be found despite being added to the list." << std::endl;
    if(returned != "ABC") std::cerr << "Info returned by GetInfo function is not correct." << std::endl;
    if(list1.GetFirst() != list1.GetLast()) std::cerr << "The head and the tail don't point to the same element despite there only being 1 element in the list." << std::endl;
    list1.Print();
    std::cout << '\n' << std::endl;

    list1.PushBack("EFG",14);
    list1.PushBack("HIJ",77);
    if(!list1.GetInfo(77,returned)) std::cerr << "The element with key 77 can't be found despite being added to the list." << std::endl;
    if(returned != "HIJ") std::cerr << "Info returned by GetInfo function is not correct." << std::endl;
    list1.Print();
    std::cout << '\n' << std::endl;


    //****************************** test zone 2 ****************************  (Testing following functions: IsEmpty, Size, PopBack, LookFor, copy constructor.)
    std::cout << "-Test Zone 2-\n" << std::endl;

    Sequence<std::string,int> list2(list1);
    if(list2.Size() != 3) std::cerr << "Number of elements not equal to 3 although there are 3 elements." << std::endl;
    if(!list2.PopBack()) std::cerr << "2nd PopBack operation unsuccessful." << std::endl;
    if(list2.Size() != 2) std::cerr << "Number of elements not equal to 2 although there are 3 elements." << std::endl;
    if(!list2.PopBack()) std::cerr << "3rd PopBack operation unsuccessful." << std::endl;
    if(list2.Size() != 1) std::cerr << "Number of elements not equal to 1 although there are 3 elements." << std::endl;
    if(!list2.PopBack()) std::cerr << "4th PopBack operation unsuccessful." << std::endl;
    if(list2.Size()) std::cerr << "Incorrect number of elements returned by Size." << std::endl;
    if(list2.PopBack()) std::cerr << "Successful PopBack operation on empty list." << std::endl;

    if(list1.IsEmpty()) std::cerr << "List defined as empty despite having elements inside." << std::endl;
    if(!list2.IsEmpty()) std::cerr << "Empty list defined as having elements." << std::endl;

    if(list1.GetFirst() != list1.LookFor(77)) std::cerr << "LookFor doesn't find the correct element." << std::endl;
    if(list1.GetLast() != list1.LookFor(1)) std::cerr << "LookFor doesn't return the correct element." << std::endl;
    if(nullptr != list1.LookFor(4)) std::cerr << "Non-existent element returned by LookFor." << std::endl;

    list1.Print();
    std::cout << '\n';
    list2.Print();
    std::cout << '\n' << std::endl;


    //****************************** test zone 3 ****************************  (Testing following functions: PushFront, PopFront, operator=, operator==, operator!=.)
    std::cout << "-Test Zone 3-\n" << std::endl;

    Sequence<std::string,int> list3;
    list1 = list2;
    if(list1 != list2) std::cerr << "Equal lists returned as unequal by != when lists are empty." << std::endl;
    if(!(list1 == list2)) std::cerr << "Equal lists returned as unequal by == operator when lists are empty." << std::endl;
    list1.PushFront("A",1);
    list2.PushFront("C",1);
    if(list1 == list2) std::cerr << "Unequal lists returned as equal by == operator when elements have same key but different info." << std::endl;
    if(!(list1 != list2)) std::cerr << "Unequal lists returned as equal by != when elements have same key but different info." << std::endl;

    if(!list2.PopFront()) std::cerr << "Unsuccessful PopFront operation on list2 with 1 element." << std::endl;
    if(!list1.PopFront()) std::cerr << "Unsuccessful PopFront operation on list1 with 1 element." << std::endl;
    if(list2.PopFront()) std::cerr << "Unsuccessful PopFront operation on list2 with no elements." << std::endl;

    list1.PushFront("C",1);
    list3 = list2 = list1;
    if(list1 != list2 || list1 != list3 || list2 != list2) std::cerr << "Assignment operator unsuccessful when called with more than 2 operands." << std::endl;
    list1.Clear();
    list3 = list2 = list1;
    if(!list1.IsEmpty() || !list2.IsEmpty() || !list3.IsEmpty()) std::cerr << "Assignment operator failed at assigning empty list when called with more than 2 operands." << std::endl;

    list1.PushFront("B",2);
    list2.PushFront("B",3);
    if(list1 == list2) std::cerr << "Unequal lists returned as equal by == operator when elements have same info but different key." << std::endl;
    if(!(list1 != list2)) std::cerr << "Unequal lists returned as equal by != when elements have same info but different key." << std::endl;

    list1 = list2;
    if(list1 != list2) std::cerr << "Equal lists returned as unequal by !=." << std::endl;
    if(!(list1 == list2)) std::cerr << "Equal lists returned as unequal by == operator." << std::endl;

    list1.Print();
    std::cout << '\n';
    list2.Print();
    std::cout << '\n';
    list3.Print();
    std::cout << '\n' << std::endl;



    //****************************** test zone 4 ****************************  (Testing following functions: Insert, Remove, Clear, Invert, LookThrough.)
    std::cout << "-Test Zone 4-\n" << std::endl;

    if(!list1.Remove(3)) std::cerr << "Remove can't delete element from list1 with single element." << std::endl;
    if(list1.Remove(3)) std::cerr << "Remove tries to delete element from empty list1." << std::endl;
    if(!list2.Clear()) std::cerr << "list2 with single element could not be cleared." << std::endl;
    if(list2.Clear()) std::cerr << "list2 not working with empty list2." << std::endl;

    list1.Insert(1,"TUV",3);
    if(!list1.IsEmpty()) std::cerr << "Element inserted in list1 despite list being empty." << std::endl;
    list1.PushBack("TUV",3);
    list1.Insert(1,"TUV",3);
    if(list1.GetFirst() != list1.GetLast()) std::cerr << "Element inserted in list1 despite key not being found." << std::endl;
    list1.Insert(3,"XYZ",1);
    if(list1.LookFor(1) == nullptr) std::cerr << "Element not inserted in list1 with 1 element despite key being found." << std::endl;
    list1.Insert(3,"POV",2);
    if(list1.LookFor(2) == nullptr) std::cerr << "Element not inserted in list1 with multiple elements despite key being found." << std::endl;

    list1.Remove(3);
    if(list1.GetFirst() != list1.LookFor(2)) std::cerr << "Head pointer lost with removal of first element using Remove." << std::endl;
    list1.Remove(1);
    if(list1.GetLast() != list1.LookFor(2)) std::cerr << "Tail pointer lost with removal of last element using Remove." << std::endl;

    list1.PushBack("AC",4);
    list1.PushFront("DC",5);
    if(!list1.Remove(2)) std::cerr << "Remove can't delete element from list1 with multiple elements." << std::endl;
    if(list1.Remove(2)) std::cerr << "Remove tries to delete non-existent element." << std::endl;

    list1.Print();
    std::cout << '\n';
    list2.Print();
    std::cout << '\n' << std::endl;

    list1.Clear();
    list1.PushFront("A",1);
    list1.PushFront("B",2);
    list1.PushFront("C",3);
    list1.Invert();
    if(list1.GetFirst() != list1.LookFor(3) || list1.GetLast() != list1.LookFor(1)) std::cerr << "list1 could not be inverted." << std::endl;
    list1.Invert();
    if(list1.GetFirst() != list1.LookFor(1) || list1.GetLast() != list1.LookFor(3)) std::cerr << "list1 could not be re-inverted." << std::endl;
    list1.PopFront();
    list1.PopFront();
    if(list1.Invert()) std::cerr << "List with 1 element was inverted." << std::endl;
    list1.PopFront();
    if(list1.Invert()) std::cerr << "List with no elements was inverted." << std::endl;

    int i=0;
    while(i++ < 3) list1.PushFront(std::to_string(i),i);
    i=0;
    while(i++ < 3) list1.PushFront(std::to_string(i),i);

    Sequence<std::string,int>::Iterator temp = list1.LookFor(3);
    if(list1.LookThrough(3,list1.GetFirst(),&temp) != nullptr) std::cerr << "Non-Null pointer returned despite no element being found." << std::endl;
    temp++;
    if(list1.LookThrough(3,list1.GetFirst(),&temp) != list1.LookFor(3)) std::cerr << "LookThrough couldn't find element in its range when starting from list Head." << std::endl;
    temp++;
    if(list1.LookThrough(3,&temp,nullptr) != list1.GetLast()) std::cerr << "LookThrough couldn't find element in its range when starting from non-Head Node." << std::endl;

    list1.Print();
    std::cout << '\n';
    list2.Print();
    std::cout << '\n' << std::endl;


    //****************************** test zone 5 ****************************  (Testing following functions: Count, operator+.)
    std::cout << "-Test Zone 5-\n" << std::endl;

    list1.Clear();
    if(list1.Count(1)) std::cerr << "Empty list returned non-zero count." << std::endl;
    list1.PushBack("A",1);
    if(list1.Count(1) != 1) std::cerr << "Element with correct key not counted in list with 1 element." << std::endl;
    list1.PushBack("B",1);
    list1.PushBack("C",2);
    if(list1.Count(1) != 2) std::cerr << "Incorrect number of elements with correct key returned by Count in list with multiple elements." << std::endl;

    list2 = list2 + list1;
    if(list1 != list2) std::cerr << "Concatenation of list1 unto list2 unsuccessful." << std::endl;
    if(list2.Size() != 3) std::cerr << "Size after concatenation of list1 unto list2 incorrect." << std::endl;
    list2 = list1 + list2;
    if(list2.Size() != 6) std::cerr << "Size after addition of list1 and list2 incorrect." << std::endl;

    list1.Clear();
    list2.Clear();
    list3.Clear();
    list2 = list1 + list2 + list3;
    if(!list2.IsEmpty()) std::cerr << "Addition of empty lists results in non-empty list ." << std::endl;

    list1.PushBack("a",1);
    list2.PushBack("b",2);
    list3.PushBack("c",3);
    list3 = list1 + list2 + list3;
    if(list3.Size() != 3) std::cerr << "Incorrect size after addition of more than two lists." << std::endl;

    list1.Print();
    std::cout << '\n';
    list2.Print();
    std::cout << '\n';
    list3.Print();
    std::cout << '\n' << std::endl;


    //****************************** test zone 6 ****************************  (Testing following functions: split_pos, split_key.)
    std::cout << "-Test Zone 6-\n" << std::endl;

    list3.Clear();
    while(i++ < 3) list3.PushFront(std::to_string(i),i);
    i=0;
    while(i++ < 3) list3.PushFront(std::to_string(i),i);
    i=0;
    while(i++ < 3) list3.PushFront(std::to_string(i),i);
    i=0;
    while(i++ < 3) list3.PushFront(std::to_string(i),i);

    std::cout << "Lists 3,1,2 before splis_pos:" << std::endl;
    list3.Print();
    std::cout << '\n';
    list1.Print();
    std::cout << '\n';
    list2.Print();
    std::cout << '\n' << std::endl;

    split_pos(list3,8,1,2,3,list1,list2);

    std::cout << "Lists 3,1,2 after splis_pos:" << std::endl;
    list3.Print();
    std::cout << '\n';
    list1.Print();
    std::cout << '\n';
    list2.Print();
    std::cout << '\n' << std::endl;

    i=0;
    list3.Clear();
    while(i++ < 3) list3.PushFront(std::to_string(i),i);
    i=0;
    while(i++ < 3) list3.PushFront(std::to_string(i),i);
    i=0;
    while(i++ < 3) list3.PushFront(std::to_string(i),i);
    i=0;
    while(i++ < 3) list3.PushFront(std::to_string(i),i);

    std::cout << "Lists 3,1,2 before splis_pos:" << std::endl;
    list3.Print();
    std::cout << '\n';
    list1.Print();
    std::cout << '\n';
    list2.Print();
    std::cout << '\n' << std::endl;

    split_key(list3,2,3,1,2,3,list1,list2);

    std::cout << "Lists 3,1,2 after splis_pos:" << std::endl;
    list3.Print();
    std::cout << '\n';
    list1.Print();
    std::cout << '\n';
    list2.Print();
    std::cout << '\n' << std::endl;

    std::cout << "\nEnd of Tests (^w^)" << std::endl;

    return 0;
}
