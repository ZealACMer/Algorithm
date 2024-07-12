//中缀表达式转后缀表达式
#include <iostream>
#include <string>
#include <stack>

bool priority(char ch, char topch)
{
    if((ch == '*' || ch == '/') && (topch == '+' || topch == '-'))
    {
        return true;
    }
    if(topch == '(' && ch != ')')
    {
        return true;
    }
    return false;
}

std::string middleToEndExpr(std::string expr)
{
    std::string result;
    std::stack<char> stk;

    for(char ch : expr)
    {
        if(ch == ' ')
        {
            continue;
        }
        else if(ch >= '0' && ch <= '9')
        {
            result.push_back(ch);
        }
        else
        {
            for(;;)
            {
                if(stk.empty() || ch == '(')
                {
                    stk.push(ch);
                    break;
                }

                //比较当前符号ch和栈顶符号top的优先级
                char topch = stk.top();
                if(priority(ch, topch))
                {
                    stk.push(ch);
                    break;
                }
                else //如果遇到')'，一直出栈，直到'(‘
                {
                    stk.pop();
                    if(topch == '(')
                    {
                        break;
                    }
                    result.push_back(topch);
                }
            }
        }
    }
    while(!stk.empty())
    {
        result.push_back(stk.top());
        stk.pop();
    }
    return result;
}

int main(int argc, char** argv)
{
    std::cout << middleToEndExpr("(1+2)*(3+4)") << std::endl;
    std::cout << middleToEndExpr("2+(4+6)/2+6/3") << std::endl;
    return 0;
}
