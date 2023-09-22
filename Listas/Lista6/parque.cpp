#include <iostream>
using namespace std;

int calculateFun(int a, int V, int B)
{
    int x = V - (a - 1) * (a - 1) * B;
    return x < 0 ? 0 : x;
}

void knapSack(int dp[], int v[], int b[], int w[], int capacity, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = capacity; j >= w[i]; j--)
        {
            int maxFun = 0;
            int var = v[i];
            for (int k = 1; k <= j / w[i]; k++)
            {
                int num = dp[j - k * w[i]] + var;

                if (num > maxFun)
                {
                    maxFun = num;
                }
                var += calculateFun(k + 1, v[i], b[i]);
            }

            if (maxFun > dp[j])
            {
                dp[j] = maxFun;
            }
        }
    }
}

int main()
{
    int n, visits, maxCapacity = 0;
    int dp[25001] = {0};
    cin >> n;
    int v[n], b[n], w[n];
    for (int i = 0; i < n; i++)
    {
        cin >> v[i] >> b[i] >> w[i];
    }
    cin >> visits;
    int capacity[visits];
    for (int i = 0; i < visits; i++)
    {
        cin >> capacity[i];
        if (capacity[i] > maxCapacity)
        {
            maxCapacity = capacity[i];
        }
    }
    knapSack(dp, v, b, w, maxCapacity, n);

    for (int i = 0; i < visits; i++)
    {
        cout << i << ": " << dp[capacity[i]] << endl;
    }
    return 0;
}
