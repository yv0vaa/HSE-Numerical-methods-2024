long double T_k(long double x, int k) {
	long double t_0 = 1.0, t_1 = x;
	for (int i = 2; i <= k; i++) {
		long double cur = 2 * x * t_1 - t_0;
		t_0 = t_1;
		t_1 = cur
	}
	return t_1;
}