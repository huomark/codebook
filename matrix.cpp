struct matrix{
	std::vector<vector<int>>bas,ans,iu,yy,ansall;
	int n, m;

	void init(int _n, int _m){
		n=_n;m=_m;
		for(int i=0;i<n;i++){
			ans.emplace_back();
			for(int j=0;j<n;j++){
				if(j==i) ans.back().pb(1);
				else ans.back().pb(0);
			}
		}
	}

	void mul(int t){
		if(t==1) ansall=bas;
		else ansall=ans;
		
		yy.clear();
		for(int i=0;i<n;i++){
			std::vector<int>tt1;
			for(int j=0;j<n;j++){
				int nn=0;
				for(int k=0;k<n;k++){
					nn+=ansall[i][k]*bas[k][j];
					nn%=m;
				}
				tt1.pb(nn);
			}
			yy.pb(tt1);
		}
		if(t==1) bas=yy;
		else ans=yy;
	}

	void mul_k(int k){
		while(k){
			if(k&1) mul(2);
			mul(1);
			k>>=1;
		}
	}
};