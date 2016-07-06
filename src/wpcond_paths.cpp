#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include <stdio.h>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>   /* For open(), creat() */
#include "path.h"
using namespace std;


/* Unrolling purpose*/
class while_blocks{
    public: int start;
    public: int end;
    public: int unroll_no; //user input
};
class lex_class{
    public: string value; //value: operands/operators
    public: string type; //type: token type
};
//Separating if-else blocks
class sub_block{
    public: int start_at;
    public: int end_at;
    public: string cond; //cond <- if/else condition
};
//Main if/else block 
class block{
    public: int mark;
    public: int start_at;
    public: int end_at;
    public: vector<sub_block> blocks; //list of each subblock
    public: block(){
        start_at = -1;
        end_at =-1;
        blocks.clear();
    }

};


int wp_count =0;
std::vector<lex_class> unroll_list; //This list contains all the while loops in terms of 'if's
std::vector<lex_class> list; // On this list extraction of path will work.
vector<block> block_list; //list of all if/else blocks and each block will contain subblocks


bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}


bool printprobs(){
    int i;
    string delimiter = ":";
    string line;
    ifstream pathprobsfile ("pathprobs.txt");
    float final_prob;
    std::vector<lex_class> list0;
    lex_class lex_object;
    // parsing the lexical file and saving the tokens with type in the lex_class list0.

    ifstream pathsfile ("ifpaths.txt");
    list0.clear();
    if (pathsfile.is_open())
    {

        i=0;
        while ( getline (pathsfile,line) )
        {
            lex_object.value= line.substr(0, line.find(delimiter));
            lex_object.type= line.substr(line.find(delimiter)+1, line.length());
            list0.push_back(lex_object);
            //cout << list0[i].value << "\t\t" << list0[i].type << endl;
            i=i+1;
        }
        pathsfile.close();
    }
    final_prob=0;
    cout << "Path probability of : "<<endl;
    for(i=0;i<list0.size();i++){
        cout << list0[i].value << "\t" << list0[i].type << endl;
        final_prob+=::atof(list0[i].type.c_str());
    }
    cout<<"Confidence Measure of program is " << final_prob << endl;

    list0.clear();
    if (pathprobsfile.is_open())
    {

        i=0;
        while ( getline (pathprobsfile,line) )
        {
            lex_object.value= line.substr(0, line.find(delimiter));
            lex_object.type= line.substr(line.find(delimiter)+1, line.length());
            list0.push_back(lex_object);
            //cout << list0[i].value << "\t\t" << list0[i].type << endl;
            i=i+1;
        }
        pathprobsfile.close();
    }


    final_prob=0;
    cout << "Success probability of   : "<<endl;
    for(i=0;i<list0.size();i++){
        cout << list0[i].value << "\t" << list0[i].type << endl;
        final_prob+=::atof(list0[i].type.c_str());
    }

    cout<<"Failure probability of program is " << 1-final_prob << endl;

    return 0;
}
//populate block_list
int get_blocks(std::vector<lex_class> list,int k){
    int braces;
    braces=0;   
    block each_block; //for each main if block
    sub_block new_sub_block; //for each sub if/else blocks
    int i;
    i=0; 
    int curves;
    for(i=k;i<list.size();i++){
        if(list.at(i).type=="IF"){  //when starting of the main if block is found
            each_block.start_at=i;  //starting of main if block
            each_block.mark=-1;
            curves=0;
            while(list.at(i).type!="("){ // need to consider if the flower braces are not there
                i++;
            }
            
            new_sub_block.start_at = i;
            new_sub_block.cond = "";
            new_sub_block.cond = new_sub_block.cond + list.at(i).value;
            i++;
            curves++;
            while(curves>0){
               if(list.at(i).type=="(") {
                   curves++;
               }else if (list.at(i).type==")"){
                   curves--;
               }
               new_sub_block.cond = new_sub_block.cond + list.at(i).value;  //condition of sub-block is saved
               i++;
            }
            

            while(list.at(i).type=="SPACE" || list.at(i).type=="ENTER"){
                i++;
            }
            if(list.at(i).type!="{"){
                new_sub_block.start_at = i;     //start of sub-block
                while(list.at(i).type!=";"){
                    i++;
                }
                new_sub_block.end_at = i;       //end of sub-block
                each_block.end_at = i;          //assumed end of main block.since we dont know if there are more sub-blocks
                i++;
            }else{
                braces++;
                i++;
                new_sub_block.start_at = i;     //start of sub-block
                while(braces>0){
                    if(list.at(i).type=="{"){
                        braces++;
                    }else if(list.at(i).type=="}"){
                        braces--;
                    }
                    if(list.at(i).type=="IF"){
                        i= get_blocks(list,i);  //calling the get_blocks func if the nested main block is present
                    }else{
                        i++;
                    }
                    
                }
                new_sub_block.end_at = i-2; //end of sub-block
                each_block.end_at = i-2;    //assumed end of main block.since we dont know if there are more sub-blocks
            }
            each_block.blocks.push_back(new_sub_block);

            while(1){
                while(list.at(i).type=="SPACE" || list.at(i).type=="ENTER"){
                    i++;
                }
                if(list.at(i).type=="ELSE"){
                    
                    i++;
                    while(list.at(i).type=="SPACE" || list.at(i).type=="ENTER"){
                        i++;
                    }
                    if(list.at(i).type=="IF"){
                      
                        while(list.at(i).type!="("){
                            i++;
                        }
                        new_sub_block.cond = "";
                        new_sub_block.cond = new_sub_block.cond + list.at(i).value;
                        curves++;
                        i++;
                        while(curves>0){
                           if(list.at(i).type=="(") {
                               curves++;
                           }else if (list.at(i).type==")"){
                               curves--;
                           }
                           new_sub_block.cond = new_sub_block.cond + list.at(i).value;
                           
                           i++;
                        }
                      
                        while(list.at(i).type=="SPACE" || list.at(i).type=="ENTER"){
                            i++;
                        }
                        if(list.at(i).type=="{"){
                            braces=1;
                            i++;
                            new_sub_block.start_at =i;
                            while(braces>0){
                                if(list.at(i).type=="{"){
                                    braces++;
                                }else if(list.at(i).type=="}"){
                                    braces--;
                                }
                                if(list.at(i).type=="IF"){
                                    i= get_blocks(list,i);
                                }else{
                                    i++;
                                }
                            }
                            new_sub_block.end_at = i-2; 
                            each_block.end_at = i-2;   
                        }else{
                            new_sub_block.start_at = i;
                            while(list.at(i).type!=";"){
                                i++;
                            }
                            new_sub_block.end_at = i;
                            i++;
                        }
                        each_block.blocks.push_back(new_sub_block);
                    }else{
                        if(list.at(i).type=="{"){
                            braces=1;
                            i++;
                            new_sub_block.start_at =i;
                            while(braces>0){
                                if(list.at(i).type=="{"){
                                    braces++;
                                }else if(list.at(i).type=="}"){
                                    braces--;
                                }
                                if(list.at(i).type=="IF"){
                                    i= get_blocks(list,i);
                                }else{
                                    i++;
                                }
                            }
                            new_sub_block.end_at = i-2;                                                        
                        }else{
                            new_sub_block.start_at = i;
                            while(list.at(i).type!=";"){
                                i++;
                            }
                            new_sub_block.end_at = i;
                            i++;
                        }
                        int j = 0;
                        new_sub_block.cond = " ( ";
                        for(j=0;j<each_block.blocks.size()-1;j++){
                            new_sub_block.cond = new_sub_block.cond + "! "+each_block.blocks.at(j).cond + " && ";
                        }
                        new_sub_block.cond = new_sub_block.cond + "! "+each_block.blocks.at(j).cond + " )";
                        
                        each_block.end_at= new_sub_block.end_at;
                        each_block.blocks.push_back(new_sub_block);
                        block_list.push_back(each_block);
                        each_block =  block();
                        if(k>0){
				            return i;
				        }
				        i--;
                        break;
                    }
                }else{
                    i--;
                    int j = 0;
                    new_sub_block.cond = " ( ";
                    for(j=0;j<each_block.blocks.size()-1;j++){
                        new_sub_block.cond = new_sub_block.cond + "! "+each_block.blocks.at(j).cond + " && ";
                    }
                    new_sub_block.cond = new_sub_block.cond + "! "+each_block.blocks.at(j).cond + " )";
                    new_sub_block.start_at = i;
                    new_sub_block.end_at = -1;

                    each_block.blocks.push_back(new_sub_block);
                    block_list.push_back(each_block);
                    each_block = block();
                    break;

                }
            }
        }
        if(k>0){
            return i++;
        }
    }
    return k;
}




void get_paths(vector<lex_class> list, vector<block> block_list,vector<int> each_path, int prsnt_block, int size , int wp_at){
    int i,j,tempi;

    if(prsnt_block==size){
        cout << "total no. of blocks : "<< block_list.size() << endl;
    	int assert_count;
        ofstream singlepath;
        string path_string;
        static string recheck_path;
        static int z=1;
        assert_count=1;
        std::stringstream sstm,sstmprev;
        
        j=0;
        int k,nearest_s,nearest_e;
        nearest_s=list.size();
        nearest_e=list.size();
        while(j<list.size()){
            
            nearest_s=list.size();
            for(k=0;k<block_list.size();k++){
                
                if(j<=block_list.at(k).start_at){
                    if(nearest_s>block_list.at(k).start_at){
                        nearest_s=block_list.at(k).start_at;
                        //nearest_s will maintain the nearest main if block's starting point
                    }
                }
                if(j<block_list.at(k).end_at){
                    if(nearest_e>block_list.at(k).end_at){
                        nearest_e=block_list.at(k).end_at;
                        //nearest_e will maintain the nearest main if block's ending point
                    }
                }
            }
            //while j is less the next coming main if block
            while(j<=nearest_s){

                std::vector<int> inside_blocks;
                int last;
                for(k=0;k<block_list.size();k++){
                    if(block_list.at(k).mark==1){
                        //mark = 1 if the j in inside that block
                        inside_blocks.push_back(k);
                        //inside blocks is maintained to know in how many blocks the current j is present
                    }
                }
                //if j is inside atleast 1 block the if condition is entered
                if(inside_blocks.size()>0){
                    last=inside_blocks.at(inside_blocks.size()-1);
                    // last will contain the immediate parent block which has j
                    if((j>=block_list.at(last).blocks.at(each_path.at(last)).start_at && j<=block_list.at(last).blocks.at(each_path.at(last)).end_at) || j==nearest_s){
                        //above if will be entered when current j is inside the immediate parent block's sub-block in this current iteration
                        if(j==block_list.at(last).blocks.at(each_path.at(last)).start_at || j==nearest_s){
                            cout << "entred the if condition " << block_list.at(last).blocks.at(each_path.at(last)).cond << endl;
                            j=block_list.at(last).blocks.at(each_path.at(last)).start_at;

                            //wp_at has the current location of actual assert
                            if(j<=wp_at){//if j is less then wp_at then IF conditions are written as //@ assert IF..
                                path_string.append("//@ assert IF");
                                path_string.append(std::to_string(assert_count++));
                                path_string.append(": ");
                            }else{//if j is greater then wp_at then IF conditions are written as normal assert
                                path_string.append("assert");
                            }

                            path_string.append(block_list.at(last).blocks.at(each_path.at(last)).cond);
                            path_string.append(";\n");
                            if(block_list.at(last).blocks.at(each_path.at(last)).end_at!=-1){
                                path_string.append(list.at(j).value);
                                j++;
                            }else{
                                j=block_list.at(last).end_at+2;
                                block_list.at(last).mark=0;
                            }        
                        }else{                            
                            if(nearest_s>block_list.at(last).blocks.at(each_path.at(last)).end_at){
                                while(j<=block_list.at(last).blocks.at(each_path.at(last)).end_at){
                                    //singlepath << list.at(j).value;
                                    path_string.append(list.at(j).value);
                                    //cout << list.at(j).value;
                                    j++;
                                }

                            	j=block_list.at(last).end_at+2;
                                block_list.at(last).mark=0;
                            }else{
                                
                                while(j<nearest_s){
                                    
                                    //singlepath << list.at(j).value;
                                    path_string.append(list.at(j).value);
                                    //cout << list.at(j).value;
                                    j++;
                                }

                                for(k=0;k<block_list.size();k++){
                                    if(block_list.at(k).start_at==nearest_s){
                                        block_list.at(k).mark=1;
                                        break;
                                    }
                                }
                            }
                        }
                        
                    }else if(j>block_list.at(last).end_at){
                    	block_list.at(last).mark=0;
                    }
                  
                }else{
                    while(j<nearest_s){
                        path_string.append(list.at(j).value);
                        j++;
                    }
                    if(j==(list.size()) ){

                        recheck_path = path_string;
                        ifstream previousfile;
                        string prevpath;

                        if(z>1){

                            sstmprev << "singlepaths/singlepath_" << z-1 <<".c";
                            string prevres = sstmprev.str();
                            previousfile.open(prevres.c_str());
                            if(previousfile.is_open()){
                                previousfile.seekg(0,std::ios::end);
                                prevpath.reserve(previousfile.tellg());
                                previousfile.seekg(0,std::ios::beg);
                                prevpath.assign((std::istreambuf_iterator<char>(previousfile)),std::istreambuf_iterator<char>());
//                                cout << "recheck_path ------------\n\n" << recheck_path.size() << "\n\n\n";
//                                cout << "prevpath ------------\n\n" << prevpath.size() << "\n\n\n";
                                if(recheck_path==prevpath){
                                    previousfile.close();
                                    return;
                                }
                            }
                        }
                        system("exec rm -r singlepaths");
                        system("mkdir singlepaths");
                        sstm << "singlepaths/singlepath_" << z++ <<".c";
                        string result = sstm.str();
                        singlepath.open (result.c_str());
                        singlepath << path_string;
                        singlepath.close();
                        std::stringstream sstm_;


                        sstm_ << "./modify.py "<<(z-1);
                        result=sstm_.str();
                        cout << "executing ./modify.py " << (z-1) << endl;
                        system(result.c_str());


                        cout << "Done" << endl;
                        return;
                    }
                    for(k=0;k<block_list.size();k++){
                        if(block_list.at(k).start_at==nearest_s){
                            block_list.at(k).mark=1;
                        }
                    }    
                }
            }
            
        }

    }else{
        
        for(i=0;i<block_list.at(prsnt_block).blocks.size();i++){
            each_path.at(prsnt_block)= i;
            get_paths(list, block_list, each_path, prsnt_block+1, size, wp_at);
        }
    }
}


struct less_than_key
{
    inline bool operator() (const block block1, const block block2)
    {
        return (block1.start_at < block2.start_at);
    }
};

// This will make the current assert as ACTUAL
int generate(std::vector<lex_class> list0, int assert_num){
  	int i,j,assert_count;

  	std::ofstream ofs;
  	ofs.open("temp.c", std::ofstream::out | std::ofstream::trunc);
 	ofs.close();

  	ofstream myfile;
  	std::stringstream sstm;
	sstm << "temp.c";
  	string result = sstm.str();
  	myfile.open (result.c_str());
  	i=0;
  	assert_count=0;
  	int braces;
  	braces=0;
  	for(i=0;i<list0.size();i++){
        if(list0.at(i).type=="ASSERT"){
            assert_count++;
            if(assert_count==assert_num){
                myfile << "//@ assert ACTUAL: ";
                j=i+1;
                while(j<list0.size()){
                    if(list0.at(j).type!=";"){
                    	myfile << list0.at(j).value;
                    	j=j+1;
                    }else{
                        myfile << ';';
                        while(braces>0){
                            myfile << "\n }";
                            braces--;
                        }
                        break;
                    }
                    //cout << "entered  " << j<< endl;
                }
                break;
            }else if(assert_count<assert_num){
            	myfile << "//@ assert OLD" << assert_count << " :  ";
                i++;
                while(i<list0.size()){
                    if(list0.at(i).type!="ENTER"){
                        myfile << list0.at(i).value;
                        i++;
                    }else{
                    	myfile << list0.at(i).value;
                    	break;
                    }
                    
                    //cout << "entered  " << j<< endl;
                }
            }else{
                i=i+1;
                while(list0.at(i).type!="ENTER"){
                    i=i+1;
                }
                
            }
        }else{
            if(list0.at(i).value=="{"){
                braces++;
            }else if(list0.at(i).value=="}"){
                braces--;
            }
            myfile << list0.at(i).value;
            
        }

  }
  myfile.close();

  if(assert_count==assert_num){
    return 1;
  }else{
    return 0;
  }
}

// generating unroll_list
bool getnewlist(){
    int wp_at,i ;
    string delimiter = "`";
    string line;
    wp_at=-1;
    unroll_list.clear();
    //system("make");
    system("./ProPFA temp.c");
    ifstream finalfile ("lexfinal.txt");

    lex_class lex_object;
    if (finalfile.is_open())
    {
        i=0;
        while ( getline (finalfile,line) )
        {
            lex_object.value= line.substr(0, line.find(delimiter));
            lex_object.type= line.substr(line.find(delimiter)+1, line.length());
            if(lex_object.value=="$"){
                lex_object.value="\n";
            }
            if(lex_object.value=="%%"){
                lex_object.value="%";
            }
            unroll_list.push_back(lex_object);
            //cout << list0[i].value << "\t\t" << list0[i].type << endl;
            i=i+1;
        }
        //cout << "------------" << endl;
        finalfile.close();
        return true;
    }else{
        return false;
    }
}



int gettextfile(){
	int wp_at,i ;
	string delimiter = "`";
  	string line;
	wp_at=-1;
    list.clear();
	//system("make");
	system("./ProPFA temp.c");
	ifstream finalfile ("lexfinal.txt");
	
	lex_class lex_object;
	if (finalfile.is_open())
	{
	    i=0;
	    while ( getline (finalfile,line) )
	    {
	      	lex_object.value= line.substr(0, line.find(delimiter));
	      	lex_object.type= line.substr(line.find(delimiter)+1, line.length());
	      	if(lex_object.value=="$"){
	        	lex_object.value="\n";
	      	}
	      	if(lex_object.value=="%%"){
	        	lex_object.value="%";
	      	}
	      	if(lex_object.type=="WPCOND"){
	        	wp_at=i; 
	      	}
	      	list.push_back(lex_object);
	      	//cout << list0[i].value << "\t\t" << list0[i].type << endl;
	      	i=i+1;
	    }
	    //cout << "------------" << endl; 
	    finalfile.close();
	    return wp_at; //id (//@) of the actual assert
	}else{
		return -1;
	}
}



// once we know that current assert is inside the loop. 
// This pasre_while will be called to save the code before the while and code till the assert to use it later in handle_while function
vector<string> parse_while(std::vector<lex_class> list0, int while_at){
    int i,j;
    bool brace_on;
    brace_on=false;
    vector <string> whiles_list;
    string temp="if";
    int braces=0;
    i=while_at+1;
    temp="";
    while(list0.at(i).type!=")"){
    	temp=temp+list0.at(i).value;
    	i++;
    }
    temp=temp+list0.at(i).value+" ;";
    i++;
    while(i<list0.size()){
        if(list0.at(i).type=="{"){
        	if(braces==0){
        		i++;
        	}
            brace_on=true;
            braces++;
        }else if(list0.at(i).type=="}"){
        	if(braces==1 && brace_on){
        		i++;
        	}
            braces--;
        }
        if(list0.at(i).type=="ASSERT"){
        	temp = temp + "//@ assert OLDER: ";
            i++;
            while(list0.at(i).type!="ENTER"){
            	temp = temp +  list0.at(i).value;
            	i++;
            }
            temp = temp +  list0.at(i).value;
        }
        else if(list0.at(i).type==";"){
            temp=temp+list0.at(i).value;
        }else if(list0.at(i).type=="SPACE"){
            temp=temp+" ";
        }
        else{
            temp=temp+list0.at(i).value;
        }
        i++;
        if(brace_on && braces==0){
             temp=temp+"\n";
            whiles_list.push_back(temp);
            break;
        }
    }

    i=while_at+1;
    braces=0;
    temp="";
    while(list0.at(i).type!=")"){
    	temp=temp+list0.at(i).value;
    	i++;
    }
    temp=temp+list0.at(i).value+" ;";
    i++;
    while(i<list0.size()){
        if(list0.at(i).type=="{"){
        	if(braces==0){
        		i++;
        	}
            braces++;
        }else if(list0.at(i).type=="}"){
            if(braces==1){
        		i++;
        	}
            braces--;
        }

        if(list0.at(i).type=="ASSERT"){
            temp = temp + "//@ assert ACTUAL:";
            j=i+1;
            while(j<list0.size()){
                if(list0.at(j).type!=";"){
                	
            		temp = temp + list0.at(j).value;
                	j=j+1;
                	
                }else{
                    temp = temp +  ';';
                    while(braces>1){
                        temp = temp +  "\n}";
                        braces--;
                    }
                    break;
                }
                //cout << "entered  " << j<< endl;
            }
            whiles_list.push_back(temp);
            break;
        }
        else if(list0.at(i).type==";"){
            temp=temp+list0.at(i).value;
        }else{
            temp=temp+list0.at(i).value;
        }
        i++;
    }
    return whiles_list;
}



//once we know that current assert is in while this function is called to handle the assert.

int handle_while(std::vector<lex_class> list0, int while_at,int assert_at){
  	int i,j,assert_count,k,max;
  	max=0;
  	string result ;
  	ofstream myfile;
  	std::stringstream sstm;
  	k=1;
  	vector<string> whiles_list;
  	
  	whiles_list = parse_while(list0,while_at);
  	cout << "enter the number of iterations for the loop : \n";
    cout << "----------------------------------------------------------\n";
    cout << "while "<<whiles_list.at(0) << endl;
    cout << "----------------------------------------------------------\n";
  	cin >> max;
  	//cout << "max : " << max; 
  	while(k<=max){
  		
      	sstm.str(std::string());
      	sstm << "temp.c";
      	result = sstm.str();
      	myfile.open (result.c_str());
      	i=0;
      	assert_count=0;
      	int braces;
      	braces=0;
      	for(i=0;i<while_at;i++){
            if(list0.at(i).type=="ASSERT"){
                assert_count++;
                i=i+1;
                myfile << "//@ assert OLD"<<i<<" : ";
                while(list0.at(i).type!="ENTER"){
                	myfile << list0.at(i).value;
                    i=i+1;
                }
                myfile << list0.at(i).value;
            }else{
                if(list0.at(i).value=="{"){
                    braces++;
                }else if(list0.at(i).value=="}"){
                    braces--;
                }
                myfile << list0.at(i).value;
                
            }

      	}
      	int temp=0;

      	temp=1;
        string firstpart,rep;
        rep = "OLDER";
        
      	while(temp<k){
            firstpart = whiles_list.at(0);
      		myfile << "//@ assert LOOP" << temp << " : ";
      		firstpart.replace(firstpart.find(rep),rep.length(),"OLDER"+to_string(temp));
           	myfile << firstpart;
           	temp++;
      	}
      	
      	myfile << "//@ assert LOOP" << temp << " : ";
      	myfile << whiles_list.at(1);
      	while(braces>0){
        	myfile << "\n}";
        	braces--;
      	}
      	
      	k++;
      	myfile.close();


    	list.clear();
    	int wp_at,size;
    	wp_at=gettextfile();
    	
        
    	if(wp_at!=-1){
    		block_list.clear();
    		
    		get_blocks(list,0);

    		if(block_list.size()!=0){
			    std::sort(block_list.begin(), block_list.end(), less_than_key());
			    	
			    vector<int> each_path;
			    size =block_list.size();
			    //cout << size << endl;
			    for(i=0;i<block_list.size();i++){
			    	//cout << "cond   " << block_list.at(i).blocks.at(0).cond << endl;
			        each_path.push_back(0);
			    }
                get_paths(list, block_list, each_path, 0, size ,wp_at );
			    //cout << "comple" << endl;
			}else{
				static int temps=1;
				std::stringstream for_cmd;
                cout << "Generating the WP-Conditions for the current assert........."<< endl;
                for_cmd << (string(FRAMA_C) + string(" -wp -wp-timeout 50 -wp-model 'Hoare' -wp-simpl  temp.c -wp-out singlepaths/singlepath_")) << temps;
                temps++;
			    string cmd = for_cmd.str();
			    system(cmd.c_str());
			    cout << "Done" << endl;
			}
    	}
  	}
  	return 0;
}




int checkloop(std::vector<lex_class> list0, int assert_num){
    int i,assert_count,braces;
    bool while_on = false;
    assert_count=0;
    braces=0;
    int val_ret=-1;

    for(i=0;i<list0.size();i++){
        if(list0.at(i).type=="WHILE"){
            while_on=true;
            val_ret=i;
        }
        if(list0.at(i).type=="ASSERT"){
            
            assert_count++;

            if(assert_count==assert_num && while_on){
                //cout << val_ret;
                return val_ret;
            }

            if(assert_count>=assert_num){
                
                return 0;
            }
        }
        if(list0.at(i).type=="{" && while_on){
            braces++;
        }else if(list0.at(i).type=="}" && while_on){
            braces--;
            if(braces==0){
                while_on=false;
                val_ret=-1;
            }
        }
    }
    return -1;
}
//unrolls the loop
void unroll_whiles(std::vector<lex_class> list0,std::vector<while_blocks> while_lists,std::vector<int> unroll_array,int size,int present){
    if(size==present){
        int list_id,while_id,unroll_id; //list_id: iterating over list0, while_id: iterating over while_lists
        ofstream myfile;
        std::stringstream sstm;
        sstm << "temp.c";
        string result = sstm.str();
        myfile.open (result.c_str());
        list_id=0;
        //This iterates over all the while loops in while_lists
        for(while_id=0;while_id<while_lists.size();while_id++){
            // it will write everything before one unprocessed while
            while(list_id<while_lists.at(while_id).start-1){
                myfile << list0.at(list_id).value;
                list_id++;
            }

            list_id++;
            // Unrolling one loop at a time with the current combinational unrolling factor 
            for(unroll_id=0;unroll_id<unroll_array.at(while_id);unroll_id++){
                myfile << "if";
                int local_id;
                local_id=while_lists.at(while_id).start;
                while(local_id<=while_lists.at(while_id).end){
                    myfile << list0.at(local_id).value;
                    local_id++;
                }
                myfile << "\n";
            }
            list_id=while_lists.at(while_id).end+1;
        }
        while(list_id<list0.size()){
            myfile << list0.at(list_id).value;
            list_id++;
        }
        myfile.close();
//        cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" << endl;
//        system("cat temp.c");
//        cout << "\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n" << endl;
        if(getnewlist()){
            int i;

            block_list.clear();

            get_blocks(unroll_list,0);
            if(block_list.size()!=0){
                std::sort(block_list.begin(), block_list.end(), less_than_key());

                vector<int> each_path;
                size =block_list.size();
                //cout << size << endl;
                for(i=0;i<block_list.size();i++){
                    //cout << "cond   " << block_list.at(i).blocks.at(0).cond << endl;
                    each_path.push_back(0);
                }

                cout << "generating all possible paths for final assertion" << endl;
                get_paths(unroll_list, block_list, each_path, 0, size ,unroll_list.size());
                //cout << "comple" << endl;
            }else{
                system("exec rm -r singlepaths");
                system("mkdir singlepaths");
                cout << "executing ./modify.py 1" << endl;
                system("./modify.py 1");

                cout << "Done"<<endl;
            }

        }else{
            exit(1);
        }
    }else{
        int i;
        for(i=0;i<while_lists.at(present).unroll_no;i++){
            unroll_array.at(present)=i;
            unroll_whiles(list0,while_lists,unroll_array,size,present+1);
        }
    }

}

// Getting the while loop, user input:unrolling factor
void get_while_blocks(std::vector<int> unroll_while_list,std::vector<lex_class> list0){
    int i,j,braces=0,max;
    vector<int> unroll_array; //used to generate all possible combinations of loop
    std::vector<while_blocks> while_lists; //list of all whiles
    while_blocks while_object;
    for(i=0;i<unroll_while_list.size();i++){
        unroll_array.push_back(0); //initialize with 0
    }

    for(i=unroll_while_list.size()-1;i>=0;i--){

        cout << "\n-------------------------------------------------------------------" << endl;
        cout << "while";
        j=unroll_while_list.at(i);
        j++;
        while_object.start=j;
        while(list0.at(j).type!=")"){
            cout << list0.at(j).value;
            j++;
        }
        cout << list0.at(j).value;
        j++;

        while(list0.at(j).type=="ENTER" || list0.at(j).type=="SPACE"){
            j++;
        }
        if(list0.at(j).type!="{"){
            while(list0.at(j).type!=";"){ //Handling one statement in the loop
                cout << list0.at(j).value;
                j++;
            }
            cout << list0.at(j).value;
            while_object.end=j;
        }else{
            braces=1;
            cout << list0.at(j).value;
            j++;
            while(braces>0){
                cout << list0.at(j).value;
                if(list0.at(j).type=="{"){
                    braces++;
                }else if(list0.at(j).type=="}"){
                    braces--;
                }
                j++;
            }
            while_object.end=j-1;
        }
        cout << "\n-------------------------------------------------------------------"<< endl;
        cout << "Please enter the number of times you want to unroll the above loop"<< endl;
        cin >> max;
        while_object.unroll_no=max+1;
        while_lists.push_back(while_object);
    }

    unroll_whiles(list0,while_lists,unroll_array,unroll_while_list.size(),0); //list 0: lex output of the original code
     //while_lists: list of all while blocks, unroll_array: for generating all possible combinations, 
    //unroll_while_list.size(): no. of while loops to unroll, 0:iterating over 1st element of unroll_array

    //
    return;
}

int main() {
    int i,j,check=1,k,wp_at,size,while_check;
  	string delimiter = "`";
  	string line;

  	//cout << "comple1" << endl;
  	ifstream myfile ("lexfile.txt");

  	std::vector<lex_class> list0;
  	lex_class lex_object;
  	// parsing the lexical file and saving the tokens with type in the lex_class list0.
  	if (myfile.is_open())
  	{

	    i=0;
        //Reading from lexfile.txt and writing it in list0
	    while ( getline (myfile,line) )
	    {
	      	lex_object.value= line.substr(0, line.find(delimiter));
	      	lex_object.type= line.substr(line.find(delimiter)+1, line.length());
	      	if(lex_object.value=="$"){
	        	lex_object.value="\n";
	      	}
	      	if(lex_object.value=="%%"){
	        	lex_object.value="%";
	      	}
	      	list0.push_back(lex_object);
	      	//cout << list0[i].value << "\t\t" << list0[i].type << endl;
	      	i=i+1;
	    }
	    myfile.close();
        int check_inv=0;
        // checking for invariants, if no invariant unroll, else do not add in whiles_to_unroll list
        vector<int> whiles_to_unroll;
        for(i=list0.size()-1;i>=0;i--){
            if(list0.at(i).type=="WHILE"){
                check_inv=0;
                for(j=i-1;j>=0;j--){
                    if(list0.at(j).type==";"){
                        check_inv++;
                        if(check_inv>1){
                            whiles_to_unroll.push_back(i);
                            break;
                        }
                    }else if(list0.at(j).type=="LOOP"){
                        break;
                    }
                }
            }
        }

        if( remove("ifpaths.txt")!=0 )
            perror( "Warning deleting file" );
        if( remove( "pathprobs.txt" ) != 0)
            perror( "Warning deleting file" );
        if(whiles_to_unroll.size()>0){
            get_while_blocks(whiles_to_unroll,list0);
            printprobs();
            return 0;
        }


        block_list.clear();

        get_blocks(list0,0);
        if(block_list.size()!=0){
            std::sort(block_list.begin(), block_list.end(), less_than_key());

            vector<int> each_path;
            size =block_list.size();
            //cout << size << endl;
            for(i=0;i<block_list.size();i++){
                //cout << "cond   " << block_list.at(i).blocks.at(0).cond << endl;
                each_path.push_back(0);
            }
            cout << "generating all possible paths for final assertion" << endl;
            get_paths(list0, block_list, each_path, 0, size ,list0.size());
            //cout << "comple" << endl;
        }else{
            ofstream tempfile;
            tempfile.open("temp.c");
            for(int tempi=0;tempi<list0.size();tempi++){
                tempfile << list0.at(tempi).value;
            }
            tempfile.close();
            system("exec rm -r singlepaths");
            system("mkdir singlepaths");
            cout << "executing ./modify.py 1"<< endl;
            system("./modify.py 1");

            cout << "Done"<<endl;
        }

        printprobs();
        //system("./getconds.py");
  	}
  	else
    	cout << "Unable to open the given file";

  	return 0;
}
