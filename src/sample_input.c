void assert(int dummy_var) {}

void test(int n, int x) {
	
	int y = 1;
	while (n < x) {
		y = y * 2;
		n = n + 2;
	}
	assert(x<=n);
	return;
}