#include <iostream>
#include <sstream>
#include <string>
#include "unorderedMap.cpp"
int main()
{
    int n, k;
    cin >> n >> k;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    unordered_map<int, int> m;
    int count = 0;
    int vec[n];
    for (int i = 0; i < k; i++)
    {
        if (!m.find(arr[i]))
        {
            m.insert(arr[i], 1);
            count++;
        }
        else
        {
            m.insert(arr[i], m[arr[i]] + 1);
        }
    }
    int j = 0;
    vec[j++] = count;
    bool flag = 0;
    for (int i = k; i < n; i++)
    {
        flag = 0;
        if (m[arr[i - k]] == 1)
        {
            count--;
        }
        m.insert(arr[i-k], m[arr[i-k]] - 1);
        if (!m.find(arr[i]))
        {
            count++;
            m.insert(arr[i],1);
            flag = 1;
        }
        else if (m[arr[i]] == 0)
        {
            count++;
        }
        if (!flag)
            m.insert(arr[i], m[arr[i]] + 1);
        vec[j++] = count;
    }
    for (int i = 0; i < j; i++)
        cout << vec[i] << " ";
}