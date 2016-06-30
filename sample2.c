void assert(int dummy_var) {}
void main(int x, int y, int fx, int fy, int fz, int fk)
{
	int h, sum;
	int n=3;
	int i=0;
	int k=0;
	h=x-y;
	assert(h>1);
	sum=sum+fx;
	sum=sum+2*fy;
	sum=sum+2*fz;
	sum=sum+2*fk;
	sum=sum+fk;
	return 0;
}
