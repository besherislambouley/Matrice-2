/*
 * add the cells in decreasing order according to a[i][j] , mark them and merge them with adjacent marked cells using dsu 
 * we store in every component the queries about cells in this component
 * when two components are merged we check it there a similar query in both components we answer it and remove it from the resulting component
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 270
//#define mp make_pair
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
#define all(x) x.begin(), x.end()
#define gc getchar_unlocked
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll inf=1e18;
const ll mod=1e9+7;
const ld pai=acos(-1);
int n , q ;
vpi v ;
int a [309][309] , done [309][309] ;
int p [100009] , ans [20009] ;
set < int > que [100009] ;
int X [] = { -1 , 0 , 1 , 0 } ;
int Y [] = { 0 , 1 , 0 , -1 } ;
int val ( int x , int y ) { return x * n + y ; }
int get ( int node ) {
	if ( p [node] == node ) return node ;
	return p [node] = get ( p [node] ) ;
}
void merge ( int a , int b , int cost ) {
	a = get ( a ) , b = get ( b ) ; 
	if ( a == b ) return ;
	if ( que [a] .size () > que [b].size() ) swap ( a , b ) ;
	vi ret ; 
	for ( auto u : que[a] ) {
		if ( que [b] . count ( u ) ) {
			ret .pb ( u ) ;
		}
	}
	for ( auto u : ret ) {
		ans [ u ] = cost ;
		que [a] .era ( u ) ;
		que [b] .era ( u ) ;
	}
	for ( auto u : que[a] ) que [b] .ins ( u ) ;
	p [a] = b ;
}
void add ( int x , int y , int cost ) {
	done [x][y] = 1 ;
	for ( int i = 0 ; i < 4 ; i ++ ) {
		int nx = x + X [i] ;
		int ny = y + Y [i] ;
		if ( nx < n && nx >= 0 && ny < n && ny >= 0 && done [nx][ny] ) {
			merge ( val ( x , y ) , val ( nx , ny ) , cost ) ; 
		}
	}	
}
int main () {
	freopen ( "matrice2.in" , "r" , stdin ) ;
	freopen ( "matrice2.out", "w" , stdout) ;
	cin >> n >> q ;
	for ( int i = 0 ; i < n ; i ++ ) {
		for ( int j = 0 ; j < n ; j ++ ) {
			scanf("%d",&a[i][j]) ; 
			p [ val (i,j) ] = val (i,j) ;
			v.pb ( { a[i][j] , val (i,j) } ) ; 
		}
	}
	for ( int i = 0 ; i < q ; i ++ ) {
		int X1 , Y1 , X2 , Y2 ;
		scanf("%d%d%d%d",&X1,&Y1,&X2,&Y2) ;
		X1 -- , Y1 -- , X2 -- , Y2 -- ;
		que [ val(X1,Y1) ] . ins ( i ) ;
		que [ val(X2,Y2) ] . ins ( i ) ; 
	}
	sort ( all ( v ) ) ;
	reverse ( all ( v ) ) ;
	for ( auto u : v ) {
		int x = u.se / n , y = u .se % n ;
		add ( x , y , u.fi ) ;
	}
	for ( int i = 0 ; i < q ; i ++ ) printf("%d\n",ans[i]) ; 

}
