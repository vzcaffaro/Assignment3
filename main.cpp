#include "GenStack.cpp"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool checkFile(string file_arg); //method to check if file is ok

int main(int argc, char** argv)
{




    bool fileok; //stores whether the file doesnt have delimiter errors
    bool checking = true; //stores whether user wants to check a file for errors
    char input; //records user input
    string file_arg = argv[1]; //assigns initial file equal to what was entered in the command line
    string nextFile;//stores user entry for next file to check

    fileok = checkFile(file_arg);//runs method to check a file, returns true if file has no delimiter syntax errors


    while(checking==true) //while the user wants to check a file
    {

        if(fileok == true) //if no errors are found
        {
            cout<<"No delimiter errors were found in the file. Would you like to check another file? Y/N "<<endl;
            cin>>input; //records user input
            input = toupper(input);
        }


        else if(fileok == false)
        {
            cout<<"Error found, program exited. "<<endl;
            break; //ends program
        }



        while(input != 'Y' && input != 'N') //while invalid characters are entered
        {
            cout<<"That is not a valid entry. Would you like to check another file? Enter Y for yes or N for no. "<<endl;
            cin>>input;
            input = toupper(input);
        }
        if(input == 'Y')
        {
            cout<<"What is the name of the file you would like to check? "<<endl;
            cin>>nextFile;
            fileok = checkFile(nextFile);

        }

        else if (input == 'N')
        {
            cout<<"Program exited successfully. "<<endl;
            checking = false;
        }

    }



}

bool checkFile(string file)
{
    int counter=0; //stores the line number where the error happens
    string line;//temporarily stores one line from the file at a time
    bool fileok; //stores if file doesnt have delimiter errors

    GenStack<char> mystack; //creates a stack of size 100

    ifstream inf; //creates an in stream for reading the file
    inf.open(file); //opens the file for reading
    while (inf.peek()!=EOF)//uses peek to return whether or not the file has a next line
    {

        getline(inf, line); //reads line and stores in variable dnastrin
        ++counter; //increments count for which line the error is at
        for(int i=0; i<line.length();++i) //allows for indexing characters in the string
        {
            if(line[i]=='{' || line[i]=='(' || line[i]=='[') //if it detects a right-facing delimiter
                mystack.push(line[i]); //it will add to stack, as you cannot get an error on a right facing delimiter
            else if(line[i]=='}')
            {
                if (mystack.peek()=='{') //if this is the correct delimiter
                {
                    mystack.pop(); //remove the right facing delimiter
                }
                else if(mystack.peek()=='[')
                {
                    cout<<"Error at line "<<counter<<": Expected ']' and found '}'"<<endl;
                    fileok = false;
                }
                else if(mystack.peek()=='(')
                {
                    cout<<"Error at line "<<counter<<": Expected ')' and found '}'"<<endl;
                    fileok = false;
                }
                else if(mystack.peek() == '\0')
                {
                    cout<<"Error at line "<<counter<<": Did not expect any left-facing delimiters. "<<endl;
                    fileok = false;
                }
            }
            else if(line[i]==']')
            {
                if (mystack.peek()=='[')
                {
                    mystack.pop();
                }
                else if(mystack.peek()=='{')
                {
                    cout<<"Error at line "<<counter<<": Expected '}' and found ']'"<<endl;
                    fileok = false;
                }
                else if(mystack.peek()=='(')
                {
                    cout<<"Error at line "<<counter<<": Expected ')' and found ']'"<<endl;
                    fileok = false;
                }
                else if(mystack.peek() == '\0')
                {
                    cout<<"Error at line "<<counter<<": Did not expect any left-facing delimiters. "<<endl;
                    fileok = false;
                }
            }
            else if(line[i]==')')
            {
                if (mystack.peek()=='(')
                {
                    mystack.pop();
                }
                else if(mystack.peek()=='{')
                {
                    cout<<"Error at line "<<counter<<": Expected '}' and found ')'"<<endl;
                    fileok = false;
                }
                else if(mystack.peek()=='[')
                {
                    cout<<"Error at line "<<counter<<": Expected ']' and found ')'"<<endl;
                    fileok = false;
                }
                else if(mystack.peek() == '\0')
                {
                    cout<<"Error at line "<<counter<<": Did not expect any left-facing delimiters. "<<endl;
                    fileok = false;
                }
            }

        }
    }

    return fileok;



}
