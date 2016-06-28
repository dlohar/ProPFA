#include <iostream>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;
string trim(string const& str)    //Trim white space
{
   int first=0,last=str.length()-1;
  	while(str[first]==' ' || str[first]=='\t')
  	{
  		first++;
  	}
  	while(str[last]==' ' || str[last]=='\t' ) 
  	{
  		last--;
 	  }
  return str.substr(first, last-first+1);
}

int main(int argc, char** argv)
{
  int i=0;
	string line,line2,line_inv,move;
	ofstream prog;
  ifstream invariant("invariant_val.txt");
	move=argv[1];
  ifstream inFile(argv[1]); //Reading file name from command line
	if (!inFile.is_open() )
  {
    	cout<<"Can not open file\n";
    	return -1;
  }
  prog.open("program.c");
	getline(inFile,line);
	
	line2=trim(line);
  while(line2.substr(0,5).compare("while")!=0)
  {

    if(line2.substr(0,6).compare("assume")!=0) //for assume clauses
    {
      prog << line2 << "\n";
      getline(inFile,line);
      line2=trim(line);
    }

    else
    {
      getline(inFile,line);
      line2=trim(line);
    }

  }
  getline(invariant,line_inv);
  if(!line_inv.empty())
  {
    prog << "//@ loop invariant ";
   while(i<line_inv.length())
    {
      if(line_inv[i]=='-' && line_inv[i+1]=='>')
      {
        prog << ";\n";
        i=i+2;
        if(i<line_inv.length()-1)
          prog << "\n //@ loop invariant ";
      }
      else
        prog << line_inv[i];
        i++;
    }
    prog << "; \n";
  }
  prog << line <<"\n";
  while(getline(inFile,line))
    prog << line<<"\n";
  system(("mv program.c "+move).c_str());
  return 0;
}