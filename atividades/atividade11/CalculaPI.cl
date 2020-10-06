__kernel void CalculaPI(__global float* a, __global float* c, int iNumElements) {
	
	// Achar o índice global
	int iGID = get_global_id(0);

	if (iGID < iNumElements) {
		c[iGID] = a[2*iGID] * a[2*iGID] + a[2*iGID+1] * a[2*iGID+1]; 
	}
}
