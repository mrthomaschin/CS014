#include <iostream>
#include <string>
#include <stack>

using namespace std;


//if open {,(,[, append to stack
//if close },),] pop everything until opening
//if stack is not empty, false;


bool test(string exp)
{

    stack<char> stack;

    if(exp.at(0) == ')' || exp.at(0) == ']' || exp.at(0) == '}')    //condition
    {
        return false;
    }

    for(int x = 0; x < exp.size(); x++)
    {
        if(exp.at(x) == ')')
        {
            while(stack.top() != '(')
            {
                stack.pop();
            }

            stack.pop(); //pop one more
        }
        else
            if(exp.at(x) == '}')
            {
                while(stack.top() != '{')
                {
                    stack.pop();
                }
    
                stack.pop(); //pop one more
            }
            else   
                if(exp.at(x) == ']')
                {
                    while(stack.top() != '[')
                    {
                        stack.pop();
                    }
        
                    stack.pop(); //pop one more
                }
                else
                    stack.push(exp.at(x));
    }

    if(stack.empty() == true)
    {
        return true;
    }
    else   
        return false;
}



int main()
{
    bool result = false;
    string exp = "[(A+B)]{C-D}{[(E-F)(G*H)]}";

    result = test(exp);

    if(result)
    {
        cout << "True" << endl;
    }
    else
    {
        cout << "False" << endl;
    }

    return 0;
}