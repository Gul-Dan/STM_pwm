

static int getCount()
{
  static unsigned int count = -1;
  count = ++count<128 ? count : 0;
  return count;
}

static int getSin(int count)
{
  /*flash*/ static unsigned char SinParam [128] =
  {
	64,	67,	70,	73,	76,	79,	82,	85,
	88,	91,	94,	96,	99,	102,	104,	106,
	109,	111,	113,	115,	117,	118,	120,	121,
	123,	124,	125,	126,	126,	127,	127,	127,
	127,	127,	127,	127,	126,	126,	125,	124,
	123,	121,	120,	118,	117,	115,	113,	111,
	109,	106,	104,	102,	99,	96,	94,	91,
	88,	85,	82,	79,	76,	73,	70,	67,
	64,	60,	57,	54,	51,	48,	45,	42,
	39,	36,	33,	31,	28,	25,	23,	21,
	18,	16,	14,	12,	10,	9,	7,	6,
	4,	3,	2,	1,	1,	0,	0,	0,
	0,	0,	0,	0,	1,	1,	2,	3,
	4,	6,	7,	9,	10,	12,	14,	16,
	18,	21,	23,	25,	28,	31,	33,	36,
	39,	42,	45,	48,	51,	54,	57,	60
  };
  return SinParam[count];
}