#include <iostream>
#include <gtest/gtest.h>
#include <stack>
#include <string>

using namespace std;

string infix2postfix(string infix) 
{
  /*
  Rules
    - if ), pop until (
    - if incoming operator is of higher value than stack.top, push
    - if incoming operator is of lower value than stack.top, pop once and push incoming operator
    - (, ), *, /, +, - 
    - empty case, one digit case, crazy wrong case
  */

  stack<char> opstack;  //Initialize a stack
  string postfix;

  for(int x = 0; x < infix.size(); x++) //Traverse the given string
  {
    if(infix.at(x) != '(' && infix.at(x) != ')' && infix.at(x) != '*' && infix.at(x) != '/' && infix.at(x) != '+' &&   infix.at(x) != '-')//If character is a number in ASCII
    {
      postfix = postfix + infix.at(x);  //Append
    }
    else //Not a number
      if(infix.at(x) == '(')
      {
        opstack.push(infix.at(x));
      }
      else
        if(infix.at(x) == ')')
        {
          while(opstack.top() != '(')
          {
            postfix = postfix + opstack.top();
            opstack.pop();
          }

          opstack.pop(); // pop opening parenthese

        }
        else
          if(infix.at(x) == '*')
          {
            if(opstack.empty() == false)  //special cases
            {
              if(opstack.top() == '*' || opstack.top() == '/')  //equal precendence
              {
                postfix = postfix + opstack.top();
                opstack.pop();
              }
            }

            opstack.push('*');
          }
          else
            if(infix.at(x) == '/')
            {
              if(opstack.empty() == false)  //special cases
              {
                if(opstack.top() == '*' || opstack.top() == '/')  //equal precendence
                {
                  postfix = postfix + opstack.top();
                  opstack.pop();
                }
              }
  
              opstack.push('/');
            }
            else
              if(infix.at(x) == '+')
              {

                if(opstack.empty() == false)  //special cases
                {
                  if(opstack.top() == '*' || opstack.top() == '/') //higher precedence
                  {
                    postfix = postfix + opstack.top();
                    opstack.pop();
                  }
                }

                if(opstack.empty() == false)  //special cases
                {
                    if(opstack.top() == '+' || opstack.top() == '-')  //equal precendence
                    {
                      postfix = postfix + opstack.top();
                      opstack.pop();
                    }
                }

                opstack.push('+');
                
              }
              else
                if(infix.at(x) == '-')
                {
                  if(opstack.empty() == false)  //special cases
                  {
                    if(opstack.top() == '*' || opstack.top() == '/') //higher precedence
                    {
                      postfix = postfix + opstack.top();
                      opstack.pop();
                    }
                  }

                  if(opstack.empty() == false)  //special cases
                  {    
                      if(opstack.top() == '+' || opstack.top() == '-')  //equal precendence
                      {
                        postfix = postfix + opstack.top();
                        opstack.pop();
                      }
                  }
  
                  opstack.push('-');
                }
  }

  while(opstack.empty() == false)
  {
    postfix = postfix + opstack.top();
    opstack.pop();
  }

  return postfix;
}

int main() 
{
  EXPECT_STREQ(infix2postfix("2+3").c_str(), "23+");
  EXPECT_STREQ(infix2postfix("a*b").c_str(), "ab*");
  EXPECT_STREQ(infix2postfix("2+3*5").c_str(), "235*+");
  EXPECT_STREQ(infix2postfix("A+B*C+D").c_str(), "ABC*+D+");
  EXPECT_STREQ(infix2postfix("(A+B)*C-(D-E)*(F+G)").c_str(), "AB+C*DE-FG+*-");
  cout << infix2postfix("(A+B)*C-(D-E)*(F+G)").c_str() << endl;
}

