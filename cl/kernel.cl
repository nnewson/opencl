kernel void square(const float bid, const float ask,  global float* spreads, 
				   const unsigned int count, 
				   global float* resultBids, global float* resultAsks, global unsigned char* backwardated)
{
	int i = get_global_id(0);
	if (i < count)
	{
		resultBids[i] = bid - spreads[i];
		resultAsks[i] = ask + spreads[i];

		backwardated[i] = resultBids[i] >= resultAsks[i];
	}
}