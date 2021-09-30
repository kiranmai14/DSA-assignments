#include <iostream>
#include <string.h>
using namespace std;

class BigInt
{
public:
    string num;
    BigInt()
    {
        num = "";
    }
    BigInt(string x)
    {
        num = x;
    }
    void print()
    {
        cout << num << " ";
    }
    void add(BigInt a, BigInt b)
    {
        string s = "";
        int s1 = a.num.size() - 1, s2 = b.num.size() - 1;
        int carry = 0, val = 0;
        while (s1 >= 0 && s2 >= 0)
        {
            val = a.num[s1] - 48 + b.num[s2] - 48 + carry;
            if (val >= 10)
            {
                carry = val / 10;
                s = to_string(val % 10) + s;
            }
            else
            {
                s = to_string(val) + s;
                carry = 0;
            }

            s1--;
            s2--;
        }
        while (s1 >= 0)
        {
            val = a.num[s1] - 48 + carry;
            if (val >= 10)
            {
                carry = val / 10;
                s = to_string(val % 10) + s;
            }
            else
            {
                s = to_string(val) + s;
                carry = 0;
            }

            s1--;
        }
        while (s2 >= 0)
        {
            val = b.num[s2] - 48 + carry;
            if (val >= 10)
            {
                carry = val / 10;
                s = to_string(val % 10) + s;
            }
            else
            {
                s = to_string(val) + s;
                carry = 0;
            }
            s2--;
        }
        if (carry > 0)
        {
            s = to_string(carry) + s;
        }
        this->num = s;
    }
    bool checkMax(BigInt a, BigInt b)
    {
        if (a.num.size() == b.num.size())
        {
            int i = 0;
            while (a.num[i] == b.num[i])
            {
                i++;
            }
            if (a.num[i] > b.num[i])
                return 1;
            else
                return 0;
        }
        else if (a.num.size() > b.num.size())
            return 1;
        else
            return 0;
    }
    void removeZeroes(string &n)
    {
        int i = 0, s = 0, e = 0;
        bool flag = 0;
        while (n[i] == '0')
        {
            i++;
            flag = 1;
        }
        if (flag)
        {
            if (i == n.size())
                e = i - 1;
            else
                e = i;
            n.erase(s, e);
        }
    }
    void subtract(BigInt a, BigInt b)
    {
        string s = "";
        if (!checkMax(a, b))
        {
            string x = a.num;
            a.num = b.num;
            b.num = x;
        }
        int s1 = a.num.size() - 1, s2 = b.num.size() - 1;
        int borrow = 0, diff = 0;
        while (s1 >= 0 && s2 >= 0)
        {
            diff = a.num[s1] - b.num[s2] - borrow;
            if (diff < 0)
            {
                borrow = 1;
                diff += 10;
            }
            else
                borrow = 0;
            s = to_string(diff) + s;
            s1--;
            s2--;
        }
        while (s1 >= 0)
        {
            diff = a.num[s1] - 48 - borrow;
            if (diff < 0)
            {
                borrow = 1;
                diff += 10;
            }
            else
                borrow = 0;
            s = to_string(diff) + s;
            s1--;
        }
        this->removeZeroes(s);
        this->num = s;
    }
    void product(string n, int p, BigInt &prod)
    {
        int carry = 0, val = 0;
        for (int i = n.size() - 1; i >= 0; i--)
        {
            val = (n[i] - 48) * p + carry;
            if (val >= 10)
            {
                carry = val / 10;
                prod.num = to_string(val % 10) + prod.num;
            }
            else
            {
                carry = 0;
                prod.num = to_string(val) + prod.num;
            }
        }
    }
    void shift(string &n, int i)
    {
        for (int j = 0; j < i; j++)
            n += '0';
    }
    void multiply(BigInt a, BigInt b)
    {
        BigInt prod;
        BigInt sum;
        if (!checkMax(a, b))
        {
            string x = a.num;
            a.num = b.num;
            b.num = x;
        }
        int s1 = a.num.size() - 1, s2 = b.num.size() - 1;
        for (int j = s2; j >= 0; j--)
        {
            product(a.num, (b.num[j] - 48), prod);
            shift(prod.num, s2 - j);
            this->add(sum, prod);
            prod.num = "";
            sum.num = this->num;
        }
        this->removeZeroes(this->num);
    }
    void calculator()
    {
        BigInt a;
        BigInt b;
        string inp = "";
        cin >> inp;
        string x = "";
        int op = -1;
        BigInt l;
        BigInt r;
        for (int i = 0; i < inp.size(); i++)
        {
            int j=0,k=0;
            if (inp[i] == 'x')
            {
                j = i - 1;
                k = i + 1;
                while (j >= 0 && (inp[j] != '+' && inp[j] != '-' && inp[j] != 'x'))
                {
                    l.num = inp[j] + l.num;
                    j--;
                }
                while (k < inp.size() && (inp[k] != '+' && inp[k] != '-' && inp[k] != 'x'))
                {
                    r.num = r.num + inp[k];
                    k++;
                }
                this->multiply(l,r);
                inp.replace(j+1,k,this->num);
                this->num ="";
                l.num="";
                r.num="";
            }
            
        }
        for (int i = 0; i < inp.size(); i++)
        {
            if (inp[i] != '+' && inp[i] != '-')
            {
                x = x + inp[i];
            }
            else
            {
                if (a.num != "")
                {
                    b.num = x;
                    x = "";
                    if (op == 1)
                        a.add(a, b);
                    // a.print();
                    else if (op == 2)
                        a.subtract(a, b);
                }
                else
                {
                    a.num = x;
                    x = "";
                }
                if (inp[i] == '+')
                    op = 1;
                else if (inp[i] == '-')
                    op = 2;
            }
        }
        if (op == 1)
        {
            b = x;
            a.add(a, b);
        }
        else if (op == 2)
        {
            b = x;
            a.subtract(a, b);
        }

        a.print();
    }
};

int main()
{
    BigInt s;
    BigInt a("1221");
    BigInt b("151");
    while (1)
    {
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            s.multiply(a, b);
            s.print();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            s.calculator();
        case 5:
            return 0;
        }
    }
}