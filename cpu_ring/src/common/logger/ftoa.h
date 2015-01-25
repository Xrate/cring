#ifndef FTOA_H
#define FTOA_H

inline int intToStr(int x, char str[], int d)
{
	int len = 0;
	while (x)
	{
		str[len++] = (x % 10) + '0';
		x = x / 10;
	}

	while (len < d)
		str[len++] = '0';

	for (int i = 0, j = len - 1, temp; i < j; ++i, --j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return len;
}

inline void ftoa(double n, char *res, int before, int after)
{
	int ipart = static_cast<int>(n);
	double fpart = n - static_cast<double>(ipart);

	int i = intToStr(ipart, res, before);

	res[i] = '.'; ++i;
	for (short j = 0; j < after; ++j)
		fpart *= 10;
	i += intToStr(static_cast<int>(fpart), res + i, after);

	res[i] = ' ';
	res[i + 1] = '\0';
}

#endif // FTOA_H