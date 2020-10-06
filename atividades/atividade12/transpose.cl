__kernel void transpose(__global float* a, __global float* b, int lins, int cols) {
	
	// Achar o índice global
	int iGID = get_global_id(0);
	int linA = iGID / cols;
	int colA = iGID % cols;
	
	if (iGID < lins * cols) {
		b[colA * lins + linA] = a[linA * cols + colA];
	}
}
