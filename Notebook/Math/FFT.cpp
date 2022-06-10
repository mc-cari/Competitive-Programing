#include "../Header.cpp"

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd> & a, bool invert) {
    int n = a.size();
    if (n == 1)
        return;

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++) {
        a0[i] = a[2*i];
        a1[i] = a[2*i+1];
    }
    fft(a0, invert);
    fft(a1, invert);

    double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++) {
        a[i] = a0[i] + w * a1[i];
        a[i + n/2] = a0[i] - w * a1[i];
        if (invert) {
            a[i] /= 2;
            a[i + n/2] /= 2;
        }
        w *= wn;
    }
}
//Polinomios
vl multiply(vl const& a, vl const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    fft(fa, true);

    vl result(n);
    for (int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
int main()
{

    int t;
    cin>>t;
    while(t--)
    {
        vl a,b;
        ll n,x;
        cin>>n;
        for(int i=0;i<n+1;i++)
        {
            cin>>x;
            a.push_back(x);
        }
        cin>>n;
        for(int i=0;i<n+1;i++)
        {
            cin>>x;
            b.push_back(x);
        }
        for(int i=0;i<a.size();i++)
        {
            cout<<a[i]<<" ";
        }cout<<endl;
        for(int i=0;i<b.size();i++)
        {
            cout<<b[i]<<" ";
        }cout<<endl;
        vl res=multiply(a,b);
        cout<<res.size()-1<<"\n";
        for(int i=0;i<res.size();i++)
        {
            cout<<res[i];
            i<res.size()-1? cout<<" " : cout<<"\n";
        }
    }
    /*
    //Arregla el resultado despues de multiplicar big integers
    int carry = 0;
    for (int i = 0; i < n; i++){
        result[i] += carry;
        carry = result[i] / 10;
        result[i] %= 10;
    }*/
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
	return 0;
}
