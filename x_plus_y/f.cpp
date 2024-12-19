const int base = 1 << 17;
long long drzewo1[base << 1];

void aktu(int v, long long wart){
drzewo1[v] = wart;
v >>= 1;
while(v > 0){
drzewo1[v] = drzewo1[v * 2];
drzewo1[v] += drzewo1[v * 2 + 1];
v >>= 1;
}
}

int odp(int a, int b){
long long wyni = 0;
a--;
b++;
while(b - a > 1){
if(!(a&1)){
wyni += drzewo1[a + 1];
}
if(b&1){
wyni += drzewo1[b - 1];
}
a >>= 1;
b >>= 1;
}
return wyni;
}