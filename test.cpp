// #include <iostream>
// #include <string>
// #include <deque>
// #include <algorithm>
// #if 0 //CREATE A REAL STL EXAMPLE
// 	#include <map>
// 	#include <stack>
// 	#include <vector>
// 	namespace ft = std;
// #else
// 	#include "map.hpp"
// 	#include "stack.hpp"
// 	#include "vector.hpp"
// #endif

// int main ()
// {
// /*------------------------------------VECTOR-------------------------------------*/
//   // //////////////////////////   begin    /////////////////////////////////////
//   // ft::vector<int> myvector;
//   // for (int i=1; i<=5; i++) myvector.push_back(i);

//   // std::cout << "myvector contains:";
//   // for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
//   //   std::cout << ' ' << *it;
//   // std::cout << '\n';
//   // //////////////////////////  end begin   /////////////////////////////////////
  
//   // /////////////////////////   end      /////////////////////////////////////
//   // ft::vector<int> myvector;
//   // for (int i=1; i<=5; i++) myvector.push_back(i);

//   // std::cout << "myvector contains:";
//   // for (ft::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
//   //   std::cout << ' ' << *it;
//   // std::cout << '\n';
//   // //////////////////////////   end to end   /////////////////////////////////

//   ////////////////////////////   rbegin     /////////////////////////////////
//   // ft::vector<int> myvector (5);  // 5 default-constructed ints
//   // int i=0;
//   // ft::vector<int>::reverse_iterator rit = myvector.rbegin();
//   // for (; rit!= myvector.rend(); ++rit)
//   //   *rit = ++i;
//   // std::cout << "myvector contains:";
//   // for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
//   //   std::cout << ' ' << *it;
//   // std::cout << '\n';
//   // ////////////////////////////   end rbegin     ////////////////////////////////////

//   /////////////////////////////// rend  //////////////////////////////////
//   // ft::vector<int> myvector (5);  // 5 default-constructed ints
//   // ft::vector<int>::reverse_iterator rit = myvector.rbegin();
//   // int i=0;
//   // for (rit = myvector.rbegin(); rit!= myvector.rend(); ++rit)
//   //   *rit = ++i;
//   // std::cout << "myvector contains:";
//   // for (ft::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
//   //   std::cout << ' ' << *it;
//   // std::cout << '\n';
//   /////////////////////////////// and rend ///////////////////////////////

//   /////////////////////////////// size ///////////////////////////////////
//   // ft::vector<int> myints;
//   // std::cout << "0. size: " << myints.size() << '\n';
//   // for (int i=0; i<10; i++) myints.push_back(i);
//   // std::cout << "1. size: " << myints.size() << '\n';
//   // myints.insert (myints.end(),10,100);
//   // std::cout << "2. size: " << myints.size() << '\n';
//   // myints.pop_back();
//   // std::cout << "3. size: " << myints.size() << '\n';
//   /////////////////////////////// and size ///////////////////////////////

//   /////////////////////////////// max_size capacity ///////////////////////////////
//   // ft::vector<int> myvector;
//   // // set some content in the vector:
//   // for (int i=0; i<100; i++) myvector.push_back(i);
//   // std::cout << "size: " << myvector.size() << "\n";
//   // std::cout << "capacity: " << myvector.capacity() << "\n";
//   // std::cout << "max_size: " << myvector.max_size() << "\n";
//   /////////////////////////////// and max_size ///////////////////////////////
  
//   /////////////////////////////// resize capacity ///////////////////////////////
//   // ft::vector<int> myvector;
//   // // set some initial content:
//   // for (int i=1;i<10;i++) myvector.push_back(i);
//   // myvector.resize(5);
//   // myvector.resize(8,100);
//   // myvector.resize(12);
//   // std::cout << "myvector contains:";
//   // for (int i=0;i<myvector.size();i++)
//   //   std::cout << ' ' << myvector[i];
//   // std::cout << '\n';
//   /////////////////////////////// and resize  capacity ///////////////////////////////

//   /////////////////////////////// empty ///////////////////////////////
//   // ft::vector<int> myvector;
//   // int sum (0);
//   // for (int i=1;i<=10;i++) myvector.push_back(i);
//   // while (!myvector.empty())
//   // {
//   //   sum += myvector.back();
//   //   myvector.pop_back();
//   // }
//   // std::cout << "total: " << sum << '\n';
//   /////////////////////////////// and empty ///////////////////////////////

//   /////////////////////////////// reserve //////////////////////////////////
//   // ft::vector<int>::size_type sz;
//   // ft::vector<int> foo;
//   // sz = foo.capacity();
//   // std::cout << "making foo grow:\n";
//   // for (int i=0; i<100; ++i) {
//   //   foo.push_back(i);
//   //   if (sz!=foo.capacity()) {
//   //     sz = foo.capacity();
//   //     std::cout << "capacity changed: " << sz << '\n';
//   //   }
//   // }

//   // ft::vector<int> bar;
//   // sz = bar.capacity();
//   // bar.reserve(100);   // this is the only difference with foo above
//   // std::cout << "making bar grow:\n";
//   // for (int i=0; i<100; ++i) {
//   //   bar.push_back(i);
//   //   if (sz!=bar.capacity()) {
//   //     sz = bar.capacity();
//   //     std::cout << "capacity changed: " << sz << '\n';
//   //   }
//   // }
//   /////////////////////////////// and reserve ///////////////////////////////

//   /////////////////////////////// front ///////////////////////////////
//   // ft::vector<int> myvector;
//   // myvector.push_back(78);
//   // myvector.push_back(16);
//   // // now front equals 78, and back 16
//   // myvector.front() -= myvector.back();
//   // std::cout << "myvector.front() is now " << myvector.front() << '\n';
//   /////////////////////////////// and front ///////////////////////////

//   /////////////////////////////// back //////////////////////////////
//   // ft::vector<int> myvector;
//   // myvector.push_back(10);
//   // while (myvector.back() != 0)
//   // {
//   //   myvector.push_back ( myvector.back() -1 );
//   // }
//   // std::cout << "myvector contains:";
//   // for (unsigned i=0; i<myvector.size() ; i++)
//   //   std::cout << ' ' << myvector[i];
//   // std::cout << '\n';
//   /////////////////////////////// and back ///////////////////////////

//   /////////////////////////////// insert ///////////////////////////
//   // ft::vector<int> myvector (3,100);
//   // ft::vector<int>::iterator it;

//   // it = myvector.begin();
//   // it = myvector.insert ( it , 200 );

//   // myvector.insert (it,2,300);

//   // // "it" no longer valid, get a new one:
//   // it = myvector.begin();

//   // ft::vector<int> anothervector (2,400);
//   // myvector.insert (it+2,anothervector.begin(),anothervector.end());

//   // int myarray [] = { 501,502,503 };
//   // myvector.insert (myvector.begin(), myarray, myarray+3);

//   // std::cout << "myvector contains:";
//   // for (it=myvector.begin(); it<myvector.end(); it++)
//   //   std::cout << ' ' << *it;
//   // std::cout << '\n';
//   /////////////////////////////// and insert ///////////////////////////

//   /////////////////////////////// erase ///////////////////////////
//   // ft::vector<int> myvector;
//   // // set some values (from 1 to 10)
//   // for (int i=1; i<=10; i++) myvector.push_back(i);
//   // // erase the 6th element
//   // myvector.erase (myvector.begin()+5);
//   // // erase the first 3 elements:
//   // myvector.erase (myvector.begin(),myvector.begin()+3);
//   // std::cout << "myvector contains:";
//   // for (unsigned i=0; i<myvector.size(); ++i)
//   //   std::cout << ' ' << myvector[i];
//   // std::cout << '\n';
//   /////////////////////////////// and erase ///////////////////////////

//   /////////////////////////////// swap ///////////////////////////
//   // ft::vector<int> foo (3,100);   // three ints with a value of 100
//   // ft::vector<int> bar (5,200);   // five ints with a value of 200
//   // foo.swap(bar);
//   // std::cout << "foo contains:";
//   // for (unsigned i=0; i<foo.size(); i++)
//   //   std::cout << ' ' << foo[i];
//   // std::cout << '\n';
//   // std::cout << "bar contains:";
//   // for (unsigned i=0; i<bar.size(); i++)
//   //   std::cout << ' ' << bar[i];
//   // std::cout << '\n';
//   /////////////////////////////// and swap ///////////////////////

//   /////////////////////////////// clear ///////////////////////
//   // ft::vector<int> myvector;
//   // myvector.push_back (100);
//   // myvector.push_back (200);
//   // myvector.push_back (300);

//   // std::cout << "myvector contains:";
//   // for (unsigned i=0; i<myvector.size(); i++)
//   //   std::cout << ' ' << myvector[i];
//   // std::cout << '\n';

//   // myvector.clear();
//   // myvector.push_back (1101);
//   // myvector.push_back (2202);

//   // std::cout << "myvector contains:";
//   // for (unsigned i=0; i<myvector.size(); i++)
//   //   std::cout << ' ' << myvector[i];
//   // std::cout << '\n';
//   /////////////////////////////// and clear ///////////////////////

//   /*------------------------------------------------end vector---------------------------------------*/

//   /*------------------------------------------------start MAP----------------------------------------*/

//   /////////////////////////////////////////////  begin  /////////////////////////////////////////
//   // ft::map<char,int> mymap;
//   // mymap['b'] = 100;
//   // mymap['a'] = 200;
//   // mymap['c'] = 300;
//   // // show content:
//   // for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';
//   /////////////////////////////////////////////  end begin  ///////////////////////////////////////

//   /////////////////////////////////////////////  end  /////////////////////////////////////////
//   // ft::map<char,int> mymap;
//   // mymap['b'] = 100;
//   // mymap['a'] = 200;
//   // mymap['c'] = 300;
//   // // show content:
//   // for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';
//   /////////////////////////////////////////////  end to end  ////////////////////////////////////

//   /////////////////////////////////////////////  rbegin  ////////////////////////////////////
//   // ft::map<char,int> mymap;
//   // mymap['x'] = 100;
//   // mymap['y'] = 200;
//   // mymap['z'] = 300;

//   // // show content:
//   // ft::map<char,int>::reverse_iterator rit;
//   // for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
//   //   std::cout << rit->first << " => " << rit->second << '\n';
//   /////////////////////////////////////////////  end rbegin  ////////////////////////////////////

//   /////////////////////////////////////////////  rend  ////////////////////////////////////
//   // ft::map<char,int> mymap;
//   // mymap['x'] = 100;
//   // mymap['y'] = 200;
//   // mymap['z'] = 300;
//   // // show content:
//   // ft::map<char,int>::reverse_iterator rit;
//   // for (rit=mymap.rbegin(); rit!=mymap.rend(); ++rit)
//   //   std::cout << rit->first << " => " << rit->second << '\n';
//   /////////////////////////////////////////////  end rend ////////////////////////////////////

//   /////////////////////////////////////////////  empty  ////////////////////////////////////
//   // ft::map<char,int> mymap;
//   // mymap['a']=10;
//   // mymap['b']=20;
//   // mymap['c']=30;

//   // while (!mymap.empty())
//   // {
//   //   std::cout << mymap.begin()->first << " => " << mymap.begin()->second << '\n';
//   //   mymap.erase(mymap.begin());
//   // }
//   /////////////////////////////////////////////  end empty ////////////////////////////////////

//   /////////////////////////////////////////////  size ////////////////////////////////////
//   // ft::map<char,int> mymap;
//   // mymap['a']=101;
//   // mymap['b']=202;
//   // mymap['c']=302;

//   // std::cout << "mymap.size() is " << mymap.size() << '\n';
//   /////////////////////////////////////////////  end szie ////////////////////////////////////

//   /////////////////////////////////////////////  max_szie ////////////////////////////////////
//   // int i;
//   // ft::map<int,int> mymap;
//   // if (mymap.max_size()>1000)
//   // {
//   //   for (i=0; i<1000; i++) mymap[i]=0;
//   //   std::cout << "The map contains 1000 elements.\n";
//   // }
//   // else std::cout << "The map could not hold 1000 elements.\n";
//   /////////////////////////////////////////////  end max_szie //////////////////////////////////

//   /////////////////////////////////////////////  insert //////////////////////////////////
//   // ft::map<char,int> mymap;

//   // // first insert function version (single parameter):
//   // mymap.insert ( ft::pair<char,int>('a',100) );
//   // mymap.insert ( ft::pair<char,int>('z',200) );

//   // ft::pair<ft::map<char,int>::iterator,bool> ret;
//   // ret = mymap.insert ( ft::pair<char,int>('z',500) );
//   // if (ret.second==false) {
//   //   std::cout << "element 'z' already existed";
//   //   std::cout << " with a value of " << ret.first->second << '\n';
//   // }

//   // // second insert function version (with hint position):
//   // ft::map<char,int>::iterator it = mymap.begin();
//   // mymap.insert (it, ft::pair<char,int>('b',300));  // max efficiency inserting
//   // mymap.insert (it, ft::pair<char,int>('c',400));  // no max efficiency inserting

//   // // third insert function version (range insertion):
//   // ft::map<char,int> anothermap;
//   // anothermap.insert(mymap.begin(),mymap.find('c'));

//   // // showing contents:
//   // std::cout << "mymap contains:\n";
//   // for (it=mymap.begin(); it!=mymap.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';

//   // std::cout << "anothermap contains:\n";
//   // for (it=anothermap.begin(); it!=anothermap.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';
//   /////////////////////////////////////////////  end insert //////////////////////////////////

//   /////////////////////////////////////////////  erase //////////////////////////////////
//   // ft::map<char,int> mymap;
//   // ft::map<char,int>::iterator it;
//   // // insert some values:
//   // mymap['a']=10;
//   // mymap['b']=20;
//   // mymap['c']=30;
//   // mymap['d']=40;
//   // mymap['e']=50;
//   // mymap['f']=60;

//   // it=mymap.find('b');
//   // mymap.erase (it);                   // erasing by iterator
//   // mymap.erase ('c');                  // erasing by key
//   // it=mymap.find ('e');
//   // mymap.erase ( it, mymap.end() );    // erasing by range
//   // // show content:
//   // for (it=mymap.begin(); it!=mymap.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';
//   /////////////////////////////////////////////  end erase //////////////////////////////////

//   /////////////////////////////////////////////  end erase //////////////////////////////////
//   // ft::map<char,int> foo,bar;

//   // foo['x']=100;
//   // foo['y']=200;

//   // bar['a']=11;
//   // bar['b']=22;
//   // bar['c']=33;

//   // foo.swap(bar);

//   // std::cout << "foo contains:\n";
//   // for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';

//   // std::cout << "bar contains:\n";
//   // for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';
//   /////////////////////////////////////////////  end erase //////////////////////////////////

//   /////////////////////////////////////////////  swap //////////////////////////////////
//   // ft::map<char,int> foo,bar;
//   // foo['x']=100;
//   // foo['y']=200;
//   // bar['a']=11;
//   // bar['b']=22;
//   // bar['c']=33;
//   // foo.swap(bar);
//   // std::cout << "foo contains:\n";
//   // for (ft::map<char,int>::iterator it=foo.begin(); it!=foo.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';
//   // std::cout << "bar contains:\n";
//   // for (ft::map<char,int>::iterator it=bar.begin(); it!=bar.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';
//   /////////////////////////////////////////////  end swap //////////////////////////////////

//   /////////////////////////////////////////////  lower_bound //////////////////////////////////
//   // ft::map<char,int> mymap;
//   // ft::map<char,int>::iterator itlow,itup;
//   // mymap['a']=20;
//   // mymap['b']=40;
//   // mymap['c']=60;
//   // mymap['d']=80;
//   // mymap['e']=100;
//   // itlow=mymap.lower_bound ('b');  // itlow points to b
//   // itup=mymap.upper_bound ('d');   // itup points to e (not d!)
//   // mymap.erase(itlow,itup);        // erases [itlow,itup)
//   // // print content:
//   // for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';
//   /////////////////////////////////////////////  end lower_bound ///////////////////////////////

//   /////////////////////////////////////////////  upper_bound ///////////////////////////////
//   // ft::map<char,int> mymap;
//   // ft::map<char,int>::iterator itlow,itup;
//   // mymap['a']=20;
//   // mymap['b']=40;
//   // mymap['c']=60;
//   // mymap['d']=80;
//   // mymap['e']=100;
//   // itlow=mymap.lower_bound ('b');  // itlow points to b
//   // itup=mymap.upper_bound ('d');   // itup points to e (not d!)
//   // mymap.erase(itlow,itup);        // erases [itlow,itup)
//   // // print content:
//   // for (ft::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
//   //   std::cout << it->first << " => " << it->second << '\n';
//   /////////////////////////////////////////////  end upper_bound ///////////////////////////////

//   /////////////////////////////////////////////  find ///////////////////////////////
//   // ft::map<char,int> mymap;
//   // ft::map<char,int>::iterator it;
//   // mymap['a']=50;
//   // mymap['b']=100;
//   // mymap['c']=150;
//   // mymap['d']=200;
//   // it = mymap.find('b');
//   // if (it != mymap.end())
//   //   mymap.erase (it);
//   // // print content:
//   // std::cout << "elements in mymap:" << '\n';
//   // std::cout << "a => " << mymap.find('a')->second << '\n';
//   // std::cout << "c => " << mymap.find('c')->second << '\n';
//   // std::cout << "d => " << mymap.find('d')->second << '\n'; 
//   /////////////////////////////////////////////  end find ///////////////////////////////

//   /*------------------------------------------------end MAP-----------------------------------------*/

//   /*------------------------------------------------stack-----------------------------------------*/


//   /////////////////////////////////////////////  constaructer ///////////////////////////////
//   // ft::vector<int> myvector (2,200);        // vector with 2 elements

//   // ft::stack<int> first;                    // empty stack
//   // ft::stack<int> second (myvector);         // stack initialized to copy of deque

//   // ft::stack<int,ft::vector<int> > third;  // empty stack using vector

//   // std::cout << "size of first: " << first.size() << '\n';
//   // std::cout << "size of second: " << second.size() << '\n';
//   // std::cout << "size of third: " << third.size() << '\n';
//   /////////////////////////////////////////////  end constaructer ///////////////////////////////

//   /////////////////////////////////////////////  embty ///////////////////////////////
//   // ft::stack<int> mystack;
//   // int sum (0);
//   // for (int i=1;i<=10;i++) mystack.push(i);
//   // while (!mystack.empty())
//   // {
//   //    sum += mystack.top();
//   //    mystack.pop();
//   // }
//   // std::cout << "total: " << sum << '\n';
//   /////////////////////////////////////////////  end embty  ///////////////////////////////

//   /////////////////////////////////////////////  size  ///////////////////////////////
//   // ft::stack<int> myints;
//   // std::cout << "0. size: " << myints.size() << '\n';
//   // for (int i=0; i<5; i++) myints.push(i);
//   // std::cout << "1. size: " << myints.size() << '\n';
//   // myints.pop();
//   // std::cout << "2. size: " << myints.size() << '\n';
//   /////////////////////////////////////////////  end size ///////////////////////////////

//   /////////////////////////////////////////////  top ///////////////////////////////
//   // ft::stack<int> mystack;
//   // mystack.push(10);
//   // mystack.push(20);
//   // mystack.top() -= 5;
//   // std::cout << "mystack.top() is now " << mystack.top() << '\n';
//   /////////////////////////////////////////////  end top ///////////////////////////////

//   /////////////////////////////////////////////  push ///////////////////////////////
//   // ft::stack<int> mystack;
//   // for (int i=0; i<5; ++i) mystack.push(i);
//   // std::cout << "Popping out elements...";
//   // while (!mystack.empty())
//   // {
//   //   std::cout << ' ' << mystack.top();
//   //   mystack.pop();
//   // }
//   // std::cout << '\n';
//   /////////////////////////////////////////////  end push ///////////////////////////////

//   /////////////////////////////////////////////  pop ///////////////////////////////
//   // ft::stack<int> mystack;
//   // for (int i=0; i<5; ++i) mystack.push(i);
//   // std::cout << "Popping out elements...";
//   // while (!mystack.empty())
//   // {
//   //   std::cout << ' ' << mystack.top();
//   //   mystack.pop();
//   // }
//   // std::cout << '\n';
//   /////////////////////////////////////////////  end pop ///////////////////////////////

//   /*------------------------------------------------end stack-----------------------------------------*/
//   return 0;
// }