#include <iostream>
#include <fstream>
#include <algorithm>
#include <bits/stdc++.h>
# define max 10

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

string negateCondition(string str) 
{
	int i;                                            //Function to negate assertion condition
	for(i=0;i<str.length();i++)
	{
		if(str[i]=='>')
		{
			str[i]='<';
			if (str[i+1]=='=')
			{	
				
				str.erase(i+1,1);
			}
		}
		else if(str[i]=='<')
		{
			str[i]='>';
			if(str[i+1]=='=')
			{
				str.erase(i+1,1);
				
			}
		}
				
		else if(str[i]=='&')str[i]='|';
		else if(str[i]=='|') str[i]='&';
		else if(str[i]=='=')
		{
			if (str[i+1]=='=')
			{
				str[i]='!';
				i++;
			}
			else if(str[i+1]=='<')
			{
				str[i]='>';
				str.erase(i,1);
			}
		}
	}
	return str;	
	
}
string get_variable(string str) //Getting the variables in the assume clauses
{
	int i=0;
	while(i<str.length())
	{
		if(str[i]=='(')
		{
			str.erase(i,1);
			while(str[i]!='>' && str[i]!='<' && str[i]!='=')
				i++;	
			
		}
		else
		{
			str.erase(i,1);
		}
		
	}
	return str;
}

int main(int argc, char** argv)
{
	int j=0, assume_count=0;
	string line,line2, mainLine;
	string type="int ";
	string temp=",";
	string str, str2, caller;	
	ofstream invInput1;
	ofstream invInput2;
	ofstream invgenInput1;
	ofstream invgenInput2;
	
	invgenInput1.open("input_to_invgen.c");
	invgenInput2.open("inverted_input_to_invgen.c");
	caller=argv[1];
	ifstream inFile(argv[1]); //Reading file name from command line
	if (!inFile.is_open() )
    {
    	cout<<"Can not open file\n";
    	return -1;
    }
	while(getline(inFile,line))
	{
		line2=trim(line);		
		if(line2.substr(0,6).compare("assume")==0) //for assume clauses
		{
			mainLine.append("void main(");
			mainLine.append(type);
			mainLine.append(get_variable(line));
			assume_count++;
			invInput1.open("invgenInput_Actual.c"); // for actual assert
			invInput2.open("invgenInput_Inverted.c"); // for inverted assert
			invInput1 << line << "\n";
			invInput2 << line << "\n";
			while(getline(inFile,line))
			{
				line2=trim(line);		
				if(line2.substr(0,6).compare("assume")==0) //for assume clauses
				{
					assume_count++;
					if((assume_count%2) !=0)
					{
						mainLine.append(temp);
						mainLine.append(type);
						mainLine.append(get_variable(line));
					}
				}
				if(line2.substr(0,6).compare("assert")==0)
				{
					invInput1 << line << "\n";

					str=line2.substr(6,line2.length()-7);
					str2=negateCondition(str);				
					invInput2 <<" assert "<< str2 << ";"<< "\n";
					invInput1 << "\n return 0; \n }";
					invInput2 << "\n return 0; \n }";
					break;
				}		
				else 
				{
					invInput1 << line << "\n";
					invInput2 << line << "\n";
				}
			}
			mainLine.append("){");
			invgenInput1 << mainLine <<"\n";
			invgenInput2 << mainLine <<"\n";
			
			invgenInput1.close();
			invgenInput2.close();
			invInput1.close();
			invInput2.close();

			system("cat invgenInput_Actual.c >> input_to_invgen.c");
			system("rm invgenInput_Actual.c");
			system("cat invgenInput_Inverted.c >> inverted_input_to_invgen.c");
			system("rm invgenInput_Inverted.c");

			system("./frontend -o input_to_invgen.pl -domain 2 input_to_invgen.c");
 			system("./invgen input_to_invgen.pl > output.txt");
 			system("mv input_to_invgen.pl GeneratedFiles/input_to_invgen.pl");
 			system("mv input_to_invgen.c GeneratedFiles/input_to_invgen.c");
 			system("./invariant_input 0"); //calling for the actual assert
 		 
		    system(("./insert_inv " + caller).c_str());

        	system("rm invariant_val.txt");
 			
			

			system ("./frontend -o inverted_input_to_invgen.pl -domain 2 inverted_input_to_invgen.c");
			system("./invgen inverted_input_to_invgen.pl > output.txt");
 			system("mv inverted_input_to_invgen.pl GeneratedFiles/inverted_input_to_invgen.pl");
 			system("mv inverted_input_to_invgen.c GeneratedFiles/inverted_input_to_invgen.c");
 			
 			system("./invariant_input 1");
  			system("rm invariant_val.txt");
		}
	
	}
	
	return 0;
}